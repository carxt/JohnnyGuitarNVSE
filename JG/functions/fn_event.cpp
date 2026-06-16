#include "fn_event.h"
#include <decoding.h>
#include <events/EventFramework.h>
#include <events/JohnnyEvents.hpp>
#include <GameObjects.h>

bool Cmd_SetJohnnyOnLimbGoneEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterFormInt::Data filter = { nullptr, -1 }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.form, &filter.intID) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnLimbGone(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}
bool Cmd_SetJohnnyOnSettingsUpdateEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnSettingsUpdate(script, setOrRemove > 0);
	}
	return true;
}
bool Cmd_SetJohnnyOnCrosshairEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterFormInt::Data filter = { nullptr, -1 };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.form, &filter.intID) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnCrosshair(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetOnActorValueChangeEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterFormInt::Data filter = { PlayerCharacter::GetSingleton(), -1 };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.intID) && script && IS_TYPE(script, Script) && filter.intID <= kAVCode_DamageThreshold) {
		JohnnyEvents::RegisterOnActorValueChange(script, (void**)&filter, setOrRemove > 0, flags);
	}
	return true;
}

bool Cmd_SetOnNPCActorValueChangeEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterFormInt::Data filter = { nullptr, -1 };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.form, &filter.intID) && script && IS_TYPE(script, Script) && filter.intID <= kAVCode_DamageThreshold) {
		JohnnyEvents::RegisterOnNPCActorValueChange(script, (void**)&filter, setOrRemove > 0, flags);
	}
	return true;
}
bool Cmd_SetJohnnyOnRemovePerkEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnRemovePerk(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}
bool Cmd_SetJohnnyOnAddPerkEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnAddPerk(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}
bool Cmd_SetJohnnyOnChallengeCompleteEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnChallengeComplete(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}
bool Cmd_SetJohnnySeenDataEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnSeenDataUpdate(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}
bool Cmd_SetJohnnyOnDyingEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnDying(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetJohnnyOnStartQuestEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnStartQuest(script, (void**)filter, setOrRemove > 0);
	}

	return true;
}

bool Cmd_SetJohnnyOnStopQuestEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnStopQuest(script, (void**)filter, setOrRemove > 0);
	}

	return true;
}

bool Cmd_SetJohnnyOnCompleteQuestEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnCompleteQuest(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetJohnnyOnFailQuestEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnFailQuest(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetJohnnyOnRenderUpdateEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	uint32_t flags = 0;
	uint32_t optionalFlags = 0;


	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &optionalFlags) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnRender(script, setOrRemove > 0, optionalFlags);
	}

	return true;
}

bool Cmd_SetOnProcessLevelChangeEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterFormInt::Data filter = { nullptr, -1 }; // you always need to make a array of pointers the size of the maximum arguments in the filter, it doesn't matter if most are empty. Framework caveat.
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.form, &filter.intID) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnProcessLevelChange(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}


bool Cmd_SetJohnnyOnRadioPostSoundAttachEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnRadioPostSoundAttach(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetJohnnyOnKeyboardControllerSelectionChangeEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterInt::Data filter{};
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.intID) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnInputSwitch(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}




bool Cmd_SetJohnnyOnSleepWaitEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterInt::Data filter{};
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.intID) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnSleepWait(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetOnTakeBackItemEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[2] = { nullptr, nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0], &filter[1]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnTakeBackItem(script, (void**)filter, setOrRemove > 0);
	}
	return true;
}


bool Cmd_SetOnNPCResponseEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	FilterInt::Data filter{};
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter.intID) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnNPCResponse(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetOnGeneralSubtitleEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnGeneralSubtitle(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}

bool Cmd_SetOnReputationChangeEventHandler_Execute(COMMAND_ARGS) {
	uint32_t setOrRemove = 0;
	Script* script = nullptr;
	TESForm* filter[1] = { nullptr };
	uint32_t flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &setOrRemove, &script, &flags, &filter[0]) && script && IS_TYPE(script, Script)) {
		JohnnyEvents::RegisterOnReputationChange(script, (void**)&filter, setOrRemove > 0);
	}
	return true;
}