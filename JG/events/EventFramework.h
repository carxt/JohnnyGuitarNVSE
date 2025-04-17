#pragma once
#include <unordered_set>
#include <vector>
#include <shared_mutex>
#include <mutex>
#include <algorithm>
bool (*CallUDF)(Script* funcScript, TESObjectREFR* callingObj, UInt8 numArgs, ...);

NVSEArrayElement EventResultPtr;
class EventInformation;
void* __fastcall GenericCreateFilter(void** maxFilters, UInt32 numFilters);

union FilterType
{
	void* ptr;
	TESForm* form;
	UInt32 refID;
	int intVal;
	float fltVal;
	char* str;

	FilterType() : ptr(nullptr) {}

	FilterType(void* ptr) : ptr(ptr) {}

	FilterType(TESForm* form) : form(form) {}

	FilterType(UInt32 refID) : refID(refID) {}

	FilterType(int intVal) : intVal(intVal) {}

	FilterType(float fltVal) : fltVal(fltVal) {}

	FilterType(char* str) : str(str) {}
};

class IFilter
{
public:
	//Framework passes the objects to add to filter here
	FilterType* genFilters = 0;
	//Used to know how many filterSet in total (aka the size of the FilterType array) the filter uses
	UInt32 numFilters = 0;
	//Default destructor
	virtual ~IFilter() = default;
	//When the framework passes filterSet, it passes them to the genFilters array pointer, specifying the number of filterSet in the numFilters member
	//This function is called by the framework so you can add the objects inside a struct more suitable for search, such as an unordered set
	virtual void SetUpFiltering() = 0;

	//Checks if an object is in the filter, recommended to use a fast lookup data structure
	virtual bool IsInFilter(UInt32 filterNum, FilterType toSearch) = 0;
	//Inserts the desired element to the Nth filter.
	virtual void InsertToFilter(UInt32 filterNum, FilterType toInsert) = 0;
	//Deletes an object from the Nth filter
	virtual void DeleteFromFilter(UInt32 filterNum, FilterType toDelete) = 0;
	//Returns if the filter is empty
	virtual bool IsFilterEmpty(UInt32 filterNum) = 0;
	//Used by the framework to check if the Nth filter equals the passed value. Useful to avoid adding the same event repeatedly
	virtual bool IsFilterEqual(FilterType Filter, UInt32 filterNum) = 0;
	//Function used by the filter to check if the object passed is an accepted parameter
	virtual bool IsAcceptedParameter(FilterType toCheck) = 0;
	virtual UInt32 GetNumFilters() { return numFilters; }
};


class FilterBase : protected IFilter
{
protected:
	using FilterSet = std::unordered_set<unsigned int>;

	FilterSet* filterSet = nullptr;

	FilterSet* GetFilter(UInt32 index)
	{
		if (index >= numFilters) return nullptr;
		return &(filterSet[index]);
	}

public:
	FilterBase(void** filters, UInt32 nuFilters)
	{
		numFilters = nuFilters;
		filterSet = new FilterSet[numFilters];
		genFilters = new FilterType[numFilters];
		for (int i = 0; i < nuFilters; i++) genFilters[i].ptr = filters[i];
	}

	virtual ~FilterBase()
	{
		delete[] filterSet;
		delete[] genFilters;
	}

	bool IsInFilter(UInt32 filterNum, FilterType toSearch) override
	{
		FilterSet* FilterSet = GetFilter(filterNum);
		return FilterSet && (FilterSet->empty() || FilterSet->find(toSearch.refID) != FilterSet->end());
	}

	bool IsFilterEmpty(UInt32 num) override
	{
		FilterSet* filters = GetFilter(num);
		return !filters || filters->empty();
	}

	void InsertToFilter(UInt32 num, FilterType toInsert) override
	{
		FilterSet* filters = GetFilter(num);
		if (filters) filters->insert(toInsert.refID);
	};

	void DeleteFromFilter(UInt32 num, FilterType toDelete) override
	{
		FilterSet* filters = GetFilter(num);
		if (filters) filters->erase(toDelete.refID);
	};

	bool IsFilterEqual(FilterType filter, UInt32 num) override
	{
		return (filter.ptr == genFilters[num].ptr);
	}

};


class FilterNull : public FilterBase
{
public:
	FilterNull(void** filters, UInt32 nuFilters) : FilterBase(filters, nuFilters){}

	virtual bool IsInFilter(UInt32 filterNum, FilterType toSearch) override { return true; }
	virtual void InsertToFilter(UInt32 filterNum, FilterType toInsert) override {}
	virtual void DeleteFromFilter(UInt32 filterNum, FilterType toDelete) override {}
	virtual bool IsFilterEqual(FilterType Filter, UInt32 nuFilter) override { return true; }
	virtual bool IsAcceptedParameter(FilterType parameter) override { return true; }
	virtual void SetUpFiltering() override {}
};

class FilterForm : public FilterBase
{
public:
	FilterForm(void** filters, UInt32 nuFilters) : FilterBase(filters, nuFilters){}

	bool IsAcceptedParameter(FilterType parameter) override
	{
		return parameter.form->typeID != kFormType_TESObjectSTAT;
	}

	void SetUpFiltering() override
	{
		for (int i = 0; i < numFilters; i++)
		{
			TESForm* currentFilter = genFilters[i].form;
			if (!currentFilter) continue;
			if (!(IsAcceptedParameter(currentFilter))) continue;
			if (currentFilter->GetIsReference())
			{
				InsertToFilter(i, ((TESObjectREFR*)currentFilter)->baseForm->refID);
				continue;
			}
			if (IS_TYPE(currentFilter, BGSListForm))
			{
				ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
				do
				{
					TESForm* it = iterator->data;
					if (it && !it->GetIsReference() && IsAcceptedParameter(it))
						InsertToFilter(i, it->refID);
				}
				while (iterator = iterator->next);
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

	void insertFormList(BGSListForm* formlist, UInt32 filter)
	{
		ListNode<TESForm>* iterator = formlist->list.Head();
		do
		{
			InsertToFilter(filter, iterator->data->refID);
		}
		while (iterator = iterator->next);
	}
};

class FilterInt : public FilterBase
{
public:
	FilterInt(void** filters, UInt32 nuFilters) : FilterBase(filters, nuFilters){}

	bool IsFilterEqual(FilterType Filter, UInt32 nuFilter) override
	{
		return Filter.intVal == genFilters[nuFilter].intVal;
	}

	bool IsAcceptedParameter(FilterType parameter) override
	{
		return true;
	}

	void SetUpFiltering() override
	{
		for (int i = 0; i < numFilters; i++)
		{
			if (genFilters[i].intVal != -1) InsertToFilter(i, genFilters[i].intVal);
		}
	}

	struct Data
	{
		int intID;
	};

	static void* __fastcall Create(void** filters, UInt32 nuFilters)
	{
		return new FilterInt(filters, nuFilters);
	}
};


class FilterFormInt : public FilterBase
{

public:
	FilterFormInt(void** filters, UInt32 nuFilters) : FilterBase(filters, nuFilters) {}

	bool IsAcceptedParameter(FilterType parameter) override
	{
		return parameter.form->refID != 0x3B; // xMarker
	}

	void SetUpFiltering() override
	{
		if (genFilters[1].intVal != -1) InsertToFilter(1, genFilters[1].intVal);
		TESForm* currentFilter = genFilters[0].form;
		if (!currentFilter) return;
		if (IS_TYPE(currentFilter, BGSListForm))
		{
			ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
			do
			{
				TESForm* it = iterator->data;
				if (it && IsAcceptedParameter(it))
					InsertToFilter(0, it->refID);
			}
			while (iterator = iterator->next);
		}
		else if (IsAcceptedParameter(currentFilter)) InsertToFilter(0, currentFilter->refID);
	}

	struct Data
	{
		TESForm* form;
		int intID;
	};

	static void* __fastcall Create(void** filters, UInt32 nuFilters)
	{
		return new FilterFormInt(filters, nuFilters);
	}
};

class EventBase
{
public:
	UInt32 Flags = 0;
	Script* script = nullptr;
	IFilter* eventFilter = nullptr;
	LambdaVariableContext capturedLambdaVars;

	EventBase() : capturedLambdaVars(nullptr){}

	enum GlobalEventFlags
	{
		kEventFlag_Deleted = 1 << 0,
	};

	bool GetDeleted()
	{
		return Flags & kEventFlag_Deleted;
	}

	void SetDeleted(bool doSet)
	{
		doSet ? Flags |= kEventFlag_Deleted : Flags &= ~kEventFlag_Deleted;
	}
};

class EventInformation
{
private:
	void* (__fastcall*CreateFilter)(void**, UInt32); // supposed to be passing itself
	std::vector<EventBase> eventAddQueue;
	std::shared_mutex queueLock;
	//need a readers writer lock to protect from multiple users registering an event in the same frame (very rare, but can happen)
public:
	const char* name;
	UInt8 numMaxArgs;
	UInt8 numMaxFilters;
	std::vector<EventBase> callbacks;

	EventInformation(const char* EventName, UInt8& numMaxArgs, UInt8& numMaxFilters,
	                 void* (__fastcall*CreatorFunction)(void**, UInt32))
	{
		this->name = EventName;
		this->numMaxArgs = numMaxArgs;
		this->numMaxFilters = numMaxFilters;
		this->CreateFilter = GenericCreateFilter;
		if (CreatorFunction) this->CreateFilter = CreatorFunction;
	}

	virtual ~EventInformation()
	{
		FlushEventCallbacks();
	}

	void FlushEventCallbacks()
	{
		for (auto& event : callbacks)
		{
			delete event.eventFilter;
		}
		callbacks.clear();
	}

	void virtual RegisterEvent(Script* script, void** filters)
	{
		UInt32 maxFilters = this->numMaxFilters;
		for (auto& event : this->callbacks)
		{
			if (script == event.script)
			{
				if (!maxFilters) return;
				if (!event.eventFilter->GetNumFilters()) continue;
				UInt32 i = 0; // filter iterator
				for (; i < maxFilters; i++)
				{
					if (!(event.eventFilter->IsFilterEqual(filters[i], i))) break;
				}
				if (i >= maxFilters) return;
			}
		}
		std::shared_lock rLock(queueLock);
		for (auto& event : this->eventAddQueue) {
			if (script == event.script)
			{
				if (!maxFilters) return;
				if (!event.eventFilter->GetNumFilters()) continue;
				UInt32 i = 0; // filter iterator
				for (; i < maxFilters; i++)
				{
					if (!(event.eventFilter->IsFilterEqual(filters[i], i))) break;
				}
				if (i >= maxFilters) return;
			}
		}
		EventBase event;
		event.script = script;
		event.capturedLambdaVars = LambdaVariableContext(script);
		if (maxFilters)
		{
			event.eventFilter = static_cast<IFilter*>(this->CreateFilter(filters, maxFilters));
			event.eventFilter->SetUpFiltering();
		}
		std::unique_lock wLock(queueLock);
		this->eventAddQueue.push_back(std::move(event));
	}

	void virtual RemoveEvent(Script* script, void** filters)
	{
		for (auto& event : callbacks)
		{
			if (script != event.script) continue;

			bool skip = false;
			
			if (auto eventFilters = event.eventFilter)
			{
				UInt32 maxFilters = eventFilters->GetNumFilters();
				for (UInt32 i = 0; i < maxFilters; i++)
				{
					if (!(event.eventFilter->IsFilterEqual(filters[i], i))) {
						skip = true;
						break;
					}
				}
			}
			if (!skip)
			{
				event.SetDeleted(true);
			}
			
		}
	}

	void virtual AddQueuedEvents()
	{
		callbacks.insert(callbacks.end(), std::make_move_iterator(eventAddQueue.begin()),
		                      std::make_move_iterator(eventAddQueue.end()));
		eventAddQueue.clear();
	}

	void virtual DeleteEvents()
	{
		auto it = callbacks.begin();
		while (it != callbacks.end())
		{
			if (it->GetDeleted())
			{
				delete it->eventFilter;

				it = callbacks.erase(it);
			}
			else {
				++it;
			}
		}
	}
};

typedef EventInformation* EventInfo;
std::mutex eventInfosMutex;
std::vector<EventInfo> EventInfos;

void* __fastcall GenericCreateFilter(void** Filters, UInt32 numFilters)
{
	return new FilterForm(Filters, numFilters);
}


EventInfo __cdecl JGCreateEvent(const char* EventName, UInt8 maxArgs, UInt8 maxFilters,
                                void* (__fastcall*CreatorFunction)(void**, UInt32) = nullptr)
{
	std::lock_guard<std::mutex> lock(eventInfosMutex);
	EventInfo eventinfo = new EventInformation(EventName, maxArgs, maxFilters, CreatorFunction);
	EventInfos.push_back(eventinfo);
	return eventinfo;
}


void __cdecl JGFreeEvent(EventInfo& toRemove)
{
	std::lock_guard<std::mutex> lock(eventInfosMutex);
	if (!toRemove) return;
	auto it = std::find(std::begin(EventInfos), std::end(EventInfos), toRemove);
	if (it != EventInfos.end())
	{
		delete*it;
		it = EventInfos.erase(it);
	}
	toRemove = nullptr;
}
