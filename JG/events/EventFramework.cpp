#include "EventFramework.h"
#include "GameObjects.h"

bool (*CallUDF)(Script* funcScript, TESObjectREFR* callingObj, UInt8 numArgs, ...);
std::mutex eventInfosMutex;
std::vector<EventInfo> EventInfos;

void* __fastcall GenericCreateFilter(void** Filters, UInt32 numFilters) {
	return new FilterForm(Filters, numFilters);
}

EventInfo __cdecl JGCreateEvent(const char* EventName, UInt8 maxArgs, UInt8 maxFilters, void* (__fastcall* CreatorFunction)(void**, UInt32)) {
	std::lock_guard<std::mutex> lock(eventInfosMutex);
	EventInfo eventinfo = new EventInformation(EventName, maxArgs, maxFilters, CreatorFunction);
	EventInfos.push_back(eventinfo);
	return eventinfo;
}

void __cdecl JGFreeEvent(EventInfo& toRemove) {
	std::lock_guard<std::mutex> lock(eventInfosMutex);
	if (!toRemove) return;
	auto it = std::find(std::begin(EventInfos), std::end(EventInfos), toRemove);
	if (it != EventInfos.end()) {
		delete* it;
		it = EventInfos.erase(it);
	}
	toRemove = nullptr;
}

FilterBase::FilterSet* FilterBase::GetFilter(UInt32 index) {
	if (index >= numFilters) return nullptr;
	return &(filterSet[index]);
}

FilterBase::FilterBase(void** filters, UInt32 nuFilters) {
	numFilters = nuFilters;
	filterSet = new FilterSet[numFilters];
	genFilters = new FilterType[numFilters];
	for (int i = 0; i < nuFilters; i++) genFilters[i].ptr = filters[i];
}

FilterBase::~FilterBase() {
	delete[] filterSet;
	delete[] genFilters;
}

bool FilterBase::IsInFilter(UInt32 filterNum, FilterType toSearch) {
	FilterSet* FilterSet = GetFilter(filterNum);
	return FilterSet && (FilterSet->empty() || FilterSet->find(toSearch.refID) != FilterSet->end());
}

bool FilterBase::IsFilterEmpty(UInt32 num) {
	FilterSet* filters = GetFilter(num);
	return !filters || filters->empty();
}

void FilterBase::InsertToFilter(UInt32 num, FilterType toInsert) {
	FilterSet* filters = GetFilter(num);
	if (filters) filters->insert(toInsert.refID);
}

void FilterBase::DeleteFromFilter(UInt32 num, FilterType toDelete) {
	FilterSet* filters = GetFilter(num);
	if (filters) filters->erase(toDelete.refID);
}

bool FilterBase::IsFilterEqual(FilterType filter, UInt32 num) {
	return (filter.ptr == genFilters[num].ptr);
}

bool FilterForm::IsAcceptedParameter(FilterType parameter) {
	return parameter.form->typeID != kFormType_TESObjectSTAT;
}

void FilterForm::SetUpFiltering() {
	for (int i = 0; i < numFilters; i++) {
		TESForm* currentFilter = genFilters[i].form;
		if (!currentFilter) continue;
		if (!(IsAcceptedParameter(currentFilter))) continue;
		if (currentFilter->GetIsReference()) {
			InsertToFilter(i, ((TESObjectREFR*)currentFilter)->baseForm->refID);
			continue;
		}
		if (IS_TYPE(currentFilter, BGSListForm)) {
			ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
			do {
				TESForm* it = iterator->data;
				if (it && !it->GetIsReference() && IsAcceptedParameter(it))
					InsertToFilter(i, it->refID);
			} while (iterator = iterator->next);
		}
		else InsertToFilter(i, currentFilter->refID);
	}
}

bool FilterForm::IsBaseInFilter(UInt32 filterNum, TESForm* form) {
	if (!form) return false;
	if (form->GetIsReference()) return IsInFilter(filterNum, ((TESObjectREFR*)form)->baseForm->refID);
	return IsInFilter(filterNum, form->refID);
}

void FilterForm::insertFormList(BGSListForm* formlist, UInt32 filter) {
	ListNode<TESForm>* iterator = formlist->list.Head();
	do {
		InsertToFilter(filter, iterator->data->refID);
	} while (iterator = iterator->next);
}

bool FilterInt::IsFilterEqual(FilterType Filter, UInt32 nuFilter) {
	return Filter.intVal == genFilters[nuFilter].intVal;
}

void FilterInt::SetUpFiltering() {
	for (int i = 0; i < numFilters; i++) {
		if (genFilters[i].intVal != -1) InsertToFilter(i, genFilters[i].intVal);
	}
}

void* __fastcall FilterInt::Create(void** filters, UInt32 nuFilters) {
	return new FilterInt(filters, nuFilters);
}

void FilterFormInt::SetUpFiltering() {
	if (genFilters[1].intVal != -1) InsertToFilter(1, genFilters[1].intVal);
	TESForm* currentFilter = genFilters[0].form;
	if (!currentFilter) return;
	if (IS_TYPE(currentFilter, BGSListForm)) {
		ListNode<TESForm>* iterator = ((BGSListForm*)currentFilter)->list.Head();
		do {
			TESForm* it = iterator->data;
			if (it && IsAcceptedParameter(it))
				InsertToFilter(0, it->refID);
		} while (iterator = iterator->next);
	}
	else if (IsAcceptedParameter(currentFilter)) InsertToFilter(0, currentFilter->refID);
}

void* __fastcall FilterFormInt::Create(void** filters, UInt32 nuFilters) {
	return new FilterFormInt(filters, nuFilters);
}

EventInformation::EventInformation(const char* EventName, UInt8& numMaxArgs, UInt8& numMaxFilters, void* (__fastcall* CreatorFunction)(void**, UInt32)) {
	this->name = EventName;
	this->numMaxArgs = numMaxArgs;
	this->numMaxFilters = numMaxFilters;
	this->CreateFilter = GenericCreateFilter;
	if (CreatorFunction) this->CreateFilter = CreatorFunction;
}

EventInformation::~EventInformation() {
	FlushEventCallbacks();
}

void EventInformation::FlushEventCallbacks() {
	for (auto& event : callbacks) {
		delete event.eventFilter;
	}
	callbacks.clear();
}

void EventInformation::RegisterEvent(Script* script, void** filters) {
	UInt32 maxFilters = this->numMaxFilters;
	for (auto& event : this->callbacks) {
		if (script == event.script) {
			if (!maxFilters) return;
			if (!event.eventFilter->GetNumFilters()) continue;
			UInt32 i = 0; // filter iterator
			for (; i < maxFilters; i++) {
				if (!(event.eventFilter->IsFilterEqual(filters[i], i))) break;
			}
			if (i >= maxFilters) return;
		}
	}
	std::shared_lock rLock(queueLock);
	for (auto& event : this->eventAddQueue) {
		if (script == event.script) {
			if (!maxFilters) return;
			if (!event.eventFilter->GetNumFilters()) continue;
			UInt32 i = 0; // filter iterator
			for (; i < maxFilters; i++) {
				if (!(event.eventFilter->IsFilterEqual(filters[i], i))) break;
			}
			if (i >= maxFilters) return;
		}
	}
	rLock.unlock();
	EventBase event;
	event.script = script;
	event.capturedLambdaVars = LambdaVariableContext(script);
	if (maxFilters) {
		event.eventFilter = static_cast<IFilter*>(this->CreateFilter(filters, maxFilters));
		event.eventFilter->SetUpFiltering();
	}
	std::unique_lock wLock(queueLock);
	this->eventAddQueue.push_back(std::move(event));
}

void EventInformation::RemoveEvent(Script* script, void** filters) {
	for (auto& event : callbacks) {
		if (script != event.script) continue;

		bool skip = false;

		if (auto eventFilters = event.eventFilter) {
			UInt32 maxFilters = eventFilters->GetNumFilters();
			for (UInt32 i = 0; i < maxFilters; i++) {
				if (!(event.eventFilter->IsFilterEqual(filters[i], i))) {
					skip = true;
					break;
				}
			}
		}
		if (!skip) {
			event.SetDeleted(true);
		}

	}
}

void EventInformation::AddQueuedEvents() {
	callbacks.insert(callbacks.end(), std::make_move_iterator(eventAddQueue.begin()),
		std::make_move_iterator(eventAddQueue.end()));
	eventAddQueue.clear();
}

void EventInformation::DeleteEvents() {
	auto it = callbacks.begin();
	while (it != callbacks.end()) {
		if (it->GetDeleted()) {
			delete it->eventFilter;

			it = callbacks.erase(it);
		}
		else {
			++it;
		}
	}
}
