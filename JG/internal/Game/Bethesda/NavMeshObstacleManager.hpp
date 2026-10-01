#pragma once

#include "BSCriticalSection.hpp"
#include "BSSimpleList.hpp"
#include "BSSpinLock.hpp"
#include "BSTaskletGroup.hpp"
#include "LockFreeQueue.hpp"
#include "ReferenceObstacleArray.hpp"
#include "Gamebryo/NiNode.hpp"
#include "Gamebryo/NiTMap.hpp"

class NavMesh;
class ObstacleTaskData;
class bhkRigidBody;
class TESObjectREFR;
class bhkObstacleDeactivationListener;
class bhkObstacleRemovalListener;

class NavMeshObstacleManager {
public:
	struct _BackgroundState {
		enum State {
			PROCESSING_OBSTACLES			= 0,
			WAITING_FOR_PATH_MANAGER_PAUSE	= 1,
			PAUSE_REQUESTED					= 2,
			PAUSED							= 3,
		};
	};
	using BackgroundState = _BackgroundState::State;

	BSCriticalSection									kCriticalSection;
	bool												bUpdateAllObstacles;
	NiTMap<FormID, NiPointer<ReferenceObstacleArray>>	kObstacleArrays;
	BSSimpleList<TESObjectREFR*>						kQueuedRefsToAdd;
	BSSimpleList<FormID>								kQueuedRefsToRemove;
	BSSimpleList<NiPointer<ObstacleData>>				kObstaclesToUpdate;
	LockFreeQueue<bhkRigidBody*>						kObstaclesToAddToUpdate;
	LockFreeQueue<bhkRigidBody*>						kObstaclesToRemoveFromUpdate;
	NiTMap<bhkRigidBody*, NiPointer<ObstacleData>>		kRigidBodyMap;
	BSSimpleList<TESObjectREFR*>						kQueuedDoorsToAdd;
	BSSimpleList<FormID>								kQueuedDoorsToRemove;
	NiTMap<FormID,NiPointer<ReferenceObstacleArray>>	kOpenDoorMap;
	NiTMap<FormID,NiPointer<ReferenceObstacleArray>>	kClosedDoorMap;
	bhkObstacleDeactivationListener*					pObstacleDeactivationListener;
	bhkObstacleRemovalListener*							pObstacleRemovalListener;
	BSTaskletGroup										kTaskletGroup;
	NiTMap<uint32_t, ObstacleTaskData*>					kCurrentNavMeshTasks;
	BSSimpleArray<ObstacleTaskData*>					kBackgroundTasks;
	BSSimpleArray<ObstacleTaskData*>					kProcessedTasks;
	BSSpinLock											kProcessedTaskLock;
	BSSimpleList<FormID>								kQueuedNavMeshesToEnable;
	BSSimpleList<FormID>								kQueuedNavMeshesToDisable;
	BackgroundState										eState;
	float												fTimeToNextSwap;
	bool												bDrawObstacles;
	NiNodePtr											spDebug3D;
	char												kMainThreadPerfTimer;
	char												kTaskletsPerfTimer;

	static NavMeshObstacleManager* GetSingleton();
	
	void AddObstacleForReference(TESObjectREFR* apReference);
	void RemoveObstacleForReference(TESObjectREFR* apReference);

	uint32_t GetBackgroundTaskCount();
};

ASSERT_SIZE(NavMeshObstacleManager, 0x1C0);