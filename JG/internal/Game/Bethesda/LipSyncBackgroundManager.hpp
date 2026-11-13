#pragma once

#include "LockFreeMap.hpp"
#include "LipTask.hpp"

class MobileObject;

class LipSyncBackgroundManager {
public:
	LockFreeMap<MobileObject*, NiPointer<LipTask>> kLipMap;
};

ASSERT_SIZE(LipSyncBackgroundManager, 0x40);