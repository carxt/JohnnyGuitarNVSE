#pragma once



EventInformation* OnDyingHandler;

void __stdcall handleDyingEvent(TESObjectREFR* thisObj) {
	for (auto const& callback : OnDyingHandler->EventCallbacks) 
		if (callback.eventFilter->IsBaseInFilter(0, thisObj)) // 0 is filter one, and we only use an argument so we don't need to check further filters
		{
			FunctionCallScript(callback.ScriptForEvent, NULL, 0, &EventResultPtr, OnDyingHandler->numMaxArgs, thisObj);
		}
}

static UInt32 OnDyingOriginalCall;
__declspec (naked) void OnDyingEventAsm()
{
	__asm
	{
		cmp dword ptr [ebp+8], 1
		jnz done
		push dword ptr[ebp - 0x2C]
		call handleDyingEvent
		done:
		mov ecx, dword ptr [ebp-0x2C]
		jmp OnDyingOriginalCall
	}
}






ParamInfo kParamsJohnnyEventOnDying[7] =
{
	{ "setOrRemove", kParamType_Integer, 0 },
	{ "Script", kParamType_AnyForm, 0 },
	{ "flags", kParamType_Integer, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Form", kParamType_AnyForm, 1 },
	{ "Form", kParamType_AnyForm, 1 }

};

DEFINE_COMMAND_PLUGIN(SetJohnnyOnDyingEventHandlerScript, , 0, 7, kParamsJohnnyEventOnDying);

bool Cmd_SetJohnnyOnDyingEventHandlerScript_Execute(COMMAND_ARGS)
{
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	UInt32 flags = 0;
	if (!(ExtractArgs(EXTRACT_ARGS, &setOrRemove, &script, &flags, &filter[0]) || !IS_TYPE(script, Script))) return true;
	{
		if (OnDyingHandler)
		{
			setOrRemove ? OnDyingHandler->RegisterEvent(script, (void**)filter) : OnDyingHandler->RemoveEventFromGame(script, (void**)filter);

		}
		return true;
	}
}







void initEventHooksAndFunctions(const NVSEInterface* nvse)
{

	REG_CMD(SetJohnnyOnDyingEventHandlerScript);
	if (!(nvse->isEditor))
	{
		OnDyingHandler = JGCreateEvent("OnDying", 1, 1, NULL);
		FunctionCallScript = g_script->CallFunction;
		OnDyingOriginalCall = RetrieveAddrFromDisp32Opcode(0x8A1898);
		WriteRelCall(0x8A1898, (UINT)OnDyingEventAsm);
	}

}


