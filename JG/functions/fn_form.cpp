#include "fn_form.h"
#include "GameSettings.h"
#include "Bethesda/TESObjectList.hpp"
#include "GameObjects.h"
#include "GameForms.h"
#include "Shared/BSMemory/BSScrapMemory.hpp"
#include <PluginAPI.h>
#include <GameExtraData.h>
#include "GameProcess.h"
#include <unordered_map>
#include "JG/JGSetList.hpp"
#include <JG/BarterFilter.hpp>
#include <JG/JohnnyExtraData.hpp>
#include <GameData.h>
#include <GameRTTI.h>
#include "decoding.h"
#include <events/LambdaVariableContext.h>
#include <numbers>
#include <Bethesda/AILinearTaskThreadManager.hpp>
#include <JG/TaskQueue.hpp>
#include <JG/LandRemapping.hpp>
#include <Bethesda/BSShaderManager.hpp>
#include <Bethesda/TESMain.hpp>

extern bool (*CallUDF)(class Script* funcScript, class TESObjectREFR* callingObj, uint8_t numArgs, ...);
extern InventoryRef* (*InventoryRefGetForID)(uint32_t refID);
extern GameTimeGlobals* g_gameTimeGlobals;

float(*GetWeaponDPS)(ActorValueOwner* avOwner, TESObjectWEAP* weapon, float condition, uint8_t arg4, ItemChange* entry, uint8_t arg6, uint8_t arg7, int arg8, float arg9, float arg10, uint8_t arg11, uint8_t arg12, TESForm* ammo) =
(float(*)(ActorValueOwner*, TESObjectWEAP*, float, uint8_t, ItemChange*, uint8_t, uint8_t, int, float, float, uint8_t, uint8_t, TESForm*))0x645380;


bool Cmd_RemoveNoteQuest_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	TESQuest* quest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &quest) && note && IS_TYPE(note, BGSNote) && IS_TYPE(quest, TESQuest)) {
		note->questList.Remove(quest);
		*result = 1;
	}
	return true;
}

bool Cmd_AddNoteQuest_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	TESQuest* quest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &quest) && note && IS_TYPE(note, BGSNote) && IS_TYPE(quest, TESQuest)) {
		note->questList.Append(quest);
		*result = 1;
	}
	return true;
}
bool Cmd_GetNoteQuestList_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	NVSEArrayVar* quests = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note) && note && IS_TYPE(note, BGSNote) && !note->questList.Empty()) {
		ListNode<TESQuest>* iter = note->questList.Head();
		do {
			if (iter->data) {
				g_arrInterface->AppendElement(quests, NVSEArrayElement(iter->data->GetFormID()));
			}
		} while (iter = iter->next);
	}
	g_arrInterface->AssignCommandResult(quests, result);
	return true;
}

bool Cmd_SetNoteImage_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	char path[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &path) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kImage) {
		note->picture->SetTextureName(path);
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteImage_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kImage) {
		g_strInterface->Assign(PASS_COMMAND_ARGS, note->picture->GetTextureName());
	}
	return true;
}
bool Cmd_SetNoteTopic_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	TESTopic* topic = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &topic) && note && IS_TYPE(note, BGSNote) && IS_TYPE(topic, TESTopic) && note->type == BGSNote::kVoice) {
		note->voice = topic;
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteTopic_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kVoice) {
		if (note->voice)
			*(uint32_t*)result = note->voice->GetFormID();
	}
	return true;
}

bool Cmd_SetNoteSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	TESSound* sound = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &sound) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kSound) {
		note->sound = sound;
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kSound) {
		if (note->sound)
			*(uint32_t*)result = note->sound->GetFormID();
	}
	return true;
}

bool Cmd_SetNoteType_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	int type = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &type) && note && IS_TYPE(note, BGSNote) && type >= 0 && type <= 3) {
		note->type = (BGSNote::Type)type;
		*result = 1;
	}
	return true;
}

bool Cmd_GetNoteType_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note) && note && IS_TYPE(note, BGSNote)) {
		*result = note->type;
	}
	return true;
}

bool Cmd_SetNoteSpeaker_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	TESNPC* npc = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &npc) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kVoice) {
		note->speaker = npc;
		*result = 1;
	}
	return true;
}
bool Cmd_GetNoteSpeaker_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSNote* note = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note) && note && IS_TYPE(note, BGSNote) && note->type == BGSNote::kVoice) {
		if (note->speaker)
			*(uint32_t*)result = note->speaker->GetFormID();
	}
	return true;
}

bool Cmd_GetCurrentFurnitureRef_Execute(COMMAND_ARGS) {
	if (!thisObj) { return true; }
	*result = 0;
	if (thisObj->IsActor()) {
		auto actorProcess = ((Actor*)thisObj)->baseProcess;
		if (actorProcess) {
			auto furniRef = actorProcess->GetCurrentFurnitureRef();
			if (furniRef) {
				*(uint32_t*)result = furniRef->GetFormID();
			}
		}

	}
	return true;
}

float(__fastcall* GetBaseScale)(TESObjectREFR*) = (float(__fastcall*)(TESObjectREFR*)) 0x00567400;
void* (__thiscall* TESNPC_GetFaceGenData)(TESNPC*) = (void* (__thiscall*)(TESNPC*)) 0x0601800;


bool Cmd_HideItemBarterEx_Execute(COMMAND_ARGS) {
	TESForm* itemFilter = nullptr, * filterArg = nullptr;
	uint32_t unhideOrHide = 0, flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &itemFilter, &unhideOrHide, &flags, &filterArg) && itemFilter) {
		DWORD idToHandle = 0;
		if (filterArg) {
			idToHandle = filterArg->GetFormID();
		}
		if (unhideOrHide) {
			BarterFilter::Add(itemFilter->GetFormID(), flags, idToHandle);
		}
		else {
			BarterFilter::Remove(itemFilter->GetFormID(), flags, idToHandle);
		}

	}
	return true;
}

bool Cmd_IsItemBarterHiddenEx_Execute(COMMAND_ARGS) {
	TESForm* itemFilter, * filterArg = nullptr;
	DWORD flags = 0;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &itemFilter, &filterArg) && itemFilter) {
		DWORD outflags = 0;
		DWORD idToHandle = 0;
		if (filterArg) {
			idToHandle = filterArg->GetFormID();
		}
		*result = BarterFilter::IsHidden(idToHandle);
	}
	return true;
}


bool Cmd_IsRadioRefPlaying_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj && thisObj->baseForm && IS_TYPE(thisObj->baseForm, TESObjectACTI)) {
		TESObjectACTI* baseActi = (TESObjectACTI*)thisObj->baseForm;
		if (baseActi->radioStation) {
			*result = (CdeclCall<void*>(0x0832930, thisObj) != nullptr);
		}
	}
	return true;
}

bool Cmd_TuneRadioRef_Execute(COMMAND_ARGS) {
	BGSTalkingActivator* actiDst = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &actiDst) && thisObj && thisObj->baseForm && IS_TYPE(thisObj->baseForm, TESObjectACTI)) {
		if (TESObjectACTI* actiBase = (TESObjectACTI*)thisObj->baseForm) {
			BGSTalkingActivator* originalTK = actiBase->radioStation;
			if (actiDst == nullptr) {
				actiDst = originalTK;
			}
			if (IS_TYPE(actiDst, BGSTalkingActivator)) {
				auto activateState = CdeclCall<unsigned int>(0x047B250, thisObj);
				if ((CdeclCall<void*>(0x0832930, thisObj) != nullptr) || (activateState == 1) || (activateState == 2)) { //the exact same logic the game uses
					CdeclCall<void*>(0x08325B0, thisObj, 0);
					actiBase->radioStation = actiDst;
					CdeclCall<void*>(0x08325B0, thisObj, 1);
					actiBase->radioStation = originalTK;
				}
			}
		}
	}
	return true;
}

bool Cmd_GetFormRecipesAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form = nullptr;
	NVSEArrayVar* rcpArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form) && form) {
		auto pIter = TESDataHandler::GetSingleton()->kRecipes.GetHead();
		while (pIter && !pIter->IsEmpty()) {
			TESRecipe* pRecipe = pIter->GetItem();
			pIter = pIter->GetNext();
			if (pRecipe && !pRecipe->outputs.Empty()) {
				TESRecipe::ComponentList* outputs = &pRecipe->outputs;
				auto it2 = outputs->Head();
				do {
					if (it2->data && it2->data->item && (it2->data->item->GetFormID() == form->GetFormID())) {
						g_arrInterface->AppendElement(rcpArr, NVSEArrayElement(pRecipe));
						break;
					}
				} while (it2 = it2->next);
			}
		}
	}
	g_arrInterface->AssignCommandResult(rcpArr, result);
	return true;
}

bool Cmd_SetFactionFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* faction = nullptr;
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &faction, &flags) && faction && IS_TYPE(faction, TESFaction)) {
		faction->factionFlags = flags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetFactionFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* faction = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &faction) && faction && IS_TYPE(faction, TESFaction)) {
		*result = faction->factionFlags;
		if (IsConsoleMode()) Console_Print("GetFactionFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_RemoveScopeModelPath_Execute(COMMAND_ARGS) {
	TESObjectWEAP* weapon = nullptr;
	TESModel* model = nullptr;
	*result = 0;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon) && weapon && IS_TYPE(weapon, TESObjectWEAP)) {
		if (weapon && weapon->HasScope()) model = &(weapon->kScope);
		if (model) {
			model->SetModel("");
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
bool Cmd_SetLightingTemplateTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
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
	*result = 0;
	uint32_t traitID = 0;
	BGSLightingTemplate* tmpl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &tmpl, &traitID) && tmpl && IS_TYPE(tmpl, BGSLightingTemplate) && traitID > 0) {
		switch (traitID) {
		case 1:
		case 2:
		case 3:
			*result = tmpl->ambientRGB[traitID - 1];
			break;
		case 4:
		case 5:
		case 6:
			*result = tmpl->directionalRGB[traitID - 4];
			break;
		case 7:
		case 8:
		case 9:
			*result = tmpl->fogRGB[traitID - 7];
			break;
		case 10:
			*result = tmpl->fogNear;
			break;
		case 11:
			*result = tmpl->fogFar;
			break;
		case 12:
			*result = tmpl->directionalXY;
			break;
		case 13:
			*result = tmpl->directionalZ;
			break;
		case 14:
			*result = tmpl->directionalFade;
			break;
		case 15:
			*result = tmpl->fogClipDist;
			break;
		case 16:
			*result = tmpl->fogPower;
			break;
		default:
			return true;
		}
		if (IsConsoleMode()) Console_Print("GetLightingTemplateTraitNumeric %d >> %f", traitID, *result);
	}
	return true;
}


BGSEncounterZone* GetEncounterZone(ExtraDataList* list) {
	ExtraEncounterZone* xZone = list->GetExtraData<ExtraEncounterZone>();
	if (xZone && xZone->pZone)
		return xZone->pZone;
	return nullptr;
}

void SetEncounterZone(ExtraDataList* list, BGSEncounterZone* zone) {
	ThisCall(0x421C60, list, zone);
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
			*(uint32_t*)result = zone->GetFormID();
	}
	return true;
}

bool Cmd_SetCellEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* zone = nullptr;
	TESObjectCELL* cell;
	ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &zone);
	if (!cell || !IS_TYPE(cell, TESObjectCELL))
		return true;
	if (!zone || IS_TYPE(zone, BGSEncounterZone)) {
		SetEncounterZone(&cell->extraDataList, zone);
		*result = 1;
	}
	return true;
}

bool Cmd_SetRefEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* zone = nullptr;
	ExtractArgsEx(EXTRACT_ARGS_EX, &zone);
	if (!zone || IS_TYPE(zone, BGSEncounterZone)) {
		SetEncounterZone(&thisObj->extraDataList, zone);
		*result = 1;
	}
	return true;
}

bool Cmd_GetRefEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* zone = GetEncounterZone(&thisObj->extraDataList);
	if (zone)
		*(uint32_t*)result = zone->GetFormID();
	return true;
}

bool Cmd_SetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	char newPrompt[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &newPrompt)) {
		ExtraActivateRef* xActivateRef = thisObj->extraDataList.GetExtraData<ExtraActivateRef>();
		if (xActivateRef) {
			xActivateRef->strActivationPrompt.Set(newPrompt);
		}
		else {
			xActivateRef = BSMemory::malloc<ExtraActivateRef>();
			ThisCall(0x4338B0, xActivateRef);
			xActivateRef->strActivationPrompt.Set(newPrompt);
			thisObj->extraDataList.AddExtra(xActivateRef);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	ExtraActivateRef* xActivateRef = thisObj->extraDataList.GetExtraData<ExtraActivateRef>();
	if (xActivateRef) {
		g_strInterface->Assign(PASS_COMMAND_ARGS, xActivateRef->strActivationPrompt.c_str());
		if (IsConsoleMode()) Console_Print("GetRefActivationPromptOverride >> %s", xActivateRef->strActivationPrompt.c_str());
	}
	return true;
}

bool Cmd_GetWeaponAltTextures_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon;
	NVSEArrayVar* txstArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon) && weapon && IS_TYPE(weapon, TESObjectWEAP)) {
		TESModelTextureSwap* model = &weapon->textureSwap;
		if (!model) return true;
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();

		do {
			if (iter->data && iter->data->textureID) g_arrInterface->AppendElement(txstArr, NVSEArrayElement(iter->data->textureID));
		} while (iter = iter->next);
	}
	g_arrInterface->AssignCommandResult(txstArr, result);
	return true;
}

bool Cmd_GetIdleMarkerAnimations_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker;
	NVSEArrayVar* idleArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker) && marker && IS_TYPE(marker, BGSIdleMarker) && marker->idleCollection.animCount > 0) {
		for (int i = 0; i < marker->idleCollection.animCount; i++) {
			g_arrInterface->AppendElement(idleArr, NVSEArrayElement(marker->idleCollection.idleList[i]));
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
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &animId, &newAnim) && marker && IS_TYPE(marker, BGSIdleMarker) && marker->idleCollection.animCount > animId) {
		marker->idleCollection.idleList[animId] = newAnim;
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
		if (marker->idleCollection.idleList) BSMemory::free(marker->idleCollection.idleList);
		marker->idleCollection.idleList = idleList;
		marker->idleCollection.animCount = size;
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
			*result = marker->idleCollection.flags;
			break;
		case 2:
			*result = marker->idleCollection.idleTimer;
			break;
		case 3:
			*result = marker->idleCollection.animCount;
			break;
		default:
			return true;
		}
		if (IsConsoleMode()) Console_Print("GetIdleMarkerTraitNumeric %d >> %.2f", traitID, *result);
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
			marker->idleCollection.flags = newVal;
			break;
		case 2:
			marker->idleCollection.idleTimer = newVal;
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
		return &armor->bipedModel.bipedModel[0]; // male biped
	case 2:
		return &armor->bipedModel.bipedModel[1]; // female biped
	case 3:
		return &armor->bipedModel.groundModel[0]; // male world
	case 4:
		return &armor->bipedModel.groundModel[1]; //female world
	default:
		return nullptr;
	}
}

bool Cmd_GetAltTexturesEx_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form = nullptr;
	uint32_t whichModel;
	NVSEArrayVar* txstArr = g_arrInterface->CreateMap(nullptr, nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form, &whichModel) && form && (IS_TYPE(form, TESObjectARMO) || IS_TYPE(form, TESObjectWEAP))) {
		TESModelTextureSwap* model;
		if (IS_TYPE(form, TESObjectARMO)) {
			TESObjectARMO* armor = DYNAMIC_CAST(form, TESForm, TESObjectARMO);
			model = GetArmorModel(armor, whichModel);
		}
		else {
			TESObjectWEAP* weapon = DYNAMIC_CAST(form, TESForm, TESObjectWEAP);
			model = &weapon->textureSwap;
		}
		if (!model) return true;
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();

		do {
			if (iter->data && iter->data->textureID) g_arrInterface->SetElement(txstArr, NVSEArrayElement(iter->data->index3D), NVSEArrayElement(iter->data->textureID));
		} while (iter = iter->next);

	}
	g_arrInterface->AssignCommandResult(txstArr, result);
	return true;
}

bool Cmd_GetArmorAltTextures_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectARMO* armor = nullptr;
	uint32_t whichModel;
	NVSEArrayVar* txstArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &whichModel) && armor && IS_TYPE(armor, TESObjectARMO)) {
		TESModelTextureSwap* model = GetArmorModel(armor, whichModel);
		if (!model) return true;
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();

		do {
			if (iter->data && iter->data->textureID) g_arrInterface->AppendElement(txstArr, NVSEArrayElement(iter->data->textureID));
		} while (iter = iter->next);

	}
	g_arrInterface->AssignCommandResult(txstArr, result);
	return true;
}
bool Cmd_SetWeaponAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon = nullptr;
	BGSTextureSet* txst = nullptr;
	int id = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon, &id, &txst) && weapon && IS_TYPE(weapon, TESObjectWEAP) && txst && IS_TYPE(txst, BGSTextureSet)) {
		TESModelTextureSwap* model = &weapon->textureSwap;
		if (!model) return true;

		TESModelTextureSwap::Texture* texture = nullptr;
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();

		do {
			if (iter->data && iter->data->index3D == id) {
				texture = iter->data;
				break;
			}
		} while (iter = iter->next);

		if (texture) {

			texture->textureID = txst;
			*result = 1;

		}
		else {
			TESModelTextureSwap::Texture* texture = BSMemory::malloc<TESModelTextureSwap::Texture>();
			if (texture != nullptr) {
				texture->index3D = id;
				texture->textureID = txst;
				*(texture->textureName) = '\0';
				model->textureList.Append(texture);
				*result = 1;

			}
		}
	}
	return true;
}
bool Cmd_SetArmorAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTextureSet* txst = nullptr;
	TESObjectARMO* armor = nullptr;
	int id = -1;
	uint32_t whichModel;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &whichModel, &id, &txst) && txst && IS_TYPE(txst, BGSTextureSet) && armor && IS_TYPE(armor, TESObjectARMO)) {
		TESModelTextureSwap* model = GetArmorModel(armor, whichModel);
		if (!model) return true;

		TESModelTextureSwap::Texture* texture = nullptr;
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();

		do {
			if (iter->data && iter->data->index3D == id) {
				texture = iter->data;
				break;
			}
		} while (iter = iter->next);

		if (texture) {

			texture->textureID = txst;
			*result = 1;

		}
		else {
			TESModelTextureSwap::Texture* texture = BSMemory::malloc<TESModelTextureSwap::Texture>();
			if (texture != nullptr) {
				texture->index3D = id;
				texture->textureID = txst;
				*(texture->textureName) = '\0';
				model->textureList.Append(texture);
				*result = 1;

			}
		}

	}
	return true;
}

bool Cmd_ClearWeaponAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon;
	int id = -2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon, &id) && weapon && IS_TYPE(weapon, TESObjectWEAP)) {
		TESModelTextureSwap* model = &weapon->textureSwap;
		if (!model) return true;

		if (id == -1) {
			model->textureList.RemoveAll();
			*result = 1;
			return true;
		}

		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();
		do {
			if (iter->data && iter->data->index3D == id) {
				model->textureList.Remove(iter->data);
				*result = 1;
				break;
			}
		} while (iter = iter->next);
	}
	return true;
}

bool Cmd_ClearArmorAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectARMO* armor = nullptr;
	int id = -2;
	uint32_t whichModel;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &whichModel, &id) && armor && IS_TYPE(armor, TESObjectARMO)) {
		TESModelTextureSwap* model = GetArmorModel(armor, whichModel);
		if (!model) return true;
		if (id == -1) {
			model->textureList.RemoveAll();
			*result = 1;
			return true;
		}
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();
		do {
			if (iter->data && iter->data->index3D == id) {
				model->textureList.Remove(iter->data);
				*result = 1;
				break;
			}
		} while (iter = iter->next);
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
			pShader->fillTexture.SetTextureName(cPath);
			break;
		case 1:
			pShader->particleShaderTexture.SetTextureName(cPath);
			break;
		case 2:
			pShader->holesTexture.SetTextureName(cPath);
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
			pPath = pShader->fillTexture.GetTextureName();
			break;
		case 1:
			pPath = pShader->particleShaderTexture.GetTextureName();
			break;
		case 2:
			pPath = pShader->holesTexture.GetTextureName();
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
	TESEffectShader* shader;
	uint32_t traitID;
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shader, &traitID, &value) && shader && IS_TYPE(shader, TESEffectShader) && traitID >= 0 && traitID <= 76) {
		switch (traitID) {
		case 0:
			shader->shaderData.flags = (uint8_t)value;
			break;
		case 61:
		{
			TESForm* pFoundForm = TESForm::GetFormByNumericID(value);
			if (pFoundForm && IS_TYPE(pFoundForm, BGSDebris))
				shader->shaderData.addonModels = static_cast<BGSDebris*>(pFoundForm);
		}
		break;
		case 4:
		case 14:
		case 47:
		case 48:
		case 49:
			((uint32_t*)shader)[6 + traitID] = SwapRGB((uint32_t)value);
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
			((uint32_t*)shader)[6 + traitID] = (uint32_t)value;
			break;
		default:
			((float*)shader)[6 + traitID] = value;
			break;
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetEffectShaderTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESEffectShader* shader;
	uint32_t traitID;
	uint32_t color;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shader, &traitID) && shader && IS_TYPE(shader, TESEffectShader) && traitID >= 0 && traitID <= 76) {
		switch (traitID) {
		case 0:
			*result = shader->shaderData.flags;
			break;
		case 61:
			*result = shader->shaderData.addonModels->GetFormID();
			break;
		case 4:
		case 14:
		case 47:
		case 48:
		case 49:
			color = SwapRGB(((uint32_t*)shader)[6 + traitID]);
			*result = color;
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
			*result = ((uint32_t*)shader)[6 + traitID];
			break;
		default:
			*result = ((float*)shader)[6 + traitID];
			break;
		}
		if (IsConsoleMode()) Console_Print("GetEffectShaderTraitNumeric %d >> %.2f", traitID, *result);
	}
	return true;
}

bool IsApplicable(BGSPerk* perk) {
	for (uint32_t i = 0; i < perk->conditions.Count(); i++) {
		Condition* condition = perk->conditions.GetNthItem(i);
		bool result = false;
		if (condition->opcode == 0x46 && !condition->Evaluate(PlayerCharacter::GetSingleton(), 0, &result)) return false;
	}
	return true;
}

bool Cmd_GetAvailablePerks_Execute(COMMAND_ARGS) {
	*result = 0;
	NVSEArrayVar* perkArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	auto pIter = TESDataHandler::GetSingleton()->kPerks.GetHead();
	BGSPerk* perk;
	int perkRank;
	while (pIter && !pIter->IsEmpty()) {
		perk = pIter->GetItem();
		pIter = pIter->GetNext();
		if (perk->data.isPlayable && perk->data.minLevel > 0 && perk->data.minLevel <= PlayerCharacter::GetSingleton()->avOwner.GetLevel()) {
			perkRank = PlayerCharacter::GetSingleton()->GetPerkRank(perk, 0);
			bool result = false;
			if (perkRank < perk->data.numRanks && !perk->data.isTrait && IsApplicable(perk)
				&& perk->conditions.Evaluate(PlayerCharacter::GetSingleton(), 0, &result, 0)) {
				g_arrInterface->AppendElement(perkArr, NVSEArrayElement(perk));
			}
		}
	}
	g_arrInterface->AssignCommandResult(perkArr, result);
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
			if (IsConsoleMode())
				Console_Print("GetFaceGenNthProperty %.2f", *result);
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
			if (IsConsoleMode()) {
				Console_Print("SetFaceGenNthProperty called");
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
		int karmaTier = CdeclCall<int>(0x47E040, PlayerCharacter::GetSingleton()->avOwner.GetActorValueF(kAVCode_Karma)); // GetKarmaTier
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
	if (IsConsoleMode()) Console_Print("GetPlayerKarmaTitle >> %s", title);
	g_strInterface->Assign(PASS_COMMAND_ARGS, title);
	return true;
}

bool Cmd_GetTalkingActivatorActor_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTalkingActivator* activator = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &activator) && activator && IS_TYPE(activator, BGSTalkingActivator)) {
		if (activator->talkingActor) {
			*(uint32_t*)result = activator->talkingActor->GetFormID();
		}
		if (IsConsoleMode()) Console_Print("GetTalkingActivatorActor >> 0x%X", *result);
	}
	return true;
}

bool Cmd_GetActorEffectType_Execute(COMMAND_ARGS) {
	*result = 0;
	SpellItem* effect = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect) && effect && IS_TYPE(effect, SpellItem)) {
		*result = effect->type;
		if (IsConsoleMode()) Console_Print("GetActorEffectType >> %.2f", *result);
	}
	else {
		*result = -1;
	}
	return true;
}

bool Cmd_GetBodyPartTraitString_Execute(COMMAND_ARGS) {
	const char* resStr = nullptr;
	BGSBodyPartData* bpData = nullptr;
	uint32_t partID;
	uint32_t traitID;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bpData, &partID, &traitID) && bpData) {
		if (IS_ID(bpData, BGSBodyPartData) && (partID <= 14) && (traitID <= 5)) {
			if (const BGSBodyPart* bodyPart = bpData->bodyParts[partID]) {
				switch (traitID) {
				case 1:
					if (bodyPart->partNode.GetLength()) resStr = bodyPart->partNode.c_str();
					break;
				case 2:
					if (bodyPart->VATSTarget.GetLength()) resStr = bodyPart->VATSTarget.c_str();
					break;
				case 3:
					if (bodyPart->startNode.GetLength()) resStr = bodyPart->startNode.c_str();
					break;
				case 4:
					if (bodyPart->partName.GetLength()) resStr = bodyPart->partName.c_str();
					break;
				case 5:
					if (bodyPart->targetBone.GetLength()) resStr = bodyPart->targetBone.c_str();
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
	uint32_t isFemale = 0;
	TESForm* form = nullptr;
	const char* path = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form, &isFemale) && form) {
		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel) {
			path = bipedModel->messageIcon[isFemale].icon.GetTextureName();
		}
		else {
			BGSMessageIcon* icon = DYNAMIC_CAST(form, TESForm, BGSMessageIcon);
			if (icon) {
				path = icon->icon.GetTextureName();
			}
		}
		if (IsConsoleMode()) Console_Print("GetMessageIconPath >> %s", path);
		g_strInterface->Assign(PASS_COMMAND_ARGS, path);
	}
	return true;
}
bool Cmd_SetMessageIconPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char path[MAX_PATH] = {};
	uint32_t isFemale = 0;
	TESForm* form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &form, &isFemale) && form) {
		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel) {
			bipedModel->messageIcon[isFemale].icon.SetTextureName(path);
			*result = 1;
		}
		else {
			BGSMessageIcon* icon = DYNAMIC_CAST(form, TESForm, BGSMessageIcon);
			if (icon) {
				icon->icon.SetTextureName(path);
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_SetNoteRead_Execute(COMMAND_ARGS) {
	uint32_t isRead = 0;
	*result = 0;
	BGSNote* note = nullptr;
	uint32_t serialize = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &isRead, &serialize) && note) {
		if (serialize)
		{
			ThisCall(0x5E9300, note, isRead > 0);
		}
		else {
			note->read = isRead > 0;
		}
		*result = 1;
	}
	return true;
}
bool Cmd_GetQuestDelay_Execute(COMMAND_ARGS) {
	*result = 0;
	TESQuest* quest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest) && quest && IS_TYPE(quest, TESQuest)) {
		*result = quest->questDelayTime;
		if (IsConsoleMode()) Console_Print("GetQuestDelay >> %.3f", *result);
	}
	return true;
}

bool Cmd_GetWeaponVATSTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weap = nullptr;
	uint32_t traitID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &traitID) && weap && IS_TYPE(weap, TESObjectWEAP)) {
		switch (traitID) {
		case 1:
			*result = weap->vatsSkill;
			break;
		case 2:
			*result = weap->vatsDamMult;
			break;
		case 3:
			*result = weap->vatsAP;
			break;
		case 4:
			*result = weap->isSilent;
			break;
		case 5:
			*result = weap->modRequired;
			break;
		}
		if (IsConsoleMode()) Console_Print("GetWeaponVATSTraitNumeric %d >> %f", traitID, *result);
	}
	return true;
}

bool Cmd_SetWeaponVATSTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weap = nullptr;
	uint32_t traitID = 0;
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &traitID, &value) && weap && IS_TYPE(weap, TESObjectWEAP)) {
		*result = 1;
		switch (traitID) {
		case 1:
			weap->vatsSkill = value;
			break;
		case 2:
			weap->vatsDamMult = value;
			break;
		case 3:
			weap->vatsAP = value;
			break;
		case 4:
			weap->isSilent = (value > 0 ? 1 : 0);
			break;
		case 5:
			weap->modRequired = (value > 0 ? 1 : 0);
			break;
		default:
			*result = 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetQuestFailed_Execute(COMMAND_ARGS) {
	*result = 0;
	TESQuest* quest = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest) && quest)
		*result = (quest->flags & 0x40) ? 1 : 0;
	if (IsConsoleMode()) Console_Print("GetQuestFailed >> %.2f", *result);
	return true;
}

bool Cmd_GetQuestFailed_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	TESQuest* quest = (TESQuest*)arg1;
	if (quest)
		*result = (quest->flags & 0x40) ? 1 : 0;
	return true;
}

bool Cmd_GetWeaponWorldModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon = nullptr;
	const char* modelPath = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon) && weapon && IS_TYPE(weapon, TESObjectWEAP)) {
		modelPath = weapon->kWorldModel.GetModel();
		g_strInterface->Assign(PASS_COMMAND_ARGS, modelPath);
		if (IsConsoleMode()) Console_Print("GetWeaponWorldModelPath >> %s", modelPath);
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
	BGSProjectile* projectile = nullptr;
	TESSound* sound = nullptr;
	int soundID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &projectile, &soundID, &sound) && projectile && IS_TYPE(projectile, BGSProjectile) && sound && IS_TYPE(sound, TESSound) && soundID <= 3) {
		*result = 1;
		switch (soundID) {
		case 1:
			projectile->soundProjectile = sound;
			break;
		case 2:
			projectile->soundCountDown = sound;
			break;
		case 3:
			projectile->soundDisable = sound;
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
	BGSExplosion* explosion = nullptr;
	TESSound* sound = nullptr;
	int soundID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &explosion, &soundID, &sound) && explosion && IS_TYPE(explosion, BGSExplosion) && sound && IS_TYPE(sound, TESSound) && soundID <= 2) {
		soundID == 1 ? (explosion->sound1 = sound) : (explosion->sound2 = sound);
		*result = 1;
	}
	return true;
}

bool Cmd_GetCreatureCombatSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCreature* creature = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &creature)) return true;
	if (!creature) {
		if (!thisObj || !thisObj->IsActor()) return true;
		creature = (TESCreature*)((Actor*)thisObj)->GetActorBase();
	}
	if IS_TYPE(creature, TESCreature)
		* result = creature->combatSkill;
	return true;
}

bool Cmd_SetContainerSound_Execute(COMMAND_ARGS) {
	int whichSound = -1;
	TESObjectCONT* container = nullptr;
	TESSound* newSound = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &container, &whichSound, &newSound) && container && IS_TYPE(container, TESObjectCONT) && newSound && IS_TYPE(newSound, TESSound)) {
		*result = 1;
		switch (whichSound) {
		case 0:
			container->openSound = newSound;
			break;
		case 1:
			container->closeSound = newSound;
			break;
		case 2:
			container->randomLoopingSound = newSound;
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
	int whichSound = -1;
	TESObjectCONT* container = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &container, &whichSound) && container && IS_TYPE(container, TESObjectCONT)) {
		switch (whichSound) {
		case 0:
			if (container->openSound) *(uint32_t*)result = container->openSound->GetFormID();
			break;
		case 1:
			if (container->closeSound) *(uint32_t*)result = container->closeSound->GetFormID();
			break;
		case 2:
			if (container->randomLoopingSound) *(uint32_t*)result = container->randomLoopingSound->GetFormID();
			break;
		}
	}
	return true;
}

bool Cmd_GetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* race = nullptr;
	UINT32 bit;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &bit) && race && IS_TYPE(race, TESRace)) {
		*result = (race->raceFlags & 1 << bit);
		if (IsConsoleMode()) Console_Print("GetRaceFlag >> %.f", *result);
	}
	return true;
}

bool Cmd_SetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* race = nullptr;
	UINT32 bit;
	UINT32 setorclear;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &bit, &setorclear) && race && IS_TYPE(race, TESRace)) {
		setorclear ? race->raceFlags |= (1 << bit) : race->raceFlags &= ~(1 << bit);
		*result = 1;
	}
	return true;
}

// 0 - alive, 1 - dying/ragdolled, 2 - dead, 3 - unconscious, 5 - restrained, 6 - essential unconscious
bool Cmd_GetLifeState_Execute(COMMAND_ARGS) {
	Actor* actor = (Actor*)thisObj;
	*result = -1;
	if (actor && actor->IsActor()) {
		*result = actor->lifeState;
		if (IsConsoleMode()) Console_Print("GetLifeState >> %.f", *result);
	}
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
			if (pActorBase->baseData.factionList.IsEmpty())
				return;

			auto pIter = pActorBase->baseData.factionList.GetHead();
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
	uint32_t newEquipType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &newEquipType) && pForm && newEquipType <= 13) {
		pForm = GetTESForm(pForm);
		BGSEquipType* pEquipType = DYNAMIC_CAST(pForm, TESForm, BGSEquipType);
		if (pEquipType) {
			pEquipType->equipType = newEquipType;
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetRaceHeadModelPath_Execute(COMMAND_ARGS) {
	TESRace* race = nullptr;
	uint32_t modelID, isFemale;
	const char* path = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &modelID, &isFemale) && race && IS_TYPE(race, TESRace)) {
		if (isFemale <= 1 && modelID <= 7) {
			path = race->faceModels[isFemale][modelID].GetModel();
			if (path) {
				g_strInterface->Assign(PASS_COMMAND_ARGS, path);
				if (IsConsoleMode()) {
					Console_Print("GetRaceHeadModelPath %i %i >> %s", modelID, isFemale, path);
				}
			}
		}
	}
	return true;
}

bool Cmd_GetRaceBodyModelPath_Execute(COMMAND_ARGS) {
	TESRace* race = nullptr;
	uint32_t modelID, isFemale;
	const char* path = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &modelID, &isFemale) && race && IS_TYPE(race, TESRace)) {
		if (isFemale <= 1 && modelID <= 2) {
			path = race->bodyModels[isFemale][modelID].GetModel();
			if (path) {
				g_strInterface->Assign(PASS_COMMAND_ARGS, path);
				if (IsConsoleMode()) {
					Console_Print("GetRaceModelPath %i %i >> %s", modelID, isFemale, path);
				}
			}
		}
	}
	return true;
}

bool Cmd_GetFacegenModelFlag_Execute(COMMAND_ARGS) {
	TESObjectARMO* armor = nullptr;
	uint32_t isFemale, flagID;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &flagID, &isFemale) && armor && IS_TYPE(armor, TESObjectARMO)) {
		if (isFemale <= 1 && flagID <= 3) {
			*result = armor->bipedModel.bipedModel[isFemale].ucFaceGenFlags.GetBit(flagID) ? 1 : 0;
			if (IsConsoleMode()) {
				Console_Print("GetFacegenModelFlag %i %i >> %.f", flagID, isFemale, *result);
			}
		}
	}
	return true;
}

bool Cmd_SetFacegenModelFlag_Execute(COMMAND_ARGS) {
	TESObjectARMO* armor = nullptr;
	uint32_t isFemale;
	uint32_t flagID;
	BOOL bEnable;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &flagID, &isFemale, &bEnable) && armor && IS_TYPE(armor, TESObjectARMO) && flagID <= 3) {
		armor->SetFacegenFlag(1 << flagID, isFemale, bEnable);
		*result = 1;
	}
	return true;
}

bool Cmd_GetBaseScale_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	TESActorBase* pBase = reinterpret_cast<TESActorBase*>(arg1);
	if (pBase) {
		FORM_TYPE eType = pBase->GetFormType();
		if (eType == FORM_TYPE::TESNPC)
			*result = static_cast<TESNPC*>(pBase)->height;
		else if (eType == FORM_TYPE::TESCreature)
			*result = static_cast<TESCreature*>(pBase)->baseScale;
	}
	else if (thisObj) {
		*result = GetBaseScale(thisObj);
	}
	return true;
}

bool Cmd_GetBaseScale_Execute(COMMAND_ARGS) {
	TESActorBase* pBase = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBase)) {
		Cmd_GetBaseScale_Eval(thisObj, pBase, 0, result);
		if (IsConsoleMode())
			Console_Print("GetBaseScale : %0.2f", *result);
	}
	return true;
}

bool Cmd_RemovePrimitive_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj->extraDataList.HasExtra<ExtraPrimitive>()) {
		ExtraPrimitive* pPrimitive = thisObj->extraDataList.GetExtraData<ExtraPrimitive>();
		thisObj->extraDataList.RemoveExtra(pPrimitive, true);
		thisObj->Update3D();
		*result = 1;
	}
	return true;
}
bool Cmd_GetPrimitiveType_Execute(COMMAND_ARGS) {
	ExtraPrimitive* pPrimitive = thisObj->extraDataList.GetExtraData<ExtraPrimitive>();
	*result = (pPrimitive && pPrimitive->pPrimitive) ? pPrimitive->pPrimitive->type : 0;
	return true;
}

bool Cmd_GetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype = nullptr;
	const char* path = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mtype) && mtype && IS_TYPE(mtype, BGSMusicType)) {
		path = mtype->soundFile.path.c_str();
		g_strInterface->Assign(PASS_COMMAND_ARGS, path);
		if (IsConsoleMode()) {
			Console_Print("GetMusicTypePath >> %s", path);
		}
	}
	return true;
}

bool Cmd_GetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mtype) && mtype && IS_TYPE(mtype, BGSMusicType)) {
		*result = mtype->dB;
		if (IsConsoleMode())
			Console_Print("GetMusicTypeDB >> %f", *result);
	}
	return true;
}

bool Cmd_SetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype = nullptr;
	float newVal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mtype, &newVal) && mtype && IS_TYPE(mtype, BGSMusicType)) {
		mtype->dB = newVal;
		*result = 1;
	}
	return true;
}

bool Cmd_SetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype = nullptr;
	char newPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mtype, &newPath) && mtype && IS_TYPE(mtype, BGSMusicType)) {
		mtype->soundFile.path.Set(newPath);
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
	TESObjectWEAP* weap = nullptr;
	int id = -1;
	TESObjectSTAT* model = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &id, &model) && weap && IS_TYPE(weap, TESObjectWEAP) && (!model || IS_TYPE(model, TESObjectSTAT)) && id <= 7) {
		*result = 1;
		switch (id) {
		case 0:
			weap->worldStatic = model;
			break;
		case 1:
			weap->modStatics[0] = model;
			break;
		case 2:
			weap->modStatics[1] = model;
			break;
		case 3:
			weap->modStatics[3] = model;
			break;
		case 4:
			weap->modStatics[2] = model;
			break;
		case 5:
			weap->modStatics[5] = model;
			break;
		case 6:
			weap->modStatics[4] = model;
			break;
		case 7:
			weap->modStatics[6] = model;
			break;
		default:
			*result = 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetWeapon1stPersonModel_Execute(COMMAND_ARGS) {
	TESObjectWEAP* weap = nullptr;
	int id = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &id) && weap && IS_TYPE(weap, TESObjectWEAP) && id <= 7) {
		switch (id) {
		case 0:
			*(uint32_t*)result = weap->worldStatic != nullptr ? weap->worldStatic->GetFormID() : 0;
			break;
		case 1:
			*(uint32_t*)result = weap->modStatics[0] != nullptr ? weap->modStatics[0]->GetFormID() : 0;
			break;
		case 2:
			*(uint32_t*)result = weap->modStatics[1] != nullptr ? weap->modStatics[1]->GetFormID() : 0;
			break;
		case 3:
			*(uint32_t*)result = weap->modStatics[3] != nullptr ? weap->modStatics[3]->GetFormID() : 0;
			break;
		case 4:
			*(uint32_t*)result = weap->modStatics[2] != nullptr ? weap->modStatics[2]->GetFormID() : 0;
			break;
		case 5:
			*(uint32_t*)result = weap->modStatics[5] != nullptr ? weap->modStatics[5]->GetFormID() : 0;
			break;
		case 6:
			*(uint32_t*)result = weap->modStatics[4] != nullptr ? weap->modStatics[4]->GetFormID() : 0;
			break;
		case 7:
			*(uint32_t*)result = weap->modStatics[6] != nullptr ? weap->modStatics[6]->GetFormID() : 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &imod) && imod && IS_TYPE(imod, TESImageSpaceModifier)) {
		*result = imod->animable;
		if (IsConsoleMode())
			Console_Print("GetIMODAnimatable >> %.f", *result);
	}
	return true;
}

bool Cmd_SetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod = nullptr;
	int newVal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &imod, &newVal) && imod && IS_TYPE(imod, TESImageSpaceModifier) && (newVal == 0 || newVal == 1)) {
		imod->animable = newVal;
		*result = 1;
		if (IsConsoleMode())
			Console_Print("SetIMODAnimatable >> %d", imod->animable);
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
			TESForm* base = thisObj->baseForm;
			if (IS_ID(base, TESObjectWEAP))
				weapon = (TESObjectWEAP*)base;
			else
				return true;

			condition = thisObj->GetHealth();
		}
		else {
			weapon = (TESObjectWEAP*)invRef->data.type;
			if NOT_ID(weapon, TESObjectWEAP) return true;
			if (invRef->data.xData) {
				condition = invRef->data.entry->GetItemHealth(true) / 100.0F;
				extendPtr = invRef->data.xData;
			}
		}
	}
	else if NOT_ID(weapon, TESObjectWEAP) return true;
	MiddleHighProcess* midHiProc = (MiddleHighProcess*)PlayerCharacter::GetSingleton()->baseProcess;
	ItemChange* weaponInfo = midHiProc->weaponInfo;
	TESForm* ammo = nullptr;
	if (!extendPtr && weaponInfo && (weaponInfo->pObject == weapon) && midHiProc->ammoInfo)
		ammo = midHiProc->ammoInfo->pObject;
	if (!ammo)
		ammo = weapon->GetAmmo();
	midHiProc->weaponInfo = nullptr;
	*result = GetWeaponDPS(&(PlayerCharacter::GetSingleton()->avOwner), weapon, condition, 1, weaponInfo, 0, 0, -1, 0.0, 0.0, 0, 0, ammo);
	midHiProc->weaponInfo = weaponInfo;
	if (IsConsoleMode())
		Console_Print("GetCalculatedWeaponDPS >> %f", *result);
	return true;
}

bool Cmd_IsCellVisited_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell) && cell && IS_TYPE(cell, TESObjectCELL)) {
		ExtraSeenData* seenData = cell->extraDataList.GetExtraData<ExtraSeenData>();
		if (seenData && seenData->pSeenData)
			*result = 1;
		if (IsConsoleMode())
			Console_Print("IsCellVisited >> %.0f", *result);
	}
	return true;
}

bool Cmd_IsCellExpired_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = nullptr;
	uint32_t iHoursToRespawnCell = *(uint32_t*)0x11CA164;
	int32_t detachTime = 0;
	float gameHoursPassed = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell) && cell && IS_TYPE(cell, TESObjectCELL)) {
		ExtraDetachTime* xDetachTime = cell->extraDataList.GetExtraData<ExtraDetachTime>();
		detachTime = xDetachTime == 0 ? 0 : xDetachTime->uiTime;
		if (detachTime == 0) {
			*result = -1;
		}
		else if (detachTime == -1 || detachTime == -2) {	//-1 is used by ResetInterior, -2 by ShowOff's ResetInteriorAlt.
			*result = 1;
		}
		else {
			float daysPassed = g_gameTimeGlobals->daysPassed == 0 ? 1.0 : g_gameTimeGlobals->daysPassed->data;
			gameHoursPassed = floor(daysPassed * 24.0);
			*result = ((gameHoursPassed - detachTime) >= iHoursToRespawnCell);
		}
		if (IsConsoleMode())
			Console_Print("IsCellExpired >> %.0f", *result);
	}
	return true;
}

bool Cmd_GetBaseEffectAV_Execute(COMMAND_ARGS) {
	*result = -1;
	EffectSetting* effect = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect) && effect && IS_TYPE(effect, EffectSetting) && (effect->archtype == 0) && effect->actorVal)
		*result = effect->actorVal;
	return true;
}

bool Cmd_GetBaseEffectArchetype_Execute(COMMAND_ARGS) {
	*result = -1;
	EffectSetting* effect = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect) && effect && IS_TYPE(effect, EffectSetting))
		*result = effect->archtype;
	return true;
}

bool Cmd_GetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = nullptr;
	int traitID = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &traitID) && cell && IS_TYPE(cell, TESObjectCELL)) {
		if (!cell->IsInterior() || traitID < 0 || traitID > 15) return true;
		TESObjectCELL::LightingData* lightingData = cell->coords.interior;
		switch (traitID) {
		case 0:
			*result = lightingData->ambientRGB.r;
			break;
		case 1:
			*result = lightingData->ambientRGB.g;
			break;
		case 2:
			*result = lightingData->ambientRGB.b;
			break;
		case 3:
			*result = lightingData->directionalRGB.r;
			break;
		case 4:
			*result = lightingData->directionalRGB.g;
			break;
		case 5:
			*result = lightingData->directionalRGB.b;
			break;
		case 6:
			*result = lightingData->directionalRotXY;
			break;
		case 7:
			*result = lightingData->directionalRotZ;
			break;
		case 8:
			*result = lightingData->directionalFade;
			break;
		case 9:
			*result = lightingData->fogRGB.r;
			break;
		case 10:
			*result = lightingData->fogRGB.g;
			break;
		case 11:
			*result = lightingData->fogRGB.b;
			break;
		case 12:
			*result = lightingData->fogNear;
			break;
		case 13:
			*result = lightingData->fogFar;
			break;
		case 14:
			*result = lightingData->fogPower;
			break;
		case 15:
			*result = lightingData->fogClipDist;
			break;
		default:
			return true;
		}
		if (IsConsoleMode())
			Console_Print("GetInteriorLightingTraitNumeric %d >> %.2f", traitID, *result);
	}
	return true;
}

bool Cmd_SetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = nullptr;
	int traitID = -1;
	float value = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &traitID, &value) && cell && IS_TYPE(cell, TESObjectCELL)) {
		if (!cell->IsInterior() || traitID < 0 || traitID > 15) return true;
		TESObjectCELL::LightingData* lightingData = cell->coords.interior;
		*result = 1;
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
			*result = 0;
			return true;
		}
		if (IsConsoleMode())
			Console_Print("SetInteriorLightingTraitNumeric %d >> %.2f", traitID, value);
	}
	return true;
}

bool Cmd_GetHotkeySlot_Execute(COMMAND_ARGS)
{
	*result = 0;

	if (!thisObj)
		return true;

	InventoryRef* pInvRef = InventoryRefGetForID(thisObj->GetFormID());
	if (!pInvRef || pInvRef->containerRef != PlayerCharacter::GetSingleton())
		return true;

	if (!pInvRef->data.type)
		return true;

	FORM_TYPE eFormType = pInvRef->data.type->GetFormType();
	if (eFormType != FORM_TYPE::TESObjectARMO && eFormType != FORM_TYPE::TESObjectWEAP && eFormType != FORM_TYPE::AlchemyItem)
		return true;

	ExtraDataList* pExtraData = pInvRef->data.xData;
	if (!pExtraData)
		return true;

	ExtraHotkey* pHotkey = pExtraData->GetExtraData<ExtraHotkey>();
	if (pHotkey)
		*result = pHotkey->ucIndex + 1;

	return true;
}

bool Cmd_GetMineArmedEx_Execute(COMMAND_ARGS)
{
	if (GrenadeProjectile* projectile = (GrenadeProjectile*)thisObj; IS_ID(projectile, GrenadeProjectile) && !(projectile->projFlags & 0x200) &&
		((((BGSProjectile*)thisObj->baseForm)->projFlags & 0x426) == 0x26))
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

		if (IsConsoleMode())
			Console_Print("GetCameraShotTraitNumeric %d >> %.2f", eTraitID, *result);
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
		if (IsConsoleMode())
			Console_Print("GetCameraShotFlags >> %08X", pCameraShot->kData.uiFlags);
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
		if (IsConsoleMode())
			Console_Print("GetCameraShotPath >> %s", pModel);
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
		TESImageSpaceModifier* pIMOD = pCameraShot->pModifier;
		if (pIMOD) {
			*reinterpret_cast<uint32_t*>(result) = pIMOD->GetFormID();
		}
		if (IsConsoleMode())
			Console_Print("GetCameraShotImageSpaceModifier >> %s", pIMOD ? pIMOD->GetFormEditorID() : "None");
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

		pCameraShot->pModifier = pIMOD;
		*result = 1;
	}
	return true;
}

namespace RefWalker {
	typedef bool(__fastcall* ReferenceFilterFunc)(const struct FilterData& arFilter, TESObjectREFR* apRef);
	struct ALIGN16 FilterData {
		template<typename T>
		class ScrapVector : public std::vector<T, BSScrapAllocator<T>> {
		};

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
				if (apRef->GetFormType() == eTypeFilter || apRef->baseForm->GetFormType() == eTypeFilter)
					return true;
			}

			return false;
		}

		bool __fastcall CheckDistance(TESObjectREFR* apRef) const {
			const float fDistance = apRef->pos.SqrDistance(NiPoint3(kPosAndDist));
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
			const NiPoint3 kVector = apRef->pos - NiPoint3(kPosAndDist);
			return std::abs(GetAngle(kVector, fHeading)) <= fConeSize;
		}

		bool __fastcall CheckDistanceAndAngle(TESObjectREFR* apRef) const {
			const NiPoint3 kVector = apRef->pos - NiPoint3(kPosAndDist);
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
			if (pRef && pRef->uiFormFlags.IsClear(uiDisallowedFlags) && pRef->GetInitialized() && pRef->baseForm && pRef->Get3DSimple()) {
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
			if (pObject && pObject->uiFormFlags.IsClear(uiDisallowedFlags) && pObject->GetInitialized() && pObject->baseForm) {
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
	*result = 0;
	Script* pScript = nullptr;
	TESObjectCELL* pCell = nullptr;
	FORM_TYPE eFormFilter = FORM_TYPE::NONE;
	float fDistanceFilter = 0.f;
	float fAngleFilter = -FLT_MAX;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pScript, &eFormFilter, &fDistanceFilter, &fAngleFilter, &pCell) && pScript && IS_TYPE(pScript, Script)) {
		if (fDistanceFilter < 0.f)
			fDistanceFilter = 0.f;

		NiPoint4 kPosAndDist;
		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();
		const NiPoint3* pPos = pCaller->PosVector();
		kPosAndDist.x = pPos->x;
		kPosAndDist.y = pPos->y;
		kPosAndDist.z = pPos->z;
		kPosAndDist.w = fDistanceFilter * fDistanceFilter;

		if (pCell && !IS_TYPE(pCell, TESObjectCELL))
			pCell = nullptr;

		if (!pCell && TES::GetSingleton()->currentInterior)
			pCell = TES::GetSingleton()->currentInterior;

		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->rot.z, kPosAndDist);
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
		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();
		const NiPoint3* pPos = pCaller->PosVector();
		kPosAndDist.x = pPos->x;
		kPosAndDist.y = pPos->y;
		kPosAndDist.z = pPos->z;
		kPosAndDist.w = fDistanceFilter * fDistanceFilter;

		if (pCell && !IS_TYPE(pCell, TESObjectCELL))
			pCell = nullptr;

		if (!pCell && TES::GetSingleton()->currentInterior)
			pCell = TES::GetSingleton()->currentInterior;

		FilterData kFilterData(pCaller, pScript, fAngleFilter, pCaller->rot.z, kPosAndDist);
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
	FORM_TYPE eFormFilter = FORM_TYPE::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pScript, &eProcessLevel, &eFormFilter) && pScript && IS_TYPE(pScript, Script)) {
		NiPoint4 kPosAndDist;
		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();

		FilterData kFilterData(pCaller, pScript, 0.f, 0.f, kPosAndDist);
		if (eFormFilter)
			kFilterData.kTypeFilters.push_back(eFormFilter);

		if (!kFilterData.kTypeFilters.empty())
			kFilterData.kFilterFunctions.push_back(TypeFilter);

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

		NiPoint4 kPosAndDist;
		TESObjectREFR* pCaller = thisObj ? thisObj : PlayerCharacter::GetSingleton();
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

static void __fastcall RefreshReferenceModel(TESObjectREFR* apReference, uint32_t auiFlags) {
	if (auiFlags & UPDATE_MODEL) {
		apReference->Update3D();
		ThisCall(0x456520, *reinterpret_cast<DWORD**>(0x1202D98));

		NiAVObject* pRoot = apReference->Get3DSimple();
		if (pRoot && pRoot->IsFadeNode())
			static_cast<BSFadeNode*>(pRoot)->TurnFadeNodeOn();
	}

	if (auiFlags & UPDATE_SCALE)
		apReference->SetScale(apReference->GetRawScale());

	if (auiFlags & UPDATE_LIGHTS) {
		ShadowSceneNode* pSSN = BSShaderManager::GetShadowSceneNode(BSShaderManager::SceneGraphType::WORLD);
		pSSN->UpdateObjectLighting(apReference->Get3DSimple(), false);
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
		if (!thisObj->Get3DSimple() || thisObj->IsStillLoading())
			return true;

		const bool bQueue = AILinearTaskThreadManager::ShouldQueue3DTask();
		if (thisObj->IsActor()) {
			Actor* pActor = static_cast<Actor*>(thisObj);
			if (pActor->baseProcess) {
				// Creatures can't refresh their models in vanilla, so we have to handle them ourselves.
				if (pActor->IsCreature()) {
					RequestModelUpdate(thisObj, uiFlags, bQueue);
				}
				else {
					pActor->baseProcess->Set3DUpdateFlag(uiFlags);
					if (!bQueue)
						pActor->baseProcess->Update3DModel(pActor);


					const uint32_t uiCustomFlags = uiFlags & uiAddedFlags;
					if (uiCustomFlags)
						RequestModelUpdate(thisObj, uiCustomFlags, bQueue);
				}
			}
		}
		else {
			RequestModelUpdate(thisObj, uiFlags, bQueue);
		}

		*result = 1;
	}
	return true;
}

bool Cmd_GetRecipeCategoryFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESRecipeCategory* category = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &category) && category && IS_TYPE(category, TESRecipeCategory)) {
		*result = category->flags;
		if (IsConsoleMode()) Console_Print("GetRecipeCategoryFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_RemapLand_Execute(COMMAND_ARGS) {
	*result = 0;
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

		*result = 1;
	}
	return true;
}

bool Cmd_GetItemEffectString_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form = NULL;
	char extraEffects[0x100] = {};

	ExtractArgsEx(EXTRACT_ARGS_EX, &form);
	if (!form) {
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}

	switch (form->GetFormType()) {
		
		// Item mod
		case FORM_TYPE::TESObjectIMOD:
		{
			TESObjectIMOD* itemMod = static_cast<TESObjectIMOD*>(form);
			if (itemMod) {
				const char* modDesc = itemMod->description.Get(itemMod, 'CSED');
				if (modDesc) {
					strcpy_s(extraEffects, sizeof(extraEffects), modDesc);
				}
			}
		}
		break;
		
		// Ingestible
		case FORM_TYPE::AlchemyItem:
		{
			AlchemyItem* ingestible = static_cast<AlchemyItem*>(form);
			if (ingestible) {
				ThisCall(0x406620, &(ingestible->magicItem.list), extraEffects, sizeof(extraEffects));
			}
		}
		break;
		
		// Ammo
		case FORM_TYPE::TESAmmo:
		{
			TESAmmo* ammo = static_cast<TESAmmo*>(form);
			if (ammo) {
				ThisCall(0x503A70, ammo, extraEffects, sizeof(extraEffects));
			}
		}
		break;
		
		// Weapon & Armor
		default:
		{
			TESEnchantableForm* enchantable = DYNAMIC_CAST(form, TESForm, TESEnchantableForm);
			if (enchantable && enchantable->enchantItem) {
				ThisCall(0x406620, &(enchantable->enchantItem->magicItem.list), extraEffects, sizeof(extraEffects));
			}
		}
	}

	g_strInterface->Assign(PASS_COMMAND_ARGS, extraEffects);

	if (IsConsoleMode())
		Console_Print("GetItemEffectString >> %s", extraEffects);

	return true;
}