#pragma once
#include "events/EventFilteringInterface.h"
#include <unordered_set>
bool (*FunctionCallScript)(Script* funcScript, TESObjectREFR* callingObj, TESObjectREFR* container, NVSEArrayElement* result, UInt8 numArgs, ...);

NVSEArrayElement EventResultPtr;
class EventInformation;
//void* __fastcall GenericCreateFilter(void** maxFilters, UInt32 numFilters);

#if NULL
class JohnnyEventFiltersForm : EventHandlerInterface
{
	typedef  std::unordered_set<unsigned int> RefUnorderedSet;

	RefUnorderedSet* Filters = nullptr;	// In order to search filters more efficiently.

	RefUnorderedSet* GetFilter(UInt32 filter)
	{
		if (filter >= numFilters) return NULL;
		return &(Filters[filter]);
	}
public:
	JohnnyEventFiltersForm(void** filters, UInt32 nuFilters)
	{
		numFilters = nuFilters;
		Filters = new RefUnorderedSet[numFilters];
		GenFilters = new GenericFilters[numFilters];
		for (int i = 0; i < nuFilters; i++) GenFilters[i].ptr = filters[i];

	}
	virtual ~JohnnyEventFiltersForm()
	{
		delete[] Filters;
		delete[] GenFilters;
	}

	virtual bool IsInFilter(UInt32 filterNum, GenericFilters toSearch)
	{
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return false;
		return FilterSet->empty() || (FilterSet->find(toSearch.refID) != FilterSet->end());
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

		return parameter.form->typeID != kFormType_TESObjectSTAT;

	}

	virtual void SetUpFiltering()
	{
		for (int i = 0; i < numFilters; i++)
		{
			TESForm* currentFilter = GenFilters[i].form;
			if (!currentFilter) continue;
			if (!(IsAcceptedParameter(currentFilter))) continue;
			if (currentFilter->GetIsReference())
			{
				InsertToFilter(i, ((TESObjectREFR*)currentFilter)->baseForm->refID);
				continue;
			}
			if (IS_TYPE(currentFilter, BGSListForm))
			{
				//Console_Print("filter looping");
				ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
				do {
					TESForm* it = iterator->data;
					if (it->GetIsReference()) continue;
					if (IsAcceptedParameter(it))
						InsertToFilter(i, it->refID);
				} while (iterator = iterator->next);

			}
			else InsertToFilter(i, currentFilter->refID);
		}
	}

	__forceinline bool IsBaseInFilter(UInt32 filterNum, TESForm* form)
	{
		if (!form) return false;
		if (form->GetIsReference()) return IsInFilter(filterNum, ((TESObjectREFR*)form)->baseForm->refID);
		return IsInFilter(filterNum, form->refID);
	}

	void insertFormList(BGSListForm* List, UInt32 filter)
	{
		ListNode<TESForm>* iterator = ((BGSListForm*)List)->list.Head();
		do {
			InsertToFilter(filter, iterator->data->refID);
		} while (iterator = iterator->next);
	}
};
#endif

class EventInformation
{
private:
	std::vector<BaseEventClass> event_queue_add;
	std::shared_mutex queue_rw_lock; //need a readers writer lock to protect from multiple users registering an event in the same frame (very rare, but can happen)
public:
	const char* event_name;
	UInt8 num_max_args;
	UInt8 num_max_filters;
	std::vector<BaseEventClass> event_callbacks;
	EventInformation(const char* eventName, UInt8& numMaxArgs, UInt8& numMaxFilters)
	{
		this->event_name = eventName;
		this->num_max_args = numMaxArgs;
		this->num_max_filters = numMaxFilters;
	}
	virtual ~EventInformation()
	{
		FlushEventCallbacks();
	}
	void FlushEventCallbacks()
	{
		auto it = event_callbacks.begin();
		while (it != event_callbacks.end())
		{
			delete it->eventFilter;
			++it;
		}
		event_callbacks.clear();
	}

	void virtual RegisterEvent(Script* script, void** filters)
	{
		UInt32 maxFilters = this->num_max_filters;
		for (auto it = this->event_callbacks.begin(); it != this->event_callbacks.end(); ++it)
		{
			if (script == it->ScriptForEvent)
			{
				if (!maxFilters) return;
				if (!it->eventFilter->GetNumFilters()) continue;
				int i = 0; // filter iterator
				for (; i < maxFilters; i++)
				{
					if (!(it->eventFilter->IsFilterEqual(filters[i], i))) break;
				}
				if (i >= maxFilters) return;
			}

		}
		std::shared_lock rLock(queue_rw_lock);
		for (auto it = this->event_queue_add.begin(); it != this->event_queue_add.end(); ++it)
		{
			if (script == it->ScriptForEvent)
			{
				if (!maxFilters) return;
				if (!it->eventFilter->GetNumFilters()) continue;
				int i = 0; // filter iterator
				for (; i < maxFilters; i++)
				{
					if (!(it->eventFilter->IsFilterEqual(filters[i], i))) break;
				}
				if (i >= maxFilters) return;
			}

		}
		rLock.unlock();
		BaseEventClass NewEvent;
		NewEvent.ScriptForEvent = script;
		NewEvent.capturedLambdaVars = LambdaVariableContext(script);
		if (maxFilters)
		{
			*(void**)&(NewEvent.eventFilter) = this->CreateFilter(filters, maxFilters);
			NewEvent.eventFilter->SetUpFiltering();
		}
		std::unique_lock wLock(queue_rw_lock);
		this->event_queue_add.push_back(std::move(NewEvent));
	}
	
	void virtual RemoveEvent(Script* script, void** filters)
	{
		auto it = event_callbacks.begin();
		while (it != event_callbacks.end())
		{
			if (script == it->ScriptForEvent)
			{
				if (auto eventFilters = it->eventFilter)
				{
					UInt32 maxFilters = eventFilters->GetNumFilters();
					for (int i = 0; i < maxFilters; i++)
					{
						if (!(it->eventFilter->IsFilterEqual(filters[i], i))) 
							goto NotFound;
					}
				}
				it->SetDeleted(true);
			}
		NotFound:
			++it;

		}
	}
	void virtual AddQueuedEvents()
	{
		event_callbacks.insert(event_callbacks.end(), std::make_move_iterator(event_queue_add.begin()), std::make_move_iterator(event_queue_add.end()));
		event_queue_add.clear();
	}
	void virtual DeleteEvents()
	{
		auto it = event_callbacks.begin();
		while (it != event_callbacks.end())
		{
			if (it->GetDeleted())
			{
				delete it->eventFilter;	// deleting nullptr is safe.
				it = event_callbacks.erase(it);
				continue;
			}
			++it;
		}
	}
	//int a = sizeof(std::unordered_set<char>);
};
typedef EventInformation* EventInfo;
std::mutex EventsArrayMutex;
std::vector<EventInfo> EventsArray;


/*
void* __fastcall GenericCreateFilter(void** Filters, UInt32 numFilters) {
	return new JohnnyEventFiltersForm(Filters, numFilters);
}
*/


EventInfo FindHandlerInfoByChar(const char* nameToFind)
{
	auto it = EventsArray.begin();
	while (it != EventsArray.end())
	{
		if (!(_stricmp((*it)->event_name, nameToFind)))
			return *it;
		++it;
	}
	return nullptr;
}

EventInfo __cdecl JGCreateEvent(const char* EventName, UInt8 maxArgs, UInt8 maxFilters)
{
	std::lock_guard lock(EventsArrayMutex);
	auto const eventInfo = new EventInformation(EventName, maxArgs, maxFilters);
	EventsArray.push_back(eventInfo);
	return eventInfo;

}


void __cdecl JGFreeEvent(EventInfo& toRemove)
{
	std::lock_guard lock(EventsArrayMutex);
	if (!toRemove) return;
	if (auto it = std::find(std::begin(EventsArray), std::end(EventsArray), toRemove); 
		it != EventsArray.end())
	{
		delete* it;
		it = EventsArray.erase(it);
	}
	toRemove = nullptr;
}
