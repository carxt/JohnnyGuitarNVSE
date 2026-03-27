#include "TESContainer.hpp"

// GAME - 0x481610
TESContainer* TESContainer::Create(TESContainer* apThis) {
	return ThisCall<TESContainer*>(0x481610, apThis);
}

// GAME - 0x481680
void TESContainer::Destroy() {
	ThisCall(0x481680, this);
}

// GAME - 0x717E50
const BSSimpleList<ContainerObject*>* TESContainer::GetObjectList() const {
	return &kObjects;
}

// GAME - 0x717E50
BSSimpleList<ContainerObject*>* TESContainer::GetObjectList() {
	return &kObjects;
}

// GAME - 0x481FD0
void TESContainer::AddContainerContents(TESContainer* apSource) {
	ThisCall(0x481FD0, this, apSource);
}

// GAME - 0x4821A0
void TESContainer::AddContainerToReference(TESObjectREFR* apRef, bool abShowMessage) {
	ThisCall(0x4821A0, this, apRef, abShowMessage);
}

// GAME - 0x481E10
float TESContainer::GetContainerWeight(bool abHardcore) const {
	return ThisCall<bool>(0x481E10, this, abHardcore);
}

// GAME - 0x482A90
uint32_t TESContainer::GetObjectCount(TESBoundObject* apObject) {
	return ThisCall<uint32_t>(0x482A90, this, apObject);
}

// GAME - 0x481EB0
bool TESContainer::HasObject(TESBoundObject* apObject) const {
	return ThisCall<bool>(0x481EB0, this, apObject);
}

// GAME - 0x481F30
bool TESContainer::ContainerCanHoldType(uint32_t auiFormType) {
	return CdeclCall<bool>(0x481F30, auiFormType);
}