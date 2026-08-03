#include "fn_gameplay.h"
#ifdef GAME
#include "decoding.h"
#include "GameEffects.h"
#include "GameForms.h"
#include "GameProcess.h"
#include "GameRTTI.h"
#include "GameUI.h"

#include "Bethesda/BGSEntryPoint.hpp"
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/ExtraOwnership.hpp"
#include "Bethesda/GameSettingCollection.hpp"
#include "Bethesda/INISettingCollection.hpp"
#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/TESObject.hpp"
#include "Bethesda/TESObjectList.hpp"

#include "JG/CustomCameraShake.hpp"
#include "JG/CustomHUDShake.hpp"
#include "JG/DisabledArrowKeys.hpp"
#include "JG/DisabledLevelUp.hpp"
#include "JG/DisabledMuzzleFlashLights.hpp"
#include "JG/DisabledSaves.hpp"
#include "JG/JohnnyPatches.hpp"
#include "JG/MediaLocationControllerTweaks.hpp"
#include "JG/NPCAccuracy.hpp"
#include "JG/ScriptUtils.hpp"
#include "JG/WorldToScreen.hpp"

#include "shared/BSMemory/BSScrapMemory.hpp"

#include "unordered_map"

bool(*Cmd_HighLightBodyPart)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB570;
bool(*Cmd_DeactivateAllHighlights)(COMMAND_ARGS) = (bool (*)(COMMAND_ARGS)) 0x5BB6C0;
void(__cdecl* HUDMainMenu_SetMenuMode)(uint32_t) = (void(__cdecl*)(uint32_t))(0x771700);

extern void (*ApplyPerkModifiers)(PerkEntryPointID entryPointID, TESObjectREFR* perkOwner, void* arg3, ...);
extern InventoryRef* (*InventoryRefGetForID)(uint32_t refID);

bool Cmd_StopHolotape_Execute(COMMAND_ARGS) {
	arResult = 0;
	BOOL bPlayStopSound = FALSE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &bPlayStopSound);
	MapMenu* pMapMenu = MapMenu::GetSingleton();
	if (pMapMenu) {
		bNoHolotapeStopSound = bPlayStopSound == FALSE;
		pMapMenu->StopHolotape();
		arResult = 1;
	}

	return true;
}

bool Cmd_PlayHolotape_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	BOOL bPlayStartStopSound = TRUE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &bPlayStartStopSound) && pNote && IS_TYPE(pNote, BGSNote) && (pNote->GetNoteType() == BGSNote::NoteType::VOICE || pNote->GetNoteType() == BGSNote::NoteType::SOUND)){
		MapMenu* pMapMenu = MapMenu::GetSingleton();
		if (pMapMenu) {
			pMapMenu->PlayHolotape(pNote, bPlayStartStopSound > 0);
			arResult = 1;
		}
	}

	return true;
}

bool Cmd_SetCasinoWinnings_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESCasino* pCasino = nullptr;
	int32_t iEarnings;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &iEarnings) && pCasino && IS_TYPE(pCasino, TESCasino)) {
		const uint32_t uiFormID = pCasino->GetFormID();
		auto pIter = PlayerCharacter::GetSingleton()->casinoDataList;
		while (pIter && !pIter->IsEmpty()) {
			CasinoStats* pStats = pIter->GetItem();
			if (pStats && pStats->casinoRefID == uiFormID) {
				pStats->earnings = iEarnings;
				arResult = 1;
				return true;
			}
			pIter = pIter->GetNext();
		}

		CasinoStats* pStats = BSMemory::malloc<CasinoStats>();
		pStats->earningStage = 0;
		pStats->earnings = iEarnings;
		pStats->casinoRefID = uiFormID;
		PlayerCharacter::GetSingleton()->casinoDataList->AddHead(pStats);
	}

	return true;
}

bool __cdecl Cmd_GetCasinoWinnings_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESCasino* pCasino = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino) && pCasino && IS_TYPE(pCasino, TESCasino)) {
		const uint32_t uiFormID = pCasino->GetFormID();
		auto pIter = PlayerCharacter::GetSingleton()->casinoDataList;
		while (pIter && !pIter->IsEmpty()) {
			CasinoStats* pStats = pIter->GetItem();
			if (pStats && pStats->casinoRefID == uiFormID) {
				arResult = pStats->earnings;
				return true;
			}
			pIter = pIter->GetNext();
		}
	}

	return true;
}

bool Cmd_GetCasinoDeckTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
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
	arResult = 0;
	TESCasino* pCasino = nullptr;
	uint32_t uiDeck;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &uiDeck, &cPath) && pCasino && IS_TYPE(pCasino, TESCasino) && cPath[0] && uiDeck >= 0 && uiDeck <= 3) {
		pCasino->kBlackjackDeck[uiDeck].SetTextureName(cPath);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetCasinoChip_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESCasino* pCasino = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino) && pCasino && pCasino->kCasinoData.uiCasinoChipID) {
		TESForm* pChipForm = TESForm::GetFormByNumericID(pCasino->kCasinoData.uiCasinoChipID);
		if (pChipForm)
			ScriptUtils::SetFormIDResult(arResult, pChipForm->GetFormID());
	}
	return true;
}

bool Cmd_SetCasinoChip_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESCasino* pCasino = nullptr;
	TESForm* pChip = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &pChip) && pCasino && IS_TYPE(pCasino, TESCasino) && pChip && IS_TYPE(pChip, TESCasinoChips)) {
		pCasino->kCasinoData.uiCasinoChipID = pChip->GetFormID();
		arResult = 1;
	}
	return true;
}

bool Cmd_ClearMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	arResult = 0;
	MediaLocationControllerTweaks::ResetOverride();
	arResult = 1;

	return true;
}

bool Cmd_SetMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	arResult = 0;
	MediaLocationController* pCtrl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCtrl) && pCtrl && IS_TYPE(pCtrl, MediaLocationController)) {
		MediaLocationControllerTweaks::SetOverride(pCtrl);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetHUDShudderPower_Execute(COMMAND_ARGS) {
	arResult = 0;
	const TESFile* pFile = apScript->GetFile(0);
	if (pFile)
		arResult = CustomHUDShake::Get(pFile);
	return true;
}

bool Cmd_SetHUDShudderPower_Execute(COMMAND_ARGS) {
	arResult = 0;
	float fPower = -1.f;
	const TESFile* pFile = apScript->GetFile(0);
	if (pFile && ExtractArgsEx(EXTRACT_ARGS_EX, &fPower)) {
		CustomHUDShake::Set(pFile, fPower);
		arResult = 1;
	}
	return true;
}


bool Cmd_ClearCustomMapMarker_Execute(COMMAND_ARGS) {
	arResult = 0;
	PlayerCharacter::GetSingleton()->RemovePlayerMapMarker();
	arResult = 1;
	return true;
}

bool Cmd_SetCustomMapMarker_Execute(COMMAND_ARGS) {
	arResult = 0;
	NiPoint3 kPos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kPos.x, &kPos.y, &kPos.z)) {
		TESForm* pSpace = nullptr;
		TESObjectCELL* pParentCell = PlayerCharacter::GetSingleton()->GetParentCell();
		if (pParentCell) {
			if (pParentCell->IsInterior())
				pSpace = pParentCell;
			else
				pSpace = pParentCell->worldSpace;
		}
		if (pSpace) {
			PlayerCharacter::GetSingleton()->SetPlayerMapMarker(kPos, pSpace);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_SetActorMovementFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags)) {
		Actor* pActor = PlayerCharacter::GetSingleton();
		if (apRef)
			pActor = static_cast<Actor*>(apRef);

		if (pActor->IsActor() && pActor->pActorMover) {
			if (uiFlags)
				pActor->pActorMover->ForceMoveMode(uiFlags);
			else
				pActor->pActorMover->ClearForcedMoveMode();
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_SetAlwaysRun_Execute(COMMAND_ARGS) {
	arResult = 0;
	int alwaysRun = -1;
	int updateMovementFlags = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &alwaysRun, &updateMovementFlags);
	if (alwaysRun > -1) {
		bool bAlwaysRun = (alwaysRun > 0);
		PlayerCharacter::GetSingleton()->alwaysRun = bAlwaysRun;
		if (updateMovementFlags) {
			PlayerMover* playerMover = (PlayerMover*)PlayerCharacter::GetSingleton()->pActorMover;
			uint32_t flags = playerMover->pcMovementFlags;
			if (bAlwaysRun) {
				flags |= 0x200;
			}
			else {
				flags &= ~0x200;
			}
			PlayerCharacter::GetSingleton()->pActorMover->ForceMoveMode(flags);
		}
		arResult = 1;
	}
	return true;
}

bool Cmd_SetAutoMove_Execute(COMMAND_ARGS) {
	arResult = 0;
	int32_t iAutoMove = -1;
	ExtractArgsEx(EXTRACT_ARGS_EX, &iAutoMove);
	if (iAutoMove > -1) {
		PlayerCharacter::GetSingleton()->autoMove = iAutoMove > 0;
		arResult = 1;
	}
	return true;
}

SPEC_NOINLINE bool Cmd_HasHealthDamageEffect_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	if (apRef->IsActor())
		arResult = static_cast<Actor*>(apRef)->HasDamageHealthEffect();
	return true;
}

bool Cmd_HasHealthDamageEffect_Execute(COMMAND_ARGS) {
	return Cmd_HasHealthDamageEffect_Eval(apRef, nullptr, nullptr, arResult);
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

static NiPoint3 __fastcall GetTriangleCenter(const NiPoint3& v1, const NiPoint3& v2, const NiPoint3& v3) {
	return NiPoint3((v1.x + v2.x + v3.x) / 3.0f, (v1.y + v2.y + v3.y) / 3.0f, (v1.z + v2.z + v3.z) / 3.0f);
}

static void __fastcall GetClosestNavMeshTriangle(const TESObjectCELL* apCell, const NiPoint3& arPointToTest, bool checkDisabled, float zLimit, NiPoint4& arOut) {
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

static bool __fastcall GetPointNavMesh(const TESObjectCELL* apCell, const NiPoint3& arPointToTest, bool checkDisabled, float zLimit, NiPoint4& arOut) {
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
	arResult = 0;
	float fMultiplier = 1.f;
	TESForm* pForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fMultiplier, &pForm)) {
		TESForm* pTarget = pForm ? pForm : apRef;
		if (pTarget) {
			if (fabs(fMultiplier) < FLT_EPSILON)
				fMultiplier = FLT_EPSILON + DBL_EPSILON;

			NPCAccuracy::SetMultiplier(pTarget, fMultiplier);
		}
	}

	return true;
}


SPEC_NOINLINE bool Cmd_GetExtraAccuracyPenaltyMult_Eval(COMMAND_ARGS_EVAL) {
	arResult = 1;
	TESForm* pForm = static_cast<TESForm*>(apParam1);
	TESForm* pTarget = pForm ? pForm : apRef;
	if (pTarget)
		arResult = NPCAccuracy::GetMultiplier(pTarget);
	return true;
}

bool Cmd_GetExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {
	TESForm* pForm = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pForm);
	return Cmd_GetExtraAccuracyPenaltyMult_Eval(apRef, pForm, nullptr, arResult);
}

bool Cmd_RemoveExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm)) {
		TESForm* pTarget = pForm ? pForm : apRef;
		if (pTarget)
			NPCAccuracy::RemoveMultiplier(pTarget);
	}

	return true;
}

bool Cmd_GetNearestNavMeshTriangle_Execute(COMMAND_ARGS) {
	arResult = 0;

	NiPoint3 kPointToTest;
	uint32_t checkDisabled = 0;
	float zLimit = 0;
	NVSEArrayVar* pointArr = g_arrInterface->CreateArray(nullptr, 0, apScript);
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

	g_arrInterface->AssignCommandResult(pointArr, &arResult);

	return true;
}

bool Cmd_GetPointInNavMesh_Execute(COMMAND_ARGS) {
	arResult = 0;
	NiPoint4 kResult;
	TESObjectCELL* pInterior = TES::GetSingleton()->currentInterior;

	uint32_t uiGridSize = INISettingCollection::General::uGridsToLoad->UInt();

	NiPoint3 kPointToTest;
	uint32_t checkDisabled = 0;
	float zLimit = 0;
	NVSEArrayVar* pointArr = g_arrInterface->CreateArray(nullptr, 0, apScript);

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

	g_arrInterface->AssignCommandResult(pointArr, &arResult);
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
	arResult = 0;
	float fTime = 0;
	TESSound* pSound;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSound, &fTime) && pSound && IS_TYPE(pSound, TESSound)) {
		TESObjectREFR* pRef = apRef;
		if (pRef == nullptr) {
			pRef = PlayerCharacter::GetSingleton();
		}
		if (pRef->Get3DVerySimple()) {
			uint32_t uiFlags = BSAudioManager::kAudioFlags_3D | BSAudioManager::kAudioFlags_100;
			BSSoundHandle kHandle = BSAudio::GetSingleton()->GetSoundHandleByFormID(pSound->GetFormID(), uiFlags);
			kHandle.SetPosition(pRef->GetPosition());
			kHandle.SetObjectToFollow(pRef->Get3DVerySimple());
			uint32_t uiTime = fTime * 1000;
			kHandle.FadeInPlay(uiTime);
			arResult = 1;
		}
	}
	return true;
}

template<typename KEY, typename DATA>
using ScrapMap = std::unordered_map<KEY, DATA, std::hash<KEY>, std::equal_to<KEY>, BSScrapAllocator<std::pair<const KEY, DATA>>>;

bool Cmd_GetTempIngestibleEffects_Execute(COMMAND_ARGS) {
	arResult = 0;
	NVSEArrayVar* pEffArr = g_arrInterface->CreateArray(nullptr, 0, apScript);
	auto pList = PlayerCharacter::GetSingleton()->GetActiveEffectList();
	if (pList && !pList->IsEmpty()) {
		ScrapMap<TESForm*, std::pair<float, float>> kTempEffectMap;
		while (pList && !pList->IsEmpty()) {
			const ActiveEffect* pEffect = pList->GetItem();
			pList = pList->GetNext();
			if (pEffect && pEffect->bActive && !pEffect->bTerminated && pEffect->magicItem && ValidTempEffect(pEffect->effectItem)) {
				TESForm* pForm = DYNAMIC_CAST(pEffect->magicItem, MagicItem, TESForm);
				if (pForm && pForm->GetFormType() == FORM_TYPE::AlchemyItem) {
					const float fTimeLeft = pEffect->duration - pEffect->timeElapsed;
					auto it = kTempEffectMap.find(pForm);
					if (it != kTempEffectMap.end() && it->second.second < pEffect->duration) {
						it->second.first = fTimeLeft;
						it->second.second = pEffect->duration;
					}
					else {
						kTempEffectMap.insert({ pForm, {fTimeLeft, pEffect->duration} });
					}
				}
			}
		}

		if (!kTempEffectMap.empty()) {
			for (auto& effect : kTempEffectMap) {
				NVSEArrayVar* pEffArrInner = g_arrInterface->CreateArray(nullptr, 0, apScript);
				g_arrInterface->AppendElements(pEffArrInner, effect.first, effect.second.first, effect.second.second);
				g_arrInterface->AppendElement(pEffArr, NVSEArrayElement(pEffArrInner));
			}
		}
	}
	g_arrInterface->AssignCommandResult(pEffArr, &arResult);
	return true;
}

bool Cmd_SetCameraShakeNoHUDShudder_Execute(COMMAND_ARGS) {
	float fShakeMult, fTime = 0.f;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fShakeMult, &fTime)) {
		CustomCameraShake::mult = fShakeMult;
		CustomCameraShake::duration = fTime;
		arResult = 1;
	}
	return true;
}

bool Cmd_RewardKarmaAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
	int32_t iDelta = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &iDelta);
	const int32_t iOrgValue = PlayerCharacter::GetSingleton()->GetActorValueI(ActorValue::Index::KARMA);
	const int32_t iKarmaMax = GameSettingCollection::iKarmaMax->Int();
	const int32_t iKarmaMin = GameSettingCollection::iKarmaMin->Int();
	if (iDelta >= 0 && ((iDelta + iOrgValue) > iKarmaMax)) {
		iDelta = iKarmaMax - iOrgValue;
	}
	else if (iDelta < 0 && ((iDelta + iOrgValue) < iKarmaMin)) {
		iDelta = iKarmaMin - iOrgValue;
	}
	if (iDelta != 0) {
		PlayerCharacter::GetSingleton()->PermanentModActorValueI(ActorValue::Index::KARMA, iDelta, nullptr);
		arResult = 1;
	}
	return true;
}

SPEC_INLINE bool Cmd_GetMoonPhase_Eval(COMMAND_ARGS_EVAL) {
	arResult = Moon::eCurrentPhase;
	return true;
}

bool Cmd_GetMoonPhase_Execute(COMMAND_ARGS) {
	return Cmd_GetMoonPhase_Eval(nullptr, nullptr, nullptr, arResult);
}

bool Cmd_GetLandTextureUnderFeet_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* pCell = apRef->GetParentCell();
	if (!pCell || pCell->IsInterior())
		return true;

	TESObjectLAND* pLand = pCell->GetLand();
	if (!pLand)
		return true;

	const NiPoint3& rPos = apRef->GetPosition();
	COORD_DATA kCoordData;
	pLand->GetCoordData(kCoordData, rPos, true);
	TESLandTexture* pTexture = pLand->GetMainTexture(apRef->GetPosition());
	if (pTexture)
		ScriptUtils::SetFormIDResult(arResult, pTexture->GetFormID());
	return true;
}

bool Cmd_RemoveNavmeshObstacle_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (apRef->IsObstacle()) {
		NavMeshObstacleManager::GetSingleton()->RemoveObstacleForReference(apRef);
		arResult = 1;
	}
	return true;
}

bool Cmd_AddNavmeshObstacle_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (apRef->IsObstacle()) {
		NavMeshObstacleManager::GetSingleton()->AddObstacleForReference(apRef);
		arResult = 1;
	}
	return true;
}

bool Cmd_StopSoundLooping_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESSound* pSoundForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSoundForm) && pSoundForm && IS_TYPE(pSoundForm, TESSound)) {
		CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
		BSGameSound* pSound;
		uint32_t uiKey;
		auto kIter = BSAudioManager::Get()->playingSounds.GetFirstPos();
		while (kIter) {
			BSAudioManager::Get()->playingSounds.GetNext(kIter, uiKey, pSound);
			if (!pSound || pSound->sourceSound != pSoundForm)
				continue;

			BSSoundHandle kHandle;
			kHandle.uiSoundID = pSound->mapKey;
			kHandle.Stop();
			arResult = 1;
		}
	}

	return true;
}

bool Cmd_GetPlayingEffectShaders_Execute(COMMAND_ARGS) {
	arResult = 0;
	ListNode<BSTempEffect>* iter = ProcessLists::GetSingleton()->tempEffects.Head();
	MagicShaderHitEffect* effect;
	NVSEArrayVar* effArr = g_arrInterface->CreateArray(nullptr, 0, apScript);

	do {
		effect = (MagicShaderHitEffect*)iter->data;
		if (effect && IS_TYPE(effect, MagicShaderHitEffect) && effect->flags != 1 && effect->target && effect->target->GetFormID() == apRef->GetFormID()) {
			g_arrInterface->AppendElement(effArr, NVSEArrayElement(effect->effectShader));
		}
	} while (iter = iter->next);

	g_arrInterface->AssignCommandResult(effArr, &arResult);
	return true;
}

bool Cmd_GetLocationName_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cLocationName[MAX_PATH] = {};
	if (apRef->GetParentCell() && apRef->GetParentCell()->IsInterior()) {
		strcpy_s(cLocationName, apRef->GetParentCell()->fullName.GetFullName());
	}
	else {
		const TESWorldSpace* pWorld = apRef->GetWorldSpace();
		if (pWorld) {
			BSString strName;
			pWorld->GetMapNameForLocation(strName, apRef->GetPosition());
			strcpy_s(cLocationName, strName.c_str());
		}
	}
	g_strInterface->Assign(PASS_COMMAND_ARGS, cLocationName);
	return true;
}

SPEC_INLINE bool Cmd_GetLocationSpecificLoadScreensOnly_Eval(COMMAND_ARGS_EVAL) {
	arResult = LoadingMenu::bLocationSpecificLoadScreensOnly;
	return true;
}

bool Cmd_GetLocationSpecificLoadScreensOnly_Execute(COMMAND_ARGS) {
	return Cmd_GetLocationSpecificLoadScreensOnly_Eval(nullptr, nullptr, nullptr, arResult);
}

bool __fastcall IsCombatTarget(const Actor* source, const Actor* toSearch) {
	if (source->bIsInCombat && source->pCombatTargets) {
		Actor** actorsArr = source->pCombatTargets->pBuffer;
		uint32_t count = source->pCombatTargets->uiSize;
		if (!actorsArr)
			return false;
		for (; count; count--, actorsArr++) {
			if (*actorsArr == toSearch) return true;
		}
	}
	return false;
}

bool __fastcall IsHostileCompassTarget(const TESObjectREFR* apTarget) {
	auto pIter = PlayerCharacter::GetSingleton()->compassTargets;
	while (pIter && !pIter->IsEmpty()) {
		PlayerCharacter::CompassTarget* pTarget = pIter->GetItem();
		if (pTarget->isHostile && pTarget->target == apTarget)
			return true;

		pIter = pIter->GetNext();
	}
	return false;
}

bool Cmd_IsCrimeOrEnemy_Execute(COMMAND_ARGS) {
	arResult = 0;
	Actor* pActor = static_cast<Actor*>(apRef);
	if (apRef->IsCrimeToActivate() && (!apRef->IsActor() || !pActor->IsPlayerTeammate()) ||
		apRef->IsActor() && (IsCombatTarget(pActor, PlayerCharacter::GetSingleton()) || IsHostileCompassTarget(apRef))) {
		arResult = 1;
	}
	if (IsConsoleMode()) 
		Console_Print("IsCrimeOrEnemy >> %.f", arResult);
	return true;
}

bool Cmd_SendTrespassAlarmAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pOwner = apRef->GetOwner();
	if (pOwner) {
		ThisCall(0x8C0EC0, PlayerCharacter::GetSingleton(), apRef, pOwner, 0xFFFFFFFF); // Actor::TrespassAlarm
		arResult = 1;
	}
	return true;
}

bool Cmd_GetCompassHostiles_Execute(COMMAND_ARGS) {
	arResult = 0;
	BOOL bSkipInvisible = FALSE;
	BOOL bUseImproveDetection = FALSE;

	ExtractArgsEx(EXTRACT_ARGS_EX, &bSkipInvisible, &bUseImproveDetection);

	bool bHasImprovedDetection = false;
	if (bUseImproveDetection) {
		float fHasPerk = 0.f; //copying code at 0x77A0C4
		BGSEntryPoint::HandleEntryPoint(BGSEntryPointType::HAS_IMPROVED_DETECTION, PlayerCharacter::GetSingleton(), &fHasPerk);
		if (fHasPerk > 0.f)
			bHasImprovedDetection = true;
	}

	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);
	auto pIter = PlayerCharacter::GetSingleton()->compassTargets;
	while (pIter && !pIter->IsEmpty()) {
		PlayerCharacter::CompassTarget* pTarget = pIter->GetItem();
		pIter = pIter->GetNext();
		if (pTarget->isHostile) {
			if (bSkipInvisible > 0 && !bHasImprovedDetection && (pTarget->target->GetActorValueI(ActorValue::Index::INVISIBILITY) > 0
				|| pTarget->target->GetActorValueI(ActorValue::Index::CHAMELEON) > 0)) {
				continue;
			}
			g_arrInterface->AppendElement(pArray, NVSEArrayElement(pTarget->target));
		}
	}
	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;
}

bool Cmd_SendStealingAlarm_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectREFR* pContainer = nullptr;
	BOOL bCheckItems = FALSE;
	if (apRef->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &pContainer, &bCheckItems) && pContainer) {
		if (bCheckItems) {
			TESForm* pOwner = pContainer->GetOwner();
			if (!pOwner)
				return true;

			ExtraContainerChanges* pContChanges = apRef->GetExtraData<ExtraContainerChanges>();
			if (!pContChanges || !pContChanges->pChanges || !pContChanges->pChanges->pItems)
				return true;

			BSSimpleList<ItemChange*>* pItemIter = pContChanges->pChanges->pItems->GetHead();
			while (pItemIter && !pItemIter->IsEmpty()){
				ItemChange* pItemChange = pItemIter->GetItem();
				pItemIter = pItemIter->GetNext();

				if (!pItemChange || !pItemChange->GetExtraDataList() || !pItemChange->GetContainerObject())
					continue;

				BSSimpleList<ExtraDataList*>* pExtraIter = pItemChange->GetExtraDataList();
				while (pExtraIter && !pExtraIter->IsEmpty()){
					ExtraDataList* pExtraDataList = pExtraIter->GetItem();
					pExtraIter = pExtraIter->GetNext();
					if (pExtraDataList) {
						ExtraOwnership* pOwnership = pExtraDataList->GetExtraData<ExtraOwnership>();
						if (pOwnership && pOwnership->pOwner && pOwnership->pOwner->GetFormID() == pOwner->GetFormID()) {
							ThisCall(0x8BFA40, apRef, pContainer, nullptr, nullptr, 1, pOwner); // Actor::StealAlarm
							arResult = 1;
							return true;
						}
					}
				}
			}
		}
		else {
			TESForm* pOwner = pContainer->GetOwner();
			ThisCall(0x8BFA40, apRef, pContainer, nullptr, nullptr, 1, pOwner); // Actor::StealAlarm
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetCalculatedSpread_Execute(COMMAND_ARGS) {
	arResult = 0;
	Actor* pActor = static_cast<Actor*>(apRef);
	if (!apRef->IsActor() || !pActor->GetCurrentAIProcess() || pActor->GetCurrentAIProcess()->GetProcessLevel() > PROCESS_TYPE::MIDDLE_HIGH)
		return true;

	ItemChange* pWeaponItem = pActor->GetCurrentAIProcess()->GetCurrentWeapon();
	if (pWeaponItem && pWeaponItem->GetContainerObject()) {
		const bool bDecreaseSpread = pWeaponItem->HasModEffectActive(WEAPON_MOD_EFFECT_TYPE::DECREASE_SPREAD);
		const float fMinSpread = ThisCall<float>(0x524B80, pWeaponItem->GetContainerObject(), bDecreaseSpread); // TESObjectWEAP::GetMinSpread
		const float fWeapSpread = ThisCall<float>(0x524BE0, pWeaponItem->GetContainerObject(), bDecreaseSpread); // TESObjectWEAP::GetMaxSpread
		const float fSpread = ThisCall<float>(0x8B0DD0, pActor, 1); // Actor::GetGunSkill

		float fTotalSpread = (fWeapSpread * fSpread + fMinSpread) * 0.01745329238474369;

		TESAmmo* pAmmo = ThisCall<TESAmmo*>(0x525980, pWeaponItem->GetContainerObject(), pActor); // TESObjectWEAP::GetCurrentAmmo
		fTotalSpread = TESAmmoEffect::ApplyAmmoEffect(AMMO_EFFECT_TYPE::SPREAD, (pAmmo ? pAmmo->GetAmmoEffectList() : nullptr), fTotalSpread);

		float fSpreadPenalty = ThisCall<float>(0x8B0DD0, pActor, 2); // Actor::GetGunSkill

		fTotalSpread += fSpreadPenalty * GameSettingCollection::fNPCMaxGunWobbleAngle->Float() * 0.01745329238474369f;

		fTotalSpread = fTotalSpread + static_cast<MiddleHighProcess*>(pActor->GetCurrentAIProcess())->fAimLooking;

		if (pWeaponItem->HasModEffectActive(WEAPON_MOD_EFFECT_TYPE::SPLIT_BEAM))
			fTotalSpread *= ThisCall<float>(0x4BCF60, pWeaponItem->GetContainerObject(), WEAPON_MOD_EFFECT_TYPE::SPLIT_BEAM, 1); // TESObjectWEAP::GetModEffectValue

		arResult = fTotalSpread;
	}
	if (IsConsoleMode()) 
		Console_Print("GetCalculatedSpread >> %f", arResult);

	return true;
}

bool Cmd_ModNthTempEffectTimeLeft_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t uiIndex;
	float modTimeLeft;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &uiIndex, &modTimeLeft) || !apRef->IsActor()) 
		return true;

	auto pIter = static_cast<Actor*>(apRef)->GetActiveEffectList();
	if (!pIter || pIter->IsEmpty())
		return true;

	while (pIter && !pIter->IsEmpty()) {
		ActiveEffect* pEffect = pIter->GetItem();
		pIter = pIter->GetNext();
		if (!pEffect || !pEffect->bApplied || !ValidTempEffect(pEffect->effectItem) || !pEffect->magicItem ||
			!DYNAMIC_CAST(pEffect->magicItem, MagicItem, TESForm))
			continue;

		if (!uiIndex--) {
			pEffect->timeElapsed += -modTimeLeft;
			if (pEffect->timeElapsed > pEffect->duration)
				pEffect->Remove(true);
			arResult = 1;
			break;
		}
	};
	return true;
}

bool Cmd_IsHostilesNearby_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* pCell = PlayerCharacter::GetSingleton()->GetParentCell();
	if (pCell)
		arResult = ProcessLists::GetSingleton()->AreHostileActorsNear(pCell->IsInterior());
	return true;
}

bool Cmd_ToggleCombatMusic_Execute(COMMAND_ARGS) {
	BOOL bValue = TRUE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &bValue);
	JohnnyPatches::bCombatMusicDisabled = bValue == FALSE;
	return true;
}

bool Cmd_IsCombatMusicEnabled_Execute(COMMAND_ARGS) {
	arResult = JohnnyPatches::bCombatMusicDisabled == false;
	if (IsConsoleMode())
		Console_Print("IsCombatMusicEnabled >> %.f", arResult);
	return true;
}

SPEC_NOINLINE bool Cmd_IsCompassHostile_Eval(COMMAND_ARGS_EVAL) {
	arResult = IsHostileCompassTarget(apRef);
	return true;
}

bool Cmd_IsCompassHostile_Execute(COMMAND_ARGS) {
	Cmd_IsCompassHostile_Eval(apRef, nullptr, nullptr, arResult);
	if (IsConsoleMode()) 
		Console_Print("IsCompassHostile >> %.f", arResult);
	return true;
}

void RestoreDisabledPlayerControlsHUDFlags() {
	HookUtils::SafeWrite32(0x771A53, HUDMainMenu::kXpMeter | HUDMainMenu::kSubtitles | HUDMainMenu::kMessages | HUDMainMenu::kQuestReminder | HUDMainMenu::kRadiationMeter);
}

bool Cmd_SetDisablePlayerControlsHUDVisibilityFlags_Execute(COMMAND_ARGS) {
	uint32_t uiFlags;
	if (NUM_ARGS && ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags)) {
		HookUtils::SafeWrite32(0x771A53, uiFlags);
		HUDMainMenu_SetMenuMode(HUDMainMenu::kHUDState_RECALCULATE);
	}
	else {
		RestoreDisabledPlayerControlsHUDFlags();
	}

	return true;
}

bool Cmd_GetNearestCompassHostile_Execute(COMMAND_ARGS) {
	arResult = -1;

	const NiPoint3& playerPos = PlayerCharacter::GetSingleton()->GetPosition();

	float fSneakMaxDistance = *(float*)(0x11CD7D8 + 4);
	float fSneakExteriorDistanceMult = *(float*)(0x11CDCBC + 4);
	bool isInterior = PlayerCharacter::GetSingleton()->GetParentCell()->IsInterior();
	float interiorDistanceSquared = fSneakMaxDistance * fSneakMaxDistance;
	float exteriorDistanceSquared = (fSneakMaxDistance * fSneakExteriorDistanceMult) * (fSneakMaxDistance * fSneakExteriorDistanceMult);
	float maxDist = isInterior ? interiorDistanceSquared : exteriorDistanceSquared;
	Actor* closestHostile = nullptr;
	uint32_t skipInvisible = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &skipInvisible);
	auto pIter = PlayerCharacter::GetSingleton()->compassTargets;
	while (pIter && !pIter->IsEmpty()) {
		PlayerCharacter::CompassTarget* target = pIter->GetItem();
		pIter = pIter->GetNext();
		if (target->isHostile) {
			if (skipInvisible > 0 && (target->target->GetActorValueI(ActorValue::Index::INVISIBILITY) > 0 || target->target->GetActorValueI(ActorValue::Index::CHAMELEON) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPosition().SqrDistance(playerPos);
			if (distToPlayer < maxDist) {
				maxDist = distToPlayer;
				closestHostile = target->target;
			}
		}
	}

	if (closestHostile)	
		ScriptUtils::SetFormIDResult(arResult, closestHostile->GetFormID());

	return true;
}

double __fastcall GetVectorAngle2D(const NiPoint3& pt) {
	double angle;
	if (pt.y == 0) {
		if (pt.x <= 0) {
			angle = kDblPIx3d2;
		}
		else {
			angle = kDblPId2;
		}
	}
	else {
		double ratio = pt.x / pt.y;
		angle = dAtan(ratio);
		if (pt.y < 0.0) {
			angle += kDblPI;
		}
	}

	return angle;
}


double __fastcall GetAngleBetweenPoints(const NiPoint3& actorPos, const NiPoint3& playerPos, float offset) {
	NiPoint3 diff = actorPos - playerPos;

	double angle = GetVectorAngle2D(diff) - offset;
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
	arResult = -1;

	const NiPoint3& playerPos = PlayerCharacter::GetSingleton()->GetPosition();

	float fSneakMaxDistance = *(float*)(0x11CD7D8 + 4);
	float fSneakExteriorDistanceMult = *(float*)(0x11CDCBC + 4);
	bool isInterior = PlayerCharacter::GetSingleton()->GetParentCell()->IsInterior();
	float maxDist = isInterior ? powf(fSneakMaxDistance, 2) : powf((fSneakMaxDistance * fSneakExteriorDistanceMult), 2);
	Actor* closestHostile = nullptr;
	uint32_t skipInvisible = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &skipInvisible);
	auto pIter = PlayerCharacter::GetSingleton()->compassTargets;
	while (pIter && !pIter->IsEmpty()) {
		PlayerCharacter::CompassTarget* target = pIter->GetItem();
		pIter = pIter->GetNext();

		if (target->isHostile) {
			if (skipInvisible > 0 && (target->target->GetActorValueI(ActorValue::Index::INVISIBILITY) > 0 || target->target->GetActorValueI(ActorValue::Index::CHAMELEON) > 0)) {
				continue;
			}
			auto distToPlayer = target->target->GetPosition().SqrDistance(playerPos);
			if (distToPlayer < maxDist) {
				maxDist = distToPlayer;
				closestHostile = target->target;
			}
		}
	}

	if (closestHostile) {
		auto playerRotation = PlayerCharacter::GetSingleton()->GetHeading(false);
		double headingAngle = GetAngleBetweenPoints(closestHostile->GetPosition(), playerPos, playerRotation);

		// shift the coordinates from -180:180 to 0:360 and offset them (360 / 8 quadrants / 2) degrees
		int angle = headingAngle + 180 + 22.5;

		// convert the angle to which quadrant the NPC is in
		angle /= 45;
		arResult = (angle + 4) % 8; // make 0 in front, 1 front right, 2 right, 3 back right ...
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
	arResult = 0;

	if (!apRef) 
		return true;

	InterfaceManager* interfaceMgr = InterfaceManager::GetSingleton();
	if (!interfaceMgr) 
		return true;

	VATSHighlightData* vatsData = interfaceMgr->GetVATSHighlightData();

	for (uint32_t index = vatsData->numHighlighted; index;) {
		if (vatsData->highlightedRefs[--index].refr != apRef)
			continue;

		if (--vatsData->numHighlighted) {
			if (index == vatsData->numHighlighted) {
				vatsData->highlightedRefs[index].refr = nullptr;
				vatsData->highlightedRefs[index].node = nullptr;
			}
			else {
				vatsData->highlightedRefs[index] = vatsData->highlightedRefs[vatsData->numHighlighted];
			}
			if (vatsData->highlightMain.refr == apRef) {
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

		arResult = 1;
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

SPEC_NOINLINE bool Cmd_GetRunSpeed_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	if (apRef->IsActor())
		arResult = static_cast<Actor*>(apRef)->GetRunSpeed();
	return true;
}

bool Cmd_GetRunSpeed_Execute(COMMAND_ARGS) {
	Cmd_GetRunSpeed_Eval(apRef, nullptr, nullptr, arResult);
	if (IsConsoleMode()) 
		Console_Print("GetRunSpeed >> %.2f", arResult);
	return true;
}

bool Cmd_ToggleNthPipboyLight_Execute(COMMAND_ARGS) {
	uint32_t index, isVisible;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &index, &isVisible) && index < 3) {
		FOPipboyManager* pipboyManager = InterfaceManager::GetSingleton()->pipboyManager;
		if (pipboyManager->byte028 && pipboyManager->pipboyLightGlow[index]) {
			pipboyManager->pipboyLightGlow[index]->SetAppCulled(!isVisible);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_UnsetAV_Execute(COMMAND_ARGS) {
	ActorValue::Index eActorValue;
	arResult = 0;
	if (apRef->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &eActorValue)) {
		Actor* pActor = static_cast<Actor*>(apRef);
		const float fOldVal = pActor->GetActorValueF(eActorValue);

		Modifier* pModifier = pActor->kBaseValueOverrides.GetModifierItem(eActorValue);
		pActor->kBaseValueOverrides.DeleteModifier(pModifier);
		apRef->AddChange(0x400000);

		if (!pActor->IsPlayer()) {
			BaseProcess* pAIProcess = pActor->GetCurrentAIProcess();
			if (pAIProcess)
				pAIProcess->SetCachedActorValueOutOfDate(eActorValue);
		}

		const float fNewVal = pActor->GetActorValueF(eActorValue);
		ActorValue::CheckCallModifiedCallback(pActor, eActorValue, fOldVal, fNewVal, nullptr);
		arResult = 1;
	}
	return true;
}

bool Cmd_UnforceAV_Execute(COMMAND_ARGS) {
	ActorValue::Index eActorValue;
	arResult = 0;
	if (apRef->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &eActorValue)) {
		Actor* pActor = static_cast<Actor*>(apRef);
		const float fOldVal = pActor->GetActorValueF(eActorValue);

		Modifier* pModifier = pActor->kPermanentModifiers.GetModifierItem(eActorValue);
		pActor->kPermanentModifiers.DeleteModifier(pModifier);
		apRef->AddChange(0x800000);

		if (!pActor->IsPlayer()) {
			BaseProcess* pAIProcess = pActor->GetCurrentAIProcess();
			if (pAIProcess)
				pAIProcess->SetCachedActorValueOutOfDate(eActorValue);
		}

		const float fNewVal = pActor->GetActorValueF(eActorValue);
		ActorValue::CheckCallModifiedCallback(pActor, eActorValue, fOldVal, fNewVal, nullptr);
		arResult = 1;
	}
	return true;
}

bool Cmd_StopSoundAlt_Execute(COMMAND_ARGS) {
	TESSound* pSoundForm = nullptr;
	TESObjectREFR* pSource = nullptr;
	float fFadeOutTime = -1;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSoundForm, &pSource, &fFadeOutTime) && pSoundForm && IS_TYPE(pSoundForm, TESSound) && pSource) {
		if (pSoundForm->soundFile.GetSoundFileLength()) {
			CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
			const char* pSoundPath = pSoundForm->soundFile.GetSoundFile();
			uint32_t uiKey;
			auto kObjIter = BSAudioManager::Get()->soundPlayingObjects.GetFirstPos();
			while (kObjIter) {
				NiPointer<NiAVObject> spObject;
				BSAudioManager::Get()->soundPlayingObjects.GetNext(kObjIter, uiKey, spObject);
				if (!spObject || !spObject->IsFadeNode())
					continue;

				BSFadeNode* pFadeNode = static_cast<BSFadeNode*>(spObject.m_pObject);
				if (pFadeNode->pLinkedObj != pSource)
					continue;

				BSGameSound* pSound;
				BSAudioManager::Get()->playingSounds.GetAt(uiKey, pSound);
				if (pSound && StrBeginsCI(pSound->cFilePath + 0xB, pSoundPath)) {
					BSSoundHandle kHandle;
					kHandle.uiSoundID = pSound->mapKey;

					if (fFadeOutTime == -1)
						kHandle.Stop();
					else
						kHandle.FadeOutAndRelease(fFadeOutTime * 1000.0);

					arResult = 1;
					break;
				}
			}
		}
	}
	return true;
}

bool Cmd_SetVelEx_Execute(COMMAND_ARGS) {
	arResult = 0;
	NiPoint3 kVelocity;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kVelocity.x, &kVelocity.y, &kVelocity.z)) {
		CdeclCall(0x62B8D0, apRef->Get3D(), &kVelocity, true); // TESHavokUtilities::AddVelocity
		arResult = 1;
	}
	return true;
}

bool Cmd_ApplyWeaponPoison_Execute(COMMAND_ARGS) {
	//removal support by jazzisparis
	arResult = 0;
	AlchemyItem* pPoison = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pPoison) && (!pPoison || (IS_TYPE(pPoison, AlchemyItem) && pPoison->CanBePoison()))) {
		TESObjectWEAP* pWeapon = nullptr;
		ExtraDataList* pExtraDataList = nullptr;
		if (!apRef->IsActor()) {
			InventoryRef* pInvRef = InventoryRefGetForID(apRef->GetFormID());
			if (!pInvRef || !pInvRef->pForm || pInvRef->pForm->GetFormType() != FORM_TYPE::TESObjectWEAP)
				return true;

			pWeapon = static_cast<TESObjectWEAP*>(pInvRef->pForm);
			pExtraDataList = pInvRef->pExtraDataList;
		}
		else {
			ItemChange* pWeaponItem = ((Actor*)apRef)->GetCurrentAIProcess()->GetCurrentWeapon();
			if (pWeaponItem && pWeaponItem->pExtraLists) {
				pWeapon = static_cast<TESObjectWEAP*>(pWeaponItem->GetContainerObject());
				pExtraDataList = pWeaponItem->pExtraLists->GetItem();
			}
		}

		if (pWeapon && pExtraDataList && (pWeapon->weaponSkill == kAVCode_Unarmed || pWeapon->weaponSkill == kAVCode_MeleeWeapons)) {
			if (pPoison)
				pExtraDataList->SetPoison(pPoison);
			else
				pExtraDataList->RemovePoison();
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_TogglePipBoy_Execute(COMMAND_ARGS) {
	arResult = 0;
	Interface::Menus eMenu = Interface::NoMenu;
	ExtractArgsEx(EXTRACT_ARGS_EX, &eMenu);
	if (eMenu == Interface::NoMenu || eMenu == Interface::Inventory || eMenu == Interface::Stats || eMenu == Interface::PipboyData) {
		InterfaceManager* pMgr = InterfaceManager::GetSingleton();
		if (pMgr) {
			if (pMgr->pipBoyMode == 0)
				pMgr->OpenPipboy(nullptr, eMenu);
			else if (pMgr->pipBoyMode == 3)
				pMgr->ClosePipboy(nullptr);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_ToggleLevelUpMenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	BOOL bValue = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bValue)) {
		DisabledLevelUp::SetShowLevelUpMenu(bValue);
		arResult = 1;
	}
	return true;
}

SPEC_INLINE bool Cmd_IsLevelUpMenuEnabled_Eval(COMMAND_ARGS_EVAL) {
	arResult = DisabledLevelUp::GetShowLevelUpMenu();
	return true;
}

bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS) {
	Cmd_IsLevelUpMenuEnabled_Eval(nullptr, nullptr, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("IsLevelUpMenuEnabled >> %.f", arResult);
	return true;
}

bool Cmd_Jump_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (apRef->IsMobileObject()) {
		static_cast<MobileObject*>(apRef)->Jump();
		arResult = 1;
	}
	return true;
}

bool Cmd_StopVATSCam_Execute(COMMAND_ARGS) {
	ThisCall(0x93E770, PlayerCharacter::GetSingleton(), 2, 0);
	return true;
}

static inline constexpr AddressPtr<float, 0x11DFED4> fCameraShakeMult;
static inline constexpr AddressPtr<float, 0x11DFED8> fCameraShakeCurrentTime;

bool Cmd_SetCameraShake_Execute(COMMAND_ARGS) {
	arResult = 0;
	float fShakeMult, fTime;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fShakeMult, &fTime)) {
		fCameraShakeMult = fShakeMult;
		fCameraShakeCurrentTime = fTime;
		arResult = 1;
	}
	return true;
}

bool Cmd_DisableMuzzleFlashLights_Execute(COMMAND_ARGS) {
	arResult = 0;
	DisabledMuzzleFlashLights::Mode eMode = DisabledMuzzleFlashLights::Mode::NONE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &eMode);
	if (ScriptUtils::InRange(eMode))
		arResult = DisabledMuzzleFlashLights::SetMode(eMode);

	if (IsConsoleMode()) 
		Console_Print("DisableMuzzleFlashLights >> %.f", arResult);
	return true;
}

bool Cmd_ToggleDisableSaves_Execute(COMMAND_ARGS) {
	BOOL bDisable = TRUE;
	uint32_t uiTypeFlags = DisabledSaves::SaveTypeFlags::ALL;
	const TESFile* pFile = apScript->GetFile(0);
	arResult = 0;
	if (pFile && ExtractArgsEx(EXTRACT_ARGS_EX, &bDisable, &uiTypeFlags)) {
		DisabledSaves::Toggle(pFile, uiTypeFlags, bDisable > 0);
		arResult = 1;
	}
	return true;
}

bool Cmd_EjectCasing_Execute(COMMAND_ARGS) {
	arResult = false;
	const char cNodeName[128] = {};
	char cNewCasingPath[MAX_PATH] = {};
	const char* pOrgCasingPath;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cNodeName, &cNewCasingPath)) {
		if (!apRef || !apRef->IsActor())
			return false;

		Actor* pActor = static_cast<Actor*>(apRef);

		TESObjectWEAP* pWeapon = pActor->GetCurrentWeapon();
		if (!pWeapon || pWeapon->IsMelee())
			return false;

		NiAVObject* pActorNode = nullptr;
		if (cNodeName[0] != 0) {
			PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
			if (apRef == pPlayer) {
				pActorNode = pPlayer->Get3D(!pPlayer->is3rdPerson);
			}
			else
				pActorNode = apRef->Get3DVerySimple();
		}

		bool bChangedPos = false;
		NiAVObject* pCasingNode = nullptr;
		NiTransform kOrgTrans;
		if (pActorNode && pActorNode->IsNode()) {
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

		arResult = true;
		return true;
	}
	return false;
}

bool Cmd_PathToRef_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectREFR* pTarget = nullptr;
	float fRadius = -1.f;
	BOOL bFaceTarget = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTarget, &fRadius, &bFaceTarget) && apRef->IsActor()) {
		Actor* pActor = static_cast<Actor*>(apRef);
		if (pTarget) {
			if (!pTarget->IsReference())
				return true;

			if (bFaceTarget)
				arResult = pActor->SetPathfindingGoalAndAngle(pTarget, fRadius);
			else
				arResult = pActor->SetPathfindingGoal(pTarget, fRadius);
		}
		else {
			pActor->StopMoving();
			arResult = 1;
		}
	}

	return true;
}

SPEC_INLINE bool Cmd_GetGrenadeHoldTime_Eval(COMMAND_ARGS_EVAL) {
	arResult = PlayerCharacter::GetSingleton()->timeGrenadeHeld;
	return true;
}

bool Cmd_GetGrenadeHoldTime_Execute(COMMAND_ARGS) {
	Cmd_GetGrenadeHoldTime_Eval(nullptr, nullptr, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("GetGrenadeHoldTime >> %f", arResult);
	return true;
}

bool Cmd_GetWeaponsForMod_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectIMOD* targetMod = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &targetMod) || !targetMod || NOT_ID(targetMod, TESObjectIMOD))
		return true;

	TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
	NVSEArrayVarInterface::Array* weaponArray = g_arrInterface->CreateArray(nullptr, 0, apScript);

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

	g_arrInterface->AssignCommandResult(weaponArray, &arResult);
	if (IsConsoleMode())
		Console_Print("GetWeaponsForMod >> Found %d weapon(s)", g_arrInterface->GetArraySize(weaponArray));

	return true;
}

SPEC_NOINLINE bool Cmd_IsInDialogueWithPlayer_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	if (apRef && apRef->IsActor()) {
		Actor* pActor = static_cast<Actor*>(apRef);
		arResult = pActor->IsInDialogueWithPlayer();
	}
	return true;
}

bool Cmd_IsInDialogueWithPlayer_Execute(COMMAND_ARGS) {
	Cmd_IsInDialogueWithPlayer_Eval(apRef, nullptr, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("IsInDialogueWithPlayer >> %f", arResult);
	return true;
}

bool Cmd_PathToPoint_Execute(COMMAND_ARGS) {
	arResult = 0;
	NiPoint3 kTarget;
	float fFaceAngle = FLT_MAX;
	float fRadius = -1.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kTarget.x, &kTarget.y, &kTarget.z, &fRadius, &fFaceAngle) && apRef->IsActor()) {
		Actor* pActor = static_cast<Actor*>(apRef);
		TESObjectCELL* pCell = TES::GetSingleton()->GetCellForPoint(kTarget);
		if (pCell) {
			TESWorldSpace* pWorld = pCell->GetWorldSpace();
			if (fFaceAngle != FLT_MAX)
				arResult = pActor->SetPathfindingGoalAndAngle(kTarget, pCell, pWorld, fRadius, fFaceAngle);
			else
				arResult = pActor->SetPathfindingGoal(kTarget, pCell, pWorld, fRadius);
		}
	}

	return true;
}

bool Cmd_SetYieldTimer_Execute(COMMAND_ARGS) {
	float fTime;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fTime)) {
		PlayerCharacter::GetSingleton()->fYieldTimer = fTime;
		arResult = 1;
	}
	return true;
}

SPEC_INLINE bool Cmd_GetYieldTimer_Eval(COMMAND_ARGS_EVAL) {
	arResult = PlayerCharacter::GetSingleton()->fYieldTimer;
	return true;
}

bool Cmd_GetYieldTimer_Execute(COMMAND_ARGS) {
	Cmd_GetYieldTimer_Eval(nullptr, nullptr, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("GetYieldTimer >> %f", arResult);
	return true;
}

SPEC_NOINLINE bool Cmd_GetPCInRootWorldspace_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	const TESWorldSpace* pWorldSpace = static_cast<TESWorldSpace*>(apParam1);
	const MapMenu* pMapMenu = MapMenu::GetSingleton();
	if (pWorldSpace && pMapMenu && pMapMenu->parentmostLastExtDoorWorldspace)
		arResult = pWorldSpace->GetFormID() == pMapMenu->parentmostLastExtDoorWorldspace->GetFormID();
	return true;  
}

bool Cmd_GetPCInRootWorldspace_Execute(COMMAND_ARGS) {
	TESWorldSpace* pWorldSpace = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pWorldSpace);
	return Cmd_GetPCInRootWorldspace_Eval(apRef, pWorldSpace, nullptr, arResult);
}

bool Cmd_GetPCRootWorldspace_Execute(COMMAND_ARGS) {
	arResult = 0;
	auto pMapMenu = MapMenu::GetSingleton();
	if (pMapMenu && pMapMenu->parentmostLastExtDoorWorldspace)
		ScriptUtils::SetFormIDResult(arResult, pMapMenu->parentmostLastExtDoorWorldspace->GetFormID());
	return true; 
}
#endif