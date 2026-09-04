#include "TESLeveledList.hpp"

// GAME - 0x717E50
const BSSimpleList<LeveledObject*>* TESLeveledList::GetLeveledList() const {
	return &kLeveledObjects;
}

BSSimpleList<LeveledObject*>* TESLeveledList::GetLeveledList() {
	return &kLeveledObjects;
}

// GAME - 0x487A60
// GECK - 0x5002E0
LeveledObject* TESLeveledList::AddLeveledObject(uint16_t ausLevel, uint16_t ausCount, TESForm* apForm, ContainerItemExtra* apExtra) {
#ifdef GAME
	return ThisCall<LeveledObject*>(0x487A60, this, ausLevel, ausCount, apForm, apExtra);
#else
	return ThisCall<LeveledObject*>(0x5002E0, this, ausLevel, ausCount, apForm, apExtra);
#endif
}

// GAME - 0x4877E0
bool TESLeveledList::GetCalcAllBelow() const {
	return ucFlags.bCalcAllBelow;
}

// GAME - 0x4878A0
bool TESLeveledList::GetUseAll() const {
	return ucFlags.bUseAll;
}

// GAME - 0x487F70
// GECK - 0x4FF6B0
void TESLeveledList::CalculateCurrentFormList(uint16_t ausLevel, uint16_t ausCount, TESContainer* apOut, uint32_t aeAllBelowForce) {
#ifdef GAME
	ThisCall(0x487F70, this, ausLevel, ausCount, apOut, aeAllBelowForce);
#else
	ThisCall(0x4FF6B0, this, ausLevel, ausCount, apOut, aeAllBelowForce);
#endif
}

// GAME - 0x487D00
// GECK - 0x4FF510
void TESLeveledList::CalculateCurrentForm(uint16_t ausLevel, TESForm*& apOutForm, uint16_t& asOutCount, ContainerItemExtra*& apOutExtra, bool abRecurse, uint32_t aeAllBelowForce) {
#ifdef GAME
	ThisCall(0x487D00, this, ausLevel, &apOutForm, &asOutCount, &apOutExtra, abRecurse, aeAllBelowForce);
#else
	ThisCall(0x4FF510, this, ausLevel, &apOutForm, &asOutCount, &apOutExtra, abRecurse, aeAllBelowForce);
#endif
}

// GAME - 0x487BE0
// GECK - 0x4FEFB0
TESLeveledList* TESLeveledList::GetFormAsLeveledList(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<TESLeveledList*>(0x487BE0, apForm);
#else
	return CdeclCall<TESLeveledList*>(0x4FEFB0, apForm);
#endif
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
