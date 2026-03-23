#include "EventFramework.h"
#include "GameObjects.h"

bool (*CallUDF)(Script* funcScript, TESObjectREFR* callingObj, uint8_t numArgs, ...);
std::mutex eventInfosMutex;
std::vector<EventInfo> EventInfos;

void* __fastcall GenericCreateFilter(void** Filters, uint32_t numFilters) {
	return new FilterForm(Filters, numFilters);
}

EventInfo __cdecl JGCreateEvent(const char* EventName, uint8_t maxArgs, uint8_t maxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t)) {
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

FilterBase::FilterSet* FilterBase::GetFilter(uint32_t index) {
	if (index >= numFilters) return nullptr;
	return &(filterSet[index]);
}

FilterBase::FilterBase(void** filters, uint32_t nuFilters) {
	numFilters = nuFilters;
	filterSet = new FilterSet[numFilters];
	genFilters = new FilterType[numFilters];
	for (uint32_t i = 0; i < nuFilters; i++) genFilters[i].ptr = filters[i];
}

FilterBase::~FilterBase() {
	delete[] filterSet;
	delete[] genFilters;
}

bool FilterBase::IsInFilter(uint32_t filterNum, FilterType toSearch) {
	FilterSet* FilterSet = GetFilter(filterNum);
	return FilterSet && (FilterSet->empty() || FilterSet->find(toSearch.refID) != FilterSet->end());
}

bool FilterBase::IsFilterEmpty(uint32_t num) {
	FilterSet* filters = GetFilter(num);
	return !filters || filters->empty();
}

void FilterBase::InsertToFilter(uint32_t num, FilterType toInsert) {
	FilterSet* filters = GetFilter(num);
	if (filters) filters->insert(toInsert.refID);
}

void FilterBase::DeleteFromFilter(uint32_t num, FilterType toDelete) {
	FilterSet* filters = GetFilter(num);
	if (filters) filters->erase(toDelete.refID);
}

bool FilterBase::IsFilterEqual(FilterType filter, uint32_t num) {
	return (filter.ptr == genFilters[num].ptr);
}

bool FilterForm::IsAcceptedParameter(FilterType parameter) {
	return parameter.form->GetFormType() != FORM_TYPE::TESObjectSTAT;
}

void FilterForm::SetUpFiltering() {
	for (uint32_t i = 0; i < numFilters; i++) {
		TESForm* currentFilter = genFilters[i].form;
		if (!currentFilter) continue;
		if (!(IsAcceptedParameter(currentFilter))) continue;
		if (currentFilter->IsReference()) {
			InsertToFilter(i, ((TESObjectREFR*)currentFilter)->baseForm->GetFormID());
			continue;
		}
		if (IS_TYPE(currentFilter, BGSListForm)) {
			BSSimpleList<TESForm*>* pIter = ((BGSListForm*)currentFilter)->GetFormList();
			while (pIter && !pIter->IsEmpty()) {
				TESForm* pForm = pIter->GetItem();
				pIter = pIter->GetNext();
				if (pForm && !pForm->IsReference() && IsAcceptedParameter(pForm))
					InsertToFilter(i, pForm->GetFormID());
			};
		}
		else InsertToFilter(i, currentFilter->GetFormID());
	}
}

bool FilterForm::IsBaseInFilter(uint32_t filterNum, TESForm* form) {
	if (!form) return false;
	if (form->IsReference()) return IsInFilter(filterNum, ((TESObjectREFR*)form)->baseForm->GetFormID());
	return IsInFilter(filterNum, form->GetFormID());
}

void FilterForm::insertFormList(BGSListForm* formlist, uint32_t filter) {
	BSSimpleList<TESForm*>* pIter = formlist->GetFormList();
	while (pIter && !pIter->IsEmpty()){
		TESForm* pForm = pIter->GetItem();
		pIter = pIter->GetNext();
		if (pForm)
			InsertToFilter(filter, pForm->GetFormID());
	};
}

bool FilterInt::IsFilterEqual(FilterType Filter, uint32_t nuFilter) {
	return Filter.intVal == genFilters[nuFilter].intVal;
}

void FilterInt::SetUpFiltering() {
	for (uint32_t i = 0; i < numFilters; i++) {
		if (genFilters[i].intVal != -1) InsertToFilter(i, genFilters[i].intVal);
	}
}

void* __fastcall FilterInt::Create(void** filters, uint32_t nuFilters) {
	return new FilterInt(filters, nuFilters);
}

void FilterFormInt::SetUpFiltering() {
	if (genFilters[1].intVal != -1) InsertToFilter(1, genFilters[1].intVal);
	TESForm* currentFilter = genFilters[0].form;
	if (!currentFilter) return;
	if (IS_TYPE(currentFilter, BGSListForm)) {
		BSSimpleList<TESForm*>* pIter = ((BGSListForm*)currentFilter)->GetFormList();
		while (pIter && !pIter->IsEmpty()) {
			TESForm* pForm = pIter->GetItem();
			pIter = pIter->GetNext();
			if (pForm && IsAcceptedParameter(pForm))
				InsertToFilter(0, pForm->GetFormID());
		};
	}
	else if (IsAcceptedParameter(currentFilter)) InsertToFilter(0, currentFilter->GetFormID());
}

void* __fastcall FilterFormInt::Create(void** filters, uint32_t nuFilters) {
	return new FilterFormInt(filters, nuFilters);
}

EventInformation::EventInformation(const char* EventName, uint8_t& numMaxArgs, uint8_t& numMaxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t)) {
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

void EventInformation::RegisterEvent(Script* script, void** filters, uint32_t userFlags) {
	uint32_t maxFilters = this->numMaxFilters;
	for (auto& event : this->callbacks) {
		if (script == event.script) {
			if (!maxFilters) return;
			if (!event.eventFilter->GetNumFilters()) continue;
			uint32_t i = 0; // filter iterator
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
			uint32_t i = 0; // filter iterator
			for (; i < maxFilters; i++) {
				if (!(event.eventFilter->IsFilterEqual(filters[i], i))) break;
			}
			if (i >= maxFilters) return;
		}
	}
	rLock.unlock();
	EventBase event;
	event.UserFlags = userFlags;
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
			uint32_t maxFilters = eventFilters->GetNumFilters();
			for (uint32_t i = 0; i < maxFilters; i++) {
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
