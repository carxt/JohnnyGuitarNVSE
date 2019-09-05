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
#include "internal/decoding.h"

__forceinline void NiPointAssign(float& xIn, float& yIn, float& zIn)
{
	NiPointBuffer->x = xIn;
	NiPointBuffer->y = yIn;
	NiPointBuffer->z = zIn;
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
		strcpy((char *)(strrchr(filepath, '\\') + 1), "Data\\Config\\UwUDaddy\\");
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
		}
		if (IsConsoleMode())
			Console_Print("GetJohnnyPatch %d >> %d", patch, enabled);
	}
	*result = enabled;
	return true;
}

bool Cmd_GetEditorID_Execute(COMMAND_ARGS) {
	TESForm *form;
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
	TESImageSpaceModifier *imod;
	if (ExtractArgs(EXTRACT_ARGS, &imod)) {
		*result = imod->animable;
		if (IsConsoleMode())
			Console_Print("GetIMODAnimatable >> %.f", *result);
	}
	return true;
}

bool Cmd_SetIMODAnimatable_Execute(COMMAND_ARGS) {
	TESImageSpaceModifier *imod;
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
	AlchemyItem *poison;
	if (ExtractArgs(EXTRACT_ARGS, &poison) && IS_TYPE(poison, AlchemyItem) && poison->IsPoison()) {
		PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
		ContChangesEntry *wpnInfo = g_thePlayer->baseProcess->GetWeaponInfo();
		if (wpnInfo && wpnInfo->extendData)
		{
			UInt32 weaponSkill = ((TESObjectWEAP*)wpnInfo->type)->weaponSkill;
			if (weaponSkill != kAVCode_Unarmed && weaponSkill != kAVCode_MeleeWeapons) return true;
			ExtraDataList *xDataList = wpnInfo->extendData->GetFirstItem();
			if (xDataList)
			{
				ExtraPoison *xPoison = GetExtraType((*xDataList), Poison);
				if (!xPoison)
					ThisStdCall(0x4BDD20, wpnInfo, poison); // ContChangesEntry::AddExtraPoison
			}
		}
	}
	return true;
}

bool Cmd_ShowPerkMenu_Execute(COMMAND_ARGS) {
	InterfaceManager* g_interfaceManager = *(InterfaceManager **)0x011D8A80;
	if (g_interfaceManager) {
		PatchMemoryNop(0x784F47, 6); // NOP-ing iLevelsPerPerk check
		SafeWrite8(0x7850D6, 0x01);
		PatchMemoryNop(0x785D25, 5);
		ThisStdCall(0x784C80, NULL);						// LevelUpMenu::Create
		SafeWriteBuf(0x784F47, "\x0F\x85\x2D\x01\x00\x00", 6); // Restoring iLevelsPerPerk check
		SafeWrite8(0x7850D6, 0x00);
		SafeWriteBuf(0x785D25, "\xE8\x06\xFB\xFF\xFF", 5);
		LevelUpMenu* g_levelUpMenu = *(LevelUpMenu**)0x11D9FDC;
		g_levelUpMenu->tileBackBtn->SetFloat(kTileValue_visible, 0);
	}
	return true;
} 
// A modified version of GetCalculatedWeaponDamage, all credits go to JazzIsParis
bool Cmd_GetCalculatedWeaponDPS_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectWEAP *weapon = NULL;
	if (!ExtractArgs(EXTRACT_ARGS, &weapon)) return true;
	float condition = 1.0F;
	ListNode<ExtraDataList> *extendPtr = NULL;
	if (!weapon)
	{
		if (!thisObj) return true;
		InventoryRef *invRef = InventoryRefGetForID(thisObj->refID);
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
	PlayerCharacter* g_thePlayer = *(PlayerCharacter**)0x11DEA3C;
	MiddleHighProcess *midHiProc = (MiddleHighProcess*)g_thePlayer->baseProcess;
	ContChangesEntry *weaponInfo = midHiProc->weaponInfo;
	TESForm *ammo = NULL;
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
		InterfaceManager* g_interfaceManager = *(InterfaceManager **)0x011D8A80;
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
		strcpy((char *)(strrchr(filename, '\\') + 1), path);
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
		strcpy((char *)(strrchr(filename, '\\') + 1), path);
		GetSHA1File(filename, outHash);
		if (IsConsoleMode())
			Console_Print(outHash);
		StrIfc->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}
bool Cmd_IsCellVisited_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL *cell = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &cell) && IS_TYPE(cell, TESObjectCELL)) {
		*result = HasSeenData(cell);
		if (IsConsoleMode())
			Console_Print("IsCellVisited >> %.0f", *result);
	}
	return true;
}

bool Cmd_IsCellExpired_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL *cell = NULL;
	float hoursToRespawn = 0;
	float detachTime = 0;
	float gameHoursPassed = 0;
		if (ExtractArgs(EXTRACT_ARGS, &cell) && IS_TYPE(cell, TESObjectCELL)) {
		detachTime = GetDetachTime(cell);
		if (detachTime == 0) *result = -1;
		else if (detachTime == -1) *result = 1;
		else { 
			hoursToRespawn = (float)*(UInt32*)ThisStdCall(0x43D4D0, (char*)0x11CA160);
			gameHoursPassed = (float)ThisStdCall(0x867E30, (UInt32*)0x11DE7B8);
			if ((gameHoursPassed - detachTime) > hoursToRespawn) *result = 1;
		}
		if (IsConsoleMode())
			Console_Print("IsCellExpired >> %.0f", *result);
	}
	return true; 
}

bool Cmd_ToggleLevelUpMenu_Execute(COMMAND_ARGS)
{
	ExtractArgs(EXTRACT_ARGS, &isShowLevelUp);
	return true;
}

bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS)
{
	*result = isShowLevelUp;
	return true;
}
bool Cmd_GetBaseEffectAV_Execute(COMMAND_ARGS)
{
	*result = -1;
	EffectSetting *effect;
	if (ExtractArgs(EXTRACT_ARGS, &effect) && IS_TYPE(effect, EffectSetting) && (effect->archtype == 0) && effect->actorVal)
		*result = effect->actorVal;
	return true;
}
bool Cmd_GetBaseEffectArchetype_Execute(COMMAND_ARGS)
{
	*result = -1;
	EffectSetting *effect;
	if (ExtractArgs(EXTRACT_ARGS, &effect) && IS_TYPE(effect, EffectSetting))
		*result = effect->archtype;
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
	TESObjectCELL *cell = NULL;
	int traitID = -1;
	if (ExtractArgs(EXTRACT_ARGS, &cell, &traitID) && IS_TYPE(cell, TESObjectCELL)) {
		if (!cell->IsInterior() || traitID < 0 || traitID > 15) return false;
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
			return false;
		}
		if (IsConsoleMode())
			Console_Print("GetInteriorLightingTraitNumeric %d >> %.2f", traitID, *result);
	}
	return true;
}
bool Cmd_SetInteriorLightingTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL *cell = NULL;
	int traitID = -1;
	float value = -1;
	if (ExtractArgs(EXTRACT_ARGS, &cell, &traitID, &value) && IS_TYPE(cell, TESObjectCELL)) {
		if (!cell->IsInterior() || traitID < 0 || traitID > 15) return false;
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
			return false;
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
		if (ReadBMP24(filename, R, G, B, width, height));
		setVarByName(PASS_VARARGS, RED, R);
		setVarByName(PASS_VARARGS, GREEN, G);
		setVarByName(PASS_VARARGS, BLUE, B);
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
