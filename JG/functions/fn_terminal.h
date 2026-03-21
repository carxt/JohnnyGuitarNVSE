#pragma once
#include "fn_common.h"

DEFINE_COMMAND_PLUGIN(AddTerminalMenuItem, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemText, , false, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemText, , false, kParams_OneForm_TwoInts_OneString);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemNote, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemNote, , false, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemSubmenu, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemSubmenu, , false, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemCount, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(RemoveTerminalMenuItem, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemFlags, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemFlags, , false, kParams_OneForm_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(RefreshTerminalMenu, rtm, , false, nullptr);

