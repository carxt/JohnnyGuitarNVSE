#include "JohnnyEvents.hpp"
#include "EventFramework.h"
#include "decoding.h"
#include "JohnnyMessageData.hpp"
#include <utility.h>

#include "Bethesda/DialogueResponse.hpp"
#include "Bethesda/MenuTopic.hpp"
#include "Bethesda/PlayerCharacter.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"
#include <shared/Utils/DebugLog.hpp>

class InventoryChanges;

extern NVSEScriptInterface* g_scriptInterface;

namespace JohnnyEvents {

	static thread_local AVChangeMode eAVChangeMode = AVChangeMode::MOD;

	STACK_FRAME_OPT_ENABLE
	EXTERN_DLL_EXPORT SPEC_NOINLINE AVChangeMode SetAVChangeMode(AVChangeMode aeMode) {
		assert(aeMode == AVChangeMode::SET || aeMode == AVChangeMode::MOD);
		auto eOld = eAVChangeMode;
		eAVChangeMode = aeMode;
		return eOld;
	}

	EXTERN_DLL_EXPORT SPEC_NOINLINE AVChangeMode GetAVChangeMode() {
		return eAVChangeMode;
	}
	STACK_FRAME_OPT_RESET
}

namespace JohnnyEvents {

	namespace Events {

		STACK_FRAME_OPT_ENABLE

		static EventInformation* OnDyingHandler;
		static EventInformation* OnStartQuestHandler;
		static EventInformation* OnStopQuestHandler;
		static EventInformation* OnFailQuestHandler;
		static EventInformation* OnCompleteQuestHandler;
		static EventInformation* OnSeenDataUpdateHandler;
		static EventInformation* OnLimbGoneHandler;
		static EventInformation* OnChallengeCompleteHandler;
		static EventInformation* OnCrosshairHandler;
		static EventInformation* OnSettingsUpdateHandler;
		static EventInformation* OnAddPerkHandler;
		static EventInformation* OnRemovePerkHandler;
		static EventInformation* OnRenderGamePreUpdateHandler;
		static EventInformation* OnRenderGameModeUpdateHandler;
		static EventInformation* OnRenderRenderedMenuUpdateHandler;
		static EventInformation* OnAVChangeHandler;
		static EventInformation* OnPLChangeHandler;
		static EventInformation* OnRadioPostSoundAttachHandler;
		static EventInformation* OnKeyboardControllerSelectionChangeHandler;
		static EventInformation* OnSleepWaitEventHandler;
		static EventInformation* OnTakeBackItemHandler;
		static EventInformation* OnNPCResponseHandler;
		static EventInformation* OnGeneralSubtitleHandler;
		static EventInformation* OnReputationChangeHandler;
		static EventInformation* OnNPCAVChangeHandler;

		static void __fastcall OnRenderGamePreUpdate() {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnRenderGamePreUpdate);
			}
			for (auto const& rCallback : OnRenderGamePreUpdateHandler->kCallbacks) {
				rCallback.CallScript(OnRenderGamePreUpdateHandler);
			}
		}

		static void __fastcall OnRenderGameModeUpdate(BSRenderedTexture* apDestination, bool abRenderedMenuMode, bool abSkipFirstPerson) {
			{
				using namespace JohnnyMessageData;
				RenderGameData kData(apDestination, abRenderedMenuMode, abSkipFirstPerson);
				SendNVSEMessage(JG_OnRenderGameModeUpdate, kData);
			}

			for (auto const& rCallback : OnRenderGameModeUpdateHandler->kCallbacks) {
				rCallback.CallScript(OnRenderGameModeUpdateHandler);
			}

		}

		static void __fastcall OnRenderRenderedMenuUpdate(BSRenderedTexture* apDestination, bool abRenderedMenuMode, bool abSkipFirstPerson) {
			{
				using namespace JohnnyMessageData;
				RenderGameData kData(apDestination, abRenderedMenuMode, abSkipFirstPerson);
				SendNVSEMessage(JG_OnRenderRenderedMenuUpdate, kData);
			}

			for (auto const& rCallback : OnRenderRenderedMenuUpdateHandler->kCallbacks) {
				rCallback.CallScript(OnRenderRenderedMenuUpdateHandler);
			}
		}

		static void __fastcall OnRemovePerk(Actor* apActor, BGSPerk* apPerk, bool abTeammate) {
			if (!apPerk) [[unlikely]]
				return;

			if (!apActor->GetPerkRank(apPerk, abTeammate)) [[unlikely]]
				return;

			{
				using namespace JohnnyMessageData;
				PerkRemoveData kData(apActor, apPerk, abTeammate);
				SendNVSEMessage(JG_OnRemovePerk, kData);
			}

			for (auto const& rCallback : OnRemovePerkHandler->kCallbacks) {
				if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsFormInFilter(apPerk, 0)) {
					rCallback.CallScript(OnRemovePerkHandler, apActor, apPerk);
				}
			}
		}

		static void __fastcall OnAddPerk(Actor* apActor, BGSPerk* apPerk, uint8_t aucRank, bool abTeammate) {
			if (!apPerk) [[unlikely]]
				return;

			{
				using namespace JohnnyMessageData;
				PerkAddData kData(apActor, apPerk, abTeammate, aucRank);
				SendNVSEMessage(JG_OnAddPerk, kData);
			}
			
			for (auto const& rCallback : OnAddPerkHandler->kCallbacks) {
				if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsFormInFilter(apPerk, 0)) {
					rCallback.CallScript(OnAddPerkHandler, apActor, apPerk, aucRank - 1, aucRank);
				}
			}
		}

		static void __fastcall OnDying(Actor* apActor) {
			if (apActor->GetLifeState() == ACTOR_LIFE_STATE::DYING) {
				{
					using namespace JohnnyMessageData;
					SendNVSEMessage(JG_OnDying, apActor);
				}

				if (apActor == PlayerCharacter::GetSingleton() || apActor->GetFullName()[0]) {
					for (auto const& rCallback : OnDyingHandler->kCallbacks) {
						if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsRefInFilter(apActor, 0)) {
							rCallback.CallScript(OnDyingHandler, nullptr, apActor);
						}
					}
				}
			}
		}
		
		static void __fastcall OnQuestStartStop(TESQuest* apQuest, bool abStarted) {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(abStarted ? JG_OnStartQuest : JG_OnStopQuest, apQuest);
			}

			const EventInformation* pEvent = abStarted ? OnStartQuestHandler : OnStopQuestHandler;
			for (auto const& rCallback : pEvent->kCallbacks) {
				if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsFormInFilter(apQuest, 0)) {
					rCallback.CallScript(pEvent, nullptr, apQuest);
				}
			}
		}

		static void __fastcall OnCompleteQuest(TESQuest* apQuest) {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnCompleteQuest, apQuest);
			}

			for (auto const& rCallback : OnCompleteQuestHandler->kCallbacks) {
				if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsFormInFilter(apQuest, 0)) {
					rCallback.CallScript(OnCompleteQuestHandler, nullptr, apQuest);
				}
			}
		}

		static void __fastcall OnFailQuest(TESQuest* apQuest) {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnFailQuest, apQuest);
			}

			for (auto const& rCallback : OnFailQuestHandler->kCallbacks) {
				if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsFormInFilter(apQuest, 0)) {
					rCallback.CallScript(OnFailQuestHandler, nullptr, apQuest);
				}
			}
		}

		static void __fastcall OnSettingsUpdate() {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnSettingsUpdate);
			}

			for (auto const& rCallback : OnSettingsUpdateHandler->kCallbacks) {
				rCallback.CallScript(OnSettingsUpdateHandler);
			}
		}

		static void __fastcall OnSeenDataUpdate(TESObjectCELL* apCell) {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnSeenDataUpdate, apCell);
			}

			for (auto const& rCallback : OnSeenDataUpdateHandler->kCallbacks) {
				if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsFormInFilter(apCell, 0)) {
					rCallback.CallScript(OnSeenDataUpdateHandler, nullptr, apCell);
				}
			}
		}

		static void __fastcall OnChallengeComplete(TESChallenge* apChallenge) {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnChallengeComplete, apChallenge);
			}

			for (auto const& rCallback : OnChallengeCompleteHandler->kCallbacks) {
				if (reinterpret_cast<FilterForm*>(rCallback.pFilter)->IsFormInFilter(apChallenge, 0)) {
					rCallback.CallScript(OnChallengeCompleteHandler, nullptr, apChallenge);
				}
			}
		}

		static void __fastcall OnLimbGone(ExtraDismemberedLimbs* apLimbData, Actor* apActor, uint32_t aeLimb, bool abExplodedLimb) {
			{
				using namespace JohnnyMessageData;
				DismemberData kData(apActor, apLimbData, aeLimb, abExplodedLimb);
				SendNVSEMessage(JG_OnLimbGone, kData);
			}

			for (auto const& rCallback : OnLimbGoneHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterFormInt*>(rCallback.pFilter);
				if (pFilter->IsIntInFilter(aeLimb) && pFilter->IsRefInFilter(apActor, 0)) {
					rCallback.CallScript(OnLimbGoneHandler, nullptr, apActor, aeLimb);
				}
			}
		}

		static void __fastcall OnCrosshair(TESObjectREFR* apRef) {
			if (!apRef)
				return;

			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnCrosshair, apRef);
			}

			for (auto const& rCallback : OnCrosshairHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterFormInt*>(rCallback.pFilter);
				if (pFilter->IsRefInFilter(apRef, 0) && pFilter->IsBaseFormInFilter(apRef->GetObjectReference(), 1)) {
					rCallback.CallScript(OnCrosshairHandler, nullptr, apRef);
				}
			}
		}

		static void __fastcall OnTakeBackItem(TESObjectREFR* apOwner, TESBoundObject* apObject, int32_t aiNumber) {
			if (!apOwner)
				return;
			
			{
				using namespace JohnnyMessageData;
				TakeBackItemData kData(apOwner, apObject, aiNumber);
				SendNVSEMessage(JG_OnTakeBackItem, kData);
			}

			for (auto const& rCallback : OnTakeBackItemHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterForm*>(rCallback.pFilter);
				if (pFilter->IsBaseFormInFilter(apObject, 0) && pFilter->IsRefInFilter(apOwner, 1)) {
					rCallback.CallScript(OnTakeBackItemHandler, nullptr, apOwner, apObject, aiNumber);
				}
			}
		}

		static void __fastcall OnAVChange(ActorValueOwner* apActor, ActorValue::Index aeActorValue, float afPreviousValue, float afNewValue) {
			const float fNewValue = GetAVChangeMode() == AVChangeMode::SET ? afNewValue : afPreviousValue + afNewValue;
			const float fPreviousValue = afPreviousValue;

			const float fNewValueFloor = floor(fNewValue);
			const float fPreviousValueFloor = floor(fPreviousValue);

			TESForm* pForm = apActor->GetAsForm();
			if (pForm && int32_t(fNewValueFloor) != int32_t(fPreviousValueFloor)) {
				{
					using namespace JohnnyMessageData;
					ActorValueChangeData kData(pForm, aeActorValue, fNewValue, fPreviousValue);
					SendNVSEMessage(JG_OnAVChange, kData);
				}

				const float fNewValueClamped = apActor->GetActorValueF(aeActorValue);
				const float fNewValueClampedFloor = floor(fNewValueClamped);

				// "fui" indeed, welcome to the hungarian notation hell
				// We're bit casting here because you can't pass floats directly
				// Man, what a mess this whole event is
				const uint32_t fuiNewValue				= std::bit_cast<uint32_t>(fNewValue);
				const uint32_t fuiNewValueClamped		= std::bit_cast<uint32_t>(fNewValueClamped);
				const uint32_t fuiPreviousValue			= std::bit_cast<uint32_t>(fPreviousValue);

				const uint32_t fuiNewValueFloor			= std::bit_cast<uint32_t>(fNewValueFloor);
				const uint32_t fuiNewValueClampedFloor	= std::bit_cast<uint32_t>(fNewValueClampedFloor);
				const uint32_t fuiPreviousValueFloor	= std::bit_cast<uint32_t>(fPreviousValueFloor);

				auto GetValues = [=](const EventBase& arCallback, uint32_t& arPrev, uint32_t& arNew) -> bool {
					const bool bNoFloor = arCallback.usUserFlags.GetBit<0>();
					const bool bUseClamp = arCallback.usUserFlags.GetBit<1>();

					arPrev = bNoFloor ? fuiPreviousValue : fuiPreviousValueFloor;
					arNew = fuiNewValueFloor;
					if (bUseClamp) [[unlikely]] {
						if (fuiNewValueClampedFloor == fuiPreviousValueFloor) [[unlikely]]
							return false;

						arNew = bNoFloor ? fuiNewValueClamped : fuiNewValueClampedFloor;
					}
					else if (bNoFloor) [[unlikely]] {
						arNew = fuiNewValue;
					}
					return true;
				};

				if (pForm == PlayerCharacter::GetSingleton()) {
					for (auto const& rCallback : OnAVChangeHandler->kCallbacks) {
						auto pFilter = reinterpret_cast<FilterFormInt*>(rCallback.pFilter);
						if (pFilter->IsIntInFilter(aeActorValue)) {
							uint32_t uiPrev = 0, uiNew = 0;
							if (GetValues(rCallback, uiPrev, uiNew)) [[likely]]
								rCallback.CallScript(OnAVChangeHandler, nullptr, aeActorValue, uiPrev, uiNew);
						}
					}
				}
				else {
					for (auto const& rCallback : OnNPCAVChangeHandler->kCallbacks) {
						auto pFilter = reinterpret_cast<FilterFormInt*>(rCallback.pFilter);
						if (pFilter->IsIntInFilter(aeActorValue) && pFilter->IsAnyFormInFilter(pForm, 0)) {
							uint32_t uiPrev = 0, uiNew = 0;
							if (GetValues(rCallback, uiPrev, uiNew)) [[likely]]
								rCallback.CallScript(OnNPCAVChangeHandler, nullptr, pForm, aeActorValue, uiPrev, uiNew);
						}
					}
				}
			}
		}

		static void __fastcall OnProcessChangeEvent(Actor* apActor, uint32_t aeOldLevel, uint32_t aeNewLevel) {
			if (aeOldLevel != aeNewLevel) {
				{
					using namespace JohnnyMessageData;
					ProcessLevelChangeData kData(apActor, aeOldLevel, aeNewLevel);
					SendNVSEMessage(JG_OnPLChange, kData);
				}

				for (auto const& rCallback : OnPLChangeHandler->kCallbacks) {
					auto pFilter = reinterpret_cast<FilterFormInt*>(rCallback.pFilter);
					if (pFilter->IsIntInFilter(aeNewLevel) && pFilter->IsRefInFilter(apActor, 0)) {
						rCallback.CallScript(OnPLChangeHandler, nullptr, apActor, aeOldLevel, aeNewLevel);
					}
				}
			}
		}

		static void __fastcall OnSleepWaitEvent(SleepWaitMenu* apMenu, uint32_t auiTileID) {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnSleepWaitEvent, apMenu);
			}

			for (auto const& rCallback : OnSleepWaitEventHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterInt*>(rCallback.pFilter);
				if (pFilter->IsIntInFilter(0, uint32_t(apMenu->isRest) + 1) || pFilter->IsIntInFilter(0, 0)) {
					rCallback.CallScript(OnSleepWaitEventHandler, nullptr, (int(apMenu->isRest) + 1));
				}
			}
		}

		static void __fastcall OnRadioPostSoundAttach(TESObjectACTI* apRadio, bool abActive) {
			if (!apRadio)
				return;

			{
				using namespace JohnnyMessageData;
				RadioPostSoundAttachData kData(apRadio, abActive);
				SendNVSEMessage(JG_OnRadioPostSoundAttach, kData);
			}

			for (auto const& rCallback : OnRadioPostSoundAttachHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterForm*>(rCallback.pFilter);
				if (pFilter->IsAnyFormInFilter(apRadio, 0)) {
					rCallback.CallScript(OnRadioPostSoundAttachHandler, nullptr, apRadio, abActive ? 1u : 0u);
				}
			}
		}

		static void __fastcall OnKeyboardControllerSelectionChange(InterfaceManager* apManager, Menu* apMenu) {
			{
				using namespace JohnnyMessageData;
				SendNVSEMessage(JG_OnKeyboardControllerSelectionChange, apMenu);
			}

			const uint32_t uiMenuID = apMenu ? apMenu->GetMenuID() : -1;
			for (auto const& rCallback : OnKeyboardControllerSelectionChangeHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterInt*>(rCallback.pFilter);
				if (pFilter->IsIntInFilter(0, uiMenuID) || pFilter->IsIntInFilter(0, 0)) {
					rCallback.CallScript(OnKeyboardControllerSelectionChangeHandler, nullptr, uiMenuID);
				}
			}
		}

		//Currently Displayed Text, Source Position, Target Reference (Usually Player)
		static void __fastcall OnGeneralSubtitle(const char* apText, NiPoint3 akPos, TESObjectREFR* apTarget) {
			{
				using namespace JohnnyMessageData;
				GeneralSubtitleData kData(apText, apTarget, akPos);
				SendNVSEMessage(JG_OnGeneralSubtitle, kData);
			}

			const char* pSubtitleString = apText ? apText : "";
			const uint32_t uiX = *reinterpret_cast<uint32_t*>(&akPos.x);
			const uint32_t uiY = *reinterpret_cast<uint32_t*>(&akPos.y);
			const uint32_t uiZ = *reinterpret_cast<uint32_t*>(&akPos.z);

			for (auto const& rCallback : OnGeneralSubtitleHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterForm*>(rCallback.pFilter);
				if (pFilter->IsRefInFilter(apTarget, 0) || pFilter->FilterForm::IsInFilter(0, 0)) {
					rCallback.CallScript(OnGeneralSubtitleHandler, nullptr, pSubtitleString, apTarget, uiX, uiY, uiZ);
				}
			}
			return;
		}

		static void __fastcall OnNPCResponse(DialogueResponse* apResponse) {
			uint32_t	uiEmotionID = 0;
			uint32_t	uiEmotionValue = 0;
			uint32_t	uiResponseNumber = 0;
			const char* pResponseString = "";
			const char* pVoicePath = "";

			if (apResponse) {
				uiEmotionID = apResponse->uiEmotionType;
				uiEmotionValue = apResponse->uiEmotionValue;
				uiResponseNumber = apResponse->uiResponseNumber;
				pResponseString = apResponse->strResponseText.c_str();
				pVoicePath = apResponse->strVoiceFilePath.c_str();
			}

			{
				using namespace JohnnyMessageData;
				NPCResponseData kData;
				kData.uiEmotionID = uiEmotionID;
				kData.uiEmotionValue = uiEmotionValue;
				kData.uiResponseNumber = uiResponseNumber;
				kData.pResponseString = pResponseString;
				kData.pVoicePath = pVoicePath;
				SendNVSEMessage(JG_OnNPCResponse, kData);
			}

			for (auto const& rCallback : OnNPCResponseHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterInt*>(rCallback.pFilter);
				if (pFilter->IsIntInFilter(0, uiEmotionID) || pFilter->IsIntInFilter(0, 0)) {
					rCallback.CallScript(OnNPCResponseHandler, nullptr, pResponseString, pVoicePath, uiEmotionID, uiEmotionValue, uiResponseNumber);
				}
			}
		}

		static void __fastcall OnReputationChange(TESReputation* apRep) {
			{
				using namespace JohnnyMessageData;
				ReputationChangeData kData(apRep, apRep->fPositiveReputation, apRep->fNegativeReputation);
				SendNVSEMessage(JG_OnReputationChange, kData);
			}

			const uint32_t uiPos = *reinterpret_cast<uint32_t*>(&apRep->fPositiveReputation);
			const uint32_t uiNeg = *reinterpret_cast<uint32_t*>(&apRep->fNegativeReputation);
			for (auto const& rCallback : OnReputationChangeHandler->kCallbacks) {
				auto pFilter = reinterpret_cast<FilterForm*>(rCallback.pFilter);
				if (pFilter->IsFormInFilter(apRep, 0)) {
					rCallback.CallScript(OnReputationChangeHandler, nullptr, apRep, uiPos, uiNeg);
				}
			}
		}

		static void Init() {
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
			OnRenderGamePreUpdateHandler = JGCreateEvent("OnRenderGamePreUpdateHandler", 0, 0, nullptr);
			OnRenderGameModeUpdateHandler = JGCreateEvent("OnRenderGameModeUpdateHandler", 0, 0, nullptr);
			OnRenderRenderedMenuUpdateHandler = JGCreateEvent("OnRenderRenderedMenuUpdateHandler", 0, 0, nullptr);
		}

		STACK_FRAME_OPT_RESET
	}

	namespace Hooks {

		namespace {
			HookUtils::CallDetour kOnRenderGamePreUpdateDetour;
			STACK_FRAME_OPT_ENABLE
			bool OnRenderGamePreUpdate() {
				Events::OnRenderGamePreUpdate();
				return CdeclCall<bool>(kOnRenderGamePreUpdateDetour);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::VirtCallDetour kOnRemovePerkDetour;
			STACK_FRAME_OPT_ENABLE
			void __fastcall OnRemovePerk(Actor* apActor, void*, BGSPerk* apPerk, bool abTeammate) {
				Events::OnRemovePerk(apActor, apPerk, abTeammate);
				if (kOnRemovePerkDetour)
					ThisCall(kOnRemovePerkDetour, apActor, apPerk, abTeammate);
				else
					apActor->RemovePerk(apPerk, abTeammate);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			STACK_FRAME_OPT_ENABLE
			SPEC_NOINLINE void __fastcall DoAddPerk(Actor* apActor, uint32_t auiAddress, BGSPerk* apPerk, uint8_t aucRank, bool abTeammate) {
				Events::OnAddPerk(apActor, apPerk, aucRank, abTeammate);

				if (auiAddress)
					ThisCall(auiAddress, apActor, apPerk, aucRank, abTeammate);
				else
					apActor->AddPerk(apPerk, aucRank, abTeammate);
			}
			STACK_FRAME_OPT_RESET

			template<uint32_t uiAddress>
			class OnAddPerkHook {
				static inline HookUtils::VirtCallDetour kDetour;

				void Hook(BGSPerk* apPerk, uint8_t aucRank, bool abTeammate) {
					DoAddPerk(reinterpret_cast<Actor*>(this), kDetour, apPerk, aucRank, abTeammate);
				}

			public:
				OnAddPerkHook() {
					kDetour.ReplaceVirtualCall(uiAddress, &OnAddPerkHook::Hook, 8);
				}
			};
		}

		namespace {
			HookUtils::CallDetour kOnCrosshairDetour;
			STACK_FRAME_OPT_ENABLE
			uint32_t __fastcall OnCrosshair(TESObjectREFR* apRef) {
				Events::OnCrosshair(apRef);
				return ThisCall<uint32_t>(kOnCrosshairDetour, apRef);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::CallDetour kOnLimbGoneDetour;
			STACK_FRAME_OPT_ENABLE
			bool __fastcall OnLimbGone(ExtraDismemberedLimbs* apLimbData, void*, Actor* apActor, uint32_t aeLimb, bool abExplodedLimb) {
				Events::OnLimbGone(apLimbData, apActor, aeLimb, abExplodedLimb);
				return ThisCall<bool>(kOnLimbGoneDetour, apLimbData, apActor, aeLimb, abExplodedLimb);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::CallDetour kOnCompleteQuestDetour;
			STACK_FRAME_OPT_ENABLE
			void __cdecl OnCompleteQuest(TESQuest* apQuest) {
				Events::OnCompleteQuest(apQuest);
				CdeclCall(kOnCompleteQuestDetour, apQuest);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::CallDetour kOnFailQuestDetour;
			STACK_FRAME_OPT_ENABLE
			void __cdecl OnFailQuest(TESQuest* apQuest) {
				Events::OnFailQuest(apQuest);
				CdeclCall(kOnFailQuestDetour, apQuest);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::CallDetour kOnSettingsUpdateDetour;
			STACK_FRAME_OPT_ENABLE
			void* __cdecl OnSettingsUpdate() {
				Events::OnSettingsUpdate();
				return CdeclCall<void*>(kOnSettingsUpdateDetour);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			STACK_FRAME_OPT_ENABLE
			SPEC_NOINLINE ExtraDataList* __fastcall DoOnSeenData(TESObjectCELL* apCell, uint32_t auiAddress) {
				Events::OnSeenDataUpdate(apCell);
				return ThisCall<ExtraDataList*>(auiAddress, apCell);
			}
			STACK_FRAME_OPT_RESET

			template<uint32_t uiAddress>
			class OnSeenDataUpdateHook {
				static inline HookUtils::CallDetour kDetour;

				ExtraDataList* Hook() {
					return DoOnSeenData(reinterpret_cast<TESObjectCELL*>(this), kDetour);
				}

			public:
				OnSeenDataUpdateHook() {
					kDetour.ReplaceCall(uiAddress, &OnSeenDataUpdateHook::Hook);
				}
			};
		}

		namespace {
			STACK_FRAME_OPT_ENABLE
			SPEC_NOINLINE uint32_t __fastcall DoChallengeComplete(TESChallenge* apChallenge, uint32_t auiAddress) {
				Events::OnChallengeComplete(apChallenge);
				return ThisCall<uint32_t>(auiAddress, apChallenge);
			}
			STACK_FRAME_OPT_RESET

			template<uint32_t uiAddress>
			class OnChallengeCompleteHook {
				static inline HookUtils::CallDetour kDetour;

				uint32_t Hook() {
					return DoChallengeComplete(reinterpret_cast<TESChallenge*>(this), kDetour);
				}

			public:
				OnChallengeCompleteHook() {
					kDetour.ReplaceCall(uiAddress, &OnChallengeCompleteHook::Hook);
				}
			};
		}

		namespace {
			HookUtils::CallDetour kOnRenderGameModeUpdateDetour;
			STACK_FRAME_OPT_ENABLE
			void __fastcall OnRenderGameModeUpdate(void* apMain, void*, BSRenderedTexture* apDestination, bool abRenderedMenuMode, bool abSkipFirstPerson) {
				Events::OnRenderGameModeUpdate(apDestination, abRenderedMenuMode, abSkipFirstPerson);
				ThisCall(kOnRenderGameModeUpdateDetour, apMain, apDestination, abRenderedMenuMode, abSkipFirstPerson);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::CallDetour kOnRenderRenderedMenuUpdateDetour;
			STACK_FRAME_OPT_ENABLE
			void __fastcall OnRenderRenderedMenuUpdate(void* apMain, void*, BSRenderedTexture* apDestination, bool abRenderedMenuMode, bool abSkipFirstPerson) {
				Events::OnRenderRenderedMenuUpdate(apDestination, abRenderedMenuMode, abSkipFirstPerson);
				ThisCall(kOnRenderRenderedMenuUpdateDetour, apMain, apDestination, abRenderedMenuMode, abSkipFirstPerson);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			STACK_FRAME_OPT_ENABLE
			SPEC_NOINLINE bool __fastcall DoProcessChange(Actor* apActor, uint32_t auiAddress) {
				const BaseProcess* pProcess = apActor->GetCurrentAIProcess();
				if (!pProcess) [[unlikely]]
					return ThisCall<bool>(auiAddress, apActor);

				const uint32_t eOldLevel = pProcess->GetProcessLevel();
				const bool bResult = ThisCall<bool>(auiAddress, apActor);
				const uint32_t eNewLevel = pProcess->GetProcessLevel();
				Events::OnProcessChangeEvent(apActor, eOldLevel, eNewLevel);
				return bResult;
			}
			STACK_FRAME_OPT_RESET

			template<uint32_t uiAddress>
			class OnProcessChangeEventHook {
				static inline HookUtils::VirtFuncDetour kDetour;

				bool Hook() {
					return DoProcessChange(reinterpret_cast<Actor*>(this), kDetour);
				}

			public:
				OnProcessChangeEventHook() {
					kDetour.ReplaceVirtualFunc(uiAddress, &OnProcessChangeEventHook::Hook);
				}
			};
		}

		namespace {
			HookUtils::CallDetour kOnAVChangeDetour;
			STACK_FRAME_OPT_DISABLE
			ActorValueInfo* __cdecl OnAVChange(ActorValue::Index aeActorValue) {
				DWORD* pReturnAddrAddr = static_cast<DWORD*>(_AddressOfReturnAddress());
				uint8_t* pEBP = GetParentBasePtr(pReturnAddrAddr);
				ActorValueOwner* pActor = *reinterpret_cast<ActorValueOwner**>(pEBP + 0x8);
				float fOldVal = *reinterpret_cast<float*>(pEBP + 0x10);
				float fNewVal = *reinterpret_cast<float*>(pEBP + 0x14);
				ActorValueInfo* pInfo = CdeclCall<ActorValueInfo*>(kOnAVChangeDetour, aeActorValue);
				if (pInfo) [[likely]]
					Events::OnAVChange(pActor, aeActorValue, fOldVal, fNewVal);
				return pInfo;
			}
			STACK_FRAME_OPT_RESET

			HookUtils::CallDetour kOnAVChangeSetDetour;
			STACK_FRAME_OPT_ENABLE
			void __cdecl OnAVChangeModeSet(ActorValueOwner* apActor, ActorValue::Index aeIndex, float afOldVal, float afNewVal, ActorValueOwner* apActorSource) {
				auto ePrevMode = JohnnyEvents::SetAVChangeMode(AVChangeMode::SET);
				CdeclCall(kOnAVChangeSetDetour, apActor, aeIndex, afOldVal, afNewVal, apActorSource);
				JohnnyEvents::SetAVChangeMode(ePrevMode);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::CallDetour kOnDyingDetour;
			STACK_FRAME_OPT_DISABLE
			void __fastcall OnDying(void* apThis) {
				uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
				Actor* pActor = *reinterpret_cast<Actor**>(pEBP - 0x18);
				Events::OnDying(pActor);
				ThisCall(kOnDyingDetour, apThis);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::VirtCallDetour kOnQuestStartStopDetour;
			STACK_FRAME_OPT_DISABLE
			void __fastcall OnQuestStartStop(TESQuest* apQuest, void*, uint32_t auiChangeFlag) {
				if (kOnQuestStartStopDetour)
					ThisCall(kOnQuestStartStopDetour, apQuest, auiChangeFlag);
				else
					apQuest->AddChange(auiChangeFlag);

				uint8_t* pEBP = GetParentBasePtr(_AddressOfReturnAddress());
				const bool bEnabled = reinterpret_cast<bool*>(pEBP + 0x8);
				Events::OnQuestStartStop(apQuest, bEnabled);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			TESObjectREFR* pItemOwnerRef = nullptr;

			HookUtils::CallDetour kOnTakeBackItemOwnerDetour;
			STACK_FRAME_OPT_ENABLE
			ExtraDataList* __fastcall OnTakeBackItem_StoreOwner(TESObjectREFR* apRef) {
				pItemOwnerRef = apRef;
				return ThisCall<ExtraDataList*>(kOnTakeBackItemOwnerDetour, apRef);
			}
			STACK_FRAME_OPT_RESET

			HookUtils::CallDetour kOnTakeBackItemDetour;
			STACK_FRAME_OPT_ENABLE
			TESObjectREFR* __fastcall OnTakeBackItem(InventoryChanges* apInvChanges, void*, TESObjectREFR* apRef, TESBoundObject* apObject, bool abStealing, int32_t aiNumber, ExtraDataList* apExtraList, bool abDropWorld, TESObjectREFR* apOtherContainer, const NiPoint3* apPoint, const NiPoint3* apRotate, bool abDelete, bool abPreferStolen, ItemChange* apItemChange) {
				TESObjectREFR* pOwner = apOtherContainer->IsActor() ? apOtherContainer : pItemOwnerRef;
				Events::OnTakeBackItem(pOwner, apObject, aiNumber);
				pItemOwnerRef = nullptr;
				return ThisCall<TESObjectREFR*>(kOnTakeBackItemDetour, apInvChanges, apRef, apObject, abStealing, aiNumber, apExtraList, abDropWorld, apOtherContainer, apPoint, apRotate, abDelete, abPreferStolen, apItemChange);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			STACK_FRAME_OPT_ENABLE
			SPEC_NOINLINE void __fastcall DoRadioPostSoundAttach(TESObjectACTI* apRef, uint32_t auiAddress, bool abActive) {
				CdeclCall(auiAddress, apRef, abActive);
				Events::OnRadioPostSoundAttach(apRef, abActive);
			}
			STACK_FRAME_OPT_RESET

			template <uintptr_t auiAddress>
			class OnRadioPostSoundAttachHook {
			private:
				static inline HookUtils::CallDetour kDetour;

				static void __cdecl Hook(TESObjectACTI* apRef, bool abActive) {
					DoRadioPostSoundAttach(apRef, kDetour, abActive);
				}

			public:
				OnRadioPostSoundAttachHook() {
					kDetour.ReplaceCall(auiAddress, Hook);
				}
			};
		}

		namespace {
			STACK_FRAME_OPT_ENABLE
			SPEC_NOINLINE void __fastcall DoKeyboardControllerSelection(InterfaceManager* apInterfaceManager, uint32_t auiAddress, Tile* apTarget, int32_t aiType, bool abPlaySounds) {
				void* pMenuManager = CdeclCall<void*>(0x71E290, true);
				Menu* pFrontmostMenu = ThisCall<Menu*>(0x720E60, pMenuManager); // MenuManager::GetFrontmostMenu
				const bool bFireEvent = apInterfaceManager->activeTileAlt != apTarget;
				ThisCall(auiAddress, apInterfaceManager, apTarget, aiType, abPlaySounds);
				if (bFireEvent)
					Events::OnKeyboardControllerSelectionChange(apInterfaceManager, pFrontmostMenu);
			}
			STACK_FRAME_OPT_RESET

			template <uintptr_t auiAddress>
			class OnKeyboardControllerSelectionChangeHook {
			private:
				static inline HookUtils::CallDetour kDetour;

				void Hook(Tile* apTarget, int32_t aiType, bool abPlaySounds) {
					DoKeyboardControllerSelection(reinterpret_cast<InterfaceManager*>(this), kDetour, apTarget, aiType, abPlaySounds);
				}

			public:
				OnKeyboardControllerSelectionChangeHook() {
					kDetour.ReplaceCall(auiAddress, &OnKeyboardControllerSelectionChangeHook::Hook);
				}
			};
		}

		namespace {
			HookUtils::VirtFuncDetour kSleepOnClickDetour;
			STACK_FRAME_OPT_ENABLE
			void __fastcall OnSleepWaitEvent(SleepWaitMenu* apMenu, void*, uint32_t auiTileID, Tile* apTarget) {
				ThisCall(kSleepOnClickDetour, apMenu, auiTileID, apTarget);
				if (auiTileID == 4)
					Events::OnSleepWaitEvent(apMenu, auiTileID);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			//Fires when general subtitles are sent to the HUD.
			HookUtils::CallDetour kGeneralSubtitleDetour;
			STACK_FRAME_OPT_ENABLE
			bool __fastcall OnGeneralSubtitle(HUDMainMenu* apMenu, void*, const char* apText, BSSoundHandle akSound, NiPoint3 akPos, TESObjectREFR* apTarget, bool abInstant) {
				if (apText)
					Events::OnGeneralSubtitle(apText, akPos, apTarget);

				return ThisCall<bool>(kGeneralSubtitleDetour, apMenu, apText, akSound, akPos, apTarget, abInstant);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::CallDetour kOnNPCResponseDetour;
			STACK_FRAME_OPT_ENABLE
			bool __fastcall OnNPCResponse(MenuTopic* apThis) {
				if (apThis->pFirstResponse)
					Events::OnNPCResponse(apThis->pFirstResponse->GetItem());
				return ThisCall<bool>(kOnNPCResponseDetour, apThis);
			}
			STACK_FRAME_OPT_RESET
		}

		namespace {
			HookUtils::VirtFuncDetour kReputationChangeDetour;
			STACK_FRAME_OPT_ENABLE
			void __fastcall OnReputationChange(TESReputation* apThis, void*, uint32_t auiChangeFlag) {
				if (auiChangeFlag & 2)
					Events::OnReputationChange(apThis);

				ThisCall(kReputationChangeDetour, apThis, auiChangeFlag);
			}
			STACK_FRAME_OPT_RESET
		}

		static void Init() {
			kOnDyingDetour.ReplaceCall(0x89F49F, OnDying);

			OnSeenDataUpdateHook<0x55678A>();
			OnSeenDataUpdateHook<0x557053>();

			kOnQuestStartStopDetour.ReplaceVirtualCall(0x60CA1F, OnQuestStartStop, 0);

			kOnLimbGoneDetour.ReplaceCall(0x572FF1, OnLimbGone);

			OnChallengeCompleteHook<0x5F5C78>();
			OnChallengeCompleteHook<0x5F6222>();

			kOnCrosshairDetour.ReplaceCall(0x776010, OnCrosshair);

			kOnFailQuestDetour.ReplaceCall(0x60CB5A, OnFailQuest);

			kOnCompleteQuestDetour.ReplaceCall(0x60CA78, OnCompleteQuest);

			kOnSettingsUpdateDetour.ReplaceCall(0x7D6D73, OnSettingsUpdate);

			OnAddPerkHook<0x5D4E5B>();
			OnAddPerkHook<0x7865BD>();
			OnAddPerkHook<0x7E772D>();
			
			kOnRemovePerkDetour.ReplaceVirtualCall(0x5D4F89, OnRemovePerk, 8);

			kOnAVChangeDetour.ReplaceCall(0x66EE58, OnAVChange);
			kOnAVChangeSetDetour.ReplaceCall(0x880842, OnAVChangeModeSet);
			// Game only passes the old value if AV has a change callback. 
			// Since we're hooking that for our own event callback, we always need the prev value
			// Nuking only the conditional jumps, ActorValueHasOnChangedCallback calls are preserved in case someone hoooooks them
			{
				HookUtils::PatchMemoryNop(0x88071A, 2); // Actor::SetActorValueF
				HookUtils::PatchMemoryNop(0x8809C6, 2); // Actor::TempModActorValueI
				HookUtils::PatchMemoryNop(0x880B53, 2); // Actor::TempModActorValueF
				HookUtils::PatchMemoryNop(0x880CE6, 2); // Actor::PermanentModActorValueI
				HookUtils::PatchMemoryNop(0x880E83, 2); // Actor::PermanentModActorValueF
				HookUtils::PatchMemoryNop(0x881026, 2); // Actor::DamageModActorValueI
				HookUtils::PatchMemoryNop(0x8811B3, 2); // Actor::DamageModActorValueF
				HookUtils::PatchMemoryNop(0x881397, 2); // Actor::ModActorBaseValueF
				HookUtils::PatchMemoryNop(0x93A90A, 2); // PlayerCharacter::ModActorBaseValueI
				HookUtils::PatchMemoryNop(0x93AA2A, 2); // PlayerCharacter::ModActorBaseValueF
				HookUtils::PatchMemoryNop(0x93AECE, 2); // PlayerCharacter::TempModActorValueI
				HookUtils::PatchMemoryNop(0x93B001, 2); // PlayerCharacter::TempModActorValueF
				HookUtils::PatchMemoryNop(0x93B15D, 2); // PlayerCharacter::PermanentModActorValueI
				HookUtils::PatchMemoryNop(0x93B2B0, 2); // PlayerCharacter::PermanentModActorValueF
				HookUtils::PatchMemoryNop(0x93B47A, 2); // PlayerCharacter::DamageModActorValueI
				HookUtils::PatchMemoryNop(0x93B87D, 2); // PlayerCharacter::DamageModActorValueF
			}

			// MoveToHigh
			OnProcessChangeEventHook<0x108AC7C>();
			OnProcessChangeEventHook<0x10872EC>();
			OnProcessChangeEventHook<0x1086CAC>();
			OnProcessChangeEventHook<0x1084494>();

			// MoveToLow
			OnProcessChangeEventHook<0x108AC80>();
			OnProcessChangeEventHook<0x10872F0>();
			OnProcessChangeEventHook<0x1086CB0>();
			OnProcessChangeEventHook<0x1084498>();

			// MoveToMiddleLow
			OnProcessChangeEventHook<0x108AC84>();
			OnProcessChangeEventHook<0x10872F4>();
			OnProcessChangeEventHook<0x1086CB4>();
			OnProcessChangeEventHook<0x108449C>();

			// MoveToMiddleHigh
			OnProcessChangeEventHook<0x108AC88>();
			OnProcessChangeEventHook<0x10872F8>();
			OnProcessChangeEventHook<0x1086CB8>();
			OnProcessChangeEventHook<0x10844A0>();

			// Keyboard/Controller selection change
			OnKeyboardControllerSelectionChangeHook<0x0718059>();
			OnKeyboardControllerSelectionChangeHook<0x0715CD5>();

			// Radio
			OnRadioPostSoundAttachHook<0x511816>();
			OnRadioPostSoundAttachHook<0x579C64>();
			OnRadioPostSoundAttachHook<0x57A23A>();

			kSleepOnClickDetour.ReplaceVirtualFunc(0x10763B8, OnSleepWaitEvent);

			kOnRenderGamePreUpdateDetour.ReplaceCall(0x943748, OnRenderGamePreUpdate);

			kOnRenderGameModeUpdateDetour.ReplaceCall(0x870244, OnRenderGameModeUpdate);

			kOnRenderRenderedMenuUpdateDetour.ReplaceCall(0x8702A9, OnRenderRenderedMenuUpdate);

			kOnTakeBackItemDetour.ReplaceCall(0x4CB976, OnTakeBackItem);
			kOnTakeBackItemOwnerDetour.ReplaceCall(0x8F24A1, OnTakeBackItem_StoreOwner);

			kOnNPCResponseDetour.ReplaceCall(0x7630FD, OnNPCResponse);

			//HUDMainMenu::AppendSubtitleData() called by Interface::ShowText()
			kGeneralSubtitleDetour.ReplaceCall(0x7052B8, OnGeneralSubtitle);

			kReputationChangeDetour.ReplaceVirtualFunc(0x104BA6C, OnReputationChange);
		}
	}

	void Init() {
		Events::Init();
		Hooks::Init();
	}

	STACK_FRAME_OPT_ENABLE
	void Reset() {
		Events::OnDyingHandler->FlushEventCallbacks();
		Events::OnLimbGoneHandler->FlushEventCallbacks();
		Events::OnCrosshairHandler->FlushEventCallbacks();
		Events::OnPLChangeHandler->FlushEventCallbacks();
		Hooks::pItemOwnerRef = nullptr;
	}

	void Update() {
		for (const auto& rInfo : kEventInfos) {
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
		Register(Events::OnDyingHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnStartQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnStartQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnStopQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnStopQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnFailQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnFailQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnCompleteQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnCompleteQuestHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnSeenDataUpdate(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnSeenDataUpdateHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnLimbGone(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnLimbGoneHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnChallengeComplete(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnChallengeCompleteHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnCrosshair(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnCrosshairHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnSettingsUpdate(Script* script, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnSettingsUpdateHandler, script, nullptr, abToggle);
	}

	void RegisterOnAddPerk(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnAddPerkHandler, apScript, apFilters, abToggle);
	}
	
	void RegisterOnRemovePerk(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnRemovePerkHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnActorValueChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnAVChangeHandler, apScript, apFilters, abToggle, auiUserFlags);
	}

	void RegisterOnProcessLevelChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnPLChangeHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnRadioPostSoundAttach(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnRadioPostSoundAttachHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnInputSwitch(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnKeyboardControllerSelectionChangeHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnSleepWait(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnSleepWaitEventHandler, apScript, apFilters, abToggle);
	}

	enum EnumFlags {
		kDoNotFireInRenderMenu	= 1 << 0,
		kDoNotFireInGameMode	= 1 << 1,
		kUseGamePreEvent		= 1 << 2,
	};

	void RegisterOnRender(Script* apScript, bool abToggle, uint32_t auiUserFlags) {
		if (!(auiUserFlags & kDoNotFireInGameMode) && Events::OnRenderGameModeUpdateHandler) {
			if (!(auiUserFlags & kUseGamePreEvent)) {
				if (abToggle)
					Events::OnRenderGameModeUpdateHandler->RegisterEvent(apScript, nullptr);
				else
					Events::OnRenderGameModeUpdateHandler->RemoveEvent(apScript, nullptr);
			}
			else if (Events::OnRenderGamePreUpdateHandler) {
				if (abToggle)
					Events::OnRenderGamePreUpdateHandler->RegisterEvent(apScript, nullptr);
				else 
					Events::OnRenderGamePreUpdateHandler->RemoveEvent(apScript, nullptr);
			}
		}

		if (!(auiUserFlags & kDoNotFireInRenderMenu) && Events::OnRenderRenderedMenuUpdateHandler) {
			if (abToggle)
				Events::OnRenderRenderedMenuUpdateHandler->RegisterEvent(apScript, nullptr);
			else 
				Events::OnRenderRenderedMenuUpdateHandler->RemoveEvent(apScript, nullptr);
		}
	}

	void RegisterOnNPCResponse(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnNPCResponseHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnGeneralSubtitle(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnGeneralSubtitleHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnReputationChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnReputationChangeHandler, apScript, apFilters, abToggle);
	}

	void RegisterOnNPCActorValueChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnNPCAVChangeHandler, apScript, apFilters, abToggle, auiUserFlags);
	}

	void RegisterOnTakeBackItem(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags) {
		Register(Events::OnTakeBackItemHandler, apScript, apFilters, abToggle, auiUserFlags);
	}

	STACK_FRAME_OPT_RESET
}

