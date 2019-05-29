#pragma once
#define VarNameSize 64
DEFINE_COMMAND_PLUGIN(WorldToScreen, , 0, 8, kParamsProjectionArgs);
DEFINE_COMMAND_PLUGIN(ToggleLevelUpMenu, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(IsLevelUpMenuEnabled, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetBaseEffectAV, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetBaseEffectArchetype, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(IsCellVisited, , 0, 1, kParams_OneForm);

__forceinline void NiPointAssign(float& xIn, float& yIn, float& zIn)
{
	NiPointBuffer->x = xIn;
	NiPointBuffer->y = yIn;
	NiPointBuffer->z = zIn;
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