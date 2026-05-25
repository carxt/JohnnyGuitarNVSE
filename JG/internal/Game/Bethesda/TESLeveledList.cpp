#include "TESLeveledList.hpp"

// GAME - 0x717E50
const BSSimpleList<LeveledObject*>* TESLeveledList::GetLeveledList() const {
	return &kLeveledObjects;
}

BSSimpleList<LeveledObject*>* TESLeveledList::GetLeveledList() {
	return &kLeveledObjects;
}

// GAME - 0x487A60
LeveledObject* TESLeveledList::AddLeveledObject(uint16_t ausLevel, uint16_t ausCount, TESForm* apForm, ContainerItemExtra* apExtra) {
	return ThisCall<LeveledObject*>(0x487A60, this, ausLevel, ausCount, apForm, apExtra);
}

// GAME - 0x4877E0
bool TESLeveledList::GetCalcAllBelow() const {
	return ucFlags.bCalcAllBelow;
}

bool TESLeveledList::GetUseAll() const {
	return ucFlags.bUseAll;
}

// GAME - 0x487F70
void TESLeveledList::CalculateCurrentFormList(uint16_t ausLevel, uint16_t ausCount, TESContainer* apOut, uint32_t aeAllBelowForce) {
	ThisCall(0x487F70, this, ausLevel, ausCount, apOut, aeAllBelowForce);
}

// GAME - 0x487D00
void TESLeveledList::CalculateCurrentForm(uint16_t ausLevel, TESForm*& apOutForm, uint16_t& asOutCount, ContainerItemExtra*& apOutExtra, bool abRecurse, uint32_t aeAllBelowForce) {
	ThisCall(0x487D00, this, ausLevel, &apOutForm, &asOutCount, &apOutExtra, abRecurse, aeAllBelowForce);
}

// GAME - 0x487BE0
TESLeveledList* TESLeveledList::GetFormAsLeveledList(const TESForm* apForm) {
	return CdeclCall<TESLeveledList*>(0x487BE0, apForm);
}

// GAME - 0x487BA0
LeveledObject::LeveledObject() {
	pForm		= nullptr;
	pItemExtra	= nullptr;
	usCount		= 1;
	usLevel		= 1;
}

// GAME - 0x487620
LeveledObject::~LeveledObject() {
	BSMemory::free(pItemExtra);
}
