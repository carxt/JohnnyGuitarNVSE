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
DEFINE_COMMAND_PLUGIN(IsBSALoaded, , false, kParams_OneString);