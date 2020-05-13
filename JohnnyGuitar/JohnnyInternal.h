#pragma once
#include <unordered_set>
class JohnnyEventFilters
{
	typedef  std::unordered_set<unsigned int> RefUnorderedSet;
private:
	UInt32 numFilters = 0;
	RefUnorderedSet* Filters = 0;

	RefUnorderedSet* GetFilter(UInt32 filter)
	{
		if (filter >= numFilters) return NULL;
		return &(Filters[filter]);
	}
public:
	JohnnyEventFilters(UInt32 nuFilters)
	{
		numFilters = nuFilters;
		Filters = new RefUnorderedSet[numFilters];
	}
	~JohnnyEventFilters()
	{
		delete[] Filters;
	}
	UInt32 GetNumFilters() { return numFilters; }

	inline bool IsInFilter(UInt32 filterNum, unsigned int toSearch)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return false;
		//RefUnorderedSet::const_iterator got = FilterSet->find(toSearch);
		return  (FilterSet->find(toSearch) != FilterSet->end());
	}
	void InsertToFilter(UInt32 filterNum, unsigned int toInsert)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->insert(toInsert);
	}
	void DeleteFromFilter(UInt32 filterNum, unsigned int toDelete)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->erase(toDelete);

	}
	bool IsFilterEmpty(UInt32 filterNum)
	{
		RefUnorderedSet* FilterSet = GetFilter(filterNum);
		if (!FilterSet) return true;
		return FilterSet->empty();
	}

};

class BaseEventClass
{
public:
	UInt32 GetNumArgs();
	UInt32 GetNumFilters();
	Script* ScriptForEvent;
	JohnnyEventFilters* eventFilter;
	void insertFormList(BGSListForm* List, UInt32 filter)
	{
		ListNode<TESForm>* iterator = ((BGSListForm*)List)->list.Head();
		do {
			eventFilter->InsertToFilter(filter, iterator->data->refID);

		} while (iterator = iterator->next);
	}
};

template<class T> using EventContainer = std::vector<T*>;
typedef EventContainer<BaseEventClass> BaseEventContainer;

void RemoveEventFromGame(Script* script, BaseEventContainer eContainer)
{
	
	auto it = eContainer.begin();
	while (it != eContainer.end())
	{
		if ((*it)->ScriptForEvent == script)
		{
			delete (*it)->eventFilter;
			delete (*it);
			it = eContainer.erase(it);
			
		}
		else it++;
	}
}




