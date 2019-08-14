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
DEFINE_COMMAND_PLUGIN(GetPixelFromBMP, , 0, 6, kParamsBMPArgs);
DEFINE_COMMAND_PLUGIN(GetWorldSpaceMapTexture, , 0, 1, kParams_OneForm);

// DEFINE_COMMAND_PLUGIN(ShowPerkMenu, , 0, 0, NULL); TBD
__forceinline void NiPointAssign(float& xIn, float& yIn, float& zIn)
{
	NiPointBuffer->x = xIn;
	NiPointBuffer->y = yIn;
	NiPointBuffer->z = zIn;
}
/*bool Cmd_ShowPerkMenu_Execute(COMMAND_ARGS) {
	InterfaceManager* g_interfaceManager = *(InterfaceManager **)0x011D8A80;
	if (g_interfaceManager) {
		ThisStdCall(0x784C80, NULL);
		LevelUpMenu* g_levelUpMenu = *(LevelUpMenu **)0x11D9FDC;
		if (g_levelUpMenu)
			g_levelUpMenu->isPerkMenu = 0;
			Tile::SetFloat(g_levelUpMenu->id)
		ThisStdCall(0x785830, g_levelUpMenu, (SInt32)1);
	}
	return true;
} */

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
