#pragma once
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnDyingEventHandler, SetOnDyingEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnStartQuestEventHandler, SetOnStartQuestEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnStopQuestEventHandler, SetOnStopQuestEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnySeenDataEventHandler, SetSeenDataEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnLimbGoneEventHandler, SetOnLimbGoneEventHandler, , 0, 5, kParams_Event_OneForm_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnChallengeCompleteEventHandler, SetOnChallengeCompleteEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnCrosshairEventHandler, SetOnCrosshairEventHandler, , 0, 5, kParams_Event_OneForm_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnFailQuestEventHandler, SetOnFailQuestEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnCompleteQuestEventHandler, SetOnCompleteQuestEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnSettingsUpdateEventHandler, SetOnSettingsUpdateEventHandler, , 0, 3, kParams_Event);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnAddPerkEventHandler, SetOnAddPerkEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnRemovePerkEventHandler, SetOnRemovePerkEventHandler, , 0, 4, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnRenderUpdateEventHandler, SetOnRenderUpdateEventHandler, , 0, 4, kParams_Event_OptionalFlag);
DEFINE_COMMAND_ALT_PLUGIN(SetOnActorValueChangeEventHandler, SetJohnnyOnActorValueChangeEventHandler, , 0, 4, kParams_Event_OneInt);
DEFINE_COMMAND_PLUGIN(SetOnProcessLevelChangeEventHandler, , 0, 5, kParams_Event_OneForm_OneInt);

EventInformation* OnDyingHandler;
EventInformation* OnStartQuestHandler;
EventInformation* OnStopQuestHandler;
EventInformation* OnFailQuestHandler;
EventInformation* OnCompleteQuestHandler;
EventInformation* OnSeenDataUpdateHandler;
EventInformation* OnLimbGoneHandler;
EventInformation* OnChallengeCompleteHandler;
EventInformation* OnCrosshairHandler;
EventInformation* OnSettingsUpdateHandler;
EventInformation* OnAddPerkHandler;
EventInformation* OnRemovePerkHandler;
EventInformation* OnRenderGamePreUpdateHandler;
EventInformation* OnRenderGameModeUpdateHandler;
EventInformation* OnRenderRenderedMenuUpdateHandler;
EventInformation* OnAVChangeHandler;
EventInformation* OnPLChangeHandler;

UInt32 handlePreRenderEvent() {
	for (auto const& callback : OnRenderGamePreUpdateHandler->EventCallbacks) {
		CallUDF(callback.ScriptForEvent, NULL, OnRenderGamePreUpdateHandler->numMaxArgs);
	}
	return CdeclCall<bool>(0x7050D0);
}

void __fastcall handleRemovePerkEvent(Actor* actor, int EDX, BGSPerk* perk, bool isTeammatePerk) {
	if (!actor->GetPerkRank(perk, isTeammatePerk))
		return;
	for (auto const& callback : OnRemovePerkHandler->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, perk)) {
			CallUDF(callback.ScriptForEvent, actor, OnRemovePerkHandler->numMaxArgs, perk);
		}
	}
	actor->RemovePerk(perk, isTeammatePerk);
}

void __fastcall handleAddPerkEvent(Actor* actor, int EDX, BGSPerk* perk, UInt8 newRank, bool isTeammatePerk) {
	for (auto const& callback : OnAddPerkHandler->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, perk)) {
			CallUDF(callback.ScriptForEvent, actor, OnAddPerkHandler->numMaxArgs, perk, newRank - 1, newRank);
		}
	}
	actor->SetPerkRank(perk, newRank, isTeammatePerk);
}

void __stdcall handleDyingEvent(Actor* thisObj) {
	if (thisObj->IsActor() && thisObj->lifeState == 1 && (*thisObj->GetTheName() || thisObj == g_thePlayer)) {
		for (auto const& callback : OnDyingHandler->EventCallbacks) {
			if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, thisObj)) {
				CallUDF(callback.ScriptForEvent, NULL, OnDyingHandler->numMaxArgs, thisObj);
			}
		}
	}
}
UInt32 __fastcall handleCrosshairEvent(TESObjectREFR* crosshairRef) {
	if (crosshairRef) {
		for (auto const& callback : OnCrosshairHandler->EventCallbacks) {
			JohnnyEventFiltersOneFormOneInt* filter = reinterpret_cast<JohnnyEventFiltersOneFormOneInt*>(callback.eventFilter);
			if ((filter->IsInFilter(0, crosshairRef->refID) || filter->IsInFilter(0, crosshairRef->baseForm->refID)) && filter->IsInFilter(1, crosshairRef->baseForm->typeID)) {
				CallUDF(callback.ScriptForEvent, NULL, OnCrosshairHandler->numMaxArgs, crosshairRef);
			}
		}
	}
	return ThisStdCall<UInt32>(0x579280, crosshairRef);
}
bool __fastcall HandleLimbGoneEvent(ExtraDismemberedLimbs* xData, Actor* actor, byte dummy, int limb, byte isExplode) {
	for (auto const& callback : OnLimbGoneHandler->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersOneFormOneInt*>(callback.eventFilter)->IsInFilter(0, actor->refID) &&
			reinterpret_cast<JohnnyEventFiltersOneFormOneInt*>(callback.eventFilter)->IsInFilter(1, limb)) {
			CallUDF(callback.ScriptForEvent, NULL, OnLimbGoneHandler->numMaxArgs, actor, limb);
		}
	}
	return ThisStdCall_B(0x430410, xData, actor, limb, isExplode);
}
void __fastcall handleQuestStartStop(TESQuest* Quest, bool IsStarted) {
	EventInformation* thisEvent = IsStarted ? OnStartQuestHandler : OnStopQuestHandler;
	for (auto const& callback : thisEvent->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, Quest)) {
			CallUDF(callback.ScriptForEvent, NULL, thisEvent->numMaxArgs, Quest);
		}
	}
}

void __cdecl handleQuestComplete(TESQuest* Quest) {
	for (auto const& callback : OnCompleteQuestHandler->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, Quest)) {
			CallUDF(callback.ScriptForEvent, NULL, OnCompleteQuestHandler->numMaxArgs, Quest);
		}
	}
	CdeclCall(0x77A480, Quest);
}

void __cdecl handleQuestFail(TESQuest* Quest) {
	for (auto const& callback : OnFailQuestHandler->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, Quest)) {
			CallUDF(callback.ScriptForEvent, NULL, OnFailQuestHandler->numMaxArgs, Quest);
		}
	}
	CdeclCall(0x77A480, Quest);
}

void* __cdecl handleSettingsUpdate() {
	for (auto const& callback : OnSettingsUpdateHandler->EventCallbacks) {
		CallUDF(callback.ScriptForEvent, NULL, OnSettingsUpdateHandler->numMaxArgs);
	}
	return CdeclCall<void*>(0x45D180);
}
ExtraDataList* __fastcall HandleSeenDataUpdateEvent(TESObjectCELL* cell) {
	for (auto const& callback : OnSeenDataUpdateHandler->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, cell)) {
			CallUDF(callback.ScriptForEvent, NULL, OnSeenDataUpdateHandler->numMaxArgs, cell);
		}
	}
	return &cell->extraDataList;
}
UInt32 __fastcall HandleChallengeCompleteEvent(TESChallenge* challenge) {
	for (auto const& callback : OnChallengeCompleteHandler->EventCallbacks) {
		if (reinterpret_cast<JohnnyEventFiltersForm*>(callback.eventFilter)->IsBaseInFilter(0, challenge)) {
			CallUDF(callback.ScriptForEvent, NULL, OnChallengeCompleteHandler->numMaxArgs, challenge);
		}
	}
	return challenge->data.type;
}

UInt32 __fastcall handlerRenderGameEvent(void* ECX, void* edx, int arg1, int arg2, int arg3) {
	for (auto const& callback : OnRenderGameModeUpdateHandler->EventCallbacks) {
		CallUDF(callback.ScriptForEvent, NULL, OnRenderGameModeUpdateHandler->numMaxArgs);
	}
	return ThisStdCall<UInt32>(0x08706B0, ECX, arg1, arg2, arg3);
}

UInt32 __fastcall handlerRenderMenuEvent(void* ECX, void* edx, int arg1, int arg2, int arg3) {
	for (auto const& callback : OnRenderRenderedMenuUpdateHandler->EventCallbacks) {
		CallUDF(callback.ScriptForEvent, NULL, OnRenderRenderedMenuUpdateHandler->numMaxArgs);
	}
	return ThisStdCall<UInt32>(0x08706B0, ECX, arg1, arg2, arg3);
}

void __stdcall HandleAVChangeEvent(int avCode, float previousVal, float modVal) {
	if (previousVal == 0.0) previousVal = g_thePlayer->avOwner.GetActorValue(avCode);
	float newVal = previousVal + modVal;
	float roundPrev(round(previousVal)), roundNew(round(newVal));
	if (roundPrev != roundNew) {
		for (auto const& callback : OnAVChangeHandler->EventCallbacks) {
			if (reinterpret_cast<JohnnyEventFiltersOneFormOneInt*>(callback.eventFilter)->IsInFilter(1, avCode)) {
				CallUDF(callback.ScriptForEvent, NULL, OnAVChangeHandler->numMaxArgs, avCode, *(UInt32*)&roundPrev, *(UInt32*)&roundNew);
			}
		}
	}
}
template <UInt32 originalCall>
bool __fastcall HandlePLChangeEvent(Actor* actor) {
	if (actor == NULL || actor->baseProcess == NULL) return true; //early exit, no need to handle error states because there's no baseProcess.
	int oldLevel = actor->baseProcess->processLevel;
	bool result = ThisStdCall_B(originalCall, actor);
	int newLevel = actor->baseProcess->processLevel;
	if (oldLevel != newLevel) {
		for (auto const& callback : OnPLChangeHandler->EventCallbacks) {
			JohnnyEventFiltersOneFormOneInt* filter = reinterpret_cast<JohnnyEventFiltersOneFormOneInt*>(callback.eventFilter);
			if ((filter->IsInFilter(0, actor->refID) || filter->IsInFilter(0, actor->GetBaseForm()->refID)) &&
				filter->IsInFilter(1, newLevel)) {
				CallUDF(callback.ScriptForEvent, NULL, OnPLChangeHandler->numMaxArgs, actor, oldLevel, newLevel);
			}
		}
	}
		return result;
}

__declspec(naked) void __cdecl AVChangeEventAsm(ActorValueOwner* avOwner, UInt32 avCode, float prevVal, float newVal, ActorValueOwner* attacker)
{
	__asm
	{
		push    ebp
		mov     ebp, esp
		mov     eax, [ebp + 0xC]
		cmp     eax, 0x4D
		jnb     done
		mov     ecx, ds:0x11D61C8[eax * 4]
		test    ecx, ecx
		jz      done
		push    ecx
		mov     ecx, [ebp + 8]
		cmp     dword ptr[ecx - 0x98], 0x14
		jnz     skipHandler
		push    dword ptr[ebp + 0x14]
		push    dword ptr[ebp + 0x10]
		push    eax
		call    HandleAVChangeEvent
		skipHandler :
			mov     ecx, [ebp - 4]
			cmp     dword ptr[ecx + 0x54], 0
			jz      done
			mov     eax, 0x66EE72
			jmp     eax
		done :
			leave
			retn
	}
}

__declspec(naked) void OnCrosshairEventAsm() {
	static const UInt32 retnAddr = 0x775A69;
	__asm {
		mov ecx, [ebp + 0x8]
		call handleCrosshairEvent
		movzx ecx, [ebp + 0x10]
		test ecx, ecx
		jmp retnAddr
	}
}
__declspec (naked) void OnDyingEventAsm() {
	static const UInt32 checkProtect = 0xEC408C;
	__asm
	{
		push dword ptr[ebp - 0x18]
		call handleDyingEvent
		mov ecx, dword ptr ss : [ebp - 0xC]
		mov dword ptr fs : [0] , ecx
		pop ecx
		pop esi
		mov ecx, dword ptr ss : [ebp - 0x14]
		xor ecx, ebp
		call checkProtect
		mov esp, ebp
		pop ebp
		mov esp, ebx
		pop ebx
		retn 8
	}
}

__declspec (naked) void OnQuestStartStopEventAsm() {
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


bool Cmd_SetJohnnyOnLimbGoneEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	EventFilterStructOneFormOneInt filter = { NULL, -1 }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.form, &filter.intID) && IS_TYPE(script, Script)) {
		if (OnLimbGoneHandler) {
			if (setOrRemove)
				OnLimbGoneHandler->RegisterEvent(script, (void**)&filter);
			else OnLimbGoneHandler->RemoveEvent(script, (void**)&filter);
		}
	}
	return true;
}
bool Cmd_SetJohnnyOnSettingsUpdateEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags) && IS_TYPE(script, Script)) {
		if (OnSettingsUpdateHandler) {
			if (setOrRemove)
				OnSettingsUpdateHandler->RegisterEvent(script, NULL);
			else OnSettingsUpdateHandler->RemoveEvent(script, NULL);
		}
	}
	return true;
}
bool Cmd_SetJohnnyOnCrosshairEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	EventFilterStructOneFormOneInt filter = { NULL, -1 };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.form, &filter.intID) && IS_TYPE(script, Script)) {
		if (OnCrosshairHandler) {
			if (setOrRemove)
				OnCrosshairHandler->RegisterEvent(script, (void**)&filter);
			else OnCrosshairHandler->RemoveEvent(script, (void**)&filter);
		}
	}
	return true;
}

bool Cmd_SetOnActorValueChangeEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	EventFilterStructOneFormOneInt filter = { g_thePlayer, -1 };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.intID) && IS_TYPE(script, Script) && filter.intID <= kAVCode_DamageThreshold) {
		if (OnAVChangeHandler) {
			if (setOrRemove)
				OnAVChangeHandler->RegisterEvent(script, (void**)&filter);
			else OnAVChangeHandler->RemoveEvent(script, (void**)&filter);
		}
	}
	return true;
}
bool Cmd_SetJohnnyOnRemovePerkEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnRemovePerkHandler) {
			if (setOrRemove)
				OnRemovePerkHandler->RegisterEvent(script, (void**)filter);
			else OnRemovePerkHandler->RemoveEvent(script, (void**)filter);
		}
	}
	return true;
}
bool Cmd_SetJohnnyOnAddPerkEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnAddPerkHandler) {
			if (setOrRemove)
				OnAddPerkHandler->RegisterEvent(script, (void**)filter);
			else OnAddPerkHandler->RemoveEvent(script, (void**)filter);
		}
	}
	return true;
}
bool Cmd_SetJohnnyOnChallengeCompleteEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnChallengeCompleteHandler) {
			if (setOrRemove)
				OnChallengeCompleteHandler->RegisterEvent(script, (void**)filter);
			else OnChallengeCompleteHandler->RemoveEvent(script, (void**)filter);
		}
	}
	return true;
}
bool Cmd_SetJohnnySeenDataEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnSeenDataUpdateHandler) {
			if (setOrRemove)
				OnSeenDataUpdateHandler->RegisterEvent(script, (void**)filter);
			else OnSeenDataUpdateHandler->RemoveEvent(script, (void**)filter);
		}
	}
	return true;
}
bool Cmd_SetJohnnyOnDyingEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnDyingHandler) {
			if (setOrRemove)
				OnDyingHandler->RegisterEvent(script, (void**)filter);
			else OnDyingHandler->RemoveEvent(script, (void**)filter);
		}
	}
	return true;
}

bool Cmd_SetJohnnyOnStartQuestEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnStartQuestHandler) {
			if (setOrRemove)
				OnStartQuestHandler->RegisterEvent(script, (void**)filter);
			else OnStartQuestHandler->RemoveEvent(script, (void**)filter);
		}
	}

	return true;
}

bool Cmd_SetJohnnyOnStopQuestEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnStopQuestHandler) {
			if (setOrRemove)
				OnStopQuestHandler->RegisterEvent(script, (void**)filter);
			else OnStopQuestHandler->RemoveEvent(script, (void**)filter);
		}
	}

	return true;
}

bool Cmd_SetJohnnyOnCompleteQuestEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnCompleteQuestHandler) {
			if (setOrRemove)
				OnCompleteQuestHandler->RegisterEvent(script, (void**)filter);
			else OnCompleteQuestHandler->RemoveEvent(script, (void**)filter);
		}
	}
	return true;
}

bool Cmd_SetJohnnyOnFailQuestEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	TESForm* filter[1] = { NULL };
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && IS_TYPE(script, Script)) {
		if (OnFailQuestHandler) {
			if (setOrRemove)
				OnFailQuestHandler->RegisterEvent(script, (void**)filter);
			else OnFailQuestHandler->RemoveEvent(script, (void**)filter);
		}
	}
	return true;
}

bool Cmd_SetJohnnyOnRenderUpdateEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	UInt32 flags = 0;
	UInt32 optionalFlags = 0;

	enum EnumFlags {
		kDoNotFireInRenderMenu = 1 << 0,
		kDoNotFireInGameMode = 1 << 1,
		kUseGamePreEvent = 1 << 2,
	};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &optionalFlags) && IS_TYPE(script, Script)) {
		if (!(optionalFlags & kDoNotFireInGameMode) && OnRenderGameModeUpdateHandler) {
			if (!(optionalFlags & kUseGamePreEvent)) {
				if (setOrRemove)
					OnRenderGameModeUpdateHandler->RegisterEvent(script, NULL);
				else OnRenderGameModeUpdateHandler->RemoveEvent(script, NULL);
			}
			else if (OnRenderGamePreUpdateHandler) {
				if (setOrRemove)
					OnRenderGamePreUpdateHandler->RegisterEvent(script, NULL);
				else OnRenderGamePreUpdateHandler->RemoveEvent(script, NULL);
			}
		}

		if (!(optionalFlags & kDoNotFireInRenderMenu) && OnRenderRenderedMenuUpdateHandler) {
			if (setOrRemove)
				OnRenderRenderedMenuUpdateHandler->RegisterEvent(script, NULL);
			else OnRenderRenderedMenuUpdateHandler->RemoveEvent(script, NULL);
		}
	}

	return true;
}

bool Cmd_SetOnProcessLevelChangeEventHandler_Execute(COMMAND_ARGS) {
	UInt32 setOrRemove = 0;
	Script* script = NULL;
	EventFilterStructOneFormOneInt filter = { NULL, -1 }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	UInt32 flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.form, &filter.intID) && IS_TYPE(script, Script)) {
		if (OnPLChangeHandler) {
			if (setOrRemove)
				OnPLChangeHandler->RegisterEvent(script, (void**)&filter);
			else OnPLChangeHandler->RemoveEvent(script, (void**)&filter);
		}
	}
	return true;
}


void HandleEventHooks() {
	OnDyingHandler = JGCreateEvent("OnDying", 1, 1, NULL);
	OnStartQuestHandler = JGCreateEvent("OnStartQuest", 1, 1, NULL);
	OnStopQuestHandler = JGCreateEvent("OnStopQuest", 1, 1, NULL);
	OnSeenDataUpdateHandler = JGCreateEvent("OnSeenDataUpdate", 1, 1, NULL);
	OnLimbGoneHandler = JGCreateEvent("OnLimbGone", 2, 2, CreateOneFormOneIntFilter);
	OnChallengeCompleteHandler = JGCreateEvent("OnChallengeComplete", 1, 1, NULL);
	OnCrosshairHandler = JGCreateEvent("OnCrosshair", 1, 2, CreateOneFormOneIntFilter);
	OnCompleteQuestHandler = JGCreateEvent("OnCompleteQuest", 1, 1, NULL);
	OnFailQuestHandler = JGCreateEvent("OnFailQuest", 1, 1, NULL);
	OnSettingsUpdateHandler = JGCreateEvent("OnSettingsUpdate", 0, 0, NULL);
	OnAddPerkHandler = JGCreateEvent("OnAddPerk", 3, 1, NULL);
	OnRemovePerkHandler = JGCreateEvent("OnRemovePerk", 1, 1, NULL);
	OnAVChangeHandler = JGCreateEvent("OnActorValueChange", 3, 2, CreateOneFormOneIntFilter);
	OnPLChangeHandler = JGCreateEvent("OnProcessLevelChange", 3, 2, CreateOneFormOneIntFilter);

	CallUDF = g_scriptInterface->CallFunctionAlt;
	WriteRelCall(0x55678A, (UINT)HandleSeenDataUpdateEvent);
	WriteRelCall(0x557053, (UINT)HandleSeenDataUpdateEvent);
	WriteRelJump(0x89F4A4, (UINT)OnDyingEventAsm);
	WriteRelJump(0x60CA24, (UINT)OnQuestStartStopEventAsm);
	WriteRelCall(0x572FF1, (UINT)HandleLimbGoneEvent);
	WriteRelCall(0x5F5C78, (UINT)HandleChallengeCompleteEvent);
	WriteRelCall(0x5F6222, (UINT)HandleChallengeCompleteEvent);
	WriteRelCall(0x776010, (UINT)handleCrosshairEvent);
	WriteRelCall(0x60CB5A, (UINT)handleQuestFail);
	WriteRelCall(0x60CA78, (UINT)handleQuestComplete);
	WriteRelCall(0x7D6D73, (UINT)handleSettingsUpdate);
	WriteRelCall(0x5D4E5B, (UINT)handleAddPerkEvent);
	WriteRelCall(0x7865BD, (UINT)handleAddPerkEvent);
	WriteRelCall(0x7E772D, (UINT)handleAddPerkEvent);
	SafeWriteBuf(0x7E7732, "\x0F\x1F\x00", 3);
	SafeWriteBuf(0x7865C2, "\x0F\x1F\x00", 3);
	SafeWriteBuf(0x5D4E60, "\x0F\x1F\x00", 3);
	WriteRelCall(0x5D4F89, (UINT)handleRemovePerkEvent);
	SafeWriteBuf(0x5D4F8E, "\x0F\x1F\x00", 3);
	SafeWrite8(0x60CA29, 0xCC);
	WriteRelJump(0x66EE50, (UINT)AVChangeEventAsm);
	// Process Level change: MoveToHigh
	SafeWrite32(0x108AC7C, (UINT)HandlePLChangeEvent<0x881D30>);
	SafeWrite32(0x10872EC, (UINT)HandlePLChangeEvent<0x881D30>);
	SafeWrite32(0x1086CAC, (UINT)HandlePLChangeEvent<0x881D30>);
	SafeWrite32(0x1084494, (UINT)HandlePLChangeEvent<0x881D30>);
	// MoveToLow
	SafeWrite32(0x108AC80, (UINT)HandlePLChangeEvent<0x882B90>);
	SafeWrite32(0x10872F0, (UINT)HandlePLChangeEvent<0x882B90>);
	SafeWrite32(0x1086CB0, (UINT)HandlePLChangeEvent<0x882B90>);
	SafeWrite32(0x1084498, (UINT)HandlePLChangeEvent<0x882B90>);
	// MoveToMiddleLow
	SafeWrite32(0x108AC84, (UINT)HandlePLChangeEvent<0x883240>);
	SafeWrite32(0x10872F4, (UINT)HandlePLChangeEvent<0x883240>);
	SafeWrite32(0x1086CB4, (UINT)HandlePLChangeEvent<0x883240>);
	SafeWrite32(0x108449C, (UINT)HandlePLChangeEvent<0x883240>);
	// MoveToMiddleHigh
	SafeWrite32(0x108AC88, (UINT)HandlePLChangeEvent<0x883800>);
	SafeWrite32(0x10872F8, (UINT)HandlePLChangeEvent<0x883800>);
	SafeWrite32(0x1086CB8, (UINT)HandlePLChangeEvent<0x883800>);
	SafeWrite32(0x10844A0, (UINT)HandlePLChangeEvent<0x883800>);


	//testing
	OnRenderGamePreUpdateHandler = JGCreateEvent("OnRenderGamePreUpdateHandler", 0, 0, NULL);
	WriteRelCall(0x943748, (uintptr_t)handlePreRenderEvent);
	OnRenderGameModeUpdateHandler = JGCreateEvent("OnRenderGameModeUpdateHandler", 0, 0, NULL);
	WriteRelCall(0x870244, (uintptr_t)handlerRenderGameEvent);
	OnRenderRenderedMenuUpdateHandler = JGCreateEvent("OnRenderRenderedMenuUpdateHandler", 0, 0, NULL);
	WriteRelCall(0x8702A9, (uintptr_t)handlerRenderMenuEvent);
}
