#pragma once

#include <Gamebryo/NiPoint3.hpp>

class Actor;
class TESForm;
class TESObjectREFR;
class BGSPerk;
class ExtraDismemberedLimbs;
class TESObjectACTI;
class TESBoundObject;
class TESReputation;

extern NVSEMessagingInterface* g_msgInterface;
extern uint32_t g_pluginHandle;

namespace JohnnyMessageData {

	enum JG_NVSE_MESSAGE_ID : uint32_t {
		JG_EVENT_BASE = 10000,

		JG_OnDying,								// Data: Actor* to the dying actor
		JG_OnStartQuest,						// Data: TESQuest* to the started quest
		JG_OnStopQuest,							// Data: TESQuest* to the stopped quest
		JG_OnFailQuest,							// Data: TESQuest* to the failed quest
		JG_OnCompleteQuest,						// Data: TESQuest* to the completed quest
		JG_OnSeenDataUpdate,					// Data: TESObjectCELL* to the seen cell
		JG_OnLimbGone,							// Data: DismemberData
		JG_OnChallengeComplete,					// Data: TESChallenge* to the completed challenge
		JG_OnCrosshair,							// Data: TESObjectREFR* to the picked reference
		JG_OnSettingsUpdate,					// Data: None
		JG_OnAddPerk,							// Data: PerkAddData
		JG_OnRemovePerk,						// Data: PerkRemoveData
		JG_OnRenderGamePreUpdate,				// Data: None
		JG_OnRenderGameModeUpdate,				// Data: RenderGameData
		JG_OnRenderRenderedMenuUpdate,			// Data: RenderGameData
		JG_OnAVChange,							// Data: ActorValueChangeData
		JG_OnPLChange,							// Data: ProcessLevelChangeData
		JG_OnRadioPostSoundAttach,				// Data: RadioPostSoundAttachData
		JG_OnKeyboardControllerSelectionChange,	// Data: Menu* to the affected menu
		JG_OnSleepWaitEvent,					// Data: SleepWaitMenu*
		JG_OnTakeBackItem,						// Data: TakeBackItemData
		JG_OnNPCResponse,						// Data: NPCResponseData
		JG_OnGeneralSubtitle,					// Data: GeneralSubtitleData
		JG_OnReputationChange,					// Data: ReputationChangeData
	};

	struct PerkRemoveData {
		Actor*		pActor;
		BGSPerk*	pPerk;
		bool		bCompanion;
	};

	struct PerkAddData {
		Actor*		pActor;
		BGSPerk*	pPerk;
		bool		bCompanion;
		uint8_t		ucRank;
	};

	struct DismemberData {
		Actor*					pActor;
		ExtraDismemberedLimbs*	pLimbData;
		uint32_t				eLimb;
		bool					bExploded;
	};

	struct RenderGameData {
		BSRenderedTexture*		pTexture;
		bool					bRenderedMenu;
		bool					bSkipFirstPerson;
	};

	struct ActorValueChangeData {
		TESForm*	pForm;
		uint32_t	eActorValue;
		float		fNewValue;
		float		fPreviousValue;
	};

	struct ProcessLevelChangeData {
		Actor*		pActor;
		uint32_t	eOldLevel;
		uint32_t	eNewLevel;
	};

	struct RadioPostSoundAttachData {
		TESObjectACTI*	pRadio;
		bool			bActive;
	};

	struct TakeBackItemData {
		TESObjectREFR*	pOwner;
		TESBoundObject* pObject;
		int32_t			iCount;
	};

	struct NPCResponseData {
		uint32_t	uiEmotionID;
		uint32_t	uiEmotionValue;
		uint32_t	uiResponseNumber;
		const char* pResponseString;
		const char* pVoicePath;
	};

	struct GeneralSubtitleData {
		const char*		pText;
		TESObjectREFR*	pTarget;
		NiPoint3		kPos;
	};

	struct ReputationChangeData {
		TESReputation*	pReputation;
		float			fPos;
		float			fNeg;
	};

	template<typename T>
	inline void __fastcall SendNVSEMessage(JG_NVSE_MESSAGE_ID aeID, T& arData) {
		g_msgInterface->Dispatch(g_pluginHandle, aeID, &arData, sizeof(T), nullptr);
	}

	inline void __fastcall SendNVSEMessage(JG_NVSE_MESSAGE_ID aeID) {
		g_msgInterface->Dispatch(g_pluginHandle, aeID, nullptr, 0, nullptr);
	}
}