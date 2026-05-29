#pragma once

#include "TESBoundObject.hpp"
#include "BGSIdleCollection.hpp"

class BGSIdleMarker : public TESBoundObject, public BGSIdleCollection {
public:
    BGSIdleMarker();
    ~BGSIdleMarker();

    TESFORM_TYPE(BGSIdleMarker);
};

ASSERT_SIZE(BGSIdleMarker, 0x40);