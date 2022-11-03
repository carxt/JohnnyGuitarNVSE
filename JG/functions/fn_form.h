#pragma once
// Get/Set/Boolean functions for various form types
#include "GameSettings.h"
DEFINE_COMMAND_PLUGIN(GetBaseEffectAV, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetBaseEffectArchetype, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetInteriorLightingTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetInteriorLightingTraitNumeric, , 0, 3, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetIMODAnimatable, , 0, 1, kParams_OneIMOD);
DEFINE_COMMAND_PLUGIN(SetIMODAnimatable, , 0, 2, kParams_OneIMOD_OneInt);
DEFINE_COMMAND_PLUGIN(SetWeapon1stPersonModel, , 0, 3, kParams_OneForm_OneInt_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetWeapon1stPersonModel, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMusicTypePath, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetMusicTypeDB, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetMusicTypeDB, , 0, 2, kParams_OneForm_OneFloat);
DEFINE_COMMAND_PLUGIN(SetExplosionSound, , 0, 3, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetProjectileSound, , 0, 3, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetWeaponWorldModelPath, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetWeaponWorldModelPath, , 0, 2, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetLifeState, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetRaceFlag, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetRaceFlag, , 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetContainerSound, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetContainerSound, , 0, 3, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetCreatureCombatSkill, , 0, 1, kParams_OneOptionalActorBase);
DEFINE_COMMAND_PLUGIN(GetFacegenModelFlag, , 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(SetFacegenModelFlag, , 0, 4, kParams_OneForm_ThreeInts);
DEFINE_COMMAND_PLUGIN(GetRaceBodyModelPath, , 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(SetEquipType, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetFactionMembers, , 0, 2, kParams_OneForm_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetRaceHeadModelPath, , 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetCalculatedWeaponDPS, , 0, 1, kParams_OneOptionalObjectID);
DEFINE_COMMAND_PLUGIN(IsCellVisited, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(IsCellExpired, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetBufferedCellsAlt, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(GetActorValueModifierAlt, GetAVModAlt, , 1, 2, kParams_OneActorValue_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(RemovePrimitive, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetPrimitiveType, , 1, 0, NULL);
DEFINE_CMD_ALT_COND_PLUGIN(GetBaseScale, GetBasedScale, , 1, NULL);
DEFINE_CMD_ALT_COND_PLUGIN(GetQuestFailed, GetQF, "", false, kParams_OneQuest);
DEFINE_COMMAND_PLUGIN(GetWeaponVATSTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetWeaponVATSTraitNumeric, , 0, 3, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetQuestDelay, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetNoteRead, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetMessageIconPath, , 0, 3, kParams_OneString_OneForm_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetMessageIconPath, , 0, 2, kParams_OneForm_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetBodyPartTraitString, , 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetActorEffectType, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetTalkingActivatorActor, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetPlayerKarmaTitle, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetFaceGenNthProperty, , 0, 3, kParams_OneActorBase_TwoInts);
DEFINE_COMMAND_PLUGIN(SetFaceGenNthProperty, , 0, 4, kParams_OneActorBase_TwoInts_OneFloat);
DEFINE_COMMAND_PLUGIN(FaceGenRefreshAppearance, , 1, 0, NULL);
DEFINE_CMD_NO_ARGS(GetAvailablePerks);
DEFINE_COMMAND_PLUGIN(GetEffectShaderTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetEffectShaderTraitNumeric, , 0, 3, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetEffectShaderTexturePath, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetEffectShaderTexturePath, , 0, 3, kParams_OneForm_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(GetArmorAltTextures, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetIdleMarkerTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetIdleMarkerAnimations, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetIdleMarkerTraitNumeric, , 0, 3, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(SetIdleMarkerAnimation, , 0, 3, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetIdleMarkerAnimations, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetWeaponAltTextures, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(GetRefActivationPromptOverride, GetXATO, , 1, 0, NULL);
DEFINE_COMMAND_ALT_PLUGIN(SetRefActivationPromptOverride, SetXATO, , 1, 1, kParams_OneString);
DEFINE_COMMAND_ALT_PLUGIN(GetRefEncounterZone, GetRefZone, , 1, 0, NULL);
DEFINE_COMMAND_ALT_PLUGIN(SetRefEncounterZone, SetRefZone, , 1, 1, kParams_OneOptionalForm);
DEFINE_COMMAND_ALT_PLUGIN(SetCellEncounterZone, SetCellZone, , 0, 2, kParams_OneForm_OneOptionalForm);
DEFINE_COMMAND_ALT_PLUGIN(GetWorldspaceEncounterZone, GetWorldZone, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetWorldspaceEncounterZone, SetWorldZone, , 0, 2, kParams_OneForm_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetLightingTemplateTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetLightingTemplateTraitNumeric, , 0, 3, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetLightingTemplateCell, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetLightingTemplateCell, , 0, 2, kParams_TwoForms);
DEFINE_COMMAND_PLUGIN(RemoveScopeModelPath, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetArmorAltTexture, , 0, 4, kParams_OneForm_TwoInts_OneForm);
DEFINE_COMMAND_PLUGIN(SetWeaponAltTexture, , 0, 3, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(ClearArmorAltTexture, , 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(ClearWeaponAltTexture, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetFactionFlags, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetFactionFlags, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetFormRecipesAlt, , 0, 1, kParams_OneForm);

float(__fastcall* GetBaseScale)(TESObjectREFR*) = (float(__fastcall*)(TESObjectREFR*)) 0x00567400;
void* (__thiscall* TESNPC_GetFaceGenData)(TESNPC*) = (void* (__thiscall*)(TESNPC*)) 0x0601800;

bool Cmd_GetFormRecipesAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form = nullptr;
	NVSEArrayVar* rcpArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		auto it = g_dataHandler->recipeList.Head();
		do {
			if (it->data && !it->data->outputs.Empty()) {
				TESRecipe::ComponentList* outputs = &it->data->outputs;
				auto it2 = outputs->Head();
				do {
					if (it2->data && it2->data->item && (it2->data->item->refID == form->refID)) {
						g_arrInterface->AppendElement(rcpArr, NVSEArrayElement(it->data));
						break;
					}
				} while (it2 = it2->next);
			} 
		} while (it = it->next);

		
	}
	g_arrInterface->AssignCommandResult(rcpArr, result);
	return true;
}

bool Cmd_SetFactionFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* faction = nullptr;
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &faction, &flags) && IS_TYPE(faction, TESFaction)) {
		faction->factionFlags = flags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetFactionFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* faction = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &faction) && IS_TYPE(faction, TESFaction)) {
		*result = faction->factionFlags;
		if (IsConsoleMode()) Console_Print("GetFactionFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_RemoveScopeModelPath_Execute(COMMAND_ARGS) {
	TESObjectWEAP* weapon = NULL;
	TESModel* model = NULL;
	*result = 0;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon) && IS_TYPE(weapon, TESObjectWEAP)) {
		if (weapon && weapon->HasScope()) model = &(weapon->targetNIF);
		if (model) {
			model->nifPath.Set("");
			*result = 1;
		}
	}

	return true;
}

bool Cmd_SetLightingTemplateCell_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSLightingTemplate* tmpl = nullptr;
	TESObjectCELL* cell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &tmpl, &cell) && IS_TYPE(tmpl, BGSLightingTemplate) && IS_TYPE(cell, TESObjectCELL)) {
		tmpl->getValuesFrom = cell;
	}
	return true;
}

bool Cmd_GetLightingTemplateCell_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSLightingTemplate* tmpl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &tmpl) && IS_TYPE(tmpl, BGSLightingTemplate)) {
		*(UInt32*)result = tmpl->getValuesFrom != nullptr ? tmpl->getValuesFrom->refID : 0;
		if (IsConsoleMode()) Console_Print("GetLightingTemplateCell >> 0x%X", *result);
	}
	return true;
}
bool Cmd_SetLightingTemplateTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 traitID = 0;
	BGSLightingTemplate* tmpl = nullptr;
	float value = 0.0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &tmpl, &traitID, &value) && IS_TYPE(tmpl, BGSLightingTemplate) && traitID > 0) {
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
	UInt32 traitID = 0;
	BGSLightingTemplate* tmpl = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &tmpl, &traitID) && IS_TYPE(tmpl, BGSLightingTemplate) && traitID > 0) {
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
/* 	UInt32			directionalXY;		// 2C
UInt32			directionalZ;		// 30
float			directionalFade;	// 34
float			fogClipDist;		// 38
float			fogPower;*/

BGSEncounterZone* GetEncounterZone(ExtraDataList* list) {
	ExtraEncounterZone* xZone = (ExtraEncounterZone*)list->GetByType(kExtraData_EncounterZone);
	if (xZone && xZone->zone) return xZone->zone;
	return nullptr;
}

void SetEncounterZone(ExtraDataList* list, BGSEncounterZone* zone) {
	ThisStdCall(0x421C60, list, zone);
}

bool Cmd_SetWorldspaceEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* zone = nullptr;
	TESWorldSpace* world;
	ExtractArgsEx(EXTRACT_ARGS_EX, &world, &zone);
	if (!world || !IS_TYPE(world, TESWorldSpace)) return true;
	if (!zone || IS_TYPE(zone, BGSEncounterZone)) {
		world->encounterZone = zone;
		*result = 1;
	}
	return true;
}

bool Cmd_GetWorldspaceEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* world;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &world) && IS_TYPE(world, TESWorldSpace)) {
		BGSEncounterZone* zone = world->encounterZone;
		if (zone) *(UInt32*)result = zone->refID;
	}
	return true;
}

bool Cmd_SetCellEncounterZone_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSEncounterZone* zone = nullptr;
	TESObjectCELL* cell;
	ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &zone);
	if (!cell || !IS_TYPE(cell, TESObjectCELL)) return true;
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
	if (zone) *(UInt32*)result = zone->refID;
	return true;
}

bool Cmd_SetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	char newPrompt[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &newPrompt)) {
		ExtraActivateRef* xActivateRef = (ExtraActivateRef*)thisObj->extraDataList.GetByType(kExtraData_ActivateRef);
		if (xActivateRef) {
			xActivateRef->activationPromptOverride.Set(newPrompt);
		}
		else {
			xActivateRef = (ExtraActivateRef*)GameHeapAlloc(0x20);
			ThisStdCall(0x4338B0, xActivateRef);
			xActivateRef->activationPromptOverride.Set(newPrompt);
			thisObj->extraDataList.Add(xActivateRef);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetRefActivationPromptOverride_Execute(COMMAND_ARGS) {
	*result = 0;
	ExtraActivateRef* xActivateRef = (ExtraActivateRef*)thisObj->extraDataList.GetByType(kExtraData_ActivateRef);
	if (xActivateRef) {
		g_strInterface->Assign(PASS_COMMAND_ARGS, xActivateRef->activationPromptOverride.CStr());
		if (IsConsoleMode()) Console_Print("GetRefActivationPromptOverride >> %s", xActivateRef->activationPromptOverride.CStr());
	}
	return true;
}

bool Cmd_GetWeaponAltTextures_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon;
	NVSEArrayVar* txstArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon) && IS_TYPE(weapon, TESObjectWEAP)) {
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
	NVSEArrayVar* idleArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker) && marker->idleCollection.animCount > 0) {
		for (int i = 0; i < marker->idleCollection.animCount; i++) {
			g_arrInterface->AppendElement(idleArr, NVSEArrayElement(marker->idleCollection.idleList[i]));
		}
	}
	g_arrInterface->AssignCommandResult(idleArr, result);
	return true;
}

bool Cmd_SetIdleMarkerAnimation_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker;
	TESIdleForm* newAnim;
	UInt32 animId;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &animId, &newAnim) && marker->idleCollection.animCount > animId) {
		marker->idleCollection.idleList[animId] = newAnim;
		*result = 1;
	}
	return true;
}

bool Cmd_SetIdleMarkerAnimations_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker;
	UInt32 arrID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &arrID)) {
		NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
		if (!inArr) return true;
		UInt32 size = g_arrInterface->GetArraySize(inArr);
		if (!size) return true;
		NVSEArrayElement* elements = new NVSEArrayElement[size];
		g_arrInterface->GetElements(inArr, elements, NULL);
		TESIdleForm** idleList = (TESIdleForm**)GameHeapAlloc(4 * size);
		for (int i = 0; i < size; i++) {
			idleList[i] = (TESIdleForm*)elements[i].Form();
		}
		if (marker->idleCollection.idleList) GameHeapFree(marker->idleCollection.idleList);
		marker->idleCollection.idleList = idleList;
		marker->idleCollection.animCount = size;
		delete[] elements;
		*result = 1;
	}

	return true;
}

bool Cmd_GetIdleMarkerTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSIdleMarker* marker;
	UInt32 traitID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &traitID)) {
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
	BGSIdleMarker* marker;
	UInt32 traitID;
	float newVal;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &marker, &traitID, &newVal)) {
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
TESModelTextureSwap* GetArmorModel(TESObjectARMO* armor, UInt32 id) {
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
bool Cmd_GetArmorAltTextures_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectARMO* armor;
	UInt32 whichModel;
	NVSEArrayVar* txstArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &whichModel) && IS_TYPE(armor, TESObjectARMO)) {
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
	TESObjectWEAP* weapon;
	BGSTextureSet* txst = nullptr;
	int id = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon, &id, &txst) && IS_TYPE(weapon, TESObjectWEAP) && IS_TYPE(txst, BGSTextureSet)) {
		TESModelTextureSwap* model = &weapon->textureSwap;
		if (!model) return true;
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();
		do {
			if (iter->data && iter->data->index3D == id) {
				iter->data->textureID = txst;
				*result = 1;
				break;
			}
		} while (iter = iter->next);
	}
	return true;
}
bool Cmd_SetArmorAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTextureSet* txst = nullptr;
	TESObjectARMO* armor = nullptr;
	int id = -1;
	UInt32 whichModel;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &whichModel, &id, &txst) && IS_TYPE(txst, BGSTextureSet) && IS_TYPE(armor, TESObjectARMO)) {
		TESModelTextureSwap* model = GetArmorModel(armor, whichModel);
		if (!model) return true;
		ListNode<TESModelTextureSwap::Texture>* iter = model->textureList.Head();
		do {
			if (iter->data && iter->data->index3D == id) {
				iter->data->textureID = txst;
				*result = 1;
				break;
			}
		} while (iter = iter->next);
	}
	return true;
}

bool Cmd_ClearWeaponAltTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon;
	int id = -2;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon, &id) && IS_TYPE(weapon, TESObjectWEAP)) {
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
	UInt32 whichModel;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &whichModel, &id) && IS_TYPE(armor, TESObjectARMO)) {
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
	TESEffectShader* shader;
	UInt32 traitID;
	char newPath[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shader, &traitID, &newPath) && traitID >= 0 && traitID <= 2) {
		switch (traitID) {
			case 0:
				shader->fillTexture.ddsPath.Set(newPath);
				break;
			case 1:
				shader->particleShaderTexture.ddsPath.Set(newPath);
				break;
			case 2:
				shader->holesTexture.ddsPath.Set(newPath);
				break;
		}
		*result = 1;
	}
	return true;
}

bool Cmd_GetEffectShaderTexturePath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESEffectShader* shader;
	UInt32 traitID;
	const char* resStr = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shader, &traitID) && traitID >= 0 && traitID <= 2) {
		switch (traitID) {
			case 0:
				resStr = shader->fillTexture.ddsPath.m_data;
				break;
			case 1:
				resStr = shader->particleShaderTexture.ddsPath.m_data;
				break;
			case 2:
				resStr = shader->holesTexture.ddsPath.m_data;
				break;
		}
		g_strInterface->Assign(PASS_COMMAND_ARGS, resStr);
	}
	return true;
}
UInt32 SwapRGB(UInt32 rgbhex) {
	UInt32 r = (rgbhex >> 0x10) & 0xFF;
	UInt32 g = (rgbhex >> 0x8) & 0xFF;
	UInt32 b = (rgbhex) & 0xFF;
	return (b << 0x10) + (g << 0x8) + r;
}

bool Cmd_SetEffectShaderTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESEffectShader* shader;
	UInt32 traitID;
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shader, &traitID, &value) && traitID >= 0 && traitID <= 76) {
		switch (traitID) {
			case 0:
				shader->shaderData.flags = (UInt8)value;
				break;
			case 61:
				shader->shaderData.addonModels->refID = (UInt32)value;
				break;
			case 4:
			case 14:
			case 47:
			case 48:
			case 49:
				((UInt32*)shader)[6 + traitID] = SwapRGB((UInt32)value);
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
				((UInt32*)shader)[6 + traitID] = (UInt32)value;
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
	UInt32 traitID;
	UInt32 color;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &shader, &traitID) && traitID >= 0 && traitID <= 76) {
		switch (traitID) {
			case 0:
				*result = shader->shaderData.flags;
				break;
			case 61:
				*result = shader->shaderData.addonModels->refID;
				break;
			case 4:
			case 14:
			case 47:
			case 48:
			case 49:
				color = SwapRGB(((UInt32*)shader)[6 + traitID]);
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
				*result = ((UInt32*)shader)[6 + traitID];
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
	for (int i = 0; i < perk->conditions.Count(); i++) {
		Condition* condition = perk->conditions.GetNthItem(i);
		bool result = false;
		if (condition->opcode == 0x46 && !condition->Evaluate(g_thePlayer, 0, &result)) return false;
	}
	return true;
}

bool Cmd_GetAvailablePerks_Execute(COMMAND_ARGS) {
	*result = 0;
	NVSEArrayVar* perkArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	ListNode<BGSPerk>* perkIter = g_dataHandler->perkList.Head();
	BGSPerk* perk;
	int perkRank;
	do {
		perk = perkIter->data;
		if (perk->data.isPlayable && perk->data.minLevel > 0 && perk->data.minLevel <= g_thePlayer->avOwner.GetLevel()) {
			perkRank = g_thePlayer->GetPerkRank(perk, 0);
			bool result = false;
			if (perkRank < perk->data.numRanks && !perk->data.isTrait && IsApplicable(perk)
				&& perk->conditions.Evaluate(g_thePlayer, 0, &result, 0)) {
				g_arrInterface->AppendElement(perkArr, NVSEArrayElement(perk));
			}
		}
	} while (perkIter = perkIter->next);
	g_arrInterface->AssignCommandResult(perkArr, result);
	return true;
}
bool Cmd_FaceGenRefreshAppearance_Execute(COMMAND_ARGS) {
	*result = 0;
	if (thisObj && thisObj->IsCharacter()) {
		ThisStdCall(0x08D3FA0, thisObj);
		*result = 1;
	}
	return true;
}
bool Cmd_GetFaceGenNthProperty_Execute(COMMAND_ARGS) {
	TESNPC* npc = NULL;
	UInt32 PropertyListIndex = 0;
	UInt32 PropertyIndex = 0;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &npc, &PropertyListIndex, &PropertyIndex) && npc && IS_TYPE(npc, TESNPC) && PropertyListIndex < 3) {
		if (auto FaceGenPTR = TESNPC_GetFaceGenData(npc)) {
			*result = CdeclCall<float>(0x652230, FaceGenPTR, UInt32(PropertyListIndex < 1), UInt32(PropertyListIndex > 1), PropertyIndex);
			if (IsConsoleMode())
				Console_Print("GetFaceGenNthProperty %.2f", *result);
		}
	}
	return true;
}

bool Cmd_SetFaceGenNthProperty_Execute(COMMAND_ARGS) {
	TESNPC* npc = NULL;
	UInt32 PropertyListIndex = 0;
	UInt32 PropertyIndex = 0;
	float val = 0;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &npc, &PropertyListIndex, &PropertyIndex, &val) && npc && IS_TYPE(npc, TESNPC) && PropertyListIndex < 3) {
		if (auto FaceGenPTR = TESNPC_GetFaceGenData(npc)) {
			CdeclCall<void>(0x652320, FaceGenPTR, (PropertyListIndex < 1), (PropertyListIndex > 1), PropertyIndex, val);
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
	UInt32 titleOrTier = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &titleOrTier);
	if (titleOrTier == 1) {
		int karmaTier = CdeclCall<int>(0x47E040, g_thePlayer->avOwner.GetActorValue(kAVCode_Karma)); // GetKarmaTier
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
		title = CdeclCall<char*>(0x47E0E0, g_thePlayer); // Actor::GetKarmaTitle
	}
	if (IsConsoleMode()) Console_Print("GetPlayerKarmaTitle >> %s", title);
	g_strInterface->Assign(PASS_COMMAND_ARGS, title);
	return true;
}
bool Cmd_GetTalkingActivatorActor_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTalkingActivator* activator;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &activator) && IS_TYPE(activator, BGSTalkingActivator)) {
		if (activator->talkingActor) {
			*(UInt32*)result = activator->talkingActor->refID;
		}
		if (IsConsoleMode()) Console_Print("GetTalkingActivatorActor >> 0x%X", *result);
	}
	return true;
}
bool Cmd_GetActorEffectType_Execute(COMMAND_ARGS) {
	*result = 0;
	SpellItem* effect;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect) && IS_TYPE(effect, SpellItem)) {
		*result = effect->type;
		if (IsConsoleMode()) Console_Print("GetActorEffectType >> %.2f", *result);
	}
	else {
		*result = -1;
	}
	return true;
}
bool Cmd_GetBodyPartTraitString_Execute(COMMAND_ARGS) {
	const char* resStr = NULL;
	BGSBodyPartData* bpData;
	UInt32 partID;
	UInt32 traitID;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bpData, &partID, &traitID)) {
		if (IS_ID(bpData, BGSBodyPartData) && (partID <= 14) && (traitID <= 5)) {
			if (const BGSBodyPart* bodyPart = bpData->bodyParts[partID]) {
				switch (traitID) {
				case 1:
					if (bodyPart->partNode.m_dataLen) resStr = bodyPart->partNode.m_data;
					break;
				case 2:
					if (bodyPart->VATSTarget.m_dataLen) resStr = bodyPart->VATSTarget.m_data;
					break;
				case 3:
					if (bodyPart->startNode.m_dataLen) resStr = bodyPart->startNode.m_data;
					break;
				case 4:
					if (bodyPart->partName.m_dataLen) resStr = bodyPart->partName.m_data;
					break;
				case 5:
					if (bodyPart->targetBone.m_dataLen) resStr = bodyPart->targetBone.m_data;
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
	UInt32 isFemale = 0;
	TESForm* form = nullptr;
	const char* path = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form, &isFemale)) {
		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel) {
			path = bipedModel->messageIcon[isFemale].icon.ddsPath.CStr();
		}
		else {
			BGSMessageIcon* icon = DYNAMIC_CAST(form, TESForm, BGSMessageIcon);
			if (icon) {
				path = icon->icon.ddsPath.CStr();
			}
		}
		if (IsConsoleMode()) Console_Print("GetMessageIconPath >> %s", path);
		g_strInterface->Assign(PASS_COMMAND_ARGS, path);
	}
	return true;
}
bool Cmd_SetMessageIconPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char path[MAX_PATH];
	UInt32 isFemale = 0;
	TESForm* form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &form, &isFemale)) {
		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel) {
			bipedModel->messageIcon[isFemale].icon.ddsPath.Set(path);
			*result = 1;
		}
		else {
			BGSMessageIcon* icon = DYNAMIC_CAST(form, TESForm, BGSMessageIcon);
			if (icon) {
				icon->icon.ddsPath.Set(path);
				*result = 1;
			}
		}
	}
	return true;
}
bool Cmd_SetNoteRead_Execute(COMMAND_ARGS) {
	UInt32 isRead = 0;
	*result = 0;
	BGSNote* note;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &note, &isRead)) {
		note->read = isRead > 0 ? 1 : 0;
		*result = 1;
	}
	return true;
}
bool Cmd_GetQuestDelay_Execute(COMMAND_ARGS) {
	*result = 0;
	TESQuest* quest;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest) && IS_TYPE(quest, TESQuest)) {
		*result = quest->questDelayTime;
		if (IsConsoleMode()) Console_Print("GetQuestDelay >> *.3f", *result);
	}
	return true;
}
bool Cmd_GetWeaponVATSTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weap;
	UInt32 traitID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &traitID) && IS_TYPE(weap, TESObjectWEAP)) {
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
	TESObjectWEAP* weap;
	UInt32 traitID = 0;
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &traitID, &value) && IS_TYPE(weap, TESObjectWEAP)) {
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
	TESQuest* quest;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest))
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
	TESObjectWEAP* weapon;
	const char* modelPath;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon) && IS_TYPE(weapon, TESObjectWEAP)) {
		modelPath = weapon->model200.GetModelPath();
		g_strInterface->Assign(PASS_COMMAND_ARGS, modelPath);
		if (IsConsoleMode()) Console_Print("GetWeaponWorldModelPath >> %s", modelPath);
	}
	return true;
}
bool Cmd_SetWeaponWorldModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon;
	char modelPath[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weapon, &modelPath) && IS_TYPE(weapon, TESObjectWEAP)) {
		weapon->model200.SetModelPath(modelPath);
		*result = 1;
	}
	return true;
}
bool Cmd_SetProjectileSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSProjectile* projectile;
	TESSound* sound = NULL;
	int soundID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &projectile, &soundID, &sound) && IS_TYPE(projectile, BGSProjectile) && soundID && soundID <= 3) {
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
	BGSExplosion* explosion;
	TESSound* sound = NULL;
	int soundID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &explosion, &soundID, &sound) && IS_TYPE(explosion, BGSExplosion) && soundID && soundID <= 2) {
		soundID == 1 ? (explosion->sound1 = sound) : (explosion->sound2 = sound);
		*result = 1;
	}
	return true;
}
bool Cmd_GetCreatureCombatSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESCreature* creature = NULL;
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
	TESObjectCONT* container;
	TESSound* newSound;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &container, &whichSound, &newSound) && IS_TYPE(container, TESObjectCONT) && IS_TYPE(newSound, TESSound)) {
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
	TESObjectCONT* container;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &container, &whichSound) && IS_TYPE(container, TESObjectCONT)) {
		switch (whichSound) {
			case 0:
				if (container->openSound) *(UInt32*)result = container->openSound->refID;
				break;
			case 1:
				if (container->closeSound) *(UInt32*)result = container->closeSound->refID;
				break;
			case 2:
				if (container->randomLoopingSound) *(UInt32*)result = container->randomLoopingSound->refID;
				break;
		}
	}
	return true;
}

bool Cmd_GetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* race;
	UINT32 bit;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &bit) && IS_TYPE(race, TESRace)) {
		*result = (race->raceFlags & 1 << bit);
		if (IsConsoleMode()) Console_Print("GetRaceFlag >> %.f", *result);
	}
	return true;
}

bool Cmd_SetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* race;
	UINT32 bit;
	UINT32 setorclear;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &bit, &setorclear) && IS_TYPE(race, TESRace)) {
		setorclear ? race->raceFlags |= (1 << bit) : race->raceFlags &= ~(1 << bit);
		*result = 1;
	}
	return true;
}
// 0 - alive, 1 - dying/ragdolled, 2 - dead, 3 - unconscious, 5 - restrained, 6 - essential unconscious
bool Cmd_GetLifeState_Execute(COMMAND_ARGS) {
	Actor* actor = (Actor*)thisObj;
	*result = -1;
	if (actor) {
		*result = actor->lifeState;
		if (IsConsoleMode()) Console_Print("GetLifeState >> %.f", *result);
	}
	return true;
}

bool Cmd_GetFactionMembers_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* faction;
	SInt32 rank = -1;
	NVSEArrayVar* factionMemberArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	ExtractArgsEx(EXTRACT_ARGS_EX, &faction, &rank);
	if (faction) {
		for (TESBoundObject* object = g_dataHandler->boundObjectList->first; object; object = object->next) {
			TESActorBase* actorBase = DYNAMIC_CAST(object, TESBoundObject, TESActorBase);
			if (actorBase && actorBase->baseData.factionList.Count() != 0) {
				ListNode<FactionListData>* fctIter = actorBase->baseData.factionList.Head();
				FactionListData* factionData;
				do {
					factionData = fctIter->data;
					if (factionData && factionData->faction && factionData->faction == faction) {
						if (rank == -1 || (rank == factionData->rank)) {
							g_arrInterface->AppendElement(factionMemberArr, NVSEArrayElement(actorBase));
						}
					}
				} while (fctIter = fctIter->next);
			}
		}
	}
	g_arrInterface->AssignCommandResult(factionMemberArr, result);
	return true;
}
bool Cmd_SetEquipType_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* pForm = 0;
	UInt32 newEquipType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm, &newEquipType) && newEquipType <= 13) {
		pForm = pForm->TryGetREFRParent();
		BGSEquipType* pEquipType = DYNAMIC_CAST(pForm, TESForm, BGSEquipType);
		if (pEquipType) {
			pEquipType->equipType = newEquipType;
			*result = 1;
		}
	}
	return true;
}
bool Cmd_GetRaceHeadModelPath_Execute(COMMAND_ARGS) {
	TESRace* race;
	UInt32 modelID, isFemale;
	const char* path = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &modelID, &isFemale)) {
		if (isFemale <= 1 && modelID <= 7) {
			path = race->faceModels[isFemale][modelID].nifPath.CStr();
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
	TESRace* race;
	UInt32 modelID, isFemale;
	const char* path = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &race, &modelID, &isFemale)) {
		if (isFemale <= 1 && modelID <= 2) {
			path = race->bodyModels[isFemale][modelID].nifPath.CStr();
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
	TESObjectARMO* armor;
	UInt32 isFemale, flagID;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &flagID, &isFemale)) {
		if (isFemale <= 1 && flagID <= 3) {
			*result = (armor->bipedModel.bipedModel[isFemale].facegenFlags & (1 << flagID)) ? 1 : 0;
			if (IsConsoleMode()) {
				Console_Print("GetFacegenModelFlag %i %i >> %.f", flagID, isFemale, *result);
			}
		}
	}
	return true;
}
bool Cmd_SetFacegenModelFlag_Execute(COMMAND_ARGS) {
	TESObjectARMO* armor;
	UInt32 isFemale;
	UInt32 flagID;
	bool bEnable;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &armor, &flagID, &isFemale, &bEnable) && flagID <= 3) {
		armor->SetFacegenFlag(1 << flagID, isFemale, bEnable);
		*result = 1;
	}
	return true;
}

bool Cmd_GetBaseScale_Eval(COMMAND_ARGS_EVAL) {
	if (thisObj) {
		*result = GetBaseScale(thisObj);
		if (IsConsoleMode())
			Console_Print("GetBaseScale : %0.2f", *result);
	}
	return true;
}

bool Cmd_GetBaseScale_Execute(COMMAND_ARGS) {
	return Cmd_GetBaseScale_Eval(thisObj, 0, 0, result);
}

bool Cmd_RemovePrimitive_Execute(COMMAND_ARGS) {
	*result = 0;
	ExtraPrimitive* xPrimitive;
	if (thisObj->extraDataList.HasType(kExtraData_Primitive)) {
		xPrimitive = GetExtraType(thisObj->extraDataList, Primitive);
		thisObj->extraDataList.Remove(xPrimitive, true);
		thisObj->Update3D();
		*result = 1;
	}
	return true;
}
bool Cmd_GetPrimitiveType_Execute(COMMAND_ARGS) {
	ExtraPrimitive* xPrimitive = GetExtraType(thisObj->extraDataList, Primitive);
	*result = (xPrimitive && xPrimitive->primitive) ? xPrimitive->primitive->type : 0;
	return true;
}

bool Cmd_GetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype;
	const char* path = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mtype) && IS_TYPE(mtype, BGSMusicType)) {
		path = mtype->soundFile.path.CStr();
		g_strInterface->Assign(PASS_COMMAND_ARGS, path);
		if (IsConsoleMode()) {
			Console_Print("GetMusicTypePath >> %s", path);
		}
	}
	return true;
}

bool Cmd_GetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mtype) && IS_TYPE(mtype, BGSMusicType)) {
		*result = mtype->dB;
		if (IsConsoleMode())
			Console_Print("GetMusicTypeDB >> %f", *result);
	}
	return true;
}
bool Cmd_SetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype;
	float newVal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mtype, &newVal) && IS_TYPE(mtype, BGSMusicType)) {
		mtype->dB = newVal;
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
	TESObjectWEAP* weap;
	int id = -1;
	TESObjectSTAT* model = nullptr;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &id, &model) && IS_TYPE(weap, TESObjectWEAP) && (!model || IS_TYPE(model, TESObjectSTAT)) && id <= 7) {
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
	TESObjectWEAP* weap;
	int id = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &weap, &id) && IS_TYPE(weap, TESObjectWEAP) && id <= 7) {
		switch (id) {
			case 0:
				*(UInt32*)result = weap->worldStatic->refID;
				break;
			case 1:
				*(UInt32*)result = weap->modStatics[0]->refID;
				break;
			case 2:
				*(UInt32*)result = weap->modStatics[1]->refID;
				break;
			case 3:
				*(UInt32*)result = weap->modStatics[3]->refID;
				break;
			case 4:
				*(UInt32*)result = weap->modStatics[2]->refID;
				break;
			case 5:
				*(UInt32*)result = weap->modStatics[5]->refID;
				break;
			case 6:
				*(UInt32*)result = weap->modStatics[4]->refID;
				break;
			case 7:
				*(UInt32*)result = weap->modStatics[6]->refID;
				break;
		}
	}
	return true;
}

bool Cmd_GetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &imod)) {
		*result = imod->animable;
		if (IsConsoleMode())
			Console_Print("GetIMODAnimatable >> %.f", *result);
	}
	return true;
}

bool Cmd_SetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod;
	int newVal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &imod, &newVal) && (newVal == 0 || newVal == 1)) {
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
	TESObjectWEAP* weapon = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &weapon)) return true;
	float condition = 1.0F;
	ListNode<ExtraDataList>* extendPtr = NULL;
	if (!weapon) {
		if (!thisObj) return true;
		InventoryRef* invRef = InventoryRefGetForID(thisObj->refID);
		if (!invRef) return true;
		weapon = (TESObjectWEAP*)invRef->data.type;
		if NOT_ID(weapon, TESObjectWEAP) return true;
		if (invRef->data.xData) {
			condition = invRef->data.entry->GetItemHealthPerc() / 100.0F;
			ListNode<ExtraDataList> tempExtend(invRef->data.xData);
			extendPtr = &tempExtend;
		}
	}
	else if NOT_ID(weapon, TESObjectWEAP) return true;
	MiddleHighProcess* midHiProc = (MiddleHighProcess*)g_thePlayer->baseProcess;
	ContChangesEntry* weaponInfo = midHiProc->weaponInfo;
	TESForm* ammo = NULL;
	if (extendPtr && weaponInfo && (weaponInfo->type == weapon) && midHiProc->ammoInfo)
		ammo = midHiProc->ammoInfo->type;
	if (!ammo) ammo = weapon->GetAmmo();
	ContChangesEntry tempEntry(extendPtr, 1, weapon);
	midHiProc->weaponInfo = NULL;
	*result = GetWeaponDPS(&(g_thePlayer->avOwner), weapon, condition, 1, weaponInfo, 0, 0, -1, 0.0, 0.0, 0, 0, ammo);
	midHiProc->weaponInfo = weaponInfo;
	if (IsConsoleMode())
		Console_Print("GetCalculatedWeaponDPS >> %f", *result);
	return true;
}

bool Cmd_IsCellVisited_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell) && IS_TYPE(cell, TESObjectCELL)) {
		ExtraSeenData* seenData = (ExtraSeenData*)cell->extraDataList.GetByType(kExtraData_SeenData);
		if (seenData && seenData->data) *result = 1;
		if (IsConsoleMode())
			Console_Print("IsCellVisited >> %.0f", *result);
	}
	return true;
}

bool Cmd_IsCellExpired_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = NULL;
	UInt32 iHoursToRespawnCell = *(UInt32*)0x11CA164;
	SInt32 detachTime = 0;
	float gameHoursPassed = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell) && IS_TYPE(cell, TESObjectCELL)) {
		ExtraDetachTime* xDetachTime = (ExtraDetachTime*)cell->extraDataList.GetByType(kExtraData_DetachTime);
		detachTime = xDetachTime == 0 ? 0 : xDetachTime->time;
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
	EffectSetting* effect;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect) && IS_TYPE(effect, EffectSetting) && (effect->archtype == 0) && effect->actorVal)
		*result = effect->actorVal;
	return true;
}
bool Cmd_GetBaseEffectArchetype_Execute(COMMAND_ARGS) {
	*result = -1;
	EffectSetting* effect;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect) && IS_TYPE(effect, EffectSetting))
		*result = effect->archtype;
	return true;
}

bool Cmd_GetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = NULL;
	int traitID = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &traitID) && IS_TYPE(cell, TESObjectCELL)) {
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
	TESObjectCELL* cell = NULL;
	int traitID = -1;
	float value = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &traitID, &value) && IS_TYPE(cell, TESObjectCELL)) {
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
