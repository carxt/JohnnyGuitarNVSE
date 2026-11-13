#pragma once

#include "DetectionTaskData.hpp"
#include "ActorsScriptTaskData.hpp"
#include "ActorUpdateTaskData.hpp"
#include "AnimationTaskData.hpp"
#include "MobileObjectMessage.hpp"
#include "MovementTaskData.hpp"
#include "PackageUpdateTaskData.hpp"
#include "BSTStaticFreeList.hpp"

class AITaskManager {
public:
	DetectionTaskData							kDetectionTaskData;
	AnimationTaskData							kAnimationTaskData;
	PackageUpdateTaskData						kPackageUpdateTaskData;
	ActorUpdateTaskData							kActorUpdateTaskData;
	ActorsScriptTaskData						kActorsScriptTaskData;
	MovementTaskData							kMovementTaskData;
	BSTStaticFreeList<MobileObjectMessage,4096> kMessagePool;
	bool										bRunningTasksDuringRendering;
};

ASSERT_SIZE(AITaskManager, 0x10184);