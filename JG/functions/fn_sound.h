#pragma once
#include "fn_common.h"

DEFINE_COMMAND_PLUGIN(StopSoundAlt, , false, kParams_TwoForms_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(StopSoundLooping, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(PlaySoundFade, , false, kParams_OneForm_OneFloat);
DEFINE_COMMAND_PLUGIN(PlaySoundFile, , false, kParams_OneString_ThreeOptionalInts);
DEFINE_COMMAND_PLUGIN(StopSoundFile, , false, nullptr);
DEFINE_COMMAND_PLUGIN(PlaySoundFromPath, , false, kParams_OneString_OneOptionalFloat_FourOptionalInts);
DEFINE_COMMAND_PLUGIN(PlaySound3DFromPath, , true, kParams_OneString_OneOptionalFloat_ThreeOptionalInts);
DEFINE_COMMAND_PLUGIN(StopSoundFromPath, , false, kParams_OneString_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(StopSound3DFromPath, , true, kParams_OneString_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(IsSoundPlayingFromPath, , false, kParams_OneString_OneOptionalObjectRef);