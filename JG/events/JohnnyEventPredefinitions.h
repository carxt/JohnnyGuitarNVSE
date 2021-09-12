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

	std::string const event_name;	// to identify the event, for lookup and etc.
	UInt8 const num_max_args;	// used when invoking script UDFs.
	std::vector<BaseEventClass> event_callbacks;

	using flagType = uint16_t;
	enum EventFlags : flagType
	{
		eFlag_FlushOnLoad = 1 << 0,
	};
	flagType const event_flags;
	[[nodiscard]] EventFlags GetFlags() const { return (EventFlags)event_flags; }

	BaseEventInformation(std::string eventName, UInt8 const& numMaxArgs, flagType flags, _FilterCreatorFunction FilterCreatorFunction)
		: event_name{ std::move(eventName) }, num_max_args(numMaxArgs), event_flags(flags)
	{
		if (!FilterCreatorFunction)
			filter_creator_func = GenericCreateFilters;
		else
			filter_creator_func = FilterCreatorFunction;
	}
	
	virtual ~BaseEventInformation() = default;
	void virtual FlushEventCallbacks() = 0;
	bool virtual RegisterEvent(Script* script, FilterTypeSetArray& filters) = 0;
	void virtual RemoveEvent(Script* script, FilterTypeSetArray& filters) = 0;
	void virtual AddQueuedEvents() = 0;
	void virtual DeleteEvents() = 0;
};


template<typename _Filter>
class EventInformation : public BaseEventInformation
{
	// Note: events must wait a frame before being fully registered. Thus, they cannot be removed on the same frame they were created.
	bool RegisterEvent(Script* script, FilterTypeSetArray& filters) override
	{
		auto const numMaxFilters = filters.size();

		enum CheckFilterFunc_ReturnValues
		{
			kRetn_Continue = 0,
			kRetn_Return = 1,
		};
		auto CheckFilterFunc = [&, this](BaseEventClass& eventIter) -> UInt8
		{
			if (script == eventIter.ScriptForEvent)
			{
				if (!numMaxFilters) return kRetn_Return;	// filter-less event was already registered
				if (!eventIter.eventFilter->GetNumGenFilters()) return kRetn_Continue;
				for (int i = 0; i < numMaxFilters; i++)
				{
					if (!eventIter.eventFilter->IsGenFilterEqual(i, filters[i]))
						return kRetn_Continue;	// new event has sufficiently different filters, look for another event match.
				}
				return kRetn_Return; // event is already registered with the same filters.
			}
			return kRetn_Continue;
		};

		for (auto& callbackIter : event_callbacks)
		{
			auto const check = CheckFilterFunc(callbackIter);
			if (check == kRetn_Return) return false;
		}

		std::shared_lock rLock(queue_rw_lock);
		for (auto& eventQueueIter : event_queue_add)
		{
			auto const check = CheckFilterFunc(eventQueueIter);
			if (check == kRetn_Return) return false;
		}
		rLock.unlock();

		BaseEventClass NewEvent;
		NewEvent.ScriptForEvent = script;
		NewEvent.capturedLambdaVars = LambdaVariableContext(script);
		if (numMaxFilters)
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
		FilterTypeSetArray arr{ filter };
		return RegisterEvent(script, arr);
	}

	void RemoveEvent(Script* script, FilterTypeSetArray& filters) override
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
						if (!it->eventFilter->IsGenFilterEqualAlt(i, filters[i]))
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
		FilterTypeSetArray arr{ filter };
		RemoveEvent(script, arr);
	}
	
public:
	using BaseEventInformation::BaseEventInformation; //steal the constructor
	
	~EventInformation() override
	{
		FlushEventCallbacks();
	}

	void FlushEventCallbacks() override
	{
		for (auto &callbackIter : event_callbacks)
		{
			delete callbackIter.eventFilter;
		}
		event_callbacks.clear();
	}
	
	bool virtual RegisterEvent(Script* script, _Filter &filter)
	{
		auto filterSetArr = filter.ToFilter();
		return RegisterEvent(script, filterSetArr);
	}
	
	void virtual RemoveEvent(Script* script, _Filter &filter)
	{
		auto filterSetArr = filter.ToFilter();
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
EventInformation<_Filter>* __cdecl JGCreateEvent(const char* eventName, UInt8 const maxArgs, uint16_t const flags = 0, _FilterCreatorFunction FilterCreatorFunction = nullptr)
{
	std::lock_guard lock(g_EventsArrayMutex);
	auto const eventInfo = new EventInformation<_Filter>(eventName, maxArgs, flags, FilterCreatorFunction);
	g_EventsArray.push_back(eventInfo);
	return eventInfo;
}

// Unused
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
