#pragma once

#include "BGSNumericIDIndex.hpp"
#include "BGSChangeFlags.hpp"

#pragma pack(push, 1)
struct BGSSaveLoadFormHeader {
  BGSNumericIDIndex kFormIDIndex;
  BGSChangeFlags	uiChangeFlags;
  uint8_t			ucFormInfo;
  uint8_t			ucVersion;
};
#pragma pack(pop)

ASSERT_SIZE(BGSSaveLoadFormHeader, 0x9);