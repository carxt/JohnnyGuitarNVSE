#pragma once
#include "fn_common.h"
// Functions that operate on files
DEFINE_COMMAND_PLUGIN(MD5File, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SHA1File, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetPixelFromBMP, , false, kParams_BMP);
DEFINE_COMMAND_PLUGIN(GetTextureWidth, , false, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetTextureHeight, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetTextureFormat, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetTextureMipMapCount, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(PlaySoundFile, , false, kParams_OneString_ThreeOptionalInts);
DEFINE_COMMAND_PLUGIN(StopSoundFile, , false, nullptr);
DEFINE_COMMAND_PLUGIN(IsBSALoaded, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(PlaySoundFromPath, , false, kParams_OneString_OneOptionalFloat_FourOptionalInts);
DEFINE_COMMAND_PLUGIN(PlaySound3DFromPath, , true, kParams_OneString_OneOptionalFloat_ThreeOptionalInts);
DEFINE_COMMAND_PLUGIN(StopSoundFromPath, , false, kParams_OneString_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(StopSound3DFromPath, , true, kParams_OneString_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(IsSoundPlayingFromPath, , false, kParams_OneString_OneOptionalObjectRef);

