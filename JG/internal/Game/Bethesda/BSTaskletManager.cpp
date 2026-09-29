#include "BSTaskletManager.hpp"

// GAME - 0xB00A00
// GECK - 0x8A2AD0
BSTaskletManager* BSTaskletManager::GetSingleton() {
#ifdef GAME
	return CdeclCall<BSTaskletManager*>(0xB00A00);
#else
	return CdeclCall<BSTaskletManager*>(0x8A2AD0);
#endif
}

// GAME - 0xB00A80
// GECK - 0x8ACE80
bool BSTaskletManager::CreateTaskGroup(BSTaskletGroup& arGroup) {
#ifdef GAME
	return ThisCall<bool>(0xB00A80, this, &arGroup);
#else
	return ThisCall<bool>(0x8ACE80, this, &arGroup);
#endif
}

// GAME - 0xB00AE0
// GECK - 0x8ACEE0
bool BSTaskletManager::OpenTaskGroup(BSTaskletGroup& arGroup) {
#ifdef GAME
	return ThisCall<bool>(0xB00AE0, this, &arGroup);
#else
	return ThisCall<bool>(0x8ACEE0, this, &arGroup);
#endif
}

// GAME - 0xB00B40
// GECK - 0x8ACF40
bool BSTaskletManager::AttachTask(BSTaskletGroup& arGroup, BSTasklet& arTask, bool abLastTask) {
#ifdef GAME
	return ThisCall<bool>(0xB00B40, this, &arGroup, &arTask, abLastTask);
#else
	return ThisCall<bool>(0x8ACF40, this, &arGroup, &arTask, abLastTask);
#endif
}

// GAME - 0xB00BC0
// GECK - 0x8ACFC0
bool BSTaskletManager::CloseTaskGroup(BSTaskletGroup& arGroup) {
#ifdef GAME
	return ThisCall<bool>(0xB00BC0, this, &arGroup);
#else
	return ThisCall<bool>(0x8ACFC0, this, &arGroup);
#endif
}

// GAME - 0xB00C20
// GECK - 0x8AD020
void BSTaskletManager::DestroyTaskGroup(BSTaskletGroup& arGroup) {
#ifdef GAME
	ThisCall(0xB00C20, this, &arGroup);
#else
	ThisCall(0x8AD020, this, &arGroup);
#endif
}
