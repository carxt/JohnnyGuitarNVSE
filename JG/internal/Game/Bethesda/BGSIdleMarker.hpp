#pragma once

#include "TESBoundObject.hpp"
#include "BGSIdleCollection.hpp"

class BGSIdleMarker : public TESBoundObject, public BGSIdleCollection {
public:
    BGSIdleMarker();
    ~BGSIdleMarker();

    TESFORM_TYPE(BGSIdleMarker);
};

#ifdef GAME
ASSERT_SIZE(BGSIdleMarker, 0x40);
#else
ASSERT_SIZE(BGSIdleMarker, 0x64);
#endif