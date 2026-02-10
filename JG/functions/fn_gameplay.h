#pragma once
#include "GameForms.h"
#include "ParamInfos.h"

#include "Bethesda/BSUtilities.hpp"

// Functions affecting gameplay
DEFINE_COMMAND_PLUGIN(ToggleLevelUpMenu, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(TogglePipBoy, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(Jump, , true, nullptr);
DEFINE_COMMAND_PLUGIN(StopVATSCam, , false, nullptr);
DEFINE_COMMAND_PLUGIN(SetCameraShake, , false, kParams_TwoFloats);
DEFINE_COMMAND_PLUGIN(ApplyWeaponPoison, , true, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(SetVelEx, , true, kParams_ThreeFloats);
DEFINE_COMMAND_PLUGIN(StopSoundAlt, , false, kParams_TwoForms_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(DisableMuzzleFlashLights, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(UnsetAV, , true, kParams_OneActorValue);
DEFINE_COMMAND_PLUGIN(UnforceAV, , true, kParams_OneActorValue);
DEFINE_COMMAND_PLUGIN(ToggleNthPipboyLight, , false, kParams_TwoInts);
DEFINE_COMMAND_PLUGIN(GetRunSpeed, , true, nullptr);
DEFINE_COMMAND_PLUGIN(DisableMenuArrowKeys, , false, nullptr);
DEFINE_COMMAND_PLUGIN(EnableMenuArrowKeys, , false, nullptr);
DEFINE_COMMAND_PLUGIN(HighlightBodyPartAlt, , true, kParams_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(DeactivateAllHighlightsAlt, , true, kParams_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(RemoveHighlightedRef, , true, nullptr);
DEFINE_COMMAND_PLUGIN(GetNearestCompassHostileDirection, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetNearestCompassHostile, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_ALT_PLUGIN(SetDisablePlayerControlsHUDVisibilityFlags, SetDPCHUDFlags, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(IsCompassHostile, , true, nullptr);
DEFINE_COMMAND_PLUGIN(ToggleCombatMusic, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(IsCombatMusicEnabled, , false, nullptr);
DEFINE_COMMAND_PLUGIN(IsHostilesNearby, , false, nullptr);
DEFINE_COMMAND_PLUGIN(ModNthTempEffectTimeLeft, , true, kParams_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetCalculatedSpread, , true, nullptr);
DEFINE_COMMAND_PLUGIN(SendStealingAlarm, , true, kParams_OneRef_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetCompassHostiles, , false, kParams_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(ToggleDisableSaves, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(SendTrespassAlarmAlt, , true, nullptr);
DEFINE_COMMAND_PLUGIN(IsCrimeOrEnemy, , true, nullptr);
DEFINE_CMD_ALT_COND_PLUGIN(GetLocationSpecificLoadScreensOnly, , , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetLocationName, , true, nullptr);
DEFINE_COMMAND_PLUGIN(GetPlayingEffectShaders, , true, nullptr);
DEFINE_COMMAND_PLUGIN(StopSoundLooping, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(AddNavmeshObstacle, , true, nullptr);
DEFINE_COMMAND_PLUGIN(RemoveNavmeshObstacle, , true, nullptr);
DEFINE_COMMAND_PLUGIN(GetLandTextureUnderFeet, , true, nullptr);
DEFINE_COMMAND_PLUGIN(GetMoonPhase, , false, nullptr);
DEFINE_COMMAND_PLUGIN(RewardKarmaAlt, , false, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetCameraShakeNoHUDShudder, CamShakeNHUD , , false, kParams_TwoFloats);
DEFINE_COMMAND_PLUGIN(GetTempIngestibleEffects, , false, nullptr);
DEFINE_COMMAND_PLUGIN(PlaySoundFade, , false, kParams_OneForm_OneFloat);
DEFINE_COMMAND_PLUGIN(GetPointInNavMesh, , false, kParams_ThreeFloats_OneInt_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(GetNearestNavMeshTriangle, , false, kParams_ThreeFloats_OneInt_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(HasHealthDamageEffect, , true, nullptr);
DEFINE_COMMAND_PLUGIN(SetAlwaysRun, , false, kParams_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetAutoMove, , false, kParams_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetPlayerMovementFlags, , false, kParams_OneInt);

DEFINE_COMMAND_PLUGIN(SetExtraAccuracyPenaltyMult, , false, kParams_OneFloat_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetExtraAccuracyPenaltyMult, , false, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(RemoveExtraAccuracyPenaltyMult, , false, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(SetCustomMapMarker, , false, kParams_ThreeFloats);
DEFINE_COMMAND_PLUGIN(ClearCustomMapMarker, , false, nullptr);
DEFINE_COMMAND_PLUGIN(EjectCasing, , false, kParams_EjectCasing);
DEFINE_COMMAND_PLUGIN(SetHUDShudderPower, , false, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(GetHUDShudderPower, , false, nullptr);
DEFINE_COMMAND_ALT_PLUGIN(SetMediaLocationControllerOverride, SetMLCOverride, , false, kParams_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(ClearMediaLocationControllerOverride, ClearMLCOverride, , false, nullptr);
DEFINE_COMMAND_ALT_PLUGIN(GetCasinoWinnings, , , false, kParams_OneCasino);
DEFINE_COMMAND_ALT_PLUGIN(SetCasinoWinnings, , , false, kParams_OneCasinoOneInt);
DEFINE_COMMAND_PLUGIN(GetCasinoDeckTexture, , false, kParams_OneCasinoOneInt);
DEFINE_COMMAND_PLUGIN(SetCasinoDeckTexture, , false, kParams_OneCasinoOneIntOneString);
DEFINE_COMMAND_PLUGIN(GetCasinoChip, , false, kParams_OneCasino);
DEFINE_COMMAND_PLUGIN(SetCasinoChip, , false, kParams_OneCasinoOneForm);
DEFINE_COMMAND_PLUGIN(PlayHolotape, , false, kParams_OneForm_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(StopHolotape, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(PathToRef, , true, kParams_OneRefOneFloat);
DEFINE_COMMAND_PLUGIN(GetGrenadeHoldTime, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetWeaponsForMod, , false, kParams_OneObjectID);
DEFINE_CMD_ALT_COND_PLUGIN(IsInDialogueWithPlayer, , "", true, nullptr);

void(__cdecl* HandleActorValueChange)(ActorValueOwner* avOwner, int avCode, float oldVal, float newVal, ActorValueOwner* avOwner2) =
(void(__cdecl*)(ActorValueOwner*, int, float, float, ActorValueOwner*))0x66EE50;
bool(*Cmd_HighLightBodyPart)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB570;
bool(*Cmd_DeactivateAllHighlights)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB6C0;
void(__cdecl* HUDMainMenu_UpdateVisibilityState)(signed int) = (void(__cdecl*)(signed int))(0x771700);

#define NUM_ARGS *((uint8_t*)scriptData + *opcodeOffsetPtr)

std::unordered_map<TESForm*, std::pair<float, float>> tempEffectMap;

bool Cmd_StopHolotape_Execute(COMMAND_ARGS)
{
	*result = 0;
	int playStopSound = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &playStopSound);
	noHolotapeStopSound = playStopSound == 0;
	MapMenu* mapMenu = MapMenu::GetSingleton();
	mapMenu->StopHolotape();
	*result = 1;
	return true;

}
bool Cmd_PlayHolotape_Execute(COMMAND_ARGS)
{
	*result = 0;
	BGSNote* note = nullptr;
	int playStartStopSound = 1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &playStartStopSound) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kVoice || note->type == BGSNote::kSound)
	{
		MapMenu* mapMenu = MapMenu::GetSingleton();
		mapMenu->PlayHolotape(note, playStartStopSound > 0);
		*result = 1;
	}
	return true;

}

bool __cdecl Cmd_SetCasinoWinnings_Execute(COMMAND_ARGS)
{
	TESCasino* casino = nullptr;
	int32_t earnings;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &casino, &earnings) && casino && IS_TYPE(casino, TESCasino))
	{

		auto casinoRefId = casino->refID;
		auto iter = PlayerCharacter::GetSingleton()->casinoDataList->Head();
		if (iter) {
			do
			{
				if (auto casinoData = iter->data)
				{
					if (casinoData->casinoRefID == casinoRefId)
					{
						casinoData->earnings = earnings;
						return true;
					}
				}
			} while (iter = iter->next);
		}

		auto casinoStats = BSMemory::malloc<CasinoStats>();
		casinoStats->earningStage = 0;
		casinoStats->earnings = earnings;
		casinoStats->casinoRefID = casinoRefId;
		PlayerCharacter::GetSingleton()->casinoDataList->Insert(casinoStats);
	}

	return true;
}

bool __cdecl Cmd_GetCasinoWinnings_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESCasino* casino = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &casino) && casino && IS_TYPE(casino, TESCasino))
	{
		auto casinoRefId = casino->refID;
		auto iter = PlayerCharacter::GetSingleton()->casinoDataList->Head();
		if (!iter) return true;
		do
		{
			if (auto casinoData = iter->data)
			{
				if (casinoData->casinoRefID == casinoRefId)
				{
					*result = casinoData->earnings;
					break;
				}
			}
		} while (iter = iter->next);
	}

	return true;
}

bool Cmd_GetCasinoDeckTexture_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESCasino* casino = nullptr;
	int32_t deckIndex;
	const char* resStr = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &casino, &deckIndex) && casino && IS_TYPE(casino, TESCasino) && deckIndex >= 0 && deckIndex <= 3)
	{
		resStr = casino->blackjackDeck[deckIndex].ddsPath.pString;
		if (IsConsoleMode())
			Console_Print("GetCasinoDeckTexture >> %s", resStr);
		g_strInterface->Assign(PASS_COMMAND_ARGS, resStr);
	}
	return true;
}

bool Cmd_SetCasinoDeckTexture_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESCasino* casino = nullptr;
	int32_t deckIndex;
	char newPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &casino, &deckIndex, &newPath) && casino && IS_TYPE(casino, TESCasino) && newPath && deckIndex >= 0 && deckIndex <= 3)
	{
		casino->blackjackDeck[deckIndex].ddsPath.Set(newPath);
		*result = 1;
	}
	return true;
}

bool Cmd_GetCasinoChip_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESCasino* casino = nullptr;
	TESForm* chipForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &casino) && casino)
	{
		chipForm = TESForm::GetFormByNumericID(casino->currencyRefID);
		*(uint32_t*)result = chipForm->refID;
	}
	return true;
}

bool Cmd_SetCasinoChip_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESCasino* casino = nullptr;
	TESForm* chip = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &casino, &chip) && casino && IS_TYPE(casino, TESCasino) && chip && IS_TYPE(chip, TESCasinoChips))
	{
		casino->currencyRefID = chip->refID;
		*result = 1;
	}
	return true;
}

bool Cmd_ClearMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	mlcOverridden = false;
	mlcOverride = nullptr;
	*result = 1;

	return true;
}

bool Cmd_SetMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaLocationController* ctrl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &ctrl) && ctrl && IS_TYPE(ctrl, MediaLocationController)) {
		mlcOverridden = true;
		mlcOverride = ctrl;
		*result = 1;
	}
	return true;
}

bool Cmd_GetHUDShudderPower_Execute(COMMAND_ARGS) {
	*result = 0;
	uint8_t modId = scriptObj->GetModIndex();
	if (modId < 0xFF && shakeRequests.find(modId) != shakeRequests.end()) {
		*result = shakeRequests[modId];
	}
	return true;
}

bool Cmd_SetHUDShudderPower_Execute(COMMAND_ARGS) {
	*result = 0;
	float power = -1.f;
	uint8_t modId = scriptObj->GetModIndex();
	if (modId < 0xFF && ExtractArgsEx(EXTRACT_ARGS_EX, &power)) {
		if (power == 0.0f) {
			shakeRequests.erase(modId);
		}
		else {
			shakeRequests[modId] = power;
		}
		*result = 1;
	}
	return true;
}


bool Cmd_ClearCustomMapMarker_Execute(COMMAND_ARGS) {
	*result = 0;
	ThisCall(0x952F90, PlayerCharacter::GetSingleton());
	*result = 1;
	return true;
}

bool Cmd_SetCustomMapMarker_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 pos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pos.x, &pos.y, &pos.z)) {
		TESForm* cellOrWorld = nullptr;
		if (PlayerCharacter::GetSingleton()->parentCell && ((PlayerCharacter::GetSingleton()->parentCell->flags & 1) != 0)) {
			cellOrWorld = PlayerCharacter::GetSingleton()->parentCell;
		}
		else {
			TESObjectCELL* cell = PlayerCharacter::GetSingleton()->parentCell;
			if (!cell) cell = PlayerCharacter::GetSingleton()->childCell.GetPersistentCell();
			if (cell && (cell->cellFlags & 1) == 0) cellOrWorld = cell->worldSpace;
		}
		if (cellOrWorld) {
			ThisCall(0x952E60, PlayerCharacter::GetSingleton(), pos.x, pos.y, pos.z, cellOrWorld);
			*result = 1;
		}
	}
	return true;
}
bool Cmd_SetPlayerMovementFlags_Execute(COMMAND_ARGS)
{
	uint32_t flags;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &flags)) {
		PlayerCharacter::GetSingleton()->actorMover->Unk_03(flags);
		*result = 1;
	}
	return true;
}

bool Cmd_SetAlwaysRun_Execute(COMMAND_ARGS) {
	*result = 0;
	int alwaysRun = -1;
	int updateMovementFlags = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &alwaysRun, &updateMovementFlags);
	if (alwaysRun > -1) {
		bool bAlwaysRun = (alwaysRun > 0);
		PlayerCharacter::GetSingleton()->alwaysRun = bAlwaysRun;
		if (updateMovementFlags) {
			PlayerMover* playerMover = (PlayerMover*)PlayerCharacter::GetSingleton()->actorMover;
			uint32_t flags = playerMover->pcMovementFlags;
			if (bAlwaysRun) {
				flags |= 0x200;
			}
			else {
				flags &= ~0x200;
			}
			PlayerCharacter::GetSingleton()->actorMover->Unk_03(flags);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_SetAutoMove_Execute(COMMAND_ARGS) {
	*result = 0;
	int autoMove = -1;
	ExtractArgsEx(EXTRACT_ARGS_EX, &autoMove);
	if (autoMove > -1) {
		PlayerCharacter::GetSingleton()->autoMove = (autoMove > 0);
		*result = 1;
	}
	return true;
}

bool Cmd_HasHealthDamageEffect_Execute(COMMAND_ARGS) {
	Actor* actor = (Actor*)thisObj;
	*result = ThisCall<bool>(0x822E00, &actor->magicTarget);
	return true;
}


void GetClosestNavMeshTriangle(const TESObjectCELL* apCell, const NiPoint3& arPointToTest, bool checkDisabled, float zLimit, NiPoint4& arOut) {
	NavMeshArray* pNavMeshArray = apCell->pNavMeshes;
	if (!pNavMeshArray)
		return;

	for (uint32_t i = 0; i < pNavMeshArray->GetSize(); i++) {

		NavMeshPtr spNavMesh = pNavMeshArray->GetAt(i);
		if (!spNavMesh)
			continue;

		NavMeshInfo* pInfo = spNavMesh->pNavMeshInfo;
		if (!pInfo)
			continue;

		for (uint32_t j = 0; j < spNavMesh->kTriangles.GetSize(); j++) {
			NavMeshTriangle* pNavMeshTriangle = spNavMesh->kTriangles.GetAt(j);
			if (!pNavMeshTriangle)
				continue;

			if (checkDisabled && ((pNavMeshTriangle->uiFlags & NavMeshTriangle::DISABLED) != 0))
				continue;

			// Get triangle vertices
			NiPoint3 kVerts[3];
			for (uint32_t k = 0; k < 3; k++) {
				NiPoint3* pVertex = spNavMesh->kVertices.GetAt(pNavMeshTriangle->sVertices[k]);
				if (!pVertex)
					continue;

				kVerts[k] = *pVertex;
			}


			NiPoint3 kTriCenter = NiPoint3::GetTriangleCenter(kVerts[0], kVerts[1], kVerts[2]);

			if (zLimit > 0 && fabs(kTriCenter.z - arPointToTest.z) > zLimit) continue;

			// Get distance to triangle center
			float fDist = arPointToTest.Distance(kTriCenter);

			if (fDist < arOut.w) {
				arOut.w = fDist;
				arOut.x = kTriCenter.x;
				arOut.y = kTriCenter.y;
				arOut.z = kTriCenter.z;
			}
		}
	}
}
bool GetPointNavMesh(const TESObjectCELL* apCell, const NiPoint3& arPointToTest, bool checkDisabled, float zLimit, NiPoint4& arOut) {
	NavMeshArray* pNavMeshArray = apCell->pNavMeshes;
	if (!pNavMeshArray)
		return false;

	for (uint32_t i = 0; i < pNavMeshArray->GetSize(); i++) {

		NavMeshPtr spNavMesh = pNavMeshArray->GetAt(i);
		if (!spNavMesh)
			continue;

		NavMeshInfo* pInfo = spNavMesh->pNavMeshInfo;
		if (!pInfo)
			continue;

		for (uint32_t j = 0; j < spNavMesh->kTriangles.GetSize(); j++) {
			NavMeshTriangle* pNavMeshTriangle = spNavMesh->kTriangles.GetAt(j);
			if (!pNavMeshTriangle)
				continue;
			if (checkDisabled && (pNavMeshTriangle->uiFlags & NavMeshTriangle::DISABLED) != 0)
				continue;

			// Get triangle vertices
			NiPoint3 kVerts[3];
			for (uint32_t k = 0; k < 3; k++) {
				NiPoint3* pVertex = spNavMesh->kVertices.GetAt(pNavMeshTriangle->sVertices[k]);
				if (!pVertex)
					continue;

				kVerts[k] = *pVertex;
			}


			// Check if player is inside the triangle
			if (NiPoint3::PointInTriangle(arPointToTest, kVerts[0], kVerts[1], kVerts[2])) {
				// Get triangle center
				NiPoint3 kTriCenter = NiPoint3::GetTriangleCenter(kVerts[0], kVerts[1], kVerts[2]);

				if (zLimit > 0 && fabs(kTriCenter.z - arPointToTest.z) > zLimit) continue;


				// Get distance to triangle center
				float fDist = arPointToTest.Distance(kTriCenter);

				arOut.x = kTriCenter.x;
				arOut.y = kTriCenter.y;
				arOut.z = kTriCenter.z;
				arOut.w = fDist;

				return true;
			}
		}
	}
	return false;
}






bool Cmd_SetExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {

	*result = 0;
	float mul = 1.0f;
	TESForm* a_form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mul, &a_form) && a_form) {
		if (fabs(mul) < FLT_EPSILON) { mul = FLT_EPSILON + DBL_EPSILON; }
		switch (a_form->typeID) {
		case FORM_TYPE::TESNPC:
		case FORM_TYPE::TESCreature:
			NPCAccuracy::tables.ACTBAS[a_form->refID] = mul;
			break;
		case FORM_TYPE::TESCombatStyle:
			NPCAccuracy::tables.CSTY[a_form->refID] = mul;
			break;
		case FORM_TYPE::TESFaction:
			NPCAccuracy::tables.FACT[a_form->refID] = mul;
			break;

		}
	}
	else if (thisObj) {
		NPCAccuracy::tables.ACTREF[thisObj->refID] = mul;

	}
	return true;


}



bool Cmd_GetExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {

	*result = 1;
	TESForm* a_form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &a_form) && a_form) {
		switch (a_form->typeID) {
		case FORM_TYPE::TESNPC:
		case FORM_TYPE::TESCreature:
			if (auto it = NPCAccuracy::tables.ACTBAS.find(a_form->refID); it != NPCAccuracy::tables.ACTBAS.end()) {
				*result = it->second;
			}
			break;
		case FORM_TYPE::TESCombatStyle:
			if (auto it = NPCAccuracy::tables.CSTY.find(a_form->refID); it != NPCAccuracy::tables.CSTY.end()) {
				*result = it->second;
			}
			break;
		case FORM_TYPE::TESFaction:
			if (auto it = NPCAccuracy::tables.FACT.find(a_form->refID); it != NPCAccuracy::tables.FACT.end()) {
				*result = it->second;
			}
			break;

		}
	}
	else if (thisObj) {
		if (auto it = NPCAccuracy::tables.ACTREF.find(thisObj->refID); it != NPCAccuracy::tables.ACTREF.end()) {
			*result = it->second;
		}
	}
	return true;


}










bool Cmd_RemoveExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {

	*result = 0;
	TESForm* a_form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &a_form) && a_form) {
		switch (a_form->typeID) {
		case FORM_TYPE::TESNPC:
		case FORM_TYPE::TESCreature:
			NPCAccuracy::tables.ACTBAS.erase(a_form->refID);
			break;
		case FORM_TYPE::TESCombatStyle:
			NPCAccuracy::tables.CSTY.erase(a_form->refID);
			break;
		case FORM_TYPE::TESFaction:
			NPCAccuracy::tables.FACT.erase(a_form->refID);
			break;

		}
	}
	else if (thisObj) {
		NPCAccuracy::tables.ACTREF.erase(thisObj->refID);

	}
	return true;


}







bool Cmd_GetNearestNavMeshTriangle_Execute(COMMAND_ARGS) {
	*result = 0;

	NiPoint3 kPointToTest;
	uint32_t checkDisabled = 0;
	float zLimit = 0;
	NVSEArrayVar* pointArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &kPointToTest.x, &kPointToTest.y, &kPointToTest.z, &checkDisabled, &zLimit)) return true;

	NiPoint4 kResult = { FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };

	TESObjectCELL* pInterior = TES::GetSingleton()->currentInterior;
	uint32_t uiGridSize = (*(Setting*)0x11C63CC).data.uint;

	if (pInterior) {
		GetClosestNavMeshTriangle(pInterior, kPointToTest, (checkDisabled > 0), zLimit, kResult);
	}
	else {
		for (uint32_t x = 0; x < uiGridSize; x++) {
			for (uint32_t y = 0; y < uiGridSize; y++) {
				TESObjectCELL* pCell = TES::GetSingleton()->gridCellArray->GetCell(x, y)->pCell;
				if (!pCell)
					continue;

				GetClosestNavMeshTriangle(pCell, kPointToTest, (checkDisabled > 0), zLimit, kResult);
			}
		}
	}
	g_arrInterface->AppendElements(pointArr, kResult.x, kResult.y, kResult.z, kResult.w);

	if (IsConsoleMode()) {
		Console_Print("GetClosestNavMeshTriangle >> Point found at (%f, %f, %f) with distance %f", kResult.x, kResult.y, kResult.z, kResult.w);
	}

	g_arrInterface->AssignCommandResult(pointArr, result);

	return true;
}

bool Cmd_GetPointInNavMesh_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint4 kResult;
	TESObjectCELL* pInterior = TES::GetSingleton()->currentInterior;

	uint32_t uiGridSize = (*(Setting*)0x11C63CC).data.uint;

	NiPoint3 kPointToTest;
	uint32_t checkDisabled = 0;
	float zLimit = 0;
	NVSEArrayVar* pointArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &kPointToTest.x, &kPointToTest.y, &kPointToTest.z, &checkDisabled, &zLimit))	return true;

	bool bResult = false;
	if (pInterior) {
		bResult = GetPointNavMesh(pInterior, kPointToTest, (checkDisabled > 0), zLimit, kResult);
	}
	else {
		for (uint32_t x = 0; x < uiGridSize && !bResult; x++) {
			for (uint32_t y = 0; y < uiGridSize && !bResult; y++) {
				TESObjectCELL* pCell = TES::GetSingleton()->gridCellArray->GetCell(x, y)->pCell;
				if (!pCell)
					continue;

				bResult = GetPointNavMesh(pCell, kPointToTest, (checkDisabled > 0), zLimit, kResult);
			}
		}
	}

	if (bResult) {
		g_arrInterface->AppendElements(pointArr, kResult.x, kResult.y, kResult.z, kResult.w);
		if (IsConsoleMode()) {
			Console_Print("GetPointInNavMesh >> Point found at (%f, %f, %f) with distance %f", kResult.x, kResult.y, kResult.z, kResult.w);
		}
	}
	else if (IsConsoleMode()) {
			Console_Print("GetPointInNavMesh >> Point not found.");

	}

	g_arrInterface->AssignCommandResult(pointArr, result);
	return bResult;
}



bool __fastcall ValidTempEffect(EffectItem* effectItem) {
	if (!effectItem || (effectItem->duration <= 0) || !effectItem->setting) return false;
	uint8_t archtype = effectItem->setting->archtype;
	return !archtype || ((archtype == 1) && (effectItem->setting->effectFlags & 0x2000)) || ((archtype > 10) && (archtype < 14)) || (archtype == 24) || (archtype > 33);
}


bool Cmd_PlaySoundFade_Execute(COMMAND_ARGS) {
	*result = 0;
	float fTime = 0;
	TESSound* sound;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sound, &fTime) && sound && IS_TYPE(sound, TESSound)) {
		TESObjectREFR* ref = thisObj;
		if (ref == nullptr) {
			ref = (TESObjectREFR*)PlayerCharacter::GetSingleton();
		}
		if (ref->GetRefNiNode()) {
			uint32_t uiFlags = BSAudioManager::kAudioFlags_3D | BSAudioManager::kAudioFlags_100;
			BSSoundHandle handle = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(sound->refID, uiFlags);
			handle.SetPosition(*ref->GetPos());
			handle.SetObjectToFollow(ref->GetRefNiNode());
			uint32_t time = fTime * 1000.0;
			handle.FadeInPlay(time);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetTempIngestibleEffects_Execute(COMMAND_ARGS) {
	*result = 0;
	NVSEArrayVar* effArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	tempEffectMap.clear();
	if (auto iter = ((Actor*)PlayerCharacter::GetSingleton())->magicTarget.GetEffectList()->Head())
	{
		do
		{
			if (ActiveEffect* activeEff = iter->data; activeEff && activeEff->bActive && !activeEff->bTerminated &&
				activeEff->magicItem && ValidTempEffect(activeEff->effectItem))
				if (TESForm* form = DYNAMIC_CAST(activeEff->magicItem, MagicItem, TESForm))
				{
					if (form->typeID == FORM_TYPE::AlchemyItem) {
						float timeLeft = activeEff->duration - activeEff->timeElapsed;
						auto it = tempEffectMap.find(form);
						if (it != tempEffectMap.end() && it->second.second < activeEff->duration) {
							it->second.first = timeLeft;
							it->second.second = activeEff->duration;
						}
						else {
							tempEffectMap.insert({form, {timeLeft, activeEff->duration}});
						}
					}
				}
		} while (iter = iter->next);

	}
	if (!tempEffectMap.empty()) {
		for (auto& effect : tempEffectMap) {
			NVSEArrayVar* effArrInner = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
			g_arrInterface->AppendElements(effArrInner, effect.first, effect.second.first, effect.second.second);
			g_arrInterface->AppendElement(effArr, NVSEArrayElement(effArrInner));
		}
		tempEffectMap.clear();
	}
	g_arrInterface->AssignCommandResult(effArr, result);
	return true;
}


bool Cmd_SetCameraShakeNoHUDShudder_Execute(COMMAND_ARGS) {
	float shakeMult, time = 0.f;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shakeMult, &time)) {
		hk_CameraShakeHook::camShakeMinAlt = shakeMult;
		hk_CameraShakeHook::camShakeTimeAlt = time;
		*result = 1;
	}
	return true;
}

bool Cmd_RewardKarmaAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	int delta = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &delta);
	int karmaBefore = PlayerCharacter::GetSingleton()->avOwner.GetActorValueI(kAVCode_Karma);
	int ikarmaMax = (*(Setting*)0x11CD644).data.i;
	int iKarmaMin = (*(Setting*)0x11CDD6C).data.i;
	if (delta >= 0 && ((delta + karmaBefore) > ikarmaMax)) {
		delta = ikarmaMax - karmaBefore;
	}
	else if (delta < 0 && ((delta + karmaBefore) < iKarmaMin)) {
		delta = iKarmaMin - karmaBefore;
	}
	if (delta != 0) {
		PlayerCharacter::GetSingleton()->ModActorValue(kAVCode_Karma, delta, 0);
		*result = 1;
	}
	return true;
}
bool Cmd_GetMoonPhase_Execute(COMMAND_ARGS) {
	*result = *(int*)0x11CCA80;
	return true;
}
bool Cmd_GetLandTextureUnderFeet_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = thisObj->GetParentCell();
	if (!cell || cell->IsInterior()) return true;
	NiPoint3* pos = thisObj->GetPos();
	COORD_DATA coordData;
	TESObjectLAND* landscape = ThisCall<TESObjectLAND*>(0x546FB0, cell); // TESObjectCELL::GetLand
	if (!landscape) return true;
	ThisCall(0x53B550, landscape, &coordData, pos, 1); // TESObjectLAND::GetCoordData
	TESLandTexture* txt = ThisCall<TESLandTexture*>(0x53A630, landscape, coordData.iBlock, coordData.iVertidx); // TESObjectLAND::GetMainTexture
	if (txt) *(uint32_t*)result = txt->refID;
	return true;
}

bool Cmd_RemoveNavmeshObstacle_Execute(COMMAND_ARGS) {
	*result = 0;
	NavMeshObstacleManager* g_nomgr = ThisCall<NavMeshObstacleManager*>(0x6C0720, nullptr);
	ThisCall(0x6C0C80, g_nomgr, thisObj);
	*result = 1;
	return true;
}

bool Cmd_AddNavmeshObstacle_Execute(COMMAND_ARGS) {
	*result = 0;
	NavMeshObstacleManager* g_nomgr = ThisCall<NavMeshObstacleManager*>(0x6C0720, nullptr);
	ThisCall(0x6C0C30, g_nomgr, thisObj);
	*result = 1;
	return true;
}
bool Cmd_StopSoundLooping_Execute(COMMAND_ARGS) {
	*result = 0;
	TESSound* sound = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sound) && sound && IS_TYPE(sound, TESSound)) {
		CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
		BSGameSound* gameSound;
		for (auto sndIter = BSAudioManager::Get()->playingSounds.Begin(); !sndIter.End(); ++sndIter) {
			gameSound = sndIter.Get();
			if (!gameSound || (gameSound->sourceSound != sound))
				continue;

			BSSoundHandle handle;
			handle.uiSoundID = gameSound->mapKey;
			handle.Stop();
			*result = 1;
		}
	}

	return true;
}

bool Cmd_GetPlayingEffectShaders_Execute(COMMAND_ARGS) {
	*result = 0;
	ListNode<BSTempEffect>* iter = ProcessManager::GetSingleton()->tempEffects.Head();
	MagicShaderHitEffect* effect;
	NVSEArrayVar* effArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	do {
		effect = (MagicShaderHitEffect*)iter->data;
		if (effect && IS_TYPE(effect, MagicShaderHitEffect) && effect->flags != 1 && effect->target && effect->target->refID == thisObj->refID) {
			g_arrInterface->AppendElement(effArr, NVSEArrayElement(effect->effectShader));
		}
	} while (iter = iter->next);

	g_arrInterface->AssignCommandResult(effArr, result);
	return true;
}

TESWorldSpace* GetWorldspace(TESObjectREFR* ref) {
	TESObjectCELL* cell = ref->parentCell;
	if (!cell) cell = ref->childCell.GetPersistentCell();
	if (cell && (cell->cellFlags & 1) == 0) return cell->worldSpace;
	return nullptr;
}

bool Cmd_GetLocationName_Execute(COMMAND_ARGS) {
	*result = 0;
	char locationName[256] = {};
	if (thisObj->parentCell && (thisObj->parentCell->cellFlags & 1) != 0) {
		strcpy_s(locationName, thisObj->parentCell->fullName.name.c_str());
	}
	else {
		TESWorldSpace* wspc = GetWorldspace(thisObj);
		if (wspc) {
			BSString str;
			NiPoint3* pos = thisObj->GetPos();
			wspc->GetMapNameForLocation(str, pos->x, pos->y, pos->z);
			strcpy_s(locationName, str.c_str());
		}
	}
	g_strInterface->Assign(PASS_COMMAND_ARGS, locationName);
	return true;
}

bool Cmd_GetLocationSpecificLoadScreensOnly_Execute(COMMAND_ARGS) {
	*result = (float)(*(uint8_t*)0x11CABB8);
	return true;
}

bool Cmd_GetLocationSpecificLoadScreensOnly_Eval(COMMAND_ARGS_EVAL) {
	*result = (float)(*(uint8_t*)0x11CABB8);
	return true;
}

bool IsCombatTarget(Actor* source, Actor* toSearch) {
	if (source->isInCombat && source->combatTargets) {
		Actor** actorsArr = source->combatTargets->pBuffer;
		uint32_t count = source->combatTargets->uiSize;
		if (!actorsArr) return false;
		for (; count; count--, actorsArr++) {
			if (*actorsArr == toSearch) return true;
		}
	}
	return false;
}

bool IsHostileCompassTarget(Actor* toSearch) {
	auto iter = PlayerCharacter::GetSingleton()->compassTargets->Begin();
	for (; !iter.End(); ++iter) {
		PlayerCharacter::CompassTarget* target = iter.Get();
		if (target->isHostile && target->target == toSearch) return true;
	}
	return false;
}
bool Cmd_IsCrimeOrEnemy_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* actor = (Actor*)thisObj;
	if (ThisCall<bool>(0x579690, thisObj) && (!thisObj->IsActor() || !actor->isTeammate) ||
		thisObj->IsActor() && (IsCombatTarget(actor, PlayerCharacter::GetSingleton()) || IsHostileCompassTarget(actor))) {
		*result = 1;
	}
	if (IsConsoleMode()) Console_Print("IsCrimeOrEnemy >> %.f", *result);
	return true;
}

bool Cmd_SendTrespassAlarmAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	ExtraOwnership* xOwn = ThisCall<ExtraOwnership*>(0x567790, thisObj); // TESObjectREFR::ResolveOwnership
	if (xOwn) {
		ThisCall(0x8C0EC0, PlayerCharacter::GetSingleton(), thisObj, xOwn, 0xFFFFFFFF); //TESObjectREFR::HandleMinorCrime
		*result = 1;
	}
	return true;
}
bool Cmd_GetCompassHostiles_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t skipInvisible = 0;

	//If player has ImprovedDetection perk effect, then they'll see invisible actors in compass.
	uint32_t accountForImprovedDetection = 0;

	ExtractArgsEx(EXTRACT_ARGS_EX, &skipInvisible, &accountForImprovedDetection);

	bool hasImprovedDetection = false;
	if (accountForImprovedDetection) {
		float hasPerk = 0.0; //copying code at 0x77A0C4
		ApplyPerkModifiers(kPerkEntry_HasImprovedDetection, PlayerCharacter::GetSingleton(), &hasPerk);
		if (hasPerk > 0.0)
			hasImprovedDetection = true;
	}

	NVSEArrayVar* hostileArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	auto iter = PlayerCharacter::GetSingleton()->compassTargets->Begin();
	for (; !iter.End(); ++iter) {
		PlayerCharacter::CompassTarget* target = iter.Get();
		if (target->isHostile) {
			if (skipInvisible > 0 && !hasImprovedDetection && (target->target->avOwner.GetActorValueI(kAVCode_Invisibility) > 0
				|| target->target->avOwner.GetActorValueI(kAVCode_Chameleon) > 0)) {
				continue;
			}
			g_arrInterface->AppendElement(hostileArr, NVSEArrayElement(target->target));
		}
	}
	g_arrInterface->AssignCommandResult(hostileArr, result);
	return true;
}

bool Cmd_SendStealingAlarm_Execute(COMMAND_ARGS) {
	TESObjectREFR* container;
	int checkItems = 0;
	*result = 0;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &container, &checkItems) && container) {
		if (checkItems) {
			TESForm* containerOwner = ThisCall<TESForm*>(0x567790, container); // TESObjectREFR::ResolveOwnership
			if (!containerOwner) return true;
			ExtraContainerChanges* xChanges = (ExtraContainerChanges*)((Actor*)thisObj)->extraDataList.GetByType(kExtraData_ContainerChanges);
			if (!xChanges || !xChanges->data || !xChanges->data->objList)
				return true;
			ListNode<ContChangesEntry>* contChangesIter = xChanges->data->objList->Head();
			ContChangesEntry* entry;
			do {
				if (!(entry = contChangesIter->data) || !entry->extendData || !entry->type) continue;
				ListNode<ExtraDataList>* xdlIter = entry->extendData->Head();
				ExtraDataList* xData;
				do {
					xData = xdlIter->data;
					if (xData && xData->HasType(kExtraData_Ownership)) {
						ExtraOwnership* xOwn = (ExtraOwnership*)xData->GetByType(kExtraData_Ownership);
						if (xOwn->owner) {
							if (xOwn->owner->refID == containerOwner->refID) {
								ThisCall(0x8BFA40, thisObj, container, nullptr, nullptr, 1, containerOwner); // Actor::HandleStealing
								*result = 1;
								return true;
							}
						}
					}
				} while (xdlIter = xdlIter->next);
			} while (contChangesIter = contChangesIter->next);
		}
		else {
			TESForm* owner = ThisCall<TESForm*>(0x567790, container); // TESObjectREFR::ResolveOwnership
			ThisCall(0x8BFA40, thisObj, container, nullptr, nullptr, 1, owner); // Actor::HandleStealing,
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetCalculatedSpread_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* actor = static_cast<Actor*>(thisObj);
	ContChangesEntry* weapInfo = actor->baseProcess->GetWeaponInfo();
	if (weapInfo && weapInfo->type) {
		bool hasDecreaseSpreadEffect = ThisCall<bool>(0x4BDA70, weapInfo, 3);
		double minSpread = ThisCall<double>(0x524B80, weapInfo->type, hasDecreaseSpreadEffect);
		double weapSpread = ThisCall<float>(0x524BE0, weapInfo->type, hasDecreaseSpreadEffect);
		double spread = ThisCall<double>(0x8B0DD0, actor, 1);

		float totalSpread = (weapSpread * spread + minSpread) * 0.01745329238474369;

		TESAmmo* eqAmmo = ThisCall<TESAmmo*>(0x525980, weapInfo->type, static_cast<MobileObject*>(actor));
		totalSpread = CdeclCall<float>(0x59A030, 3, (eqAmmo ? &eqAmmo->effectList : nullptr), totalSpread);

		double spreadPenalty = ThisCall<double>(0x8B0DD0, actor, 2);

		Setting* fNPCMaxGunWobbleAngle;
		GameSettingCollection::GetSingleton()->GetGameSetting("fNPCMaxGunWobbleAngle", &fNPCMaxGunWobbleAngle);

		totalSpread += spreadPenalty * fNPCMaxGunWobbleAngle->data.f * 0.01745329238474369;

		float noIdea = ThisCall<HighProcess*>(0x8D8520, actor)->angle1D0;
		totalSpread = totalSpread + noIdea;

		bool hasSplitBeamEffect = ThisCall<bool>(0x4BDA70, weapInfo, 0xC);
		if (hasSplitBeamEffect) {
			totalSpread *= ThisCall<float>(0x4BCF60, weapInfo->type, 0xC, 1);
		}
		*result = totalSpread;
	}
	if (IsConsoleMode()) Console_Print("GetCalculatedSpread >> %f", *result);
	return true;
}



bool Cmd_ModNthTempEffectTimeLeft_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t index;
	float modTimeLeft;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &index, &modTimeLeft) || !thisObj->IsActor()) return true;
	ActiveEffectList* effList = ((Actor*)thisObj)->magicTarget.GetEffectList();
	if (!effList) return true;
	ListNode<ActiveEffect>* iter = effList->Head();
	ActiveEffect* activeEff;
	do {
		activeEff = iter->data;
		if (!activeEff || !activeEff->bApplied || !ValidTempEffect(activeEff->effectItem) || !activeEff->magicItem ||
			!DYNAMIC_CAST(activeEff->magicItem, MagicItem, TESForm)) continue;
		if (!index--) {
			activeEff->timeElapsed += -modTimeLeft;
			if (activeEff->timeElapsed > activeEff->duration) activeEff->Remove(true);
			*result = 1;
			break;
		}
	} while (iter = iter->next);
	return true;
}
bool Cmd_IsHostilesNearby_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* actorCell = PlayerCharacter::GetSingleton()->parentCell;
	if (actorCell)
		*result = ThisCall<bool>(0x9764A0, ProcessManager::GetSingleton(), actorCell->IsInterior());
	return true;
}
bool Cmd_ToggleCombatMusic_Execute(COMMAND_ARGS) {
	uint32_t toggle = 1;
	ExtractArgsEx(EXTRACT_ARGS_EX, &toggle);
	bCombatMusicDisabled = (toggle == 0);
	return true;
}
bool Cmd_IsCombatMusicEnabled_Execute(COMMAND_ARGS) {
	*result = (bCombatMusicDisabled == 0);
	if (IsConsoleMode()) Console_Print("IsCombatMusicEnabled >> %.f", *result);
	return true;
}
bool Cmd_IsCompassHostile_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* toCheck = (Actor*)thisObj;
	auto iter = PlayerCharacter::GetSingleton()->compassTargets->Begin();
	for (; !iter.End(); ++iter) {
		PlayerCharacter::CompassTarget* target = iter.Get();
		if (target->isHostile && target->target == toCheck) {
			*result = 1;
			break;
		}
	}
	if (IsConsoleMode()) Console_Print("IsCompassHostile >> %.f", *result);
	return true;
}
void RestoreDisabledPlayerControlsHUDFlags() {
	SafeWrite32(0x771A53, HUDMainMenu::kXpMeter | HUDMainMenu::kSubtitles | HUDMainMenu::kMessages | HUDMainMenu::kQuestReminder | HUDMainMenu::kRadiationMeter);
}

bool Cmd_SetDisablePlayerControlsHUDVisibilityFlags_Execute(COMMAND_ARGS) {
	uint32_t flags;
	if (NUM_ARGS && ExtractArgsEx(EXTRACT_ARGS_EX, &flags)) {
		SafeWrite32(0x771A53, flags);
		HUDMainMenu_UpdateVisibilityState(HUDMainMenu::kHUDState_RECALCULATE);
	}
	else {
		RestoreDisabledPlayerControlsHUDFlags();
	}

	return true;
}
bool Cmd_GetNearestCompassHostile_Execute(COMMAND_ARGS) {
	*result = -1;

	NiPoint3* playerPos = PlayerCharacter::GetSingleton()->GetPos();

	float fSneakMaxDistance = *(float*)(0x11CD7D8 + 4);
	float fSneakExteriorDistanceMult = *(float*)(0x11CDCBC + 4);
	bool isInterior = PlayerCharacter::GetSingleton()->GetParentCell()->IsInterior();
	float interiorDistanceSquared = fSneakMaxDistance * fSneakMaxDistance;
	float exteriorDistanceSquared = (fSneakMaxDistance * fSneakExteriorDistanceMult) * (fSneakMaxDistance * fSneakExteriorDistanceMult);
	float maxDist = isInterior ? interiorDistanceSquared : exteriorDistanceSquared;
	Actor* closestHostile = nullptr;
	uint32_t skipInvisible = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &skipInvisible);
	auto iter = PlayerCharacter::GetSingleton()->compassTargets->Begin();
	for (; !iter.End(); ++iter) {
		PlayerCharacter::CompassTarget* target = iter.Get();
		if (target->isHostile) {
			if (skipInvisible > 0 && (target->target->avOwner.GetActorValueI(kAVCode_Invisibility) > 0 || target->target->avOwner.GetActorValueI(kAVCode_Chameleon) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPos()->CalculateDistSquared(playerPos);
			if (distToPlayer < maxDist) {
				maxDist = distToPlayer;
				closestHostile = target->target;
			}
		}
	}

	if (closestHostile)	*(uint32_t*)result = closestHostile->refID;

	return true;
}
bool Cmd_GetNearestCompassHostileDirection_Execute(COMMAND_ARGS) {
	*result = -1;

	NiPoint3* playerPos = PlayerCharacter::GetSingleton()->GetPos();

	float fSneakMaxDistance = *(float*)(0x11CD7D8 + 4);
	float fSneakExteriorDistanceMult = *(float*)(0x11CDCBC + 4);
	bool isInterior = PlayerCharacter::GetSingleton()->GetParentCell()->IsInterior();
	float maxDist = isInterior ? powf(fSneakMaxDistance, 2) : powf((fSneakMaxDistance * fSneakExteriorDistanceMult), 2);
	Actor* closestHostile = nullptr;
	uint32_t skipInvisible = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &skipInvisible);
	auto iter = PlayerCharacter::GetSingleton()->compassTargets->Begin();
	for (; !iter.End(); ++iter) {
		PlayerCharacter::CompassTarget* target = iter.Get();
		if (target->isHostile) {
			if (skipInvisible > 0 && (target->target->avOwner.GetActorValueI(kAVCode_Invisibility) > 0 || target->target->avOwner.GetActorValueI(kAVCode_Chameleon) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPos()->CalculateDistSquared(playerPos);
			if (distToPlayer < maxDist) {
				maxDist = distToPlayer;
				closestHostile = target->target;
			}
		}
	}

	if (closestHostile) {
		auto playerRotation = PlayerCharacter::GetSingleton()->GetZRotation(0);
		double headingAngle = GetAngleBetweenPoints(closestHostile->GetPos(), playerPos, playerRotation);

		// shift the coordinates from -180:180 to 0:360 and offset them (360 / 8 quadrants / 2) degrees
		int angle = headingAngle + 180 + 22.5;

		// convert the angle to which quadrant the NPC is in
		angle /= 45;
		*result = (angle + 4) % 8; // make 0 in front, 1 front right, 2 right, 3 back right ...
	}

	return true;
}
bool Cmd_HighlightBodyPartAlt_Execute(COMMAND_ARGS) {
	return Cmd_HighLightBodyPart(PASS_COMMAND_ARGS);
}

bool Cmd_DeactivateAllHighlightsAlt_Execute(COMMAND_ARGS) {
	return Cmd_DeactivateAllHighlights(PASS_COMMAND_ARGS);
}

bool Cmd_RemoveHighlightedRef_Execute(COMMAND_ARGS) {
	*result = 0;

	if (!thisObj) return true;

	InterfaceManager* interfaceMgr = InterfaceManager::GetSingleton();
	if (!interfaceMgr) return true;

	VATSHighlightData* vatsData = interfaceMgr->GetVATSHighlightData();

	for (uint32_t index = vatsData->numHighlighted; index;) {
		if (vatsData->highlightedRefs[--index].refr != thisObj)
			continue;

		if (--vatsData->numHighlighted) {
			if (index == vatsData->numHighlighted) {
				vatsData->highlightedRefs[index].refr = nullptr;
				vatsData->highlightedRefs[index].node = nullptr;
			} else {
				vatsData->highlightedRefs[index] = vatsData->highlightedRefs[vatsData->numHighlighted];
			}
			if (vatsData->highlightMain.refr == thisObj) {
				vatsData->highlightMain = vatsData->highlightedRefs[0];
			}
		} else {
			vatsData->highlightedRefs[0].refr = nullptr;
			vatsData->highlightedRefs[0].node = nullptr;
			vatsData->highlightMain.refr = nullptr;
			vatsData->highlightMain.node = nullptr;
			vatsData->highlightState = 0;
		}

		*result = 1;
		break;
	}

	return true;
}

bool Cmd_DisableMenuArrowKeys_Execute(COMMAND_ARGS) {
	if (!bArrowKeysDisabled) {
		bArrowKeysDisabled = true;
	}
	return true;
}
bool Cmd_EnableMenuArrowKeys_Execute(COMMAND_ARGS) {
	if (bArrowKeysDisabled) {
		bArrowKeysDisabled = false;
	}
	return true;
}
bool Cmd_GetRunSpeed_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* actor = (Actor*)thisObj;
	*result = ThisCall<float>(0x884EB0, actor);
	if (IsConsoleMode()) Console_Print("GetRunSpeed >> %.2f", *result);
	return true;
}
bool Cmd_ToggleNthPipboyLight_Execute(COMMAND_ARGS) {
	uint32_t index, isVisible;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &index, &isVisible) && index < 3) {
		FOPipboyManager* pipboyManager = InterfaceManager::GetSingleton()->pipboyManager;
		if (pipboyManager->byte028) {
			if (isVisible) {
				pipboyManager->pipboyLightGlow[index]->m_flags &= ~1;
			}
			else {
				pipboyManager->pipboyLightGlow[index]->m_flags |= 1;
			}
			*result = 1;
		}
	}
	return true;
}
bool Cmd_UnsetAV_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t avCode;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &avCode)) {
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValueF(avCode);

		tList<void>* actorPermSetAVList = &actor->list0E0;
		void* avEntry = ThisCall<void*>(0x937760, actorPermSetAVList, avCode);
		ThisCall(0x937400, actorPermSetAVList, avEntry);
		thisObj->MarkAsModified(0x400000);

		if (!actor->IsPlayerRef()) {
			BaseProcess* base = actor->baseProcess;
			if (base) {
				base->Unk_EC(avCode);
			}
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValueF(avCode);
		HandleActorValueChange(avOwner, avCode, oldVal, newVal, nullptr);
		*result = 1;
	}
	return true;
}

bool Cmd_UnforceAV_Execute(COMMAND_ARGS) {
	uint32_t avCode;
	*result = 0;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &avCode)) {
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValueF(avCode);

		tList<void>* actorPermForceAVList = &actor->list0D0;
		void* avEntry = ThisCall<void*>(0x937760, actorPermForceAVList, avCode);
		ThisCall(0x937400, actorPermForceAVList, avEntry);
		thisObj->MarkAsModified(0x800000);

		if (!actor->IsPlayerRef()) {
			BaseProcess* base = actor->baseProcess;
			if (base) {
				base->Unk_EC(avCode);
			}
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValueF(avCode);
		HandleActorValueChange(avOwner, avCode, oldVal, newVal, nullptr);
		*result = 1;
	}
	return true;
}

bool Cmd_StopSoundAlt_Execute(COMMAND_ARGS) {
	TESSound* soundForm = nullptr;
	TESObjectREFR* source = nullptr;
	BSFadeNode* fadeNode = nullptr;
	float fadeOutTime = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &soundForm, &source, &fadeOutTime) && soundForm && IS_TYPE(soundForm, TESSound) && source) {
		if (soundForm->soundFile.path.GetLength()) {
			CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
			const char* soundPath = soundForm->soundFile.path.pString;
			BSGameSound* gameSound;
			for (auto sndIter = BSAudioManager::Get()->playingSounds.Begin(); !sndIter.End(); ++sndIter) {
				gameSound = sndIter.Get();
				if (gameSound && StrBeginsCI(gameSound->filePath + 0xB, soundPath)) {
					fadeNode = (BSFadeNode*)BSAudioManager::Get()->soundPlayingObjects.Lookup(gameSound->mapKey);
					if (fadeNode && fadeNode->GetFadeNode() && fadeNode->linkedObj && fadeNode->linkedObj == source) {
						BSSoundHandle handle;
						handle.uiSoundID = gameSound->mapKey;

						if (fadeOutTime == -1) {
							handle.Stop();
						}
						else {
							int time = fadeOutTime * 1000.0;
							handle.FadeOutAndRelease(time);
						}
						*result = 1;
						break;
					}
				}
			}
		}
	}
	return true;
}

bool Cmd_SetVelEx_Execute(COMMAND_ARGS) {
	NiPoint3 Point;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &(Point.x), &(Point.y), &(Point.z))) {
		((void(__cdecl*)(NiNode*, NiPoint3*, int))(0x62B8D0))(thisObj->GetNiNode(), &Point, 1);
		*result = 1;
	}
	return true;
}

bool Cmd_ApplyWeaponPoison_Execute(COMMAND_ARGS)
{
	//removal support by jazzisparis
	*result = 0;
	AlchemyItem* poison = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &poison) && (!poison || (IS_TYPE(poison, AlchemyItem) && poison->IsPoison())))
	{
		TESObjectWEAP* weapon = nullptr;
		ExtraDataList* xData = nullptr;
		if (!thisObj->IsActor())
		{
			InventoryRef* invRef = InventoryRefGetForID(thisObj->refID);
			if (!invRef) return true;
			weapon = (TESObjectWEAP*)(invRef->data.type);
			xData = invRef->data.xData;
		}
		else
		{
			ContChangesEntry* wpnInfo = ((Actor*)thisObj)->baseProcess->GetWeaponInfo();
			if (wpnInfo && wpnInfo->extendData)
			{
				weapon = ((TESObjectWEAP*)wpnInfo->type);
				xData = wpnInfo->extendData->GetFirstItem();
			}
		}
		if (weapon && xData && (weapon->weaponSkill == kAVCode_Unarmed || weapon->weaponSkill == kAVCode_MeleeWeapons))
		{
			if (poison)
				ThisCall(0x419D10, xData, poison); // ExtraDataList::UpdateExtraPoison
			else
				ThisCall(0x410140, xData, kExtraData_Poison); // ExtraDataList::RemoveByType
			*result = 1;
		}
	}
	return true;
}
bool Cmd_TogglePipBoy_Execute(COMMAND_ARGS) {
	int pipboyTab = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pipboyTab);
	*result = 0;
	if (pipboyTab == 0 || pipboyTab == 1002 || pipboyTab == 1003 || pipboyTab == 1023) {
		if (InterfaceManager::GetSingleton()) {
			if (!InterfaceManager::GetSingleton()->pipBoyMode) {
				ThisCall(0x70F4E0, InterfaceManager::GetSingleton(), 0, pipboyTab);
			}
			else if (InterfaceManager::GetSingleton()->pipBoyMode == 3) {
				ThisCall(0x70F690, InterfaceManager::GetSingleton(), 0);
			}
			*result = 1;
		}
	}
	return true;
}

bool Cmd_ToggleLevelUpMenu_Execute(COMMAND_ARGS) {
	uint32_t ToExtract;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &ToExtract)) isShowLevelUp = ToExtract;
	return true;
}

bool Cmd_Jump_Execute(COMMAND_ARGS) {
	if (!thisObj->IsActor()) return true;
	((MobileObject*)thisObj)->Unk_95();
	return true;
}

bool Cmd_StopVATSCam_Execute(COMMAND_ARGS) {
	ThisCall(0x93E770, PlayerCharacter::GetSingleton(), 2, 0);
	return true;
}

bool Cmd_SetCameraShake_Execute(COMMAND_ARGS) {
	float shakeMult, time;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shakeMult, &time)) {
		*(float*)(0x11DFED4) = shakeMult;
		*(float*)(0x11DFED8) = time;
		*result = 1;
	}
	return true;
}

bool Cmd_DisableMuzzleFlashLights_Execute(COMMAND_ARGS) {
	int disable = -1;
	ExtractArgsEx(EXTRACT_ARGS_EX, &disable);
	if (disable >= 0 && disable <= 3) disableMuzzleLights = disable;
	*result = disableMuzzleLights;
	if (IsConsoleMode()) Console_Print("DisableMuzzleFlashLights >> %.f", *result);
	return true;
}
bool Cmd_ToggleDisableSaves_Execute(COMMAND_ARGS) {
	int doDisable = 1;
	BYTE modIdx = scriptObj->GetModIndex();
	*result = 0;
	if (modIdx < 0xFF && ExtractArgsEx(EXTRACT_ARGS_EX, &doDisable)) {
		if (doDisable) {
			SaveGameUMap.insert(modIdx);
		}
		else {
			SaveGameUMap.erase(modIdx);
		}
		*result = 1;
	}
	return true;
}


bool Cmd_EjectCasing_Execute(COMMAND_ARGS) {
	*result = false;
	const char cNodeName[128] = {};
	char cNewCasingPath[MAX_PATH] = {};
	const char* pOrgCasingPath;
	ConsoleManager* pConsole = ConsoleManager::GetSingleton();
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cNodeName, &cNewCasingPath)) {
		if (!thisObj || !thisObj->IsActor())
			return false;

		Actor* pActor = (Actor*)thisObj;

		TESObjectWEAP* pWeapon = pActor->GetEquippedWeapon();
		if (!pWeapon || pWeapon->IsMelee())
			return false;

		NiNode* pActorNode = nullptr;
		if (cNodeName[0] != 0) {
			PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
			if (thisObj == pPlayer) {
				pActorNode = pPlayer->GetNode(!pPlayer->is3rdPerson);
			}
			else
				pActorNode = thisObj->GetRefNiNode();
		}

		bool bChangedPos = false;
		NiAVObject* pCasingNode = nullptr;
		NiTransform kOrgTrans;
		if (pActorNode) {
			NiAVObject* pNewCasingNode = BSUtilities::GetObjectByName(pActorNode, cNodeName);
			pCasingNode = BSUtilities::GetObjectByName(pActorNode, "ShellCasingNode");
			if (pCasingNode && pNewCasingNode) {
				kOrgTrans = pCasingNode->m_world;

				pCasingNode->m_world = pNewCasingNode->m_world;

				bChangedPos = true;
			}
		}

		bool bHasCasingPath = false;
		if (cNewCasingPath[0] != 0) {
			bHasCasingPath = true;
			pOrgCasingPath = pWeapon->shellCasingModel.nifPath.c_str();
			pWeapon->shellCasingModel.nifPath.pString = cNewCasingPath;
		}

		pWeapon->EjectShellCasing(pActor);


		if (bChangedPos)
			pCasingNode->m_world = kOrgTrans;

		if (bHasCasingPath)
			pWeapon->shellCasingModel.nifPath.pString = (char*)pOrgCasingPath;

		*result = true;
		return true;
	}
	return false;
}

bool Cmd_PathToRef_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectREFR* pTarget = nullptr;
	float fRadius = -1.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTarget, &fRadius) && pTarget && pTarget->GetIsReference() && thisObj->IsActor()) {
		Actor* pActor = static_cast<Actor*>(thisObj);
		if (pTarget)
			pActor->SetPathfindingGoal(pTarget, fRadius);
		else
			pActor->StopMoving();

		*result = 1;
	}

	return true;
}

bool Cmd_GetGrenadeHoldTime_Execute(COMMAND_ARGS) {
	*result = PlayerCharacter::GetSingleton()->timeGrenadeHeld;
	return true;
}

bool Cmd_GetWeaponsForMod_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectIMOD* targetMod = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &targetMod) || !targetMod || NOT_ID(targetMod, TESObjectIMOD))
		return true;

	DataHandler* dataHandler = DataHandler::Get();
	if (!dataHandler) 
    return true;

	NVSEArrayVarInterface::Array* weaponArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	for (TESBoundObject* object = dataHandler->boundObjectList->first; object; object = object->next) {
		if (object->typeID != FORM_TYPE::TESObjectWEAP) 
      continue;
    
		TESObjectWEAP* weapon = (TESObjectWEAP*)object;

		for (int slot = 0; slot < 3; slot++) {
			if (weapon->itemMod[slot] == targetMod) {
				g_arrInterface->AppendElement(weaponArray, NVSEArrayElement(weapon));
				break;
			}
		}
	}

	g_arrInterface->AssignCommandResult(weaponArray, result);
	if (IsConsoleMode())
		Console_Print("GetWeaponsForMod >> Found %d weapon(s)", g_arrInterface->GetArraySize(weaponArray));
  
  return true;
}

bool Cmd_IsInDialogueWithPlayer_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj && thisObj->IsActor()) {
		Actor* pActor = static_cast<Actor*>(thisObj);
		*result = pActor->IsInDialogueWithPlayer();
	}
	return true;
}

bool Cmd_IsInDialogueWithPlayer_Execute(COMMAND_ARGS) {
	*result = 0;
	Cmd_IsInDialogueWithPlayer_Eval(thisObj, nullptr, nullptr, result);
	return true;
}