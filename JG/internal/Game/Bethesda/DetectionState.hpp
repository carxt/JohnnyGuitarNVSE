#pragma once

#include "Gamebryo/NiPoint3.hpp"
#include "CombatTimeStamp.hpp"
#include "BSEnums.hpp"

class Actor;

class DetectionState {
public:
	Actor*			pActor;
	DETECTION_LEVEL eDetectionLevel;
	int32_t			iLevel;
	NiPoint3		kLastPositionDetected;
	CombatTimeStamp	kLastTimeDetected;
	bool			b360View;
	bool			bCombat;
	bool			bLineofSight;
	bool			bEvaluated;
	int32_t			iDetectedEventLevel;
};

ASSERT_SIZE(DetectionState, 0x24);