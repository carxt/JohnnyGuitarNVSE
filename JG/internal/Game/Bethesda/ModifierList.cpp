#include "ModifierList.hpp"

// GAME - 0x937760
Modifier* ModifierList::GetModifierItem(uint8_t aucActorValue) const {
	return ThisCall<Modifier*>(0x937760, this, aucActorValue);
}

// GAME - 0x9376E0
float ModifierList::GetModifier(uint8_t aucActorValue, bool& abFound) const {
	return ThisCall<float>(0x9376E0, this, aucActorValue, &abFound);
}

// GAME - 0x937730
float ModifierList::GetModifier(uint8_t aucActorValue) const {
	return ThisCall<float>(0x937730, this, aucActorValue);
}

// GAME - 0x9375E0
void ModifierList::SetModifier(uint8_t aucActorValue, float afValue) {
	ThisCall(0x9375E0, this, aucActorValue, afValue);
}

// GAME - 0x937480
void ModifierList::AdjustModifier(uint8_t aucActorValue, float afValue, ClampStyle aeClamp) {
	ThisCall(0x937480, this, aucActorValue, afValue, aeClamp);
}

// GAME - 0x937380
void ModifierList::AddModifier(Modifier* apModifier) {
	ThisCall(0x937380, this, apModifier);
}

// GAME - 0x937280
void ModifierList::AddFastModifier(uint8_t aucActorValue, Modifier* apModifier) {
	ThisCall(0x937280, this, aucActorValue, apModifier);
}

// GAME - 0x937400
void ModifierList::DeleteModifier(Modifier* apModifier) {
	ThisCall(0x937400, this, apModifier);
}

// GAME - 0x9370B0
void ModifierList::DeleteAllModifiers() {
	ThisCall(0x9370B0, this);
}

// GAME - 0x937810
float ModifierList::ModifyAndClamp(float afValue, float afDelta, ClampStyle aeClamp) {
	return CdeclCall<float>(0x937810, afValue, afDelta, aeClamp);
}
