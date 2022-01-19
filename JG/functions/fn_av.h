#pragma once
// Alternative actor value functions to allow using numeric AV IDs
// Deprecated, xNVSE allows using AV codes with regular functions in parentheses
DEFINE_COMMAND_ALT_PLUGIN(GetActorValueAlt, GetAVAlt, , 1, 1, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetActorValueAlt, SetAVAlt, , 1, 2, kParams_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(GetBaseActorValueAlt, GetBaseAVAlt, , 1, 1, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(ForceActorValueAlt, ForceAVAlt, , 1, 2, kParams_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(DamageActorValueAlt, DamageAVAlt, , 1, 2, kParams_OneInt_OneFloat);
DEFINE_COMMAND_ALT_PLUGIN(RestoreActorValueAlt, RestoreAVAlt, , 1, 2, kParams_OneInt_OneFloat);
DEFINE_COMMAND_ALT_PLUGIN(ModActorValueAlt, ModAVAlt, , 1, 2, kParams_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(GetThresholdedActorValue, GetThresholdAV, , 1, 1, kParams_OneActorValue);
bool(__cdecl* Cmd_GetAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BD8A0;
bool(__cdecl* Cmd_SetAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BDCD0;
bool(__cdecl* Cmd_ForceAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BE190;
bool(__cdecl* Cmd_ModAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BDE40;
bool(__cdecl* Cmd_DamageAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BDF20;
bool(__cdecl* Cmd_RestoreAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BE080;
bool(__cdecl* Cmd_GetBaseAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BE6E0;

bool Cmd_GetThresholdedActorValue_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 avCode;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &avCode) && thisObj->IsActor()) {
		Actor* actor = (Actor*)thisObj;
		*result = ThisStdCall<double>(0x66EF50, &actor->avOwner, avCode);
		if (IsConsoleMode()) Console_Print("GetThresholdAV %d >> %.2f", avCode, *result);
	}
	return true;
}
bool Cmd_GetActorValueAlt_Execute(COMMAND_ARGS) {
	return Cmd_GetAV(PASS_COMMAND_ARGS);
}

bool Cmd_SetActorValueAlt_Execute(COMMAND_ARGS) {
	return Cmd_SetAV(PASS_COMMAND_ARGS);
}

bool Cmd_ForceActorValueAlt_Execute(COMMAND_ARGS) {
	return Cmd_ForceAV(PASS_COMMAND_ARGS);
}

bool Cmd_DamageActorValueAlt_Execute(COMMAND_ARGS) {
	return Cmd_DamageAV(PASS_COMMAND_ARGS);
}

bool Cmd_RestoreActorValueAlt_Execute(COMMAND_ARGS) {
	return Cmd_RestoreAV(PASS_COMMAND_ARGS);
}

bool Cmd_GetBaseActorValueAlt_Execute(COMMAND_ARGS) {
	return Cmd_GetBaseAV(PASS_COMMAND_ARGS);
}

bool Cmd_ModActorValueAlt_Execute(COMMAND_ARGS) {
	return Cmd_ModAV(PASS_COMMAND_ARGS);
}