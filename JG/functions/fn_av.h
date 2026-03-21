#pragma once
#include "fn_common.h"
// Alternative actor value functions to allow using numeric AV IDs
// Deprecated, xNVSE allows using AV codes with regular functions in parentheses
DEFINE_COMMAND_ALT_PLUGIN(GetActorValueAlt, GetAVAlt, , true, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(SetActorValueAlt, SetAVAlt, , true, kParams_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(GetBaseActorValueAlt, GetBaseAVAlt, , true, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(ForceActorValueAlt, ForceAVAlt, , true, kParams_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(DamageActorValueAlt, DamageAVAlt, , true, kParams_OneInt_OneFloat);
DEFINE_COMMAND_ALT_PLUGIN(RestoreActorValueAlt, RestoreAVAlt, , true, kParams_OneInt_OneFloat);
DEFINE_COMMAND_ALT_PLUGIN(ModActorValueAlt, ModAVAlt, , true, kParams_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(GetThresholdedActorValue, GetThresholdAV, , true, kParams_OneActorValue);
