#pragma once
// Utility or miscellaneous functions
DEFINE_COMMAND_PLUGIN(GetEditorID, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetJohnnyPatch, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetTimePlayed, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(AsmBreak, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(RefAddr, , 0, 1, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(EditorIDToFormID, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetDefaultHeapSize, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetLinearVelocity, , 1, 4, kParamsJohnnyFourStrings);
DEFINE_COMMAND_PLUGIN(IsLevelUpMenuEnabled, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetPipBoyMode, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetFormOverrideIndex, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetSequenceAnimGroup, , 0, 1, kParams_OneInt);

bool Cmd_GetSequenceAnimGroup_Execute(COMMAND_ARGS)
{
	*result = -1;
	UInt32 sequenceID;
	if (ExtractArgs(EXTRACT_ARGS, &sequenceID) && sequenceID < 8)
	{
		if (auto animData = thisObj->GetAnimData())
		{
			if (auto sequence = animData->animSequence[sequenceID])
			{
				UInt16 groupID = animData->groupIDs[sequenceID] & 0xFF;
				*result = groupID;
			}
		}
	}

	return true;
}
bool Cmd_GetFormOverrideIndex_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* form;
	if (scriptObj && ExtractArgs(EXTRACT_ARGS, &form))
	{
		UInt8 overriding = form->GetOverridingModIdx();
		*result = ((overriding > scriptObj->modIndex) ? overriding : 0);
		if (IsConsoleMode) Console_Print("GetFormOverrideIndex >> %.f", *result);
	}
	return true;
}
bool Cmd_GetPipBoyMode_Execute(COMMAND_ARGS) {
	*result = 0;
	InterfaceManager* g_interfaceManager = *(InterfaceManager**)0x011D8A80;
	if (g_interfaceManager) *result = g_interfaceManager->pipBoyMode;
	if (IsConsoleMode()) Console_Print("GetPipBoyMode >> %.2f", *result);
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

bool Cmd_GetDefaultHeapSize_Execute(COMMAND_ARGS) {
	UInt32 heapSize = *(reinterpret_cast<UInt32*>(0x866E9F + 1));
	*result = heapSize / 1024 / 1024;
	if (IsConsoleMode())
		Console_Print("DefaultHeapInitialAllocMB >> `%f", *result);
	return true;
}

bool Cmd_EditorIDToFormID_Execute(COMMAND_ARGS) {
	char edid[MAX_PATH];
	TESForm* form = NULL;
	*result = 0;
	if (ExtractArgs(EXTRACT_ARGS, &edid)) {
		form = ((TESForm * (__cdecl*)(char*))(0x483A00))(edid); //LookupEditorID
		if (form) {
			*(UInt32*)result = form->refID;
		}
		if (IsConsoleMode()) {
			Console_Print("EditorIDToFormID >> 0x%X", *result);
		}
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

bool Cmd_GetTimePlayed_Execute(COMMAND_ARGS) {
	int type = 0;
	UInt32 tickCount;
	ExtractArgs(EXTRACT_ARGS, &type);
	PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
	tickCount = ThisStdCall<UInt32>(0x457FE0, NULL);
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
bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS)
{
	*result = isShowLevelUp;
	if (IsConsoleMode()) Console_Print("IsLevelUpMenuEnabled >> %.f", *result);
	return true;
}