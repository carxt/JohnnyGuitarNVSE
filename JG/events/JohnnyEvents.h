#pragma once
#include "GameScript.h"
namespace JohnnyEvents {

	void RegisterOnDying(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnStartQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnStopQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnFailQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnCompleteQuest(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnSeenDataUpdate(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnLimbGone(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnChallengeComplete(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnCrosshair(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnSettingsUpdate(Script* apScript, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnAddPerk(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnRemovePerk(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnActorValueChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnProcessLevelChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnRadioPostSoundAttach(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnInputSwitch(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnSleepWait(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnRender(Script* apScript, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnNPCResponse(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnGeneralSubtitle(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnReputationChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnNPCActorValueChange(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);
	void RegisterOnTakeBackItem(Script* apScript, void** apFilters, bool abToggle, uint32_t auiUserFlags = 0);

	void Install();
	void Reset();
	void Update();
}