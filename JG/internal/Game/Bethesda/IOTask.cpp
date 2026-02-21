#include "IOTask.hpp"

// GAME - 0x440540
// GECK - 0x6090D0
IOTask::IOTask(IO_TASK_PRIORITY aePriority) {
    SetIOTaskPriority(aePriority);
}

IOTask::~IOTask() {
}

void IOTask::PostProcess() {
}

// GAME - 0x43DB70
// GECK - 0x4BBC90
void IOTask::GenerateKey() {
#ifdef GAME
	ThisCall(0x43DB70, this);
#else
	ThisCall(0x4BBC90, this);
#endif
}

// GAME - 0x440660
// GECK - 0x609130
void IOTask::Requeue(IO_TASK_PRIORITY aeNewPriority) {
#ifdef GAME
    ThisCall(0x440660, this, aeNewPriority);
#else
	ThisCall(0x609130, this, aeNewPriority);
#endif
}

// GAME - 0x4405B0
void IOTask::SetIOTaskPriority(IO_TASK_PRIORITY aePriority) {
    SetPriority(aePriority);
}

// GAME - 0x43CC80
uint8_t IOTask::GetPriority() const {
    return GetPriorityFromKey(iKey);
}

// GAME - 0x4405D0
void IOTask::SetPriority(uint8_t aePriority) {
    iKey = (uint64_t(aePriority) << 16) + (iKey & 0xFFFFFFFFFF00FFFF);
}

// GAME - 0x43DBB0
void IOTask::SetKey(uint8_t aeFileIndex, uint32_t auiOffset, uint8_t aePriority, uint16_t ausCounter) {
    iKey = uint64_t(ausCounter) + (uint64_t(auiOffset) << 24) + (uint64_t(aePriority) << 16) + (uint64_t(aeFileIndex) << 56);
}

// GAME - 0x43D690
void IOTask::AddToPostProcessQueue() {
#ifdef GAME
	ThisCall(0x43D690, this);
#endif
}

// GAME - 0x43CCA0
uint8_t IOTask::GetPriorityFromKey(int64_t& arKey) {
    return arKey >> 16;
}

// GAME - 0x43DC10
uint32_t IOTask::GetNextCounter() {
    return InterlockedIncrement(&iStaticCounter);
}

// GAME - 0x43DC30
uint32_t IOTask::GetNextOffset() {
    return InterlockedIncrement(&iStaticOffset);
}
