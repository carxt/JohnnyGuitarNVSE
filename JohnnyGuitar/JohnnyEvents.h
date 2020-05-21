#pragma once
DEFINE_COMMAND_PLUGIN(SetJohnnyOnDyingEventHandler, , 0, 4, kParamsJohnnyEventOneFormFilter);
DEFINE_COMMAND_PLUGIN(SetJohnnyOnStartQuestEventHandler, , 0, 4, kParamsJohnnyEventOneFormFilter);
DEFINE_COMMAND_PLUGIN(SetJohnnyOnStopQuestEventHandler, , 0, 4, kParamsJohnnyEventOneFormFilter);


EventInformation* OnDyingHandler;
EventInformation* OnStartQuestHandler;
EventInformation* OnStopQuestHandler;


void __stdcall handleDyingEvent(TESObjectREFR* thisObj) {
	for (auto const& callback : OnDyingHandler->EventCallbacks)
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, thisObj)) // 0 is filter one, and we only use an argument so we don't need to check further filters
		{
			FunctionCallScript(callback.ScriptForEvent, NULL, 0, &EventResultPtr, OnDyingHandler->numMaxArgs, thisObj);
		}
}


void __fastcall handleQuestStartStop(TESQuest* Quest, bool IsStarted) {
	EventInformation* thisEvent = IsStarted ? OnStartQuestHandler : OnStopQuestHandler;
	for (auto const& callback : thisEvent->EventCallbacks)
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, Quest)) // 0 is filter one, and we only use an argument so we don't need to check further filters
		{
			FunctionCallScript(callback.ScriptForEvent, NULL, 0, &EventResultPtr, thisEvent->numMaxArgs, Quest);
		}
}


static UInt32 OnDyingOriginalCall;
__declspec (naked) void OnDyingEventAsm()
{
	__asm
	{
		cmp dword ptr[ebp + 8], 1
		jnz done
		push dword ptr[ebp - 0x2C]
		call handleDyingEvent
		done :
		mov ecx, dword ptr[ebp - 0x2C]
			jmp OnDyingOriginalCall
	}
}

__declspec (naked) void OnQuestStartStopEventAsm()
{
	__asm
	{
		mov ecx, dword ptr[ebp - 4]
		mov dl, byte ptr[ebp + 8]
		call handleQuestStartStop
		mov esp, ebp
		pop ebp
		ret 4
	}
}

bool Cmd_SetJohnnyOnDyingEventHandler_Execute(COMMAND_ARGS)
{
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	UInt32 flags = 0;
	if (!(ExtractArgs(EXTRACT_ARGS, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script))) return true;
	{
		if (OnDyingHandler)
		{
			if (setOrRemove)
				OnDyingHandler->RegisterEvent(script, (void**)filter);
			else OnDyingHandler->RemoveEventFromGame(script, (void**)filter);

		}
		return true;
	}
}

bool Cmd_SetJohnnyOnStartQuestEventHandler_Execute(COMMAND_ARGS)
{
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	UInt32 flags = 0;
	if (!(ExtractArgs(EXTRACT_ARGS, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script))) return true;
	{
		if (OnStartQuestHandler)
		{
			if (setOrRemove)
				OnStartQuestHandler->RegisterEvent(script, (void**)filter);
			else OnStartQuestHandler->RemoveEventFromGame(script, (void**)filter);

		}
		return true;
	}
}


bool Cmd_SetJohnnyOnStopQuestEventHandler_Execute(COMMAND_ARGS)
{
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	UInt32 flags = 0;
	if (!(ExtractArgs(EXTRACT_ARGS, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script))) return true;
	{
		if (OnStopQuestHandler)
		{
			if (setOrRemove)
				OnStopQuestHandler->RegisterEvent(script, (void**)filter);
			else OnStopQuestHandler->RemoveEventFromGame(script, (void**)filter);

		}
		return true;
	}
}


void initEventHooksAndFunctions(const NVSEInterface* nvse)
{

	REG_CMD(SetJohnnyOnDyingEventHandler);
	REG_CMD(SetJohnnyOnStartQuestEventHandler);
	REG_CMD(SetJohnnyOnStopQuestEventHandler);

	if (!(nvse->isEditor))
	{
		OnDyingHandler = JGCreateEvent("OnDying", 1, 1, NULL);
		OnStartQuestHandler = JGCreateEvent("OnStartQuest", 1, 1, NULL);
		OnStopQuestHandler = JGCreateEvent("OnStopQuest", 1, 1, NULL);

		FunctionCallScript = g_script->CallFunction;
		OnDyingOriginalCall = RetrieveAddrFromDisp32Opcode(0x8A1898);
		WriteRelCall(0x8A1898, (UINT)OnDyingEventAsm);
		WriteRelJump(0x60CA24, (UINT)OnQuestStartStopEventAsm);
		SafeWrite8(0x60CA29, 0xCC);
	}

}