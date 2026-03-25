#pragma once

#include "Bethesda/BSSimpleList.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/FormID.hpp"
#include "Gamebryo/NiPoint3.hpp"

class MediaLocationController;
class AudioBuoyMarkerInfo;
class TESObjectREFR;

class AudioMarkerData {
public:
    TESFullName                         kLocationName;
    float                               fSecondLayerPercent;
    float                               fThirdLayerPercent;
    float                               fRadius;
    NiPoint3                            kLocation;
    FormID                              uiMediaLocationController;
    bool                                bUseController;
    BSSimpleList<AudioBuoyMarkerInfo*>  kBuoyMarkers;
};

ASSERT_SIZE(AudioMarkerData, 0x34);