#include "NavMeshObstacleManager.hpp"

// GAME - 0x6C0720
// GECK - 0x719050
NavMeshObstacleManager* NavMeshObstacleManager::GetSingleton() {
#ifdef GAME
	return CdeclCall<NavMeshObstacleManager*>(0x6C0720);
#else
	return CdeclCall<NavMeshObstacleManager*>(0x719050);
#endif
}

#ifdef GAME
// GAME - 0x6C0C30
void NavMeshObstacleManager::AddObstacleForReference(TESObjectREFR* apReference) {
	ThisCall(0x6C0C30, this, apReference);
}

// GAME - 0x6C0C80
void NavMeshObstacleManager::RemoveObstacleForReference(TESObjectREFR* apReference) {
	ThisCall(0x6C0C80, this, apReference);
}
#endif

// GAME - 0x6C3970
uint32_t NavMeshObstacleManager::GetBackgroundTaskCount() {
#ifdef GAME
	return ThisCall<uint32_t>(0x6C3970, this);
#else
	kProcessedTaskLock.Lock();
	const uint32_t uiCount = kBackgroundTasks.GetSize();
	kProcessedTaskLock.Unlock();
	return uiCount;
#endif
}