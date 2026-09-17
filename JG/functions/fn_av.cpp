#include "fn_av.h"
#include "GameObjects.h"
#include "Bethesda/Interface.hpp"

inline Cmd_Execute Cmd_GetAV		= reinterpret_cast<Cmd_Execute>(0x5BD8A0);
inline Cmd_Execute Cmd_SetAV		= reinterpret_cast<Cmd_Execute>(0x5BDCD0);
inline Cmd_Execute Cmd_ForceAV		= reinterpret_cast<Cmd_Execute>(0x5BE190);
inline Cmd_Execute Cmd_ModAV		= reinterpret_cast<Cmd_Execute>(0x5BDE40);
inline Cmd_Execute Cmd_DamageAV		= reinterpret_cast<Cmd_Execute>(0x5BDF20);
inline Cmd_Execute Cmd_RestoreAV	= reinterpret_cast<Cmd_Execute>(0x5BE080);
inline Cmd_Execute Cmd_GetBaseAV	= reinterpret_cast<Cmd_Execute>(0x5BE6E0);

bool Cmd_GetThresholdedActorValue_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj && thisObj->IsActor()) {
		const ActorValue::Index eActorValue = static_cast<ActorValue::Index>(reinterpret_cast<uint32_t>(arg1));
		*result = static_cast<Actor*>(thisObj)->avOwner.GetClampedActorValueF(eActorValue);
	}
	return true;
}

bool Cmd_GetThresholdedActorValue_Execute(COMMAND_ARGS) {
	*result = 0;
	ActorValue::Index eActorValue = ActorValue::Index::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eActorValue) && thisObj->IsActor()) {
		Cmd_GetThresholdedActorValue_Eval(thisObj, (void*)eActorValue, nullptr, result);
		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetThresholdAV %s >> %.2f", ActorValue::GetActorValueName(eActorValue), *result);
	}
	return true;
}

STACK_FRAME_OPT_ENABLE
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
STACK_FRAME_OPT_RESET