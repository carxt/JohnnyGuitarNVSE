#include "fn_form.h"
#ifdef GAME
#include "decoding.h"
#include "events/LambdaVariableContext.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameProcess.h"
#include "GameRTTI.h"
#include "GameSettings.h"
#include "PluginAPI.h"

#include "Bethesda/AILinearTaskThreadManager.hpp"
#include "Bethesda/BSShaderManager.hpp"
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/Calendar.hpp"
#include "Bethesda/ExtraActivateRef.hpp"
#include "Bethesda/ExtraDetachTime.hpp"
#include "Bethesda/ExtraFactionChanges.hpp"
#include "Bethesda/ExtraHotkey.hpp"
#include "Bethesda/ExtraPrimitive.hpp"
#include "Bethesda/ExtraSeenData.hpp"
#include "Bethesda/GrenadeProjectile.hpp"
#include "Bethesda/ModelLoader.hpp"
#include "Bethesda/TESDataHandler.hpp"
#include "Bethesda/TESMain.hpp"
#include "Bethesda/TESObjectList.hpp"

#include "JG/AnimActivationHeight.hpp"
#include "JG/BarterFilter.hpp"
#include "JG/JGSetList.hpp"
#include "JG/JohnnyExtraData.hpp"
#include "JG/LandRemapping.hpp"
#include "JG/ScriptUtils.hpp"
#include "JG/TaskQueue.hpp"
using namespace ScriptUtils;

#include "numbers"
#include "unordered_map"

#include "Shared/BSMemory/BSScrapMemory.hpp"

extern bool (*CallUDF)(class Script* funcScript, class TESObjectREFR* callingObj, uint8_t numArgs, ...);
extern InventoryRef* (*InventoryRefGetForID)(uint32_t refID);

float(*GetWeaponDPS)(ActorValueOwner* avOwner, TESObjectWEAP* weapon, float condition, uint8_t arg4, ItemChange* entry, uint8_t arg6, uint8_t arg7, int arg8, float arg9, float arg10, uint8_t arg11, uint8_t arg12, TESForm* ammo) =
(float(*)(ActorValueOwner*, TESObjectWEAP*, float, uint8_t, ItemChange*, uint8_t, uint8_t, int, float, float, uint8_t, uint8_t, TESForm*))0x645380;


bool Cmd_RemoveNoteQuest_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	TESQuest* pQuest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pQuest) && pNote && IS_TYPE(pNote, BGSNote) && IS_TYPE(pQuest, TESQuest)) {
		pNote->kOwnerQuests.Remove(pQuest);
		arResult = 1;
	}
	return true;
}

bool Cmd_AddNoteQuest_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	TESQuest* pQuest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pQuest) && pNote && IS_TYPE(pNote, BGSNote) && IS_TYPE(pQuest, TESQuest)) {
		pNote->kOwnerQuests.AddHead(pQuest);
		arResult = 1;
	}
	return true;
}
bool Cmd_GetNoteQuestList_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	NVSEArrayVar* pQuests = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote) && !pNote->kOwnerQuests.IsEmpty()) {
		auto pIter = pNote->kOwnerQuests.GetHead();
		while (pIter && !pIter->IsEmpty()) {
			TESQuest* pQuest = pIter->GetItem();
			if (pQuest)
				g_arrInterface->AppendElement(pQuests, NVSEArrayElement(pQuest->GetFormID()));
			pIter = pIter->GetNext();
		}
	}
	g_arrInterface->AssignCommandResult(pQuests, &arResult);
	return true;
}

bool Cmd_SetNoteImage_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &cPath) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESTexture* pImage = pNote->GetNoteImage();
		if (pImage) {
			pImage->SetTextureName(cPath);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetNoteImage_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESTexture* pImage = pNote->GetNoteImage();
		if (pImage)
			g_strInterface->Assign(PASS_COMMAND_ARGS, pImage->GetTextureName());
	}
	return true;
}
bool Cmd_SetNoteTopic_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	TESTopic* pTopic = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pTopic) && pNote && IS_TYPE(pNote, BGSNote) && IS_TYPE(pTopic, TESTopic) && pNote->GetNoteType() == BGSNote::NoteType::VOICE) {
		pNote->SetNoteTopic(pTopic);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetNoteTopic_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESTopic* pTopic = pNote->GetNoteTopic();
		if (pTopic)
			ScriptUtils::SetFormIDResult(arResult, pTopic->GetFormID());
	}
	return true;
}

bool Cmd_SetNoteSound_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	TESSound* pSound = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pSound) && pNote && IS_TYPE(pNote, BGSNote) && pNote->GetNoteType() == BGSNote::NoteType::SOUND) {
		pNote->SetNoteSound(pSound);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetNoteSound_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESSound* pSound = pNote->GetNoteSound();
		if (pSound)
			ScriptUtils::SetFormIDResult(arResult, pSound->GetFormID());
	}
	return true;
}

bool Cmd_SetNoteType_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	BGSNote::NoteType eType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &eType) && pNote && IS_TYPE(pNote, BGSNote) && eType >= BGSNote::NoteType::SOUND && eType <= BGSNote::NoteType::VOICE) {
		pNote->SetNoteType(eType);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetNoteType_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		arResult = pNote->GetNoteType();
	}
	return true;
}

bool Cmd_SetNoteSpeaker_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	TESActorBase* pSpeaker = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pSpeaker) && pNote && IS_TYPE(pNote, BGSNote) && pNote->GetNoteType() == BGSNote::NoteType::VOICE) {
		pNote->SetNoteSpeaker(pSpeaker);
		arResult = 1;
	}
	return true;
}
bool Cmd_GetNoteSpeaker_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESActorBase* pSpeaker = pNote->GetNoteSpeaker();
		if (pSpeaker)
			ScriptUtils::SetFormIDResult(arResult, pSpeaker->GetFormID());
	}
	return true;
}

bool Cmd_GetCurrentFurnitureRef_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (!apRef) 
		return true;

	if (apRef->IsActor()) {
		BaseProcess* pAIProcess = static_cast<Actor*>(apRef)->GetCurrentAIProcess();
		if (pAIProcess) {
			TESObjectREFR* pFurniture = pAIProcess->GetCurrentFurniture();
			if (pFurniture)
				ScriptUtils::SetFormIDResult(arResult, pFurniture->GetFormID());
		}
	}
	return true;
}

bool Cmd_HideItemBarterEx_Execute(COMMAND_ARGS) {
	const TESForm* pItem = nullptr;
	const TESForm* pSeller = nullptr;
	BOOL bAdd = TRUE;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pItem, &bAdd, &uiFlags, &pSeller) && pItem) {
		const uint32_t uiFormID = pItem->GetFormID();
		const uint32_t uiSellerFormID = pSeller ? pSeller->GetFormID() : 0;

		if (bAdd)
			arResult = BarterFilter::Add(uiFormID, uiFlags, uiSellerFormID);
		else
			arResult = BarterFilter::Remove(uiFormID, uiFlags, uiSellerFormID);
	}
	return true;
}

bool Cmd_IsItemBarterHiddenEx_Execute(COMMAND_ARGS) {
	arResult = 0;
	const TESForm* pItem = nullptr;
	const TESForm* pSeller = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pItem, &pSeller) && pItem) {
		const uint32_t uiFormID = pItem->GetFormID();
		const uint32_t uiSellerFormID = pSeller ? pSeller->GetFormID() : 0;

		arResult = BarterFilter::IsHidden(uiFormID, uiSellerFormID);
		if (IsConsoleMode())
			Console_Print("IsItemBarterHiddenEx >> %f", arResult);
	}
	return true;
}

SPEC_NOINLINE bool Cmd_IsRadioRefPlaying_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	if (apRef && apRef->GetObjectReference() && IS_TYPE(apRef->GetObjectReference(), TESObjectACTI)) {
		TESObjectACTI* pActivator = static_cast<TESObjectACTI*>(apRef->GetObjectReference());
		if (pActivator->GetRadioStation())
			arResult = CdeclCall<void*>(0x0832930, apRef) != nullptr;
	}
	return true;
}

bool Cmd_IsRadioRefPlaying_Execute(COMMAND_ARGS) {
	return Cmd_IsRadioRefPlaying_Eval(apRef, nullptr, nullptr, arResult);
}

bool Cmd_TuneRadioRef_Execute(COMMAND_ARGS) {
	BGSTalkingActivator* actiDst = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &actiDst) && apRef && apRef->GetObjectReference() && IS_TYPE(apRef->GetObjectReference(), TESObjectACTI)) {
		TESObjectACTI* actiBase = static_cast<TESObjectACTI*>(apRef->GetObjectReference());
		BGSTalkingActivator * originalTK = actiBase->GetRadioStation();
		if (actiDst == nullptr) {
			actiDst = originalTK;
		}
		if (IS_TYPE(actiDst, BGSTalkingActivator)) {
			auto activateState = CdeclCall<unsigned int>(0x047B250, apRef);
			if ((CdeclCall<void*>(0x0832930, apRef) != nullptr) || (activateState == 1) || (activateState == 2)) { //the exact same logic the game uses
				CdeclCall<void*>(0x08325B0, apRef, 0);
				actiBase->SetRadioStation(actiDst);
				CdeclCall<void*>(0x08325B0, apRef, 1);
				actiBase->SetRadioStation(originalTK);
			}
		}
	}
	return true;
}

bool Cmd_GetFormRecipesAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	NVSEArrayVar* pRecipes = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm) && pForm) {
		auto pIter = TESDataHandler::GetSingleton()->kRecipes.GetHead();
		while (pIter && !pIter->IsEmpty()) {
			TESRecipe* pRecipe = pIter->GetItem();
			if (pRecipe && !pRecipe->GetOutputList()->IsEmpty()) {
				auto pOutputsIter = pRecipe->GetOutputList();
				while (pOutputsIter && !pOutputsIter->IsEmpty()) {
					TESRecipeComponent* pComponent = pOutputsIter->GetItem();
					if (pComponent && pComponent->GetItem() && (pComponent->GetItem()->GetFormID() == pForm->GetFormID())) {
						g_arrInterface->AppendElement(pRecipes, NVSEArrayElement(pRecipe));
						break;
					}
					pOutputsIter = pOutputsIter->GetNext();
				}
			}
			pIter = pIter->GetNext();
		}
	}
	g_arrInterface->AssignCommandResult(pRecipes, &arResult);
	return true;
}

bool Cmd_SetFactionFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESFaction* pFaction = nullptr;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pFaction, &uiFlags) && pFaction && IS_TYPE(pFaction, TESFaction)) {
		pFaction->kData.uiFlags = uiFlags;
		arResult = 1;
	}
	return true;
}

bool Cmd_GetFactionFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESFaction* pFaction = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pFaction) && pFaction && IS_TYPE(pFaction, TESFaction)) {
		arResult = pFaction->kData.uiFlags;
		if (IsConsoleMode())
			Console_Print("GetFactionFlags >> %.f", arResult);
	}
	return true;
}

bool Cmd_RemoveScopeModelPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		TESModel* pModel = nullptr;
		if (pWeapon && pWeapon->HasScope()) {
			pWeapon->kScope.SetModel("");
			arResult = 1;
		}
	}

	return true;
}

bool Cmd_SetLightingTemplateCell_Execute(COMMAND_ARGS) {
	arResult = 0;
	return true;
}

bool Cmd_GetLightingTemplateCell_Execute(COMMAND_ARGS) {
	arResult = 0;
	return true;
}

bool Cmd_SetLightingTemplateTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t traitID = 0;
	BGSLightingTemplate* tmpl = nullptr;
	float value = 0.0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &tmpl, &traitID, &value) && tmpl && IS_TYPE(tmpl, BGSLightingTemplate) && traitID > 0) {
		switch (traitID) {
		case 1:
		case 2:
		case 3:
			tmpl->ambientRGB[traitID - 1] = value;
			break;
		case 4:
		case 5:
		case 6:
			tmpl->directionalRGB[traitID - 4] = value;
			break;
		case 7:
		case 8:
		case 9:
			tmpl->fogRGB[traitID - 7] = value;
			break;
		case 10:
			tmpl->fogNear = value;
			break;
		case 11:
			tmpl->fogFar = value;
			break;
		case 12:
			tmpl->directionalXY = value;
			break;
		case 13:
			tmpl->directionalZ = value;
			break;
		case 14:
			tmpl->directionalFade = value;
			break;
		case 15:
			tmpl->fogClipDist = value;
			break;
		case 16:
			tmpl->fogPower = value;
			break;
		default:
			return true;
		}
	}
	return true;
}

bool Cmd_GetLightingTemplateTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t traitID = 0;
	BGSLightingTemplate* tmpl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &tmpl, &traitID) && tmpl && IS_TYPE(tmpl, BGSLightingTemplate) && traitID > 0) {
		switch (traitID) {
		case 1:
		case 2:
		case 3:
			arResult = tmpl->ambientRGB[traitID - 1];
			break;
		case 4:
		case 5:
		case 6:
			arResult = tmpl->directionalRGB[traitID - 4];
			break;
		case 7:
		case 8:
		case 9:
			arResult = tmpl->fogRGB[traitID - 7];
			break;
		case 10:
			arResult = tmpl->fogNear;
			break;
		case 11:
			arResult = tmpl->fogFar;
			break;
		case 12:
			arResult = tmpl->directionalXY;
			break;
		case 13:
			arResult = tmpl->directionalZ;
			break;
		case 14:
			arResult = tmpl->directionalFade;
			break;
		case 15:
			arResult = tmpl->fogClipDist;
			break;
		case 16:
			arResult = tmpl->fogPower;
			break;
		default:
			return true;
		}
		if (IsConsoleMode()) 
			Console_Print("GetLightingTemplateTraitNumeric %d >> %f", traitID, arResult);
	}
	return true;
}

bool Cmd_SetWorldspaceEncounterZone_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSEncounterZone* pZone = nullptr;
	TESWorldSpace* pWorld = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pWorld, &pZone);
	if (!pWorld || !IS_TYPE(pWorld, TESWorldSpace))
		return true;

	if (!pZone || IS_TYPE(pZone, BGSEncounterZone)) {
		pWorld->pEncounterZone = pZone;
		arResult = 1;
	}
	return true;
}

bool Cmd_GetWorldspaceEncounterZone_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESWorldSpace* pWorld = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWorld) && pWorld && IS_TYPE(pWorld, TESWorldSpace)) {
		BGSEncounterZone* pZone = pWorld->pEncounterZone;
		if (pZone)
			ScriptUtils::SetFormIDResult(arResult, pZone->GetFormID());
	}
	return true;
}

bool Cmd_SetCellEncounterZone_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSEncounterZone* pZone = nullptr;
	TESObjectCELL* pCell = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, &pZone);
	if (!pCell || !IS_TYPE(pCell, TESObjectCELL))
		return true;

	if (!pZone || IS_TYPE(pZone, BGSEncounterZone)) {
		pCell->extraDataList.SetEncounterZone(pZone);
		arResult = 1;
	}
	return true;
}

bool Cmd_SetRefEncounterZone_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSEncounterZone* pZone = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pZone);
	if (!pZone || IS_TYPE(pZone, BGSEncounterZone)) {
		apRef->GetExtra()->SetEncounterZone(pZone);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetRefEncounterZone_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSEncounterZone* pZone = apRef->GetExtra()->GetEncounterZone();
	if (pZone)
		ScriptUtils::SetFormIDResult(arResult, pZone->GetFormID());
	return true;
}

bool Cmd_SetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPrompt[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPrompt)) {
		apRef->GetExtra()->SetActivateTextOverride(cPrompt);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	arResult = 0;
	ExtraActivateRef* pActivateRef = apRef->GetExtraData<ExtraActivateRef>();
	if (pActivateRef) {
		g_strInterface->Assign(PASS_COMMAND_ARGS, pActivateRef->strActivationPrompt.c_str());
		if (IsConsoleMode()) 
			Console_Print("GetRefActivationPromptOverride >> %s", pActivateRef->strActivationPrompt.c_str());
	}
	return true;
}

bool Cmd_GetWeaponAltTextures_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		TESModelTextureSwap* pModel = &pWeapon->textureSwap;
		if (pModel) {
			auto pIter = pModel->GetTexSwapList();
			while (pIter && !pIter->IsEmpty()) {
				TEX_SWAP* pEntry = pIter->GetItem();
				pIter = pIter->GetNext();
				if (pEntry && pEntry->pTextureSet) {
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pEntry->pTextureSet));
				}
			}
		}
	}
	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;
}

bool Cmd_GetIdleMarkerAnimations_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSIdleMarker* pMarker;
	NVSEArrayVar* pIdles = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMarker) && pMarker && IS_TYPE(pMarker, BGSIdleMarker) && pMarker->ucIdleCount > 0) {
		for (int i = 0; i < pMarker->ucIdleCount; i++) {
			g_arrInterface->AppendElement(pIdles, NVSEArrayElement(pMarker->ppIdles[i]));
		}
	}
	g_arrInterface->AssignCommandResult(pIdles, &arResult);
	return true;
}

bool Cmd_SetIdleMarkerAnimation_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSIdleMarker* pMarker = nullptr;
	TESIdleForm* pIdle = nullptr;
	uint32_t uiIndex;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMarker, &uiIndex, &pIdle) && pMarker && IS_TYPE(pMarker, BGSIdleMarker) && pMarker->ucIdleCount > uiIndex) {
		pMarker->ppIdles[uiIndex] = pIdle;
		arResult = 1;
	}
	return true;
}

bool Cmd_SetIdleMarkerAnimations_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSIdleMarker* pMarker = nullptr;
	uint32_t uiArrayID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMarker, &uiArrayID) && pMarker && IS_TYPE(pMarker, BGSIdleMarker)) {
		NVSEArrayVar* pArray = g_arrInterface->LookupArrayByID(uiArrayID);
		if (!pArray)
			return true;

		uint32_t uiSize = g_arrInterface->GetArraySize(pArray);
		if (!uiSize || uiSize > UINT8_MAX)
			return true;

		BSScrapBuffer<NVSEArrayElement> kElements(uiSize);
		g_arrInterface->GetElements(pArray, kElements.get(), nullptr);
		TESIdleForm** ppIdles = BSMemory::malloc<TESIdleForm*>(uiSize);
		for (uint32_t i = 0; i < uiSize; i++) {
			ppIdles[i] = static_cast<TESIdleForm*>(kElements[i].GetTESForm());
		}

		if (pMarker->ppIdles) 
			BSMemory::free(pMarker->ppIdles);

		pMarker->ppIdles = ppIdles;
		pMarker->ucIdleCount = uiSize;
		arResult = 1;
	}

	return true;
}

bool Cmd_GetIdleMarkerTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSIdleMarker* pMarker = nullptr;
	uint32_t uiTrait;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMarker, &uiTrait) && pMarker && IS_TYPE(pMarker, BGSIdleMarker)) {
		switch (uiTrait) {
		case 1:
			arResult = pMarker->ucIdleFlags;
			break;
		case 2:
			arResult = pMarker->fTimerCheckForIdle;
			break;
		case 3:
			arResult = pMarker->ucIdleCount;
			break;
		default:
			return true;
		}
		if (IsConsoleMode()) Console_Print("GetIdleMarkerTraitNumeric %d >> %.2f", uiTrait, arResult);
	}
	return true;
}

bool Cmd_SetIdleMarkerTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSIdleMarker* pMarker = nullptr;
	uint32_t uiTrait;
	float fValue;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMarker, &uiTrait, &fValue) && pMarker && IS_TYPE(pMarker, BGSIdleMarker)) {
		switch (uiTrait) {
		case 1:
			pMarker->ucIdleFlags = fValue;
			break;
		case 2:
			pMarker->fTimerCheckForIdle = fValue;
			break;
		default:
			return true;
		}
		arResult = 1;
	}
	return true;
}

TESModelTextureSwap* __fastcall GetArmorModel(TESObjectARMO* apArmor, uint32_t auiType) {
	switch (auiType) {
	case 1:
		return &apArmor->kBipedModels[0]; // male biped
	case 2:
		return &apArmor->kBipedModels[1]; // female biped
	case 3:
		return &apArmor->kWorldModels[0]; // male world
	case 4:
		return &apArmor->kWorldModels[1]; // female world
	default:
		return nullptr;
	}
}

bool Cmd_GetAltTexturesEx_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	uint32_t uiWhichModel;
	NVSEArrayVar* pMap = g_arrInterface->CreateMap(nullptr, nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &uiWhichModel) && pForm && (IS_TYPE(pForm, TESObjectARMO) || IS_TYPE(pForm, TESObjectWEAP))) {
		TESModelTextureSwap* pModel;
		if (IS_TYPE(pForm, TESObjectARMO)) {
			TESObjectARMO* pArmor = DYNAMIC_CAST(pForm, TESForm, TESObjectARMO);
			pModel = GetArmorModel(pArmor, uiWhichModel);
		}
		else {
			TESObjectWEAP* pWeapon = DYNAMIC_CAST(pForm, TESForm, TESObjectWEAP);
			pModel = &pWeapon->textureSwap;
		}
		if (pModel) {
			auto pIter = pModel->GetTexSwapList();
			while (pIter && !pIter->IsEmpty()) {
				TEX_SWAP* pEntry = pIter->GetItem();
				pIter = pIter->GetNext();
				if (pEntry && pEntry->pTextureSet) {
					g_arrInterface->SetElement(pMap, NVSEArrayElement(pEntry->iObjectIndex), NVSEArrayElement(pEntry->pTextureSet));
				}
			}
		}
	}
	g_arrInterface->AssignCommandResult(pMap, &arResult);
	return true;
}

bool Cmd_GetArmorAltTextures_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectARMO* pArmor = nullptr;
	uint32_t uiWhichModel;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pArmor, &uiWhichModel) && pArmor && IS_TYPE(pArmor, TESObjectARMO)) {
		TESModelTextureSwap* pModel = GetArmorModel(pArmor, uiWhichModel);
		if (pModel) {
			auto pIter = pModel->GetTexSwapList();
			while (pIter && !pIter->IsEmpty()) {
				TEX_SWAP* pEntry = pIter->GetItem();
				pIter = pIter->GetNext();
				if (pEntry && pEntry->pTextureSet) {
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pEntry->pTextureSet));
				}
			}
		}
	}
	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;
}

bool Cmd_SetWeaponAltTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	BGSTextureSet* pTextureSet = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &iIndex, &pTextureSet) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP) && pTextureSet && IS_TYPE(pTextureSet, BGSTextureSet)) {
		TESModelTextureSwap* pModel = &pWeapon->textureSwap;
		if (!pModel)
			return true;

		TEX_SWAP* pSwap = pModel->GetTexSwap(iIndex);
		if (pSwap) {
			pSwap->pTextureSet = pTextureSet;
			arResult = 1;
		}
		else {
			pModel->AddTexSwap("", iIndex, pTextureSet);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_SetArmorAltTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTextureSet* pTextureSet = nullptr;
	TESObjectARMO* pArmor = nullptr;
	int32_t iIndex = -1;
	uint32_t uiWhichModel;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pArmor, &uiWhichModel, &iIndex, &pTextureSet) && pTextureSet && IS_TYPE(pTextureSet, BGSTextureSet) && pArmor && IS_TYPE(pArmor, TESObjectARMO)) {
		TESModelTextureSwap* pModel = GetArmorModel(pArmor, uiWhichModel);
		if (!pModel)
			return true;

		TEX_SWAP* pSwap = pModel->GetTexSwap(iIndex);
		if (pSwap) {
			pSwap->pTextureSet = pTextureSet;
			arResult = 1;
		}
		else {
			pModel->AddTexSwap("", iIndex, pTextureSet);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_ClearWeaponAltTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon;
	int32_t iIndex = -2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &iIndex) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		TESModelTextureSwap* pModel = &pWeapon->textureSwap;
		if (!pModel)
			return true;

		if (iIndex == -1) {
			pModel->ClearTexSwapList();
			arResult = 1;
			return true;
		}
		else {
			pModel->RemoveTexSwap(iIndex);
			arResult = 1;
			return true;
		}
	}
	return true;
}

bool Cmd_ClearArmorAltTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectARMO* pArmor = nullptr;
	int32_t iIndex = -2;
	uint32_t uiWhichModel;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pArmor, &uiWhichModel, &iIndex) && pArmor && IS_TYPE(pArmor, TESObjectARMO)) {
		TESModelTextureSwap* pModel = GetArmorModel(pArmor, uiWhichModel);
		if (!pModel)
			return true;

		if (iIndex == -1) {
			pModel->ClearTexSwapList();
			arResult = 1;
			return true;
		}
		else {
			pModel->RemoveTexSwap(iIndex);
			arResult = 1;
			return true;
		}
	}
	return true;
}

bool Cmd_SetEffectShaderTexturePath_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESEffectShader* pShader = nullptr;
	uint32_t uiTexture;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pShader, &uiTexture, &cPath) && pShader && IS_TYPE(pShader, TESEffectShader) && uiTexture >= 0 && uiTexture <= 2) {
		switch (uiTexture) {
		case 0:
			pShader->SetFillTexture(cPath);
			break;
		case 1:
			pShader->SetParticleTexture(cPath);
			break;
		case 2:
			pShader->SetHolesTexture(cPath);
			break;
		}
		arResult = 1;
	}
	return true;
}

bool Cmd_GetEffectShaderTexturePath_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESEffectShader* pShader = nullptr;
	uint32_t uiTexture;
	const char* pPath = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pShader, &uiTexture) && pShader && IS_TYPE(pShader, TESEffectShader) && uiTexture >= 0 && uiTexture <= 2) {
		switch (uiTexture) {
		case 0:
			pPath = pShader->GetFillTexture()->GetTextureName();
			break;
		case 1:
			pPath = pShader->GetParticleTexture()->GetTextureName();
			break;
		case 2:
			pPath = pShader->GetHolesTexture()->GetTextureName();
			break;
		}
		g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
	}
	return true;
}

uint32_t SwapRGB(uint32_t rgbhex) {
	uint32_t r = (rgbhex >> 0x10) & 0xFF;
	uint32_t g = (rgbhex >> 0x8) & 0xFF;
	uint32_t b = (rgbhex) & 0xFF;
	return (b << 0x10) + (g << 0x8) + r;
}

bool Cmd_SetEffectShaderTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESEffectShader* pShader;
	uint32_t traitID;
	float fValue;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pShader, &traitID, &fValue) && pShader && IS_TYPE(pShader, TESEffectShader) && traitID >= 0 && traitID <= 76) {
		switch (traitID) {
		case 0:
			pShader->GetData()->ucFlags = static_cast<uint8_t>(fValue);
			break;
		case 61:
		{
			TESForm* pFoundForm = TESForm::GetFormByNumericID(fValue);
			if (pFoundForm && IS_TYPE(pFoundForm, BGSDebris))
				pShader->SetAddonModels(static_cast<BGSDebris*>(pFoundForm));
		}
		break;
		case 4:
		case 14:
		case 47:
		case 48:
		case 49:
			((uint32_t*)pShader)[6 + traitID] = SwapRGB((uint32_t)fValue);
			break;
		case 1:
		case 2:
		case 3:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 67:
		case 69:
		case 70:
			((uint32_t*)pShader)[6 + traitID] = (uint32_t)fValue;
			break;
		default:
			((float*)pShader)[6 + traitID] = fValue;
			break;
		}
		arResult = 1;
	}
	return true;
}

bool Cmd_GetEffectShaderTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESEffectShader* pShader;
	uint32_t traitID;
	uint32_t color;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pShader, &traitID) && pShader && IS_TYPE(pShader, TESEffectShader) && traitID >= 0 && traitID <= 76) {
		switch (traitID) {
		case 0:
			arResult = pShader->GetData()->ucFlags;
			break;
		case 61:
			if (pShader->GetAddonModels())
				arResult = pShader->GetAddonModels()->GetFormID();
			break;
		case 4:
		case 14:
		case 47:
		case 48:
		case 49:
			color = SwapRGB(((uint32_t*)pShader)[6 + traitID]);
			arResult = color;
			if (IsConsoleMode()) Console_Print("GetEffectShaderTraitNumeric %d >> 0x%X", traitID, color);
			return true;
			break;
		case 1:
		case 2:
		case 3:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 67:
		case 69:
		case 70:
			arResult = ((uint32_t*)pShader)[6 + traitID];
			break;
		default:
			arResult = ((float*)pShader)[6 + traitID];
			break;
		}
		if (IsConsoleMode()) Console_Print("GetEffectShaderTraitNumeric %d >> %.2f", traitID, arResult);
	}
	return true;
}

bool Cmd_GetAvailablePerks_Execute(COMMAND_ARGS) {
	arResult = 0;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);
	auto pIter = TESDataHandler::GetSingleton()->kPerks.GetHead();
	
	PlayerCharacter* const pPlayer = PlayerCharacter::GetSingleton();
	while (pIter && !pIter->IsEmpty()) {
		BGSPerk* pPerk = pIter->GetItem();
		if (pPerk->GetLevel() > 0) {
			uint8_t ucRank = pPlayer->GetPerkRank(pPerk, 0);
			if (ucRank < pPerk->GetNumRanks() && !pPerk->GetIsTrait() && pPerk->IsPerkAttainable(pPlayer) && pPerk->GetIsPlayable()) {
				if (pPerk->IsPerkAvailable(pPlayer) && pPerk->GetLevel() <= pPlayer->GetLevel())
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pPerk));
			}
		}
		pIter = pIter->GetNext();
	}
	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;
}

bool Cmd_FaceGenRefreshAppearance_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (apRef && apRef->IsCharacter()) {
		ThisCall(0x08D3FA0, apRef);
		arResult = 1;
	}
	return true;
}

bool Cmd_FaceGenGetNthProperty_Execute(COMMAND_ARGS) {
	TESNPC* npc = nullptr;
	uint32_t PropertyListIndex = 0;
	uint32_t PropertyIndex = 0;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &npc, &PropertyListIndex, &PropertyIndex) && npc && IS_TYPE(npc, TESNPC) && PropertyListIndex < 3) {

		uintptr_t propertyListMinorIdx = PropertyListIndex % 2;
		uintptr_t propertyListMajorIdx = (PropertyIndex - propertyListMinorIdx) / 2;
		if (auto FaceGenPTR = npc->GetOffsetFaceCoord()) {
			arResult = CdeclCall<float>(0x652230, FaceGenPTR, propertyListMajorIdx, propertyListMinorIdx, PropertyIndex);
			if (IsConsoleMode())
				Console_Print("GetFaceGenNthProperty %.2f", arResult);
		}
	}
	return true;
}

bool Cmd_FaceGenSetNthProperty_Execute(COMMAND_ARGS) {
	TESNPC* npc = nullptr;
	uint32_t PropertyListIndex = 0;
	uint32_t PropertyIndex = 0;
	float val = 0;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &npc, &PropertyListIndex, &PropertyIndex, &val) && npc && IS_TYPE(npc, TESNPC) && PropertyListIndex < 3) {
		uintptr_t propertyListMinorIdx = PropertyListIndex % 2;
		uintptr_t propertyListMajorIdx = (PropertyIndex - propertyListMinorIdx) / 2;

		if (auto FaceGenPTR = npc->GetOffsetFaceCoord()) {
			CdeclCall<void>(0x652320, FaceGenPTR, propertyListMajorIdx, PropertyListIndex, PropertyIndex, val);
			arResult = 1;
			if (IsConsoleMode())
				Console_Print("SetFaceGenNthProperty called");
		}
	}
	return true;
}

bool Cmd_GetPlayerKarmaTitle_Execute(COMMAND_ARGS) {
	arResult = 0;
	const char* pTitle = nullptr;
	uint32_t uiTitleOrTier = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &uiTitleOrTier);
	if (uiTitleOrTier == 1) {
		uint32_t uiAlignment = TESActorBaseData::GetAlignmentForKarma(PlayerCharacter::GetSingleton()->GetActorValueF(ActorValue::Index::KARMA));
		switch (uiAlignment) {
		case 0:
			pTitle = GameSettingCollection::sAlignGood->String();
			break;
		case 1:
			pTitle = GameSettingCollection::sAlignNeutral->String();
			break;
		case 2:
			pTitle = GameSettingCollection::sAlignEvil->String();
			break;
		case 3:
			pTitle = GameSettingCollection::sAlignVeryGood->String();
			break;
		case 4:
			pTitle = GameSettingCollection::sAlignVeryEvil->String();
			break;
		}
	}
	else {
		pTitle = TESActorBaseData::GetKarmicTitle(PlayerCharacter::GetSingleton());
	}
	if (IsConsoleMode()) 
		Console_Print("GetPlayerKarmaTitle >> %s", pTitle);
	g_strInterface->Assign(PASS_COMMAND_ARGS, pTitle);
	return true;
}

bool Cmd_GetTalkingActivatorActor_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTalkingActivator* pActivator = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pActivator) && pActivator && IS_TYPE(pActivator, BGSTalkingActivator)) {
		if (pActivator->GetTempRef())
			ScriptUtils::SetFormIDResult(arResult, pActivator->GetTempRef()->GetFormID());

		if (IsConsoleMode()) 
			Console_Print("GetTalkingActivatorActor >> 0x%X", arResult);
	}
	return true;
}

bool Cmd_GetActorEffectType_Execute(COMMAND_ARGS) {
	arResult = 0;
	SpellItem* pSpell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSpell) && pSpell && IS_TYPE(pSpell, SpellItem)) {
		arResult = pSpell->kData.eType;
		if (IsConsoleMode()) 
			Console_Print("GetActorEffectType >> %.2f", arResult);
	}
	else {
		arResult = -1;
	}
	return true;
}

bool Cmd_GetBodyPartTraitString_Execute(COMMAND_ARGS) {
	const char* resStr = nullptr;
	BGSBodyPartData* pPartData = nullptr;
	BODY_PART_TYPE ePart;
	uint32_t eType;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pPartData, &ePart, &eType) && pPartData) {
		if (IS_ID(pPartData, BGSBodyPartData) && InRange(ePart) && (eType <= 5)) {
			if (const BGSBodyPart* bodyPart = pPartData->GetBodyPart(ePart)) {
				switch (eType) {
				case 1:
					if (bodyPart->strNodeName.GetLength()) 
						resStr = bodyPart->GetNodeName();
					break;
				case 2:
					if (bodyPart->strTargetName.GetLength()) 
						resStr = bodyPart->GetTargetName();
					break;
				case 3:
					if (bodyPart->strIKStartNodeName.GetLength()) 
						resStr = bodyPart->GetIKStartNodeName();
					break;
				case 4:
					if (bodyPart->strPartName.GetLength()) 
						resStr = bodyPart->GetPartName();
					break;
				case 5:
					if (bodyPart->strGoreObjectName.GetLength()) 
						resStr = bodyPart->GetGoreObjectName();
					break;
				default:
					break;
				}
			}
		}
		g_strInterface->Assign(PASS_COMMAND_ARGS, resStr);
	}
	return true;
}

bool Cmd_GetMessageIconPath_Execute(COMMAND_ARGS) {
	TESForm* pForm = nullptr;
	SEX eSex = SEX::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &eSex) && pForm) {
		TESBipedModelForm* pBipedModel = DYNAMIC_CAST(pForm, TESForm, TESBipedModelForm);
		const char* pPath = nullptr;
		if (pBipedModel) {
			pPath = pBipedModel->kMessageIcons[eSex].GetMessageIconTextureName();
		}
		else {
			BGSMessageIcon* pIcon = DYNAMIC_CAST(pForm, TESForm, BGSMessageIcon);
			if (pIcon)
				pPath = pIcon->GetMessageIconTextureName();
		}
		if (IsConsoleMode()) 
			Console_Print("GetMessageIconPath >> %s", pPath);
		g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
	}
	return true;
}

bool Cmd_SetMessageIconPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	TESForm* form = nullptr;
	SEX eSex = SEX::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &form, &eSex) && form) {
		TESBipedModelForm* pBipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (pBipedModel) {
			pBipedModel->kMessageIcons[eSex].SetMessageIconTextureName(cPath);
			arResult = 1;
		}
		else {
			BGSMessageIcon* pIcon = DYNAMIC_CAST(form, TESForm, BGSMessageIcon);
			if (pIcon) {
				pIcon->SetMessageIconTextureName(cPath);
				arResult = 1;
			}
		}
	}
	return true;
}

bool Cmd_SetNoteRead_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSNote* pNote = nullptr;
	BOOL bRead = FALSE;
	BOOL bSave = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &bRead, &bSave) && pNote) {
		if (bSave)
			pNote->SetHasBeenRead(bRead > 0);
		else
			pNote->bHasBeenRead = bRead > 0;
		arResult = 1;
	}
	return true;
}

bool Cmd_GetQuestDelay_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESQuest* pQuest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pQuest) && pQuest && IS_TYPE(pQuest, TESQuest)) {
		arResult = pQuest->kData.fQuestDelayTime;
		if (IsConsoleMode()) 
			Console_Print("GetQuestDelay >> %.3f", arResult);
	}
	return true;
}

bool Cmd_GetWeaponVATSTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	uint32_t traitID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &traitID) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		switch (traitID) {
		case 1:
			arResult = pWeapon->vatsSkill;
			break;
		case 2:
			arResult = pWeapon->vatsDamMult;
			break;
		case 3:
			arResult = pWeapon->vatsAP;
			break;
		case 4:
			arResult = pWeapon->isSilent;
			break;
		case 5:
			arResult = pWeapon->modRequired;
			break;
		}
		if (IsConsoleMode()) Console_Print("GetWeaponVATSTraitNumeric %d >> %f", traitID, arResult);
	}
	return true;
}

bool Cmd_SetWeaponVATSTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	uint32_t traitID = 0;
	float fValue;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &traitID, &fValue) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		arResult = 1;
		switch (traitID) {
		case 1:
			pWeapon->vatsSkill = fValue;
			break;
		case 2:
			pWeapon->vatsDamMult = fValue;
			break;
		case 3:
			pWeapon->vatsAP = fValue;
			break;
		case 4:
			pWeapon->isSilent = (fValue > 0 ? 1 : 0);
			break;
		case 5:
			pWeapon->modRequired = (fValue > 0 ? 1 : 0);
			break;
		default:
			arResult = 0;
			break;
		}
	}
	return true;
}

SPEC_NOINLINE bool Cmd_GetQuestFailed_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	TESQuest* pQuest = static_cast<TESQuest*>(apParam1);
	if (pQuest && pQuest->IsType<TESQuest>())
		arResult = pQuest->GetFailed();
	return true;
}

bool Cmd_GetQuestFailed_Execute(COMMAND_ARGS) {
	TESQuest* pQuest = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pQuest);
	Cmd_GetQuestFailed_Eval(nullptr, pQuest, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("GetQuestFailed >> %.2f", arResult);
	return true;
}

bool Cmd_GetWeaponWorldModelPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		const char* pPath = pWeapon->kWorldModel.GetModel();
		g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
		if (IsConsoleMode()) 
			Console_Print("GetWeaponWorldModelPath >> %s", pPath);
	}
	return true;
}

bool Cmd_SetWeaponWorldModelPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &cPath) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		pWeapon->kWorldModel.SetModel(cPath);
		arResult = 1;
	}
	return true;
}

bool Cmd_SetProjectileSound_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSProjectile* pProjectile = nullptr;
	TESSound* pSound = nullptr;
	uint32_t uiSoundType = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pProjectile, &uiSoundType, &pSound) && pProjectile && IS_TYPE(pProjectile, BGSProjectile) && pSound && IS_TYPE(pSound, TESSound) && uiSoundType <= 3) {
		arResult = 1;
		switch (uiSoundType) {
		case 1:
			pProjectile->kData.pSoundProjectile = pSound;
			break;
		case 2:
			pProjectile->kData.pSoundCountDown = pSound;
			break;
		case 3:
			pProjectile->kData.pSoundDisable = pSound;
			break;
		default:
			arResult = 0;
			break;
		}
	}
	return true;
}

bool Cmd_SetExplosionSound_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSExplosion* pExplosion = nullptr;
	TESSound* pSound = nullptr;
	uint32_t uiSoundType = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pExplosion, &uiSoundType, &pSound) && pExplosion && IS_TYPE(pExplosion, BGSExplosion) && pSound && IS_TYPE(pSound, TESSound) && uiSoundType <= 2) {
		if (uiSoundType == 1)
			pExplosion->SetSound1(pSound);
		else
			pExplosion->SetSound2(pSound);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetCreatureCombatSkill_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESCreature* pCreature = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pCreature)) 
		return true;
	
	if (!pCreature && apRef && apRef->IsCreature())
		pCreature = static_cast<TESCreature*>(apRef->GetOriginalObjectReference());

	if (pCreature && IS_TYPE(pCreature, TESCreature))
		arResult = pCreature->kData.ucCombatSkill;
	return true;
}

bool Cmd_SetContainerSound_Execute(COMMAND_ARGS) {
	int32_t iSoundType = -1;
	TESObjectCONT* pContainer = nullptr;
	TESSound* pSound = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pContainer, &iSoundType, &pSound) && pContainer && IS_TYPE(pContainer, TESObjectCONT) && pSound && IS_TYPE(pSound, TESSound)) {
		arResult = 1;
		switch (iSoundType) {
		case 0:
			pContainer->SetOpenSound(pSound);
			break;
		case 1:
			pContainer->SetCloseSound(pSound);
			break;
		case 2:
			pContainer->SetLoopSound(pSound);
			break;
		default:
			arResult = 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetContainerSound_Execute(COMMAND_ARGS) {
	arResult = 0;
	int32_t iSoundType = -1;
	TESObjectCONT* pContainer = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pContainer, &iSoundType) && pContainer && IS_TYPE(pContainer, TESObjectCONT)) {
		switch (iSoundType) {
		case 0:
			if (pContainer->GetOpenSound()) 
				ScriptUtils::SetFormIDResult(arResult, pContainer->GetOpenSound()->GetFormID());
			break;
		case 1:
			if (pContainer->GetCloseSound()) 
				ScriptUtils::SetFormIDResult(arResult, pContainer->GetCloseSound()->GetFormID());
			break;
		case 2:
			if (pContainer->GetLoopSound()) 
				ScriptUtils::SetFormIDResult(arResult, pContainer->GetLoopSound()->GetFormID());
			break;
		}
	}
	return true;
}

bool Cmd_GetRaceFlag_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESRace* pRace = nullptr;
	uint32_t uiBit;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &uiBit) && pRace && IS_TYPE(pRace, TESRace)) {
		arResult = pRace->kData.uiFlags.GetBit(uiBit);
		if (IsConsoleMode())
			Console_Print("GetRaceFlag >> %.f", arResult);
	}
	return true;
}

bool Cmd_SetRaceFlag_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESRace* pRace = nullptr;
	uint32_t uiBit;
	BOOL bSet;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &uiBit, &bSet) && pRace && IS_TYPE(pRace, TESRace)) {
		pRace->kData.uiFlags.SetBit(uiBit, bSet);
		arResult = 1;
	}
	return true;
}

// 0 - alive, 1 - dying/ragdolled, 2 - dead, 3 - unconscious, 5 - restrained, 6 - essential unconscious
SPEC_NOINLINE bool Cmd_GetLifeState_Eval(COMMAND_ARGS_EVAL) {
	arResult = -1;
	if (apRef && apRef->IsActor())
		arResult = static_cast<Actor*>(apRef)->GetLifeState();
	return true;
}

bool Cmd_GetLifeState_Execute(COMMAND_ARGS) {
	Cmd_GetLifeState_Eval(apRef, nullptr, nullptr, arResult);
	if (IsConsoleMode()) 
		Console_Print("GetLifeState >> %.f", arResult);
	return true;
}

bool Cmd_GetFactionMembers_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESFaction* pFaction = nullptr;
	int32_t iRank = -1;
	NVSEArrayVar* factionMemberArr = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pFaction, &iRank) && pFaction) {
		TESDataHandler::GetSingleton()->pObjects->ForEach([&](TESObject* apObject) {
			if (!apObject || !apObject->IsActorBase())
				return;

			TESActorBase* pActorBase = static_cast<TESActorBase*>(apObject);
			if (pActorBase->GetFactionList()->IsEmpty())
				return;

			auto pIter = pActorBase->GetFactionList();
			while (pIter && !pIter->IsEmpty()) {
				FactionRank* pRank = pIter->GetItem();
				pIter = pIter->GetNext();
				if (pRank && pRank->pFaction == pFaction && (iRank == -1 || iRank == pRank->cRank))
					g_arrInterface->AppendElement(factionMemberArr, NVSEArrayElement(pActorBase));
			}
		});
	}
	g_arrInterface->AssignCommandResult(factionMemberArr, &arResult);
	return true;
}

bool Cmd_SetEquipType_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	BGSEquipType::Type eEquipType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &eEquipType) && pForm && eEquipType < BGSEquipType::Type::COUNT) {
		pForm = GetTESForm(pForm);
		BGSEquipType* pEquipType = DYNAMIC_CAST(pForm, TESForm, BGSEquipType);
		if (pEquipType) {
			pEquipType->SetEquipType(eEquipType);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetRaceHeadModelPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESRace* pRace = nullptr;
	TESRace::HeadPart eHeadPart;
	SEX eSex = SEX::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &eHeadPart, &eSex) && pRace && IS_TYPE(pRace, TESRace)) {
		if (InRange(eSex) && eHeadPart < TESRace::HeadPart::COUNT) {
			const TESModel* pModel = pRace->GetHeadPartModel(eSex, eHeadPart);
			if (pModel) {
				const char* pPath = pModel->GetModel();
				g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
				if (IsConsoleMode())
					Console_Print("GetRaceHeadModelPath %i %i >> %s", eHeadPart, eSex, pPath);
			}
		}
	}
	return true;
}

bool Cmd_GetRaceBodyModelPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESRace* pRace = nullptr;
	TESRace::BodyPart eBodyPart;
	SEX eSex = SEX::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &eBodyPart, &eSex) && pRace && IS_TYPE(pRace, TESRace)) {
		if (InRange(eSex) && eBodyPart < TESRace::BodyPart::COUNT) {
			const TESModel* pModel = pRace->GetBodyPartModel(eSex, eBodyPart);
			if (pModel) {
				const char* pPath = pModel->GetModel();
				g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
				if (IsConsoleMode())
					Console_Print("GetRaceHeadModelPath %i %i >> %s", eBodyPart, eSex, pPath);
			}
		}
	}
	return true;
}

bool Cmd_GetFacegenModelFlag_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectARMO* pArmor = nullptr;
	uint32_t uiBit;
	SEX eSex = SEX::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pArmor, &uiBit, &eSex) && pArmor && IS_TYPE(pArmor, TESObjectARMO)) {
		if (InRange(eSex) && uiBit < 8) {
			arResult = pArmor->kBipedModels[eSex].ucFlags.GetBit(uiBit);
			if (IsConsoleMode()) {
				Console_Print("GetFacegenModelFlag %i %i >> %.f", uiBit, eSex, arResult);
			}
		}
	}
	return true;
}

bool Cmd_SetFacegenModelFlag_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectARMO* pArmor = nullptr;
	uint32_t uiBit;
	SEX eSex = SEX::NONE;
	BOOL bEnable;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pArmor, &uiBit, &eSex, &bEnable) && pArmor && IS_TYPE(pArmor, TESObjectARMO) && uiBit < 8) {
		pArmor->kBipedModels[eSex].ucFlags.SetBit(uiBit, bEnable);
		arResult = 1;
	}
	return true;
}

SPEC_NOINLINE bool Cmd_GetBaseScale_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	TESActorBase* pBase = reinterpret_cast<TESActorBase*>(apParam1);
	if (pBase) {
		const FORM_TYPE eType = pBase->GetFormType();
		if (eType == FORM_TYPE::TESNPC)
			arResult = static_cast<TESNPC*>(pBase)->GetHeight();
		else if (eType == FORM_TYPE::TESCreature)
			arResult = static_cast<TESCreature*>(pBase)->GetBaseScale();
	}
	else if (apRef) {
		arResult = apRef->GetScale();
	}
	return true;
}

bool Cmd_GetBaseScale_Execute(COMMAND_ARGS) {
	TESActorBase* pBase = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pBase);
	Cmd_GetBaseScale_Eval(apRef, pBase, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("GetBaseScale : %0.2f", arResult);
	return true;
}

bool Cmd_RemovePrimitive_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (apRef->HasExtra<ExtraPrimitive>()) {
		apRef->GetExtra()->RemoveExtra<ExtraPrimitive>();
		UpdateReference3D(apRef);
		arResult = 1;
	}
	return true;
}
bool Cmd_GetPrimitiveType_Execute(COMMAND_ARGS) {
	ExtraPrimitive* pPrimitive = apRef->GetExtraData<ExtraPrimitive>();
	arResult = (pPrimitive && pPrimitive->pPrimitive) ? pPrimitive->pPrimitive->type : 0;
	return true;
}

bool Cmd_GetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusicType = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusicType) && pMusicType && IS_TYPE(pMusicType, BGSMusicType)) {
		const char* pPath = pMusicType->GetSoundFile();
		g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
		if (IsConsoleMode())
			Console_Print("GetMusicTypePath >> %s", pPath);
	}
	return true;
}

bool Cmd_SetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusicType = nullptr;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusicType, &cPath) && pMusicType && IS_TYPE(pMusicType, BGSMusicType)) {
		pMusicType->SetSoundFile(cPath);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusicType = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusicType) && pMusicType && IS_TYPE(pMusicType, BGSMusicType)) {
		arResult = pMusicType->fAttenuation;
		if (IsConsoleMode())
			Console_Print("GetMusicTypeDB >> %f", arResult);
	}
	return true;
}

bool Cmd_SetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusicType = nullptr;
	float fValue = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusicType, &fValue) && pMusicType && IS_TYPE(pMusicType, BGSMusicType)) {
		pMusicType->fAttenuation = fValue;
		arResult = 1;
	}
	return true;
}

// JIP function with a fix for detrimental effects, deprecated
bool Cmd_GetActorValueModifierAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
	return true;
}

// JIP function with a sanity check to prevent errors, deprecated
bool Cmd_GetBufferedCellsAlt_Execute(COMMAND_ARGS) {
	arResult = 0;
	return true;
}

bool Cmd_SetWeapon1stPersonModel_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	int32_t iType = -1;
	TESObjectSTAT* pModel = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &iType, &pModel) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP) && (!pModel || IS_TYPE(pModel, TESObjectSTAT)) && iType <= 7) {
		arResult = 1;
		switch (iType) {
		case 0:
			pWeapon->worldStatic = pModel;
			break;
		case 1:
			pWeapon->modStatics[0] = pModel;
			break;
		case 2:
			pWeapon->modStatics[1] = pModel;
			break;
		case 3:
			pWeapon->modStatics[3] = pModel;
			break;
		case 4:
			pWeapon->modStatics[2] = pModel;
			break;
		case 5:
			pWeapon->modStatics[5] = pModel;
			break;
		case 6:
			pWeapon->modStatics[4] = pModel;
			break;
		case 7:
			pWeapon->modStatics[6] = pModel;
			break;
		default:
			arResult = 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetWeapon1stPersonModel_Execute(COMMAND_ARGS) {
	TESObjectWEAP* pWeapon = nullptr;
	int32_t iType = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &iType) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP) && iType <= 7) {
		FormID uiFormID = 0;
		switch (iType) {
		case 0:
			uiFormID = pWeapon->worldStatic ? pWeapon->worldStatic->GetFormID() : 0;
			break;
		case 1:
			uiFormID = pWeapon->modStatics[0] ? pWeapon->modStatics[0]->GetFormID() : 0;
			break;
		case 2:
			uiFormID = pWeapon->modStatics[1] ? pWeapon->modStatics[1]->GetFormID() : 0;
			break;
		case 3:
			uiFormID = pWeapon->modStatics[3] ? pWeapon->modStatics[3]->GetFormID() : 0;
			break;
		case 4:
			uiFormID = pWeapon->modStatics[2] ? pWeapon->modStatics[2]->GetFormID() : 0;
			break;
		case 5:
			uiFormID = pWeapon->modStatics[5] ? pWeapon->modStatics[5]->GetFormID() : 0;
			break;
		case 6:
			uiFormID = pWeapon->modStatics[4] ? pWeapon->modStatics[4]->GetFormID() : 0;
			break;
		case 7:
			uiFormID = pWeapon->modStatics[6] ? pWeapon->modStatics[6]->GetFormID() : 0;
			break;
		}

		ScriptUtils::SetFormIDResult(arResult, uiFormID);
	}
	return true;
}

bool Cmd_GetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* pModifier = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pModifier) && pModifier && IS_TYPE(pModifier, TESImageSpaceModifier)) {
		arResult = pModifier->kData.bAnimatable;
		if (IsConsoleMode())
			Console_Print("GetIMODAnimatable >> %.f", arResult);
	}
	return true;
}

bool Cmd_SetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* pModifier = nullptr;
	BOOL bVal = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pModifier, &bVal) && pModifier && IS_TYPE(pModifier, TESImageSpaceModifier) && (bVal == 0 || bVal == 1)) {
		pModifier->kData.bAnimatable = bVal;
		arResult = 1;
	}
	return true;
}

// A modified version of GetCalculatedWeaponDamage, all credits go to JazzIsParis
bool Cmd_GetCalculatedWeaponDPS_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectWEAP* pWeapon = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon)) 
		return true;

	PlayerCharacter* const pPlayer = PlayerCharacter::GetSingleton();
	if (!pPlayer->GetCurrentAIProcess() || pPlayer->GetCurrentAIProcess()->GetProcessLevel() > PROCESS_TYPE::MIDDLE_HIGH)
		return true;

	float fCondition = 1.f;
	ExtraDataList* pExtraData = nullptr;
	if (!pWeapon) {
		if (!apRef) 
			return true;

		InventoryRef* pInvRef = InventoryRefGetForID(apRef->GetFormID());
		if (!pInvRef) {
			if (apRef->GetObjectReference() && apRef->GetObjectReference()->GetFormType() == FORM_TYPE::TESObjectWEAP)
				pWeapon = static_cast<TESObjectWEAP*>(apRef->GetObjectReference());
			else
				return true;

			fCondition = apRef->GetHealth();
		}
		else {
			if (pInvRef->pForm && pInvRef->pForm->GetFormType() != FORM_TYPE::TESObjectWEAP)
				return true;

			pWeapon = static_cast<TESObjectWEAP*>(pInvRef->pForm);

			if (pInvRef->pExtraDataList) {
				fCondition = pInvRef->pItemChange->GetItemHealth(true) / 100.f;
				pExtraData = pInvRef->pExtraDataList;
			}
		}
	}
	else if (pWeapon->GetFormType() != FORM_TYPE::TESObjectWEAP) {
		return true;
	}

	MiddleHighProcess* pAIProcess = static_cast<MiddleHighProcess*>(pPlayer->GetCurrentAIProcess());
	ItemChange* pWeaponItem = pAIProcess->pCurrentWeapon;
	TESForm* pAmmo = nullptr;
	if (!pExtraData && pWeaponItem && (pWeaponItem->GetContainerObject() == pWeapon) && pAIProcess->pCurrentAmmo)
		pAmmo = pAIProcess->pCurrentAmmo->GetContainerObject();

	if (!pAmmo)
		pAmmo = pWeapon->GetAmmo();

	pAIProcess->pCurrentWeapon = nullptr;
	arResult = GetWeaponDPS(pPlayer, pWeapon, fCondition, 1, pWeaponItem, 0, 0, -1, 0.f, 0.f, 0, 0, pAmmo);
	pAIProcess->pCurrentWeapon = pWeaponItem;
	if (IsConsoleMode())
		Console_Print("GetCalculatedWeaponDPS >> %f", arResult);
	return true;
}

bool Cmd_IsCellVisited_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* pCell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		ExtraSeenData* pSeenData = pCell->extraDataList.GetExtraData<ExtraSeenData>();
		if (pSeenData && pSeenData->pSeenData)
			arResult = 1;
		if (IsConsoleMode())
			Console_Print("IsCellVisited >> %.0f", arResult);
	}
	return true;
}

bool Cmd_IsCellExpired_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* pCell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		const ExtraDetachTime* pDetachTime = pCell->extraDataList.GetExtraData<ExtraDetachTime>();
		const uint32_t uiDetachTime = pDetachTime ? pDetachTime->uiTime : 0;
		if (uiDetachTime == 0) {
			arResult = -1;
		}
		else if (uiDetachTime == uint32_t(-1) || uiDetachTime == uint32_t(-2)) { // -1 is used by ResetInterior, -2 by ShowOff's ResetInteriorAlt.
			arResult = 1;
		}
		else {
			const uint32_t uiHoursToRespawnCell = GameSettingCollection::iHoursToRespawnCell->Int();
			const uint32_t uiGameHoursPassed = Calendar::GetSingleton()->GetHoursPassed();
			arResult = (uiGameHoursPassed - uiDetachTime) >= uiHoursToRespawnCell;
		}
		if (IsConsoleMode())
			Console_Print("IsCellExpired >> %.0f", arResult);
	}
	return true;
}

bool Cmd_GetBaseEffectAV_Execute(COMMAND_ARGS) {
	arResult = -1;
	EffectSetting* pEffect = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pEffect) && pEffect && IS_TYPE(pEffect, EffectSetting)) {
		if (pEffect->GetEffectArchetype() == EffectArchetypes::Type::VALUE_MODIFIER && pEffect->GetAssociatedActorValue()){
			arResult = pEffect->GetAssociatedActorValue();
		}
	}
	return true;
}

bool Cmd_GetBaseEffectArchetype_Execute(COMMAND_ARGS) {
	arResult = -1;
	EffectSetting* pEffect = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pEffect) && pEffect && IS_TYPE(pEffect, EffectSetting))
		arResult = pEffect->GetEffectArchetype();
	return true;
}

bool Cmd_GetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* cell = nullptr;
	int traitID = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &traitID) && cell && IS_TYPE(cell, TESObjectCELL)) {
		if (!cell->IsInterior() || traitID < 0 || traitID > 15) return true;
		TESObjectCELL::LightingData* lightingData = cell->coords.interior;
		switch (traitID) {
		case 0:
			arResult = lightingData->ambientRGB.r;
			break;
		case 1:
			arResult = lightingData->ambientRGB.g;
			break;
		case 2:
			arResult = lightingData->ambientRGB.b;
			break;
		case 3:
			arResult = lightingData->directionalRGB.r;
			break;
		case 4:
			arResult = lightingData->directionalRGB.g;
			break;
		case 5:
			arResult = lightingData->directionalRGB.b;
			break;
		case 6:
			arResult = lightingData->directionalRotXY;
			break;
		case 7:
			arResult = lightingData->directionalRotZ;
			break;
		case 8:
			arResult = lightingData->directionalFade;
			break;
		case 9:
			arResult = lightingData->fogRGB.r;
			break;
		case 10:
			arResult = lightingData->fogRGB.g;
			break;
		case 11:
			arResult = lightingData->fogRGB.b;
			break;
		case 12:
			arResult = lightingData->fogNear;
			break;
		case 13:
			arResult = lightingData->fogFar;
			break;
		case 14:
			arResult = lightingData->fogPower;
			break;
		case 15:
			arResult = lightingData->fogClipDist;
			break;
		default:
			return true;
		}
		if (IsConsoleMode())
			Console_Print("GetInteriorLightingTraitNumeric %d >> %.2f", traitID, arResult);
	}
	return true;
}

bool Cmd_SetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* pCell = nullptr;
	int traitID = -1;
	float value = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, &traitID, &value) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		if (!pCell->IsInterior() || traitID < 0 || traitID > 15) return true;
		TESObjectCELL::LightingData* lightingData = pCell->coords.interior;
		arResult = 1;
		switch (traitID) {
		case 0:
			lightingData->ambientRGB.r = value;
			break;
		case 1:
			lightingData->ambientRGB.g = value;
			break;
		case 2:
			lightingData->ambientRGB.b = value;
			break;
		case 3:
			lightingData->directionalRGB.r = value;
			break;
		case 4:
			lightingData->directionalRGB.g = value;
			break;
		case 5:
			lightingData->directionalRGB.b = value;
			break;
		case 6:
			lightingData->directionalRotXY = value;
			break;
		case 7:
			lightingData->directionalRotZ = value;
			break;
		case 8:
			lightingData->directionalFade = value;
			break;
		case 9:
			lightingData->fogRGB.r = value;
			break;
		case 10:
			lightingData->fogRGB.g = value;
			break;
		case 11:
			lightingData->fogRGB.b = value;
			break;
		case 12:
			lightingData->fogNear = value;
			break;
		case 13:
			lightingData->fogFar = value;
			break;
		case 14:
			lightingData->fogPower = value;
			break;
		case 15:
			lightingData->fogClipDist = value;
			break;
		default:
			arResult = 0;
			return true;
		}
		if (IsConsoleMode())
			Console_Print("SetInteriorLightingTraitNumeric %d >> %.2f", traitID, value);
	}
	return true;
}

bool Cmd_GetHotkeySlot_Execute(COMMAND_ARGS) {
	arResult = 0;

	if (!apRef)
		return true;

	InventoryRef* pInvRef = InventoryRefGetForID(apRef->GetFormID());
	if (!pInvRef || pInvRef->pContainerRef != PlayerCharacter::GetSingleton())
		return true;

	if (!pInvRef->pForm)
		return true;

	FORM_TYPE eFormType = pInvRef->pForm->GetFormType();
	if (eFormType != FORM_TYPE::TESObjectARMO && eFormType != FORM_TYPE::TESObjectWEAP && eFormType != FORM_TYPE::AlchemyItem && eFormType != FORM_TYPE::TESObjectBOOK)
		return true;

	ExtraDataList* pExtraData = pInvRef->pExtraDataList;
	if (!pExtraData)
		return true;

	ExtraHotkey* pHotkey = pExtraData->GetExtraData<ExtraHotkey>();
	if (pHotkey)
		arResult = pHotkey->ucIndex + 1;

	return true;
}

bool Cmd_GetMineArmedEx_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (!apRef->IsType<GrenadeProjectile>())
		return true;

	const GrenadeProjectile* pGrenade = static_cast<GrenadeProjectile*>(apRef);
	const BGSProjectile* pBase = pGrenade->GetProjectileBase();
	if (!pBase)
		return true;
	
	if (!pGrenade->IsFlagSet(GrenadeProjectile::ProjectileFlags::TURNED_OFF) && pGrenade->IsMine() && pGrenade->GetProjectileBase()->GetCanTurnOff())
		arResult = 1;

	return true;
}

namespace {
	enum CameraShotTrait : int32_t {
		INVALID = -1,
		ACTION = 0,
		LOCATION = 1,
		TARGET = 2,
		PLAYER_TIME_MULT = 3,
		TARGET_TIME_MULT = 4,
		GLOBAL_TIME_MULT = 5,
		MAX_TIME = 6,
		MIN_TIME = 7,
		TARGET_PCT_BETWEEN_ACTORS = 8,
	};
}

bool Cmd_GetCameraShotTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	CameraShotTrait eTraitID = CameraShotTrait::INVALID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &eTraitID) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		BGSCameraShot::Data& rData = pCameraShot->kData;
		switch (eTraitID) {
		case CameraShotTrait::ACTION:
			arResult = rData.eAction;
			break;
		case CameraShotTrait::LOCATION:
			arResult = rData.eLocation;
			break;
		case CameraShotTrait::TARGET:
			arResult = rData.eTarget;
			break;
		case CameraShotTrait::PLAYER_TIME_MULT:
			arResult = rData.fPlayerTimeMult;
			break;
		case CameraShotTrait::TARGET_TIME_MULT:
			arResult = rData.fTargetTimeMult;
			break;
		case CameraShotTrait::GLOBAL_TIME_MULT:
			arResult = rData.fGlobalTimeMult;
			break;
		case CameraShotTrait::MAX_TIME:
			arResult = rData.fMaxTime;
			break;
		case CameraShotTrait::MIN_TIME:
			arResult = rData.fMinTime;
			break;
		case CameraShotTrait::TARGET_PCT_BETWEEN_ACTORS:
			arResult = rData.fTargetPercentBetweenActors;
			break;
		default:
			return true;
		}

		if (IsConsoleMode())
			Console_Print("GetCameraShotTraitNumeric %d >> %.2f", eTraitID, arResult);
	}
	return true;
}

bool Cmd_SetCameraShotTraitNumeric_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	CameraShotTrait eTraitID = CameraShotTrait::INVALID;
	float fValue = 0.0f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &eTraitID, &fValue) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		BGSCameraShot::Data& rData = pCameraShot->kData;
		arResult = 1;
		switch (eTraitID) {
		case CameraShotTrait::ACTION:
			rData.eAction = static_cast<BGSCameraShot::Action>(fValue);
			break;
		case CameraShotTrait::LOCATION:
			rData.eLocation = static_cast<BGSCameraShot::Object>(fValue);
			break;
		case CameraShotTrait::TARGET:
			rData.eTarget = static_cast<BGSCameraShot::Object>(fValue);
			break;
		case CameraShotTrait::PLAYER_TIME_MULT:
			rData.fPlayerTimeMult = fValue;
			break;
		case CameraShotTrait::TARGET_TIME_MULT:
			rData.fTargetTimeMult = fValue;
			break;
		case CameraShotTrait::GLOBAL_TIME_MULT:
			rData.fGlobalTimeMult = fValue;
			break;
		case CameraShotTrait::MAX_TIME:
			rData.fMaxTime = fValue;
			break;
		case CameraShotTrait::MIN_TIME:
			rData.fMinTime = fValue;
			break;
		case CameraShotTrait::TARGET_PCT_BETWEEN_ACTORS:
			rData.fTargetPercentBetweenActors = fValue;
			break;
		default:
			break;
		}
	}
	return true;
}

bool Cmd_GetCameraShotFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		arResult = pCameraShot->kData.uiFlags;
		if (IsConsoleMode())
			Console_Print("GetCameraShotFlags >> %08X", pCameraShot->kData.uiFlags);
	}
	return true;
}

bool Cmd_SetCameraShotFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &uiFlags) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		pCameraShot->kData.uiFlags = uiFlags;
		arResult = 1;
	}
	return true;
}

bool Cmd_GetCameraShotPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		const char* pModel = pCameraShot->GetModel();
		g_strInterface->Assign(PASS_COMMAND_ARGS, pModel);
		if (IsConsoleMode())
			Console_Print("GetCameraShotPath >> %s", pModel);
	}
	return true;
}

bool Cmd_SetCameraShotPath_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	char cNewPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &cNewPath) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot) && cNewPath[0]) {
		pCameraShot->SetModel(cNewPath);
		arResult = 1;
	}
	return true;
}

bool Cmd_GetCameraShotImageSpaceModifier_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		TESImageSpaceModifier* pIMOD = pCameraShot->GetFormImageSpaceModifier();
		if (pIMOD)
			ScriptUtils::SetFormIDResult(arResult, pIMOD->GetFormID());

		if (IsConsoleMode())
			Console_Print("GetCameraShotImageSpaceModifier >> %s", pIMOD ? pIMOD->GetFormEditorID() : "None");
	}
	return true;
}

bool Cmd_SetCameraShotImageSpaceModifier_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSCameraShot* pCameraShot = nullptr;
	TESImageSpaceModifier* pIMOD = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &pIMOD) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		if (pIMOD && !IS_TYPE(pIMOD, TESImageSpaceModifier))
			return true;

		pCameraShot->SetFormImageSpaceModifier(pIMOD);
		arResult = 1;
	}
	return true;
}

namespace RefWalker {
	typedef bool(__fastcall* ReferenceFilterFunc)(const struct FilterData& arFilter, TESObjectREFR* apRef);
	struct ALIGN16 FilterData {
		template<typename T>
		using ScrapVector = std::vector<T, BSScrapAllocator<T>>;

		FilterData(TESObjectREFR* apCaller, Script* apScript, float afConeSize, float afHeading, const NiPoint4& akPosAndDist)
			: pCaller(apCaller), pScript(apScript), fConeSize(afConeSize * 0.017453292f), fHeading(afHeading), kPosAndDist(akPosAndDist) {}

		ScrapVector<ReferenceFilterFunc>	kFilterFunctions;
		Script*								pScript;
		ScrapVector<FORM_TYPE>				kTypeFilters;
		TESObjectREFR*						pCaller;
		float								fConeSize;
		float								fHeading;
		PROCESS_TYPE 						eProcessLevel;
		uint32_t							pad;
		NiPoint4							kPosAndDist;

		bool __fastcall CheckFormType(TESObjectREFR* apRef) const {
			for (FORM_TYPE eTypeFilter : kTypeFilters) {
				if (apRef->GetFormType() == eTypeFilter || apRef->GetObjectReference()->GetFormType() == eTypeFilter)
					return true;
			}

			return false;
		}

		bool __fastcall CheckDistance(TESObjectREFR* apRef) const {
			const float fDistance = apRef->GetPosition().SqrDistance(NiPoint3(kPosAndDist));
			return fDistance <= kPosAndDist.w;
		}

		static float __fastcall GetAngle(const NiPoint3& arVector, float afHeading) {
			float fAngle = (CdeclCall<float>(0xA811F0, arVector.x, arVector.y) - afHeading);
			constexpr float fPi = std::numbers::pi_v<float>;
			constexpr float f2Pi = std::numbers::pi_v<float> * 2;
			if (fAngle < -fPi)
				fAngle += f2Pi;
			else if (fAngle > fPi)
				fAngle -= f2Pi;
			return fAngle;
		}

		bool __fastcall CheckAngle(TESObjectREFR* apRef) const {
			const NiPoint3 kVector = apRef->GetPosition() - NiPoint3(kPosAndDist);
			return std::abs(GetAngle(kVector, fHeading)) <= fConeSize;
		}

		bool __fastcall CheckDistanceAndAngle(TESObjectREFR* apRef) const {
			const NiPoint3 kVector = apRef->GetPosition() - NiPoint3(kPosAndDist);
			const float fDistance = kVector.SqrLength();
			if (fDistance > kPosAndDist.w)
				return false;

			return std::abs(GetAngle(kVector, fHeading)) <= fConeSize;
		}

		bool __fastcall operator()(TESObjectREFR* apRef) const {
			if (kFilterFunctions.empty())
				return true;

			for (ReferenceFilterFunc pFunc : kFilterFunctions) {
				if (!pFunc(*this, apRef))
					return false;
			}
			return true;
		}
	};

	uint32_t SPEC_NOINLINE __fastcall IterateCellReferencesFiltered(TESObjectCELL* apCell, const FilterData& arFilter) {
		uint32_t uiCount = 0;
		TESObjectREFR* pCaller = arFilter.pCaller;
		apCell->CellRefLockEnter();
		auto pIter = apCell->objectList.GetHead();
		while (pIter && !pIter->IsEmpty()) {
			TESObjectREFR* pRef = pIter->GetItem();
			pIter = pIter->GetNext();

			if (pRef == pCaller)
				continue;

			constexpr uint32_t uiDisallowedFlags = TESForm::FormFlags::STILL_LOADING | TESForm::FormFlags::DELETED | TESForm::FormFlags::DISABLED;
			if (pRef && pRef->uiFormFlags.IsClear(uiDisallowedFlags) && pRef->GetInitialized() && pRef->GetObjectReference() && pRef->Get3DVerySimple()) {
				if (arFilter(pRef))
					uiCount += CallUDF(arFilter.pScript, pCaller, 1, pRef);
			}
		}
		apCell->CellRefLockLeave();
		return uiCount;
	}

	uint32_t SPEC_NOINLINE __fastcall IterateCells(TESObjectCELL* apCell, const FilterData& arFilter) {
		if (apCell) {
			return IterateCellReferencesFiltered(apCell, arFilter);
		}
		else {
			uint32_t uiCount = 0;
			GridCellArray* pArray = TES::GetSingleton()->gridCellArray;
			int32_t iGridSize = pArray->iDimension;
			for (int32_t x = 0; x < iGridSize; x++) {
				for (int32_t y = 0; y < iGridSize; y++) {
					GridCell* pGridCell = pArray->GetCell(x, y);
					if (pGridCell->pCell)
						uiCount += IterateCellReferencesFiltered(pGridCell->pCell, arFilter);
				}
			}
			return uiCount;
		}
	}

	uint32_t SPEC_NOINLINE __fastcall IterateMobileObjects(PROCESS_TYPE aeProcessLevel, const FilterData& arFilter) {
		uint32_t uiCount = 0;
		TESObjectREFR* pCaller = arFilter.pCaller;
		ProcessLists* pPL = ProcessLists::GetSingleton();

		const uint32_t uiBegin = pPL->beginOffsets[aeProcessLevel];
		const uint32_t uiEnd = pPL->endOffsets[aeProcessLevel];

		for (uint32_t i = uiBegin; i < uiEnd; i++) {
			MobileObject* pObject = pPL->objects.GetAt(i);
			if (pObject == pCaller)
				continue;

			constexpr uint32_t uiDisallowedFlags = TESForm::FormFlags::STILL_LOADING | TESForm::FormFlags::DELETED | TESForm::FormFlags::DISABLED;
			if (pObject && pObject->uiFormFlags.IsClear(uiDisallowedFlags) && pObject->GetInitialized() && pObject->GetObjectReference()) {
				if (arFilter(pObject))
					uiCount += CallUDF(arFilter.pScript, pCaller, 1, pObject);
			}
		}

		return uiCount;
	}

	bool __fastcall DistanceFilter(const FilterData& arFilter, TESObjectREFR* apRef) {
		return arFilter.CheckDistance(apRef);
	}

	bool __fastcall AngleFilter(const FilterData& arFilter, TESObjectREFR* apRef) {
		return arFilter.CheckAngle(apRef);
	}

	bool __fastcall DistanceAndAngleFilter(const FilterData& arFilter, TESObjectREFR* apRef) {
		return arFilter.CheckDistanceAndAngle(apRef);
	}

	bool __fastcall TypeFilter(const FilterData& arFilter, TESObjectREFR* apRef) {
		return arFilter.CheckFormType(apRef);
	}
}


bool Cmd_CallPerRef_Execute(COMMAND_ARGS) {
	using namespace RefWalker;
	arResult = 0;
	Script* pScript = nullptr;
	TESObjectCELL* pCell = nullptr;
	FORM_TYPE eFormFilter = FORM_TYPE::NONE;
	float fDistanceFilter = 0.f;
	float fAngleFilter = -FLT_MAX;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pScript, &eFormFilter, &fDistanceFilter, &fAngleFilter, &pCell) && pScript && IS_TYPE(pScript, Script)) {
		if (fDistanceFilter < 0.f)
			fDistanceFilter = 0.f;

		NiPoint4 kPosAndDist;
		TESObjectREFR* pCaller = apRef ? apRef : PlayerCharacter::GetSingleton();
		const NiPoint3& rPos = pCaller->GetLocationOnReference();
		kPosAndDist.x = rPos.x;
		kPosAndDist.y = rPos.y;
		kPosAndDist.z = rPos.z;
		kPosAndDist.w = fDistanceFilter * fDistanceFilter;

		if (pCell && !IS_TYPE(pCell, TESObjectCELL))
			pCell = nullptr;

		if (!pCell && TES::GetSingleton()->currentInterior)
			pCell = TES::GetSingleton()->currentInterior;

		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->GetAngleOnReference().z, kPosAndDist);
		if (eFormFilter)
			kFilterData.kTypeFilters.push_back(eFormFilter);

		if (!kFilterData.kTypeFilters.empty())
			kFilterData.kFilterFunctions.push_back(TypeFilter);

		if (fAngleFilter > 0.f && kPosAndDist.w > 0.f)
			kFilterData.kFilterFunctions.push_back(DistanceAndAngleFilter);
		else if (fAngleFilter > 0.f)
			kFilterData.kFilterFunctions.push_back(AngleFilter);
		else if (kPosAndDist.w > 0.f)
			kFilterData.kFilterFunctions.push_back(DistanceFilter);

		{
			LambdaVariableContext kVarContext(pScript);
			arResult = IterateCells(pCell, kFilterData);
		}
	}
	return true;
}

bool Cmd_CallPerRefEx_Execute(COMMAND_ARGS) {
	using namespace RefWalker;

	arResult = 0;
	PluginExpressionEvaluator kEval(PASS_COMMAND_ARGS);
	if (!kEval.ExtractArgs())
		return true;

	Script* pScript = reinterpret_cast<Script*>(kEval.GetNthArg(0)->GetTESForm());
	if (pScript && IS_TYPE(pScript, Script)) {
		TESObjectCELL* pCell = nullptr;
		float fDistanceFilter = 0.f;
		float fAngleFilter = -FLT_MAX;

		NVSEArrayVar* pTypeArray = kEval.GetNthArg(1)->GetArrayVar();
		uint32_t uiArraySize = g_arrInterface->GetArraySize(pTypeArray);
		if (!uiArraySize)
			return true;

		{
			PluginScriptToken* pToken = kEval.GetNthArg(2);
			if (pToken)
				fDistanceFilter = pToken->GetFloat();
		}
		{
			PluginScriptToken* pToken = kEval.GetNthArg(3);
			if (pToken)
				fAngleFilter = pToken->GetFloat();
		}
		{
			PluginScriptToken* pToken = kEval.GetNthArg(4);
			if (pToken)
				pCell = reinterpret_cast<TESObjectCELL*>(pToken->GetTESForm());
		}

		if (fDistanceFilter < 0.f)
			fDistanceFilter = 0.f;

		NiPoint4 kPosAndDist;
		TESObjectREFR* pCaller = apRef ? apRef : PlayerCharacter::GetSingleton();
		const NiPoint3& rPos = pCaller->GetLocationOnReference();
		kPosAndDist.x = rPos.x;
		kPosAndDist.y = rPos.y;
		kPosAndDist.z = rPos.z;
		kPosAndDist.w = fDistanceFilter * fDistanceFilter;

		if (pCell && !IS_TYPE(pCell, TESObjectCELL))
			pCell = nullptr;

		if (!pCell && TES::GetSingleton()->currentInterior)
			pCell = TES::GetSingleton()->currentInterior;

		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->GetAngleOnReference().z, kPosAndDist);
		BSScrapBuffer<NVSEArrayElement> kElements(uiArraySize);
		g_arrInterface->GetElements(pTypeArray, kElements.get(), nullptr);
		kFilterData.kTypeFilters.resize(uiArraySize);
		for (uint32_t i = 0; i < uiArraySize; i++) {
			kFilterData.kTypeFilters[i] = static_cast<FORM_TYPE>(kElements[i].GetNumber());
		}

		if (!kFilterData.kTypeFilters.empty())
			kFilterData.kFilterFunctions.push_back(TypeFilter);

		if (fAngleFilter > 0.f && kPosAndDist.w > 0.f)
			kFilterData.kFilterFunctions.push_back(DistanceAndAngleFilter);
		else if (fAngleFilter > 0.f)
			kFilterData.kFilterFunctions.push_back(AngleFilter);
		else if (kPosAndDist.w > 0.f)
			kFilterData.kFilterFunctions.push_back(DistanceFilter);

		{
			LambdaVariableContext kVarContext(pScript);
			arResult = IterateCells(pCell, kFilterData);
		}
	}
	return true;
}

bool Cmd_CallPerMobileObject_Execute(COMMAND_ARGS) {
	using namespace RefWalker;
	arResult = 0;
	Script* pScript = nullptr;
	PROCESS_TYPE eProcessLevel = PROCESS_TYPE::INVALID;
	FORM_TYPE eFormFilter = FORM_TYPE::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pScript, &eProcessLevel, &eFormFilter) && pScript && IS_TYPE(pScript, Script)) {
		NiPoint4 kPosAndDist;
		TESObjectREFR* pCaller = apRef ? apRef : PlayerCharacter::GetSingleton();

		FilterData kFilterData(pCaller, pScript, 0.f, 0.f, kPosAndDist);
		if (eFormFilter)
			kFilterData.kTypeFilters.push_back(eFormFilter);

		if (!kFilterData.kTypeFilters.empty())
			kFilterData.kFilterFunctions.push_back(TypeFilter);

		{
			LambdaVariableContext kVarContext(pScript);
			arResult = IterateMobileObjects(eProcessLevel, kFilterData);
		}
	}
	return true;
}

bool Cmd_CallPerMobileObjectEx_Execute(COMMAND_ARGS) {
	using namespace RefWalker;

	arResult = 0;
	PluginExpressionEvaluator kEval(PASS_COMMAND_ARGS);
	if (!kEval.ExtractArgs())
		return true;

	Script* pScript = reinterpret_cast<Script*>(kEval.GetNthArg(0)->GetTESForm());
	if (pScript && IS_TYPE(pScript, Script)) {
		NVSEArrayVar* pTypeArray = kEval.GetNthArg(2)->GetArrayVar();
		uint32_t uiArraySize = g_arrInterface->GetArraySize(pTypeArray);
		if (!uiArraySize)
			return true;

		PROCESS_TYPE eProcessLevel = PROCESS_TYPE(kEval.GetNthArg(1)->GetInt());

		NiPoint4 kPosAndDist;
		TESObjectREFR* pCaller = apRef ? apRef : PlayerCharacter::GetSingleton();
		FilterData kFilterData(pCaller, pScript, 0.f, 0.f, kPosAndDist);

		BSScrapBuffer<NVSEArrayElement> kElements(uiArraySize);
		g_arrInterface->GetElements(pTypeArray, kElements.get(), nullptr);
		kFilterData.kTypeFilters.resize(uiArraySize);
		for (uint32_t i = 0; i < uiArraySize; i++) {
			kFilterData.kTypeFilters[i] = static_cast<FORM_TYPE>(kElements[i].GetNumber());
		}

		if (!kFilterData.kTypeFilters.empty())
			kFilterData.kFilterFunctions.push_back(TypeFilter);

		{
			LambdaVariableContext kVarContext(pScript);
			arResult = IterateMobileObjects(eProcessLevel, kFilterData);
		}
	}
	return true;
}

enum UPDATE3D_FLAGS_EX {
	UPDATE_MODEL	= 1u << 0,
	UPDATE_SKIN		= 1u << 1,
	UPDATE_HEAD		= 1u << 2,
	UPDATE_FACE		= 1u << 3,
	UPDATE_SCALE	= 1u << 4,
	UPDATE_LIGHTS	= 1u << 5,
	UPDATE_POS		= 1u << 6,
};

static ShadowSceneNode* FindSceneNodeRecurse(const NiAVObject* apObject) {
	const NiNode* pParent = apObject->GetParent();
	if (!pParent)
		return nullptr;

	if (pParent->IsExactKindOf<ShadowSceneNode>())
		return static_cast<ShadowSceneNode*>(const_cast<NiNode*>(pParent));
	else
		return FindSceneNodeRecurse(pParent);
}

static void __fastcall RefreshReferenceModel(TESObjectREFR* apReference, uint32_t auiFlags) {
	if (auiFlags & UPDATE_MODEL) {
		UpdateReference3D(apReference);
		ThisCall(0x456520, *reinterpret_cast<DWORD**>(0x1202D98));

		NiAVObject* pRoot = apReference->Get3DVerySimple();
		if (pRoot && pRoot->IsFadeNode())
			static_cast<BSFadeNode*>(pRoot)->TurnFadeNodeOn();
	}

	if (auiFlags & UPDATE_SCALE)
		apReference->SetScale(apReference->GetRawScale());

	if (auiFlags & UPDATE_LIGHTS) {
		NiAVObject* pRoot = apReference->Get3DVerySimple();
		if (pRoot) {
			ShadowSceneNode* pSSN = FindSceneNodeRecurse(pRoot);
			if (pSSN)
				pSSN->UpdateObjectLighting(pRoot, false);
		}
	}

	if (auiFlags & UPDATE_POS) {
		apReference->Update3DPosition();
	}
}

static void __fastcall RequestModelUpdate(TESObjectREFR* apReference, uint32_t auiFlags, bool abQueue) {
	if (abQueue) {
		JohnnyExtraData* pExtraData = JohnnyExtraData::GetOrCreate(apReference);
		pExtraData->IncRefCount();

		QueuedTask kTask;
		kTask.kItems[0].p = pExtraData;
		kTask.kItems[1].ui = auiFlags;
		kTask.pFunction = QUEUED_TASK{
			JohnnyExtraData* pData = reinterpret_cast<JohnnyExtraData*>(arTask.kItems[0].p);
			TESObjectREFR* pRef = static_cast<TESObjectREFR*>(pData->pOwner);
			if (pRef) {
				uint32_t uiFlags = arTask.kItems[1].ui;
				RefreshReferenceModel(pRef, uiFlags);
			}
			pData->DecRefCount();
		};
		TaskQueue::QueueTask(kTask);
	}
	else {
		RefreshReferenceModel(apReference, auiFlags);
	}
}

bool Cmd_Update3DAlt_Execute(COMMAND_ARGS) {
	constexpr uint32_t uiAddedFlags = UPDATE_LIGHTS | UPDATE_POS;

	arResult = 0;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags) && uiFlags) {
		if (!apRef->Get3DVerySimple() || apRef->IsStillLoading())
			return true;

		const bool bQueue = AILinearTaskThreadManager::ShouldQueue3DTask();
		if (apRef->IsActor()) {
			Actor* pActor = static_cast<Actor*>(apRef);
			if (pActor->GetCurrentAIProcess()) {
				// Creatures can't refresh their models in vanilla, so we have to handle them ourselves.
				if (pActor->IsCreature()) {
					RequestModelUpdate(apRef, uiFlags, bQueue);
				}
				else {
					pActor->GetCurrentAIProcess()->Set3DUpdateFlag(uiFlags);
					if (!bQueue)
						pActor->GetCurrentAIProcess()->Update3DModel(pActor);


					const uint32_t uiCustomFlags = uiFlags & uiAddedFlags;
					if (uiCustomFlags)
						RequestModelUpdate(apRef, uiCustomFlags, bQueue);
				}
			}
		}
		else {
			RequestModelUpdate(apRef, uiFlags, bQueue);
		}

		arResult = 1;
	}
	return true;
}

bool Cmd_GetRecipeCategoryFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESRecipeCategory* pCategory = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCategory) && pCategory && IS_TYPE(pCategory, TESRecipeCategory)) {
		arResult = pCategory->ucFlags;
		if (IsConsoleMode()) 
			Console_Print("GetRecipeCategoryFlags >> %.f", arResult);
	}
	return true;
}

bool Cmd_RemapLand_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t uiLandID = 0;
	TESWorldSpace* pWorld = nullptr;
	int32_t iGridX = INT32_MAX, iGridY = INT32_MAX;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiLandID, &pWorld, &iGridX, &iGridY)) {
		bool bValidCoord;
		if (pWorld) {
			const int32_t iWorldMinX = int32_t(pWorld->kMinCoords.x) >> 12;
			const int32_t iWorldMinY = int32_t(pWorld->kMinCoords.y) >> 12;

			const int32_t iWorldMaxX = int32_t(pWorld->kMaxCoords.x) >> 12;
			const int32_t iWorldMaxY = int32_t(pWorld->kMaxCoords.y) >> 12;
			bValidCoord = iGridX <= iWorldMaxX && iGridY <= iWorldMaxY && iGridX >= iWorldMinX && iGridY >= iWorldMinY;
		}
		else {
			constexpr int32_t iMax =  32767;
			constexpr int32_t iMin = -32768;
			bValidCoord = iGridX <= iMax && iGridY <= iMax && iGridX >= iMin && iGridY >= iMin;
		}

		if (pWorld && !bValidCoord) {
			if (IsConsoleMode())
				Console_Print("RemapLand >> You must provide valid cell coordinates");
			return true;
		}

		TESForm* pFoundForm = TESForm::GetFormByNumericID(uiLandID);
		bool bFoundLand = false;
		if (pFoundForm) {
			if (pFoundForm->GetFormType() == FORM_TYPE::TESObjectLAND) {
				bFoundLand = true;
			}
			else {
				if (IsConsoleMode())
					Console_Print("RemapLand >> Found form is not to a TESObjectLAND!");
				return true;
			}
		}

		LandRemapping::RemapLand(uiLandID, pWorld, iGridX, iGridY);

		if (bFoundLand) {
			TESObjectLAND* pLand = static_cast<TESObjectLAND*>(pFoundForm);
			if (pLand->IsLoaded()) {
				QueuedTask kTask;
				kTask.kItems[0].ui = uiLandID;
				kTask.pFunction = QUEUED_TASK{
					TESObjectLAND * pLand = static_cast<TESObjectLAND*>(TESForm::GetFormByNumericID(arTask.kItems[0].ui));
					if (pLand)
						LandRemapping::ReloadModel(pLand, true);
				};
				TaskQueue::QueueTask(kTask);
			}
		}

		arResult = 1;
	}
	return true;
}

bool Cmd_GetItemEffectString_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;

	ExtractArgsEx(EXTRACT_ARGS_EX, &pForm);

	if (!pForm) {
		if (!apRef) 
			return true;
		pForm = apRef->GetObjectReference();
	}

	if (!pForm)
		return true;

	char cEffects[512] = {};

	switch (pForm->GetFormType()) {
		// Item mod
		case FORM_TYPE::TESObjectIMOD:
		{
			const TESObjectIMOD* pItemMod = static_cast<TESObjectIMOD*>(pForm);
			const char* pModDescription = pItemMod->GetDescription(pForm, 'CSED');
			if (pModDescription)
				strcpy_s(cEffects, sizeof(cEffects), pModDescription);
		}
		break;

		// Ingestible
		case FORM_TYPE::AlchemyItem:
		{
			const AlchemyItem* pAlchItem = static_cast<AlchemyItem*>(pForm);
			pAlchItem->GetEffectsString(cEffects, sizeof(cEffects));
		}
		break;

		// Ammo
		case FORM_TYPE::TESAmmo:
		{
			const TESAmmo* pAmmo = static_cast<TESAmmo*>(pForm);
			pAmmo->GetEffectNames(cEffects, sizeof(cEffects));
		}
		break;

		// Weapon & Armor
		default:
		{
			const EnchantmentItem* pItem = TESEnchantableForm::GetFormEnchanting(pForm);
			if (pItem)
				pItem->GetEffectsString(cEffects, sizeof(cEffects));
		}
	}

	g_strInterface->Assign(PASS_COMMAND_ARGS, cEffects);

	if (IsConsoleMode())
		Console_Print("GetItemEffectString >> %s", cEffects);

	return true;
}


bool Cmd_ApplyModelTextureSwap_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESBoundObject* pBaseForm = nullptr;
	TESObjectREFR* pReference = nullptr;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBaseForm, &cObjectName, &pReference, &bFirstPerson) && pBaseForm) {
		NiAVObject* pScene = GetReferenceScene(apRef, bFirstPerson);
		if (cObjectName[0])
			pScene = BSUtilities::GetObjectByName(pScene, cObjectName);

		if (pScene) {
			if (!pReference)
				pReference = apRef;

			TESModel* pModel = ModelLoader::GetSingleton()->GetModelForBoundObject(pBaseForm, pReference);
			if (pModel) {
				TESModelTextureSwap* pTexSwap = pModel->GetAsModelMaterialSwap();
				if (pTexSwap) {
					pTexSwap->SwapTextures(pScene);
					arResult = 1;
				}
			}

			if (pBaseForm->GetHasPLSpecTex()) {
				CdeclCall(0x4B7660, pScene); // SwapPlatformLanguageTextures
				arResult = 1;
			}
		}
	}
	return true;
}

enum class IKType : int32_t {
	NONE = -1,
	LOOK = 0,
	FOOT = 1,
	GRAB = 2,
	COUNT,
};

bool Cmd_SetIKState_Execute(COMMAND_ARGS) {
	IKType eType = IKType::NONE;
	BOOL bToggle = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eType, &bToggle) && InRange(eType) && apRef->IsActor()) {
		const Actor* pActor = static_cast<Actor*>(apRef);
		bhkRagdollController* pCtrl = pActor->pRagdollController;
		if (pCtrl) {
			switch (eType) {
				case IKType::LOOK:
					pCtrl->SetLookIKEnable(bToggle);
					break;
				case IKType::FOOT:
					pCtrl->SetFootIKEnable(bToggle);
					break;
				case IKType::GRAB:
					pCtrl->SetGrabIKEnable(bToggle);
					break;
				default:
					__assume(0);
					break;
			}
		}
	}
	return true;
}

SPEC_NOINLINE bool Cmd_GetIKState_Eval(COMMAND_ARGS_EVAL) {
	arResult = -1.0;
	const IKType eType = *reinterpret_cast<IKType*>(&apParam1);
	if (InRange(eType) && apRef->IsActor()) {
		const Actor* pActor = static_cast<Actor*>(apRef);
		bhkRagdollController* pCtrl = pActor->pRagdollController;
		if (pCtrl) {
			switch (eType) {
				case IKType::LOOK:
					arResult = pCtrl->GetLookIKEnable();
					break;
				case IKType::FOOT:
					arResult = pCtrl->GetFootIKEnable();
					break;
				case IKType::GRAB:
					arResult = pCtrl->GetGrabIKEnable();
					break;
				default:
					__assume(0);
					break;
			}
		}
	}
	return true;
}

bool Cmd_GetIKState_Execute(COMMAND_ARGS) {
	IKType eType = IKType::NONE;
	ExtractArgsEx(EXTRACT_ARGS_EX, &eType);
	return Cmd_GetIKState_Eval(apRef, reinterpret_cast<void*>(eType), nullptr, arResult);
}

SPEC_NOINLINE bool Cmd_IsCarryable_Eval(COMMAND_ARGS_EVAL) {
	TESForm* pForm = reinterpret_cast<TESForm*>(apParam1);
	pForm = pForm ? pForm : apRef;
	if (!pForm)
		pForm = CdeclCall<TESForm*>(0x6008F0); // TESIdleManager::GetUsedItem

	arResult = TESContainer::ContainerCanHoldForm(pForm);
	return true;
}

bool Cmd_IsCarryable_Execute(COMMAND_ARGS) {
	TESForm* pForm = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pForm);
	Cmd_IsCarryable_Eval(apRef, pForm, nullptr, arResult);

	if (IsConsoleMode())
		Console_Print("IsCarryable >> %f", arResult);

	return true;
}

bool Cmd_PickIdleEx_Execute(COMMAND_ARGS) {
	if (!apRef->IsActor())
		return true;
	
	Actor* pUser = static_cast<Actor*>(apRef);
	if (!pUser->GetCurrentAIProcess())
		return true;

	TESObjectREFR* pTargetRef = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTargetRef) && pTargetRef && pTargetRef->GetObjectReference()) {
		LowProcess* pAIProcess = static_cast<LowProcess*>(pUser->GetCurrentAIProcess());
		const TESObjectREFR* pOrgTarget = pAIProcess->pTarget;
		pAIProcess->pTarget = pTargetRef;
		arResult = pAIProcess->FindSpecialIdletoPlay(pUser, pTargetRef->GetOriginalObjectReference(), pTargetRef);
		pAIProcess->pTarget = pOrgTarget;
	}

	return true;
}

SPEC_INLINE bool Cmd_GetUsedItemHeight_Eval(COMMAND_ARGS_EVAL) {
	arResult = AnimActivationHeight::GetHeight();
	return true;
}

bool Cmd_GetUsedItemHeight_Execute(COMMAND_ARGS) {
	Cmd_GetUsedItemHeight_Eval(apRef, nullptr, nullptr, arResult);
	return true;
}

bool Cmd_ClearAltTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm;
	int32_t iIndex = -2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &iIndex) && pForm) {
		TESModelTextureSwap* pModel = DYNAMIC_CAST(pForm, TESForm, TESModelTextureSwap);
		if (!pModel)
			return true;

		if (iIndex == -1) {
			pModel->ClearTexSwapList();
			arResult = 1;
			return true;
		}
		else {
			pModel->RemoveTexSwap(iIndex);
			arResult = 1;
			return true;
		}
	}
	return true;
}

bool Cmd_SetAltTexture_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	BGSTextureSet* pTextureSet = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &iIndex, &pTextureSet) && pForm && pTextureSet && IS_TYPE(pTextureSet, BGSTextureSet)) {
		TESModelTextureSwap* pModel = DYNAMIC_CAST(pForm, TESForm, TESModelTextureSwap);
		if (!pModel)
			return true;

		TEX_SWAP* pSwap = pModel->GetTexSwap(iIndex);
		if (pSwap) {
			pSwap->pTextureSet = pTextureSet;
			arResult = 1;
		}
		else {
			pModel->AddTexSwap("", iIndex, pTextureSet);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetAltTextures_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm) && pForm) {
		TESModelTextureSwap* pModel = DYNAMIC_CAST(pForm, TESForm, TESModelTextureSwap);
		if (pModel) {
			auto pIter = pModel->GetTexSwapList();
			while (pIter && !pIter->IsEmpty()) {
				TEX_SWAP* pEntry = pIter->GetItem();
				pIter = pIter->GetNext();
				if (pEntry && pEntry->pTextureSet) {
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pEntry->pTextureSet));
				}
			}
		}
	}
	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;
}
#endif