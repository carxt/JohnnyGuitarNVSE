#include "AILinearTaskThreadManager.hpp"

// GAME - 0x8C7AA0
bool AILinearTaskThreadManager::ShouldQueue3DTask() {
	return CdeclCall<bool>(0x8C7AA0);
}

// GAME - 0x713D90
bool AILinearTaskThreadManager::GetRunningThreads() {
	return CdeclCall<bool>(0x713D90);
}