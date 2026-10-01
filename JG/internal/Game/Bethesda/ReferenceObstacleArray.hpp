#pragma once

#include "ObstacleData.hpp"
#include "BSEnums.hpp"

class ReferenceObstacleArray : public NiRefObject {
public:
	FormID									uiFormID;
	BSSimpleArray<NiPointer<ObstacleData>>	kObstacles;
};

ASSERT_SIZE(ReferenceObstacleArray, 0x1C);