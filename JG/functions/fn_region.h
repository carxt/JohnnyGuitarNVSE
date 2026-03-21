#pragma once
#include "fn_common.h"
// Region functions
DEFINE_COMMAND_PLUGIN(GetRegionWeatherOverride, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherOverride, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetRegionWeatherPriority, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionWeatherPriority, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(IsWeatherInRegion, , false, kParams_TwoForms);
DEFINE_COMMAND_PLUGIN(RemoveRegionWeather, , false, kParams_TwoForms);
DEFINE_COMMAND_PLUGIN(AddRegionWeather, , false, kParams_OneForm_OneWeatherID_OneInt_OneOptionalGlobal);
DEFINE_COMMAND_PLUGIN(GetRegionWeathers, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(ClearRegionWeathers, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetRegionMapName, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetRegionMapName, , false, kParams_OneForm_OneString);
DEFINE_COMMAND_PLUGIN(GetNthRegionWeatherType, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetNthRegionWeatherChance, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetNthRegionWeatherGlobal, , false, kParams_OneForm_OneInt);

