#include "fn_form.h"
#include "decoding.h"
#include "GameData.h"
#include "GameForms.h"
#include "GameProcess.h"
#include "GameRTTI.h"
#include "GameTasks.h"
#include "PluginAPI.h"

#include "Bethesda/AILinearTaskThreadManager.hpp"
#include "Bethesda/BGSLoadGameSubBuffer.hpp"
#include "Bethesda/BGSPrimitive.hpp"
#include "Bethesda/BGSSaveFormBuffer.hpp"
#include "Bethesda/BSShaderManager.hpp"
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/ExtraActivateRef.hpp"
#include "Bethesda/ExtraHotkey.hpp"
#include "Bethesda/ExtraPrimitive.hpp"
#include "Bethesda/INIPrefSettingCollection.hpp"
#include "Bethesda/ItemChange.hpp"
#include "Bethesda/TESMain.hpp"
#include "Bethesda/TESObjectList.hpp"
#include "Bethesda/GrenadeProjectile.hpp"
#include "Bethesda/PlayerCharacter.hpp"

#include "NVSE/InventoryRef.hpp"

#include "Shared/BSMemory/BSMemoryUtils.hpp"
#include "Shared/Utils/StackObject.hpp"

#include "events/LambdaVariableContext.h"
#include "JG/AnimActivationHeight.hpp"
#include "JG/BarterFilter.hpp"
#include "JG/ExternalEmittanceOnBases.hpp"
#include "JG/JGSetList.hpp"
#include "JG/JohnnyExtraData.hpp"
#include "JG/LandRemapping.hpp"
#include "JG/TaskQueue.hpp"

#include <numbers>
#include <unordered_map>

#include "JG/ScriptUtils.hpp"
using namespace ScriptUtils;

extern bool (*CallUDF)(class Script* funcScript, class TESObjectREFR* callingObj, uint8_t numArgs, ...);
extern InventoryRef* (*InventoryRefGetForID)(FormID refID);

float(*GetWeaponDPS)(ActorValueOwner* avOwner, TESObjectWEAP* weapon, float condition, uint8_t arg4, ItemChange* entry, uint8_t arg6, uint8_t arg7, int arg8, float arg9, float arg10, uint8_t arg11, uint8_t arg12, TESForm* ammo) =
(float(*)(ActorValueOwner*, TESObjectWEAP*, float, uint8_t, ItemChange*, uint8_t, uint8_t, int, float, float, uint8_t, uint8_t, TESForm*))0x645380;

bool Cmd_RemoveNoteQuest_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	TESQuest* pQuest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pQuest) && pNote && IS_TYPE(pNote, BGSNote) && IS_TYPE(pQuest, TESQuest)) {
		pNote->kOwnerQuests.Remove(pQuest);
		*result = 1;
	}
	return true;
}

bool Cmd_AddNoteQuest_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	TESQuest* pQuest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pQuest) && pNote && IS_TYPE(pNote, BGSNote) && IS_TYPE(pQuest, TESQuest)) {
		pNote->kOwnerQuests.AddTail(pQuest);
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteQuestList_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	NVSEArrayVar* pQuests = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote) && !pNote->kOwnerQuests.IsEmpty()) {
		auto pIter = pNote->kOwnerQuests.GetHead();
		while (pIter && !pIter->IsEmpty()) {
			TESQuest* pQuest = pIter->GetItem();
			if (pQuest)
				g_arrInterface->AppendElement(pQuests, NVSEArrayElement(pQuest->GetFormID()));
			pIter = pIter->GetNext();
		}
	}
	g_arrInterface->AssignCommandResult(pQuests, result);
	return true;
}

bool Cmd_SetNoteImage_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &cPath) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESTexture* pImage = pNote->GetNoteImage();
		if (pImage) {
			pImage->SetTextureName(cPath);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetNoteImage_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		const TESTexture* pImage = pNote->GetNoteImage();
		if (pImage)
			g_strInterface->Assign(PASS_COMMAND_ARGS, pImage->GetTextureName());
	}
	return true;
}
bool Cmd_SetNoteTopic_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	TESTopic* pTopic = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pTopic) && pNote && IS_TYPE(pNote, BGSNote) && IS_TYPE(pTopic, TESTopic) && pNote->GetNoteType() == BGSNote::Type::VOICE) {
		pNote->SetNoteTopic(pTopic);
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteTopic_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESTopic* pTopic = pNote->GetNoteTopic();
		if (pTopic)
			*reinterpret_cast<FormID*>(result) = pTopic->GetFormID();
	}
	return true;
}

bool Cmd_SetNoteSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	TESSound* pSound = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pSound) && pNote && IS_TYPE(pNote, BGSNote) && pNote->GetNoteType() == BGSNote::Type::SOUND) {
		pNote->SetNoteSound(pSound);
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESSound* pSound = pNote->GetNoteSound();
		if (pSound)
			*reinterpret_cast<FormID*>(result) = pSound->GetFormID();
	}
	return true;
}

bool Cmd_SetNoteType_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	BGSNote::Type eType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &eType) && pNote && IS_TYPE(pNote, BGSNote) && eType >= BGSNote::Type::SOUND && eType <= BGSNote::Type::VOICE) {
		pNote->SetNoteType(eType);
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteType_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		*result = pNote->GetNoteType();
	}
	return true;
}

bool Cmd_SetNoteSpeaker_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	TESActorBase* pSpeaker = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &pSpeaker) && pNote && IS_TYPE(pNote, BGSNote) && pNote->GetNoteType() == BGSNote::Type::VOICE) {
		pNote->SetNoteSpeaker(pSpeaker);
		*result = 1;
	}
	return true;
}
bool Cmd_GetNoteSpeaker_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote) && pNote && IS_TYPE(pNote, BGSNote)) {
		TESActorBase* pSpeaker = pNote->GetNoteSpeaker();
		if (pSpeaker)
			*reinterpret_cast<FormID*>(result) = pSpeaker->GetFormID();
	}
	return true;
}

bool Cmd_GetCurrentFurnitureRef_Execute(COMMAND_ARGS) {
	if (!thisObj) { return true; }
	*result = 0;
	if (thisObj->IsActor()) {
		auto actorProcess = ((Actor*)thisObj)->GetCurrentAIProcess();
		if (actorProcess) {
			auto furniRef = actorProcess->GetCurrentFurniture();
			if (furniRef) {
				*(FormID*)result = furniRef->GetFormID();
			}
		}

	}
	return true;
}

float(__fastcall* GetBaseScale)(TESObjectREFR*) = (float(__fastcall*)(TESObjectREFR*)) 0x00567400;
void* (__thiscall* TESNPC_GetFaceGenData)(TESNPC*) = (void* (__thiscall*)(TESNPC*)) 0x0601800;


bool Cmd_HideItemBarterEx_Execute(COMMAND_ARGS) {
	const TESForm* pItem = nullptr;
	const TESForm* pSeller = nullptr;
	BOOL bAdd = TRUE;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pItem, &bAdd, &uiFlags, &pSeller) && pItem) {
		const FormID uiFormID = pItem->GetFormID();
		const FormID uiSellerFormID = pSeller ? pSeller->GetFormID() : 0;

		if (bAdd)
			*result = BarterFilter::Add(uiFormID, uiFlags, uiSellerFormID);
		else
			*result = BarterFilter::Remove(uiFormID, uiFlags, uiSellerFormID);
	}
	return true;
}

bool Cmd_IsItemBarterHiddenEx_Execute(COMMAND_ARGS) {
	*result = 0;
	const TESForm* pItem = nullptr;
	const TESForm* pSeller = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pItem, &pSeller) && pItem) {
		const FormID uiFormID = pItem->GetFormID();
		const FormID uiSellerFormID = pSeller ? pSeller->GetFormID() : 0;

		*result = BarterFilter::IsHidden(uiFormID, uiSellerFormID);
		if (Script::GetConsoleOuput())
			Interface::PrintLine("IsItemBarterHiddenEx >> %f", *result);
	}
	return true;
}

SPEC_NOINLINE bool Cmd_IsRadioRefPlaying_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj && thisObj->GetObjectReference() && IS_TYPE(thisObj->GetObjectReference(), TESObjectACTI)) {
		TESObjectACTI* baseActi = static_cast<TESObjectACTI*>(thisObj->GetObjectReference());
		if (baseActi->GetRadioStation()) {
			*result = (CdeclCall<void*>(0x0832930, thisObj) != nullptr);
		}
	}
	return true;
}

bool Cmd_IsRadioRefPlaying_Execute(COMMAND_ARGS) {
	return Cmd_IsRadioRefPlaying_Eval(thisObj, nullptr, nullptr, result);
}

bool Cmd_TuneRadioRef_Execute(COMMAND_ARGS) {
	BGSTalkingActivator* actiDst = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &actiDst) && thisObj && thisObj->GetObjectReference() && IS_TYPE(thisObj->GetObjectReference(), TESObjectACTI)) {
		if (TESObjectACTI* actiBase = (TESObjectACTI*)thisObj->GetObjectReference()) {
			BGSTalkingActivator* originalTK = actiBase->GetRadioStation();
			if (actiDst == nullptr) {
				actiDst = originalTK;
			}
			if (IS_TYPE(actiDst, BGSTalkingActivator)) {
				auto activateState = CdeclCall<unsigned int>(0x047B250, thisObj);
				if ((CdeclCall<void*>(0x0832930, thisObj) != nullptr) || (activateState == 1) || (activateState == 2)) { //the exact same logic the game uses
					CdeclCall<void*>(0x08325B0, thisObj, 0);
					actiBase->SetRadioStation(actiDst);
					CdeclCall<void*>(0x08325B0, thisObj, 1);
					actiBase->SetRadioStation(originalTK);
				}
			}
		}
	}
	return true;
}

bool Cmd_GetFormRecipesAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	NVSEArrayVar* pRecipes = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
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
	g_arrInterface->AssignCommandResult(pRecipes, result);
	return true;
}

bool Cmd_SetFactionFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* pFaction = nullptr;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pFaction, &uiFlags) && pFaction && IS_ID(pFaction, TESFaction)) {
		pFaction->kData.uiFlags = uiFlags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetFactionFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* pFaction = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pFaction) && pFaction && IS_ID(pFaction, TESFaction)) {
		*result = pFaction->kData.uiFlags;
		if (Script::GetConsoleOuput()) 
			Interface::PrintLine("GetFactionFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_RemoveScopeModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* pWeapon = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon) && pWeapon && IS_ID(pWeapon, TESObjectWEAP)) {
		if (pWeapon && pWeapon->GetHasScope()) {
			pWeapon->GetScopeModel()->SetModel("");
			*result = 1;
		}
	}

	return true;
}

bool Cmd_SetLightingTemplateCell_Execute(COMMAND_ARGS) {
	*result = 0;
	return true;
}

bool Cmd_GetLightingTemplateCell_Execute(COMMAND_ARGS) {
	*result = 0;
	return true;
}

namespace {

	struct ALIGN4 RGBA {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	enum class LightingTemplateTraits {
		NONE = 0,

		AMBIENT_RED = 1,
		AMBIENT_GREEN = 2,
		AMBIENT_BLUE = 3,

		DIRECTIONAL_RED = 4,
		DIRECTIONAL_GREEN = 5,
		DIRECTIONAL_BLUE = 6,

		FOG_RED = 7,
		FOG_GREEN = 8,
		FOG_BLUE = 9,

		FOG_NEAR = 10,
		FOG_FAR = 11,

		DIRECTIONAL_XY = 12,
		DIRECTIONAL_Z = 13,
		DIRECTIONAL_FADE = 14,

		CLIP_DISTANCE = 15,

		FOG_POWER = 16,

		COUNT
	};

	enum class InteriorDataTraits {
		NONE = -1,

		AMBIENT_RED = 0,
		AMBIENT_GREEN = 1,
		AMBIENT_BLUE = 2,

		DIRECTIONAL_RED = 3,
		DIRECTIONAL_GREEN = 4,
		DIRECTIONAL_BLUE = 5,

		DIRECTIONAL_XY = 6,
		DIRECTIONAL_Z = 7,
		DIRECTIONAL_FADE = 8,

		FOG_RED = 9,
		FOG_GREEN = 10,
		FOG_BLUE = 11,

		FOG_NEAR = 12,
		FOG_FAR = 13,

		FOG_POWER = 14,

		CLIP_DISTANCE = 15,

		COUNT
	};

	SPEC_NOINLINE InteriorDataTraits ConvertTemplateType(LightingTemplateTraits aeType) {
		switch (aeType) {
			case LightingTemplateTraits::AMBIENT_RED:
				return InteriorDataTraits::AMBIENT_RED;
			case LightingTemplateTraits::AMBIENT_GREEN:
				return InteriorDataTraits::AMBIENT_GREEN;
			case LightingTemplateTraits::AMBIENT_BLUE:
				return InteriorDataTraits::AMBIENT_BLUE;
			case LightingTemplateTraits::DIRECTIONAL_RED:
				return InteriorDataTraits::DIRECTIONAL_RED;
			case LightingTemplateTraits::DIRECTIONAL_GREEN:
				return InteriorDataTraits::DIRECTIONAL_GREEN;
			case LightingTemplateTraits::DIRECTIONAL_BLUE:
				return InteriorDataTraits::DIRECTIONAL_BLUE;
			case LightingTemplateTraits::DIRECTIONAL_XY:
				return InteriorDataTraits::DIRECTIONAL_XY;
			case LightingTemplateTraits::DIRECTIONAL_Z:
				return InteriorDataTraits::DIRECTIONAL_Z;
			case LightingTemplateTraits::DIRECTIONAL_FADE:
				return InteriorDataTraits::DIRECTIONAL_FADE;
			case LightingTemplateTraits::FOG_RED:
				return InteriorDataTraits::FOG_RED;
			case LightingTemplateTraits::FOG_GREEN:
				return InteriorDataTraits::FOG_GREEN;
			case LightingTemplateTraits::FOG_BLUE:
				return InteriorDataTraits::FOG_BLUE;
			case LightingTemplateTraits::FOG_NEAR:
				return InteriorDataTraits::FOG_NEAR;
			case LightingTemplateTraits::FOG_FAR:
				return InteriorDataTraits::FOG_FAR;
			case LightingTemplateTraits::FOG_POWER:
				return InteriorDataTraits::FOG_POWER;
			case LightingTemplateTraits::CLIP_DISTANCE:
				return InteriorDataTraits::CLIP_DISTANCE;
			default:
				return InteriorDataTraits::NONE;
		}
	}

	SPEC_NOINLINE double __fastcall GetInteriorDataValue(InteriorCellData* apData, InteriorDataTraits aeType) {
		if (!apData)
			return 0.f;

		switch (aeType) {
			case InteriorDataTraits::AMBIENT_RED:
				return reinterpret_cast<RGBA&>(apData->uiAmbientColor).r;
			case InteriorDataTraits::AMBIENT_GREEN:
				return reinterpret_cast<RGBA&>(apData->uiAmbientColor).g;
			case InteriorDataTraits::AMBIENT_BLUE:
				return reinterpret_cast<RGBA&>(apData->uiAmbientColor).b;
			case InteriorDataTraits::DIRECTIONAL_RED:
				return reinterpret_cast<RGBA&>(apData->uiDirectionalColor).r;
			case InteriorDataTraits::DIRECTIONAL_GREEN:
				return reinterpret_cast<RGBA&>(apData->uiDirectionalColor).g;
			case InteriorDataTraits::DIRECTIONAL_BLUE:
				return reinterpret_cast<RGBA&>(apData->uiDirectionalColor).b;
			case InteriorDataTraits::DIRECTIONAL_XY:
				return apData->iDirectionalXY;
			case InteriorDataTraits::DIRECTIONAL_Z:
				return apData->iDirectionalZ;
			case InteriorDataTraits::DIRECTIONAL_FADE:
				return apData->fDirectionalFade;
			case InteriorDataTraits::FOG_RED:
				return reinterpret_cast<RGBA&>(apData->uiFogColor).r;
			case InteriorDataTraits::FOG_GREEN:
				return reinterpret_cast<RGBA&>(apData->uiFogColor).g;
			case InteriorDataTraits::FOG_BLUE:
				return reinterpret_cast<RGBA&>(apData->uiFogColor).b;
			case InteriorDataTraits::FOG_NEAR:
				return apData->fFogNear;
			case InteriorDataTraits::FOG_FAR:
				return apData->fFogFar;
			case InteriorDataTraits::FOG_POWER:
				return apData->fFogPower;
			case InteriorDataTraits::CLIP_DISTANCE:
				return apData->fClipDist;
			default:
				return 0.f;
		}
	}

	SPEC_NOINLINE bool __fastcall SetInteriorDataValue(InteriorCellData* apData, InteriorDataTraits aeType, float afValue) {
		if (!apData)
			return false;

		switch (aeType) {
			case InteriorDataTraits::AMBIENT_RED:
				reinterpret_cast<RGBA&>(apData->uiAmbientColor).r = afValue;
				break;
			case InteriorDataTraits::AMBIENT_GREEN:
				reinterpret_cast<RGBA&>(apData->uiAmbientColor).g = afValue;
				break;
			case InteriorDataTraits::AMBIENT_BLUE:
				reinterpret_cast<RGBA&>(apData->uiAmbientColor).b = afValue;
				break;
			case InteriorDataTraits::DIRECTIONAL_RED:
				reinterpret_cast<RGBA&>(apData->uiDirectionalColor).r = afValue;
				break;
			case InteriorDataTraits::DIRECTIONAL_GREEN:
				reinterpret_cast<RGBA&>(apData->uiDirectionalColor).g = afValue;
				break;
			case InteriorDataTraits::DIRECTIONAL_BLUE:
				reinterpret_cast<RGBA&>(apData->uiDirectionalColor).b = afValue;
				break;
			case InteriorDataTraits::DIRECTIONAL_XY:
				apData->iDirectionalXY = afValue;
				break;
			case InteriorDataTraits::DIRECTIONAL_Z:
				apData->iDirectionalZ = afValue;
				break;
			case InteriorDataTraits::DIRECTIONAL_FADE:
				apData->fDirectionalFade = afValue;
				break;
			case InteriorDataTraits::FOG_RED:
				reinterpret_cast<RGBA&>(apData->uiFogColor).r = afValue;
				break;
			case InteriorDataTraits::FOG_GREEN:
				reinterpret_cast<RGBA&>(apData->uiFogColor).g = afValue;
				break;
			case InteriorDataTraits::FOG_BLUE:
				reinterpret_cast<RGBA&>(apData->uiFogColor).b = afValue;
				break;
			case InteriorDataTraits::FOG_NEAR:
				apData->fFogNear = afValue;
				break;
			case InteriorDataTraits::FOG_FAR:
				apData->fFogFar = afValue;
				break;
			case InteriorDataTraits::FOG_POWER:
				apData->fFogPower = afValue;
				break;
			case InteriorDataTraits::CLIP_DISTANCE:
				apData->fClipDist = afValue;
				break;
			default:
				return false;
		}
		return true;
	}

	double __fastcall GetLightingTemplateValue(BGSLightingTemplate* apTemplate, LightingTemplateTraits aeType) {
		return GetInteriorDataValue(&apTemplate->kData, ConvertTemplateType(aeType));
	}

	bool __fastcall SetLightingTemplateValue(BGSLightingTemplate* apTemplate, LightingTemplateTraits aeType, float afValue) {
		return SetInteriorDataValue(&apTemplate->kData, ConvertTemplateType(aeType), afValue);
	}
}

bool Cmd_SetLightingTemplateTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	LightingTemplateTraits eTrait = LightingTemplateTraits::NONE;
	BGSLightingTemplate* pTemplate = nullptr;
	float fValue = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTemplate, &eTrait, &fValue) && InRange(eTrait) && pTemplate && IS_TYPE(pTemplate, BGSLightingTemplate)) {
		*result = SetLightingTemplateValue(pTemplate, eTrait, fValue);
	}
	return true;
}

bool Cmd_GetLightingTemplateTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	LightingTemplateTraits eTrait = LightingTemplateTraits::NONE;
	BGSLightingTemplate* pTemplate = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTemplate, &eTrait) && InRange(eTrait) && pTemplate && IS_TYPE(pTemplate, BGSLightingTemplate)) {
		*result = GetLightingTemplateValue(pTemplate, eTrait);
	}
	return true;
}

bool Cmd_GetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	InteriorDataTraits eTrait = InteriorDataTraits::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, &eTrait) && InRange(eTrait) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		*result = GetInteriorDataValue(pCell->GetInteriorData(), eTrait);

		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetInteriorLightingTraitNumeric %d >> %.2f", eTrait, *result);
	}
	return true;
}

bool Cmd_SetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	InteriorDataTraits eTrait = InteriorDataTraits::NONE;
	float fValue = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, &eTrait, &fValue) && InRange(eTrait) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		*result = SetInteriorDataValue(pCell->GetInteriorData(), eTrait, fValue);

		if (Script::GetConsoleOuput())
			Interface::PrintLine("SetInteriorLightingTraitNumeric %d >> %.2f", eTrait, fValue);
	}
	return true;
}

bool Cmd_SetWorldspaceEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* zone = nullptr;
	TESWorldSpace* world;
	ExtractArgsEx(EXTRACT_ARGS_EX, &world, &zone);
	if (!world || !IS_TYPE(world, TESWorldSpace))
		return true;
	if (!zone || IS_TYPE(zone, BGSEncounterZone)) {
		world->pEncounterZone = zone;
		*result = 1;
	}
	return true;
}

bool Cmd_GetWorldspaceEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* world = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &world) && world && IS_TYPE(world, TESWorldSpace)) {
		BGSEncounterZone* zone = world->pEncounterZone;
		if (zone)
			*(FormID*)result = zone->GetFormID();
	}
	return true;
}

bool Cmd_SetCellEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* pZone = nullptr;
	TESObjectCELL* pCell = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, &pZone);
	if (!pCell || !IS_TYPE(pCell, TESObjectCELL))
		return true;

	if (!pZone || IS_TYPE(pZone, BGSEncounterZone)) {
		pCell->SetEncounterZone(pZone);
		*result = 1;
	}
	return true;
}

bool Cmd_SetRefEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* pZone = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pZone);
	if (!pZone || IS_TYPE(pZone, BGSEncounterZone)) {
		thisObj->GetExtra()->SetEncounterZone(pZone);
		*result = 1;
	}
	return true;
}

bool Cmd_GetRefEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* pZone = thisObj->GetExtra()->GetEncounterZone();
	if (pZone)
		*(FormID*)result = pZone->GetFormID();
	return true;
}

bool Cmd_SetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	char newPrompt[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &newPrompt)) {
		ExtraActivateRef* xActivateRef = thisObj->GetExtra()->GetExtraData<ExtraActivateRef>();
		if (xActivateRef) {
			xActivateRef->strActivationPrompt.Set(newPrompt);
		}
		else {
			xActivateRef = BSMemory::malloc<ExtraActivateRef>();
			ThisCall(0x4338B0, xActivateRef);
			xActivateRef->strActivationPrompt.Set(newPrompt);
			thisObj->GetExtra()->AddExtra(xActivateRef);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	ExtraActivateRef* xActivateRef = thisObj->GetExtra()->GetExtraData<ExtraActivateRef>();
	if (xActivateRef) {
		g_strInterface->Assign(PASS_COMMAND_ARGS, xActivateRef->strActivationPrompt.c_str());
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetRefActivationPromptOverride >> %s", xActivateRef->strActivationPrompt.c_str());
	}
	return true;
}

bool Cmd_GetWeaponAltTextures_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* pWeapon;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		auto pIter = pWeapon->GetTexSwapList();
		while (pIter && !pIter->IsEmpty()) {
			TEX_SWAP* pEntry = pIter->GetItem();
			pIter = pIter->GetNext();
			if (pEntry && pEntry->pTextureSet) {
				g_arrInterface->AppendElement(pArray, NVSEArrayElement(pEntry->pTextureSet));
			}
		}
	}
	g_arrInterface->AssignCommandResult(pArray, result);
	return true;
}

bool Cmd_GetIdleMarkerAnimations_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker;
	NVSEArrayVar* idleArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker) && marker && IS_TYPE(marker, BGSIdleMarker) && marker->GetIdleCount() > 0) {
		for (int i = 0; i < marker->GetIdleCount(); i++) {
			g_arrInterface->AppendElement(idleArr, NVSEArrayElement(marker->ppIdles[i]));
		}
	}
	g_arrInterface->AssignCommandResult(idleArr, result);
	return true;
}

bool Cmd_SetIdleMarkerAnimation_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker = nullptr;
	TESIdleForm* newAnim = nullptr;
	uint32_t animId;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &animId, &newAnim) && marker && IS_TYPE(marker, BGSIdleMarker) && marker->GetIdleCount() > animId) {
		marker->ppIdles[animId] = newAnim;
		*result = 1;
	}
	return true;
}

bool Cmd_SetIdleMarkerAnimations_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker = nullptr;
	uint32_t arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &arrID) && marker && IS_TYPE(marker, BGSIdleMarker)) {
		NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
		if (!inArr) return true;
		uint32_t size = g_arrInterface->GetArraySize(inArr);
		if (!size) return true;

		BSScrapBuffer<NVSEArrayElement> elements(size);
		g_arrInterface->GetElements(inArr, elements.get(), nullptr);
		TESIdleForm** idleList = BSMemory::malloc<TESIdleForm*>(size);
		for (uint32_t i = 0; i < size; i++) {
			idleList[i] = (TESIdleForm*)elements[i].GetTESForm();
		}
		if (marker->ppIdles) 
			BSMemory::free(marker->ppIdles);
		marker->ppIdles = idleList;
		marker->ucIdleCount = size;
		*result = 1;
	}

	return true;
}

bool Cmd_GetIdleMarkerTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker = nullptr;
	uint32_t traitID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &traitID) && marker && IS_TYPE(marker, BGSIdleMarker)) {
		switch (traitID) {
		case 1:
			*result = marker->ucIdleFlags.Get();
			break;
		case 2:
			*result = marker->fTimerCheckForIdle;
			break;
		case 3:
			*result = marker->GetIdleCount();
			break;
		default:
			return true;
		}
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetIdleMarkerTraitNumeric %d >> %.2f", traitID, *result);
	}
	return true;
}

bool Cmd_SetIdleMarkerTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker = nullptr;
	uint32_t traitID;
	float newVal;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &traitID, &newVal) && marker && IS_TYPE(marker, BGSIdleMarker)) {
		switch (traitID) {
		case 1:
			marker->ucIdleFlags = newVal;
			break;
		case 2:
			marker->fTimerCheckForIdle = newVal;
			break;
		default:
			return true;
		}
		*result = 1;
	}
	return true;
}
TESModelTextureSwap* GetArmorModel(TESObjectARMO* armor, uint32_t id) {
	switch (id) {
	case 1:
		return &armor->kBipedModels[SEX::MALE];
	case 2:
		return &armor->kBipedModels[SEX::FEMALE];
	case 3:
		return &armor->kWorldModels[SEX::MALE];
	case 4:
		return &armor->kWorldModels[SEX::FEMALE];
	default:
		return nullptr;
	}
}

bool Cmd_GetAltTexturesEx_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	uint32_t uiWhichModel;
	NVSEArrayVar* pMap = g_arrInterface->CreateMap(nullptr, nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &uiWhichModel) && pForm) {
		const TESModelTextureSwap* pModel = nullptr;
		if (IS_ID(pForm, TESObjectARMO) || IS_ID(pForm, TESObjectARMA)) {
			TESObjectARMO* pArmor = static_cast<TESObjectARMO*>(pForm);
			pModel = GetArmorModel(pArmor, uiWhichModel);
		}
		else if (IS_ID(pForm, TESObjectWEAP)) {
			TESObjectWEAP* pWeapon = static_cast<TESObjectWEAP*>(pForm);
			pModel = pWeapon;
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
	g_arrInterface->AssignCommandResult(pMap, result);
	return true;
}

bool Cmd_GetArmorAltTextures_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectARMO* pArmor = nullptr;
	uint32_t uiWhichModel;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
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
	g_arrInterface->AssignCommandResult(pArray, result);
	return true;
}

bool Cmd_SetWeaponAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* pWeapon = nullptr;
	BGSTextureSet* pTextureSet = nullptr;
	int32_t iIndex = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &iIndex, &pTextureSet) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP) && pTextureSet && IS_TYPE(pTextureSet, BGSTextureSet)) {
		TEX_SWAP* pSwap = pWeapon->GetTexSwap(iIndex);
		if (pSwap) {
			pSwap->pTextureSet = pTextureSet;
			*result = 1;
		}
		else {
			pWeapon->AddTexSwap("", iIndex, pTextureSet);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_SetArmorAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
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
			*result = 1;
		}
		else {
			pModel->AddTexSwap("", iIndex, pTextureSet);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_ClearWeaponAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* pWeapon;
	int32_t iIndex = -2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &iIndex) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		if (iIndex == -1) {
			pWeapon->ClearTexSwapList();
			*result = 1;
			return true;
		}
		else {
			pWeapon->RemoveTexSwap(iIndex);
			*result = 1;
			return true;
		}
	}
	return true;
}

bool Cmd_ClearArmorAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectARMO* pArmor = nullptr;
	int32_t iIndex = -2;
	uint32_t uiWhichModel;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pArmor, &uiWhichModel, &iIndex) && pArmor && IS_TYPE(pArmor, TESObjectARMO)) {
		TESModelTextureSwap* pModel = GetArmorModel(pArmor, uiWhichModel);
		if (!pModel)
			return true;

		if (iIndex == -1) {
			pModel->ClearTexSwapList();
			*result = 1;
			return true;
		}
		else {
			pModel->RemoveTexSwap(iIndex);
			*result = 1;
			return true;
		}
	}
	return true;
}

bool Cmd_SetEffectShaderTexturePath_Execute(COMMAND_ARGS) {
	*result = 0;
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
		*result = 1;
	}
	return true;
}

bool Cmd_GetEffectShaderTexturePath_Execute(COMMAND_ARGS) {
	*result = 0;
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
	*result = 0;
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
		*result = 1;
	}
	return true;
}

bool Cmd_GetEffectShaderTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESEffectShader* pShader;
	uint32_t traitID;
	uint32_t color;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pShader, &traitID) && pShader && IS_TYPE(pShader, TESEffectShader) && traitID >= 0 && traitID <= 76) {
		switch (traitID) {
		case 0:
			*result = pShader->GetData()->ucFlags;
			break;
		case 61:
			if (pShader->GetAddonModels())
				*result = pShader->GetAddonModels()->GetFormID();
			break;
		case 4:
		case 14:
		case 47:
		case 48:
		case 49:
			color = SwapRGB(((uint32_t*)pShader)[6 + traitID]);
			*result = color;
			if (Script::GetConsoleOuput()) Interface::PrintLine("GetEffectShaderTraitNumeric %d >> 0x%X", traitID, color);
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
			*result = ((uint32_t*)pShader)[6 + traitID];
			break;
		default:
			*result = ((float*)pShader)[6 + traitID];
			break;
		}
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetEffectShaderTraitNumeric %d >> %.2f", traitID, *result);
	}
	return true;
}

bool Cmd_GetAvailablePerks_Execute(COMMAND_ARGS) {
	*result = 0;
	Actor* pTarget = PlayerCharacter::GetSingleton();
	if (thisObj && thisObj->IsActor())
		pTarget = static_cast<Actor*>(thisObj);

	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);

	if (pTarget) {
		const uint32_t uiActorLevel = pTarget->GetActorLevel();
		auto pIter = TESDataHandler::GetSingleton()->kPerks.GetHead();
		while (pIter && !pIter->IsEmpty()) {
			BGSPerk* pPerk = pIter->GetItem();
			pIter = pIter->GetNext();

			if (pPerk->GetLevel() <= 0)
				continue;

			const uint8_t ucRank = pTarget->GetPerkRank(pPerk, false);
			if (ucRank < pPerk->GetNumRanks() && !pPerk->GetIsTrait() && pPerk->IsPerkAttainable(pTarget) && pPerk->GetIsPlayable()) {
				if (pPerk->IsPerkAvailable(pTarget) && pPerk->GetLevel() <= uiActorLevel)
					g_arrInterface->AppendElement(pArray, NVSEArrayElement(pPerk));
			}
		}
	}

	g_arrInterface->AssignCommandResult(pArray, result);
	return true;
}

bool Cmd_FaceGenRefreshAppearance_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj && thisObj->IsCharacter()) {
		ThisCall(0x08D3FA0, thisObj);
		*result = 1;
	}
	return true;
}

bool Cmd_FaceGenGetNthProperty_Execute(COMMAND_ARGS) {
	TESNPC* npc = nullptr;
	uint32_t PropertyListIndex = 0;
	uint32_t PropertyIndex = 0;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &npc, &PropertyListIndex, &PropertyIndex) && npc && IS_TYPE(npc, TESNPC) && PropertyListIndex < 3) {

		uintptr_t propertyListMinorIdx = PropertyListIndex % 2;
		uintptr_t propertyListMajorIdx = (PropertyIndex - propertyListMinorIdx) / 2;
		if (auto FaceGenPTR = TESNPC_GetFaceGenData(npc)) {
			*result = CdeclCall<float>(0x652230, FaceGenPTR, propertyListMajorIdx, propertyListMinorIdx, PropertyIndex);
			if (Script::GetConsoleOuput())
				Interface::PrintLine("GetFaceGenNthProperty %.2f", *result);
		}
	}
	return true;
}

bool Cmd_FaceGenSetNthProperty_Execute(COMMAND_ARGS) {
	TESNPC* npc = nullptr;
	uint32_t PropertyListIndex = 0;
	uint32_t PropertyIndex = 0;
	float val = 0;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &npc, &PropertyListIndex, &PropertyIndex, &val) && npc && IS_TYPE(npc, TESNPC) && PropertyListIndex < 3) {
		uintptr_t propertyListMinorIdx = PropertyListIndex % 2;
		uintptr_t propertyListMajorIdx = (PropertyIndex - propertyListMinorIdx) / 2;

		if (auto FaceGenPTR = TESNPC_GetFaceGenData(npc)) {
			CdeclCall<void>(0x652320, FaceGenPTR, propertyListMajorIdx, PropertyListIndex, PropertyIndex, val);
			*result = 1;
			if (Script::GetConsoleOuput()) {
				Interface::PrintLine("SetFaceGenNthProperty called");
			}
		}
	}
	return true;
}

bool Cmd_GetPlayerKarmaTitle_Execute(COMMAND_ARGS) {
	*result = 0;
	char* title;
	uint32_t titleOrTier = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &titleOrTier);
	if (titleOrTier == 1) {
		int karmaTier = CdeclCall<int>(0x47E040, PlayerCharacter::GetSingleton()->GetActorValueF(ActorValue::Index::KARMA)); // GetKarmaTier
		switch (karmaTier) {
		case 0:
			title = *(char**)0x11D41B4; // sAlignGood
			break;
		case 1:
			title = *(char**)0x11D3208; // sAlignNeutral
			break;
		case 2:
			title = *(char**)0x11D4580; // sAlignEvil
			break;
		case 3:
			title = *(char**)0x11D5000; // sAlignVeryGood
			break;
		case 4:
			title = *(char**)0x11D31D8; // sAlignVeryEvil
			break;
		}
	}
	else {
		title = CdeclCall<char*>(0x47E0E0, PlayerCharacter::GetSingleton()); // Actor::GetKarmaTitle
	}
	if (Script::GetConsoleOuput()) Interface::PrintLine("GetPlayerKarmaTitle >> %s", title);
	g_strInterface->Assign(PASS_COMMAND_ARGS, title);
	return true;
}

bool Cmd_GetTalkingActivatorActor_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTalkingActivator* activator = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &activator) && activator && IS_TYPE(activator, BGSTalkingActivator)) {
		if (activator->GetTempRef()) {
			*(FormID*)result = activator->GetTempRef()->GetFormID();
		}
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetTalkingActivatorActor >> 0x%X", *result);
	}
	return true;
}

bool Cmd_GetActorEffectType_Execute(COMMAND_ARGS) {
	*result = 0;
	SpellItem* pSpell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSpell) && pSpell && IS_TYPE(pSpell, SpellItem)) {
		*result = pSpell->GetSpellType();
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetActorEffectType >> %.2f", *result);
	}
	else {
		*result = -1;
	}
	return true;
}

bool Cmd_GetBodyPartTraitString_Execute(COMMAND_ARGS) {
	*result = 0;
	const char* pText = nullptr;
	BGSBodyPartData* pPartData = nullptr;
	BODY_PART_TYPE ePartType;
	uint32_t uiStringType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pPartData, &ePartType, &uiStringType) && pPartData && InRange(ePartType)) {
		if (IS_ID(pPartData, BGSBodyPartData) && (uiStringType <= 5)) {
			const BGSBodyPart* pBodyPart = pPartData->GetBodyPart(ePartType);
			if (pBodyPart) {
				switch (uiStringType) {
				case 1:
					pText = pBodyPart->GetNodeName();
					break;
				case 2:
					pText = pBodyPart->GetTargetName();
					break;
				case 3:
					pText = pBodyPart->GetIKStartNodeName();
					break;
				case 4:
					pText = pBodyPart->GetPartName();
					break;
				case 5:
					pText = pBodyPart->GetGoreObjectName();
					break;
				default:
					break;
				}
			}
		}

		if (!pText)
			pText = "";

		g_strInterface->Assign(PASS_COMMAND_ARGS, pText);
	}
	return true;
}

bool Cmd_GetMessageIconPath_Execute(COMMAND_ARGS) {
	BOOL bFemale = FALSE;
	TESForm* pForm = nullptr;
	const char* pPath = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &bFemale) && pForm) {
		TESBipedModelForm* pBiped = TESBipedModelForm::GetFormAsBipedModel(pForm);
		if (pBiped) {
			const SEX eSex = bFemale ? SEX::FEMALE : SEX::MALE;
			pPath = pBiped->kMessageIcons[eSex].GetMessageIconTextureName();
		}
		else {
			BGSMessageIcon* pIcon = DYNAMIC_CAST(pForm, TESForm, BGSMessageIcon);
			if (pIcon)
				pPath = pIcon->GetMessageIconTextureName();
		}
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetMessageIconPath >> %s", pPath);
		g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
	}
	return true;
}

bool Cmd_SetMessageIconPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	BOOL bFemale = FALSE;
	TESForm* pForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &pForm, &bFemale) && pForm) {
		TESBipedModelForm* pBiped = TESBipedModelForm::GetFormAsBipedModel(pForm);
		if (pBiped) {
			const SEX eSex = bFemale ? SEX::FEMALE : SEX::MALE;
			pBiped->SetMessageIcon(eSex, cPath);
			*result = 1;
		}
		else {
			BGSMessageIcon* pIcon = DYNAMIC_CAST(pForm, TESForm, BGSMessageIcon);
			if (pIcon) {
				pIcon->SetMessageIconTextureName(cPath);
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_SetNoteRead_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* pNote = nullptr;
	BOOL bRead = FALSE;
	BOOL bSave = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pNote, &bRead, &bSave) && pNote) {
		{
			AutoSaveFormChanges kChanges(bSave);
			pNote->SetHasBeenRead(bRead > 0);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetQuestDelay_Execute(COMMAND_ARGS) {
	*result = 0;
	TESQuest* pQuest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pQuest) && pQuest && IS_TYPE(pQuest, TESQuest)) {
		*result = pQuest->GetScriptProcessingDelay();
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetQuestDelay >> %.3f", *result);
	}
	return true;
}

bool Cmd_GetWeaponVATSTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* pWeapon = nullptr;
	uint32_t uiTrait = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &uiTrait) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		switch (uiTrait) {
		case 1:
			*result = pWeapon->GetVATSSpecialAttackSkillRequirement();
			break;
		case 2:
			*result = pWeapon->GetVATSSpecialAttackDamageMultiplier();
			break;
		case 3:
			*result = pWeapon->GetVATSSpecialAttackAPCost();
			break;
		case 4:
			*result = pWeapon->GetVATSSpecialAttackSilent();
			break;
		case 5:
			*result = pWeapon->GetVATSSpecialAttackModRequirement();
			break;
		}
		if (Script::GetConsoleOuput()) 
			Interface::PrintLine("GetWeaponVATSTraitNumeric %d >> %f", uiTrait, *result);
	}
	return true;
}

bool Cmd_SetWeaponVATSTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* pWeapon = nullptr;
	uint32_t uiTrait = 0;
	float fValue;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &uiTrait, &fValue) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP)) {
		*result = 1;
		switch (uiTrait) {
		case 1:
			pWeapon->SetVATSSpecialAttackSkillRequirement(fValue);
			break;
		case 2:
			pWeapon->SetVATSSpecialAttackDamageMultiplier(fValue);
			break;
		case 3:
			pWeapon->SetVATSSpecialAttackAPCost(fValue);
			break;
		case 4:
			pWeapon->SetVATSSpecialAttackSilent(fValue > 0.f);
			break;
		case 5:
			pWeapon->SetVATSSpecialAttackModRequirement(fValue > 0.f);
			break;
		default:
			*result = 0;
			break;
		}
	}
	return true;
}

SPEC_NOINLINE bool Cmd_GetQuestFailed_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	TESQuest* pQuest = static_cast<TESQuest*>(arg1);
	if (pQuest && pQuest->GetFormType() == FORM_TYPE::TESQuest)
		*result = pQuest->GetFailed();
	return true;
}

bool Cmd_GetQuestFailed_Execute(COMMAND_ARGS) {
	TESQuest* pQuest = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pQuest);
	Cmd_GetQuestFailed_Eval(nullptr, pQuest, nullptr, result);
	if (Script::GetConsoleOuput())
		Interface::PrintLine("GetQuestFailed >> %.2f", *result);
	return true;
}

bool Cmd_GetWeaponWorldModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon = nullptr;
	const char* modelPath = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon) && weapon && IS_TYPE(weapon, TESObjectWEAP)) {
		modelPath = weapon->kWorldModel.GetModel();
		g_strInterface->Assign(PASS_COMMAND_ARGS, modelPath);
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetWeaponWorldModelPath >> %s", modelPath);
	}
	return true;
}

bool Cmd_SetWeaponWorldModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon = nullptr;
	char modelPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon, &modelPath) && weapon && IS_TYPE(weapon, TESObjectWEAP)) {
		weapon->kWorldModel.SetModel(modelPath);
		*result = 1;
	}
	return true;
}

bool Cmd_SetProjectileSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSProjectile* pProjectile = nullptr;
	TESSound* pSound = nullptr;
	int uiSoundType = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pProjectile, &uiSoundType, &pSound) && pProjectile && IS_TYPE(pProjectile, BGSProjectile) && pSound && IS_TYPE(pSound, TESSound) && uiSoundType <= 3) {
		*result = 1;
		switch (uiSoundType) {
		case 1:
			pProjectile->SetActiveSound(pSound);
			break;
		case 2:
			pProjectile->SetCountdownSound(pSound);
			break;
		case 3:
			pProjectile->SetDeactivateSound(pSound);
			break;
		default:
			*result = 0;
			break;
		}
	}
	return true;
}

bool Cmd_SetExplosionSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSExplosion* pExplosion = nullptr;
	TESSound* pSound = nullptr;
	uint32_t uiSoundType = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pExplosion, &uiSoundType, &pSound) && pExplosion && IS_TYPE(pExplosion, BGSExplosion) && pSound && IS_TYPE(pSound, TESSound) && uiSoundType <= 2) {
		if (uiSoundType == 1)
			pExplosion->SetSound1(pSound);
		else
			pExplosion->SetSound2(pSound);
		*result = 1;
	}
	return true;
}

bool Cmd_GetCreatureCombatSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCreature* pCreature = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pCreature);

	if (!pCreature) {
		if (!thisObj || !thisObj->IsCreature()) 
			return true;
		
		pCreature = static_cast<TESCreature*>(static_cast<Actor*>(thisObj)->GetTemplateObjectReference());
	}

	if (pCreature && pCreature->GetFormType() == FORM_TYPE::TESCreature)
		*result = pCreature->kData.ucCombatSkill;

	return true;
}

bool Cmd_SetContainerSound_Execute(COMMAND_ARGS) {
	int32_t iSoundType = -1;
	TESObjectCONT* pContainer = nullptr;
	TESSound* pSound = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pContainer, &iSoundType, &pSound) && pContainer && IS_ID(pContainer, TESObjectCONT)) {
		if (pSound && !IS_ID(pSound, TESSound))
			return true;

		*result = 1;
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
			*result = 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetContainerSound_Execute(COMMAND_ARGS) {
	*result = 0;
	int32_t iSoundType = -1;
	TESObjectCONT* pContainer = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pContainer, &iSoundType) && pContainer && IS_ID(pContainer, TESObjectCONT)) {
		TESSound* pSound = nullptr;
		switch (iSoundType) {
		case 0:
			pSound = pContainer->GetOpenSound();
			break;
		case 1:
			pSound = pContainer->GetCloseSound();
			break;
		case 2:
			pSound = pContainer->GetLoopSound();
			break;
		}

		if (pSound)
			*reinterpret_cast<FormID*>(result) = pSound->GetFormID();
	}
	return true;
}

bool Cmd_GetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* pRace = nullptr;
	uint32_t uiBit = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &uiBit) && pRace && IS_TYPE(pRace, TESRace)) {
		*result = pRace->kData.uiFlags.GetBit(uiBit);
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetRaceFlag >> %.f", *result);
	}
	return true;
}

bool Cmd_SetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* pRace = nullptr;
	uint32_t uiBit = 0;
	BOOL bSet = FALSE;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &uiBit, &bSet) && pRace && IS_TYPE(pRace, TESRace)) {
		pRace->kData.uiFlags.SetBit(uiBit, bSet);
		*result = 1;
	}
	return true;
}

// 0 - alive, 1 - dying/ragdolled, 2 - dead, 3 - unconscious, 5 - restrained, 6 - essential unconscious
SPEC_NOINLINE bool Cmd_GetLifeState_Eval(COMMAND_ARGS_EVAL) {
	*result = -1;
	if (thisObj && thisObj->IsActor())
		*result = static_cast<Actor*>(thisObj)->GetLifeState();
	return true;
}

bool Cmd_GetLifeState_Execute(COMMAND_ARGS) {
	Cmd_GetLifeState_Eval(thisObj, nullptr, nullptr, result);
	if (Script::GetConsoleOuput()) 
		Interface::PrintLine("GetLifeState >> %.f", *result);
	return true;
}

bool Cmd_GetFactionMembers_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* pFaction = nullptr;
	int32_t iRank = -1;
	NVSEArrayVar* factionMemberArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
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
	g_arrInterface->AssignCommandResult(factionMemberArr, result);
	return true;
}

bool Cmd_SetEquipType_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	BGSEquipType::Type eType = BGSEquipType::Type::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &eType) && pForm && InRange(eType)) {
		BGSEquipType* pEquipType = DYNAMIC_CAST(GetTESObject(pForm), TESForm, BGSEquipType);
		if (pEquipType) {
			pEquipType->SetEquipType(eType);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetRaceHeadModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRace* pRace = nullptr;
	TESRace::HeadPart ePart;
	SEX eSex;
	const char* pPath = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &ePart, &eSex) && pRace && IS_TYPE(pRace, TESRace)) {
		if (InRange(eSex) && ePart < TESRace::HeadPart::COUNT) {
			pPath = pRace->GetHeadPartModel(eSex, ePart)->GetModel();
			g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
			if (Script::GetConsoleOuput()) {
				Interface::PrintLine("GetRaceHeadModelPath %i %i >> %s", ePart, eSex, pPath);
			}
		}
	}
	return true;
}

bool Cmd_GetRaceBodyModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRace* pRace = nullptr;
	TESRace::BodyPart ePart;
	SEX eSex;
	const char* pPath = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pRace, &ePart, &eSex) && pRace && IS_TYPE(pRace, TESRace)) {
		if (InRange(eSex) && ePart < TESRace::BodyPart::COUNT) {
			pPath = pRace->GetBodyPartModel(eSex, ePart)->GetModel();
			g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
			if (Script::GetConsoleOuput()) {
				Interface::PrintLine("GetRaceBodyModelPath %i %i >> %s", ePart, eSex, pPath);
			}
		}
	}
	return true;
}

bool Cmd_GetFacegenModelFlag_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	uint32_t uiBit = 0;
	BOOL bFemale = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &uiBit, &bFemale) && pForm && uiBit < 8) {
		TESBipedModelForm* pBipedModel = TESBipedModelForm::GetFormAsBipedModel(pForm);
		if (pBipedModel) {
			const SEX eSex = bFemale ? SEX::FEMALE : SEX::MALE;
			*result = pBipedModel->kBipedModels[eSex].ucFlags.GetBit(uiBit);
			if (Script::GetConsoleOuput())
				Interface::PrintLine("GetFacegenModelFlag %i %i >> %.f", uiBit, bFemale, *result);
		}
	}
	return true;
}

bool Cmd_SetFacegenModelFlag_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	uint32_t uiBit = 0;
	BOOL bFemale = FALSE;
	BOOL bEnable = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &uiBit, &bFemale, &bEnable) && pForm && uiBit < 8) {
		TESBipedModelForm* pBipedModel = TESBipedModelForm::GetFormAsBipedModel(pForm);
		if (pBipedModel) {
			const SEX eSex = bFemale ? SEX::FEMALE : SEX::MALE;
			pBipedModel->kBipedModels[eSex].ucFlags.SetBit(uiBit, bEnable);
			*result = 1;
		}
	}
	return true;
}

SPEC_NOINLINE bool Cmd_GetBaseScale_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	TESActorBase* pBase = reinterpret_cast<TESActorBase*>(arg1);
	if (pBase) {
		FORM_TYPE eType = pBase->GetFormType();
		if (eType == FORM_TYPE::TESNPC)
			*result = static_cast<TESNPC*>(pBase)->GetHeight();
		else if (eType == FORM_TYPE::TESCreature)
			*result = static_cast<TESCreature*>(pBase)->GetBaseScale();
	}
	else if (thisObj) {
		*result = GetBaseScale(thisObj);
	}
	return true;
}

bool Cmd_GetBaseScale_Execute(COMMAND_ARGS) {
	TESActorBase* pBase = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pBase);
	Cmd_GetBaseScale_Eval(thisObj, pBase, nullptr, result);
	if (Script::GetConsoleOuput())
		Interface::PrintLine("GetBaseScale : %0.2f", *result);
	return true;
}

bool Cmd_RemovePrimitive_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj->GetExtra()->HasExtra<ExtraPrimitive>()) {
		ExtraPrimitive* pPrimitive = thisObj->GetExtra()->GetExtraData<ExtraPrimitive>();
		thisObj->GetExtra()->RemoveExtra(pPrimitive, true);
		UpdateReference3D(thisObj);
		*result = 1;
	}
	return true;
}
bool Cmd_GetPrimitiveType_Execute(COMMAND_ARGS) {
	ExtraPrimitive* pPrimitive = thisObj->GetExtra()->GetExtraData<ExtraPrimitive>();
	*result = (pPrimitive && pPrimitive->pPrimitive) ? pPrimitive->pPrimitive->GetType() : 0;
	return true;
}

bool Cmd_GetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusic = nullptr;
	const char* pPath = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusic) && pMusic && IS_TYPE(pMusic, BGSMusicType)) {
		pPath = pMusic->GetSoundFile();
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetMusicTypePath >> %s", pPath);
	}
	g_strInterface->Assign(PASS_COMMAND_ARGS, pPath);
	return true;
}

bool Cmd_GetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusic = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusic) && pMusic && IS_TYPE(pMusic, BGSMusicType)) {
		*result = pMusic->fAttenuation;
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetMusicTypeDB >> %f", *result);
	}
	return true;
}

bool Cmd_SetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusic = nullptr;
	float fAttenuation = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusic, &fAttenuation) && pMusic && IS_TYPE(pMusic, BGSMusicType)) {
		pMusic->fAttenuation = fAttenuation;
		*result = 1;
	}
	return true;
}

bool Cmd_SetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* pMusic = nullptr;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMusic, &cPath) && pMusic && IS_TYPE(pMusic, BGSMusicType)) {
		pMusic->SetSoundFile(cPath);
		*result = 1;
	}
	return true;
}

// JIP function with a fix for detrimental effects, deprecated
bool Cmd_GetActorValueModifierAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	return true;
}

// JIP function with a sanity check to prevent errors, deprecated
bool Cmd_GetBufferedCellsAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	return true;
}

bool Cmd_SetWeapon1stPersonModel_Execute(COMMAND_ARGS) {
	TESObjectWEAP* pWeapon = nullptr;
	uint32_t uiType = -1;
	TESObjectSTAT* pStatic = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &uiType, &pStatic) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP) && (!pStatic || IS_TYPE(pStatic, TESObjectSTAT)) && uiType <= 7) {
		*result = 1;
		switch (uiType) {
		case 0:
			pWeapon->p1stPersonObject = pStatic;
			break;
		case 1:
			pWeapon->p1stPersonModObjects[0] = pStatic;
			break;
		case 2:
			pWeapon->p1stPersonModObjects[1] = pStatic;
			break;
		case 3:
			pWeapon->p1stPersonModObjects[3] = pStatic;
			break;
		case 4:
			pWeapon->p1stPersonModObjects[2] = pStatic;
			break;
		case 5:
			pWeapon->p1stPersonModObjects[5] = pStatic;
			break;
		case 6:
			pWeapon->p1stPersonModObjects[4] = pStatic;
			break;
		case 7:
			pWeapon->p1stPersonModObjects[6] = pStatic;
			break;
		default:
			*result = 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetWeapon1stPersonModel_Execute(COMMAND_ARGS) {
	TESObjectWEAP* pWeapon = nullptr;
	uint32_t uiType = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pWeapon, &uiType) && pWeapon && IS_TYPE(pWeapon, TESObjectWEAP) && uiType <= 7) {
		TESObjectSTAT* pStatic = nullptr;
		switch (uiType) {
		case 0:
			pStatic = pWeapon->p1stPersonObject;
			break;
		case 1:
			pStatic = pWeapon->p1stPersonModObjects[0];
			break;
		case 2:
			pStatic = pWeapon->p1stPersonModObjects[1];
			break;
		case 3:
			pStatic = pWeapon->p1stPersonModObjects[3];
			break;
		case 4:
			pStatic = pWeapon->p1stPersonModObjects[2];
			break;
		case 5:
			pStatic = pWeapon->p1stPersonModObjects[5];
			break;
		case 6:
			pStatic = pWeapon->p1stPersonModObjects[4];
			break;
		case 7:
			pStatic = pWeapon->p1stPersonModObjects[6];
			break;
		}

		if (pStatic)
			*reinterpret_cast<FormID*>(result) = pStatic->GetFormID();
	}
	return true;
}

bool Cmd_GetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &imod) && imod && IS_TYPE(imod, TESImageSpaceModifier)) {
		*result = imod->animable;
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetIMODAnimatable >> %.f", *result);
	}
	return true;
}

bool Cmd_SetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod = nullptr;
	int newVal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &imod, &newVal) && imod && IS_TYPE(imod, TESImageSpaceModifier) && (newVal == 0 || newVal == 1)) {
		imod->animable = newVal;
		*result = 1;
		if (Script::GetConsoleOuput())
			Interface::PrintLine("SetIMODAnimatable >> %d", imod->animable);
	}
	return true;
}

// A modified version of GetCalculatedWeaponDamage, all credits go to JazzIsParis
bool Cmd_GetCalculatedWeaponDPS_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &weapon)) return true;
	float condition = 1.0F;
	ExtraDataList* extendPtr = nullptr;
	if (!weapon) {
		if (!thisObj) return true;
		InventoryRef* invRef = InventoryRefGetForID(thisObj->GetFormID());
		if (!invRef) {
			TESForm* base = thisObj->GetObjectReference();
			if (IS_ID(base, TESObjectWEAP))
				weapon = (TESObjectWEAP*)base;
			else
				return true;

			condition = thisObj->GetHealth();
		}
		else {
			weapon = (TESObjectWEAP*)invRef->pForm;
			if NOT_ID(weapon, TESObjectWEAP) return true;
			if (invRef->pExtraDataList) {
				condition = invRef->pItemChange->GetItemHealth(true) / 100.0F;
				extendPtr = invRef->pExtraDataList;
			}
		}
	}
	else if NOT_ID(weapon, TESObjectWEAP) return true;
	MiddleHighProcess* midHiProc = (MiddleHighProcess*)PlayerCharacter::GetSingleton()->GetCurrentAIProcess();
	ItemChange* weaponInfo = midHiProc->GetCurrentWeapon();
	TESForm* ammo = nullptr;
	if (!extendPtr && weaponInfo && (weaponInfo->pObject == weapon) && midHiProc->GetCurrentAmmo())
		ammo = midHiProc->GetCurrentAmmo()->pObject;
	if (!ammo)
		ammo = weapon->GetCurrentAmmo(nullptr);
	midHiProc->pCurrentWeapon = nullptr;
	*result = GetWeaponDPS(PlayerCharacter::GetSingleton(), weapon, condition, 1, weaponInfo, 0, 0, -1, 0.0, 0.0, 0, 0, ammo);
	midHiProc->pCurrentWeapon = weaponInfo;
	if (Script::GetConsoleOuput())
		Interface::PrintLine("GetCalculatedWeaponDPS >> %f", *result);
	return true;
}

bool Cmd_IsCellVisited_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		if (pCell->GetSeenData())
			*result = 1;

		if (Script::GetConsoleOuput())
			Interface::PrintLine("IsCellVisited >> %.0f", *result);
	}
	return true;
}

bool Cmd_IsCellExpired_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	uint32_t iHoursToRespawnCell = *(uint32_t*)0x11CA164;
	int32_t detachTime = 0;
	float gameHoursPassed = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		const uint32_t uiDetachTime = pCell->GetDetachTime();
		if (uiDetachTime == 0) {
			*result = -1;
		}
		else if (uiDetachTime == uint32_t(-1) || uiDetachTime == uint32_t(-2)) { // -1 is used by ResetInterior, -2 by ShowOff's ResetInteriorAlt.
			*result = 1;
		}
		else {
			const uint32_t uiHoursToRespawnCell = TESObjectCELL::GetHoursToClearCorpses();
			const uint32_t uiGameHoursPassed = Calendar::GetSingleton()->GetHoursPassed();
			*result = (uiGameHoursPassed - uiDetachTime) >= uiHoursToRespawnCell;
		}
		if (Script::GetConsoleOuput())
			Interface::PrintLine("IsCellExpired >> %.0f", *result);
	}
	return true;
}

bool Cmd_GetBaseEffectAV_Execute(COMMAND_ARGS) {
	*result = -1;
	EffectSetting* pEffect = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pEffect) && pEffect && IS_TYPE(pEffect, EffectSetting)) {
		if (pEffect->IsAssociatedActorValueUsed())
			*result = pEffect->GetAssociatedActorValue();
	}
	return true;
}

bool Cmd_GetBaseEffectArchetype_Execute(COMMAND_ARGS) {
	*result = -1;
	EffectSetting* pEffect = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pEffect) && pEffect && IS_TYPE(pEffect, EffectSetting))
		*result = pEffect->GetEffectArchetype();
	return true;
}

bool Cmd_GetHotkeySlot_Execute(COMMAND_ARGS)
{
	*result = 0;

	if (!thisObj)
		return true;

	InventoryRef* pInvRef = InventoryRefGetForID(thisObj->GetFormID());
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
		*result = pHotkey->ucIndex + 1;

	return true;
}

bool Cmd_GetMineArmedEx_Execute(COMMAND_ARGS) {
	*result = 0;
	if (!IS_ID(thisObj, GrenadeProjectile))
		return true;

	const GrenadeProjectile* pGrenade = static_cast<GrenadeProjectile*>(thisObj);
	const BGSProjectile* pBase = pGrenade->GetProjectileBase();
	if (!pBase)
		return true;
	
	if (!pGrenade->uiProjectileFlags.bTurnedOff && pGrenade->IsMine() && pBase->GetCanTurnOff())
		*result = 1;

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
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	CameraShotTrait eTraitID = CameraShotTrait::INVALID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &eTraitID) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		BGSCameraShot::Data& rData = pCameraShot->kData;
		switch (eTraitID) {
		case CameraShotTrait::ACTION:
			*result = rData.eAction;
			break;
		case CameraShotTrait::LOCATION:
			*result = rData.eLocation;
			break;
		case CameraShotTrait::TARGET:
			*result = rData.eTarget;
			break;
		case CameraShotTrait::PLAYER_TIME_MULT:
			*result = rData.fPlayerTimeMult;
			break;
		case CameraShotTrait::TARGET_TIME_MULT:
			*result = rData.fTargetTimeMult;
			break;
		case CameraShotTrait::GLOBAL_TIME_MULT:
			*result = rData.fGlobalTimeMult;
			break;
		case CameraShotTrait::MAX_TIME:
			*result = rData.fMaxTime;
			break;
		case CameraShotTrait::MIN_TIME:
			*result = rData.fMinTime;
			break;
		case CameraShotTrait::TARGET_PCT_BETWEEN_ACTORS:
			*result = rData.fTargetPercentBetweenActors;
			break;
		default:
			return true;
		}

		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetCameraShotTraitNumeric %d >> %.2f", eTraitID, *result);
	}
	return true;
}

bool Cmd_SetCameraShotTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	CameraShotTrait eTraitID = CameraShotTrait::INVALID;
	float fValue = 0.0f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &eTraitID, &fValue) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		BGSCameraShot::Data& rData = pCameraShot->kData;
		*result = 1;
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
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		*result = pCameraShot->kData.uiFlags;
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetCameraShotFlags >> %08X", pCameraShot->kData.uiFlags);
	}
	return true;
}

bool Cmd_SetCameraShotFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &uiFlags) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		pCameraShot->kData.uiFlags = uiFlags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetCameraShotPath_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		const char* pModel = pCameraShot->GetModel();
		g_strInterface->Assign(PASS_COMMAND_ARGS, pModel);
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetCameraShotPath >> %s", pModel);
	}
	return true;
}

bool Cmd_SetCameraShotPath_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	char cNewPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &cNewPath) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot) && cNewPath[0]) {
		pCameraShot->SetModel(cNewPath);
		*result = 1;
	}
	return true;
}

bool Cmd_GetCameraShotImageSpaceModifier_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		TESImageSpaceModifier* pIMOD = pCameraShot->GetFormImageSpaceModifier();
		if (pIMOD) {
			*reinterpret_cast<FormID*>(result) = pIMOD->GetFormID();
		}
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetCameraShotImageSpaceModifier >> %s", pIMOD ? pIMOD->GetFormEditorID() : "None");
	}
	return true;
}

bool Cmd_SetCameraShotImageSpaceModifier_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSCameraShot* pCameraShot = nullptr;
	TESImageSpaceModifier* pIMOD = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCameraShot, &pIMOD) && pCameraShot && IS_TYPE(pCameraShot, BGSCameraShot)) {
		if (pIMOD && !IS_TYPE(pIMOD, TESImageSpaceModifier))
			return true;

		pCameraShot->SetFormImageSpaceModifier(pIMOD);
		*result = 1;
	}
	return true;
}

namespace RefWalker {
	using ReferenceFilterFunc = bool(__fastcall*)(const struct FilterData& arFilter, TESObjectREFR* apRef);

	template<typename T>
	using ScrapVector = std::vector<T, BSScrapAllocator<T>>;

	struct ALIGN16 FilterData {
		FilterData(TESObjectREFR* apCaller, Script* apScript, float afConeSize, float afHeading, const NiPoint4& akPosAndDist, const TESForm* apSpace = nullptr)
			: pCaller(apCaller), pScript(apScript), fConeSize(afConeSize * 0.017453292f), fHeading(afHeading), kPosAndDist(akPosAndDist), pSpace(apSpace) {}

		ScrapVector<ReferenceFilterFunc>	kFilterFunctions;
		Script*								pScript;
		ScrapVector<FORM_TYPE>				kTypeFilters;
		TESObjectREFR*						pCaller;
		float								fConeSize;
		float								fHeading;
		PROCESS_TYPE 						eProcessLevel;
		const TESForm*						pSpace;
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

		bool __fastcall CheckParentCell(TESObjectREFR* apRef) const {
			return apRef->GetParentCell() == pSpace;
		}

		bool __fastcall CheckParentWorld(TESObjectREFR* apRef) const {
			return apRef->GetWorldSpace() == pSpace;
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
		auto pIter = apCell->GetRefList();
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

	bool __fastcall CellFilter(const FilterData& arFilter, TESObjectREFR* apRef) {
		return arFilter.CheckParentCell(apRef);
	}

	bool __fastcall WorldFilter(const FilterData& arFilter, TESObjectREFR* apRef) {
		return arFilter.CheckParentWorld(apRef);
	}
}


bool Cmd_CallPerRef_Execute(COMMAND_ARGS) {
	using namespace RefWalker;
	*result = 0;
	Script* pScript = nullptr;
	TESObjectCELL* pCell = nullptr;
	FORM_TYPE eFormFilter = FORM_TYPE::NONE;
	float fDistanceFilter = 0.f;
	float fAngleFilter = -FLT_MAX;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pScript, &eFormFilter, &fDistanceFilter, &fAngleFilter, &pCell) && pScript && IS_TYPE(pScript, Script)) {
		if (fDistanceFilter < 0.f)
			fDistanceFilter = 0.f;

		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();
		const NiPoint4 kPosAndDist(pCaller->GetPosition(), fDistanceFilter * fDistanceFilter);

		if (pCell && !IS_TYPE(pCell, TESObjectCELL))
			pCell = nullptr;

		if (!pCell && TES::GetSingleton()->currentInterior)
			pCell = TES::GetSingleton()->currentInterior;

		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->GetRotation().z, kPosAndDist);
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
			*result = IterateCells(pCell, kFilterData);
		}
	}
	return true;
}

bool Cmd_CallPerRefEx_Execute(COMMAND_ARGS) {
	using namespace RefWalker;

	*result = 0;
	PluginExpressionEvaluator kEval(PASS_COMMAND_ARGS);
	if (!kEval.ExtractArgs())
		return true;

	Script* pScript = reinterpret_cast<Script*>(kEval.GetNthArg(0)->GetTESForm());
	if (pScript && IS_TYPE(pScript, Script)) {
		NVSEArrayVar* pTypeArray = kEval.GetNthArg(1)->GetArrayVar();
		uint32_t uiArraySize = g_arrInterface->GetArraySize(pTypeArray);
		if (!uiArraySize)
			return true;

		float fDistanceFilter = 0.f;
		{
			PluginScriptToken* pToken = kEval.GetNthArg(2);
			if (pToken)
				fDistanceFilter = pToken->GetFloat();
		}

		float fAngleFilter = -FLT_MAX;
		{
			PluginScriptToken* pToken = kEval.GetNthArg(3);
			if (pToken)
				fAngleFilter = pToken->GetFloat();
		}
		TESObjectCELL* pCell = nullptr;
		{
			PluginScriptToken* pToken = kEval.GetNthArg(4);
			if (pToken)
				pCell = reinterpret_cast<TESObjectCELL*>(pToken->GetTESForm());
		}

		if (fDistanceFilter < 0.f)
			fDistanceFilter = 0.f;

		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();
		const NiPoint4 kPosAndDist(pCaller->GetPosition(), fDistanceFilter * fDistanceFilter);

		if (pCell && !IS_TYPE(pCell, TESObjectCELL))
			pCell = nullptr;

		if (!pCell && TES::GetSingleton()->currentInterior)
			pCell = TES::GetSingleton()->currentInterior;

		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->GetRotation().z, kPosAndDist);
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
			*result = IterateCells(pCell, kFilterData);
		}
	}
	return true;
}

bool Cmd_CallPerMobileObject_Execute(COMMAND_ARGS) {
	using namespace RefWalker;
	*result = 0;
	Script* pScript = nullptr;
	PROCESS_TYPE eProcessLevel = PROCESS_TYPE::INVALID;
	TESForm* pSpace = nullptr;
	FORM_TYPE eFormFilter = FORM_TYPE::NONE;
	float fDistanceFilter = 0.f;
	float fAngleFilter = -FLT_MAX;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pScript, &eProcessLevel, &eFormFilter, &fDistanceFilter, &fAngleFilter, &pSpace) && pScript && IS_TYPE(pScript, Script)) {
		if (fDistanceFilter < 0.f)
			fDistanceFilter = 0.f;

		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();
		const NiPoint4 kPosAndDist(pCaller->GetPosition(), fDistanceFilter * fDistanceFilter);
		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->GetRotation().z, kPosAndDist, pSpace);
		if (eFormFilter)
			kFilterData.kTypeFilters.push_back(eFormFilter);

		if (!kFilterData.kTypeFilters.empty())
			kFilterData.kFilterFunctions.push_back(TypeFilter);

		if (pSpace) {
			if (pSpace->GetFormType() == FORM_TYPE::TESObjectCELL)
				kFilterData.kFilterFunctions.push_back(CellFilter);
			else if (pSpace->GetFormType() == FORM_TYPE::TESWorldSpace)
				kFilterData.kFilterFunctions.push_back(WorldFilter);

			if (fAngleFilter > 0.f && kPosAndDist.w > 0.f)
				kFilterData.kFilterFunctions.push_back(DistanceAndAngleFilter);
			else if (fAngleFilter > 0.f)
				kFilterData.kFilterFunctions.push_back(AngleFilter);
			else if (kPosAndDist.w > 0.f)
				kFilterData.kFilterFunctions.push_back(DistanceFilter);
		}

		{
			LambdaVariableContext kVarContext(pScript);
			*result = IterateMobileObjects(eProcessLevel, kFilterData);
		}
	}
	return true;
}

bool Cmd_CallPerMobileObjectEx_Execute(COMMAND_ARGS) {
	using namespace RefWalker;

	*result = 0;
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
		float fDistanceFilter = 0.f;
		{
			PluginScriptToken* pToken = kEval.GetNthArg(3);
			if (pToken)
				fDistanceFilter = pToken->GetFloat();
		}

		float fAngleFilter = -FLT_MAX;
		{
			PluginScriptToken* pToken = kEval.GetNthArg(4);
			if (pToken)
				fAngleFilter = pToken->GetFloat();
		}

		TESForm* pSpace = nullptr;
		{
			PluginScriptToken* pToken = kEval.GetNthArg(5);
			if (pToken)
				pSpace = reinterpret_cast<TESObjectCELL*>(pToken->GetTESForm());
		}

		if (fDistanceFilter < 0.f)
			fDistanceFilter = 0.f;

		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();
		const NiPoint4 kPosAndDist(pCaller->GetPosition(), fDistanceFilter * fDistanceFilter);
		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->GetRotation().z, kPosAndDist, pSpace);

		BSScrapBuffer<NVSEArrayElement> kElements(uiArraySize);
		g_arrInterface->GetElements(pTypeArray, kElements.get(), nullptr);
		kFilterData.kTypeFilters.resize(uiArraySize);
		for (uint32_t i = 0; i < uiArraySize; i++) {
			kFilterData.kTypeFilters[i] = static_cast<FORM_TYPE>(kElements[i].GetNumber());
		}

		if (!kFilterData.kTypeFilters.empty())
			kFilterData.kFilterFunctions.push_back(TypeFilter);

		if (pSpace) {
			if (pSpace->GetFormType() == FORM_TYPE::TESObjectCELL)
				kFilterData.kFilterFunctions.push_back(CellFilter);
			else if (pSpace->GetFormType() == FORM_TYPE::TESWorldSpace)
				kFilterData.kFilterFunctions.push_back(WorldFilter);

			if (fAngleFilter > 0.f && kPosAndDist.w > 0.f)
				kFilterData.kFilterFunctions.push_back(DistanceAndAngleFilter);
			else if (fAngleFilter > 0.f)
				kFilterData.kFilterFunctions.push_back(AngleFilter);
			else if (kPosAndDist.w > 0.f)
				kFilterData.kFilterFunctions.push_back(DistanceFilter);
		}

		{
			LambdaVariableContext kVarContext(pScript);
			*result = IterateMobileObjects(eProcessLevel, kFilterData);
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
		BGSLoadGameSubBuffer kSavedAnim;
		SaveAnimation(kSavedAnim, apReference, apReference->GetAnimation());

		UpdateReference3D(apReference);
		ThisCall(0x456520, *reinterpret_cast<DWORD**>(0x1202D98));

		NiAVObject* pRoot = apReference->Get3DVerySimple();
		if (pRoot && pRoot->IsFadeNode())
			static_cast<BSFadeNode*>(pRoot)->TurnFadeNodeOn();

		LoadAnimation(kSavedAnim, apReference, apReference->GetAnimation());
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

	*result = 0;
	uint32_t uiFlags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiFlags) && uiFlags) {
		if (!thisObj->Get3DVerySimple() || thisObj->IsStillLoading())
			return true;

		const bool bQueue = AILinearTaskThreadManager::ShouldQueue3DTask();
		if (thisObj->IsActor()) {
			Actor* pActor = static_cast<Actor*>(thisObj);
			if (pActor->GetCurrentAIProcess()) {
				// Creatures can't refresh their models in vanilla, so we have to handle them ourselves.
				if (pActor->IsCreature()) {
					RequestModelUpdate(thisObj, uiFlags, bQueue);
				}
				else {
					pActor->GetCurrentAIProcess()->Set3DUpdateFlag(uiFlags);
					if (!bQueue)
						pActor->GetCurrentAIProcess()->Update3DModel(pActor);


					const uint32_t uiCustomFlags = uiFlags & uiAddedFlags;
					if (uiCustomFlags)
						RequestModelUpdate(thisObj, uiCustomFlags, bQueue);
				}
			}
		}
		else {
			RequestModelUpdate(thisObj, uiFlags, bQueue);
		}

		*result = bQueue ? 2 : 1;
	}
	return true;
}

bool Cmd_GetRecipeCategoryFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRecipeCategory* pCategory = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCategory) && pCategory && IS_TYPE(pCategory, TESRecipeCategory)) {
		*result = pCategory->ucFlags;
		if (Script::GetConsoleOuput()) Interface::PrintLine("GetRecipeCategoryFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_RemapLand_Execute(COMMAND_ARGS) {
	*result = 0;
	FormID uiLandID = 0;
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
			if (Script::GetConsoleOuput())
				Interface::PrintLine("RemapLand >> You must provide valid cell coordinates");
			return true;
		}

		TESForm* pFoundForm = TESForm::GetFormByNumericID(uiLandID);
		bool bFoundLand = false;
		if (pFoundForm) {
			if (pFoundForm->GetFormType() == FORM_TYPE::TESObjectLAND) {
				bFoundLand = true;
			}
			else {
				if (Script::GetConsoleOuput())
					Interface::PrintLine("RemapLand >> Found form is not to a TESObjectLAND!");
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

		*result = 1;
	}
	return true;
}

bool Cmd_GetItemEffectString_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;

	ExtractArgsEx(EXTRACT_ARGS_EX, &pForm);

	if (!pForm) {
		if (!thisObj) 
			return true;
		pForm = thisObj->GetObjectReference();
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

	if (Script::GetConsoleOuput())
		Interface::PrintLine("GetItemEffectString >> %s", cEffects);

	return true;
}


bool Cmd_ApplyModelTextureSwap_Execute(COMMAND_ARGS) {
	*result = 0;
	TESBoundObject* pBaseForm = nullptr;
	TESObjectREFR* pReference = nullptr;
	char cObjectName[MAX_PATH] = {};
	BOOL bFirstPerson = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBaseForm, &cObjectName, &pReference, &bFirstPerson) && pBaseForm) {
		NiAVObject* pScene = GetReferenceScene(thisObj, bFirstPerson);
		if (cObjectName[0])
			pScene = BSUtilities::GetObjectByName(pScene, cObjectName);

		if (pScene) {
			if (!pReference)
				pReference = thisObj;

			TESModel* pModel = ModelLoader::GetSingleton()->GetModelForBoundObject(pBaseForm, pReference);
			if (pModel) {
				TESModelTextureSwap* pTexSwap = pModel->GetAsModelMaterialSwap();
				if (pTexSwap) {
					pTexSwap->SwapTextures(pScene);
					*result = 1;
				}
			}

			if (pBaseForm->GetHasSpecificTextures()) {
				CdeclCall(0x4B7660, pScene); // SwapPlatformLanguageTextures
				*result = 1;
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
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eType, &bToggle) && InRange(eType) && thisObj->IsActor()) {
		const Actor* pActor = static_cast<Actor*>(thisObj);
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
	*result = -1.0;
	const IKType eType = *reinterpret_cast<IKType*>(&arg1);
	if (InRange(eType) && thisObj->IsActor()) {
		const Actor* pActor = static_cast<Actor*>(thisObj);
		bhkRagdollController* pCtrl = pActor->pRagdollController;
		if (pCtrl) {
			switch (eType) {
				case IKType::LOOK:
					*result = pCtrl->GetLookIKEnable();
					break;
				case IKType::FOOT:
					*result = pCtrl->GetFootIKEnable();
					break;
				case IKType::GRAB:
					*result = pCtrl->GetGrabIKEnable();
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
	return Cmd_GetIKState_Eval(thisObj, reinterpret_cast<void*>(eType), nullptr, result);
}

SPEC_NOINLINE bool Cmd_IsCarryable_Eval(COMMAND_ARGS_EVAL) {
	TESForm* pForm = reinterpret_cast<TESForm*>(arg1);
	pForm = pForm ? pForm : thisObj;
	if (!pForm)
		pForm = CdeclCall<TESForm*>(0x6008F0); // TESIdleManager::GetUsedItem

	*result = TESContainer::ContainerCanHoldForm(pForm);
	return true;
}

bool Cmd_IsCarryable_Execute(COMMAND_ARGS) {
	TESForm* pForm = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &pForm);
	Cmd_IsCarryable_Eval(thisObj, pForm, nullptr, result);

	if (Script::GetConsoleOuput())
		Interface::PrintLine("IsCarryable >> %f", *result);

	return true;
}

bool Cmd_PickIdleEx_Execute(COMMAND_ARGS) {
	if (!thisObj->IsActor())
		return true;
	
	Actor* pUser = static_cast<Actor*>(thisObj);
	if (!pUser->GetCurrentAIProcess())
		return true;

	TESObjectREFR* pTargetRef = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTargetRef) && pTargetRef && pTargetRef->GetObjectReference()) {
		LowProcess* pAIProcess = static_cast<LowProcess*>(pUser->GetCurrentAIProcess());
		const TESObjectREFR* pOrgTarget = pAIProcess->pTarget;
		pAIProcess->pTarget = pTargetRef;
		*result = pAIProcess->FindSpecialIdletoPlay(pUser, pTargetRef->GetObjectReference(), pTargetRef);
		pAIProcess->pTarget = pOrgTarget;
	}

	return true;
}

SPEC_INLINE bool Cmd_GetUsedItemHeight_Eval(COMMAND_ARGS_EVAL) {
	*result = AnimActivationHeight::GetHeight();
	return true;
}

bool Cmd_GetUsedItemHeight_Execute(COMMAND_ARGS) {
	Cmd_GetUsedItemHeight_Eval(thisObj, nullptr, nullptr, result);
	return true;
}

bool Cmd_ClearAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm;
	int32_t iIndex = -2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &iIndex) && pForm) {
		TESModelTextureSwap* pModel = DYNAMIC_CAST(pForm, TESForm, TESModelTextureSwap);
		if (!pModel)
			return true;

		if (iIndex == -1) {
			pModel->ClearTexSwapList();
			*result = 1;
			return true;
		}
		else {
			pModel->RemoveTexSwap(iIndex);
			*result = 1;
			return true;
		}
	}
	return true;
}

bool Cmd_SetAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
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
			*result = 1;
		}
		else {
			pModel->AddTexSwap("", iIndex, pTextureSet);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetAltTextures_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
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
	g_arrInterface->AssignCommandResult(pArray, result);
	return true;
}

namespace {

	static bool __fastcall HasScopedWeapon(Character* apCharacter) {
		ItemChange* pItem = apCharacter->GetCurrentAIProcess()->GetCurrentWeapon();
		if (pItem) {
			TESObjectWEAP* pWeapon = static_cast<TESObjectWEAP*>(pItem->pObject);
			return pWeapon && pWeapon->GetHasScope() && (!pWeapon->GetHasModScope() || pItem->HasModEffectActive(WEAPON_MOD_EFFECT_TYPE::IRON_SITES));
		}
		return false;
	}

	static SPEC_NOINLINE void __fastcall ReloadWeaponScope(Character* apCharacter, BipedAnim* apBiped) {
		TESObjectWEAP* pWeapon = apBiped->kObjects[BIPED_OBJECT::WEAPON].pWeapon;
		if (pWeapon && HasScopedWeapon(apCharacter)) {
			const bool bScopeVisible = HUDMainMenu::GetSingleton()->bScopeVisible;
			Interface::InitGunScope(pWeapon->GetScopeModel());
			Interface::SetGunScopeVisible(bScopeVisible);
		}
	}

	static SPEC_NOINLINE BipedAnim* __fastcall CanReloadBipedModels(TESObjectREFR* apReference) {
		constexpr uint32_t uiDisallowedFlags = TESForm::FormFlags::STILL_LOADING | TESForm::FormFlags::DELETED | TESForm::FormFlags::DISABLED;
		if (apReference->uiFormFlags.Get(uiDisallowedFlags) || !apReference->IsCharacter())
			return nullptr;

		Character* pChar = static_cast<Character*>(apReference);
		const BaseProcess* pProcess = pChar->GetCurrentAIProcess();
		if (!pProcess || pProcess->GetProcessLevel() != PROCESS_TYPE::HIGH)
			return nullptr;

		if (!pChar->Get3DVerySimple())
			return nullptr;

		return pChar->GetBiped();
	}

	static void __fastcall ReloadBipedModels(Character* apCharacter, int32_t aiTargetObject) {
		if (aiTargetObject >= BIPED_OBJECT::COUNT)
			return;

		BipedAnim* pBiped = CanReloadBipedModels(apCharacter);
		if (!pBiped)
			return;

		Bitfield32 uiValidParts = 0xFFFFFFBF;
		if (aiTargetObject >= 0)
			uiValidParts = (1u << aiTargetObject) & 0xFFFFFFBF;

		const bool bReloadWeapon = uiValidParts.GetAndClearBit(BIPED_OBJECT::WEAPON);
		const bool bPlayer = apCharacter == PlayerCharacter::GetSingleton();
		bool bPlayerHasIS = false;

		BGSLoadGameSubBuffer kSavedAnim1st;
		BGSLoadGameSubBuffer kSavedAnim3rd;

		NiFixedString strIronSightNodeName;

		if (bPlayer) {
			PlayerCharacter* pPlayer = static_cast<PlayerCharacter*>(apCharacter);

			if (pPlayer->GetIronSights() && pPlayer->pIronSightNode)
				strIronSightNodeName = pPlayer->pIronSightNode->GetName();

			Animation* pAnim1st = pPlayer->GetAnimation(true);
			Animation* pAnim3rd = pPlayer->GetAnimation(false);

			SaveAnimation(kSavedAnim1st, apCharacter, pAnim1st);
			SaveAnimation(kSavedAnim3rd, apCharacter, pAnim3rd);
	
			BipedAnim* pBiped1st = pPlayer->GetBiped(true);
			BipedAnim* pBiped3rd = pPlayer->GetBiped(false);
			for (uint32_t i = 0; i < BIPED_OBJECT::COUNT; i++) {
				if (uiValidParts.GetBit(i)) {
					pBiped1st->RemovePart(BIPED_OBJECT(i), true);
					pBiped3rd->RemovePart(BIPED_OBJECT(i), true);
				}
			}

			if (bReloadWeapon) {
				pBiped1st->RemoveBipedWeapon();
				pBiped3rd->RemoveBipedWeapon();
			}
		}
		else {
			Animation* pAnim = apCharacter->GetAnimation();

			SaveAnimation(kSavedAnim3rd, apCharacter, pAnim);

			for (uint32_t i = 0; i < BIPED_OBJECT::COUNT; i++) {
				if (uiValidParts.GetBit(i)) {
					pBiped->RemovePart(BIPED_OBJECT(i), true);
				}
			}

			if (bReloadWeapon)
				pBiped->RemoveBipedWeapon();
		}

		apCharacter->ReplaceModel();

		if (bPlayer) {
			if (bReloadWeapon)
				ReloadWeaponScope(apCharacter, pBiped);

			PlayerCharacter* pPlayer = static_cast<PlayerCharacter*>(apCharacter);

			if (strIronSightNodeName)
				pPlayer->pIronSightNode = static_cast<NiNode*>(pPlayer->Get3D(true)->GetObjectByName(strIronSightNodeName));

			Animation* pAnim1st = pPlayer->GetAnimation(true);
			Animation* pAnim3rd = pPlayer->GetAnimation(false);

			if (!bReloadWeapon) {
				pAnim1st->ReloadTargets(true);
				pAnim3rd->ReloadTargets(false);
			}

			LoadAnimation(kSavedAnim1st, apCharacter, pAnim1st);
			LoadAnimation(kSavedAnim3rd, apCharacter, pAnim3rd);
		}
		else {
			Animation* pAnim = apCharacter->GetAnimation();

			if (!bReloadWeapon) {
				pAnim->ReloadTargets(false);
			}

			LoadAnimation(kSavedAnim3rd, apCharacter, pAnim);
		}

		BSShaderManager::GetShadowSceneNode(0)->AddObject(apCharacter->Get3D());
	}
}

static void __fastcall RequestBipedModelUpdate(Character* apCharacter, int32_t aiTargetObject, bool abQueue) {
	if (abQueue) {
		JohnnyExtraData* pExtraData = JohnnyExtraData::GetOrCreate(apCharacter);
		pExtraData->IncRefCount();

		QueuedTask kTask;
		kTask.kItems[0].p = pExtraData;
		kTask.kItems[1].i = aiTargetObject;
		kTask.pFunction = QUEUED_TASK{
			JohnnyExtraData* pData = reinterpret_cast<JohnnyExtraData*>(arTask.kItems[0].p);
			Character* pChar = static_cast<Character*>(pData->pOwner);
			if (pChar) {
				int32_t iTargetObject = arTask.kItems[1].i;
				ReloadBipedModels(pChar, iTargetObject);
			}
			pData->DecRefCount();
		};
		TaskQueue::QueueTask(kTask);
	}
	else {
		ReloadBipedModels(apCharacter, aiTargetObject);
	}
}

bool Cmd_ReloadEquippedModelsAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	if (!CanReloadBipedModels(thisObj))
		return true;

	int32_t iTargetObject = BIPED_OBJECT::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &iTargetObject) && iTargetObject < BIPED_OBJECT::COUNT) {
		const bool bPipBoyReload = iTargetObject == BIPED_OBJECT::PIPBOY && thisObj == PlayerCharacter::GetSingleton();
		if (bPipBoyReload) {
			FOPipboyManager* pPipBoy = Interface::GetPipboy();
			if (pPipBoy)
				pPipBoy->SetPipBoyManagerReset(true);
		}
		else {
			Character* pChar = static_cast<Character*>(thisObj);
			const bool bQueue = AILinearTaskThreadManager::ShouldQueue3DTask();
			RequestBipedModelUpdate(pChar, iTargetObject, bQueue);
			*result = bQueue ? 2 : 1;
		}
	}
	return true;
}

bool Cmd_GetExternalEmittanceSource_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm)) {
		if (!pForm)
			pForm = thisObj;

		if (!pForm)
			return true;

		TESForm* pSource = nullptr;
		if (pForm->IsReference()) {
			pSource = static_cast<TESObjectREFR*>(pForm)->GetEmittanceSource();
		}
		else if (pForm->IsBoundObject()) {
			pSource = ExternalEmittanceOnBases::GetExternalEmittanceSource(static_cast<TESBoundObject*>(pForm));
		}

		if (pSource)
			*reinterpret_cast<FormID*>(result) = pSource->GetFormID();
	}

	return true;
}

void __fastcall SetEmittanceSourceForRef(TESObjectREFR* apRef, TESForm* apSource) {
	if (!apRef)
		return;
	
	TESForm* pExistingSource = apRef->GetEmittanceSource();
	if (pExistingSource == apSource)
		return;

	TESObjectCELL* pCell = apRef->GetSaveParentCell();
	if (pCell) {
		pCell->CellRefLockEnter();

		if (pExistingSource)
			pCell->RemoveEmittanceRef(apRef);
	}

	apRef->SetEmittanceSource(apSource);

	if (pCell) {
		if (apSource)
			pCell->AddEmittanceRef(apRef);
		else
			pCell->RemoveEmittanceRef(apRef);

		pCell->CellRefLockLeave();
	}
}

bool Cmd_SetExternalEmittanceSource_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = nullptr;
	TESForm* pSource = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &pSource) && pForm) {
		if (pSource) {
			if (pSource->GetFormType() != FORM_TYPE::TESRegion && pSource->GetFormType() != FORM_TYPE::TESObjectLIGH)
				return true;
		}

		if (pForm->IsReference()) {
			TESObjectREFR* pReference = static_cast<TESObjectREFR*>(pForm);
			if (AILinearTaskThreadManager::GetRunningThreads()) {
				JohnnyExtraData* pExtraData = JohnnyExtraData::GetOrCreate(pReference);
				pExtraData->IncRefCount();

				QueuedTask kTask;
				kTask.kItems[0].p = pExtraData;
				kTask.kItems[1].p = pSource;
				kTask.pFunction = QUEUED_TASK{
					JohnnyExtraData* pData = reinterpret_cast<JohnnyExtraData*>(arTask.kItems[0].p);
					TESForm* pSource = reinterpret_cast<TESForm*>(arTask.kItems[1].p);
					TESObjectREFR* pRef = static_cast<TESObjectREFR*>(pData->pOwner);
					SetEmittanceSourceForRef(pRef, pSource);
					pData->DecRefCount();
				};
				TaskQueue::QueueTask(kTask);
			}
			else {
				SetEmittanceSourceForRef(pReference, pSource);
			}
		}
		else if (pForm->IsBoundObject()) {
			ExternalEmittanceOnBases::SetExternalEmittanceSource(static_cast<TESBoundObject*>(pForm), pSource);
		}
		else {
			return true;
		}

		*result = 1;
	}
	return true;
}

bool Cmd_GetProjectileMuzzleFlashLight_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSProjectile* pProjectile = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pProjectile) && pProjectile && IS_TYPE(pProjectile, BGSProjectile) && pProjectile->GetMuzzleFlashLight()) {
		*reinterpret_cast<FormID*>(result) = pProjectile->GetMuzzleFlashLight()->GetFormID();
	}
	return true;
}

bool Cmd_SetProjectileMuzzleFlashLight_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSProjectile* pProjectile = nullptr;
	TESObjectLIGH* pLight = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pProjectile, &pLight) && pProjectile && IS_TYPE(pProjectile, BGSProjectile)) {
		if (pLight && !IS_TYPE(pLight, TESObjectLIGH))
			return true;

		pProjectile->SetMuzzleFlashLight(pLight);
		*result = 1;
	}
	return true;
}

bool Cmd_GetReputationTitle_Execute(COMMAND_ARGS) {
	*result = 0;
	const char* pTitle = "";
	TESReputation* pReputation = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pReputation) && pReputation && IS_TYPE(pReputation, TESReputation)) {
		pTitle = pReputation->GetReputationTitle();

		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetReputationTitle >> \"%s\": \"%s\"", pReputation->GetFullName(), pTitle);
	}
	g_strInterface->Assign(PASS_COMMAND_ARGS, pTitle);
	return true;
}

bool Cmd_GetReputationIcon_Execute(COMMAND_ARGS) {
	*result = 0;
	const char* pIcon = "";
	TESReputation* pReputation = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pReputation) && pReputation && IS_TYPE(pReputation, TESReputation)) {
		pIcon = pReputation->GetReputationIcon();

		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetReputationIcon >> \"%s\": \"%s\"", pReputation->GetFullName(), pIcon);
	}
	g_strInterface->Assign(PASS_COMMAND_ARGS, pIcon);
	return true;
}

enum class ReputationIconType : int32_t {
	NONE	= -1,
	MAIN	= 0,
	MESSAGE = 1,
	COUNT
};

bool Cmd_GetReputationFormIcon_Execute(COMMAND_ARGS) {
	*result = 0;
	const char* pIcon = "";
	TESReputation* pReputation = nullptr;
	ReputationIconType eIconType = ReputationIconType::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pReputation, &eIconType) && pReputation && IS_TYPE(pReputation, TESReputation) && InRange(eIconType)) {
		if (eIconType == ReputationIconType::MAIN)
			pIcon = pReputation->GetReputationMainIcon();
		else if (eIconType == ReputationIconType::MESSAGE)
			pIcon = pReputation->GetMessageIconTextureName();
	
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetReputationFormIcon >> \"%s\": \"%s\"", pReputation->GetFullName(), pIcon);
	}
	g_strInterface->Assign(PASS_COMMAND_ARGS, pIcon);
	return true;
}

bool Cmd_SetReputationFormIcon_Execute(COMMAND_ARGS) {
	*result = 0;
	TESReputation* pReputation = nullptr;
	ReputationIconType eIconType = ReputationIconType::NONE;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pReputation, &eIconType, &cPath) && pReputation && IS_TYPE(pReputation, TESReputation) && InRange(eIconType)) {
		if (eIconType == ReputationIconType::MAIN)
			pReputation->SetReputationMainIcon(cPath);
		else if (eIconType == ReputationIconType::MESSAGE)
			pReputation->SetMessageIconTextureName(cPath);
		*result = 1;
	}
	return true;
}