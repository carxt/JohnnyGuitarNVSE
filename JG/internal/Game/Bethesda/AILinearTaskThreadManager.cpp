#include "AILinearTaskThreadManager.hpp"

// GAME - 0x8C7AA0
bool AILinearTaskThreadManager::ShouldQueue3DTask() {
	return CdeclCall<bool>(0x8C7AA0);
}