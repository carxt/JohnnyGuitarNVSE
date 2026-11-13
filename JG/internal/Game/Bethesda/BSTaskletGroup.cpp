#include "BSTaskletGroup.hpp"
#ifdef EDITOR
#include "BSTaskletManager.hpp"
#endif

// GAME - 0x44DEE0
BSTaskletGroup::BSTaskletGroup() : pData(nullptr) {
}

BSTaskletGroup::BSTaskletGroup(BSTaskletGroupData* apData) : pData(apData) {
}

BSTaskletGroup::~BSTaskletGroup() {
}

BSTaskletGroupData* BSTaskletGroup::GetGroupData() const {
	return pData;
}

void BSTaskletGroup::SetGroupData(BSTaskletGroupData* apData) {
	pData = apData;
}

// GAME - 0x6C08E0
bool BSTaskletGroup::Open() {
#ifdef GAME
	return ThisCall<bool>(0x6C08E0, this);
#else
	return BSTaskletManager::GetSingleton()->OpenTaskGroup(*this);
#endif
}

// GAME - 0x6C5EC0
bool BSTaskletGroup::AttachTask(BSTasklet& arTask, bool abLastTask) {
#ifdef GAME
	return ThisCall<bool>(0x6C5EC0, this, &arTask, abLastTask);
#else
	return BSTaskletManager::GetSingleton()->AttachTask(*this, arTask, abLastTask);
#endif
}

// GAME - 0x6C09D0
bool BSTaskletGroup::Close() {
#ifdef GAME
	return ThisCall<bool>(0x6C09D0, this);
#else
	return BSTaskletManager::GetSingleton()->CloseTaskGroup(*this);
#endif
}

// GAME - 0x6EB670
void BSTaskletGroup::WaitForCompletion(bool abPoll) {
#ifdef GAME
	ThisCall(0x6EB670, this, abPoll);
#else
	if (pData && !pData->IsComplete())
		pData->WaitForCompletion(abPoll);
#endif
}

void BSTaskletGroup::SetMaxConcurrent(uint32_t auiMaxConcurrent) {
	if (pData)
		pData->SetMaxConcurrent(auiMaxConcurrent);
}
