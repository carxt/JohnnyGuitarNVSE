#include "fn_av.h"
#include "GameObjects.h"
#include "GameAPI.h"

bool(__cdecl* Cmd_GetAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BD8A0;
bool(__cdecl* Cmd_SetAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BDCD0;
bool(__cdecl* Cmd_ForceAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BE190;
bool(__cdecl* Cmd_ModAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BDE40;
bool(__cdecl* Cmd_DamageAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BDF20;
bool(__cdecl* Cmd_RestoreAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BE080;
bool(__cdecl* Cmd_GetBaseAV)(COMMAND_ARGS) = (bool(__cdecl*)(COMMAND_ARGS)) 0x5BE6E0;

bool Cmd_GetThresholdedActorValue_Execute(COMMAND_ARGS) {
	arResult = 0;
	ActorValue::Index eIndex;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eIndex) && apRef->IsActor()) {
		arResult = static_cast<Actor*>(apRef)->GetClampedActorValueF(eIndex);
		if (IsConsoleMode()) 
			Console_Print("GetThresholdAV %d >> %.2f", eIndex, arResult);
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