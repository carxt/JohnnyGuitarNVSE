#pragma once
#include "fn_common.h"


DEFINE_COMMAND_PLUGIN(SetBipedIconPathAlt, , false, kParams_OneString_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetWorldSpaceMapTexture, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetWorldSpaceMapTexture, , false, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarker, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetCustomMapMarkerIcon, , true, nullptr);
DEFINE_COMMAND_PLUGIN(SetCustomMapMarkerIcon, , false, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(QueueCinematicText, , false, kParams_TwoStrings_OneOptionalString_FourOptionalInts);
DEFINE_COMMAND_PLUGIN(QueueObjectiveText, , false, kParams_OneString_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetSystemColor, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetSystemColorAlt, , false, kParams_OneInt_ThreeScriptVars);
DEFINE_COMMAND_ALT_PLUGIN(SetCustomReputationChangeIcon, scrci, , false, kParams_OneForm_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(GetExtraMiscStat, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(ModExtraMiscStat, , false, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(InitExtraMiscStat, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(ShowBarberMenuEx, , false, kParams_OneInt_OneOptionalForm);
DEFINE_COMMAND_ALT_PLUGIN(PushUIQuestToTop, PushSelectedQuestInterfaceListEntryToTheTopOfThePipBoyQuestLogInterfaceImmediately, , false, kParams_OneQuest);
DEFINE_COMMAND_PLUGIN(DumpQuestObjectiveList, , false, nullptr); //DO NOT REGISTER YET.
DEFINE_COMMAND_PLUGIN(GetSleepWaitMenuState, , false, nullptr);
DEFINE_CMD_ALT_COND_PLUGIN(IsMenuPaused, , "", false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetHUDVisibilityOverride, "Sets HUD element visibility override flags", false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetHUDVisibilityOverride, "Gets HUD element visibility override flags", false, nullptr);
DEFINE_COMMAND_PLUGIN(UpdateRepairMenu, , false, nullptr);
DEFINE_COMMAND_PLUGIN(SetWeaponScopeUIModel, , false, kParams_OneString_OneOptionalObject);
DEFINE_COMMAND_PLUGIN(ToggleWeaponScopeUIModel, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(ClearWeaponScopeUIModel, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetMenuItemListIndex, , true, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SelectMenuItemListIndex, , false, kParams_OneInt_OneOptionalInt);
