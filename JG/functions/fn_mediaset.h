#pragma once
#include "fn_common.h"
//Mediaset functions
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitNumeric, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitSound, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitString, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitNumeric, , false, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitSound, , false, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitString, , false, kParams_OneForm_OneInt_OneString);
DEFINE_CMD_ALT_COND_PLUGIN(AudioMarkerGetController, AMKGetCtrl, , true, nullptr);
DEFINE_CMD_ALT_COND_PLUGIN(AudioMarkerGetCurrent, AMKGetCur, , false, nullptr);
DEFINE_COMMAND_ALT_PLUGIN(AudioMarkerGetProperty, AMKGetProp, , true, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(AudioMarkerSetProperty, AMKSetProp, , true, kParams_OneInt_OneFloat);
DEFINE_COMMAND_ALT_PLUGIN(AudioMarkerSetController, AMKSetCtrl, , true, kParams_OneForm);

DEFINE_COMMAND_PLUGIN(GetAcousticSpace, , true, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetAcousticSpace, , true, kParams_OneForm_OneOptionalForm);


