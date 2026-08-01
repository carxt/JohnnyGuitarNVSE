#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameTasks.h"
#include "GameUI.h"
#include "GameProcess.h"
#include "CommandTable.h"

#include "Bethesda/BSUtilities.hpp"
#if 0
TESForm* TESObjectREFR::GetBaseForm()
{
	TESBoundObject* baseform = nullptr;
	if (this->baseForm) {
		baseform = this->baseForm;
		if (baseform->GetCompileIndex() == 0xFF) {
			if (IS_TYPE(baseform, BGSPlaceableWater))
				return baseform->GetWaterType();

			ExtraLeveledCreature* pLevCrea = extraDataList.GetExtraData<ExtraLeveledCreature>();
			if (pLevCrea && pLevCrea->pOriginalBase)
				return pLevCrea->pOriginalBase;
		}
	}
	return baseform;
}
#endif

PlayerCharacter* PlayerCharacter::GetSingleton() {
	return *(PlayerCharacter**)0x11DEA3C;
}

NiAVObject* PlayerCharacter::Get3D(bool abFirstPerson) const {
	if (abFirstPerson)
		return playerNode;
	else if (pLoadedData)
		return pLoadedData->spSceneRoot;
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
	else if (GetCurrentAIProcess())
		return GetCurrentAIProcess()->GetAnimation();
	else
		return nullptr;
}

extern bool (*Cmd_Update3D)(COMMAND_ARGS);
void __fastcall UpdateReference3D(TESObjectREFR* apReference) {
	double dResult;
	uint32_t uiOffset = 0;
	Cmd_Update3D(nullptr, nullptr, apReference, nullptr, nullptr, nullptr, dResult, uiOffset);
}