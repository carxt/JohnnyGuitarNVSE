#include "TESContainer.hpp"
#include "TESObjectREFR.hpp"
#include "TESObjectLIGH.hpp"

// GAME - 0x717E50
const BSSimpleList<ContainerObject*>* TESContainer::GetObjectList() const {
	return &kObjects;
}

// GAME - 0x717E50
BSSimpleList<ContainerObject*>* TESContainer::GetObjectList() {
	return &kObjects;
}

// GAME - 0x481FD0
// GECK - 0x4F4E30
void TESContainer::AddContainerContents(TESContainer* apSource) {
#ifdef GAME
	ThisCall(0x481FD0, this, apSource);
#else
	ThisCall(0x4F4E30, this, apSource);
#endif
}

#ifdef GAME
// GAME - 0x4821A0
void TESContainer::AddContainerToReference(TESObjectREFR* apRef, bool abShowMessage) {
	ThisCall(0x4821A0, this, apRef, abShowMessage);
}
#endif

// GAME - 0x481E10
float TESContainer::GetContainerWeight(bool abHardcore) const {
#ifdef GAME
	return ThisCall<float>(0x481E10, this, abHardcore);
#else
	return ThisCall<float>(0x4F4590, this, abHardcore);
#endif
}

// GAME - 0x482A90
// GECK - 0x4F4720
uint32_t TESContainer::GetObjectCount(const TESBoundObject* apObject) const {
#ifdef GAME
	return ThisCall<uint32_t>(0x482A90, this, apObject);
#else
	return ThisCall<uint32_t>(0x4F4720, this, apObject);
#endif
}

// GAME - 0x481EB0
// GECK - 0x4F45F0
bool TESContainer::HasObject(const TESBoundObject* apObject) const {
#ifdef GAME
	return ThisCall<bool>(0x481EB0, this, apObject);
#else
	return ThisCall<bool>(0x4F45F0, this, apObject);
#endif
}

// GAME - 0x481F30
// GECK - 0x4F4100
bool TESContainer::ContainerCanHoldType(uint8_t aucFormType) {
#ifdef GAME
	return CdeclCall<bool>(0x481F30, aucFormType);
#else
	return CdeclCall<bool>(0x4F4100, aucFormType);
#endif
}

bool TESContainer::ContainerCanHoldForm(const TESForm* apForm) {
	if (!apForm)
		return false;

	if (apForm->IsReference()) {
		const TESObjectREFR* pRef = static_cast<const TESObjectREFR*>(apForm);
		return ContainerCanHoldForm(pRef->GetObjectReference());
	}
	else if (apForm->GetFormType() == FORM_TYPE::TESObjectLIGH) {
		const TESObjectLIGH* pLight = static_cast<const TESObjectLIGH*>(apForm);
		return pLight->GetCanCarry();
	}
	else {
		return ContainerCanHoldType(apForm->GetFormType());
	}
}
