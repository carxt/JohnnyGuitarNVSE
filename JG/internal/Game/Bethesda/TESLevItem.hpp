#pragma once

#include "TESBoundObject.hpp"
#include "TESLeveledList.hpp"

class TESLevItem : public TESBoundObject, public TESLeveledList {
public:
    TESLevItem();
    ~TESLevItem();

    TESFORM_TYPE(TESLevItem);
};

#ifdef GAME
ASSERT_SIZE(TESLevItem, 0x4C)
#else
ASSERT_SIZE(TESLevItem, 0x68)
#endif