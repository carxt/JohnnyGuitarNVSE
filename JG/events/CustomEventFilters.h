#pragma once

#if NULL
class JohnnyEventFiltersOneFormOneInt : EventHandlerInterface
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

struct EventFilterStructOneFormOneInt {
	TESForm* form;
	int intID;
};
#endif



//== Demo's Generic Filter

// Taken from https://www.cppstories.com/2018/09/visit-variants/. Also shows up in https://gummif.github.io/blog/overloading_lambdas.html.
template<class... Ts> struct overload : Ts...
{
	using Ts::operator()...;
};
template<class... Ts> overload(Ts...)->overload<Ts...>;

FilterTypeSets testFilter1 = { RefIDSet {5, 0x7} };
FilterTypeSets testFilter2 = { StringSet {"testStr", "testStr2", "tt"} };
FilterTypeSetArray testFilters = { testFilter1, testFilter2 };

class GenericEventFilters : EventHandlerInterface
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
		bool isFound;
		std::visit(overload{
		[&isFound](RefIDSet& arg1, RefID& arg2) { isFound = arg1.find(arg2) != arg1.end(); },
		[&isFound](FormSet &arg1, TESForm* &arg2) { isFound = arg1.find(arg2) != arg1.end(); },
		[&isFound](IntSet &arg1, int &arg2) { isFound = arg1.find(arg2) != arg1.end(); },
		[&isFound](FloatSet &arg1, float &arg2) { isFound = arg1.find(arg2) != arg1.end(); },
		[&isFound](StringSet &arg1, std::string &arg2) { isFound = arg1.find(arg2) != arg1.end(); },
		[&isFound](auto &arg1, auto &arg2) {isFound = false; /*Types do not match*/ },
			},	*filterSet, toSearch);
		return isFound;
	}
	
	bool InsertToFilter(UInt32 filterNum, FilterTypes toInsert) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return false;
		bool isInserted;
		std::visit(overload{
		[&isInserted](RefIDSet& arg1, RefID& arg2) { isInserted = arg1.insert(arg2).second; },
		[&isInserted](FormSet& arg1, TESForm*& arg2) { isInserted = arg1.insert(arg2).second; },
		[&isInserted](IntSet& arg1, int& arg2) { isInserted = arg1.insert(arg2).second; },
		[&isInserted](FloatSet& arg1, float& arg2) { isInserted = arg1.insert(arg2).second; },
		[&isInserted](StringSet& arg1, std::string& arg2) { isInserted = arg1.insert(arg2).second; },
		[&isInserted](auto& arg1, auto& arg2) {isInserted = false; /*Types do not match*/ },
			}, *filterSet, toInsert);
		return isInserted;
	}
	
	bool DeleteFromFilter(UInt32 filterNum, FilterTypes toDelete) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return false;
		bool isDeleted;
		std::visit(overload{
		[&isDeleted](RefIDSet& arg1, RefID& arg2) { isDeleted = arg1.erase(arg2); },
		[&isDeleted](FormSet& arg1, TESForm*& arg2) { isDeleted = arg1.erase(arg2); },
		[&isDeleted](IntSet& arg1, int& arg2) { isDeleted = arg1.erase(arg2); },
		[&isDeleted](FloatSet& arg1, float& arg2) { isDeleted = arg1.erase(arg2); },
		[&isDeleted](StringSet& arg1, std::string& arg2) { isDeleted = arg1.erase(arg2); },
		[&isDeleted](auto& arg1, auto& arg2) {isDeleted = false; /*Types do not match*/ },
			}, *filterSet, toDelete);
		return isDeleted;
	}
	
	bool IsFilterEmpty(UInt32 filterNum) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum))) return true;	// technically empty if there is no filter
		bool isEmpty;
		std::visit([&isEmpty](auto &filter) { isEmpty = filter.empty(); }, *filterSet);
		return isEmpty;
	}
	
	bool IsFilterEqual(UInt32 filterNum, FilterTypes cmpFilter) override
	{
		FilterTypeSets* filterSet;
		if (!(filterSet = GetFilter(filterNum)))
		{
			if (cmpFilter.valueless_by_exception()) return true;	// rare case
			return false;
		}
		UInt32 size;
		std::visit([&size](auto& filter) { size = filter.size(); }, *filterSet);
		if (size > 1) return false;	// comparing a single value to an array of values.
		if (size == 1)
		{
			bool isEqual;
			std::visit([&size](auto& filter) { size = filter.size(); }, *filterSet);
			//return (Filter.ptr == GenFilters[nuFilter].ptr);
		}
		//if (size == 0)
		return cmpFilter.valueless_by_exception() ? true : false;
	}
	/*
	bool IsAcceptedParameter(FilterTypes parameter) override
	{
		return parameter.form->refID != 0x3B; // xMarker
	}

	void SetUpFiltering() override
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
		else if (IsAcceptedParameter(currentFilter)) 
			InsertToFilter(0, currentFilter->refID);
	}
	*/

};
void* __fastcall CreateGenericFilters(void** Filters, UInt32 numFilters) {
	//todo: return new GenericEventFilters(Filters, numFilters);
}
	