#pragma once
class JohnnyEventFiltersOneFormOneInt : EventHandlerInterface
{


	typedef  std::unordered_set<unsigned int> RefUnorderedSet;
private:
	RefUnorderedSet* Filters = 0;

	RefUnorderedSet* GetFilter(UInt32 filter)
	{
		if (filter >= numFilters) return NULL;
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
		//Console_Print("in filter");
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return false;
		//Console_Print("found filter %d", filterNum);
		//RefUnorderedSet::const_iterator got = FilterSet->find(toSearch);
	//	if (FilterSet->empty()) Console_Print("Filter %d empty, returning 1", filterNum);
		//else if (FilterSet->find(toSearch.refID) != FilterSet->end()) Console_Print("found in filter %d, returning 1", filterNum);
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
			//Console_Print("filter looping");
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
	UInt32 intID;
};