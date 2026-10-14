#include "fn_gameplay.h"

#include "decoding.h"
#include "GameForms.h"
#include "GameRTTI.h"
#include "GameUI.h"

#include "Bethesda/BGSEntryPoint.hpp"
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/ExtraContainerChanges.hpp"
#include "Bethesda/GameSettingCollection.hpp"
#include "Bethesda/INISettingCollection.hpp"
#include "Bethesda/Moon.hpp"
#include "Bethesda/NavMesh.hpp"
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/PlayerMover.hpp"
#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/TESHavokUtilities.hpp"
#include "Bethesda/TESObject.hpp"
#include "Bethesda/TESObjectList.hpp"
#include "Bethesda/NavMeshObstacleManager.hpp"
#include "Bethesda/TES.hpp"
#include "Bethesda/ProcessLists.hpp"
#include "Bethesda/ActiveEffect.hpp"
#include "Bethesda/MagicShaderHitEffect.hpp"
#include "Bethesda/BGSChangeFlags.hpp"

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
#include <Events/JohnnyEvents.hpp>

#include "NVSE/InventoryRef.hpp"

#include "Shared/BSMemory/BSMemoryUtils.hpp"
#include "Shared/SafeWrite/SafeWrite.hpp"

#include "utility.h"

#include <unordered_map>
#include <span>
#include <mutex>

inline Cmd_Execute Cmd_HighLightBodyPart = reinterpret_cast<Cmd_Execute>(0x5BB570);
inline Cmd_Execute Cmd_DeactivateAllHighlights = reinterpret_cast<Cmd_Execute>(0x5BB6C0);

#define NUM_ARGS *((uint8_t*)scriptData + *opcodeOffsetPtr)

extern InventoryRef* (*InventoryRefGetForID)(FormID refID);

bool Cmd_StopHolotape_Execute(COMMAND_ARGS) {
	*result = 0;
	MapMenu* pMapMenu = MapMenu::GetSingleton();
	if (!pMapMenu)
		return true;

	BOOL bPlayStopSound = FALSE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &bPlayStopSound);

	bNoHolotapeStopSound = bPlayStopSound == FALSE;
	pMapMenu->StopHolotape();
	*result = 1;

	return true;
}

bool Cmd_PlayHolotape_Execute(COMMAND_ARGS) {
	*result = 0;
	MapMenu* pMapMenu = MapMenu::GetSingleton();
	if (!pMapMenu)
		return true;

	BGSNote* pNote = nullptr;
	BOOL bPlayStartStopSound = TRUE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &bPlayStartStopSound) && pNote && IS_TYPE(pNote, BGSNote)) {
		if (pNote->GetNoteType() == BGSNote::Type::VOICE || pNote->GetNoteType() == BGSNote::Type::SOUND) {
			pMapMenu->PlayHolotape(pNote, bPlayStartStopSound > 0);
			*result = 1;
		}
	}

	return true;
}

bool Cmd_SetCasinoWinnings_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCasino* pCasino = nullptr;
	int32_t iEarnings;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &iEarnings) && pCasino && IS_TYPE(pCasino, TESCasino)) {
		const FormID uiFormID = pCasino->GetFormID();
		auto pIter = PlayerCharacter::GetSingleton()->pCasinoData;
		while (pIter && !pIter->IsEmpty()) {
			CasinoData* pStats = pIter->GetItem();
			if (pStats && pStats->uiCasinoFormID == uiFormID) {
				pStats->iEarnings = iEarnings;
				*result = 1;
				return true;
			}
			pIter = pIter->GetNext();
		}

		CasinoData* pStats = BSMemory::malloc<CasinoData>();
		pStats->sEarningsLevel = 0;
		pStats->iEarnings = iEarnings;
		pStats->uiCasinoFormID = uiFormID;
		PlayerCharacter::GetSingleton()->pCasinoData->AddHead(pStats);
	}

	return true;
}

bool Cmd_GetCasinoWinnings_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCasino* pCasino = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino) && pCasino && IS_TYPE(pCasino, TESCasino)) {
		const FormID uiFormID = pCasino->GetFormID();
		auto pIter = PlayerCharacter::GetSingleton()->pCasinoData;
		while (pIter && !pIter->IsEmpty()) {
			const CasinoData* pStats = pIter->GetItem();
			if (pStats && pStats->uiCasinoFormID == uiFormID) {
				*result = pStats->iEarnings;
				return true;
			}
			pIter = pIter->GetNext();
		}
	}

	return true;
}

bool Cmd_GetCasinoDeckTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCasino* pCasino = nullptr;
	uint32_t uiDeck = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &uiDeck) && pCasino && IS_TYPE(pCasino, TESCasino) && uiDeck >= 0 && uiDeck <= 3) {
		const char* pPath = pCasino->kTextures[uiDeck].GetTextureName();
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetCasinoDeckTexture >> %s", pPath);
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
		pCasino->kTextures[uiDeck].SetTextureName(cPath);
		*result = 1;
	}
	return true;
}

bool Cmd_GetCasinoChip_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCasino* pCasino = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino) && pCasino) {
		TESForm* pChip = pCasino->GetChipType();
		if (pChip)
			*reinterpret_cast<FormID*>(result) = pChip->GetFormID();
	}
	return true;
}

bool Cmd_SetCasinoChip_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCasino* pCasino = nullptr;
	TESForm* pChip = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCasino, &pChip) && pCasino && IS_TYPE(pCasino, TESCasino) && pChip && IS_TYPE(pChip, TESCasinoChips)) {
		pCasino->kData.uiCasinoChipID = pChip->GetFormID();
		*result = 1;
	}
	return true;
}

bool Cmd_ClearMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaLocationControllerTweaks::ResetOverride();
	*result = 1;

	return true;
}

bool Cmd_SetMediaLocationControllerOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaLocationController* pCtrl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCtrl) && pCtrl && IS_TYPE(pCtrl, MediaLocationController)) {
		MediaLocationControllerTweaks::SetOverride(pCtrl);
		*result = 1;
	}
	return true;
}

bool Cmd_GetHUDShudderPower_Execute(COMMAND_ARGS) {
	*result = 0;
	const TESFile* pFile = scriptObj->GetFile(0);
	if (pFile)
		*result = CustomHUDShake::Get(pFile);
	return true;
}

bool Cmd_SetHUDShudderPower_Execute(COMMAND_ARGS) {
	*result = 0;
	float fPower = -1.f;
	const TESFile* pFile = scriptObj->GetFile(0);
	if (pFile && ExtractArgsEx(EXTRACT_ARGS_EX, &fPower)) {
		CustomHUDShake::Set(pFile, fPower);
		*result = 1;
	}
	return true;
}


bool Cmd_ClearCustomMapMarker_Execute(COMMAND_ARGS) {
	*result = 0;
	PlayerCharacter::GetSingleton()->RemovePlayerMapMarker();
	*result = 1;
	return true;
}

bool Cmd_SetCustomMapMarker_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 kPos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kPos.x, &kPos.y, &kPos.z)) {
		TESForm* pSpace = nullptr;
		TESObjectCELL* pParentCell = PlayerCharacter::GetSingleton()->GetParentCell();
		if (pParentCell) {
			if (pParentCell->GetInterior())
				pSpace = pParentCell;
			else
				pSpace = pParentCell->GetWorldSpace();
		}
		if (pSpace) {
			PlayerCharacter::GetSingleton()->SetPlayerMapMarker(kPos, pSpace);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_SetActorMovementFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags)) {
		Actor* pActor = PlayerCharacter::GetSingleton();
		if (thisObj)
			pActor = static_cast<Actor*>(thisObj);

		if (pActor->IsActor() && pActor->pActorMover) {
			if (uiFlags)
				pActor->pActorMover->ForceMoveMode(uiFlags);
			else
				pActor->pActorMover->ClearForcedMoveMode();
			*result = 1;
		}
	}
	return true;
}

bool Cmd_SetAlwaysRun_Execute(COMMAND_ARGS) {
	*result = 0;
	int32_t iAlwaysRun = -1;
	BOOL bUpdateFlags = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &iAlwaysRun, &bUpdateFlags);
	if (iAlwaysRun > -1) {
		const bool bAlwaysRun = iAlwaysRun > 0;
		PlayerCharacter::GetSingleton()->bAlwaysRun = bAlwaysRun;
		if (bUpdateFlags) {
			PlayerMover* pMover = static_cast<PlayerMover*>(PlayerCharacter::GetSingleton()->pActorMover);
			auto uiFlags = pMover->uiMoveMode;
			uiFlags.bRunning = bAlwaysRun;
			pMover->ForceMoveMode(uiFlags);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_SetAutoMove_Execute(COMMAND_ARGS) {
	*result = 0;
	int32_t iAutoMove = -1;
	ExtractArgsEx(EXTRACT_ARGS_EX, &iAutoMove);
	if (iAutoMove > -1) {
		PlayerCharacter::GetSingleton()->bAutoMove = iAutoMove > 0;
		*result = 1;
	}
	return true;
}

SPEC_NOINLINE bool Cmd_HasHealthDamageEffect_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj && thisObj->IsActor())
		*result = static_cast<Actor*>(thisObj)->HasDamageHealthEffect();
	return true;
}

bool Cmd_HasHealthDamageEffect_Execute(COMMAND_ARGS) {
	return Cmd_HasHealthDamageEffect_Eval(thisObj, nullptr, nullptr, result);
}

bool Cmd_SetExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {
	*result = 0;
	float fMultiplier = 1.f;
	TESForm* pForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fMultiplier, &pForm)) {
		TESForm* pTarget = pForm ? pForm : thisObj;
		if (pTarget) {
			if (fabs(fMultiplier) < std::numeric_limits<float>::epsilon())
				fMultiplier = std::numeric_limits<float>::epsilon() * 2;

			NPCAccuracy::SetMultiplier(pTarget, fMultiplier);
		}
	}

	return true;
}


SPEC_NOINLINE bool Cmd_GetExtraAccuracyPenaltyMult_Eval(COMMAND_ARGS_EVAL) {
	*result = 1;
	TESForm* pForm = static_cast<TESForm*>(arg1);
	TESForm* pTarget = pForm ? pForm : thisObj;
	if (pTarget)
		*result = NPCAccuracy::GetMultiplier(pTarget);
	return true;
}

bool Cmd_GetExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {
	TESForm* pForm = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pForm);
	return Cmd_GetExtraAccuracyPenaltyMult_Eval(thisObj, pForm, nullptr, result);
}

bool Cmd_RemoveExtraAccuracyPenaltyMult_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm)) {
		TESForm* pTarget = pForm ? pForm : thisObj;
		if (pTarget)
			NPCAccuracy::RemoveMultiplier(pTarget);
	}

	return true;
}

namespace {
	static float __fastcall Sign(const NiPoint3& p1, const NiPoint3& p2, const NiPoint3& p3) {
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	static bool __fastcall PointInTriangle(const NiPoint3& pt, const NiPoint3& v1, const NiPoint3& v2, const NiPoint3& v3) {
		bool b1 = Sign(pt, v1, v2) < 0.0;
		bool b2 = Sign(pt, v2, v3) < 0.0;
		bool b3 = Sign(pt, v3, v1) < 0.0;

		return (b1 == b2) && (b2 == b3);
	}

	static NiPoint3 __fastcall GetTriangleCenter(const NiPoint3& v1, const NiPoint3& v2, const NiPoint3& v3) {
		return NiPoint3((v1.x + v2.x + v3.x) / 3.0f, (v1.y + v2.y + v3.y) / 3.0f, (v1.z + v2.z + v3.z) / 3.0f);
	}

	static bool __fastcall GetClosestNavMeshTriangle(const TESObjectCELL* apCell, const NiPoint4& arPointToTest, bool abCheckDisabled, NiPoint4& arOut) {
		const NavMeshArray* pNavMeshArray = apCell->GetNavMeshArray();
		if (!pNavMeshArray) [[unlikely]]
			return false;

		const NiPoint3 kPointToTest = static_cast<NiPoint3>(arPointToTest);
		const float fZLimit = arPointToTest.w;

		for (uint32_t i = 0; i < pNavMeshArray->GetNavMeshCount(); i++) {
			const NavMeshPtr spNavMesh = pNavMeshArray->GetNavMeshByIndex(i);
			if (!spNavMesh) [[unlikely]]
				continue;

			const NavMeshInfo* pInfo = spNavMesh->pNavMeshInfo;
			if (!pInfo) [[unlikely]]
				continue;

			for (uint32_t j = 0; j < spNavMesh->GetTriangleCount(); j++) {
				const NavMeshTriangle* pNavMeshTriangle = spNavMesh->GetTriangle(j);
				if (abCheckDisabled && pNavMeshTriangle->IsDisabled())
					continue;

				// Get triangle vertices
				NiPoint3 kVerts[3];
				for (uint32_t k = 0; k < 3; k++) {
					const NiPoint3* pVertex = spNavMesh->GetVertex(pNavMeshTriangle->GetVertex(k));
					if (!pVertex) [[unlikely]]
						continue;

					kVerts[k] = *pVertex;
				}


				const NiPoint3 kTriCenter = GetTriangleCenter(kVerts[0], kVerts[1], kVerts[2]);
				if (fZLimit > 0 && fabs(kTriCenter.z - kPointToTest.z) > fZLimit)
					continue;

				// Get distance to triangle center
				float fDist = kPointToTest.SqrDistance(kTriCenter);

				if (fDist < arOut.w) {
					arOut.x = kTriCenter.x;
					arOut.y = kTriCenter.y;
					arOut.z = kTriCenter.z;
					arOut.w = fDist;
				}
			}
		}
		return true;
	}

	static bool __fastcall GetPointNavMesh(const TESObjectCELL* apCell, const NiPoint4& arPointToTest, bool abCheckDisabled, NiPoint4& arOut) {
		NavMeshArray* pNavMeshArray = apCell->GetNavMeshArray();
		if (!pNavMeshArray) [[unlikely]]
			return false;

		const NiPoint3 kPointToTest = static_cast<NiPoint3>(arPointToTest);
		const float fZLimit = arPointToTest.w;

		for (uint32_t i = 0; i < pNavMeshArray->GetNavMeshCount(); i++) {
			const NavMeshPtr spNavMesh = pNavMeshArray->GetNavMeshByIndex(i);
			if (!spNavMesh) [[unlikely]]
				continue;

			NavMeshInfo* pInfo = spNavMesh->pNavMeshInfo;
			if (!pInfo) [[unlikely]]
				continue;

			for (uint32_t j = 0; j < spNavMesh->GetTriangleCount(); j++) {
				const NavMeshTriangle* pNavMeshTriangle = spNavMesh->GetTriangle(j);
				if (!pNavMeshTriangle) [[unlikely]]
					continue;

				if (abCheckDisabled && pNavMeshTriangle->IsDisabled())
					continue;

				// Get triangle vertices
				NiPoint3 kVerts[3];
				for (uint32_t k = 0; k < 3; k++) {
					NiPoint3* pVertex = spNavMesh->GetVertex(pNavMeshTriangle->GetVertex(k));
					if (!pVertex) [[unlikely]]
						continue;

					kVerts[k] = *pVertex;
				}

				// Check if player is inside the triangle
				if (PointInTriangle(kPointToTest, kVerts[0], kVerts[1], kVerts[2])) {
					// Get triangle center
					const NiPoint3 kTriCenter = GetTriangleCenter(kVerts[0], kVerts[1], kVerts[2]);
					if (fZLimit > 0 && fabs(kTriCenter.z - kPointToTest.z) > fZLimit)
						continue;

					// Get distance to triangle center
					float fDist = kPointToTest.SqrDistance(kTriCenter);
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
}

bool Cmd_GetNearestNavMeshTriangle_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint4 kResult = { FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };
	NiPoint4 kPointToTest = { FLT_MAX, FLT_MAX, FLT_MAX, 0.f };
	BOOL bCheckDisabledArg = FALSE;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kPointToTest.x, &kPointToTest.y, &kPointToTest.z, &bCheckDisabledArg, &kPointToTest.w)) {
		const TESObjectCELL* pInterior = TES::GetSingleton()->GetInterior();
		const bool bCheckDisabled = (bCheckDisabledArg > 0);
		if (pInterior) {
			GetClosestNavMeshTriangle(pInterior, kPointToTest, bCheckDisabled, kResult);
		}
		else {
			const uint32_t uiGridSize = TES::GetSingleton()->pGridCellArray->GetDimension();
			for (uint32_t x = 0; x < uiGridSize; x++) {
				for (uint32_t y = 0; y < uiGridSize; y++) {
					TESObjectCELL* pCell = TES::GetSingleton()->GetGridCell(x, y)->pCell;
					if (pCell) [[likely]]
						GetClosestNavMeshTriangle(pCell, kPointToTest, bCheckDisabled, kResult);
				}
			}
		}

		kResult.w = sqrtf(kResult.w);
		g_arrInterface->AppendElements(pArray, kResult.x, kResult.y, kResult.z, kResult.w);
	}

	if (Script::GetConsoleOuput()) [[unlikely]]
		Interface::PrintLine("GetClosestNavMeshTriangle >> Point found at (%f, %f, %f) with distance %f", kResult.x, kResult.y, kResult.z, kResult.w);

	g_arrInterface->AssignCommandResult(pArray, result);

	return true;
}

bool Cmd_GetPointInNavMesh_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint4 kResult = { FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };
	NiPoint4 kPointToTest = { FLT_MAX, FLT_MAX, FLT_MAX, 0.f };
	BOOL bCheckDisabledArg = FALSE;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	bool bResult = false;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kPointToTest.x, &kPointToTest.y, &kPointToTest.z, &bCheckDisabledArg, &kPointToTest.w)) {
		const TESObjectCELL* pInterior = TES::GetSingleton()->GetInterior();
		const bool bCheckDisabled = (bCheckDisabledArg > 0);
		if (pInterior) {
			bResult = GetPointNavMesh(pInterior, kPointToTest, bCheckDisabled, kResult);
		}
		else {
			const uint32_t uiGridSize = TES::GetSingleton()->pGridCellArray->GetDimension();
			for (uint32_t x = 0; x < uiGridSize && !bResult; x++) {
				for (uint32_t y = 0; y < uiGridSize && !bResult; y++) {
					TESObjectCELL* pCell = TES::GetSingleton()->GetGridCell(x, y)->pCell;
					if (pCell) [[likely]]
						bResult = GetPointNavMesh(pCell, kPointToTest, bCheckDisabled, kResult);
				}
			}
		}

		if (bResult) {
			kResult.w = sqrtf(kResult.w);
			g_arrInterface->AppendElements(pArray, kResult.x, kResult.y, kResult.z, kResult.w);
		}
	}

	if (Script::GetConsoleOuput()) [[unlikely]] {
		if (bResult)
			Interface::PrintLine("GetPointInNavMesh >> Point found at (%f, %f, %f) with distance %f", kResult.x, kResult.y, kResult.z, kResult.w);
		else
			Interface::PrintLine("GetPointInNavMesh >> Point not found.");
	}

	g_arrInterface->AssignCommandResult(pArray, result);
	return bResult;
}

bool __fastcall ValidTempEffect(const EffectItem* apEffectItem) {
	if (!apEffectItem || (apEffectItem->GetDuration() <= 0) || !apEffectItem->GetEffectSetting())
		return false;

	const auto eArchetype = apEffectItem->GetEffectSetting()->GetEffectArchetype();
	return eArchetype == EffectArchetypes::Type::VALUE_MODIFIER
		|| (eArchetype == EffectArchetypes::Type::SCRIPT && apEffectItem->GetEffectSetting()->GetFlags().bDisplayEffectName)
		|| (eArchetype >= EffectArchetypes::Type::INVISIBILITY && eArchetype <= EffectArchetypes::Type::DARKNESS)
		|| (eArchetype == EffectArchetypes::Type::PARALYSIS)
		|| (eArchetype >= EffectArchetypes::Type::CONCUSSION);
}

template<typename KEY, typename DATA>
using ScrapMap = std::unordered_map<KEY, DATA, std::hash<KEY>, std::equal_to<KEY>, BSScrapAllocator<std::pair<const KEY, DATA>>>;

bool Cmd_GetTempIngestibleEffects_Execute(COMMAND_ARGS) {
	*result = 0;
	NVSEArrayVar* pEffArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	Actor* pActor = PlayerCharacter::GetSingleton();
	if (thisObj && thisObj->IsActor())
		pActor = static_cast<Actor*>(thisObj);

	auto pList = pActor->GetActiveEffectList();
	if (pList && !pList->IsEmpty()) {
		ScrapMap<TESForm*, std::pair<float, float>> kTempEffectMap;
		while (pList && !pList->IsEmpty()) {
			const ActiveEffect* pEffect = pList->GetItem();
			pList = pList->GetNext();
			if (pEffect && pEffect->IsActive() && !pEffect->IsDone() && pEffect->GetSpell() && ValidTempEffect(pEffect->GetEffectItem())) {
				TESForm* pForm = DYNAMIC_CAST(pEffect->GetSpell(), MagicItem, TESForm);
				if (pForm && pForm->GetFormType() == FORM_TYPE::AlchemyItem) {
					const float fTimeLeft = pEffect->GetDuration() - pEffect->GetElapsedTime();
					auto it = kTempEffectMap.find(pForm);
					if (it != kTempEffectMap.end() && it->second.second < pEffect->GetDuration()) {
						it->second.first = fTimeLeft;
						it->second.second = pEffect->GetDuration();
					}
					else {
						kTempEffectMap.insert({ pForm, {fTimeLeft, pEffect->GetDuration()} });
					}
				}
			}
		}

		if (!kTempEffectMap.empty()) {
			for (auto& effect : kTempEffectMap) {
				NVSEArrayVar* pEffArrInner = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
				g_arrInterface->AppendElements(pEffArrInner, effect.first, effect.second.first, effect.second.second);
				g_arrInterface->AppendElement(pEffArr, NVSEArrayElement(pEffArrInner));
			}
		}
	}
	g_arrInterface->AssignCommandResult(pEffArr, result);
	return true;
}


bool Cmd_SetCameraShakeNoHUDShudder_Execute(COMMAND_ARGS) {
	float fShakeMult, fTime = 0.f;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fShakeMult, &fTime)) {
		CustomCameraShake::mult = fShakeMult;
		CustomCameraShake::duration = fTime;
		*result = 1;
	}
	return true;
}

bool Cmd_RewardKarmaAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	int32_t iDelta = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &iDelta);
	const int32_t iKarmaBefore = PlayerCharacter::GetSingleton()->GetActorValueI(ActorValue::Index::KARMA);
	const int32_t iKarmaMax = GameSettingCollection::iKarmaMax->Int();
	const int32_t iKarmaMin = GameSettingCollection::iKarmaMin->Int();
	if (iDelta >= 0 && ((iDelta + iKarmaBefore) > iKarmaMax)) {
		iDelta = iKarmaMax - iKarmaBefore;
	}
	else if (iDelta < 0 && ((iDelta + iKarmaBefore) < iKarmaMin)) {
		iDelta = iKarmaMin - iKarmaBefore;
	}
	if (iDelta != 0) {
		PlayerCharacter::GetSingleton()->PermanentModActorValueI(ActorValue::Index::KARMA, iDelta, nullptr);
		*result = 1;
	}
	return true;
}

SPEC_INLINE bool Cmd_GetMoonPhase_Eval(COMMAND_ARGS_EVAL) {
	*result = Moon::eCurrentPhase;
	return true;
}

bool Cmd_GetMoonPhase_Execute(COMMAND_ARGS) {
	return Cmd_GetMoonPhase_Eval(nullptr, nullptr, nullptr, result);
}

bool Cmd_GetLandTextureUnderFeet_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* pCell = thisObj->GetParentCell();
	if (!pCell || pCell->GetInterior())
		return true;

	TESObjectLAND* pLand = pCell->GetLand();
	if (!pLand) [[unlikely]]
		return true;

	const NiPoint3 kPos = thisObj->GetLocationOnReference();
	COORD_DATA kCoordData;
	pLand->GetCoordData(kCoordData, kPos, true);
	const TESLandTexture* pTexture = pLand->GetMainTexture(kPos);
	if (pTexture)
		*reinterpret_cast<FormID*>(result) = pTexture->GetFormID();
	return true;
}

bool Cmd_RemoveNavmeshObstacle_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj->IsObstacle()) {
		NavMeshObstacleManager::GetSingleton()->RemoveObstacleForReference(thisObj);
		*result = 1;
	}
	return true;
}

bool Cmd_AddNavmeshObstacle_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj->IsObstacle()) {
		NavMeshObstacleManager::GetSingleton()->AddObstacleForReference(thisObj);
		*result = 1;
	}
	return true;
}

bool Cmd_GetPlayingEffectShaders_Execute(COMMAND_ARGS) {
	*result = 0;
	auto pIter = ProcessLists::GetSingleton()->kMagicEffects.GetHead();
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	while (pIter && !pIter->IsEmpty()) {
		NiPointer<BSTempEffect> spEffect = pIter->GetItem();
		pIter = pIter->GetNext();

		if (!spEffect) [[unlikely]]
			continue;

		MagicShaderHitEffect* pHitEffect = spEffect->NiDynamicCast<MagicShaderHitEffect>();
		if (pHitEffect && pHitEffect->GetFinished() && pHitEffect->GetTarget() == thisObj) {
			g_arrInterface->AppendElement(pArray, NVSEArrayElement(pHitEffect->pEffectShader));
		}
	}

	g_arrInterface->AssignCommandResult(pArray, result);
	return true;
}

bool Cmd_GetLocationName_Execute(COMMAND_ARGS) {
	*result = 0;
	char cLocationName[MAX_PATH] = {};
	if (thisObj->GetParentCell() && thisObj->GetParentCell()->GetInterior()) {
		strcpy_s(cLocationName, thisObj->GetParentCell()->GetFullName());
	}
	else {
		const TESWorldSpace* pWorld = thisObj->GetWorldSpace();
		if (pWorld) {
			BSString strName;
			pWorld->GetMapNameForLocation(strName, thisObj->GetLocationOnReference());
			strcpy_s(cLocationName, strName.c_str());
		}
	}
	g_strInterface->Assign(PASS_COMMAND_ARGS, cLocationName);
	return true;
}

SPEC_INLINE bool Cmd_GetLocationSpecificLoadScreensOnly_Eval(COMMAND_ARGS_EVAL) {
	*result = LoadingMenu::bLocationSpecificLoadScreensOnly;
	return true;
}

bool Cmd_GetLocationSpecificLoadScreensOnly_Execute(COMMAND_ARGS) {
	return Cmd_GetLocationSpecificLoadScreensOnly_Eval(nullptr, nullptr, nullptr, result);
}

bool __fastcall IsHostileCompassTarget(const TESObjectREFR* apTarget) {
	auto pIter = PlayerCharacter::GetSingleton()->pPerceivedActors;
	while (pIter && !pIter->IsEmpty()) {
		PlayerCharacter::PerceivedActor* pTarget = pIter->GetItem();
		if (pTarget->bIsHostile && pTarget->pActor == apTarget)
			return true;

		pIter = pIter->GetNext();
	}
	return false;
}

bool Cmd_IsCrimeOrEnemy_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* pActor = static_cast<Actor*>(thisObj);
	const bool bIsActor = thisObj->IsActor();
	if (thisObj->IsCrimeToActivate() && (!bIsActor || !pActor->IsPlayerTeammate()) || bIsActor && 
		(pActor->IsInCombatWithActor(PlayerCharacter::GetSingleton()) || IsHostileCompassTarget(thisObj))) {
		*result = 1;
	}
	if (Script::GetConsoleOuput()) 
		Interface::PrintLine("IsCrimeOrEnemy >> %.f", *result);
	return true;
}

bool Cmd_SendTrespassAlarmAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pOwner = thisObj->GetOwner();
	if (pOwner) {
		PlayerCharacter::GetSingleton()->TrespassAlarm(thisObj, pOwner, -1);
		*result = 1;
	}
	return true;
}

static bool __fastcall IsActorInvisible(Actor* apActor) {
	if (apActor->GetActorValueI(ActorValue::Index::INVISIBILITY) > 0)
		return true;
	
	if (apActor->GetActorValueI(ActorValue::Index::CHAMELEON) > 0)
		return true;

	return false;
}

bool Cmd_GetCompassHostiles_Execute(COMMAND_ARGS) {
	*result = 0;
	BOOL bSkipInvisibleArg = FALSE;
	BOOL bAccountForImprovedDetection = FALSE; // If player has ImprovedDetection perk effect, then they'll see invisible actors in compass.
	ExtractArgsEx(EXTRACT_ARGS_EX, &bSkipInvisibleArg, &bAccountForImprovedDetection);

	bool bHasImprovedDetection = false;
	if (bAccountForImprovedDetection) {
		float fHasPerk = 0.f; //copying code at 0x77A0C4
		BGSEntryPoint::HandleEntryPoint(BGSEntryPointType::HAS_IMPROVED_DETECTION, PlayerCharacter::GetSingleton(), &fHasPerk);
		if (fHasPerk > 0.f)
			bHasImprovedDetection = true;
	}

	const bool bSkipInvisible = bSkipInvisibleArg > 0;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	auto pIter = PlayerCharacter::GetSingleton()->pPerceivedActors;
	while (pIter && !pIter->IsEmpty()) {
		const PlayerCharacter::PerceivedActor* pTarget = pIter->GetItem();
		pIter = pIter->GetNext();
		if (pTarget->bIsHostile) {
			if (bSkipInvisible && !bHasImprovedDetection && IsActorInvisible(pTarget->pActor))
				continue;
			g_arrInterface->AppendElement(pArray, NVSEArrayElement(pTarget->pActor));
		}
	}
	g_arrInterface->AssignCommandResult(pArray, result);
	return true;
}

bool Cmd_SendStealingAlarm_Execute(COMMAND_ARGS) {
	TESObjectREFR* pContainer;
	BOOL bCheckItems = FALSE;
	*result = 0;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &pContainer, &bCheckItems) && pContainer) {
		Actor* pCaller = static_cast<Actor*>(thisObj);
		TESForm* pContainerOwner = pContainer->GetOwner();
		if (bCheckItems) {
			if (!pContainerOwner)
				return true;

			const InventoryChanges* pInvChanges = InventoryChanges::GetInventoryChanges(thisObj);
			if (!pInvChanges || !pInvChanges->pItems)
				return true;

			const BSSimpleList<ItemChange*>* pItemIter = pInvChanges->pItems->GetHead();
			while (pItemIter && !pItemIter->IsEmpty()) {
				const ItemChange* pItem = pItemIter->GetItem();
				pItemIter = pItemIter->GetNext();

				if (!pItem || !pItem->GetExtraDataList() || !pItem->GetItemObject())
					continue;

				const BSSimpleList<ExtraDataList*>* pExtraIter = pItem->GetExtraDataList();
				while (pExtraIter && !pExtraIter->IsEmpty()) {
					const ExtraDataList* pExtraList = pExtraIter->GetItem();
					pExtraIter = pExtraIter->GetNext();
					if (pExtraList) [[likely]] {
						const TESForm* pOwner = pExtraList->GetOwner();
						if (pOwner && pOwner == pContainerOwner) {
							pCaller->StealAlarm(pContainer, nullptr, 0, 1, pContainerOwner);
							*result = 1;
							return true;
						}
					}
				}
			}
		}
		else {
			pCaller->StealAlarm(pContainer, nullptr, 0, 1, pContainerOwner);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetCalculatedSpread_Execute(COMMAND_ARGS) {
	*result = 0;
	if (!thisObj->IsActor())
		return true;

	Actor* pActor = static_cast<Actor*>(thisObj);
	ItemChange* pWeaponItem = pActor->GetCurrentAIProcess()->GetCurrentWeapon();
	if (pWeaponItem && pWeaponItem->pObject) {
		TESObjectWEAP* pWeapon = static_cast<TESObjectWEAP*>(pWeaponItem->pObject);
		const bool bDecreaseSpread = pWeaponItem->HasModEffectActive(WEAPON_MOD_EFFECT_TYPE::DECREASE_SPREAD);
		const float fMinSpread = pWeapon->GetMinSpread(bDecreaseSpread);
		const float fWeapSpread = pWeapon->GetSpread(bDecreaseSpread);
		const float fGunSkill = pActor->GetGunSkill(GUN_SKILL_TYPE::GUN);

		float fTotalSpread = (fWeapSpread * fGunSkill + fMinSpread) * 0.01745329238474369;

		TESAmmo* pAmmo = pWeapon->GetCurrentAmmo(pActor);
		fTotalSpread = TESAmmoEffect::ApplyAmmoEffect(AMMO_EFFECT_TYPE::SPREAD, (pAmmo ? pAmmo->GetAmmoEffectList() : nullptr), fTotalSpread);

		// Mods hook the 2nd GetGunSkill, so we want to use that
		const uintptr_t uiGetActorGunSkillAddr = HookUtils::GetRelJumpAddr(0x524019);
		float fActorSkill = ThisCall<float>(uiGetActorGunSkillAddr, pActor, GUN_SKILL_TYPE::ACTOR);
		fTotalSpread += fActorSkill * GameSettingCollection::fNPCMaxGunWobbleAngle->Float() * 0.01745329238474369f;

		const float fAimLooking = pActor->GetCurrentAIProcess()->GetAimLooking();
		fTotalSpread = fTotalSpread + fAimLooking;

		const bool bHasSplitBeam = pWeaponItem->HasModEffectActive(WEAPON_MOD_EFFECT_TYPE::SPLIT_BEAM);
		if (bHasSplitBeam)
			fTotalSpread *= pWeapon->GetModEffectValue(WEAPON_MOD_EFFECT_TYPE::SPLIT_BEAM, 1);

		*result = fTotalSpread;
	}
	if (Script::GetConsoleOuput()) 
		Interface::PrintLine("GetCalculatedSpread >> %f", *result);
	return true;
}

bool Cmd_ModNthTempEffectTimeLeft_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t uiIndex = 0;
	float fTimeLeftMod = 0.f;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &uiIndex, &fTimeLeftMod) || !thisObj->IsActor()) 
		return true;

	auto pIter = static_cast<Actor*>(thisObj)->GetActiveEffectList();
	if (!pIter || pIter->IsEmpty())
		return true;

	while (pIter && !pIter->IsEmpty()) {
		ActiveEffect* pEffect = pIter->GetItem();
		pIter = pIter->GetNext();
		if (!pEffect || !pEffect->IsActive() || !ValidTempEffect(pEffect->GetEffectItem()) || !pEffect->GetSpell() || !DYNAMIC_CAST(pEffect->GetSpell(), MagicItem, TESForm))
			continue;

		if (!uiIndex--) {
			pEffect->fElapsedTime += -fTimeLeftMod;
			if (pEffect->GetElapsedTime() > pEffect->GetDuration())
				pEffect->Dispel(true);
			*result = 1;
			break;
		}
	};
	return true;
}

bool Cmd_IsHostilesNearby_Execute(COMMAND_ARGS) {
	*result = 0;
	const TESObjectCELL* pCell = PlayerCharacter::GetSingleton()->GetParentCell();
	if (pCell)
		*result = ProcessLists::GetSingleton()->AreHostileActorsNear(pCell->GetInterior());
	return true;
}

bool Cmd_ToggleCombatMusic_Execute(COMMAND_ARGS) {
	BOOL bValue = TRUE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &bValue);
	JohnnyPatches::bCombatMusicDisabled = bValue == FALSE;
	return true;
}

bool Cmd_IsCombatMusicEnabled_Execute(COMMAND_ARGS) {
	*result = JohnnyPatches::bCombatMusicDisabled == false;
	if (Script::GetConsoleOuput())
		Interface::PrintLine("IsCombatMusicEnabled >> %.f", *result);
	return true;
}

SPEC_NOINLINE bool Cmd_IsCompassHostile_Eval(COMMAND_ARGS_EVAL) {
	*result = IsHostileCompassTarget(thisObj);
	return true;
}

bool Cmd_IsCompassHostile_Execute(COMMAND_ARGS) {
	Cmd_IsCompassHostile_Eval(thisObj, nullptr, nullptr, result);
	if (Script::GetConsoleOuput()) 
		Interface::PrintLine("IsCompassHostile >> %.f", *result);
	return true;
}

void RestoreDisabledPlayerControlsHUDFlags() {
	HookUtils::SafeWrite32(0x771A53, HUDMainMenu::kXpMeter | HUDMainMenu::kSubtitles | HUDMainMenu::kMessages | HUDMainMenu::kQuestReminder | HUDMainMenu::kRadiationMeter);
}

bool Cmd_SetDisablePlayerControlsHUDVisibilityFlags_Execute(COMMAND_ARGS) {
	uint32_t flags;
	if (NUM_ARGS && ExtractArgsEx(EXTRACT_ARGS_EX, &flags)) {
		HookUtils::SafeWrite32(0x771A53, flags);
		HUDMainMenu::SetMenuMode(HUDMainMenu::kHUDState_RECALCULATE);
	}
	else {
		RestoreDisabledPlayerControlsHUDFlags();
	}

	return true;
}

namespace {

	static Actor* __fastcall GetNearestCompassHostile(bool bSkipInvisible) {
		auto pIter = PlayerCharacter::GetSingleton()->pPerceivedActors;
		if (!pIter || pIter->IsEmpty()) [[unlikely]]
			return nullptr;

		const NiPoint3 kPlayerPos = PlayerCharacter::GetSingleton()->GetLocationOnReference();
		const bool bInterior = PlayerCharacter::GetSingleton()->GetParentCell()->GetInterior();

		const float fSneakMaxDistance = GameSettingCollection::fSneakMaxDistance;
		const float fSneakExteriorDistanceMult = GameSettingCollection::fSneakExteriorDistanceMult;
		const float fInteriorDistSqr = fSneakMaxDistance * fSneakMaxDistance;
		const float fExteriorDistSqr = (fSneakMaxDistance * fSneakExteriorDistanceMult) * (fSneakMaxDistance * fSneakExteriorDistanceMult);
		float fMaxDist = bInterior ? fInteriorDistSqr : fExteriorDistSqr;

		Actor* pClosestHostile = nullptr;
		while (pIter && !pIter->IsEmpty()) {
			PlayerCharacter::PerceivedActor* pTarget = pIter->GetItem();
			pIter = pIter->GetNext();

			if (pTarget->bIsHostile) {
				if (bSkipInvisible && IsActorInvisible(pTarget->pActor))
					continue;

				auto distToPlayer = pTarget->pActor->GetLocationOnReference().SqrDistance(kPlayerPos);
				if (distToPlayer < fMaxDist) {
					fMaxDist = distToPlayer;
					pClosestHostile = pTarget->pActor;
				}
			}
		}

		return pClosestHostile;
	}

	static double __fastcall GetVectorAngle2D(const NiPoint3& pt) {
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

	static double __fastcall GetAngleBetweenPoints(const NiPoint3& actorPos, const NiPoint3& playerPos, float offset) {
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

}

bool Cmd_GetNearestCompassHostile_Execute(COMMAND_ARGS) {
	*result = -1;

	BOOL bSkipInvisibleArg = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &bSkipInvisibleArg);

	const Actor* pClosestHostile = GetNearestCompassHostile(bSkipInvisibleArg > 0);
	if (pClosestHostile)
		*reinterpret_cast<FormID*>(result) = pClosestHostile->GetFormID();

	return true;
}

bool Cmd_GetNearestCompassHostileDirection_Execute(COMMAND_ARGS) {
	*result = -1;

	BOOL bSkipInvisibleArg = FALSE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &bSkipInvisibleArg);

	const Actor* pClosestHostile = GetNearestCompassHostile(bSkipInvisibleArg > 0);

	if (pClosestHostile) {
		float fHeading = PlayerCharacter::GetSingleton()->GetHeading(false);
		double dAngle = GetAngleBetweenPoints(pClosestHostile->GetLocationOnReference(), PlayerCharacter::GetSingleton()->GetLocationOnReference(), fHeading);

		// shift the coordinates from -180:180 to 0:360 and offset them (360 / 8 quadrants / 2) degrees
		int iAngle = dAngle + 180 + 22.5;

		// convert the angle to which quadrant the NPC is in
		iAngle /= 45;

		*result = (iAngle + 4) % 8; // make 0 in front, 1 front right, 2 right, 3 back right ...
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

	if (!thisObj) 
		return true;

	InterfaceManager* pUIMgr = InterfaceManager::GetSingleton();
	if (!pUIMgr) 
		return true;

	VATSHighlightData* pVATSEffect = pUIMgr->GetVATSHighlightData();

	for (uint32_t i = pVATSEffect->numHighlighted; i;) {
		if (pVATSEffect->highlightedRefs[--i].refr != thisObj)
			continue;

		if (--pVATSEffect->numHighlighted) {
			if (i == pVATSEffect->numHighlighted) {
				pVATSEffect->highlightedRefs[i].refr = nullptr;
				pVATSEffect->highlightedRefs[i].node = nullptr;
			}
			else {
				pVATSEffect->highlightedRefs[i] = pVATSEffect->highlightedRefs[pVATSEffect->numHighlighted];
			}
			if (pVATSEffect->highlightMain.refr == thisObj) {
				pVATSEffect->highlightMain = pVATSEffect->highlightedRefs[0];
			}
		}
		else {
			pVATSEffect->highlightedRefs[0].refr = nullptr;
			pVATSEffect->highlightedRefs[0].node = nullptr;
			pVATSEffect->highlightMain.refr = nullptr;
			pVATSEffect->highlightMain.node = nullptr;
			pVATSEffect->highlightState = 0;
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

SPEC_NOINLINE bool Cmd_GetRunSpeed_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj->IsActor())
		*result = static_cast<Actor*>(thisObj)->GetRunSpeed();
	return true;
}

bool Cmd_GetRunSpeed_Execute(COMMAND_ARGS) {
	Cmd_GetRunSpeed_Eval(thisObj, nullptr, nullptr, result);
	if (Script::GetConsoleOuput()) 
		Interface::PrintLine("GetRunSpeed >> %.2f", *result);
	return true;
}

bool Cmd_ToggleNthPipboyLight_Execute(COMMAND_ARGS) {
	uint32_t uiIndex = UINT32_MAX;
	BOOL bVisibleArg = FALSE;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiIndex, &bVisibleArg) && uiIndex < 3 && InterfaceManager::GetSingleton()) {
		FOPipboyManager* pPipBoyMgr = InterfaceManager::GetSingleton()->pipboyManager;
		if (pPipBoyMgr->byte028 && pPipBoyMgr->pipboyLightGlow[uiIndex]) {
			const bool bVisible = bVisibleArg > 0;
			pPipBoyMgr->pipboyLightGlow[uiIndex]->SetAppCulled(bVisible);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_UnsetAV_Execute(COMMAND_ARGS) {
	*result = 0;
	ActorValue::Index eActorValue = ActorValue::Index::NONE;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &eActorValue)) {
		Actor* pActor = static_cast<Actor*>(thisObj);
		const float fOldVal = pActor->GetActorValueF(eActorValue);

		Modifier* pModifier = pActor->kBaseValueOverrides.GetModifierItem(eActorValue);
		pActor->kBaseValueOverrides.DeleteModifier(pModifier);
		pActor->AddChange(BGSChangeFlag::ACTOR_OVERRIDE_MODIFIERS);

		if (!pActor->IsPlayer()) {
			BaseProcess* pAIProcess = pActor->GetCurrentAIProcess();
			if (pAIProcess)
				pAIProcess->SetCachedActorValueOutOfDate(eActorValue);
		}

		const float fNewVal = pActor->GetActorValueF(eActorValue);
		auto ePrevMode = JohnnyEvents::SetAVChangeMode(JohnnyEvents::AVChangeMode::SET);
		ActorValue::CheckCallModifiedCallback(pActor, eActorValue, fOldVal, fNewVal, nullptr);
		JohnnyEvents::SetAVChangeMode(ePrevMode);
		*result = 1;
	}
	return true;
}

bool Cmd_UnforceAV_Execute(COMMAND_ARGS) {
	*result = 0;
	ActorValue::Index eActorValue = ActorValue::Index::NONE;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &eActorValue)) {
		Actor* pActor = static_cast<Actor*>(thisObj);
		const float fOldVal = pActor->GetActorValueF(eActorValue);

		Modifier* pModifier = pActor->kPermanentModifiers.GetModifierItem(eActorValue);
		pActor->kPermanentModifiers.DeleteModifier(pModifier);
		pActor->AddChange(BGSChangeFlag::ACTOR_PERMANENT_MODIFIERS);

		if (!pActor->IsPlayer()) {
			BaseProcess* pAIProcess = pActor->GetCurrentAIProcess();
			if (pAIProcess)
				pAIProcess->SetCachedActorValueOutOfDate(eActorValue);
		}

		const float fNewVal = pActor->GetActorValueF(eActorValue);
		auto ePrevMode = JohnnyEvents::SetAVChangeMode(JohnnyEvents::AVChangeMode::SET);
		ActorValue::CheckCallModifiedCallback(pActor, eActorValue, fOldVal, fNewVal, nullptr);
		JohnnyEvents::SetAVChangeMode(ePrevMode);
		*result = 1;
	}
	return true;
}

bool Cmd_SetVelEx_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 kVelocity;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &kVelocity.x, &kVelocity.y, &kVelocity.z)) {
		TESHavokUtilities::AddVelocity(thisObj->Get3D(), kVelocity, true);
		*result = 1;
	}
	return true;
}

bool Cmd_ApplyWeaponPoison_Execute(COMMAND_ARGS) {
	//removal support by jazzisparis
	*result = 0;
	AlchemyItem* pPoison = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pPoison) && (!pPoison || (IS_TYPE(pPoison, AlchemyItem) && pPoison->CanBePoison()))) {
		TESObjectWEAP* pWeapon = nullptr;
		ExtraDataList* pExtraDataList = nullptr;
		if (thisObj->IsActor()) {
			ItemChange* pWeaponItem = static_cast<Actor*>(thisObj)->GetCurrentAIProcess()->GetCurrentWeapon();
			if (pWeaponItem && pWeaponItem->pExtraLists) {
				pWeapon = static_cast<TESObjectWEAP*>(pWeaponItem->pObject);
				pExtraDataList = pWeaponItem->pExtraLists->GetItem();
			}
		}
		else {
			InventoryRef* pInvRef = InventoryRefGetForID(thisObj->GetFormID());
			if (!pInvRef || !pInvRef->pForm || pInvRef->pForm->GetFormType() != FORM_TYPE::TESObjectWEAP)
				return true;

			pWeapon = static_cast<TESObjectWEAP*>(pInvRef->pForm);
			pExtraDataList = pInvRef->pExtraDataList;
		}

		if (pWeapon && pExtraDataList && (pWeapon->GetWeaponSkill() == ActorValue::Index::UNARMED || pWeapon->GetWeaponSkill() == ActorValue::Index::MELEE_WEAPONS)) {
			if (pPoison)
				pExtraDataList->SetPoison(pPoison);
			else
				pExtraDataList->RemovePoison();
			*result = 1;
		}
	}
	return true;
}

bool Cmd_TogglePipBoy_Execute(COMMAND_ARGS) {
	*result = 0;
	Interface::Menus eMenu = Interface::Menus::NoMenu;
	ExtractArgsEx(EXTRACT_ARGS_EX, &eMenu);
	if (eMenu == Interface::Menus::NoMenu || eMenu == Interface::Menus::Inventory || eMenu == Interface::Menus::Stats || eMenu == Interface::Menus::PipboyData) {
		InterfaceManager* pUIMgr = InterfaceManager::GetSingleton();
		if (pUIMgr) {
			if (pUIMgr->pipBoyMode == 0)
				pUIMgr->OpenPipboy(nullptr, eMenu);
			else if (pUIMgr->pipBoyMode == 3)
				pUIMgr->ClosePipboy(nullptr);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_ToggleLevelUpMenu_Execute(COMMAND_ARGS) {
	*result = 0;
	BOOL bValue = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bValue)) {
		DisabledLevelUp::SetShowLevelUpMenu(bValue);
		*result = 1;
	}
	return true;
}

SPEC_INLINE bool Cmd_IsLevelUpMenuEnabled_Eval(COMMAND_ARGS_EVAL) {
	*result = DisabledLevelUp::GetShowLevelUpMenu();
	return true;
}

bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS) {
	Cmd_IsLevelUpMenuEnabled_Eval(nullptr, nullptr, nullptr, result);
	if (Script::GetConsoleOuput())
		Interface::PrintLine("IsLevelUpMenuEnabled >> %.f", *result);
	return true;
}

bool Cmd_Jump_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj->IsMobileObject()) {
		static_cast<MobileObject*>(thisObj)->Jump();
		*result = 1;
	}
	return true;
}

bool Cmd_StopVATSCam_Execute(COMMAND_ARGS) {
	PlayerCharacter::GetSingleton()->ResetKillCam(KILL_CAM_TYPE::VATS, false);
	*result = 1;
	return true;
}

constexpr inline AddressPtr<float, 0x11DFED4> fCameraShakeMult;
constexpr inline AddressPtr<float, 0x11DFED8> fCameraShakeCurrentTime;

bool Cmd_SetCameraShake_Execute(COMMAND_ARGS) {
	*result = 0;
	float fShakeMult;
	float fTime;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fShakeMult, &fTime)) {
		fCameraShakeMult = fShakeMult;
		fCameraShakeCurrentTime = fTime;
		*result = 1;
	}
	return true;
}

bool Cmd_DisableMuzzleFlashLights_Execute(COMMAND_ARGS) {
	*result = 0;
	DisabledMuzzleFlashLights::Mode eMode = DisabledMuzzleFlashLights::Mode::NONE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &eMode);
	if (ScriptUtils::InRange(eMode))
		*result = DisabledMuzzleFlashLights::SetMode(eMode);

	if (Script::GetConsoleOuput()) 
		Interface::PrintLine("DisableMuzzleFlashLights >> %.f", *result);
	return true;
}

bool Cmd_ToggleDisableSaves_Execute(COMMAND_ARGS) {
	BOOL bDisable = TRUE;
	uint32_t uiTypeFlags = DisabledSaves::SaveTypeFlags::ALL;
	const TESFile* pFile = scriptObj->GetFile(0);
	*result = 0;
	if (pFile && ExtractArgsEx(EXTRACT_ARGS_EX, &bDisable, &uiTypeFlags)) {
		DisabledSaves::Toggle(pFile, uiTypeFlags, bDisable > 0);
		*result = 1;
	}
	return true;
}

bool Cmd_EjectCasing_Execute(COMMAND_ARGS) {
	*result = 0;
	if (!thisObj || !thisObj->IsActor())
		return true;

	char cCasingNodeName[MAX_PATH] = {};
	char cNewCasingPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cCasingNodeName, &cNewCasingPath)) {
		Actor* pActor = static_cast<Actor*>(thisObj);

		TESObjectWEAP* pWeapon = pActor->GetCurrentWeapon();
		if (!pWeapon)
			return true;

		NiAVObject* pActorScene = nullptr;
		if (cCasingNodeName[0] != 0)
			pActorScene = ScriptUtils::GetReferenceScene(pActor, false);

		NiPointer<NiAVObject> spOrgCasingNode;
		NiTransform kOrgTrans;
		if (pActorScene) [[likely]] {
			const NiAVObject* pNewCasingNode = BSUtilities::GetObjectByName(pActorScene, cCasingNodeName);
			if (pNewCasingNode) [[likely]] {
				spOrgCasingNode = BSUtilities::GetObjectByName(pActorScene, "ShellCasingNode");
				if (spOrgCasingNode) [[likely]] {
					kOrgTrans = spOrgCasingNode->m_kWorld;

					spOrgCasingNode->m_kWorld = pNewCasingNode->m_kWorld;
				}
			}
		}

		BSString strOrgCasingPath;
		if (cNewCasingPath[0] != 0) {
			strOrgCasingPath = std::move(pWeapon->kShellCasingModel.strModel);
			pWeapon->kShellCasingModel.SetModel(cNewCasingPath);
		}

		pWeapon->EjectShellCasing(pActor);

		if (spOrgCasingNode)
			spOrgCasingNode->m_kWorld = kOrgTrans;

		if (strOrgCasingPath)
			pWeapon->kShellCasingModel.strModel = std::move(strOrgCasingPath);

		*result = 1;
	}
	return true;
}

bool Cmd_PathToRef_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectREFR* pTarget = nullptr;
	float fRadius = -1.f;
	BOOL bFaceTarget = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTarget, &fRadius, &bFaceTarget) && thisObj->IsActor()) {
		Actor* pActor = static_cast<Actor*>(thisObj);
		if (pTarget && pTarget->IsReference()) {
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

SPEC_INLINE bool Cmd_GetGrenadeHoldTime_Eval(COMMAND_ARGS_EVAL) {
	*result = PlayerCharacter::GetSingleton()->fProjectileReleaseTimer;
	return true;
}

bool Cmd_GetGrenadeHoldTime_Execute(COMMAND_ARGS) {
	Cmd_GetGrenadeHoldTime_Eval(nullptr, nullptr, nullptr, result);
	if (Script::GetConsoleOuput())
		Interface::PrintLine("GetGrenadeHoldTime >> %f", *result);
	return true;
}

bool Cmd_GetWeaponsForMod_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectIMOD* pTargetMod = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pTargetMod) || !pTargetMod || NOT_ID(pTargetMod, TESObjectIMOD))
		return true;

	TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
	NVSEArrayVarInterface::Array* weaponArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	pDataHandler->pObjects->ForEach([&](TESObject* apObject) {
		if (apObject->GetFormType() != FORM_TYPE::TESObjectWEAP)
			return;

		TESObjectWEAP* pWeapon = static_cast<TESObjectWEAP*>(apObject);
		for (uint32_t uiSlot = 0; uiSlot < 3; uiSlot++) {
			if (pWeapon->pModObjects[uiSlot] == pTargetMod) {
				g_arrInterface->AppendElement(weaponArray, NVSEArrayElement(pWeapon));
				break;
			}
		}
	});

	g_arrInterface->AssignCommandResult(weaponArray, result);
	if (Script::GetConsoleOuput())
		Interface::PrintLine("GetWeaponsForMod >> Found %d weapon(s)", g_arrInterface->GetArraySize(weaponArray));

	return true;
}

SPEC_NOINLINE bool Cmd_IsInDialogueWithPlayer_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj && thisObj->IsMobileObject()) {
		*result = static_cast<Actor*>(thisObj)->IsInDialogueWithPlayer();
	}
	return true;
}

bool Cmd_IsInDialogueWithPlayer_Execute(COMMAND_ARGS) {
	Cmd_IsInDialogueWithPlayer_Eval(thisObj, nullptr, nullptr, result);
	if (Script::GetConsoleOuput())
		Interface::PrintLine("IsInDialogueWithPlayer >> %f", *result);
	return true;
}

bool Cmd_PathToPoint_Execute(COMMAND_ARGS) {
	*result = 0;
	NiPoint3 kTarget;
	float fFaceAngle = FLT_MAX;
	float fRadius = -1.f;
	if (thisObj->IsActor() && ExtractArgsEx(EXTRACT_ARGS_EX, &kTarget.x, &kTarget.y, &kTarget.z, &fRadius, &fFaceAngle)) {
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

SPEC_INLINE bool Cmd_GetYieldTimer_Eval(COMMAND_ARGS_EVAL) {
	*result = PlayerCharacter::GetSingleton()->fYieldTimer;
	return true;
}

bool Cmd_GetYieldTimer_Execute(COMMAND_ARGS) {
	Cmd_GetYieldTimer_Eval(nullptr, nullptr, nullptr, result);
	if (Script::GetConsoleOuput())
		Interface::PrintLine("GetYieldTimer >> %f", *result);
	return true;
}

SPEC_NOINLINE bool Cmd_GetPCInRootWorldspace_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	const TESWorldSpace* pWorldSpace = static_cast<TESWorldSpace*>(arg1);
	const MapMenu* pMapMenu = MapMenu::GetSingleton();
	if (pWorldSpace && pMapMenu && pMapMenu->parentmostLastExtDoorWorldspace)
		*result = pWorldSpace->GetFormID() == pMapMenu->parentmostLastExtDoorWorldspace->GetFormID();
	return true;  
}

bool Cmd_GetPCInRootWorldspace_Execute(COMMAND_ARGS) {
	TESWorldSpace* pWorldSpace = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pWorldSpace);
	return Cmd_GetPCInRootWorldspace_Eval(thisObj, pWorldSpace, nullptr, result);;
}

bool Cmd_GetPCRootWorldspace_Execute(COMMAND_ARGS) {
	*result = 0;
	auto pMapMenu = MapMenu::GetSingleton();
	if (pMapMenu && pMapMenu->parentmostLastExtDoorWorldspace)
		*reinterpret_cast<FormID*>(result) = pMapMenu->parentmostLastExtDoorWorldspace->GetFormID();
	return true; 
}