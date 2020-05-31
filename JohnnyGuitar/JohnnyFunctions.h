#pragma once
#define VarNameSize 64
DEFINE_COMMAND_PLUGIN(WorldToScreen, , 0, 8, kParamsProjectionArgs);
DEFINE_COMMAND_PLUGIN(ToggleLevelUpMenu, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(IsLevelUpMenuEnabled, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetBaseEffectAV, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetBaseEffectArchetype, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(IsCellVisited, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(IsCellExpired, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(MD5File, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SHA1File, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(TogglePipBoy, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(ShowPerkMenu, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetCalculatedWeaponDPS, , 0, 1, kParams_OneOptionalObjectID);
DEFINE_COMMAND_PLUGIN(GetInteriorLightingTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetInteriorLightingTraitNumeric, , 0, 3, kParamsJohnnyOneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetPixelFromBMP, , 0, 6, kParamsBMPArgs);
DEFINE_COMMAND_PLUGIN(GetWorldSpaceMapTexture, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(Jump, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(StopVATSCam, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetCameraShake, , 0, 2, kParams_TwoFloats);
DEFINE_COMMAND_PLUGIN(ApplyWeaponPoison, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SendStealingAlarm, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(GetIMODAnimatable, , 0, 1, kParamsJohnny_OneIMOD);
DEFINE_COMMAND_PLUGIN(SetIMODAnimatable, , 0, 2, kParamsJohnny_OneIMOD_OneInt);
DEFINE_COMMAND_PLUGIN(GetEditorID, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetJohnnyPatch, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(SetVelEx, , 1, 3, kParamsJohnnyThreeFloats);
DEFINE_COMMAND_PLUGIN(UwUDelete, , 0, 2, kParamsJohnny_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitSound, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitString, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitNumeric, , 0, 3, kParamsJohnnyOneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitSound, , 0, 3, kParamsJohnnyOneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitString, , 0, 3, kParamsJohnnyOneForm_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(SetWeapon1stPersonModel, , 0, 3, kParamsJohnnyOneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetWeapon1stPersonModel, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetBufferedCellsAlt, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetTimePlayed, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_ALT_PLUGIN(GetActorValueModifierAlt, GetAVModAlt, , 1, 2, kParamsJohnny_OneActorValue_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(AsmBreak, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(RefAddr, , 0, 1, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetMusicTypePath, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetMusicTypeDB, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetMusicTypeDB, , 0, 2, kParams_OneForm_OneFloat);
DEFINE_COMMAND_PLUGIN(EditorIDToFormID, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetRegionWeatherOverride, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherOverride, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetRegionWeatherPriority, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherPriority, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(IsWeatherInRegion, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(RemoveRegionWeather, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(AddRegionWeather, , 0, 4, kParams_Johnny_OneForm_OneWeatherID_OneInt_OneOptionalGlobal);
DEFINE_COMMAND_PLUGIN(GetRegionWeathers, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(ClearRegionWeathers, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(StopSoundAlt, , 0, 2, kParamsJohnny_TwoForms);
DEFINE_COMMAND_PLUGIN(RemovePrimitive, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetPrimitiveType, , 1, 0, NULL);
DEFINE_CMD_ALT_COND_PLUGIN(GetBaseScale, , , 1, NULL);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarker, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(UnsetAV, , 1, 1, kParams_OneActorValue);
DEFINE_COMMAND_PLUGIN(UnforceAV, , 1, 1, kParams_OneActorValue);
DEFINE_COMMAND_PLUGIN(ToggleNthPipboyLight, , 0, 2, kParams_TwoInts);
DEFINE_COMMAND_PLUGIN(SetBipedIconPathAlt, , 0, 3, kParamsJohnny_OneString_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetFacegenModelFlag, , 0, 3, kParamsJohnny_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(SetFacegenModelFlag, , 0, 4, kParamsJohnny_OneForm_ThreeInts);
DEFINE_COMMAND_PLUGIN(GetRaceBodyModelPath, , 0, 3, kParamsJohnny_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(SetEquipType, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetFactionMembers, , 0, 2, kParamsJohnny_OneForm_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetRaceHeadModelPath, , 0, 3, kParamsJohnny_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetDefaultHeapSize, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(Get3DDistanceBetweenNiNodes, , 0, 4, kParamsJohnnyTwoRefsTwoStrings);
DEFINE_COMMAND_PLUGIN(Get3DDistanceToNiNode, , 1, 4, kParamsJohnnyOneStringThreeFloats);
DEFINE_COMMAND_PLUGIN(Get3DDistanceFromHitToNiNode, , 1, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetVector3DDistance, , 0, 6, kParamsJohnny_SixFloats);
DEFINE_COMMAND_PLUGIN(GetLinearVelocity, , 1, 4, kParamsJohnnyFourStrings);
DEFINE_COMMAND_PLUGIN(GetLifeState, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetRaceFlag, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetRaceFlag, , 0, 3, kParamsJohnny_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetContainerSound, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetContainerSound, , 0, 3, kParamsJohnnyOneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetCreatureCombatSkill, , 0, 1, kParams_OneOptionalActorBase);
DEFINE_COMMAND_PLUGIN(DisableMuzzleFlashLights, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetCustomMapMarkerIcon, , 0, 2, kParamsJohnny_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(SetExplosionSound, , 0, 3, kParamsJohnnyOneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetProjectileSound, , 0, 3, kParamsJohnnyOneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetWeaponWorldModelPath, , 0, 2, kParamsJohnny_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(Clamp, , 0, 3, kParamsJohnnyThreeFloats);
DEFINE_COMMAND_PLUGIN(Remap, , 0, 5, kParamsJohnnyFiveFloats);
DEFINE_COMMAND_PLUGIN(Lerp, , 0, 3, kParamsJohnnyThreeFloats);
#include "internal/decoding.h"
float(__fastcall* GetBaseScale)(TESObjectREFR*) = (float(__fastcall*)(TESObjectREFR*)) 0x00567400;
void(__cdecl* HandleActorValueChange)(ActorValueOwner* avOwner, int avCode, float oldVal, float newVal, ActorValueOwner* avOwner2) =
(void(__cdecl*)(ActorValueOwner*, int, float, float, ActorValueOwner*))0x66EE50;
bool Cmd_Lerp_Execute(COMMAND_ARGS) {
	float v0 = 0, v1 = 0, t = 0;
	if (ExtractArgs(EXTRACT_ARGS, &v0, &v1, &t)) {
		*result = (1 - t) * v0 + t * v1;
	}
	return true;
}
bool Cmd_Remap_Execute(COMMAND_ARGS) {
	float v1current = 0, v1min = 0, v1max = 0, v2min = 0, v2max = 0;
	if (ExtractArgs(EXTRACT_ARGS, &v1current, &v1min, &v1max, &v2min, &v2max)) {
		*result = (v1current - v1min) / (v1max - v1min) * (v2max - v2min) + v2min;
	}
	return true;
}
bool Cmd_Clamp_Execute(COMMAND_ARGS) {
	float value = 0, min = 0, max = 0;
	if (ExtractArgs(EXTRACT_ARGS, &value, &min, &max)) {
		*result = value;
		if (value < min) {
			*result = min;
		}
		else if (value > max) {
			*result = max;
		}

	}
	return true;
	
}
bool Cmd_SetWeaponWorldModelPath_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectWEAP* weapon;
	char modelPath[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &weapon, &modelPath) && IS_TYPE(weapon, TESObjectWEAP)) {
		weapon->model200.SetModelPath(modelPath);
	}
	return true;
}
bool Cmd_SetProjectileSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSProjectile* projectile;
	TESSound* sound = NULL;
	int soundID = 0;
	if (ExtractArgs(EXTRACT_ARGS, &projectile, &soundID, &sound) && IS_TYPE(projectile, BGSProjectile) && soundID && soundID <= 3) {
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
		}
	}
	return true;
}

bool Cmd_SetExplosionSound_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSExplosion* explosion;
	TESSound* sound = NULL;
	int soundID = 0;
	if (ExtractArgs(EXTRACT_ARGS, &explosion, &soundID, &sound) && IS_TYPE(explosion, BGSExplosion) && soundID && soundID <= 2) {
		soundID == 1 ? (explosion->sound1 = sound) : (explosion->sound2 = sound);
	}
	return true;
}
bool Cmd_GetCreatureCombatSkill_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESCreature *creature = NULL;
	if (!ExtractArgs(EXTRACT_ARGS, &creature)) return true;
	if (!creature)
	{
		if (!thisObj || !thisObj->IsActor()) return true;
		creature = (TESCreature*)((Actor*)thisObj)->GetActorBase();
	}
	if IS_TYPE(creature, TESCreature)
		*result = creature->combatSkill;
	return true;
}
bool Cmd_SetContainerSound_Execute(COMMAND_ARGS) {
	int whichSound = -1;
	TESObjectCONT* container;
	TESSound* newSound;
	if (ExtractArgs(EXTRACT_ARGS, &container, &whichSound, &newSound) && IS_TYPE(container, TESObjectCONT) && IS_TYPE(newSound, TESSound)) {
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
		}
	}
	return true;
}
bool Cmd_GetContainerSound_Execute(COMMAND_ARGS) {
	*result = 0;
	int whichSound = -1;
	TESObjectCONT* container;
	if (ExtractArgs(EXTRACT_ARGS, &container, &whichSound) && IS_TYPE(container, TESObjectCONT)) {
		switch (whichSound) {
		case 0:
			*(UInt32*)result = container->openSound->refID;
			break;
		case 1:
			*(UInt32*)result = container->closeSound->refID;
			break;
		case 2:
			*(UInt32*)result = container->randomLoopingSound->refID;
			break;
		}
	}
	return true;
}

bool Cmd_GetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* race;
	UINT32 bit;
	if (ExtractArgs(EXTRACT_ARGS, &race, &bit) && IS_TYPE(race, TESRace))
	{
		*result = (race->raceFlags & 1 << bit);
		if (IsConsoleMode()) Console_Print("GetRaceFlag >> %.f", *result);
	}
	return true;
}


bool Cmd_SetRaceFlag_Execute(COMMAND_ARGS) {
	TESRace* race;
	UINT32 bit;
	UINT32 setorclear;
	if (ExtractArgs(EXTRACT_ARGS, &race, &bit, &setorclear) && IS_TYPE(race, TESRace))
	{
		setorclear ? race->raceFlags |= (1 << bit) : race->raceFlags &= ~(1 << bit);
	}
	return true;
}
// 0 - alive, 1 - dying/ragdolled, 2 - dead, 3 - unconscious, 5 - restrained
bool Cmd_GetLifeState_Execute(COMMAND_ARGS) {
	Actor* actor = (Actor*)thisObj;
	*result = -1;
	if (actor) {
		*result = actor->lifeState;
		if (IsConsoleMode()) Console_Print("GetLifeState >> %.f", *result);
	}
	return true;
}
bool Cmd_GetLinearVelocity_Execute(COMMAND_ARGS) {
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	char nodeName[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &nodeName, &X_outS, &Y_outS, &Z_outS))
	{
		hkpRigidBody* rigidBody = thisObj->GetRigidBody(nodeName);
		if (rigidBody)
		{
			NiVector4 linVelocity = rigidBody->motion.linVelocity;
			setVarByName(PASS_VARARGS, X_outS, linVelocity.x);
			setVarByName(PASS_VARARGS, Y_outS, linVelocity.y);
			setVarByName(PASS_VARARGS, Z_outS, linVelocity.z);
		}
	}
	return true;
}
bool Cmd_GetVector3DDistance_Execute(COMMAND_ARGS) {
	*result = 0;
	NiVector3 pos1;
	NiVector3 pos2;
	if (ExtractArgs(EXTRACT_ARGS, &(pos1.x), &(pos1.y), &(pos1.z), &(pos2.x), &(pos2.y), &(pos2.z))) {
		*result = NiNodeComputeDistance(&pos1, &pos2);
		if (IsConsoleMode()) Console_Print("Get3DDistance >> %f", *result);
	}
	return true;
}

bool Cmd_Get3DDistanceFromHitToNiNode_Execute(COMMAND_ARGS)
{
	Actor* actor = (Actor*)thisObj;
	char NiName[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &NiName) && actor->IsActor() && actor->baseProcess)
	{
		NiAVObject* t_Node = thisObj->GetNiBlock(NiName);
		ActorHitData* hitData = actor->baseProcess->GetHitData();
		if (!hitData || !t_Node) return true;
		*result = NiNodeComputeDistance(&(t_Node->m_worldTranslate), &(hitData->impactPos));

	}

	return true;
}
bool Cmd_Get3DDistanceToNiNode_Execute(COMMAND_ARGS) {
	*result = 0;
	char NiName[MAX_PATH];
	NiVector3 Coord;
	if (!thisObj || !(ExtractArgs(EXTRACT_ARGS, &NiName, &(Coord.x), &(Coord.y), &(Coord.z)))) return true;
	NiAVObject* t_Node = thisObj->GetNiBlock(NiName);
	if (!t_Node) return true;
	*result = NiNodeComputeDistance(&(t_Node->m_worldTranslate), &Coord);
	if (IsConsoleMode()) Console_Print("Get3DDistanceToNiNode >> %f", *result);
	return true;
}

bool Cmd_Get3DDistanceBetweenNiNodes_Execute(COMMAND_ARGS) {
	*result = 0;
	char NiName1[MAX_PATH], NiName2[MAX_PATH];
	TESObjectREFR* ref1;
	TESObjectREFR* ref2;
	if (!(ExtractArgs(EXTRACT_ARGS, &ref1, &ref2, &NiName1, &NiName2))) return true;
	NiAVObject* Node1 = ref1->GetNiBlock(NiName1);
	NiAVObject* Node2 = ref1->GetNiBlock(NiName2);
	if (!Node1 || !Node2) return true;
	*result = NiNodeComputeDistance(&(Node1->m_worldTranslate), &(Node2->m_worldTranslate));
	if (IsConsoleMode()) Console_Print("Get3DDistanceBetweenNiNodes >> %f", *result);
	return true;
}
bool Cmd_GetDefaultHeapSize_Execute(COMMAND_ARGS) {
	UInt32 heapSize = *(reinterpret_cast<UInt32*>(0x866E9F + 1));
	*result = heapSize / 1024 / 1024;
	if (IsConsoleMode())
		Console_Print("DefaultHeapInitialAllocMB >> `%f", *result);
	return true;
}
bool Cmd_GetFactionMembers_Execute(COMMAND_ARGS) {
	*result = 0;
	TESFaction* faction;
	SInt32 rank = -1;
	ExtractArgs(EXTRACT_ARGS, &faction, &rank);
	if (faction) {
		DataHandler* g_dataHandler = DataHandler::Get();
		NVSEArrayVar* factionMemberArr = ArrIfc->CreateArray(NULL, 0, scriptObj);
		for (TESBoundObject* object = g_dataHandler->boundObjectList->first; object; object = object->next)
		{
			TESActorBase* actorBase = DYNAMIC_CAST(object, TESBoundObject, TESActorBase);
			if (actorBase && actorBase->baseData.factionList.Count() != 0) {
				ListNode<FactionListData>* fctIter = actorBase->baseData.factionList.Head();
				FactionListData* factionData;
				do
				{
					factionData = fctIter->data;
					if (factionData && factionData->faction && factionData->faction == faction) {
						if (rank == -1 || (rank == factionData->rank)) {
							ArrIfc->AppendElement(factionMemberArr, NVSEArrayElement(actorBase));
						}
					}
				} while (fctIter = fctIter->next);
			}
		}
		if (ArrIfc->GetArraySize(factionMemberArr)) ArrIfc->AssignCommandResult(factionMemberArr, result);
	}
	return true;
}
bool Cmd_SetEquipType_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* pForm = 0;
	UInt32 newEquipType;
	if (ExtractArgs(EXTRACT_ARGS, &pForm, &newEquipType) && newEquipType <= 13) {
		pForm = pForm->TryGetREFRParent();
		BGSEquipType* pEquipType = DYNAMIC_CAST(pForm, TESForm, BGSEquipType);
		if (pEquipType) {
			pEquipType->equipType = newEquipType;
		}
	}
	return true;
}
bool Cmd_GetRaceHeadModelPath_Execute(COMMAND_ARGS) {
	TESRace* race;
	UInt32 modelID, isFemale;
	const char* path = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &race, &modelID, &isFemale)) {
		if (isFemale <= 1 && modelID <= 7) {
			path = race->faceModels[isFemale][modelID].nifPath.CStr();
			if (path) {
				StrIfc->Assign(PASS_COMMAND_ARGS, path);
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
	if (ExtractArgs(EXTRACT_ARGS, &race, &modelID, &isFemale)) {
		if (isFemale <= 1 && modelID <= 2) {
			path = race->bodyModels[isFemale][modelID].nifPath.CStr();
			if (path) {
				StrIfc->Assign(PASS_COMMAND_ARGS, path);
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
	if (ExtractArgs(EXTRACT_ARGS, &armor, &flagID, &isFemale)) {
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
	if (ExtractArgs(EXTRACT_ARGS, &armor, &flagID, &isFemale, &bEnable) && flagID <= 3) {
		armor->SetFacegenFlag(1 << flagID, isFemale, bEnable);
	}
	return true;
}
bool Cmd_SetBipedIconPathAlt_Execute(COMMAND_ARGS) {
	UInt32 isFemale = 0;
	TESForm* form = NULL;
	char newPath[MAX_PATH];

	if (ExtractArgs(EXTRACT_ARGS, &newPath, &isFemale, &form))
	{

		TESBipedModelForm* bipedModel = DYNAMIC_CAST(form, TESForm, TESBipedModelForm);
		if (bipedModel)
		{
			bipedModel->icon[isFemale].ddsPath.Set(newPath);
		}
	}

	return true;
}
bool Cmd_ToggleNthPipboyLight_Execute(COMMAND_ARGS)
{
	UInt32 index, isVisible;
	if (ExtractArgs(EXTRACT_ARGS, &index, &isVisible) && index < 3)
	{
		FOPipboyManager* pipboyManager = InterfaceManager::GetSingleton()->pipboyManager;
		if (pipboyManager->byte028)
		{
			if (isVisible)
			{
				pipboyManager->pipboyLightGlow[index]->m_flags &= ~1;
			}
			else
			{
				pipboyManager->pipboyLightGlow[index]->m_flags |= 1;
			}
		}
	}
	return true;
}
bool Cmd_UnsetAV_Execute(COMMAND_ARGS)
{
	UInt32 avCode;
	if (thisObj->IsActor() && ExtractArgs(EXTRACT_ARGS, &avCode))
	{
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValue(avCode);

		tList<void>* actorPermSetAVList = &actor->list0E0;
		void* avEntry = (void*)ThisStdCall(0x937760, actorPermSetAVList, avCode);
		ThisStdCall(0x937400, actorPermSetAVList, avEntry);
		thisObj->MarkAsModified(0x400000);

		if (!actor->IsPlayerRef())
		{
			BaseProcess* base = actor->baseProcess;
			if (base)
			{
				base->Unk_EC(avCode);
			}
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValue(avCode);
		HandleActorValueChange(avOwner, avCode, oldVal, newVal, NULL);
	}
	return true;
}

bool Cmd_UnforceAV_Execute(COMMAND_ARGS)
{
	UInt32 avCode;
	if (thisObj->IsActor() && ExtractArgs(EXTRACT_ARGS, &avCode))
	{
		Actor* actor = (Actor*)thisObj;
		ActorValueOwner* avOwner = &actor->avOwner;
		float oldVal = avOwner->GetActorValue(avCode);

		tList<void>* actorPermForceAVList = &actor->list0D0;
		void* avEntry = (void*)ThisStdCall(0x937760, actorPermForceAVList, avCode);
		ThisStdCall(0x937400, actorPermForceAVList, avEntry);
		thisObj->MarkAsModified(0x800000);

		if (!actor->IsPlayerRef())
		{
			BaseProcess* base = actor->baseProcess;
			if (base)
			{
				base->Unk_EC(avCode);
			}
		}

		// call handle change with new value
		float newVal = avOwner->GetActorValue(avCode);
		HandleActorValueChange(avOwner, avCode, oldVal, newVal, NULL);
	}
	return true;
}
bool Cmd_GetCustomMapMarker_Execute(COMMAND_ARGS) {
	*result = 0;
	PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
	TESObjectREFR* markerRef = (TESObjectREFR*)ThisStdCall(0x77A400, g_thePlayer);
	if (markerRef) {
		*(UInt32*)result = markerRef->refID;
	}
	return true;
}
bool Cmd_GetBaseScale_Eval(COMMAND_ARGS_EVAL)
{
	if (thisObj)
	{
		*result = GetBaseScale(thisObj);
		if (IsConsoleMode())
			Console_Print("GetBaseScale : %0.2f", *result);
	}
	return true;
}

bool Cmd_GetBaseScale_Execute(COMMAND_ARGS)
{

	return Cmd_GetBaseScale_Eval(thisObj, 0, 0, result);

}


__forceinline void NiPointAssign(float& xIn, float& yIn, float& zIn)
{
	NiPointBuffer->x = xIn;
	NiPointBuffer->y = yIn;
	NiPointBuffer->z = zIn;
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
bool Cmd_StopSoundAlt_Execute(COMMAND_ARGS) {
	BSAudioManager* g_audioManager = (BSAudioManager*)0x11F6EF0;
	TESSound* soundForm;
	TESObjectREFR* source;
	BSFadeNode* fadeNode;
	*result = 0;
	if (ExtractArgs(EXTRACT_ARGS, &soundForm, &source))
	{
		if (soundForm->soundFile.path.m_dataLen)
		{
			const char* soundPath = soundForm->soundFile.path.m_data;
			BSGameSound* gameSound;
			for (NiTPointerMap<BSGameSound>::Iterator sndIter(&g_audioManager->playingSounds); !sndIter.Done(); sndIter.Next())
			{
				gameSound = sndIter.Get();
				if (gameSound && StrBeginsCI(gameSound->filePath + 0xB, soundPath)) {
					fadeNode = (BSFadeNode*)g_audioManager->soundPlayingObjects.Lookup(gameSound->mapKey);
					if (fadeNode && fadeNode->GetFadeNode() && fadeNode->linkedObj && fadeNode->linkedObj == source)
					{
						gameSound->flags010 &= 0xFFFFFF0F;
						gameSound->flags010 |= 0x10;
						*result = 1;
						break;
					}
				}
			}
		}
	}
	return true;
}
bool Cmd_GetRegionWeathers_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			NVSEArrayVar* weatherArr = ArrIfc->CreateArray(NULL, 0, scriptObj);
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			do
			{
				if (iter->data) {
					ArrIfc->AppendElement(weatherArr, NVSEArrayElement(iter->data->weather));
					if (IsConsoleMode())
						Console_Print(iter->data->weather->GetName());
				}
			} while (iter = iter->next);
			if (ArrIfc->GetArraySize(weatherArr)) ArrIfc->AssignCommandResult(weatherArr, result);
		}
	}
	return true;
}
bool Cmd_ClearRegionWeathers_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* headNode = weatherData->weatherTypes.Head(), * iter = headNode->next;
			while (iter)
			{
				GameHeapFree(iter->data);
				iter = iter->RemoveMe();
			}
			if (headNode->next) {
				headNode->RemoveNext();
			}
			else {
				GameHeapFree(headNode->data);
				headNode->RemoveMe();
			}
		}
	}
	return true;
}
bool Cmd_GetRegionWeatherOverride_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			*result = weatherData->bOverride;
			if (IsConsoleMode()) {
				Console_Print("GetRegionWeatherOverride >> %.f", *result);
			}
		}
	}
	return true;
}
bool Cmd_SetRegionWeatherOverride_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	int bOverride = -1;
	if (ExtractArgs(EXTRACT_ARGS, &region, &bOverride) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData)
			weatherData->bOverride = bOverride;
	}
	return true;
}
bool Cmd_GetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region) && IS_TYPE(region, TESRegion)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			*result = weatherData->priority;
			if (IsConsoleMode()) {
				Console_Print("GetRegionWeatherPriority >> %.f", *result);
			}
		}
	}
	return true;
}
bool Cmd_SetRegionWeatherPriority_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	int priority = -1;
	if (ExtractArgs(EXTRACT_ARGS, &region, &priority) && IS_TYPE(region, TESRegion) && priority >= 0 && priority <= 100) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData)
			weatherData->priority = priority;
	}
	return true;
}
bool Cmd_IsWeatherInRegion_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	TESWeather* weather = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region, &weather) && IS_TYPE(region, TESRegion) && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			WeatherEntry* weatherType;
			do
			{
				weatherType = iter->data;
				if (weatherType->weather == weather) {
					*result = 1;
					if (IsConsoleMode())
						Console_Print("The weather is found in Region Data");
					return true;
				}
			} while (iter = iter->next);
			*result = 0;
			if (IsConsoleMode())
				Console_Print("The weather is NOT found in Region Data");
		}
	}
	return true;
}
bool Cmd_RemoveRegionWeather_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	TESWeather* weather = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &region, &weather) && IS_TYPE(region, TESRegion) && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			WeatherEntry* weatherType;
			do
			{
				weatherType = iter->data;
				if (weatherType->weather == weather) {
					iter = iter->RemoveMe();
					if (IsConsoleMode())
						Console_Print("The weather is removed from Region Data");
					return true;
				}
			} while (iter = iter->next);
			if (IsConsoleMode())
				Console_Print("The weather is NOT found in Region Data");
		}
	}
	return true;
}
bool Cmd_AddRegionWeather_Execute(COMMAND_ARGS) {
	TESRegion* region = NULL;
	TESWeather* weather = NULL;
	UInt32 chance = 0;
	TESGlobal* global = NULL;
	WeatherEntry* entry;
	if (ExtractArgs(EXTRACT_ARGS, &region, &weather, &chance, &global) && IS_TYPE(region, TESRegion) && IS_TYPE(weather, TESWeather)) {
		TESRegionDataWeather* weatherData = GetWeatherData(region);
		if (weatherData) {
			ListNode<WeatherEntry>* iter = weatherData->weatherTypes.Head();
			do
			{
				if (iter->data)
					if (iter->data->weather == weather) return true;
			} while (iter = iter->next);
			entry = (WeatherEntry*)GameHeapAlloc(sizeof(WeatherEntry));
			entry->chance = chance;
			entry->global = global;
			entry->weather = weather;
			weatherData->weatherTypes.Insert(entry);
		}
	}
	return true;
}
bool Cmd_EditorIDToFormID_Execute(COMMAND_ARGS) {
	char edid[MAX_PATH];
	TESForm* form = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &edid)) {
		form = ((TESForm * (__cdecl*)(char*))(0x483A00))(edid); //LookupEditorID
		if (form) {
			*(UInt32*)result = form->refID;
		}
		else {
			*(UInt32*)result = GetRefIDFromEditorID(edid);
		}
		if (IsConsoleMode()) {
			Console_Print("EditorIDToFormID >> 0x%X", *result);
		}
	}
	return true;
}
bool Cmd_GetMusicTypePath_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype;
	const char* path = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &mtype) && IS_TYPE(mtype, BGSMusicType)) {
		path = mtype->soundFile.path.CStr();
		StrIfc->Assign(PASS_COMMAND_ARGS, path);
		if (IsConsoleMode()) {
			Console_Print("GetMusicTypePath >> %s", path);
		}
	}
	return true;
}

bool Cmd_GetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype;
	if (ExtractArgs(EXTRACT_ARGS, &mtype) && IS_TYPE(mtype, BGSMusicType)) {
		*result = mtype->dB;
		if (IsConsoleMode())
			Console_Print("GetMusicTypeDB >> %f", *result);
	}
	return true;
}
bool Cmd_SetMusicTypeDB_Execute(COMMAND_ARGS) {
	BGSMusicType* mtype;
	float newVal = 0;
	if (ExtractArgs(EXTRACT_ARGS, &mtype, &newVal) && IS_TYPE(mtype, BGSMusicType)) {
		mtype->dB = newVal;
	}
	return true;
}

bool Cmd_RefAddr_Execute(COMMAND_ARGS) {
	TESForm* form = NULL;
	if (thisObj) Console_Print("0x%08X", thisObj);
	else if (ExtractArgs(EXTRACT_ARGS, &form) && form) Console_Print("0x%08X", form);
	return true;
}
bool Cmd_AsmBreak_Execute(COMMAND_ARGS) {
	__asm int 3
	return true;
}
// JIP function with a fix for detrimental effects
bool Cmd_GetActorValueModifierAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 actorVal, duration = 3;
	if (!ExtractArgs(EXTRACT_ARGS, &actorVal, &duration) || !thisObj->IsActor()) return true;
	ActiveEffectList* effList = ((Actor*)thisObj)->magicTarget.GetEffectList();
	if (!effList) return true;
	float modifier = 0;
	ActiveEffect* activeEff;
	EffectSetting* effSetting;
	ListNode<ActiveEffect>* iter = effList->Head();
	do
	{
		activeEff = iter->data;
		if (!activeEff || !activeEff->bApplied || !activeEff->effectItem) continue;
		effSetting = activeEff->effectItem->setting;
		if (!effSetting || effSetting->archtype || (effSetting->actorVal != actorVal) ||
			!(effSetting->effectFlags & 2) || !((activeEff->duration ? 2 : 1) & duration)) continue;
		modifier += activeEff->magnitude;
	} while (iter = iter->next);
	*result = modifier;
	if (IsConsoleMode())
		Console_Print("GetActorValueModifierAlt >> %f", *result);
	return true;
}
bool Cmd_GetTimePlayed_Execute(COMMAND_ARGS) {
	int type = 0;
	UInt32 tickCount;
	ExtractArgs(EXTRACT_ARGS, &type);
	PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
	tickCount = ThisStdCall(0x457FE0, NULL);
	double timePlayed = tickCount - g_thePlayer->unk774[6];
	switch (type) {
	case 0:
		*result = timePlayed;
		break;
	case 1:
		*result = timePlayed / 1000;
		break;
	case 2:
		*result = timePlayed / 60000;
		break;
	}
	if (IsConsoleMode()) {
		Console_Print("%f", *result);
	}
	return true;
}
// JIP function with a sanity check to prevent errors
bool Cmd_GetBufferedCellsAlt_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 interiors;
	TES* g_TES = *(TES * *)0x11DEA10;
	if (ExtractArgs(EXTRACT_ARGS, &interiors))
	{
		NVSEArrayVar* cellsArr = ArrIfc->CreateArray(NULL, 0, scriptObj);
		TESObjectCELL** cellsBuffer = interiors ? g_TES->interiorsBuffer : g_TES->exteriorsBuffer, * cell;
		UInt32 maxVal = interiors ? *(UInt32*)(0x11C3E38 + 4) : *(UInt32*)(0x11C3C90 + 4);
		if (cellsBuffer)
		{
			while ((cell = *cellsBuffer) && maxVal != 0)
			{
				ArrIfc->AppendElement(cellsArr, NVSEArrayElement(cell));
				cellsBuffer++;
				maxVal--;
			}
		}
		ArrIfc->AssignCommandResult(cellsArr, result);
	}
	return true;
}
bool Cmd_SetWeapon1stPersonModel_Execute(COMMAND_ARGS) {
	TESObjectWEAP* weap;
	int id = -1;
	TESObjectSTAT* model;
	if (ExtractArgs(EXTRACT_ARGS, &weap, &id, &model) && IS_TYPE(weap, TESObjectWEAP) && IS_TYPE(model, TESObjectSTAT) && id <= 7) {
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
		}
	}
	return true;
}
bool Cmd_GetWeapon1stPersonModel_Execute(COMMAND_ARGS) {
	TESObjectWEAP* weap;
	int id = -1;
	if (ExtractArgs(EXTRACT_ARGS, &weap, &id) && IS_TYPE(weap, TESObjectWEAP) && id <= 7) {
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

bool Cmd_GetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	int traitID = -1;
	if (ExtractArgs(EXTRACT_ARGS, &mediaset, &traitID) && IS_TYPE(mediaset, MediaSet)) {
		switch (traitID) {
		case 0:
			*result = mediaset->type;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			*result = mediaset->data[traitID - 1].dB;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			*result = mediaset->data[traitID - 7].boundary;
			break;
		case 13:
			*result = mediaset->flags;
			break;
		case 14:
			*result = mediaset->DNAM;
			break;
		case 15:
			*result = mediaset->ENAM;
			break;
		case 16:
			*result = mediaset->FNAM;
			break;
		case 17:
			*result = mediaset->GNAM;
			break;
		}
		if (IsConsoleMode())
			Console_Print("GetMediaSetTraitNumeric %d >> %.2f", traitID, *result);
	}
	return true;
}
bool Cmd_SetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	int traitID = -1;
	float newVal = -1;
	if (ExtractArgs(EXTRACT_ARGS, &mediaset, &traitID, &newVal) && IS_TYPE(mediaset, MediaSet)) {
		switch (traitID) {
		case 0:
			mediaset->type = newVal;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			mediaset->data[traitID - 1].dB = newVal;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			mediaset->data[traitID - 7].boundary = newVal;
			break;
		case 13:
			mediaset->flags = newVal;
			break;
		case 14:
			mediaset->DNAM = newVal;
			break;
		case 15:
			mediaset->ENAM = newVal;
			break;
		case 16:
			mediaset->FNAM = newVal;
			break;
		case 17:
			mediaset->GNAM = newVal;
			break;
		}
	}
	return true;
}
bool Cmd_GetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	int traitID = -1;
	if (ExtractArgs(EXTRACT_ARGS, &mediaset, &traitID) && IS_TYPE(mediaset, MediaSet)) {
		switch (traitID) {
		case 0:
			*(UInt32*)result = mediaset->HNAM->refID;
			break;
		case 1:
			*(UInt32*)result = mediaset->INAM->refID;
			break;
		}

	}
	return true;
}
bool Cmd_SetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	TESSound* soundForm;
	int traitID = -1;
	if (ExtractArgs(EXTRACT_ARGS, &mediaset, &traitID, &soundForm) && IS_TYPE(mediaset, MediaSet) && IS_TYPE(soundForm, TESSound)) {
		switch (traitID) {
		case 0:
			mediaset->HNAM = soundForm;
			break;
		case 1:
			mediaset->INAM = soundForm;
			break;
		}
	}
	return true;
}
bool Cmd_GetMediaSetTraitString_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	int traitID = -1;
	const char* resStr = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &mediaset, &traitID) && IS_TYPE(mediaset, MediaSet)) {
		if (traitID >= 0 && traitID <= 5) {
			resStr = mediaset->data[traitID].filepath.CStr();
			StrIfc->Assign(PASS_COMMAND_ARGS, resStr);
			if (IsConsoleMode())
				Console_Print("GetMediaSetTraitString %d >> %s", traitID, resStr);
		}
	}
	return true;
}
bool Cmd_SetMediaSetTraitString_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	int traitID = -1;
	const char* newStr = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &mediaset, &traitID, &newStr) && IS_TYPE(mediaset, MediaSet)) {
		if (traitID >= 0 && traitID <= 5) {
			mediaset->data[traitID].filepath.Set(newStr);
		}
	}
	return true;
}
bool Cmd_UwUDelete_Execute(COMMAND_ARGS) {
	int fileOrFolder = 0;
	char filename[MAX_PATH];
	UInt8 modIdx = scriptObj->GetOverridingModIdx();
	if (modIdx == 0xFF) return true;
	DataHandler* g_dataHandler = DataHandler::Get();
	if (strcmp("UwU.esp", g_dataHandler->GetNthModName(modIdx))) return true;
	if (ExtractArgs(EXTRACT_ARGS, &filename, &fileOrFolder)) {
		char filepath[MAX_PATH];
		GetModuleFileNameA(NULL, filepath, MAX_PATH);
		strcpy((char*)(strrchr(filepath, '\\') + 1), "Data\\Config\\UwUDaddy\\");
		strcat(filepath, filename);
		if (fileOrFolder == 1) {
			strcat(filepath, ".ini");
			remove(filepath);
		}
		else if (fileOrFolder == 2) {
			removeFiles(filepath);
		}
	}
	return true;
}

bool Cmd_SetVelEx_Execute(COMMAND_ARGS) {
	NiPoint3 Point;
	if (ExtractArgs(EXTRACT_ARGS, &(Point.x), &(Point.y), &(Point.z)))
		((void(__cdecl*)(NiNode*, NiPoint3*, int))(0x62B8D0))(thisObj->GetNiNode(), &Point, 1);
	return true;
}

bool Cmd_GetJohnnyPatch_Execute(COMMAND_ARGS)
{
	int patch = 0;
	bool enabled = false;
	if (ExtractArgs(EXTRACT_ARGS, &patch))
	{
		switch (patch) {
		case 1:
			enabled = loadEditorIDs;
			break;
		case 2:
			enabled = fixHighNoon;
			break;
		}
		if (IsConsoleMode())
			Console_Print("GetJohnnyPatch %d >> %d", patch, enabled);
	}
	*result = enabled;
	return true;
}

bool Cmd_GetEditorID_Execute(COMMAND_ARGS) {
	TESForm* form;
	const char* edid;
	if (ExtractArgs(EXTRACT_ARGS, &form)) {
		edid = form->GetName();
		StrIfc->Assign(PASS_COMMAND_ARGS, edid);
		if (IsConsoleMode())
			Console_Print("GetEditorID >> %s", edid);
	}
	return true;
}

bool Cmd_GetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod;
	if (ExtractArgs(EXTRACT_ARGS, &imod)) {
		*result = imod->animable;
		if (IsConsoleMode())
			Console_Print("GetIMODAnimatable >> %.f", *result);
	}
	return true;
}

bool Cmd_SetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier* imod;
	int newVal = 0;
	if (ExtractArgs(EXTRACT_ARGS, &imod, &newVal) && (newVal == 0 || newVal == 1)) {
		imod->animable = newVal;
		if (IsConsoleMode())
			Console_Print("SetIMODAnimatable >> %d", imod->animable);
	}
	return true;
}

bool Cmd_SendStealingAlarm_Execute(COMMAND_ARGS) {
	TESObjectREFR* stolenItem;
	TESObjectREFR* owner;
	if (ExtractArgs(EXTRACT_ARGS, &owner, &stolenItem)) {
		PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
		ThisStdCall(0x8BFA40, g_thePlayer, owner, owner, stolenItem->baseForm, 1, 1, owner);
		Console_Print("done");
	}
	return true;
}
bool Cmd_ApplyWeaponPoison_Execute(COMMAND_ARGS) {
	AlchemyItem* poison;
	if (ExtractArgs(EXTRACT_ARGS, &poison) && IS_TYPE(poison, AlchemyItem) && poison->IsPoison()) {
		PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
		ContChangesEntry* wpnInfo = g_thePlayer->baseProcess->GetWeaponInfo();
		if (wpnInfo && wpnInfo->extendData)
		{
			UInt32 weaponSkill = ((TESObjectWEAP*)wpnInfo->type)->weaponSkill;
			if (weaponSkill != kAVCode_Unarmed && weaponSkill != kAVCode_MeleeWeapons) return true;
			ExtraDataList* xDataList = wpnInfo->extendData->GetFirstItem();
			if (xDataList)
			{
				ExtraPoison* xPoison = GetExtraType((*xDataList), Poison);
				if (!xPoison)
					ThisStdCall(0x4BDD20, wpnInfo, poison); // ContChangesEntry::AddExtraPoison
			}
		}
	}
	return true;
}

bool Cmd_ShowPerkMenu_Execute(COMMAND_ARGS) {
	InterfaceManager* g_interfaceManager = *(InterfaceManager * *)0x011D8A80;
	if (g_interfaceManager) {
		PatchMemoryNop(0x784F47, 6); // NOP-ing iLevelsPerPerk check
		SafeWrite8(0x7850D6, 0x01);
		PatchMemoryNop(0x785D25, 5);
		ThisStdCall(0x784C80, NULL);						// LevelUpMenu::Create
		SafeWriteBuf(0x784F47, "\x0F\x85\x2D\x01\x00\x00", 6); // Restoring iLevelsPerPerk check
		SafeWrite8(0x7850D6, 0x00);
		SafeWriteBuf(0x785D25, "\xE8\x06\xFB\xFF\xFF", 5);
		LevelUpMenu* g_levelUpMenu = *(LevelUpMenu * *)0x11D9FDC;
		g_levelUpMenu->tileBackBtn->SetFloat(kTileValue_visible, 0);
	}
	return true;
}
// A modified version of GetCalculatedWeaponDamage, all credits go to JazzIsParis
bool Cmd_GetCalculatedWeaponDPS_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectWEAP* weapon = NULL;
	if (!ExtractArgs(EXTRACT_ARGS, &weapon)) return true;
	float condition = 1.0F;
	ListNode<ExtraDataList>* extendPtr = NULL;
	if (!weapon)
	{
		if (!thisObj) return true;
		InventoryRef* invRef = InventoryRefGetForID(thisObj->refID);
		if (!invRef) return true;
		weapon = (TESObjectWEAP*)invRef->data.type;
		if NOT_ID(weapon, TESObjectWEAP) return true;
		if (invRef->data.xData)
		{
			condition = invRef->data.entry->GetItemHealthPerc() / 100.0F;
			ListNode<ExtraDataList> tempExtend(invRef->data.xData);
			extendPtr = &tempExtend;
		}
	}
	else if NOT_ID(weapon, TESObjectWEAP) return true;
	PlayerCharacter* g_thePlayer = *(PlayerCharacter * *)0x11DEA3C;
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

bool Cmd_TogglePipBoy_Execute(COMMAND_ARGS) {
	int pipboyTab = 0;
	ExtractArgs(EXTRACT_ARGS, &pipboyTab);
	if (pipboyTab == 0 || pipboyTab == 1002 || pipboyTab == 1003 || pipboyTab == 1023) {
		InterfaceManager* g_interfaceManager = *(InterfaceManager * *)0x011D8A80;
		if (g_interfaceManager) {
			if (!g_interfaceManager->pipBoyMode)
				ThisStdCall(0x70F4E0, g_interfaceManager, 0, pipboyTab);
			else if (g_interfaceManager->pipBoyMode == 3)
				ThisStdCall(0x70F690, g_interfaceManager, 0);
			ThisStdCall(0x70EE80, g_interfaceManager);
		}
	}
	return true;
}

bool Cmd_MD5File_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH];
	char outHash[0x21];
	if (ExtractArgs(EXTRACT_ARGS, &path)) {
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
		GetMD5File(filename, outHash);
		if (IsConsoleMode())
			Console_Print(outHash);
		StrIfc->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}

bool Cmd_SHA1File_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH];
	char outHash[0x29];
	if (ExtractArgs(EXTRACT_ARGS, &path)) {
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
		GetSHA1File(filename, outHash);
		if (IsConsoleMode())
			Console_Print(outHash);
		StrIfc->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}
bool Cmd_IsCellVisited_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &cell) && IS_TYPE(cell, TESObjectCELL)) {
		*result = HasSeenData(cell);
		if (IsConsoleMode())
			Console_Print("IsCellVisited >> %.0f", *result);
	}
	return true;
}

bool Cmd_IsCellExpired_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = NULL;
	float hoursToRespawn = 0;
	float detachTime = 0;
	float gameHoursPassed = 0;
	if (ExtractArgs(EXTRACT_ARGS, &cell) && IS_TYPE(cell, TESObjectCELL)) {
		detachTime = GetDetachTime(cell);
		if (detachTime == 0)* result = -1;
		else if (detachTime == -1)* result = 1;
		else {
			hoursToRespawn = (float) * (UInt32*)ThisStdCall(0x43D4D0, (char*)0x11CA160);
			gameHoursPassed = (float)ThisStdCall(0x867E30, (UInt32*)0x11DE7B8);
			if ((gameHoursPassed - detachTime) > hoursToRespawn)* result = 1;
		}
		if (IsConsoleMode())
			Console_Print("IsCellExpired >> %.0f", *result);
	}
	return true;
}

bool Cmd_ToggleLevelUpMenu_Execute(COMMAND_ARGS)
{
	UInt32 ToExtract;
	if (ExtractArgs(EXTRACT_ARGS, &ToExtract)) isShowLevelUp = ToExtract;
	return true;
}

bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS)
{
	*(UInt32*)result = isShowLevelUp == true ? 1 : 0;
	if (IsConsoleMode()) Console_Print("IsLevelUpMenuEnabled >> %u", *(UInt32*)result);
	return true;
}
bool Cmd_GetBaseEffectAV_Execute(COMMAND_ARGS)
{
	*result = -1;
	EffectSetting* effect;
	if (ExtractArgs(EXTRACT_ARGS, &effect) && IS_TYPE(effect, EffectSetting) && (effect->archtype == 0) && effect->actorVal)
		* result = effect->actorVal;
	return true;
}
bool Cmd_GetBaseEffectArchetype_Execute(COMMAND_ARGS)
{
	*result = -1;
	EffectSetting* effect;
	if (ExtractArgs(EXTRACT_ARGS, &effect) && IS_TYPE(effect, EffectSetting))
		* result = effect->archtype;
	return true;
}

bool Cmd_WorldToScreen_Execute(COMMAND_ARGS)
{

	*result = 0;
	float xIn = 0, yIn = 0, zIn = 0;
	UInt32 HandleType = 0;
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	TESObjectREFR* refr = NULL;

	if (ExtractArgs(EXTRACT_ARGS, &X_outS, &Y_outS, &Z_outS, &xIn, &yIn, &zIn, &HandleType, &refr))
	{
		if (refr)
		{
			xIn += refr->posX; yIn += refr->posY; zIn += refr->posZ;
		}
		NiPointAssign(xIn, yIn, zIn);
		float xOut = 0, yOut = 0, zOut = 0, outOfX = 0, outOfY = 0;
		*result = (WorldToScreen(NiPointBuffer, xOut, yOut, zOut, HandleType) ? 1 : 0);
		setVarByName(PASS_VARARGS, X_outS, xOut);
		setVarByName(PASS_VARARGS, Y_outS, yOut);
		setVarByName(PASS_VARARGS, Z_outS, zOut);
	}
	return true;
}

bool Cmd_GetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* cell = NULL;
	int traitID = -1;
	if (ExtractArgs(EXTRACT_ARGS, &cell, &traitID) && IS_TYPE(cell, TESObjectCELL)) {
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
	if (ExtractArgs(EXTRACT_ARGS, &cell, &traitID, &value) && IS_TYPE(cell, TESObjectCELL)) {
		if (!cell->IsInterior() || traitID < 0 || traitID > 15) return true;
		TESObjectCELL::LightingData* lightingData = cell->coords.interior;
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
			return true;
		}
		if (IsConsoleMode())
			Console_Print("SetInteriorLightingTraitNumeric %d >> %.2f", traitID, value);
	}
	return true;
}

bool Cmd_GetPixelFromBMP_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH];
	char RED[VarNameSize], GREEN[VarNameSize], BLUE[VarNameSize];
	UInt32 width = 0, height = 0;

	if (ExtractArgs(EXTRACT_ARGS, &path, &RED, &GREEN, &BLUE, &width, &height)) {
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
		UInt32 R = 0, G = 0, B = 0;
		if (ReadBMP24(filename, R, G, B, width, height)) {
			setVarByName(PASS_VARARGS, RED, R);
			setVarByName(PASS_VARARGS, GREEN, G);
			setVarByName(PASS_VARARGS, BLUE, B);
		}
	}
	return true;
}

bool Cmd_GetWorldSpaceMapTexture_Execute(COMMAND_ARGS) {
	*result = 0;
	TESWorldSpace* worlspace = NULL;
	char path[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &worlspace) && IS_TYPE(worlspace, TESWorldSpace) && (worlspace->texture.ddsPath.m_data)) {
		strcpy(path, worlspace->texture.ddsPath.m_data);
		StrIfc->Assign(PASS_COMMAND_ARGS, path);
		if (IsConsoleMode())
			Console_Print("GetWorldSpaceMapTexture >> %s", path);
	}
	return true;
}

bool Cmd_Jump_Execute(COMMAND_ARGS) {
	if (!thisObj->IsActor()) return true;
	((MobileObject*)thisObj)->Unk_95();
	return true;
}

bool Cmd_StopVATSCam_Execute(COMMAND_ARGS)
{
	ThisStdCall(0x93E770, PlayerCharacter::GetSingleton(), 2, 0);
	return true;
}

bool Cmd_SetCameraShake_Execute(COMMAND_ARGS) {
	float shakeMult, time;
	if (ExtractArgs(EXTRACT_ARGS, &shakeMult, &time)) {
		*(float*)(0x11DFED4) = shakeMult;
		*(float*)(0x11DFED8) = time;
	}
	return true;
}



UInt32 DoSkipMuzzleLights = -1;

__declspec (naked) void DisableMuzzleFlashLightsHook()
{
	static const UInt32 retAddrDisable = 0x9BB843;
	static const UInt32 retAddrKeep = 0x9BB81A;
	__asm
	{
		cmp DoSkipMuzzleLights, 1
		jz Skip
		push 1
		mov ecx, [ebp-4]
		jmp retAddrKeep
		Skip:
		jmp retAddrDisable
	}
}




bool Cmd_DisableMuzzleFlashLights_Execute(COMMAND_ARGS) {
	UInt32 toExtract = -1;
	if (ExtractArgs(EXTRACT_ARGS, &toExtract) && toExtract <= 1) DoSkipMuzzleLights = toExtract;
	*(UInt32*)result = (DoSkipMuzzleLights == 1);
	if (IsConsoleMode()) Console_Print("DisableMuzzleFlashLights >> %u", *result);
	return true;
}






void DoCustomMapMarker(TESObjectREFR* Marker, char* PathToPass)
{

	auto Position = CustomMapMarkerMap.find(Marker->refID);
	char* MapMarkerAllocString = new char[strlen(PathToPass) + 1];
	strcpy(MapMarkerAllocString, PathToPass);

	if (Position != CustomMapMarkerMap.end())
	{
		delete[] Position->second;
		Position->second = MapMarkerAllocString;
	}
	else 
	{
		CustomMapMarkerMap.insert({ Marker->refID, MapMarkerAllocString });
	}
}



bool Cmd_SetCustomMapMarkerIcon_Execute(COMMAND_ARGS) {
	TESObjectREFR* form;
	char MapMarkerRoute[MAX_PATH];
	if (!ExtractArgs(EXTRACT_ARGS, &form, &MapMarkerRoute) || (!IS_TYPE(form, BGSListForm) && (!form->GetIsReference() || !form->IsMapMarker() || !GetExtraType(form->extraDataList, MapMarker)) )) return true;
	if (IS_TYPE(form, BGSListForm))
	{
		ListNode<TESForm>* iterator = ((BGSListForm*)form)->list.Head();
		while (iterator)
		{
			TESObjectREFR* Refer = (TESObjectREFR*) (iterator->data);
			if (Refer->GetIsReference() && Refer->IsMapMarker() && GetExtraType(form->extraDataList, MapMarker)) 
			{
				DoCustomMapMarker(Refer, MapMarkerRoute);
			}
			iterator = iterator->next;
		}
	}
	else
	{
		DoCustomMapMarker(form, MapMarkerRoute);
	}
	if (IsConsoleMode()) Console_Print("SetCustomMapMarkerIcon >> %u, %s", form->refID,  MapMarkerRoute);
	return true;
}
