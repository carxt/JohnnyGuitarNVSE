#pragma once
#include "JohnnyGuitar/JohnnyEventInterface.h"

EventInformation* OnDyingHandler;

void __stdcall handleDyingEvent(TESObjectREFR* thisObj) {
	for (auto const& callback : OnDyingHandler->EventCallbacks) 
		if (callback->IsBaseInFilter(0, thisObj)) // 0 is filter one, and we only use an argument so we don't need to check further filters
		{
			FunctionCallScript(callback->ScriptForEvent, NULL, 0, &EventResultPtr, OnDyingHandler->numMaxArgs, thisObj);
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

void initEventHooksAndFunctions(const NVSEInterface* nvse)
{
	REG_CMD(RegisterEventHandlerScript);
	REG_CMD(UnregisterEventHandlerScript);
	OnDyingOriginalCall = RetrieveAddrFromDisp32Opcode(0x8A1898);
	WriteRelCall(0x8A1898, (UINT)OnDyingEventAsm);
	OnDyingHandler = DefineEvent("OnDying", 1, 1, NULL, NULL);


}


