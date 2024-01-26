#pragma once
#include "events/EventFilteringInterface.h"
#include <unordered_set>
bool (*CallUDF)(Script* funcScript, TESObjectREFR* callingObj, UInt8 numArgs, ...);

NVSEArrayElement EventResultPtr;
class EventInformation;
void* __fastcall GenericCreateFilter(void** maxFilters, UInt32 numFilters);

class JohnnyEventFiltersForm : EventHandlerInterface {
	typedef  std::unordered_set<unsigned int> RefUnorderedSet;

private:
	RefUnorderedSet* Filters = 0;

	RefUnorderedSet* GetFilter(UInt32 filter) {
		if (filter >= numFilters) return NULL;
		return &(Filters[filter]);
	}
public:
	JohnnyEventFiltersForm(void** filters, UInt32 nuFilters) {
		numFilters = nuFilters;
		Filters = new RefUnorderedSet[numFilters];
		GenFilters = new GenericFilters[numFilters];
		for (int i = 0; i < nuFilters; i++) GenFilters[i].ptr = filters[i];
	}
	virtual ~JohnnyEventFiltersForm() {
		delete[] Filters;
		delete[] GenFilters;
	}

	virtual bool IsInFilter(UInt32 filterNum, GenericFilters toSearch) {
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return false;
		//RefUnorderedSet::const_iterator got = FilterSet->find(toSearch);
		return  FilterSet->empty() || (FilterSet->find(toSearch.refID) != FilterSet->end());
	}

	virtual void InsertToFilter(UInt32 filterNum, GenericFilters toInsert) {
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->insert(toInsert.refID);
	}
	virtual void DeleteFromFilter(UInt32 filterNum, GenericFilters toDelete) {
		RefUnorderedSet* FilterSet;
		if (!(FilterSet = GetFilter(filterNum))) return;
		FilterSet->erase(toDelete.refID);
	}
	virtual bool IsFilterEmpty(UInt32 filterNum) {
		RefUnorderedSet* FilterSet = GetFilter(filterNum);
		if (!FilterSet) return true;
		return FilterSet->empty();
	}
	virtual bool IsFilterEqual(GenericFilters Filter, UInt32 nuFilter) {
		return (Filter.ptr == GenFilters[nuFilter].ptr);
	}
	virtual bool IsAcceptedParameter(GenericFilters parameter) {
		return parameter.form->typeID != kFormType_TESObjectSTAT;
	}

	virtual void SetUpFiltering() {
		for (int i = 0; i < numFilters; i++) {
			TESForm* currentFilter = GenFilters[i].form;
			if (!currentFilter) continue;
			if (!(IsAcceptedParameter(currentFilter))) continue;
			if (currentFilter->GetIsReference()) {
				InsertToFilter(i, ((TESObjectREFR*)currentFilter)->baseForm->refID);
				continue;
			}
			if (IS_TYPE(currentFilter, BGSListForm)) {
				//Console_Print("filter looping");
				ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
				do {
					TESForm* it = iterator->data;
					if (!it || it->GetIsReference()) continue;
					if (IsAcceptedParameter(it))
						InsertToFilter(i, it->refID);
				} while (iterator = iterator->next);
			}
			else InsertToFilter(i, currentFilter->refID);
		}
	}

	__forceinline bool IsBaseInFilter(UInt32 filterNum, TESForm* form) {
		if (!form) return false;
		if (form->GetIsReference()) return IsInFilter(filterNum, ((TESObjectREFR*)form)->baseForm->refID);
		return IsInFilter(filterNum, form->refID);
	}

	void insertFormList(BGSListForm* List, UInt32 filter) {
		ListNode<TESForm>* iterator = ((BGSListForm*)List)->list.Head();
		do {
			InsertToFilter(filter, iterator->data->refID);
		} while (iterator = iterator->next);
	}
};

class EventInformation {
private:
	void* (__fastcall* CreateFilter)(void**, UInt32); // supposed to be passing itself
	std::vector<BaseEventClass> EventQueueAdd;
	std::shared_mutex QueueRWLock; //need a readers writer lock to protect from multiple users registering an event in the same frame (very rare, but can happen)
public:
	const char* EventName;
	UInt8 numMaxArgs;
	UInt8 numMaxFilters;
	std::vector<BaseEventClass> EventCallbacks;
	EventInformation(const char* EventName, UInt8& numMaxArgs, UInt8& numMaxFilters, void* (__fastcall* CreatorFunction)(void**, UInt32)) {
		this->EventName = EventName;
		this->numMaxArgs = numMaxArgs;
		this->numMaxFilters = numMaxFilters;
		this->CreateFilter = GenericCreateFilter;
		if (CreatorFunction) this->CreateFilter = CreatorFunction;
	}
	virtual ~EventInformation() {
		FlushEventCallbacks();
	}
	void FlushEventCallbacks() {
		auto it = EventCallbacks.begin();
		while (it != EventCallbacks.end()) {
			delete it->eventFilter;
			++it;
		}
		EventCallbacks.clear();
	}

	void virtual RegisterEvent(Script* script, void** filters) {
		UInt32 maxFilters = this->numMaxFilters;
		for (std::vector<BaseEventClass>::iterator it = this->EventCallbacks.begin(); it != this->EventCallbacks.end(); ++it) {
			if (script == it->ScriptForEvent) {
				if (!maxFilters) return;
				if (!it->eventFilter->GetNumFilters()) continue;
				int i = 0; // filter iterator
				for (; i < maxFilters; i++) {
					if (!(it->eventFilter->IsFilterEqual(filters[i], i))) break;
				}
				if (i >= maxFilters) return;
			}
		}
		std::shared_lock rLock(QueueRWLock);
		for (std::vector<BaseEventClass>::iterator it = this->EventQueueAdd.begin(); it != this->EventQueueAdd.end(); ++it) {
			if (script == it->ScriptForEvent) {
				if (!maxFilters) return;
				if (!it->eventFilter->GetNumFilters()) continue;
				int i = 0; // filter iterator
				for (; i < maxFilters; i++) {
					if (!(it->eventFilter->IsFilterEqual(filters[i], i))) break;
				}
				if (i >= maxFilters) return;
			}
		}
		rLock.unlock();
		BaseEventClass NewEvent;
		NewEvent.ScriptForEvent = script;
		NewEvent.capturedLambdaVars = LambdaVariableContext(script);
		if (maxFilters) {
			*(void**)&(NewEvent.eventFilter) = this->CreateFilter(filters, maxFilters);
			NewEvent.eventFilter->SetUpFiltering();
		}
		std::unique_lock wLock(QueueRWLock);
		this->EventQueueAdd.push_back(std::move(NewEvent));
	}
	void virtual RemoveEvent(Script* script, void** filters) {
		auto it = EventCallbacks.begin();
		while (it != EventCallbacks.end()) {
			if (script == it->ScriptForEvent) {
				if (auto eventFilters = it->eventFilter) {
					UInt32 maxFilters = eventFilters->GetNumFilters();
					for (int i = 0; i < maxFilters; i++) {
						if (!(it->eventFilter->IsFilterEqual(filters[i], i))) goto NotFound;
					}
				}
				it->SetDeleted(true);
			}
		NotFound:
			it++;
		}
	}
	void virtual AddQueuedEvents() {
		EventCallbacks.insert(EventCallbacks.end(), std::make_move_iterator(EventQueueAdd.begin()), std::make_move_iterator(EventQueueAdd.end()));
		EventQueueAdd.clear();
	}
	void virtual DeleteEvents() {
		auto it = EventCallbacks.begin();
		while (it != EventCallbacks.end()) {
			if (it->GetDeleted()) {
				if (it->eventFilter) {
					delete it->eventFilter;
				}

				it = EventCallbacks.erase(it);
				continue;
			}
			it++;
		}
	}
	int a = sizeof(std::unordered_set<char>);
};
typedef EventInformation* EventInfo;
std::mutex EventsArrayMutex;
std::vector<EventInfo> EventsArray;

void* __fastcall GenericCreateFilter(void** Filters, UInt32 numFilters) {
	return new JohnnyEventFiltersForm(Filters, numFilters);
}

EventInfo FindHandlerInfoByChar(const char* nameToFind) {
	auto it = EventsArray.begin();
	while (it != EventsArray.end()) {
		if (!(_stricmp((*it)->EventName, nameToFind)))
			return *it;
		it++;
	}
	return NULL;
}

EventInfo __cdecl JGCreateEvent(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, void* (__fastcall* CreatorFunction)(void**, UInt32)) {
	std::lock_guard<std::mutex> lock(EventsArrayMutex);
	EventInfo eventinfo = new EventInformation(EventName, maxArgs, maxFilters, CreatorFunction);
	EventsArray.push_back(eventinfo);
	return eventinfo;
}

void __cdecl JGFreeEvent(EventInfo& toRemove) {
	std::lock_guard<std::mutex> lock(EventsArrayMutex);
	if (!toRemove) return;
	auto it = std::find(std::begin(EventsArray), std::end(EventsArray), toRemove);
	if (it != EventsArray.end()) {
		delete* it;
		it = EventsArray.erase(it);
	}
	toRemove = NULL;
}
