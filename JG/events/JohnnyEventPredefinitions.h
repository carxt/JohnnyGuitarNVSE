#pragma once
#include "events/EventFilteringInterface.h"
#include <unordered_set>

bool (*FunctionCallScript)(Script* funcScript, TESObjectREFR* callingObj, TESObjectREFR* container, NVSEArrayElement* result, UInt8 numArgs, ...);
NVSEArrayElement EventResultPtr;
class EventInformation;
void* __fastcall GenericCreateFilters(FilterTypeSetArray &filters);
using _FilterCreatorFunction = void* (__fastcall* )(FilterTypeSetArray& filters);

#if NULL
class JohnnyEventFiltersForm : EventHandlerFilterBase
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
	_FilterCreatorFunction filter_creator_func; // supposed to be passing a class that inherits from EventHandlerFilterBase
	std::vector<BaseEventClass> event_queue_add;
	std::shared_mutex queue_rw_lock; //need a readers writer lock to protect from multiple users registering an event in the same frame (very rare, but can happen)
public:
	std::string const event_name;
	UInt8 const num_max_args;	// used when invoking script UDFs.
	UInt8 const num_max_filters;
	std::vector<BaseEventClass> event_callbacks;
	EventInformation(std::string eventName, UInt8 const& numMaxArgs, UInt8 const& numMaxFilters, _FilterCreatorFunction FilterCreatorFunction)
		: event_name{ std::move(eventName) }, num_max_args(numMaxArgs), num_max_filters(numMaxFilters)
	{
		if (!FilterCreatorFunction)
			this->filter_creator_func = GenericCreateFilters;
		else
			this->filter_creator_func = FilterCreatorFunction;
	}
	virtual ~EventInformation()
	{
		FlushEventCallbacks();
	}
	void FlushEventCallbacks()
	{
		for (auto &callbackIter : event_callbacks)
		{
			delete callbackIter.eventFilter;
		}
		event_callbacks.clear();
	}

	bool virtual RegisterEvent(Script* script, FilterTypeSetArray &filters)
	{
		if (filters.size() > num_max_filters)
		{
			throw std::logic_error("Filter array must not have greater size than EventInfo's num_max_args.");
		}

		enum CheckFilterFunc_ReturnValues
		{
			kRetn_Break = 0,
			kRetn_Continue = 1,
			kRetn_Return = 2,
		};
		auto CheckFilterFunc = [&, this](BaseEventClass &eventIter) -> UInt8
		{
			if (script == eventIter.ScriptForEvent)
			{
				if (!eventIter.eventFilter->GetNumFilters()) return kRetn_Continue;
				for (int i = 0; i < num_max_filters; i++)
				{
					if (!eventIter.eventFilter->IsFilterEqual(i, filters[i]))
						return kRetn_Break;
				}
				return kRetn_Return; // event is already registered.
			}
			return kRetn_Continue;
		};
		
		for (auto &callbackIter: event_callbacks)
		{
			auto const check = CheckFilterFunc(callbackIter);
			if (check == kRetn_Break) break;
			if (check == kRetn_Return) return false;
		}
		
		std::shared_lock rLock(queue_rw_lock);
		for (auto &eventQueueIter : event_queue_add)
		{
			auto const check = CheckFilterFunc(eventQueueIter);
			if (check == kRetn_Break) break;
			if (check == kRetn_Return) return false;
		}
		rLock.unlock();
		
		BaseEventClass NewEvent;
		NewEvent.ScriptForEvent = script;
		NewEvent.capturedLambdaVars = LambdaVariableContext(script);
		if (num_max_filters)
		{
			*(void**)&(NewEvent.eventFilter) = this->filter_creator_func(filters);
			NewEvent.eventFilter->SetUpFiltering();
		}
		std::unique_lock wLock(queue_rw_lock);
		this->event_queue_add.push_back(std::move(NewEvent));
		return true;
	}
	bool virtual RegisterEvent(Script* script, FilterTypeSets& filter)
	{
		FilterTypeSetArray arr { filter };
		return RegisterEvent(script, arr);
	}
	
	void virtual RemoveEvent(Script* script, FilterTypeSetArray &filters)
	{
		auto it = event_callbacks.begin();
		while (it != event_callbacks.end())
		{
			if (script == it->ScriptForEvent)
			{
				if (auto eventFilters = it->eventFilter)
				{
					auto const maxFilters = eventFilters->GetNumFilters();
					for (int i = 0; i < maxFilters; i++)
					{
						if (!it->eventFilter->IsFilterEqual(i, filters[i]))
							goto NotFound;
					}
				}
				it->SetDeleted(true);
			}
		NotFound:
			++it;
		}
	}
	void virtual RemoveEvent(Script* script, FilterTypeSets& filter)
	{
		FilterTypeSetArray arr { filter };
		RemoveEvent(script, arr);
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
};
typedef EventInformation* EventInfo;
std::mutex EventsArrayMutex;
std::vector<EventInfo> EventsArray;

EventInfo FindHandlerInfoByChar(std::string &nameToFind)
{
	for (auto const &eventsIter : EventsArray)
	{
		if (eventsIter->event_name == nameToFind)
			return eventsIter;
	}
	return nullptr;
}

EventInfo __cdecl JGCreateEvent(std::string const &eventName, UInt8 const maxArgs, UInt8 const maxFilters, _FilterCreatorFunction FilterCreatorFunction = nullptr)
{
	std::lock_guard lock(EventsArrayMutex);
	auto const eventInfo = new EventInformation(eventName, maxArgs, maxFilters, FilterCreatorFunction);
	EventsArray.push_back(eventInfo);
	return eventInfo;
}

void __cdecl JGFreeEvent(EventInfo &toRemove)
{
	if (!toRemove) return;
	std::lock_guard lock(EventsArrayMutex);
	if (auto it = std::find(std::begin(EventsArray), std::end(EventsArray), toRemove); 
		it != EventsArray.end())
	{
		delete* it;
		it = EventsArray.erase(it);
	}
	toRemove = nullptr;
}
