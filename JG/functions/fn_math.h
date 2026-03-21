#pragma once
#include "fn_common.h"
// Functions that perform mathematical calculations
DEFINE_COMMAND_PLUGIN(JGLegacyWorldToScreen, , false, kParamsProjectionArgsLegacy);
DEFINE_COMMAND_PLUGIN(Get3DDistanceBetweenNiNodes, , false, kParams_TwoRefs_TwoStrings);
DEFINE_COMMAND_PLUGIN(Get3DDistanceToNiNode, , true, kParams_OneString_ThreeFloats);
DEFINE_COMMAND_PLUGIN(Get3DDistanceFromHitToNiNode, , true, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetVector3DDistance, , false, kParams_SixFloats);
DEFINE_COMMAND_PLUGIN(Clamp, , false, kParams_ThreeFloats);
DEFINE_COMMAND_PLUGIN(Remap, , false, kParams_FiveFloats);
DEFINE_COMMAND_PLUGIN(Lerp, , false, kParams_ThreeFloats);
DEFINE_COMMAND_PLUGIN(Sign, , false, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(GetCameraTranslation, , FALSE, kParams_ThreeStrings_OneInt);
DEFINE_COMMAND_PLUGIN(WorldToScreen, , false, kParamsProjectionArgs);
DEFINE_COMMAND_PLUGIN(RGBtoHSV, , false, kParams_SixScriptVars);
DEFINE_COMMAND_PLUGIN(HSVtoRGB, , false, kParams_SixScriptVars);
DEFINE_COMMAND_PLUGIN(GetRGBColor, , false, kParams_ThreeInts);
DEFINE_COMMAND_PLUGIN(GetPackedPlayerFOV, , false, kParams_TwoScriptVars_OneOptionalScriptVar);
DEFINE_COMMAND_PLUGIN(GetPlayerCamFOV, , false, kParams_OneInt);

