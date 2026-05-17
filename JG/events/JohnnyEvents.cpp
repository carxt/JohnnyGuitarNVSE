#include "JohnnyEvents.h"
#include "EventFramework.h"
#include "GameProcess.h"
#include "decoding.h"
#include <internal/Game/Bethesda/DialogueResponse.hpp>
#include <internal/Game/Bethesda/MenuTopic.hpp>


extern NVSEScriptInterface* g_scriptInterface;
extern NVSEMessagingInterface* g_msgInterface;
extern uint32_t g_pluginHandle;

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

	enum JG_NVSE_MESSAGE_ID : uint32_t {
		JG_EVENT_BASE = 10000,

		JG_OnDying,
		JG_OnStartQuest,
		JG_OnStopQuest,
		JG_OnFailQuest,
		JG_OnCompleteQuest,
		JG_OnSeenDataUpdate,
		JG_OnLimbGone,
		JG_OnChallengeComplete,
		JG_OnCrosshair,
		JG_OnSettingsUpdate,
		JG_OnAddPerk,
		JG_OnRemovePerk,
		JG_OnRenderGamePreUpdate,
		JG_OnRenderGameModeUpdate,
		JG_OnRenderRenderedMenuUpdate,
		JG_OnAVChange,
		JG_OnPLChange,
		JG_OnRadioPostSoundAttach,
		JG_OnKeyboardControllerSelectionChange,
		JG_OnSleepWaitEvent,
		JG_OnTakeBackItem,
		JG_OnNPCResponse,
		JG_OnGeneralSubtitle,
		JG_OnReputationChange,
		JG_OnNPCAVChange,
	};

	template<typename T>
	inline void __fastcall SendNVSEMessage(JG_NVSE_MESSAGE_ID aeID, T& arData) {
		g_msgInterface->Dispatch(g_pluginHandle, aeID, &arData, sizeof(T), nullptr);
	}

	inline void __fastcall SendNVSEMessage(JG_NVSE_MESSAGE_ID aeID) {
		g_msgInterface->Dispatch(g_pluginHandle, aeID, nullptr, 0, nullptr);
	}

	bool HandlePreRenderEvent() {
		SendNVSEMessage(JG_OnRenderGamePreUpdate);
		for (auto const& rCallback : OnRenderGamePreUpdateHandler->callbacks) {
			CallUDF(rCallback.script, nullptr, OnRenderGamePreUpdateHandler->numMaxArgs);
		}
		return CdeclCall<bool>(0x7050D0);
	}

	void __fastcall HandleRemovePerkEvent(Actor* apActor, int EDX, BGSPerk* apPerk, bool abTeammate) {
		if (!apActor->GetPerkRank(apPerk, abTeammate))
			return;

		{
			struct EventData {
				Actor*		pActor;
				BGSPerk*	pPerk;
				bool		bCompanion;
			} kData(apActor, apPerk, abTeammate);
			SendNVSEMessage(JG_OnRemovePerk, kData);
		}

		for (auto const& rCallback : OnRemovePerkHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apPerk)) {
				CallUDF(rCallback.script, apActor, OnRemovePerkHandler->numMaxArgs, apPerk);
			}
		}
		apActor->RemovePerk(apPerk, abTeammate);
	}

	void __fastcall HandleAddPerkEvent(Actor* apActor, int EDX, BGSPerk* apPerk, uint8_t aucRank, bool abTeammate) {

		{
			struct EventData {
				Actor*		pActor;
				BGSPerk*	pPerk;
				bool		bCompanion;
				uint8_t		ucRank;
			} kData(apActor, apPerk, abTeammate, aucRank);
			SendNVSEMessage(JG_OnAddPerk, kData);
		}

		for (auto const& rCallback : OnAddPerkHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apPerk)) {
				CallUDF(rCallback.script, apActor, OnAddPerkHandler->numMaxArgs, apPerk, aucRank - 1, aucRank);
			}
		}
		apActor->SetPerkRank(apPerk, aucRank, abTeammate);
	}

	void __stdcall HandleDyingEvent(Actor* apActor) {
		if (apActor->IsActor() && apActor->lifeState == 1) {

			SendNVSEMessage(JG_OnAddPerk, apActor);

			if ((apActor->GetFullName()[0] || apActor == PlayerCharacter::GetSingleton())) {
				for (auto const& rCallback : OnDyingHandler->callbacks) {
					if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apActor)) {
						CallUDF(rCallback.script, nullptr, OnDyingHandler->numMaxArgs, apActor);
					}
				}
			}
		}
	}

	uint32_t __fastcall HandleCrosshairEvent(TESObjectREFR* apRef) {
		if (apRef) {
			SendNVSEMessage(JG_OnCrosshair, apRef);

			for (auto const& rCallback : OnCrosshairHandler->callbacks) {
				FilterFormInt* pFilter = reinterpret_cast<FilterFormInt*>(rCallback.eventFilter);
				if ((pFilter->IsInFilter(0, apRef->GetFormID()) || pFilter->IsInFilter(0, apRef->baseForm->GetFormID())) && pFilter->IsInFilter(1, apRef->baseForm->GetFormType())) {
					CallUDF(rCallback.script, nullptr, OnCrosshairHandler->numMaxArgs, apRef);
				}
			}
		}
		return ThisCall<uint32_t>(0x579280, apRef);
	}
	bool __fastcall HandleLimbGoneEvent(ExtraDismemberedLimbs* apLimbData, void*, Actor* apActor, uint32_t aeLimb, bool abExplodedLimb) {

		{
			struct EventData {
				Actor*					pActor;
				ExtraDismemberedLimbs*	pLimbData;
				uint32_t				eLimb;
				bool					bExploded;
			} kData(apActor, apLimbData, aeLimb, abExplodedLimb);
			SendNVSEMessage(JG_OnLimbGone, kData);
		}

		for (auto const& rCallback : OnLimbGoneHandler->callbacks) {
			FilterFormInt* pFilter = reinterpret_cast<FilterFormInt*>(rCallback.eventFilter);
			if ((pFilter->IsInFilter(0, apActor->GetFormID()) || pFilter->IsInFilter(0, apActor->baseForm->GetFormID())) && pFilter->IsInFilter(1, aeLimb)) {
				CallUDF(rCallback.script, nullptr, OnLimbGoneHandler->numMaxArgs, apActor, aeLimb);
			}
		}
		return ThisCall<bool>(0x430410, apLimbData, apActor, aeLimb, abExplodedLimb);
	}

	void __fastcall HandleQuestStartStop(TESQuest* apQuest, bool abStarted) {
		SendNVSEMessage(abStarted ? JG_OnStartQuest : JG_OnStopQuest, apQuest);

		const EventInformation* pEvent = abStarted ? OnStartQuestHandler : OnStopQuestHandler;
		for (auto const& rCallback : pEvent->callbacks) {
			if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apQuest)) {
				CallUDF(rCallback.script, nullptr, pEvent->numMaxArgs, apQuest);
			}
		}
	}

	void __cdecl HandleQuestComplete(TESQuest* apQuest) {
		SendNVSEMessage(JG_OnCompleteQuest, apQuest);

		for (auto const& rCallback : OnCompleteQuestHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apQuest)) {
				CallUDF(rCallback.script, nullptr, OnCompleteQuestHandler->numMaxArgs, apQuest);
			}
		}
		CdeclCall(0x77A480, apQuest);
	}

	void __cdecl HandleQuestFail(TESQuest* apQuest) {
		SendNVSEMessage(JG_OnFailQuest, apQuest);

		for (auto const& rCallback : OnFailQuestHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apQuest)) {
				CallUDF(rCallback.script, nullptr, OnFailQuestHandler->numMaxArgs, apQuest);
			}
		}
		CdeclCall(0x77A480, apQuest);
	}

	void* __cdecl HandleSettingsUpdate() {
		SendNVSEMessage(JG_OnSettingsUpdate);

		for (auto const& rCallback : OnSettingsUpdateHandler->callbacks) {
			CallUDF(rCallback.script, nullptr, OnSettingsUpdateHandler->numMaxArgs);
		}
		return CdeclCall<void*>(0x45D180);
	}

	ExtraDataList* __fastcall HandleSeenDataUpdateEvent(TESObjectCELL* apCell) {
		SendNVSEMessage(JG_OnSeenDataUpdate, apCell);

		for (auto const& rCallback : OnSeenDataUpdateHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apCell)) {
				CallUDF(rCallback.script, nullptr, OnSeenDataUpdateHandler->numMaxArgs, apCell);
			}
		}
		return &apCell->extraDataList;
	}

	uint32_t __fastcall HandleChallengeCompleteEvent(TESChallenge* apChallenge) {
		SendNVSEMessage(JG_OnChallengeComplete, apChallenge);

		for (auto const& rCallback : OnChallengeCompleteHandler->callbacks) {
			if (reinterpret_cast<FilterForm*>(rCallback.eventFilter)->IsBaseInFilter(0, apChallenge)) {
				CallUDF(rCallback.script, nullptr, OnChallengeCompleteHandler->numMaxArgs, apChallenge);
			}
		}
		return apChallenge->data.type;
	}

	void __fastcall HandleRenderGameEvent(void* apMain, void*, BSRenderedTexture* apDestination, bool abRenderedMenuMode, bool abSkipFirstPerson) {

		{
			struct EventData {
				BSRenderedTexture*		pTexture;
				bool					bRenderedMenu;
				bool					bSkipFirstPerson;
			} kData(apDestination, abRenderedMenuMode, abSkipFirstPerson);
			SendNVSEMessage(JG_OnRenderGameModeUpdate, kData);
		}

		for (auto const& rCallback : OnRenderGameModeUpdateHandler->callbacks) {
			CallUDF(rCallback.script, nullptr, OnRenderGameModeUpdateHandler->numMaxArgs);
		}
		ThisCall(0x8706B0, apMain, apDestination, abRenderedMenuMode, abSkipFirstPerson);
	}

	void __fastcall HandleRenderMenuEvent(void* apMain, void*, BSRenderedTexture* apDestination, bool abRenderedMenuMode, bool abSkipFirstPerson) {

		{
			struct EventData {
				BSRenderedTexture*		pTexture;
				bool					bRenderedMenu;
				bool					bSkipFirstPerson;
			} kData(apDestination, abRenderedMenuMode, abSkipFirstPerson);
			SendNVSEMessage(JG_OnRenderRenderedMenuUpdate, kData);
		}

		for (auto const& rCallback : OnRenderRenderedMenuUpdateHandler->callbacks) {
			CallUDF(rCallback.script, nullptr, OnRenderRenderedMenuUpdateHandler->numMaxArgs);
		}
		ThisCall(0x8706B0, apMain, apDestination, abRenderedMenuMode, abSkipFirstPerson);
	}

	inline static bool __fastcall CompareFloats(float a, float b) {
		constexpr float fEpsilon = 0.0001f;
		return fabs(a - b) < fEpsilon;
	}

	void __stdcall HandleAVChangeEvent(ActorValueOwner* apActor, uint32_t aeActorValue, float afPreviousValue, float afModValue, void* apChangeCallback) {
		if (apChangeCallback == nullptr)
			afPreviousValue = apActor->GetActorValueF(aeActorValue) - afModValue;

		const float fNewValue = afPreviousValue + afModValue;
		const float fPreviousValue = afPreviousValue;

		const float fNewValueFloor = floor(fNewValue);
		const float fPreviousValueFloor = floor(fPreviousValue);

		TESForm* pForm = apActor->GetAsForm();
		if (pForm && !CompareFloats(fNewValueFloor, fPreviousValueFloor)) {
			Actor* pActor = pForm->IsActor() ? static_cast<Actor*>(pForm) : nullptr;

			{
				struct EventData {
					TESForm*	pForm;
					float		fNewValue;
					float		fPreviousValue;
				} kData(pForm, fNewValue, fPreviousValue);
				SendNVSEMessage(JG_OnAVChange, kData);
			}

			if (pActor && pActor->IsPlayerRef()) {
				for (auto const& rCallback : OnAVChangeHandler->callbacks) {
					FilterFormInt* pFilter = reinterpret_cast<FilterFormInt*>(rCallback.eventFilter);
					if (pFilter->IsInFilter(1, aeActorValue)) {

						bool bFullValues = rCallback.UserFlags.Get(1);

						const float& fNewVal = bFullValues ? fNewValue : fNewValueFloor;
						const float& fPrevVal = bFullValues ? fPreviousValue : fPreviousValueFloor;

						CallUDF(rCallback.script, nullptr, OnAVChangeHandler->numMaxArgs, aeActorValue, *(uint32_t*)&fPrevVal, *(uint32_t*)&fNewVal);
					}
				}
			}
			else {
				for (auto const& rCallback : OnNPCAVChangeHandler->callbacks) {
					FilterFormInt* pFilter = reinterpret_cast<FilterFormInt*>(rCallback.eventFilter);
					if (pFilter->IsInFilter(1, aeActorValue) && (pFilter->IsInFilter(0, pForm->GetFormID()) || (pActor && pFilter->IsInFilter(0, pActor->GetBaseForm()->GetFormID())))) {

						bool bFullValues = rCallback.UserFlags.Get(1);

						const float& fNewVal = bFullValues ? fNewValue : fNewValueFloor;
						const float& fPrevVal = bFullValues ? fPreviousValue : fPreviousValueFloor;

						CallUDF(rCallback.script, nullptr, OnNPCAVChangeHandler->numMaxArgs, pForm, aeActorValue, *(uint32_t*)&fPrevVal, *(uint32_t*)&fNewVal);
					}
				}
			}
		}
	}

	template <uint32_t originalCall>
	bool __fastcall HandlePLChangeEvent(Actor* apActor) {
		if (apActor == nullptr || apActor->baseProcess == nullptr) [[unlikely]]
			return true; //early exit, no need to  error states because there's no baseProcess.

		const uint32_t eOldLevel = apActor->baseProcess->processLevel;
		const bool bResult = ThisCall<bool>(originalCall, apActor);
		const uint32_t eNewLevel = apActor->baseProcess->processLevel;
		if (eOldLevel != eNewLevel) {

			{
				struct EventData {
					Actor*		pActor;
					uint32_t	eOldLevel;
					uint32_t	eNewLevel;
				} kData(apActor, eOldLevel, eNewLevel);
				SendNVSEMessage(JG_OnPLChange, kData);
			}

			for (auto const& rCallback : OnPLChangeHandler->callbacks) {
				FilterFormInt* pFilter = reinterpret_cast<FilterFormInt*>(rCallback.eventFilter);
				if ((pFilter->IsInFilter(0, apActor->GetFormID()) || pFilter->IsInFilter(0, apActor->GetBaseForm()->GetFormID())) && pFilter->IsInFilter(1, eNewLevel)) {
					CallUDF(rCallback.script, nullptr, OnPLChangeHandler->numMaxArgs, apActor, eOldLevel, eNewLevel);
				}
			}
		}
		return bResult;
	}

	void __fastcall HandleOnRadioPostSoundAttach(TESObjectACTI* apRadio, bool abActive) {
		if (!apRadio) 
			return;

		{
			struct EventData {
				TESObjectACTI*	pRadio;
				bool			bActive;
			} kData(apRadio, abActive);
			SendNVSEMessage(JG_OnRadioPostSoundAttach, kData);
		}

		for (auto const& rCallback : OnRadioPostSoundAttachHandler->callbacks) {
			FilterForm* pFilter = reinterpret_cast<FilterForm*>(rCallback.eventFilter);
			if (pFilter->IsBaseInFilter(0, apRadio)) {
				CallUDF(rCallback.script, nullptr, OnRadioPostSoundAttachHandler->numMaxArgs, apRadio, abActive ? 1u : 0u);
			}
		}
	}


	void __fastcall HandleInputSwitch(InterfaceManager* apManager, Menu* apMenu) {
		SendNVSEMessage(JG_OnKeyboardControllerSelectionChange, apMenu);

		const uint32_t uiMenuID = apMenu ? apMenu->GetID() : -1;
		for (auto const& rCallback : OnKeyboardControllerSelectionChangeHandler->callbacks) {
			auto pFilter = reinterpret_cast<FilterInt*>(rCallback.eventFilter);
			if (pFilter->IsInFilter(0, uiMenuID) || pFilter->IsInFilter(0, 0)) {
				CallUDF(rCallback.script, nullptr, OnKeyboardControllerSelectionChangeHandler->numMaxArgs, uiMenuID);
			}
		}
	}


	void __fastcall HandleOnSleepWait(SleepWaitMenu* apMenu, uint32_t auiTileID) {
		SendNVSEMessage(JG_OnSleepWaitEvent, apMenu);

		for (auto const& rCallback : OnSleepWaitEventHandler->callbacks) {
			auto pFilter = reinterpret_cast<FilterInt*>(rCallback.eventFilter);
			if (pFilter->IsInFilter(0, uint32_t(apMenu->isRest) + 1) || pFilter->IsInFilter(0, 0)) {
				CallUDF(rCallback.script, nullptr, OnSleepWaitEventHandler->numMaxArgs, (int(apMenu->isRest) + 1));
			}
		}
	}

	__declspec(naked) void __cdecl AVChangeEventAsm(ActorValueOwner* avOwner, uint32_t avCode, float prevVal, float newVal, ActorValueOwner* attacker) {
		__asm {
			push    ebp
			mov     ebp, esp
			mov     eax, [ebp + 0xC]
			cmp     eax, 0x4D
			jnb     DONE
			mov     ecx, ds:0x11D61C8[eax * 4]
			test    ecx, ecx
			jz      DONE
			push    ecx
			mov		ecx, dword ptr[ecx + 0x54]
			push	ecx
			mov     ecx, [ebp + 8]
			push    dword ptr[ebp + 0x14]
			push    dword ptr[ebp + 0x10]
			push    eax
			push    dword ptr[ebp + 0x08]
			call    HandleAVChangeEvent
			mov     ecx, [ebp - 4]
			cmp     dword ptr[ecx + 0x54], 0
			jz      DONE
			mov     eax, 0x66EE72
			jmp     eax
			DONE:
			leave
			retn
		}
	}

	__declspec(naked) void OnCrosshairEventAsm() {
		static constexpr uint32_t retnAddr = 0x775A69;
		__asm {
			mov		ecx, [ebp + 0x8]
			call	HandleCrosshairEvent
			movzx	ecx, [ebp + 0x10]
			test	ecx, ecx
			jmp		retnAddr
		}
	}
	__declspec (naked) void OnDyingEventAsm() {
		static constexpr uint32_t checkProtect = 0xEC408C;
		__asm {
			push	dword ptr[ebp - 0x18]
			call	HandleDyingEvent
			mov		ecx, dword ptr ss : [ebp - 0xC]
			mov		dword ptr fs : [0] , ecx
			pop		ecx
			pop		esi
			mov		ecx, dword ptr ss : [ebp - 0x14]
			xor		ecx, ebp
			call	checkProtect
			mov		esp, ebp
			pop		ebp
			mov		esp, ebx
			pop		ebx
			retn	8
		}
	}

	__declspec (naked) void OnQuestStartStopEventAsm() {
		__asm {
			mov		ecx, dword ptr[ebp - 4]
			mov		dl, byte ptr[ebp + 8]
			call	HandleQuestStartStop
			mov		esp, ebp
			pop		ebp
			ret		4
		}
	}

	TESObjectREFR* pItemOwnerRef = nullptr;

	ExtraDataList* __fastcall GetExtraDataListHook(TESObjectREFR* apRef) {
		pItemOwnerRef = apRef;
		return &apRef->extraDataList;
	}

	TESObjectREFR* __fastcall HandleTakeBackItem(InventoryChanges* apInvChanges, void*, TESObjectREFR* apRef, TESBoundObject* apObject, bool abStealing, int32_t aiNumber, ExtraDataList* apExtraList, bool abDropWorld, TESObjectREFR* apOtherContainer, const NiPoint3* apPoint, const NiPoint3* apRotate, bool abDelete, bool abPreferStolen, ItemChange* apItemChange) {
		TESObjectREFR* pOwner = apOtherContainer->IsActor() ? apOtherContainer : pItemOwnerRef;

		{
			struct EventData {
				TESObjectREFR*	pOwner;
				TESBoundObject* pObject;
				int32_t			iCount;
			} kData(pOwner, apObject, aiNumber);
			SendNVSEMessage(JG_OnTakeBackItem, kData);
		}

		for (auto const& rCallback : OnTakeBackItemHandler->callbacks) {
			auto pFilter = reinterpret_cast<FilterForm*>(rCallback.eventFilter);
			if (pFilter->IsBaseInFilter(0, apObject) && (pFilter->IsInFilter(1, pOwner->GetFormID()) || pFilter->IsInFilter(1, pOwner->baseForm->GetFormID()))) {
				CallUDF(rCallback.script, nullptr, OnTakeBackItemHandler->numMaxArgs, pOwner, apObject, aiNumber);
			}
		}
		return ThisCall<TESObjectREFR*>(0x4C37D0, apInvChanges, apRef, apObject, abStealing, aiNumber, apExtraList, abDropWorld, apOtherContainer, apPoint, apRotate, abDelete, abPreferStolen, apItemChange);
	}

	template <uintptr_t auiAddress>
	class RadioTuneOnHook {
	private:
		static inline CallDetour kDetour;
	public:
		static void  __cdecl Hook(TESObjectACTI* apRef, bool abActive) {
			CdeclCall(kDetour.GetOverwrittenAddr(), apRef, abActive);
			HandleOnRadioPostSoundAttach(apRef, abActive);
		}

		RadioTuneOnHook() {
			kDetour.ReplaceCall(auiAddress, Hook);
		}
	};

	template <uintptr_t auiAddress>
	class InputSwitchHook {
	private:
		static inline CallDetour kDetour;
	public:
		static void __fastcall Hook(InterfaceManager* apInterfaceManager, void*, Tile* apTarget, int32_t aiType, bool abPlaySounds) {
			void* pMenuManager = CdeclCall<void*>(0x71E290, true);
			Menu* pFrontmostMenu = ThisCall<Menu*>(0x720E60, pMenuManager); // MenuManager::GetFrontmostMenu
			const bool bFireEvent = apInterfaceManager->activeTileAlt != apTarget;
			ThisCall(kDetour.GetOverwrittenAddr(), apInterfaceManager, apTarget, aiType, abPlaySounds);
			if (bFireEvent)
				HandleInputSwitch(apInterfaceManager, pFrontmostMenu);
		}
		InputSwitchHook() {
			kDetour.ReplaceCall(auiAddress, Hook);
		}
	};

	void __fastcall HandleSleepWaitClick(SleepWaitMenu* apMenu, void*, uint32_t auiTileID, Tile* apTarget) {
		ThisCall(0x7C0220, apMenu, auiTileID, apTarget);
		if (auiTileID == 4)
			HandleOnSleepWait(apMenu, auiTileID);
	}

	void __fastcall HandleOnNPCResponse(DialogueResponse* apResponse) {
		struct EventData {
			uint32_t	uiEmotionID = 0;
			uint32_t	uiEmotionValue = 0;
			uint32_t	uiResponseNumber = 0;
			const char* pResponseString = "";
			const char* pVoicePath = "";
		} kData;

		if (apResponse) {
			kData.uiEmotionID = apResponse->uiEmotionType;
			kData.uiEmotionValue = apResponse->uiEmotionValue;
			kData.uiResponseNumber = apResponse->uiResponseNumber;
			kData.pResponseString = apResponse->strResponseText.c_str();
			kData.pVoicePath = apResponse->strVoiceFilePath.c_str();
		}

		SendNVSEMessage(JG_OnNPCResponse, kData);

		for (auto const& rCallback : OnNPCResponseHandler->callbacks) {
			auto pFilter = reinterpret_cast<FilterInt*>(rCallback.eventFilter);
			if (pFilter->IsInFilter(0, kData.uiEmotionID) || pFilter->IsInFilter(0, 0)) {
				CallUDF(rCallback.script, nullptr, OnNPCResponseHandler->numMaxArgs, kData.pResponseString, kData.pVoicePath, kData.uiEmotionID, kData.uiEmotionValue, kData.uiResponseNumber);
			}
		}
	}

	//Currently Displayed Text, Source Position, Target Reference (Usually Player)
	void __fastcall HandleOnGeneralSubtitle(const char* apText, NiPoint3 akPos, TESObjectREFR* apTarget) {
		{
			struct EventData {
				const char*		pText;
				TESObjectREFR*	pTarget;
				NiPoint3		kPos;
			} kData(apText, apTarget, akPos);
			SendNVSEMessage(JG_OnGeneralSubtitle, kData);
		}

		const char* pSubtitleString = apText ? apText : "";
		const uint32_t uiX = *reinterpret_cast<uint32_t*>(&akPos.x);
		const uint32_t uiY = *reinterpret_cast<uint32_t*>(&akPos.y);
		const uint32_t uiZ = *reinterpret_cast<uint32_t*>(&akPos.z);

		for (auto const& rCallback : OnGeneralSubtitleHandler->callbacks) {
			auto pFilter = reinterpret_cast<FilterForm*>(rCallback.eventFilter);
			if (pFilter->IsInFilter(0, apTarget) || pFilter->IsInFilter(0, 0)) {
				CallUDF(rCallback.script, nullptr, OnGeneralSubtitleHandler->numMaxArgs, pSubtitleString, apTarget, uiX, uiY, uiZ);
			}
		}
		return;
	}

	void __fastcall HandleOnReputationChange(TESReputation* apRep) {
		{
			struct EventData {
				TESReputation*	pReputation;
				float			fPos;
				float			fNeg;
			} kData(apRep, apRep->fPositiveReputation, apRep->fNegativeReputation);
			SendNVSEMessage(JG_OnReputationChange, kData);
		}

		const uint32_t uiPos = *reinterpret_cast<uint32_t*>(&apRep->fPositiveReputation);
		const uint32_t uiNeg = *reinterpret_cast<uint32_t*>(&apRep->fNegativeReputation);
		for (auto const& rCallback : OnReputationChangeHandler->callbacks) {
			auto pFilter = reinterpret_cast<FilterForm*>(rCallback.eventFilter);
			if (pFilter->IsBaseInFilter(0, apRep)) {
				CallUDF(rCallback.script, nullptr, OnReputationChangeHandler->numMaxArgs, apRep, uiPos, uiNeg);
			}
		}
	}

	//Fires when general subtitles are sent to the HUD.
	bool __fastcall HandleOnGeneralSubtitleEvent(HUDMainMenu* apMenu, void*, const char* apText, BSSoundHandle akSound, NiPoint3 akPos, TESObjectREFR* apTarget, bool abInstant) {
		if (apText) 
			HandleOnGeneralSubtitle(apText, akPos, apTarget);

		return ThisCall<bool>(0x774FD0, apMenu, apText, akSound, akPos, apTarget, abInstant);
	}

	bool __fastcall HandleOnNPCResponseEvent(MenuTopic* apThis) {
		if (apThis->pFirstResponse) {
			HandleOnNPCResponse(apThis->pFirstResponse->GetItem());
			apThis->pFirstResponse = apThis->pFirstResponse->GetNext();
		}
		return apThis->pFirstResponse && apThis->pFirstResponse->GetItem();
	}

	void __fastcall HandleOnReputationChangeEvent(TESReputation* apThis, void*, uint32_t auiChangeFlag) {
		if (auiChangeFlag & 2)
			HandleOnReputationChange(apThis);

		ThisCall(0x484B60, apThis, auiChangeFlag);
	}

	void Install() {
		CallUDF = g_scriptInterface->CallFunctionAlt;

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

		WriteRelCall(0x55678A, HandleSeenDataUpdateEvent);
		WriteRelCall(0x557053, HandleSeenDataUpdateEvent);
		WriteRelJump(0x89F4A4, OnDyingEventAsm);
		WriteRelJump(0x60CA24, OnQuestStartStopEventAsm);
		WriteRelCall(0x572FF1, HandleLimbGoneEvent);
		WriteRelCall(0x5F5C78, HandleChallengeCompleteEvent);
		WriteRelCall(0x5F6222, HandleChallengeCompleteEvent);
		WriteRelCall(0x776010, HandleCrosshairEvent);
		WriteRelCall(0x60CB5A, HandleQuestFail);
		WriteRelCall(0x60CA78, HandleQuestComplete);
		WriteRelCall(0x7D6D73, HandleSettingsUpdate);
		WriteRelCall(0x5D4E5B, HandleAddPerkEvent);
		WriteRelCall(0x7865BD, HandleAddPerkEvent);
		WriteRelCall(0x7E772D, HandleAddPerkEvent);
		SafeWriteBuf(0x7E7732, "\x0F\x1F\x00");
		SafeWriteBuf(0x7865C2, "\x0F\x1F\x00");
		SafeWriteBuf(0x5D4E60, "\x0F\x1F\x00");
		WriteRelCall(0x5D4F89, HandleRemovePerkEvent);
		SafeWriteBuf(0x5D4F8E, "\x0F\x1F\x00");
		SafeWrite8(0x60CA29, 0xCC);
		WriteRelJump(0x66EE50, AVChangeEventAsm);
		// Process Level change: MoveToHigh
		ReplaceVirtualFunc(0x108AC7C, HandlePLChangeEvent<0x881D30>);
		ReplaceVirtualFunc(0x10872EC, HandlePLChangeEvent<0x881D30>);
		ReplaceVirtualFunc(0x1086CAC, HandlePLChangeEvent<0x881D30>);
		ReplaceVirtualFunc(0x1084494, HandlePLChangeEvent<0x881D30>);
		// MoveToLow
		ReplaceVirtualFunc(0x108AC80, HandlePLChangeEvent<0x882B90>);
		ReplaceVirtualFunc(0x10872F0, HandlePLChangeEvent<0x882B90>);
		ReplaceVirtualFunc(0x1086CB0, HandlePLChangeEvent<0x882B90>);
		ReplaceVirtualFunc(0x1084498, HandlePLChangeEvent<0x882B90>);
		// MoveToMiddleLow
		ReplaceVirtualFunc(0x108AC84, HandlePLChangeEvent<0x883240>);
		ReplaceVirtualFunc(0x10872F4, HandlePLChangeEvent<0x883240>);
		ReplaceVirtualFunc(0x1086CB4, HandlePLChangeEvent<0x883240>);
		ReplaceVirtualFunc(0x108449C, HandlePLChangeEvent<0x883240>);
		// MoveToMiddleHigh
		ReplaceVirtualFunc(0x108AC88, HandlePLChangeEvent<0x883800>);
		ReplaceVirtualFunc(0x10872F8, HandlePLChangeEvent<0x883800>);
		ReplaceVirtualFunc(0x1086CB8, HandlePLChangeEvent<0x883800>);
		ReplaceVirtualFunc(0x10844A0, HandlePLChangeEvent<0x883800>);

		// Keyboard/Controller selection change
		InputSwitchHook<0x0718059>();
		InputSwitchHook<0x0715CD5>();

		//Radio
		RadioTuneOnHook<0x511816>();
		RadioTuneOnHook<0x579C64>();
		RadioTuneOnHook<0x57A23A>();

		ReplaceVirtualFunc(0x10763B8, HandleSleepWaitClick);

		OnRenderGamePreUpdateHandler = JGCreateEvent("OnRenderGamePreUpdateHandler", 0, 0, nullptr);
		WriteRelCall(0x943748, HandlePreRenderEvent);
		OnRenderGameModeUpdateHandler = JGCreateEvent("OnRenderGameModeUpdateHandler", 0, 0, nullptr);
		WriteRelCall(0x870244, HandleRenderGameEvent);
		OnRenderRenderedMenuUpdateHandler = JGCreateEvent("OnRenderRenderedMenuUpdateHandler", 0, 0, nullptr);
		WriteRelCall(0x8702A9, HandleRenderMenuEvent);

		WriteRelCall(0x4CB976, HandleTakeBackItem);
		WriteRelCall(0x8F24A1, GetExtraDataListHook);

		WriteRelCall(0x7630FD, HandleOnNPCResponseEvent);

		//HUDMainMenu::AppendSubtitleData() called by Interface::ShowText()
		WriteRelCall(0x7052B8, HandleOnGeneralSubtitleEvent);

		ReplaceVirtualFunc(0x104BA6C, HandleOnReputationChangeEvent);
	}

	void Reset() {
		OnDyingHandler->FlushEventCallbacks();
		OnLimbGoneHandler->FlushEventCallbacks();
		OnCrosshairHandler->FlushEventCallbacks();
		OnPLChangeHandler->FlushEventCallbacks();
		pItemOwnerRef = nullptr;
	}

	void Update() {
		for (const auto& rInfo : EventInfos) {
			rInfo->AddQueuedEvents();
			rInfo->DeleteEvents();
		}
	}

	void __fastcall Register(EventInformation* apEventInfo, Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0) {
		if (apEventInfo) {
			if (abToggle)
				apEventInfo->RegisterEvent(apScript, apFilters, auiUserFlags);
			else 
				apEventInfo->RemoveEvent(apScript, apFilters);
		}
	}

	void RegisterOnDying(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnDyingHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnStartQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnStartQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnStopQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnStopQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnFailQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnFailQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnCompleteQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnCompleteQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnSeenDataUpdate(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnSeenDataUpdateHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnLimbGone(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnLimbGoneHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnChallengeComplete(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnChallengeCompleteHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnCrosshair(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnCrosshairHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnSettingsUpdate(Script* script, bool abToggle, uint32_t auiUserFlags) {
		Register(OnSettingsUpdateHandler, script, nullptr, abToggle);
	}

	void RegisterOnAddPerk(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnAddPerkHandler, apScript, apFilters, abToggle);
	}
	
	void RegisterOnRemovePerk(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnRemovePerkHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnActorValueChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnAVChangeHandler, apScript, apFilters, abToggle, auiUserFlags);
	}

	void RegisterOnProcessLevelChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnPLChangeHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnRadioPostSoundAttach(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnRadioPostSoundAttachHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnInputSwitch(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnKeyboardControllerSelectionChangeHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnSleepWait(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnSleepWaitEventHandler, apScript, apFilters, abToggle);
	}

	enum EnumFlags {
		kDoNotFireInRenderMenu	= 1 << 0,
		kDoNotFireInGameMode	= 1 << 1,
		kUseGamePreEvent		= 1 << 2,
	};

	void RegisterOnRender(Script* apScript, bool abToggle, uint32_t auiUserFlags) {
		if (!(auiUserFlags & kDoNotFireInGameMode) && OnRenderGameModeUpdateHandler) {
			if (!(auiUserFlags & kUseGamePreEvent)) {
				if (abToggle)
					OnRenderGameModeUpdateHandler->RegisterEvent(apScript, nullptr);
				else
					OnRenderGameModeUpdateHandler->RemoveEvent(apScript, nullptr);
			}
			else if (OnRenderGamePreUpdateHandler) {
				if (abToggle)
					OnRenderGamePreUpdateHandler->RegisterEvent(apScript, nullptr);
				else 
					OnRenderGamePreUpdateHandler->RemoveEvent(apScript, nullptr);
			}
		}

		if (!(auiUserFlags & kDoNotFireInRenderMenu) && OnRenderRenderedMenuUpdateHandler) {
			if (abToggle)
				OnRenderRenderedMenuUpdateHandler->RegisterEvent(apScript, nullptr);
			else 
				OnRenderRenderedMenuUpdateHandler->RemoveEvent(apScript, nullptr);
		}
	}

	void RegisterOnNPCResponse(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnNPCResponseHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnGeneralSubtitle(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnGeneralSubtitleHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnReputationChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnReputationChangeHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnNPCActorValueChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnNPCAVChangeHandler, apScript, apFilters, abToggle, auiUserFlags);
	}

	void RegisterOnTakeBackItem(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(OnTakeBackItemHandler, apScript, apFilters, abToggle, auiUserFlags);
	}
}

