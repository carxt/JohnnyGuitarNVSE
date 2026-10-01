#include "EventFramework.h"
#include "Bethesda/TESObjectREFR.hpp"
#include "Bethesda/ExtraLeveledCreature.hpp"

STACK_FRAME_OPT_ENABLE

bool (*CallUDF)(Script* funcScript, TESObjectREFR* callingObj, uint8_t numArgs, ...);
std::shared_mutex kEventInfosMutex;
std::vector<EventInfo> kEventInfos;

void* __fastcall GenericCreateFilter(void** appFilters, uint32_t auiFilterCount) {
	return new FilterForm(appFilters, auiFilterCount);
}

EventInfo __cdecl JGCreateEvent(const char* apEventName, uint8_t aucMaxArgs, uint8_t aucMaxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t)) {
	std::lock_guard kGuard(kEventInfosMutex);
	EventInfo pEventInfo = new EventInformation(apEventName, aucMaxArgs, aucMaxFilters, CreatorFunction);
	kEventInfos.push_back(pEventInfo);
	return pEventInfo;
}

void __cdecl JGFreeEvent(EventInfo& arEvent) {
	if (!arEvent)
		return;

	std::lock_guard kGuard(kEventInfosMutex);
	auto it = std::find(kEventInfos.begin(), kEventInfos.end(), arEvent);
	if (it != kEventInfos.end()) {
		delete* it;
		it = kEventInfos.erase(it);
	}
	arEvent = nullptr;
}

FilterBase::FilterSet* __fastcall FilterBase::GetFilter(uint32_t auiIndex) const {
	if (auiIndex >= uiFilterCount) [[unlikely]]
		return nullptr;

	return &(pFilterSets[auiIndex]);
}

FilterBase::FilterBase(void** appFilters, uint32_t auiFilterCount) {
	uiFilterCount = auiFilterCount;
	pFilterSets = new FilterSet[uiFilterCount];
	pFilterTypes = new FilterType[uiFilterCount];
	for (uint32_t i = 0; i < auiFilterCount; i++) 
		pFilterTypes[i].pVal = appFilters[i];
}

FilterBase::~FilterBase() {
	delete[] pFilterSets;
	delete[] pFilterTypes;
}

bool FilterBase::IsInFilter(uint32_t auiIndex, FilterType auFilter) const {
	const FilterSet* pFilters = GetFilter(auiIndex);
	return pFilters && pFilters->contains(auFilter.uiFormID);
}

bool FilterBase::IsFilterEmpty(uint32_t auiIndex) {
	const FilterSet* pFilters = GetFilter(auiIndex);
	return !pFilters || pFilters->empty();
}

void FilterBase::InsertToFilter(uint32_t auiIndex, FilterType auFilter) {
	FilterSet* pFilters = GetFilter(auiIndex);
	if (pFilters) 
		pFilters->insert(auFilter.uiFormID);
}

void FilterBase::DeleteFromFilter(uint32_t auiIndex, FilterType auFilter) {
	FilterSet* pFilters = GetFilter(auiIndex);
	if (pFilters) 
		pFilters->erase(auFilter.uiFormID);
}

bool FilterBase::IsFilterEqual(FilterType auFilter, uint32_t auiIndex) {
	return auFilter.pVal == pFilterTypes[auiIndex].pVal;
}

bool __fastcall FilterForm::DoFilterForm(const FilterSet& arSet, const TESForm* apForm) {
	return arSet.contains(apForm->GetFormID());
}

bool __fastcall FilterForm::DoFilterRef(const FilterSet& arSet, const TESObjectREFR* apRef) {
	if (arSet.contains(apRef->GetFormID()))
		return true;

	const TESBoundObject* pBase = apRef->GetObjectReference();
	if (pBase && !pBase->GetTemporary()) [[likely]] {
		if (arSet.contains(pBase->GetFormID()))
			return true;

		if (pBase->GetFormType() == FORM_TYPE::BGSPlaceableWater) [[unlikely]] {
			const TESWaterForm* pWater = pBase->GetWaterType();
			if (pWater && arSet.contains(pWater->GetFormID()))
				return true;
		}

		if (apRef->IsLeveledCreature()) [[unlikely]] {
			const ExtraLeveledCreature* pExtra = apRef->GetExtraData<ExtraLeveledCreature>();
			pBase = pExtra->pTemplate;
			if (pBase && arSet.contains(pBase->GetFormID()))
				return true;

			pBase = pExtra->pOriginalBase;
			if (pBase && arSet.contains(pBase->GetFormID()))
				return true;
		}
	}

	return false;
}

bool FilterForm::IsAcceptedParameter(FilterType parameter) {
	return parameter.pForm->GetFormType() != FORM_TYPE::TESObjectSTAT;
}

void FilterForm::SetUpFiltering() {
	for (uint32_t i = 0; i < uiFilterCount; ++i) {
		const TESForm* pCurrentForm = pFilterTypes[i].pForm;
		if (pCurrentForm) [[likely]]
			InsertForm(i, pCurrentForm);
	}
}

bool __fastcall FilterForm::IsAnyFormInFilter(uint32_t auiIndex, const TESForm* apForm) const {
	if (!apForm) [[unlikely]]
		return false;

	const FilterSet* pFilter = GetFilter(auiIndex);
	if (!pFilter || pFilter->empty()) [[unlikely]]
		return false;

	if (TESObjectREFR::IsReferenceFormType(apForm->GetFormType()))
		return DoFilterRef(*pFilter, static_cast<const TESObjectREFR*>(apForm));
	else
		return DoFilterForm(*pFilter, apForm);
}

bool __fastcall FilterForm::IsNonRefFormInFilter(uint32_t auiIndex, const TESForm* apForm) const {
	if (!apForm) [[unlikely]]
		return false;

	const FilterSet* pFilter = GetFilter(auiIndex);
	if (!pFilter || pFilter->empty()) [[unlikely]]
		return false;

	assert(!apForm->IsReference());
	return DoFilterForm(*pFilter, apForm);
}

bool __fastcall FilterForm::IsRefInFilter(uint32_t auiIndex, const TESObjectREFR* apRef) const {
	if (!apRef) [[unlikely]]
		return false;

	const FilterSet* pFilter = GetFilter(auiIndex);
	if (!pFilter || pFilter->empty()) [[unlikely]]
		return false;

	return DoFilterRef(*pFilter, apRef);
}

void __fastcall FilterForm::InsertForm(uint32_t auiIndex, const TESForm* apForm) {
	const FORM_TYPE eFormType = apForm->GetFormType();
	if (TESObjectREFR::IsReferenceFormType(eFormType)) [[unlikely]] {
		InsertReference(auiIndex, static_cast<const TESObjectREFR*>(apForm));
	}
	else if (eFormType == FORM_TYPE::BGSListForm) [[unlikely]] {
		InsertFormList(auiIndex, static_cast<const BGSListForm*>(apForm));
	}
	else if (IsAcceptedParameter(apForm)) [[likely]] {
		FilterBase::InsertToFilter(auiIndex, apForm->GetFormID());
	}
}

void __fastcall FilterForm::InsertReference(uint32_t auiIndex, const TESObjectREFR* apRef) {
	const TESForm* pBase = apRef->GetObjectReference();
	if (pBase && IsAcceptedParameter(pBase)) [[likely]]
		FilterBase::InsertToFilter(auiIndex, pBase->GetFormID());
}

void __fastcall FilterForm::InsertFormList(uint32_t auiIndex, const BGSListForm* apFormList) {
	const BSSimpleList<TESForm*>* pIter = apFormList->GetFormList();
	while (pIter && !pIter->IsEmpty()){
		const TESForm* pForm = pIter->GetItem();
		pIter = pIter->GetNext();
		if (pForm) [[likely]] {
			InsertForm(auiIndex, pForm);
		}
	};
}

void FilterInt::SetUpFiltering() {
	for (uint32_t i = 0; i < uiFilterCount; i++) {
		if (pFilterTypes[i].iVal != -1) 
			FilterBase::InsertToFilter(i, pFilterTypes[i].iVal);
	}
}

void* __fastcall FilterInt::Create(void** appFilters, uint32_t auiFilterCount) {
	return new FilterInt(appFilters, auiFilterCount);
}

bool FilterFormInt::IsAcceptedParameter(FilterType parameter) {
	return parameter.pForm->GetFormID() != 0x3B; // xMarker
}

void FilterFormInt::SetUpFiltering() {
	if (pFilterTypes[1].iVal != -1) 
		FilterBase::InsertToFilter(1, pFilterTypes[1].iVal);

	const TESForm* pCurrentForm = pFilterTypes[0].pForm;
	if (pCurrentForm) [[likely]]
		InsertForm(0, pCurrentForm);
}

void* __fastcall FilterFormInt::Create(void** appFilters, uint32_t auiFilterCount) {
	return new FilterFormInt(appFilters, auiFilterCount);
}

EventInformation::EventInformation(const char* apEventName, uint8_t& arMaxArgs, uint8_t& arMaxFilters, void* (__fastcall* CreatorFunction)(void**, uint32_t)) {
	this->pName = apEventName;
	this->ucMaxArgsCount = arMaxArgs;
	this->ucMaxFilterCount = arMaxFilters;
	this->CreateFilter = GenericCreateFilter;
	if (CreatorFunction) 
		this->CreateFilter = CreatorFunction;
}

EventInformation::~EventInformation() {
	FlushEventCallbacks();
}

void EventInformation::FlushEventCallbacks() {
	for (auto& event : kCallbacks) {
		delete event.pFilter;
	}
	kCallbacks.clear();
}

void EventInformation::RegisterEvent(Script* apScript, void** appFilters, uint32_t auiUserFlags) {
	const uint32_t uiMaxFilterCount = ucMaxFilterCount;
	for (auto& rEvent : kCallbacks) {
		if (apScript == rEvent.pScript) {
			if (!uiMaxFilterCount) [[unlikely]]
				return;
			
			if (!rEvent.pFilter->GetNumFilters()) [[unlikely]]
				continue;
			
			uint32_t i = 0; // auFilter iterator
			for (; i < uiMaxFilterCount; i++) {
				if (!rEvent.pFilter->IsFilterEqual(appFilters[i], i)) 
					break;
			}
			
			if (i >= uiMaxFilterCount) 
				return;
		}
	}
	
	{
		std::shared_lock rLock(kQueueLock);
		for (auto& rEvent : kEventAddQueue) {
			if (apScript == rEvent.pScript) {
				if (!uiMaxFilterCount) [[unlikely]]
					return;

				if (!rEvent.pFilter->GetNumFilters()) [[unlikely]]
					continue;

				uint32_t i = 0; // auFilter iterator
				for (; i < uiMaxFilterCount; i++) {
					if (!rEvent.pFilter->IsFilterEqual(appFilters[i], i))
						break;
				}

				if (i >= uiMaxFilterCount)
					return;
			}
		}
	}

	EventBase kEvent;
	kEvent.usUserFlags = auiUserFlags;
	kEvent.pScript = apScript;
	kEvent.pLambdaVars = LambdaVariableContext(apScript);
	if (uiMaxFilterCount) {
		kEvent.pFilter = static_cast<IFilter*>(this->CreateFilter(appFilters, uiMaxFilterCount));
		kEvent.pFilter->SetUpFiltering();
	}
	std::unique_lock wLock(kQueueLock);
	kEventAddQueue.push_back(std::move(kEvent));
}

void EventInformation::RemoveEvent(Script* apScript, void** appFilters) {
	for (auto& rEvent : kCallbacks) {
		if (apScript != rEvent.pScript) 
			continue;

		bool bSkip = false;
		if (auto eventFilters = rEvent.pFilter) {
			const uint32_t uiFilterCount = eventFilters->GetNumFilters();
			for (uint32_t i = 0; i < uiFilterCount; ++i) {
				if (!rEvent.pFilter->IsFilterEqual(appFilters[i], i)) {
					bSkip = true;
					break;
				}
			}
		}

		if (!bSkip)
			rEvent.SetDeleted(true);
	}
}

void EventInformation::AddQueuedEvents() {
	kCallbacks.insert(kCallbacks.end(), std::make_move_iterator(kEventAddQueue.begin()), std::make_move_iterator(kEventAddQueue.end()));
	kEventAddQueue.clear();
}

void EventInformation::DeleteEvents() {
	auto it = kCallbacks.begin();
	while (it != kCallbacks.end()) {
		if (it->GetDeleted()) {
			delete it->pFilter;

			it = kCallbacks.erase(it);
		}
		else {
			++it;
		}
	}
}
STACK_FRAME_OPT_RESET