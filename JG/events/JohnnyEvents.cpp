#include "JohnnyEvents.h"
#include "EventFramework.h"
#include "GameProcess.h"
#include "decoding.h"
#include <internal/Game/Bethesda/DialogueResponse.hpp>
#include <internal/Game/Bethesda/MenuTopic.hpp>


extern NVSEScriptInterface* g_scriptInterface;

namespace JohnnyEvents {

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
	EventInformation* OnRadioPostSoundAttachHandler;
	EventInformation* OnKeyboardControllerSelectionChangeHandler;
	EventInformation* OnSleepWaitEventHandler;
	EventInformation* OnTakeBackItemHandler;
	EventInformation* OnNPCResponseHandler;
	EventInformation* OnGeneralSubtitleHandler;
	EventInformation* OnReputationChangeHandler;
	EventInformation* OnNPCAVChangeHandler;


	uint32_t handlePreRenderEvent() {
		for (auto const& callback : OnRenderGamePreUpdateHandler->callbacks) {
			CallUDF(callback.script, nullptr, OnRenderGamePreUpdateHandler->numMaxArgs);
		}
		return CdeclCall<bool>(0x7050D0);
	}

	void __fastcall handleRemovePerkEvent(Actor* actor, int EDX, BGSPerk* perk, bool isTeammatePerk) {
		if (!actor->GetPerkRank(perk, isTeammatePerk))
			return;
		for (auto const& callback : OnRemovePerkHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, perk)) {
				CallUDF(callback.script, actor, OnRemovePerkHandler->numMaxArgs, perk);
			}
		}
		actor->RemovePerk(perk, isTeammatePerk);
	}

	void __fastcall handleAddPerkEvent(Actor* actor, int EDX, BGSPerk* perk, uint8_t newRank, bool isTeammatePerk) {
		for (auto const& callback : OnAddPerkHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, perk)) {
				CallUDF(callback.script, actor, OnAddPerkHandler->numMaxArgs, perk, newRank - 1, newRank);
			}
		}
		actor->SetPerkRank(perk, newRank, isTeammatePerk);
	}

	void __stdcall handleDyingEvent(Actor* thisObj) {
		if (thisObj->IsActor() && thisObj->lifeState == 1 && (thisObj->GetFullName()[0] || thisObj == PlayerCharacter::GetSingleton())) {
			for (auto const& callback : OnDyingHandler->callbacks) {
				if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, thisObj)) {
					CallUDF(callback.script, nullptr, OnDyingHandler->numMaxArgs, thisObj);
				}
			}
		}
	}
	uint32_t __fastcall handleCrosshairEvent(TESObjectREFR* crosshairRef) {
		if (crosshairRef) {
			for (auto const& callback : OnCrosshairHandler->callbacks) {
				FilterFormInt* filter = reinterpret_cast<FilterFormInt*>(callback.eventFilter);
				if ((filter->IsInFilter(0, crosshairRef->GetFormID()) || filter->IsInFilter(0, crosshairRef->baseForm->GetFormID())) && filter->IsInFilter(1, crosshairRef->baseForm->GetFormType())) {
					CallUDF(callback.script, nullptr, OnCrosshairHandler->numMaxArgs, crosshairRef);
				}
			}
		}
		return ThisCall<uint32_t>(0x579280, crosshairRef);
	}
	bool __fastcall HandleLimbGoneEvent(ExtraDismemberedLimbs* xData, Actor* actor, byte dummy, int limb, byte isExplode) {
		for (auto const& callback : OnLimbGoneHandler->callbacks) {
			FilterFormInt* filter = reinterpret_cast<FilterFormInt*>(callback.eventFilter);
			if ((filter->IsInFilter(0, actor->GetFormID()) || filter->IsInFilter(0, actor->baseForm->GetFormID())) && filter->IsInFilter(1, limb)) {
				CallUDF(callback.script, nullptr, OnLimbGoneHandler->numMaxArgs, actor, limb);
			}
		}
		return ThisCall<bool>(0x430410, xData, actor, limb, isExplode);
	}
	void __fastcall handleQuestStartStop(TESQuest* Quest, bool IsStarted) {
		EventInformation* thisEvent = IsStarted ? OnStartQuestHandler : OnStopQuestHandler;
		for (auto const& callback : thisEvent->callbacks) {
			if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, Quest)) {
				CallUDF(callback.script, nullptr, thisEvent->numMaxArgs, Quest);
			}
		}
	}

	void __cdecl handleQuestComplete(TESQuest* Quest) {
		for (auto const& callback : OnCompleteQuestHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, Quest)) {
				CallUDF(callback.script, nullptr, OnCompleteQuestHandler->numMaxArgs, Quest);
			}
		}
		CdeclCall(0x77A480, Quest);
	}

	void __cdecl handleQuestFail(TESQuest* Quest) {
		for (auto const& callback : OnFailQuestHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, Quest)) {
				CallUDF(callback.script, nullptr, OnFailQuestHandler->numMaxArgs, Quest);
			}
		}
		CdeclCall(0x77A480, Quest);
	}

	void* __cdecl handleSettingsUpdate() {
		for (auto const& callback : OnSettingsUpdateHandler->callbacks) {
			CallUDF(callback.script, nullptr, OnSettingsUpdateHandler->numMaxArgs);
		}
		return CdeclCall<void*>(0x45D180);
	}
	ExtraDataList* __fastcall HandleSeenDataUpdateEvent(TESObjectCELL* cell) {
		for (auto const& callback : OnSeenDataUpdateHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, cell)) {
				CallUDF(callback.script, nullptr, OnSeenDataUpdateHandler->numMaxArgs, cell);
			}
		}
		return &cell->extraDataList;
	}
	uint32_t __fastcall HandleChallengeCompleteEvent(TESChallenge* challenge) {
		for (auto const& callback : OnChallengeCompleteHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(callback.eventFilter)->IsBaseInFilter(0, challenge)) {
				CallUDF(callback.script, nullptr, OnChallengeCompleteHandler->numMaxArgs, challenge);
			}
		}
		return challenge->kData.eType;
	}

	uint32_t __fastcall handlerRenderGameEvent(void* ECX, void* edx, int arg1, int arg2, int arg3) {
		for (auto const& callback : OnRenderGameModeUpdateHandler->callbacks) {
			CallUDF(callback.script, nullptr, OnRenderGameModeUpdateHandler->numMaxArgs);
		}
		return ThisCall<uint32_t>(0x08706B0, ECX, arg1, arg2, arg3);
	}

	uint32_t __fastcall handlerRenderMenuEvent(void* ECX, void* edx, int arg1, int arg2, int arg3) {
		for (auto const& callback : OnRenderRenderedMenuUpdateHandler->callbacks) {
			CallUDF(callback.script, nullptr, OnRenderRenderedMenuUpdateHandler->numMaxArgs);
		}
		return ThisCall<uint32_t>(0x08706B0, ECX, arg1, arg2, arg3);
	}

	bool CompareFloats(float a, float b) {
		const float epsilon = 0.0001f;
		return fabs(a - b) < epsilon;
	}

	void __stdcall HandleAVChangeEvent(ActorValueOwner* avOwner, ActorValue::Index avCode, float previousVal, float modVal, void* onChangeCallback) {
		if (onChangeCallback == nullptr)
			previousVal = avOwner->GetActorValueF(avCode) - modVal;

		const float fNewValue = previousVal + modVal;
		const float fPreviousValue = previousVal;

		const float fNewValueFloor = floor(fNewValue);
		const float fPreviousValueFloor = floor(fPreviousValue);

		TESForm* pForm = avOwner->GetAsForm();
		Actor* pActor = nullptr;
		if (pForm->IsActor())
			pActor = static_cast<Actor*>(pForm);

		if (!CompareFloats(fNewValueFloor, fPreviousValueFloor)) {
			//Console_Print("actor 0x%X av %d prev %.2f mod %.2f new %.2f callback 0x%X", avOwner->GetAsForm()->GetFormID(), avCode, previousVal, modVal, newVal, onChangeCallback);

			if (pActor && pActor->IsPlayerRef()) {
				for (auto const& callback : OnAVChangeHandler->callbacks) {
					FilterFormInt* filter = reinterpret_cast<FilterFormInt*>(callback.eventFilter);
					if (filter->IsInFilter(1, avCode)) {

						bool bFullValues = callback.UserFlags.Get(1);

						const float& fNewVal = bFullValues ? fNewValue : fNewValueFloor;
						const float& fPrevVal = bFullValues ? fPreviousValue : fPreviousValueFloor;

						CallUDF(callback.script, nullptr, OnAVChangeHandler->numMaxArgs, avCode, *(uint32_t*)&fPrevVal, *(uint32_t*)&fNewVal);
					}
				}
			}
			else {
				for (auto const& callback : OnNPCAVChangeHandler->callbacks) {
					FilterFormInt* filter = reinterpret_cast<FilterFormInt*>(callback.eventFilter);
					if (filter->IsInFilter(1, avCode) && (filter->IsInFilter(0, pForm->GetFormID()) || (pActor && filter->IsInFilter(0, pActor->GetBaseForm()->GetFormID())))) {

						bool bFullValues = callback.UserFlags.Get(1);

						const float& fNewVal = bFullValues ? fNewValue : fNewValueFloor;
						const float& fPrevVal = bFullValues ? fPreviousValue : fPreviousValueFloor;

						CallUDF(callback.script, nullptr, OnNPCAVChangeHandler->numMaxArgs, pForm, avCode, *(uint32_t*)&fPrevVal, *(uint32_t*)&fNewVal);
					}
				}
			}
		}
	}
	template <uint32_t originalCall>
	bool __fastcall HandlePLChangeEvent(Actor* actor) {
		if (actor == nullptr || actor->baseProcess == nullptr) return true; //early exit, no need to handle error states because there's no baseProcess.
		int oldLevel = actor->baseProcess->processLevel;
		bool result = ThisCall<bool>(originalCall, actor);
		int newLevel = actor->baseProcess->processLevel;
		if (oldLevel != newLevel) {
			for (auto const& callback : OnPLChangeHandler->callbacks) {
				FilterFormInt* filter = reinterpret_cast<FilterFormInt*>(callback.eventFilter);
				if ((filter->IsInFilter(0, actor->GetFormID()) || filter->IsInFilter(0, actor->GetBaseForm()->GetFormID())) &&
					filter->IsInFilter(1, newLevel)) {
					CallUDF(callback.script, nullptr, OnPLChangeHandler->numMaxArgs, actor, oldLevel, newLevel);
				}
			}
		}
		return result;
	}

	void __fastcall HandleOnRadioPostSoundAttach(TESObjectACTI* a_radioActi, unsigned int mode) {
		if (a_radioActi == nullptr) return;
		for (auto const& callback : OnRadioPostSoundAttachHandler->callbacks) {
			FilterForm* filter = reinterpret_cast<FilterForm*>(callback.eventFilter);
			if (filter->IsBaseInFilter(0, a_radioActi)) {
				CallUDF(callback.script, nullptr, OnRadioPostSoundAttachHandler->numMaxArgs, a_radioActi, (mode > 0) ? 1 : 0);
			}
		}
	}


	void __fastcall HandleInputSwitch(InterfaceManager* a_man, Menu* a_menu) {
		int menuId = -1;
		if (a_menu) {
			menuId = a_menu->GetID();
		}
		for (auto const& callback : OnKeyboardControllerSelectionChangeHandler->callbacks) {
			auto filter = reinterpret_cast<FilterInt*>(callback.eventFilter);
			if (filter->IsInFilter(0, menuId) || filter->IsInFilter(0, 0)) {
				CallUDF(callback.script, nullptr, OnKeyboardControllerSelectionChangeHandler->numMaxArgs, menuId);
			}
		}
	}


	void __fastcall HandleOnSleepWait(SleepWaitMenu* a_man, uint32_t clickMode) {
		for (auto const& callback : OnSleepWaitEventHandler->callbacks) {
			auto filter = reinterpret_cast<FilterInt*>(callback.eventFilter);
			if (filter->IsInFilter(0, int(a_man->isRest) + 1) || filter->IsInFilter(0, 0)) {
				CallUDF(callback.script, nullptr, OnKeyboardControllerSelectionChangeHandler->numMaxArgs, (int(a_man->isRest) + 1));
			}
		}
	}



	__declspec(naked) void __cdecl AVChangeEventAsm(ActorValueOwner* avOwner, uint32_t avCode, float prevVal, float newVal, ActorValueOwner* attacker)
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
			mov		ecx, dword ptr[ecx + 0x54]
			push	ecx
			mov     ecx, [ebp + 8]
			//cmp     dword ptr[ecx - 0x98], 0x14 // Check for PlayerREF
			//jnz     skipHandler
			push    dword ptr[ebp + 0x14]
			push    dword ptr[ebp + 0x10]
			push    eax
			push    dword ptr[ebp + 0x08]
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
		static const uint32_t retnAddr = 0x775A69;
		__asm {
			mov ecx, [ebp + 0x8]
			call handleCrosshairEvent
			movzx ecx, [ebp + 0x10]
			test ecx, ecx
			jmp retnAddr
		}
	}
	__declspec (naked) void OnDyingEventAsm() {
		static const uint32_t checkProtect = 0xEC408C;
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


	__declspec (naked) void OnKeyboardControllerSelectionChangeAsm() {
		__asm
		{
			ret 4
		}
	}

	TESObjectREFR* hkOwner = nullptr;

	ExtraDataList* __fastcall GetExtraDataListHook(TESObjectREFR* owner)
	{
		hkOwner = owner;
		return &owner->extraDataList;
	}

	void __fastcall HandleTakeBackItem(void* contChanges, void* edx, PlayerCharacter* player, TESForm* item, bool keepOwner, int32_t quantity, void* xList, bool a9, Actor* target, int a10, int a11, bool a12, bool a13, void* cEntry)
	{
		for (auto const& callback : OnTakeBackItemHandler->callbacks) {
			auto filter = reinterpret_cast<FilterForm*>(callback.eventFilter);
			TESObjectREFR* owner = target->IsActor() ? target : hkOwner;
			if (filter->IsBaseInFilter(0, item) && (filter->IsInFilter(1, owner->GetFormID()) || filter->IsInFilter(1, owner->baseForm->GetFormID()))) {
				CallUDF(callback.script, nullptr, OnTakeBackItemHandler->numMaxArgs, owner, item, quantity);
			}
		}
		ThisCall<TESObjectREFR*>(0x4C37D0, contChanges, player, item, keepOwner, quantity, xList, a9, target, a10, a11, a12, a13, cEntry);
	}

	template <uintptr_t a_addr>
	class RadioTuneOnHook {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  DWORD __cdecl Hook(TESObjectACTI* ref, DWORD mode) {
			auto res = CdeclCall<DWORD>(hookCall, ref, mode);
			HandleOnRadioPostSoundAttach(ref, mode);
			return res;
		}

		RadioTuneOnHook() {
			uintptr_t hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hookPoint, (uintptr_t)Hook);
		}
	};


	template <uintptr_t a_addr>
	class InputSwitchHook {
	private:
		static inline uintptr_t hookCall = a_addr;
	public:
		static  DWORD __fastcall Hook(InterfaceManager* r_man, void* edx, Tile* newTile, DWORD tileVal, DWORD doPlaySound) {
			Menu* curMen = ThisCall<Menu*>(0x720E60, r_man);
			bool fireEvent = r_man->activeTileAlt != newTile;
			auto res = ThisCall<DWORD>(hookCall, r_man, newTile, tileVal, doPlaySound);
			if (fireEvent) {
				HandleInputSwitch(r_man, curMen);
			}
			return res;
		}
		InputSwitchHook() {
			uintptr_t hookPoint = hookCall;
			hookCall = GetRelJumpAddr(hookCall);
			WriteRelCall(hookPoint, (uintptr_t)Hook);
		}
	};


	void __fastcall handleSleepWaitClick(SleepWaitMenu* menu, void* edx, int mode, void* tile)
	{
		ThisCall(0x7C0220, menu, mode, tile);
		if (mode == 4) {
			HandleOnSleepWait(menu, mode);
		}
	}

	void __stdcall HandleOnNPCResponse(DialogueResponse* npcResponse)
	{
		int emotionID = 0;
		int emotionValue = 0;
		int responseNumber = 0;
		const char* responseString = "";
		const char* voicePath = "";

		if (npcResponse)
		{
			emotionID = npcResponse->uiEmotionType;
			emotionValue = npcResponse->uiEmotionValue;
			responseNumber = npcResponse->uiResponseNumber;
			responseString = npcResponse->strResponseText.c_str();
			voicePath = npcResponse->strVoiceFilePath.c_str();
		}

		for (auto const& callback : OnNPCResponseHandler->callbacks) {
			auto filter = reinterpret_cast<FilterInt*>(callback.eventFilter);
			if (filter->IsInFilter(0, emotionID) || filter->IsInFilter(0, 0)) {
				CallUDF(callback.script, nullptr, OnNPCResponseHandler->numMaxArgs, responseString, voicePath, emotionID, emotionValue, responseNumber);
			}
		}
		return;
	}

	//Currently Displayed Text, Source Position, Target Reference (Usually Player)
	void __stdcall HandleOnGeneralSubtitle(char* apText, NiPoint3 akPos, TESObjectREFR* apTarget)
	{
		NiPoint3 pos = akPos;
		const char* subtitleString = apText ? apText : "";
		float x = pos.x;
		float y = pos.y;
		float z = pos.z;

		TESObjectREFR* player = apTarget ? apTarget : nullptr;

		for (auto const& callback : OnGeneralSubtitleHandler->callbacks) {
			auto filter = reinterpret_cast<FilterForm*>(callback.eventFilter);
			if (filter->IsInFilter(0, player) || filter->IsInFilter(0, 0)) {
				CallUDF(callback.script, nullptr, OnGeneralSubtitleHandler->numMaxArgs, subtitleString, player, *(uint32_t*)&x, *(uint32_t*)&y, *(uint32_t*)&z);
			}
		}
		return;
	}

	void __fastcall HandleOnReputationChange(TESReputation* apRep) {
		for (auto const& callback : OnReputationChangeHandler->callbacks) {
			float fPos = apRep->fPositiveReputation;
			float fNeg = apRep->fNegativeReputation;
			auto filter = reinterpret_cast<FilterForm*>(callback.eventFilter);
			if (filter->IsBaseInFilter(0, apRep)) {
				CallUDF(callback.script, nullptr, OnReputationChangeHandler->numMaxArgs, apRep, *(uint32_t*)&fPos, *(uint32_t*)&fNeg);
			}
		}
	}

	//Fires when general subtitles are sent to the HUD.
	bool __fastcall HandleOnGeneralSubtitleEvent(HUDMainMenu* thisPtr, void* edx, char* apText, BSSoundHandle akSound, NiPoint3 akPos, TESObjectREFR* apTarget, bool abInstant)
	{
		if (apText) HandleOnGeneralSubtitle(apText, akPos, apTarget);

		return ThisCall<bool>(0x774FD0, thisPtr, apText, akSound, akPos, apTarget, abInstant);
	}

	bool __fastcall HandleOnNPCResponseEvent(MenuTopic* apThis) {
		if (apThis->pFirstResponse) {
			HandleOnNPCResponse(apThis->pFirstResponse->GetItem());
			apThis->pFirstResponse = apThis->pFirstResponse->GetNext();
		}
		return apThis->pFirstResponse && apThis->pFirstResponse->GetItem();
	}

	void __fastcall HandleOnReputationChangeEvent(TESReputation* apThis, void* edx, uint32_t auiChangeFlag)
	{
		if (auiChangeFlag & 2)
			HandleOnReputationChange(apThis);

		ThisCall(0x484B60, apThis, auiChangeFlag);
	}


	void RegisterOnNPCActorValueChange(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		if (OnNPCAVChangeHandler) {
			if (toggle)
				OnNPCAVChangeHandler->RegisterEvent(script, filters, userFlags);
			else OnNPCAVChangeHandler->RemoveEvent(script, filters);
		}
	}

	void RegisterOnTakeBackItem(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		if (OnTakeBackItemHandler) {
			if (toggle)
				OnTakeBackItemHandler->RegisterEvent(script, filters);
			else OnTakeBackItemHandler->RemoveEvent(script, filters);
		}
	}

	void Install() {
		OnDyingHandler = JGCreateEvent("OnDying", 1, 1);
		OnStartQuestHandler = JGCreateEvent("OnStartQuest", 1, 1);
		OnStopQuestHandler = JGCreateEvent("OnStopQuest", 1, 1);
		OnSeenDataUpdateHandler = JGCreateEvent("OnSeenDataUpdate", 1, 1);
		OnLimbGoneHandler = JGCreateEvent("OnLimbGone", 2, 2, FilterFormInt::Create);
		OnChallengeCompleteHandler = JGCreateEvent("OnChallengeComplete", 1, 1);
		OnCrosshairHandler = JGCreateEvent("OnCrosshair", 1, 2, FilterFormInt::Create);
		OnCompleteQuestHandler = JGCreateEvent("OnCompleteQuest", 1, 1);
		OnFailQuestHandler = JGCreateEvent("OnFailQuest", 1, 1);
		OnSettingsUpdateHandler = JGCreateEvent("OnSettingsUpdate", 0, 0);
		OnAddPerkHandler = JGCreateEvent("OnAddPerk", 3, 1);
		OnRemovePerkHandler = JGCreateEvent("OnRemovePerk", 1, 1);
		OnAVChangeHandler = JGCreateEvent("OnActorValueChange", 3, 2, FilterFormInt::Create);
		OnPLChangeHandler = JGCreateEvent("OnProcessLevelChange", 3, 2, FilterFormInt::Create);
		OnRadioPostSoundAttachHandler = JGCreateEvent("OnRadioPostSoundAttach", 2, 1);
		OnKeyboardControllerSelectionChangeHandler = JGCreateEvent("OnKeyboardControllerSelectionChange", 1, 1, FilterInt::Create);
		OnSleepWaitEventHandler = JGCreateEvent("OnSleepWaitEventHandler", 1, 1, FilterInt::Create);
		OnTakeBackItemHandler = JGCreateEvent("OnTakeBackItem", 3, 2);
		OnNPCResponseHandler = JGCreateEvent("OnNPCResponse", 5, 1, FilterInt::Create);
		OnGeneralSubtitleHandler = JGCreateEvent("OnGeneralSubtitle", 5, 1, FilterFormInt::Create);
		OnReputationChangeHandler = JGCreateEvent("OnReputationChangeHandler", 3, 1);
		OnNPCAVChangeHandler = JGCreateEvent("OnNPCActorValueChangeHandler", 4, 2, FilterFormInt::Create);

		CallUDF = g_scriptInterface->CallFunctionAlt;
		WriteRelCall(0x55678A, (uint32_t)HandleSeenDataUpdateEvent);
		WriteRelCall(0x557053, (uint32_t)HandleSeenDataUpdateEvent);
		WriteRelJump(0x89F4A4, (uint32_t)OnDyingEventAsm);
		WriteRelJump(0x60CA24, (uint32_t)OnQuestStartStopEventAsm);
		WriteRelCall(0x572FF1, (uint32_t)HandleLimbGoneEvent);
		WriteRelCall(0x5F5C78, (uint32_t)HandleChallengeCompleteEvent);
		WriteRelCall(0x5F6222, (uint32_t)HandleChallengeCompleteEvent);
		WriteRelCall(0x776010, (uint32_t)handleCrosshairEvent);
		WriteRelCall(0x60CB5A, (uint32_t)handleQuestFail);
		WriteRelCall(0x60CA78, (uint32_t)handleQuestComplete);
		WriteRelCall(0x7D6D73, (uint32_t)handleSettingsUpdate);
		WriteRelCall(0x5D4E5B, (uint32_t)handleAddPerkEvent);
		WriteRelCall(0x7865BD, (uint32_t)handleAddPerkEvent);
		WriteRelCall(0x7E772D, (uint32_t)handleAddPerkEvent);
		SafeWriteBuf(0x7E7732, "\x0F\x1F\x00", 3);
		SafeWriteBuf(0x7865C2, "\x0F\x1F\x00", 3);
		SafeWriteBuf(0x5D4E60, "\x0F\x1F\x00", 3);
		WriteRelCall(0x5D4F89, (uint32_t)handleRemovePerkEvent);
		SafeWriteBuf(0x5D4F8E, "\x0F\x1F\x00", 3);
		SafeWrite8(0x60CA29, 0xCC);
		WriteRelJump(0x66EE50, (uint32_t)AVChangeEventAsm);
		// Process Level change: MoveToHigh
		SafeWrite32(0x108AC7C, (uint32_t)HandlePLChangeEvent<0x881D30>);
		SafeWrite32(0x10872EC, (uint32_t)HandlePLChangeEvent<0x881D30>);
		SafeWrite32(0x1086CAC, (uint32_t)HandlePLChangeEvent<0x881D30>);
		SafeWrite32(0x1084494, (uint32_t)HandlePLChangeEvent<0x881D30>);
		// MoveToLow
		SafeWrite32(0x108AC80, (uint32_t)HandlePLChangeEvent<0x882B90>);
		SafeWrite32(0x10872F0, (uint32_t)HandlePLChangeEvent<0x882B90>);
		SafeWrite32(0x1086CB0, (uint32_t)HandlePLChangeEvent<0x882B90>);
		SafeWrite32(0x1084498, (uint32_t)HandlePLChangeEvent<0x882B90>);
		// MoveToMiddleLow
		SafeWrite32(0x108AC84, (uint32_t)HandlePLChangeEvent<0x883240>);
		SafeWrite32(0x10872F4, (uint32_t)HandlePLChangeEvent<0x883240>);
		SafeWrite32(0x1086CB4, (uint32_t)HandlePLChangeEvent<0x883240>);
		SafeWrite32(0x108449C, (uint32_t)HandlePLChangeEvent<0x883240>);
		// MoveToMiddleHigh
		SafeWrite32(0x108AC88, (uint32_t)HandlePLChangeEvent<0x883800>);
		SafeWrite32(0x10872F8, (uint32_t)HandlePLChangeEvent<0x883800>);
		SafeWrite32(0x1086CB8, (uint32_t)HandlePLChangeEvent<0x883800>);
		SafeWrite32(0x10844A0, (uint32_t)HandlePLChangeEvent<0x883800>);

		// Keyboard/Controller selection change
		InputSwitchHook<0x0718059>();
		InputSwitchHook<0x0715CD5>();

		//Radio
		RadioTuneOnHook<0x511816>();
		RadioTuneOnHook<0x579C64>();
		RadioTuneOnHook<0x57A23A>();

		SafeWrite32(0x10763B8, (uint32_t)handleSleepWaitClick);

		//testing
		OnRenderGamePreUpdateHandler = JGCreateEvent("OnRenderGamePreUpdateHandler", 0, 0, nullptr);
		WriteRelCall(0x943748, (uintptr_t)handlePreRenderEvent);
		OnRenderGameModeUpdateHandler = JGCreateEvent("OnRenderGameModeUpdateHandler", 0, 0, nullptr);
		WriteRelCall(0x870244, (uintptr_t)handlerRenderGameEvent);
		OnRenderRenderedMenuUpdateHandler = JGCreateEvent("OnRenderRenderedMenuUpdateHandler", 0, 0, nullptr);
		WriteRelCall(0x8702A9, (uintptr_t)handlerRenderMenuEvent);

		WriteRelCall(0x4CB976, (uint32_t)HandleTakeBackItem);
		WriteRelCall(0x8F24A1, (uint32_t)GetExtraDataListHook);

		WriteRelCall(0x7630FD, (uint32_t)HandleOnNPCResponseEvent);

		//HUDMainMenu::AppendSubtitleData() called by Interface::ShowText()
		WriteRelCall(0x7052B8, (uint32_t)HandleOnGeneralSubtitleEvent);

		SafeWrite32(0x104BA6C, (uint32_t)HandleOnReputationChangeEvent);
	}

	void Reset()
	{
		OnDyingHandler->FlushEventCallbacks();
		OnLimbGoneHandler->FlushEventCallbacks();
		OnCrosshairHandler->FlushEventCallbacks();
		OnPLChangeHandler->FlushEventCallbacks();
		hkOwner = nullptr;
	}

	void Update() {
		for (const auto& EventInfo : EventInfos) {
			EventInfo->AddQueuedEvents();
			EventInfo->DeleteEvents();
		}
	}

	void Register(EventInformation* eventInfo, Script* script, void** filters, bool toggle, uint32_t userFlags = 0)
	{
		if (eventInfo) {
			if (toggle)
				eventInfo->RegisterEvent(script, filters, userFlags);
			else eventInfo->RemoveEvent(script, filters);
		}
	}

	void RegisterOnDying(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnDyingHandler, script, filters, toggle);
	}

	void RegisterOnStartQuest(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnStartQuestHandler, script, filters, toggle);
	}

	void RegisterOnStopQuest(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnStopQuestHandler, script, filters, toggle);
	}

	void RegisterOnFailQuest(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnFailQuestHandler, script, filters, toggle);
	}

	void RegisterOnCompleteQuest(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnCompleteQuestHandler, script, filters, toggle);
	}

	void RegisterOnSeenDataUpdate(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnSeenDataUpdateHandler, script, filters, toggle);
	}

	void RegisterOnLimbGone(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnLimbGoneHandler, script, filters, toggle);
	}
	void RegisterOnChallengeComplete(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnChallengeCompleteHandler, script, filters, toggle);
	}
	void RegisterOnCrosshair(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnCrosshairHandler, script, filters, toggle);
	}
	void RegisterOnSettingsUpdate(Script* script, bool toggle, uint32_t userFlags)
	{
		Register(OnSettingsUpdateHandler, script, nullptr, toggle);
	}
	void RegisterOnAddPerk(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnAddPerkHandler, script, filters, toggle);
	}
	void RegisterOnRemovePerk(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnRemovePerkHandler, script, filters, toggle);
	}
	void RegisterOnActorValueChange(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnAVChangeHandler, script, filters, toggle, userFlags);
	}

	void RegisterOnProcessLevelChange(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnPLChangeHandler, script, filters, toggle);
	}

	void RegisterOnRadioPostSoundAttach(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnRadioPostSoundAttachHandler, script, filters, toggle);
	}

	void RegisterOnInputSwitch(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnKeyboardControllerSelectionChangeHandler, script, filters, toggle);
	}

	void RegisterOnSleepWait(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnSleepWaitEventHandler, script, filters, toggle);
	}

	enum EnumFlags {
		kDoNotFireInRenderMenu = 1 << 0,
		kDoNotFireInGameMode = 1 << 1,
		kUseGamePreEvent = 1 << 2,
	};

	void RegisterOnRender(Script* script, bool toggle, uint32_t userFlags)
	{
		if (!(userFlags & kDoNotFireInGameMode) && OnRenderGameModeUpdateHandler) {
			if (!(userFlags & kUseGamePreEvent)) {
				if (toggle)
					OnRenderGameModeUpdateHandler->RegisterEvent(script, nullptr);
				else OnRenderGameModeUpdateHandler->RemoveEvent(script, nullptr);
			}
			else if (OnRenderGamePreUpdateHandler) {
				if (toggle)
					OnRenderGamePreUpdateHandler->RegisterEvent(script, nullptr);
				else OnRenderGamePreUpdateHandler->RemoveEvent(script, nullptr);
			}
		}

		if (!(userFlags & kDoNotFireInRenderMenu) && OnRenderRenderedMenuUpdateHandler) {
			if (toggle)
				OnRenderRenderedMenuUpdateHandler->RegisterEvent(script, nullptr);
			else OnRenderRenderedMenuUpdateHandler->RemoveEvent(script, nullptr);
		}
	}

	void RegisterOnNPCResponse(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnNPCResponseHandler, script, filters, toggle);
	}

	void RegisterOnGeneralSubtitle(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnGeneralSubtitleHandler, script, filters, toggle);
	}

	void RegisterOnReputationChange(Script* script, void** filters, bool toggle, uint32_t userFlags)
	{
		Register(OnReputationChangeHandler, script, filters, toggle);
	}
}

