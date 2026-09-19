#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameTasks.h"
#include "GameUI.h"
#include "GameProcess.h"
#include "CommandTable.h"

#ifdef GAME
extern bool (*Cmd_Update3D)(COMMAND_ARGS);
void __fastcall UpdateReference3D(TESObjectREFR* apReference) {
	double dResult;
	uint32_t uiOffset = 0;
	Cmd_Update3D(nullptr, nullptr, apReference, nullptr, nullptr, nullptr, &dResult, &uiOffset);
}

PlayerCharacter* PlayerCharacter::GetSingleton() {
	return *(PlayerCharacter**)0x11DEA3C;
}

NiNode* PlayerCharacter::Get3D(bool abFirstPerson) const {
	if (abFirstPerson)
		return playerNode;
	else if (pLoadedData)
		return reinterpret_cast<NiNode*>(pLoadedData->spSceneRoot.m_pObject);
	else
		return nullptr;
}

// GAME - 0x950B00
BipedAnim* PlayerCharacter::GetBiped(bool abFirstPerson) const {
	return abFirstPerson ? p1stPersonBipedAnim : pBipedAnim;
}

// GAME - 0x950A60
Animation* PlayerCharacter::GetAnimation(bool abFirstPerson) const {
	if (abFirstPerson)
		return p1stPersonAnimation;
	else if (pCurrentProcess)
		return pCurrentProcess->GetAnimation();
	else
		return nullptr;
}
#endif