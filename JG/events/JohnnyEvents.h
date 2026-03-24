#pragma once
#include "GameScript.h"
namespace JohnnyEvents {

	void RegisterOnDying(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnStartQuest(Script* script, void** filters,  bool toggle, uint32_t userFlags = 0);
	void RegisterOnStopQuest(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnFailQuest(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnCompleteQuest(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnSeenDataUpdate(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnLimbGone(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnChallengeComplete(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnCrosshair(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnSettingsUpdate(Script* script, bool toggle, uint32_t userFlags = 0);
	void RegisterOnAddPerk(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnRemovePerk(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnActorValueChange(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnProcessLevelChange(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnRadioPostSoundAttach(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnInputSwitch(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnSleepWait(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnRender(Script* script, bool toggle, uint32_t userFlags = 0);
	void RegisterOnNPCResponse(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnGeneralSubtitle(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnReputationChange(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnNPCActorValueChange(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);
	void RegisterOnTakeBackItem(Script* script, void** filters, bool toggle, uint32_t userFlags = 0);


	void Install();
	void Reset();
	void Update();
}