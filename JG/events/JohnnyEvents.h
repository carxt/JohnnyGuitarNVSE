#pragma once
#include "functions\fn_common.h"

DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnDyingEventHandler, SetOnDyingEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnStartQuestEventHandler, SetOnStartQuestEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnStopQuestEventHandler, SetOnStopQuestEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnySeenDataEventHandler, SetSeenDataEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnLimbGoneEventHandler, SetOnLimbGoneEventHandler, , false, kParams_Event_OneForm_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnChallengeCompleteEventHandler, SetOnChallengeCompleteEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnCrosshairEventHandler, SetOnCrosshairEventHandler, , false, kParams_Event_OneForm_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnFailQuestEventHandler, SetOnFailQuestEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnCompleteQuestEventHandler, SetOnCompleteQuestEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnSettingsUpdateEventHandler, SetOnSettingsUpdateEventHandler, , false, kParams_Event);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnAddPerkEventHandler, SetOnAddPerkEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnRemovePerkEventHandler, SetOnRemovePerkEventHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnRenderUpdateEventHandler, SetOnRenderUpdateEventHandler, , false, kParams_Event_OptionalFlag);
DEFINE_COMMAND_ALT_PLUGIN(SetOnActorValueChangeEventHandler, SetJohnnyOnActorValueChangeEventHandler, , false, kParams_Event_OneInt);
DEFINE_COMMAND_PLUGIN(SetOnProcessLevelChangeEventHandler, , false, kParams_Event_OneForm_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnRadioPostSoundAttachEventHandler, SetOnRadioPostSoundHandler, , false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnKeyboardControllerSelectionChangeEventHandler, SetOnKBCTrlUIDeltaHandler, , false, kParams_Event_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetJohnnyOnSleepWaitEventHandler, SetONSleepWEventHandler, , false, kParams_Event_OneInt);
DEFINE_COMMAND_PLUGIN(SetOnTakeBackItemEventHandler, , false, kParams_Event_TwoForms);
DEFINE_COMMAND_PLUGIN(SetOnNPCResponseEventHandler, , false, kParams_Event_OneInt);
DEFINE_COMMAND_PLUGIN(SetOnGeneralSubtitleEventHandler, "Fires upon the display of a General Subtitle", false, kParams_Event_OneInt);
DEFINE_COMMAND_PLUGIN(SetOnReputationChangeEventHandler, "Fires upon the change of a reputation", false, kParams_Event_OneForm);
DEFINE_COMMAND_ALT_PLUGIN(SetOnNPCActorValueChangeEventHandler, SetJohnnyOnNPCActorValueEventHandler, , false, kParams_Event_OneForm_OneInt)


namespace JohnnyEvents {


	void Install();
	void Reset();
	void Update();
}