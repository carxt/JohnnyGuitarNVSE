#pragma once
#include "GameRTTI.h"
#include "events/EventFilteringInterface.h"

#if NULL
class JohnnyEventFiltersOneFormOneInt : EventHandlerFilterBase
{


	typedef  std::unordered_set<unsigned int> RefUnorderedSet;
private:
	RefUnorderedSet* Filters = nullptr;

	RefUnorderedSet* GetFilter(UInt32 filter)
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
		if (!(FilterSet = GetFilter(filterNum))) return false;
		return  FilterSet->empty() || (FilterSet->find(toSearch.refID) != FilterSet->end());
	}


	virtual void InsertToFilter(UInt32 filterNum, GenericFilters toInsert)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->insert(toInsert.refID);
	}
	virtual void DeleteFromFilter(UInt32 filterNum, GenericFilters toDelete)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->erase(toDelete.refID);

	}
	virtual bool IsFilterEmpty(UInt32 filterNum)
	{
		RefUnorderedSet* FilterSet = GetFilter(filterNum);
		if (!FilterSet) return true;
		return FilterSet->empty();
	}
	virtual bool IsFilterEqual(GenericFilters Filter, UInt32 nuFilter)
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






//== Demo's Generic Filter

// Taken from https://www.cppstories.com/2018/09/visit-variants/. Also shows up in https://gummif.github.io/blog/overloading_lambdas.html.
template<class... Ts> struct overload : Ts...
{
	using Ts::operator()...;
};
template<class... Ts> overload(Ts...)->overload<Ts...>;

FilterTypeSets testFilter1 = { IntSet {5, 0x7} };
FilterTypeSets testFilter2 = { StringSet {"testStr", "testStr2", "tt"} };
FilterTypeSetArray testFilters = { testFilter1, testFilter2 };

class GenericEventFilters : EventHandlerFilterBase
{
public:
	GenericEventFilters(FilterTypeSetArray &filters)
	{
		filtersArr = filters;
	}
	GenericEventFilters(FilterTypeSets& filter)
	{
		filtersArr = FilterTypeSetArray { filter };
	}

	bool IsInFilter(UInt32 filterNum, FilterTypes toSearch) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return false;
		bool const isFound = std::visit(overload{
		[](FormSet &arg1, TESForm* &arg2) { return arg1.find(arg2) != arg1.end(); },
		[](IntSet &arg1, int &arg2) { return arg1.find(arg2) != arg1.end(); },
		[](FloatSet &arg1, float &arg2) { return arg1.find(arg2) != arg1.end(); },
		[](StringSet &arg1, std::string &arg2) { return arg1.find(arg2) != arg1.end(); },
		[](auto &arg1, auto &arg2) { return false; /*Types do not match*/ },
			},	*filterSet, toSearch);
		return isFound;
	}

	bool IsBaseInFilter(UInt32 filterNum, TESForm* toSearch)
	{
		if (!toSearch) return false;
		if (toSearch->GetIsReference())
			toSearch = ((TESObjectREFR*)toSearch)->baseForm;
		FilterTypes filter = toSearch;
		return IsInFilter(filterNum, toSearch);
	}
	
	bool InsertToFilter(UInt32 filterNum, FilterTypes toInsert) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return false;
		bool const isInserted = std::visit(overload{
		[](FormSet& arg1, TESForm*& arg2) { return arg1.insert(arg2).second; },
		[](IntSet& arg1, int& arg2) { return arg1.insert(arg2).second; },
		[](FloatSet& arg1, float& arg2) { return arg1.insert(arg2).second; },
		[](StringSet& arg1, std::string& arg2) { return arg1.insert(arg2).second; },
		[](auto& arg1, auto& arg2) { return false; /*Types do not match*/ },
			}, *filterSet, toInsert);
		return isInserted;
	}
	
	bool DeleteFromFilter(UInt32 filterNum, FilterTypes toDelete) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return false;
		bool const isDeleted = std::visit(overload{
		[](FormSet& arg1, TESForm* &arg2) { return arg1.erase(arg2); },
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
	
	bool IsFilterEmpty(UInt32 filterNum) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return true;	// technically empty if there is no filter
		bool const isEmpty = std::visit([](auto &filter) { return filter.empty(); }, *filterSet);
		return isEmpty;
	}
	
	bool IsFilterEqual(UInt32 filterNum, FilterTypeSets cmpFilterSet) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return false;
		return cmpFilterSet == *filterSet;
	}

	//	Unused in SetUpFiltering, so it's useless.
	bool IsAcceptedParameter(FilterTypes param) override
	{
	//	bool const isAccepted = std::visit(overload{
	//		[&](TESForm* &filter) { return filter->refID != g_xMarkerID; },
	//		[&](auto& filter) { return true; } /*Default case*/
	//		}, param);
	//	return isAccepted;
		return true;
	}
	//
	
	void SetUpFiltering() override
	{
		// Filters out all -1 values from IntSets.
		// Transforms all BGSListForm*-type TESForm* into the TESForm* that were contained.
		// Filters out xMarker refs.
		for (auto& filterSet : filtersArr)
		{
			std::visit(overload{
			[](FormSet &filter)
			{
				FormSet newSet;
				// Append forms that were inside form-lists to newSet.
				// Note: does not support deep form-lists.
				for (auto const &formIter : filter)
				{
					if (auto const listForm = DYNAMIC_CAST(formIter, TESForm, BGSListForm))
					{
						// Insert only the form-list elements; omit the form-list itself.
						ListNode<TESForm>* listFormIter = listForm->list.Head();
						do { newSet.insert(listFormIter->Data());}
						while (listFormIter = listFormIter->next);
					}
					else
					{
						newSet.insert(formIter);
					}
				}
				newSet.erase(LookupFormByID(g_xMarkerID));	// todo: refactor to use IsAcceptedParameter instead?
				filter = newSet;	// todo: check if filterSet needs to be captured and set instead.
			},
			[](IntSet &filter)
			{
				filter.erase(-1);	// todo: refactor to use IsAcceptedParameter instead?
			},
			[](auto &filter) { return; } /*Default case*/
				}, filterSet);
		}
	}
};

void* __fastcall GenericCreateFilters(FilterTypeSetArray &filters) {
	return new GenericEventFilters(filters);
}


struct EventFilter_OneForm {
	TESForm* form = nullptr;

	FilterTypeSetArray ToFilter() const
	{
		FormSet formSet{ form };
		return FilterTypeSetArray{ formSet };
	}
};

struct EventFilter_OneForm_OneInt {
	TESForm* form = nullptr;
	int intID = -1;

	FilterTypeSetArray ToFilter() const
	{
		FormSet formSet{ form };
		IntSet idSet{ intID };
		return FilterTypeSetArray{ formSet, idSet };
	}
};