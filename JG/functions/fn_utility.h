#pragma once
// Utility or miscellaneous functions
#include "fn_common.h"

DEFINE_COMMAND_ALT_PLUGIN(GetEditorID, GetEdID, , false, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetJohnnyPatch, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetTimePlayed, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(AsmBreak, , false, nullptr);
DEFINE_COMMAND_PLUGIN(RefAddr, , false, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(RefAddrxData, , true, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(EditorIDToFormID, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetDefaultHeapSize, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetLinearVelocity, , true, kParams_FourStrings);
DEFINE_COMMAND_PLUGIN(IsLevelUpMenuEnabled, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetPipBoyMode, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetFormOverrideIndex, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetSequenceAnimGroup, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(ar_SortEditor, , false, kParams_OneInt_OneOptionalInt)
DEFINE_COMMAND_PLUGIN(SetUIUpdateSound, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(ar_IsFormInList, , false, kParams_OneInt_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(IsDLLLoaded, , false, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(RefreshIdle, , true, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(ExitGameAlt, , false, nullptr);
DEFINE_COMMAND_PLUGIN(UpdateCrosshairPrompt, , false, nullptr);
DEFINE_COMMAND_PLUGIN(SetOptionalBone, , true, kParams_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(GetOptionalBone, , true, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(TriggerScreenSplatterEx, , false, kSplatterParams);
DEFINE_COMMAND_PLUGIN(SetViewmodelClipDistance, , false, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(GetViewmodelClipDistance, , false, nullptr);
DEFINE_COMMAND_PLUGIN(SetBlockTransform, , true, kTransformParams);
DEFINE_COMMAND_PLUGIN(SetCameraTranslate, , false, kParams_OneBoolThreeFloats);
DEFINE_COMMAND_PLUGIN(SetCameraRotate, , false, kParams_OneBoolOneIntOneFloat);
DEFINE_COMMAND_PLUGIN(DumpIconMap, , false, nullptr);
DEFINE_COMMAND_PLUGIN(RollCredits, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetAllGameRadios, , false, nullptr);
DEFINE_COMMAND_PLUGIN(GetAvailableRadios, , true, nullptr);
DEFINE_COMMAND_PLUGIN(NullArgs, , false, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(NullNoArgs, , false, nullptr);
DEFINE_CMD_ALT_COND_PLUGIN(GameGetSecondsPassed, GGetSecPass, , false, nullptr);
DEFINE_COMMAND_PLUGIN(ar_Shuffle, , false, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetCurrentSkyColor, , false, kParams_OneInt_ThreeScriptVars);