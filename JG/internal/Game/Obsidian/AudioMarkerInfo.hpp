#pragma once

#include "AudioMarkerData.hpp"

class TESObjectREFR;

class AudioMarkerInfo {
public:
    TESObjectREFR*      pReference;
    AudioMarkerData*    pMarker;
};

ASSERT_SIZE(AudioMarkerInfo, 0x8);