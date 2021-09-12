#pragma once
#include <shared_mutex>
#include "events/EventFilteringInterface.h"
#include <unordered_set>


bool (*FunctionCallScript)(Script* funcScript, TESObjectREFR* callingObj, TESObjectREFR* container, NVSEArrayElement* result, UInt8 numArgs, ...);
NVSEArrayElement EventResultPtr;
void* __fastcall GenericCreateFilters(FilterTypeSetArray &filters);
using _FilterCreatorFunction = void* (__fastcall* )(FilterTypeSetArray& filters);	//todo: look into why ReSharper says this uses a reserved identifier...

class BaseEventClass
{
public:
	ULONG_PTR Flags = 0;
	Script* ScriptForEvent = nullptr;
	EventHandlerFilterBase* eventFilter = nullptr;
	LambdaVariableContext capturedLambdaVars;

	BaseEventClass() : capturedLambdaVars(nullptr) {}

	enum GlobalEventFlags
	{
		kEventFlag_Deleted = 1 << 0,
	};

	bool GetDeleted() const
	{
		return Flags & kEventFlag_Deleted;
	}
	void SetDeleted(bool doSet)
	{
		doSet ? Flags |= kEventFlag_Deleted : Flags &= ~kEventFlag_Deleted;
	}
};


class BaseEventInformation
{
public:
	// Values are stored here for ease of accessibility from the outside.
	_FilterCreatorFunction filter_creator_func; // supposed to be passing a class that inherits from EventHandlerFilterBase
	std::vector<BaseEventClass> event_queue_add;
	std::shared_mutex queue_rw_lock; //need a readers writer lock to protect from multiple users registering an event in the same frame (very rare, but can happen)

	std::string const event_name;
	UInt8 const num_max_args;	// used when invoking script UDFs.
	std::vector<BaseEventClass> event_callbacks;

	BaseEventInformation(std::string eventName, UInt8 const& numMaxArgs, _FilterCreatorFunction FilterCreatorFunction)
		: event_name{ std::move(eventName) }, num_max_args(numMaxArgs)
	{
		if (!FilterCreatorFunction)
			filter_creator_func = GenericCreateFilters;
		else
			filter_creator_func = FilterCreatorFunction;
	}
	
	virtual ~BaseEventInformation() = default;
	virtual bool RegisterEvent(Script* script, FilterTypeSetArray& filters) = 0;
	void virtual RemoveEvent(Script* script, FilterTypeSetArray& filters) = 0;
	void virtual AddQueuedEvents() = 0;
	void virtual DeleteEvents() = 0;
};


template<typename _Filter>
class EventInformation : BaseEventInformation
{
	using BaseEventInformation::BaseEventInformation; //steal the constructor
	
	~EventInformation() override
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

	// Note: events must wait a frame before being fully registered. Thus, they cannot be removed on the same frame they were created.
	bool RegisterEvent(Script* script, FilterTypeSetArray &filters) override
	{
		enum CheckFilterFunc_ReturnValues
		{
			kRetn_Continue = 0,
			kRetn_Return = 1,
		};
		auto CheckFilterFunc = [&, this](BaseEventClass &eventIter) -> UInt8
		{
			if (script == eventIter.ScriptForEvent)
			{
				if (!num_max_filters) return kRetn_Return;	// filter-less event was already registered
				if (!eventIter.eventFilter->GetNumGenFilters()) return kRetn_Continue;
				for (int i = 0; i < num_max_filters; i++)
				{
					if (!eventIter.eventFilter->IsGenFilterEqual(i, filters[i]))
						return kRetn_Continue;	// new event has sufficiently different filters, look for another event match.
				}
				return kRetn_Return; // event is already registered with the same filters.
			}
			return kRetn_Continue;
		};
		
		for (auto &callbackIter: event_callbacks)
		{
			auto const check = CheckFilterFunc(callbackIter);
			if (check == kRetn_Return) return false;
		}
		
		std::shared_lock rLock(queue_rw_lock);
		for (auto &eventQueueIter : event_queue_add)
		{
			auto const check = CheckFilterFunc(eventQueueIter);
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
	bool virtual RegisterEvent(Script* script)
	{
		FilterTypeSetArray nullArr{};
		return RegisterEvent(script, nullArr);
	}
	bool virtual RegisterEvent(Script* script, _Filter &filter)
	{
		auto filterSetArr = filter.ToArray();
		return RegisterEvent(script, filterSetArr);
	}
	
	void RemoveEvent(Script* script, FilterTypeSetArray &filters) override
	{
		auto it = event_callbacks.begin();
		while (it != event_callbacks.end())
		{
			if (script == it->ScriptForEvent)
			{
				if (auto eventFilters = it->eventFilter)
				{
					auto const maxFilters = eventFilters->GetNumGenFilters();
					for (int i = 0; i < maxFilters; i++)
					{
						if (!it->eventFilter->IsGenFilterEqual(i, filters[i]))
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
	void virtual RemoveEvent(Script* script)
	{
		FilterTypeSetArray nullArr{};
		RemoveEvent(script, nullArr);
	}
	void virtual RemoveEvent(Script* script, _Filter &filter)
	{
		auto filterSetArr = filter.ToArray();
		RemoveEvent(script, filterSetArr);
	}
	
	void AddQueuedEvents() override
	{
		event_callbacks.insert(event_callbacks.end(), std::make_move_iterator(event_queue_add.begin()), std::make_move_iterator(event_queue_add.end()));
		event_queue_add.clear();
	}
	
	void DeleteEvents() override
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

using EventInfo = BaseEventInformation*;
std::mutex g_EventsArrayMutex;
std::vector<EventInfo> g_EventsArray;

EventInfo FindHandlerInfoByString(std::string const &nameToFind)
{
	for (auto const &eventsIter : g_EventsArray)
	{
		if (eventsIter->event_name == nameToFind)
			return eventsIter;
	}
	return nullptr;
}

template<typename _Filter>
EventInformation<_Filter>* __cdecl JGCreateEvent(const char* eventName, UInt8 const maxArgs, _FilterCreatorFunction FilterCreatorFunction = nullptr)
{
	std::lock_guard lock(g_EventsArrayMutex);
	auto const eventInfo = new EventInformation<_Filter>(eventName, maxArgs, FilterCreatorFunction);
	g_EventsArray.push_back(eventInfo);
	return eventInfo;
}

void __cdecl JGFreeEvent(EventInfo &toRemove)
{
	if (!toRemove) return;
	std::lock_guard lock(g_EventsArrayMutex);
	if (auto it = std::find(std::begin(g_EventsArray), std::end(g_EventsArray), toRemove); 
		it != g_EventsArray.end())
	{
		delete* it;
		it = g_EventsArray.erase(it);
	}
	toRemove = nullptr;
}
