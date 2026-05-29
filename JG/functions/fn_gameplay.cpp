#include "fn_gameplay.h"
#include "GameForms.h"

#include "Bethesda/BSUtilities.hpp"
#include <GameUI.h>
#include <Bethesda/INISettingCollection.hpp>
#include <misc/WorldToScreen.h>
#include <GameRTTI.h>
#include <JG/CustomCameraShake.hpp>
#include <Bethesda/GameSettingCollection.hpp>
#include <GameEffects.h>
#include <JG/JohnnyPatches.hpp>
#include <Bethesda/TESObjectList.hpp>
#include <Bethesda/TESObject.hpp>
#include <Bethesda/TESDataHandler.hpp>
#include <JG/NPCAccuracy.hpp>
#include "decoding.h"
#include "GameProcess.h"
#include <JG/MediaLocationControllerOverride.hpp>
#include <JG/CustomHUDShake.hpp>
#include <JG/DisabledSaves.hpp>
#include <JG/DisabledLevelUp.hpp>
#include <JG/DisabledMuzzleFlashLights.hpp>
#include <JG/DisabledArrowKeys.hpp>

void(__cdecl* HandleActorValueChange)(ActorValueOwner* avOwner, int avCode, float oldVal, float newVal, ActorValueOwner* avOwner2) =
(void(__cdecl*)(ActorValueOwner*, int, float, float, ActorValueOwner*))0x66EE50;
bool(*Cmd_HighLightBodyPart)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB570;
bool(*Cmd_DeactivateAllHighlights)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB6C0;
void(__cdecl* HUDMainMenu_UpdateVisibilityState)(signed int) = (void(__cdecl*)(signed int))(0x771700);

#define NUM_ARGS *((uint8_t*)scriptData + *opcodeOffsetPtr)

std::unordered_map<TESForm*, std::pair<float, float>> tempEffectMap;

extern void (*ApplyPerkModifiers)(PerkEntryPointID entryPointID, TESObjectREFR* perkOwner, void* arg3, ...);
extern InventoryRef* (*InventoryRefGetForID)(uint32_t refID);

bool Cmd_StopHolotape_Execute(COMMAND_ARGS)
{
	*result = 0;
	BOOL bPlayStopSound = FALSE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &bPlayStopSound);
	noHolotapeStopSound = bPlayStopSound == 0;
	MapMenu* pMapMenu = MapMenu::GetSingleton();
	if (pMapMenu)
		pMapMenu->StopHolotape();
	*result = 1;
	return true;

}
bool Cmd_PlayHolotape_Execute(COMMAND_ARGS)
{
	*result = 0;
	BGSNote* pNote = nullptr;
	BOOL bPlayStartStopSound = TRUE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &bPlayStartStopSound) && pNote && IS_TYPE(pNote, BGSNote) && (pNote->GetNoteType() == BGSNote::NoteType::VOICE || pNote->GetNoteType() == BGSNote::NoteType::VOICE))
	{
		MapMenu* pMapMenu = MapMenu::GetSingleton();
		if (pMapMenu)
			pMapMenu->PlayHolotape(pNote, bPlayStartStopSound > 0);
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

		auto casinoRefId = casino->GetFormID();
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
		auto casinoRefId = casino->GetFormID();
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

bool Cmd_GetCasinoDeckTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCasino* pCasino = nullptr;
	uint32_t uiDeck = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &uiDeck) && pCasino && IS_TYPE(pCasino, TESCasino) && uiDeck >= 0 && uiDeck <= 3) {
		const char* pPath = pCasino->kBlackjackDeck[uiDeck].GetTextureName();
		if (IsConsoleMode())
			Console_Print("GetCasinoDeckTexture >> %s", pPath);
		g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
	}
	return true;
}

bool Cmd_SetCasinoDeckTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCasino* pCasino = nullptr;
	uint32_t uiDeck;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &uiDeck, &cPath) && pCasino && IS_TYPE(pCasino, TESCasino) && cPath[0] && uiDeck >= 0 && uiDeck <= 3) {
		pCasino->kBlackjackDeck[uiDeck].SetTextureName(cPath);
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
		chipForm = TESForm::GetFormByNumericID(casino->kCasinoData.uiCasinoChipID);
		*(uint32_t*)result = chipForm->GetFormID();
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
		casino->kCasinoData.uiCasinoChipID = chip->GetFormID();
		*result = 1;
	}
	return true;
}

bool Cmd_ClearMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaLocationControllerOverride::Reset();
	*result = 1;

	return true;
}

bool Cmd_SetMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaLocationController* ctrl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &ctrl) && ctrl && IS_TYPE(ctrl, MediaLocationController)) {
		MediaLocationControllerOverride::Set(ctrl);
		*result = 1;
	}
	return true;
}

bool Cmd_GetHUDShudderPower_Execute(COMMAND_ARGS) {
	*result = 0;
	uint8_t modId = scriptObj->GetCompileIndex();
	*result = CustomHUDShake::Get(modId);
	return true;
}

bool Cmd_SetHUDShudderPower_Execute(COMMAND_ARGS) {
	*result = 0;
	float power = -1.f;
	uint8_t modId = scriptObj->GetCompileIndex();
	if (modId < 0xFF && ExtractArgsEx(EXTRACT_ARGS_EX, &power)) {
		CustomHUDShake::Set(modId, power);
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
		TESForm* pSpace = nullptr;
		TESObjectCELL* pParentCell = PlayerCharacter::GetSingleton()->parentCell;
		if (pParentCell) {
			if (pParentCell->IsInterior())
				pSpace = pParentCell;
			else
				pSpace = pParentCell->worldSpace;
		}
		if (pSpace) {
			ThisCall(0x952E60, PlayerCharacter::GetSingleton(), pos.x, pos.y, pos.z, pSpace);
			*result = 1;
		}
	}
	return true;
}
bool Cmd_SetActorMovementFlags_Execute(COMMAND_ARGS)
{
	*result = 0;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags)) {
		Actor* pActor = PlayerCharacter::GetSingleton();
		if (thisObj)
			pActor = static_cast<Actor*>(thisObj);

		if (pActor->IsActor() && pActor->actorMover) {
			if (uiFlags)
				pActor->actorMover->ForceMoveMode(uiFlags);
			else
				pActor->actorMover->ClearForcedMoveMode();
			*result = 1;
		}
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
			PlayerCharacter::GetSingleton()->actorMover->ForceMoveMode(flags);
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

static float Sign(const NiPoint3& p1, const NiPoint3& p2, const NiPoint3& p3) {
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

static bool PointInTriangle(const NiPoint3& pt, const NiPoint3& v1, const NiPoint3& v2, const NiPoint3& v3) {
	bool b1 = Sign(pt, v1, v2) < 0.0;
	bool b2 = Sign(pt, v2, v3) < 0.0;
	bool b3 = Sign(pt, v3, v1) < 0.0;

	return (b1 == b2) && (b2 == b3);
}

static NiPoint3 GetTriangleCenter(const NiPoint3& v1, const NiPoint3& v2, const NiPoint3& v3) {
	return NiPoint3((v1.x + v2.x + v3.x) / 3.0f, (v1.y + v2.y + v3.y) / 3.0f, (v1.z + v2.z + v3.z) / 3.0f);
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

		for (uint32_t j = 0; j < spNavMesh->GetTriangleCount(); j++) {
			NavMeshTriangle* pNavMeshTriangle = spNavMesh->GetTriangle(j);
			if (checkDisabled && ((pNavMeshTriangle->uiFlags & NavMeshTriangle::DISABLED) != 0))
				continue;

			// Get triangle vertices
			NiPoint3 kVerts[3];
			for (uint32_t k = 0; k < 3; k++) {
				NiPoint3* pVertex = spNavMesh->GetVertex(pNavMeshTriangle->sVertices[k]);
				if (!pVertex)
					continue;

				kVerts[k] = *pVertex;
			}


			NiPoint3 kTriCenter = GetTriangleCenter(kVerts[0], kVerts[1], kVerts[2]);

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

		for (uint32_t j = 0; j < spNavMesh->GetTriangleCount(); j++) {
			NavMeshTriangle* pNavMeshTriangle = spNavMesh->GetTriangle(j);
			if (!pNavMeshTriangle)
				continue;
			if (checkDisabled && (pNavMeshTriangle->uiFlags & NavMeshTriangle::DISABLED) != 0)
				continue;

			// Get triangle vertices
			NiPoint3 kVerts[3];
			for (uint32_t k = 0; k < 3; k++) {
				NiPoint3* pVertex = spNavMesh->GetVertex(pNavMeshTriangle->sVertices[k]);
				if (!pVertex)
					continue;

				kVerts[k] = *pVertex;
			}


			// Check if player is inside the triangle
			if (PointInTriangle(arPointToTest, kVerts[0], kVerts[1], kVerts[2])) {
				// Get triangle center
				NiPoint3 kTriCenter = GetTriangleCenter(kVerts[0], kVerts[1], kVerts[2]);

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
		switch (a_form->GetFormType()) {
		case FORM_TYPE::TESNPC:
		case FORM_TYPE::TESCreature:
			NPCAccuracy::tables.ACTBAS[a_form->GetFormID()] = mul;
			break;
		case FORM_TYPE::TESCombatStyle:
			NPCAccuracy::tables.CSTY[a_form->GetFormID()] = mul;
			break;
		case FORM_TYPE::TESFaction:
			NPCAccuracy::tables.FACT[a_form->GetFormID()] = mul;
			break;

		}
	}
	else if (thisObj) {
		NPCAccuracy::tables.ACTREF[thisObj->GetFormID()] = mul;

	}
	return true;
}


bool Cmd_GetExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {

	*result = 1;
	TESForm* a_form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &a_form) && a_form) {
		switch (a_form->GetFormType()) {
		case FORM_TYPE::TESNPC:
		case FORM_TYPE::TESCreature:
			if (auto it = NPCAccuracy::tables.ACTBAS.find(a_form->GetFormID()); it != NPCAccuracy::tables.ACTBAS.end()) {
				*result = it->second;
			}
			break;
		case FORM_TYPE::TESCombatStyle:
			if (auto it = NPCAccuracy::tables.CSTY.find(a_form->GetFormID()); it != NPCAccuracy::tables.CSTY.end()) {
				*result = it->second;
			}
			break;
		case FORM_TYPE::TESFaction:
			if (auto it = NPCAccuracy::tables.FACT.find(a_form->GetFormID()); it != NPCAccuracy::tables.FACT.end()) {
				*result = it->second;
			}
			break;

		}
	}
	else if (thisObj) {
		if (auto it = NPCAccuracy::tables.ACTREF.find(thisObj->GetFormID()); it != NPCAccuracy::tables.ACTREF.end()) {
			*result = it->second;
		}
	}
	return true;


}

bool Cmd_RemoveExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {

	*result = 0;
	TESForm* a_form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &a_form) && a_form) {
		switch (a_form->GetFormType()) {
		case FORM_TYPE::TESNPC:
		case FORM_TYPE::TESCreature:
			NPCAccuracy::tables.ACTBAS.erase(a_form->GetFormID());
			break;
		case FORM_TYPE::TESCombatStyle:
			NPCAccuracy::tables.CSTY.erase(a_form->GetFormID());
			break;
		case FORM_TYPE::TESFaction:
			NPCAccuracy::tables.FACT.erase(a_form->GetFormID());
			break;

		}
	}
	else if (thisObj) {
		NPCAccuracy::tables.ACTREF.erase(thisObj->GetFormID());

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
	uint32_t uiGridSize = INISettingCollection::General::uGridsToLoad->UInt();

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

	uint32_t uiGridSize = INISettingCollection::General::uGridsToLoad->UInt();

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



bool __fastcall ValidTempEffect(EffectItem* apEffectItem) {
	if (!apEffectItem || (apEffectItem->GetDuration() <= 0) || !apEffectItem->GetEffectSetting())
		return false;

	const auto eArchetype = apEffectItem->GetEffectSetting()->GetEffectArchetype();
	return !eArchetype == EffectArchetypes::Type::VALUE_MODIFIER
		|| (eArchetype == EffectArchetypes::Type::SCRIPT && apEffectItem->GetEffectSetting()->GetFlags().bDisplayEffectName)
		|| (eArchetype >= EffectArchetypes::Type::INVISIBILITY && eArchetype <= EffectArchetypes::Type::DARKNESS)
		|| (eArchetype == EffectArchetypes::Type::PARALYSIS)
		|| (eArchetype >= EffectArchetypes::Type::CONCUSSION);
}


bool Cmd_PlaySoundFade_Execute(COMMAND_ARGS) {
	*result = 0;
	float fTime = 0;
	TESSound* sound;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sound, &fTime) && sound && IS_TYPE(sound, TESSound)) {
		TESObjectREFR* ref = thisObj;
		if (ref == nullptr) {
			ref = PlayerCharacter::GetSingleton();
		}
		if (ref->Get3DSimple()) {
			uint32_t uiFlags = BSAudioManager::kAudioFlags_3D | BSAudioManager::kAudioFlags_100;
			BSSoundHandle handle = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(sound->GetFormID(), uiFlags);
			handle.SetPosition(ref->GetPos());
			handle.SetObjectToFollow(ref->Get3DSimple());
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
					if (form->GetFormType() == FORM_TYPE::AlchemyItem) {
						float timeLeft = activeEff->duration - activeEff->timeElapsed;
						auto it = tempEffectMap.find(form);
						if (it != tempEffectMap.end() && it->second.second < activeEff->duration) {
							it->second.first = timeLeft;
							it->second.second = activeEff->duration;
						}
						else {
							tempEffectMap.insert({ form, {timeLeft, activeEff->duration} });
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
		CustomCameraShake::mult = shakeMult;
		CustomCameraShake::duration = time;
		*result = 1;
	}
	return true;
}

bool Cmd_RewardKarmaAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	int delta = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &delta);
	int karmaBefore = PlayerCharacter::GetSingleton()->avOwner.GetActorValueI(ActorValue::Index::KARMA);
	int ikarmaMax = GameSettingCollection::iKarmaMax->Int();
	int iKarmaMin = GameSettingCollection::iKarmaMin->Int();
	if (delta >= 0 && ((delta + karmaBefore) > ikarmaMax)) {
		delta = ikarmaMax - karmaBefore;
	}
	else if (delta < 0 && ((delta + karmaBefore) < iKarmaMin)) {
		delta = iKarmaMin - karmaBefore;
	}
	if (delta != 0) {
		PlayerCharacter::GetSingleton()->ModActorValue(ActorValue::Index::KARMA, delta, 0);
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
	const NiPoint3& pos = thisObj->GetPos();
	COORD_DATA coordData;
	TESObjectLAND* landscape = ThisCall<TESObjectLAND*>(0x546FB0, cell); // TESObjectCELL::GetLand
	if (!landscape) return true;
	landscape->GetCoordData(coordData, pos, 1);
	TESLandTexture* txt = ThisCall<TESLandTexture*>(0x53A630, landscape, coordData.iBlock, coordData.iVertIdx); // TESObjectLAND::GetMainTexture
	if (txt) *(uint32_t*)result = txt->GetFormID();
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
		BSGameSound* pSound;
		uint32_t uiKey;
		auto kIter = BSAudioManager::Get()->playingSounds.GetFirstPos();
		while (kIter) {
			BSAudioManager::Get()->playingSounds.GetNext(kIter, uiKey, pSound);
			if (!pSound || (pSound->sourceSound != sound))
				continue;

			BSSoundHandle handle;
			handle.uiSoundID = pSound->mapKey;
			handle.Stop();
			*result = 1;
		}
	}

	return true;
}

bool Cmd_GetPlayingEffectShaders_Execute(COMMAND_ARGS) {
	*result = 0;
	ListNode<BSTempEffect>* iter = ProcessLists::GetSingleton()->tempEffects.Head();
	MagicShaderHitEffect* effect;
	NVSEArrayVar* effArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	do {
		effect = (MagicShaderHitEffect*)iter->data;
		if (effect && IS_TYPE(effect, MagicShaderHitEffect) && effect->flags != 1 && effect->target && effect->target->GetFormID() == thisObj->GetFormID()) {
			g_arrInterface->AppendElement(effArr, NVSEArrayElement(effect->effectShader));
		}
	} while (iter = iter->next);

	g_arrInterface->AssignCommandResult(effArr, result);
	return true;
}

TESWorldSpace* GetWorldspace(TESObjectREFR* ref) {
	TESObjectCELL* cell = ref->parentCell;
	if (!cell) cell = ref->childCell.GetSaveParentCell();
	if (cell && (cell->cellFlags & 1) == 0) return cell->worldSpace;
	return nullptr;
}

bool Cmd_GetLocationName_Execute(COMMAND_ARGS) {
	*result = 0;
	char locationName[256] = {};
	if (thisObj->parentCell && (thisObj->parentCell->cellFlags & 1) != 0) {
		strcpy_s(locationName, thisObj->parentCell->fullName.GetFullName());
	}
	else {
		TESWorldSpace* wspc = GetWorldspace(thisObj);
		if (wspc) {
			BSString str;
			const NiPoint3& pos = thisObj->GetPos();
			wspc->GetMapNameForLocation(str, pos.x, pos.y, pos.z);
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
	TESForm* pOwner = ThisCall<TESForm*>(0x567790, thisObj); // TESObjectREFR::GetOwner
	if (pOwner) {
		ThisCall(0x8C0EC0, PlayerCharacter::GetSingleton(), thisObj, pOwner, 0xFFFFFFFF); // Actor::TrespassAlarm
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
			if (skipInvisible > 0 && !hasImprovedDetection && (target->target->avOwner.GetActorValueI(ActorValue::Index::INVISIBILITY) > 0
				|| target->target->avOwner.GetActorValueI(ActorValue::Index::CHAMELEON) > 0)) {
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
			TESForm* containerOwner = ThisCall<TESForm*>(0x567790, container); // TESObjectREFR::GetOwner
			if (!containerOwner) return true;
			ExtraContainerChanges* xChanges = thisObj->extraDataList.GetExtraData<ExtraContainerChanges>();
			if (!xChanges || !xChanges->pChanges || !xChanges->pChanges->pItems)
				return true;
			BSSimpleList<ItemChange*>* contChangesIter = xChanges->pChanges->pItems->GetHead();
			while (contChangesIter && !contChangesIter->IsEmpty()){
				ItemChange* entry = contChangesIter->GetItem();
				contChangesIter = contChangesIter->GetNext();

				if (!entry || !entry->pExtraLists || !entry->pObject)
					continue;

				BSSimpleList<ExtraDataList*>* xdlIter = entry->pExtraLists->GetHead();
				ExtraDataList* xData;
				while (xdlIter && !xdlIter->IsEmpty()){
					xData = xdlIter->GetItem();
					xdlIter = xdlIter->GetNext();
					if (xData) {
						ExtraOwnership* xOwn = xData->GetExtraData<ExtraOwnership>();
						if (xOwn && xOwn->pOwner && xOwn->pOwner->GetFormID() == containerOwner->GetFormID()) {
							ThisCall(0x8BFA40, thisObj, container, nullptr, nullptr, 1, containerOwner); // Actor::StealAlarm
							*result = 1;
							return true;
						}
					}
				}
			}
		}
		else {
			TESForm* owner = ThisCall<TESForm*>(0x567790, container); // TESObjectREFR::GetOwner
			ThisCall(0x8BFA40, thisObj, container, nullptr, nullptr, 1, owner); // Actor::StealAlarm
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetCalculatedSpread_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* pActor = static_cast<Actor*>(thisObj);
	if (!thisObj->IsActor() || !pActor->baseProcess || pActor->baseProcess->GetProcessLevel() > PROCESS_TYPE::MIDDLE_HIGH)
		return true;

	ItemChange* pWeaponItem = pActor->baseProcess->GetCurrentWeapon();
	if (pWeaponItem && pWeaponItem->pObject) {
		bool bDecreaseSpread = pWeaponItem->HasModEffectActive(WEAPON_MOD_EFFECT_TYPE::DECREASE_SPREAD);
		float fMinSpread = ThisCall<float>(0x524B80, pWeaponItem->pObject, bDecreaseSpread); // TESObjectWEAP::GetMinSpread
		float fWeapSpread = ThisCall<float>(0x524BE0, pWeaponItem->pObject, bDecreaseSpread); // TESObjectWEAP::GetMaxSpread
		float fSpread = ThisCall<float>(0x8B0DD0, pActor, 1); // Actor::GetGunSkill

		float fTotalSpread = (fWeapSpread * fSpread + fMinSpread) * 0.01745329238474369;

		TESAmmo* pAmmo = ThisCall<TESAmmo*>(0x525980, pWeaponItem->pObject, pActor); // TESObjectWEAP::GetCurrentAmmo
		fTotalSpread = TESAmmoEffect::ApplyAmmoEffect(AMMO_EFFECT_TYPE::SPREAD, (pAmmo ? pAmmo->GetAmmoEffectList() : nullptr), fTotalSpread);

		float fSpreadPenalty = ThisCall<float>(0x8B0DD0, pActor, 2); // Actor::GetGunSkill

		fTotalSpread += fSpreadPenalty * GameSettingCollection::fNPCMaxGunWobbleAngle->Float() * 0.01745329238474369f;

		fTotalSpread = fTotalSpread + static_cast<MiddleHighProcess*>(pActor->baseProcess)->fAimLooking;

		if (pWeaponItem->HasModEffectActive(WEAPON_MOD_EFFECT_TYPE::SPLIT_BEAM))
			fTotalSpread *= ThisCall<float>(0x4BCF60, pWeaponItem->pObject, WEAPON_MOD_EFFECT_TYPE::SPLIT_BEAM, 1); // TESObjectWEAP::GetModEffectValue

		*result = fTotalSpread;
	}
	if (IsConsoleMode()) 
		Console_Print("GetCalculatedSpread >> %f", *result);

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
		*result = ThisCall<bool>(0x9764A0, ProcessLists::GetSingleton(), actorCell->IsInterior());
	return true;
}

bool Cmd_ToggleCombatMusic_Execute(COMMAND_ARGS) {
	uint32_t toggle = 1;
	ExtractArgsEx(EXTRACT_ARGS_EX, &toggle);
	JohnnyPatches::bCombatMusicDisabled = (toggle == 0);
	return true;
}

bool Cmd_IsCombatMusicEnabled_Execute(COMMAND_ARGS) {
	*result = (JohnnyPatches::bCombatMusicDisabled == 0);
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

	const NiPoint3& playerPos = PlayerCharacter::GetSingleton()->GetPos();

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
			if (skipInvisible > 0 && (target->target->avOwner.GetActorValueI(ActorValue::Index::INVISIBILITY) > 0 || target->target->avOwner.GetActorValueI(ActorValue::Index::CHAMELEON) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPos().SqrDistance(playerPos);
			if (distToPlayer < maxDist) {
				maxDist = distToPlayer;
				closestHostile = target->target;
			}
		}
	}

	if (closestHostile)	*(uint32_t*)result = closestHostile->GetFormID();

	return true;
}

double GetVectorAngle2D(const NiPoint3* pt) {
	double angle;
	if (pt->y == 0) {
		if (pt->x <= 0) {
			angle = kDblPIx3d2;
		}
		else {
			angle = kDblPId2;
		}
	}
	else {
		double ratio = pt->x / pt->y;
		angle = dAtan(ratio);
		if (pt->y < 0.0) {
			angle += kDblPI;
		}
	}

	return angle;
}


double GetAngleBetweenPoints(const NiPoint3& actorPos, const NiPoint3& playerPos, float offset) {
	NiPoint3 diff = actorPos - playerPos;

	double angle = GetVectorAngle2D(&diff) - offset;
	if (angle > -kDblPI) {
		if (angle > kDblPI) {
			angle = kDblPIx2 - angle;
		}
	}
	else {
		angle += kDblPIx2;
	}
	return angle * 57.295779513;
}


bool Cmd_GetNearestCompassHostileDirection_Execute(COMMAND_ARGS) {
	*result = -1;

	const NiPoint3& playerPos = PlayerCharacter::GetSingleton()->GetPos();

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
			if (skipInvisible > 0 && (target->target->avOwner.GetActorValueI(ActorValue::Index::INVISIBILITY) > 0 || target->target->avOwner.GetActorValueI(ActorValue::Index::CHAMELEON) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPos().SqrDistance(playerPos);
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
			}
			else {
				vatsData->highlightedRefs[index] = vatsData->highlightedRefs[vatsData->numHighlighted];
			}
			if (vatsData->highlightMain.refr == thisObj) {
				vatsData->highlightMain = vatsData->highlightedRefs[0];
			}
		}
		else {
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
	DisabledArrowKeys::Toggle(true);
	return true;
}
bool Cmd_EnableMenuArrowKeys_Execute(COMMAND_ARGS) {
	DisabledArrowKeys::Toggle(false);
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
		if (pipboyManager->byte028 && pipboyManager->pipboyLightGlow[index]) {
			pipboyManager->pipboyLightGlow[index]->SetAppCulled(!isVisible);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_UnsetAV_Execute(COMMAND_ARGS) {
	*result = 0;
	ActorValue::Index eActorValue;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &eActorValue)) {
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValueF(eActorValue);

		tList<void>* actorPermSetAVList = &actor->list0E0;
		void* avEntry = ThisCall<void*>(0x937760, actorPermSetAVList, eActorValue); // ModifierList::GetModifierItem
		ThisCall(0x937400, actorPermSetAVList, avEntry); // ModifierList::DeleteModifier
		thisObj->AddChange(0x400000);

		if (!actor->IsPlayerRef()) {
			BaseProcess* base = actor->baseProcess;
			if (base)
				base->SetCachedActorValueOutOfDate(eActorValue);
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValueF(eActorValue);
		HandleActorValueChange(avOwner, eActorValue, oldVal, newVal, nullptr);
		*result = 1;
	}
	return true;
}

bool Cmd_UnforceAV_Execute(COMMAND_ARGS) {
	ActorValue::Index eActorValue;
	*result = 0;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &eActorValue)) {
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValueF(eActorValue);

		tList<void>* actorPermForceAVList = &actor->list0D0;
		void* avEntry = ThisCall<void*>(0x937760, actorPermForceAVList, eActorValue);
		ThisCall(0x937400, actorPermForceAVList, avEntry);
		thisObj->AddChange(0x800000);

		if (!actor->IsPlayerRef()) {
			BaseProcess* base = actor->baseProcess;
			if (base)
				base->SetCachedActorValueOutOfDate(eActorValue);
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValueF(eActorValue);
		HandleActorValueChange(avOwner, eActorValue, oldVal, newVal, nullptr);
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
		if (soundForm->soundFile.GetSoundFileLength()) {
			CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
			const char* soundPath = soundForm->soundFile.GetSoundFile();
			BSGameSound* pSound;
			uint32_t uiKey;
			auto kObjIter = BSAudioManager::Get()->soundPlayingObjects.GetFirstPos();
			while (kObjIter) {
				NiPointer<NiAVObject> spObject;
				BSAudioManager::Get()->soundPlayingObjects.GetNext(kObjIter, uiKey, spObject);
				if (!spObject || !spObject->IsFadeNode())
					continue;

				BSFadeNode* pFadeNode = static_cast<BSFadeNode*>(spObject.m_pObject);

				if (pFadeNode->pLinkedObj != source)
					continue;

				BSAudioManager::Get()->playingSounds.GetAt(uiKey, pSound);
				if (pSound && StrBeginsCI(pSound->filePath + 0xB, soundPath)) {
					BSSoundHandle handle;
					handle.uiSoundID = pSound->mapKey;

					if (fadeOutTime == -1)
						handle.Stop();
					else
						handle.FadeOutAndRelease(fadeOutTime * 1000.0);
					*result = 1;
					break;
				}
			}
		}
	}
	return true;
}

bool Cmd_SetVelEx_Execute(COMMAND_ARGS) {
	NiPoint3 kVector;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kVector.x, &kVector.y, &kVector.z)) {
		CdeclCall(0x62B8D0, thisObj->Get3D(), &kVector, true);
		*result = 1;
	}
	return true;
}

bool Cmd_ApplyWeaponPoison_Execute(COMMAND_ARGS) {
	// Removal support by jazzisparis
	*result = 0;
	AlchemyItem* pPoison = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pPoison) && (!pPoison || (IS_TYPE(pPoison, AlchemyItem) && pPoison->CanBePoison()))) {
		TESObjectWEAP* pWeapon = nullptr;
		ExtraDataList* pExtraData = nullptr;
		if (!thisObj->IsActor()) {
			InventoryRef* pInvRef = InventoryRefGetForID(thisObj->GetFormID());
			if (!pInvRef)
				return true;

			if (!pInvRef->data.type)
				return true;

			if (pInvRef->data.type->GetFormType() == FORM_TYPE::TESObjectWEAP) {
				pWeapon = static_cast<TESObjectWEAP*>(pInvRef->data.type);
				pExtraData = pInvRef->data.xData;
			}
		}
		else if (static_cast<Actor*>(thisObj)->baseProcess) {
			ItemChange* pWeaponItem = static_cast<Actor*>(thisObj)->baseProcess->GetCurrentWeapon();
			if (pWeaponItem && pWeaponItem->pExtraLists) {
				pWeapon = static_cast<TESObjectWEAP*>(pWeaponItem->GetContainerObject());
				pExtraData = pWeaponItem->pExtraLists->GetItem();
			}
		}
		if (pWeapon && pExtraData && (pWeapon->weaponSkill == kAVCode_Unarmed || pWeapon->weaponSkill == kAVCode_MeleeWeapons)) {
			if (pPoison)
				ThisCall(0x419D10, pExtraData, pPoison); // ExtraDataList::UpdateExtraPoison
			else
				pExtraData->RemoveExtra<ExtraPoison>();
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
	BOOL bValue;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bValue))
		DisabledLevelUp::isShowLevelUp = bValue;
	return true;
}

bool Cmd_Jump_Execute(COMMAND_ARGS) {
	if (!thisObj->IsActor()) 
		return true;
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
	int mode = -1;
	ExtractArgsEx(EXTRACT_ARGS_EX, &mode);
	if (mode < 0 || mode > 3) {
		mode = -1;
	}
	*result = DisabledMuzzleFlashLights::SetMode(mode);
	if (IsConsoleMode()) Console_Print("DisableMuzzleFlashLights >> %.f", *result);
	return true;
}
bool Cmd_ToggleDisableSaves_Execute(COMMAND_ARGS) {
	BOOL bDisable = TRUE;
	uint32_t uiTypeFlags = DisabledSaves::SaveTypeFlags::ALL;
	const uint8_t ucIndex = scriptObj->GetCompileIndex();
	*result = 0;
	if (ucIndex < 0xFF && ExtractArgsEx(EXTRACT_ARGS_EX, &bDisable, &uiTypeFlags)) {
		DisabledSaves::Toggle(ucIndex, bDisable > 0, uiTypeFlags);
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

		Actor* pActor = static_cast<Actor*>(thisObj);

		TESObjectWEAP* pWeapon = pActor->GetEquippedWeapon();
		if (!pWeapon || pWeapon->IsMelee())
			return false;

		NiNode* pActorNode = nullptr;
		if (cNodeName[0] != 0) {
			PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
			if (thisObj == pPlayer) {
				pActorNode = pPlayer->Get3D(!pPlayer->is3rdPerson);
			}
			else
				pActorNode = thisObj->Get3DSimple();
		}

		bool bChangedPos = false;
		NiAVObject* pCasingNode = nullptr;
		NiTransform kOrgTrans;
		if (pActorNode) {
			NiAVObject* pNewCasingNode = BSUtilities::GetObjectByName(pActorNode, cNodeName);
			pCasingNode = BSUtilities::GetObjectByName(pActorNode, "ShellCasingNode");
			if (pCasingNode && pNewCasingNode) {
				kOrgTrans = pCasingNode->m_kWorld;

				pCasingNode->m_kWorld = pNewCasingNode->m_kWorld;

				bChangedPos = true;
			}
		}

		bool bHasCasingPath = false;
		if (cNewCasingPath[0] != 0) {
			bHasCasingPath = true;
			pOrgCasingPath = pWeapon->shellCasingModel.strModel.c_str();
			pWeapon->shellCasingModel.strModel.pString = cNewCasingPath;
		}

		pWeapon->EjectShellCasing(pActor);


		if (bChangedPos)
			pCasingNode->m_kWorld = kOrgTrans;

		if (bHasCasingPath)
			pWeapon->shellCasingModel.strModel.pString = (char*)pOrgCasingPath;

		*result = true;
		return true;
	}
	return false;
}

bool Cmd_PathToRef_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectREFR* pTarget = nullptr;
	float fRadius = -1.f;
	BOOL bFaceTarget = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTarget, &fRadius, &bFaceTarget) && pTarget && pTarget->IsReference() && thisObj->IsActor()) {
		Actor* pActor = static_cast<Actor*>(thisObj);
		if (pTarget) {
			if (bFaceTarget)
				*result = pActor->SetPathfindingGoalAndAngle(pTarget, fRadius);
			else
				*result = pActor->SetPathfindingGoal(pTarget, fRadius);
		}
		else {
			pActor->StopMoving();
			*result = 1;
		}
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

	TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
	NVSEArrayVarInterface::Array* weaponArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	pDataHandler->pObjects->ForEach([&](TESObject* apObject) {
		if (apObject->GetFormType() != FORM_TYPE::TESObjectWEAP)
			return;

		TESObjectWEAP* pWeapon = static_cast<TESObjectWEAP*>(apObject);

		for (uint32_t uiSlot = 0; uiSlot < 3; uiSlot++) {
			if (pWeapon->itemMod[uiSlot] == targetMod) {
				g_arrInterface->AppendElement(weaponArray, NVSEArrayElement(pWeapon));
				break;
			}
		}
		});

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

bool Cmd_PathToPoint_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 kTarget;
	float fFaceAngle = FLT_MAX;
	float fRadius = -1.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kTarget.x, &kTarget.y, &kTarget.z, &fRadius, &fFaceAngle) && thisObj->IsActor()) {
		Actor* pActor = static_cast<Actor*>(thisObj);
		TESObjectCELL* pCell = TES::GetSingleton()->GetCellForPoint(kTarget);
		if (pCell) {
			TESWorldSpace* pWorld = pCell->GetWorldSpace();
			if (fFaceAngle != FLT_MAX)
				*result = pActor->SetPathfindingGoalAndAngle(kTarget, pCell, pWorld, fRadius, fFaceAngle);
			else
				*result = pActor->SetPathfindingGoal(kTarget, pCell, pWorld, fRadius);
		}
	}

	return true;
}

bool Cmd_SetYieldTimer_Execute(COMMAND_ARGS) {
	float fTime;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fTime)) {
		PlayerCharacter::GetSingleton()->fYieldTimer = fTime;
		*result = 1;
	}
	return true;
}

bool Cmd_GetYieldTimer_Execute(COMMAND_ARGS) {
	*result = PlayerCharacter::GetSingleton()->fYieldTimer;
	return true;
}