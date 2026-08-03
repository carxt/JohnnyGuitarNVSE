#include "GameObjects.h"
#include "GameProcess.h"
#include "CommandTable.h"

PlayerCharacter* PlayerCharacter::GetSingleton() {
	return *(PlayerCharacter**)0x11DEA3C;
}

NiAVObject* PlayerCharacter::Get3D(bool abFirstPerson) const {
	return ThisCall<NiAVObject*>(0x950BB0, this, abFirstPerson);
}

// GAME - 0x950B00
BipedAnim* PlayerCharacter::GetBiped(bool abFirstPerson) const {
	return abFirstPerson ? p1stPersonBipedAnim : pBipedAnim;
}

// GAME - 0x950A60
Animation* PlayerCharacter::GetAnimation(bool abFirstPerson) const {
	return ThisCall<Animation*>(0x950A60, this, abFirstPerson);
}

extern bool (*Cmd_Update3D)(COMMAND_ARGS);
void __fastcall UpdateReference3D(TESObjectREFR* apReference) {
	double dResult;
	uint32_t uiOffset = 0;
	Cmd_Update3D(nullptr, nullptr, apReference, nullptr, nullptr, nullptr, dResult, uiOffset);
}