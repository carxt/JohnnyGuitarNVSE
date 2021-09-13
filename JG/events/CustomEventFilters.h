#pragma once
#include "GameForms.h"
#include "GameRTTI.h"	// for DYNAMIC_CAST
#include "events/EventFilteringInterface.h"

#if NULL
class JohnnyEventFiltersOneFormOneInt : EventHandlerFilterBase
{


	typedef  std::unordered_set<unsigned int> RefUnorderedSet;
private:
	RefUnorderedSet* Filters = nullptr;

	RefUnorderedSet* GetNthFilter(UInt32 filter)
	{
		if (filter >= numFilters) return nullptr;
		return &(Filters[filter]);
	}
public:

	JohnnyEventFiltersOneFormOneInt(void** filters, UInt32 nuFilters)
	{
		numFilters = nuFilters;
		Filters = new RefUnorderedSet[numFilters];
		GenFilters = new GenericFilters[numFilters];
		for (int i = 0; i < nuFilters; i++) GenFilters[i].ptr = filters[i];

	}
	virtual ~JohnnyEventFiltersOneFormOneInt()
	{
		delete[] Filters;
		delete[] GenFilters;
	}

	virtual bool IsInFilter(UInt32 filterNum, GenericFilters toSearch)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetNthFilter(filterNum))) return false;
		return  FilterSet->empty() || (FilterSet->find(toSearch.refID) != FilterSet->end());
	}


	virtual void InsertToFilter(UInt32 filterNum, GenericFilters toInsert)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetNthFilter(filterNum))) return;
		FilterSet->insert(toInsert.refID);
	}
	virtual void DeleteFromFilter(UInt32 filterNum, GenericFilters toDelete)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetNthFilter(filterNum))) return;
		FilterSet->erase(toDelete.refID);

	}
	virtual bool IsFilterEmpty(UInt32 filterNum)
	{
		RefUnorderedSet* FilterSet = GetNthFilter(filterNum);
		if (!FilterSet) return true;
		return FilterSet->empty();
	}
	virtual bool IsGenFilterEqual(GenericFilters Filter, UInt32 nuFilter)
	{
		return (Filter.ptr == GenFilters[nuFilter].ptr);
	}
	virtual bool IsAcceptedParameter(GenericFilters parameter)
	{
		return parameter.form->refID != 0x3B; // xMarker

	}

	virtual void SetUpFiltering()
	{
		if (GenFilters[1].intVal != -1) InsertToFilter(1, GenFilters[1].intVal);
		TESForm* currentFilter = GenFilters[0].form;
		if (!currentFilter) return;
		if (IS_TYPE(currentFilter, BGSListForm))
		{
			ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
			do {
				TESForm* it = iterator->data;
				if (IsAcceptedParameter(it))
					InsertToFilter(0, it->refID);
			} while (iterator = iterator->next);

		}
		else if (IsAcceptedParameter(currentFilter)) InsertToFilter(0, currentFilter->refID);

	}

};
void* __fastcall CreateOneFormOneIntFilter(void** Filters, UInt32 numFilters) {
	return new JohnnyEventFiltersOneFormOneInt(Filters, numFilters);
}
#endif






//== Demo's Generic Filter System


// Allow overloading lambda functions, used for std::visit on std::variants.
// Taken from https://www.cppstories.com/2018/09/visit-variants/. Also shows up in https://gummif.github.io/blog/overloading_lambdas.html.
template<class... Ts> struct overload : Ts...
{
	using Ts::operator()...;
};
template<class... Ts> overload(Ts...)->overload<Ts...>;


class GenericEventFilters : EventHandlerFilterBase
{
public:
	GenericEventFilters(FilterTypeSetArray &filters)
	{
		filtersArr = genFiltersArr = filters;
	}
	GenericEventFilters(FilterTypeSets& filter)
	{
		filtersArr = genFiltersArr = FilterTypeSetArray { filter };
	}

	bool IsInFilter(UInt32 const filterNum, FilterTypes toSearch) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetNthFilter(filterNum))) return false;
		bool const isFound = std::visit(overload{
		[](RefIDSet &arg1, RefID &arg2) { return arg1.empty() || arg1.find(arg2) != arg1.end(); },
		[](IntSet &arg1, int &arg2) { return arg1.empty() || arg1.find(arg2) != arg1.end(); },
		[](FloatSet &arg1, float &arg2) { return arg1.empty() || arg1.find(arg2) != arg1.end(); },
		[](StringSet &arg1, std::string &arg2) { return arg1.empty() || arg1.find(arg2) != arg1.end(); },
		[](auto &arg1, auto &arg2) { return false; /*Types do not match*/ },
			},	*filterSet, toSearch);
		return isFound;
	}
	bool IsInFilter(UInt32 const filterNum, TESForm* toSearch)
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetNthFilter(filterNum))) return false;
		bool const isFound = std::visit(overload{
		[&toSearch](RefIDSet& set) { return set.empty() || set.find(toSearch->refID) != set.end(); },
		[](auto& set) { return false; /*Types do not match*/ },
			}, *filterSet);
		return isFound;
	}

	bool IsBaseInFilter(UInt32 const filterNum, RefID toSearch)
	{
		if (!toSearch) return false;
		auto const formToSearch = LookupFormByID(toSearch);
		if (formToSearch->GetIsReference())
			toSearch = ((TESObjectREFR*)formToSearch)->baseForm->refID;
		return IsInFilter(filterNum, toSearch);
	}
	bool IsBaseInFilter(UInt32 const filterNum, TESForm* toSearch)
	{
		if (!toSearch) return false;
		if (toSearch->GetIsReference())
			toSearch = ((TESObjectREFR*)toSearch)->baseForm;
		return IsInFilter(filterNum, toSearch);
	}

	// Unused
	bool InsertToFilter(UInt32 const filterNum, FilterTypes toInsert) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetNthFilter(filterNum))) return false;
		bool const isInserted = std::visit(overload{
		[](RefIDSet& arg1, RefID& arg2) { return arg1.insert(arg2).second; },
		[](IntSet& arg1, int& arg2) { return arg1.insert(arg2).second; },
		[](FloatSet& arg1, float& arg2) { return arg1.insert(arg2).second; },
		[](StringSet& arg1, std::string& arg2) { return arg1.insert(arg2).second; },
		[](auto& arg1, auto& arg2) { return false; /*Types do not match*/ },
			}, *filterSet, toInsert);
		return isInserted;
	}

	// Unused
	bool DeleteFromFilter(UInt32 const filterNum, FilterTypes toDelete) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetNthFilter(filterNum))) return false;
		bool const isDeleted = std::visit(overload{
		[](RefIDSet& arg1, RefID &arg2) { return arg1.erase(arg2); },
		[](IntSet& arg1, int &arg2) { return arg1.erase(arg2); },
		[](FloatSet& arg1, float &arg2) { return arg1.erase(arg2); },
		[](StringSet& arg1, std::string &arg2) { return arg1.erase(arg2); },
		[](auto& arg1, auto& arg2)	/*Types do not match*/
		{
			size_t const t = 0;
			return t;
		},
			}, *filterSet, toDelete);
		return isDeleted;
	}

	// Unused
	bool IsFilterEmpty(UInt32 const filterNum) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetNthFilter(filterNum))) return true;	// technically empty if there is no filter
		bool const isEmpty = std::visit([](auto &filter) { return filter.empty(); }, *filterSet);
		return isEmpty;
	}
	
	bool IsGenFilterEqual(UInt32 const filterNum, FilterTypeSets const &cmpFilterSet) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetNthGenFilter(filterNum))) return false;
		return cmpFilterSet == *filterSet;
	}

	static bool IsDefaultFilterValue(FilterTypes const &filterVal)
	{
		bool const isDefault = std::visit(overload{
		[](RefID filter) { return filter == kIgnFilter_FormID; },
		[](int filter) { return filter == kIgnFilter_Int; },
		[](auto& filter) { return false; } /*Default case*/
		}, filterVal);
		return isDefault;
	}

	bool IsGenFilterEqualAlt(UInt32 const filterNum, FilterTypeSets const &cmpFilterSet) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetNthGenFilter(filterNum))) return false;
		bool const isEqual = std::visit(
		[](auto& genSet, auto& cmpSet)
		{
			// Use std::decay_t to remove const type from comparison.
			if constexpr (std::is_same_v<std::decay_t<decltype(genSet)>, std::decay_t<decltype(cmpSet)>>)
			{
				if (cmpSet.size() != genSet.size())
					return false;
				
				auto setElemIter = genSet.begin();
				for (auto cmpElemIter = cmpSet.begin(); setElemIter != genSet.end(); ++setElemIter, ++cmpElemIter)
				{
					if (IsDefaultFilterValue(*cmpElemIter))
						continue;
					if (*setElemIter != *cmpElemIter)
						return false;
				}
				return true;
			}
			return false;
		}, *filterSet, cmpFilterSet);
		return isEqual;
	}

	//	Unused in SetUpFiltering, so it's useless.
	bool IsAcceptedParameter(FilterTypes param) override
	{
	//	bool const isAccepted = std::visit(overload{
	//		[&](RefID filter) { return filter != g_xMarkerID; },
	//		[&](auto& filter) { return true; } /*Default case*/
	//		}, param);
	//	return isAccepted;
		return true;
	}

	static RefIDSet SetUpFormFilters(RefIDSet const &refIDFilters)
	{
		RefIDSet newSet;	// To avoid iterator invalidation by adding mid-loop, + avoid inconsistent behavior with deep form-lists.

		// Append forms that were inside form-lists to newSet.
		// Note: does not support deep form-lists.
		for (auto const& refIDIter : refIDFilters)
		{
			auto const formIter = LookupFormByID(refIDIter);
			if (auto const listForm = DYNAMIC_CAST(formIter, TESForm, BGSListForm))
			{
				// Insert only the form-list elements; omit the form-list itself.
				ListNode<TESForm>* listFormIter = listForm->list.Head();
				do { newSet.insert(listFormIter->Data()->refID); }
				while (listFormIter = listFormIter->next);
			}
			else
			{
				newSet.insert(refIDIter);
			}
		}

		newSet.erase(kIgnFilter_RefID);
		//newSet.erase(nullptr);	// maybe filtering to only null forms could be useful?
		return newSet;
	}

	// Modifies by reference.
	static void SetUpIntFilters(IntSet& intFilters)
	{
		intFilters.erase(kIgnFilter_Int);
	}
	
	void SetUpFiltering() override
	{
		// Filters out all -1 values from IntSets.
		// Transforms all BGSListForm*-type TESForm* into the TESForm* that were contained.
		// Filters out xMarker refs.
		for (auto &filterSetIter : filtersArr )
		{
			std::visit(overload{
			[](RefIDSet &filter)
			{
				filter = SetUpFormFilters(filter);	// todo: check if filterSet needs to be captured and set instead.
			},
			[](IntSet &filter)
			{
				SetUpIntFilters(filter);
			},
			[](auto &filter) { return; } /*Default case*/
				}, filterSetIter);
		}
	}
};

void* __fastcall GenericCreateFilters(FilterTypeSetArray &filters) {
	return new GenericEventFilters(filters);
}