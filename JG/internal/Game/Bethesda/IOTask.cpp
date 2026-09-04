#include "IOTask.hpp"

// GAME - 0x4405B0
void IOTask::SetIOTaskPriority(IO_TASK_PRIORITY aePriority) {
#ifdef GAME
    ThisCall(0x4405B0, this, aePriority);
#else
    SetPriority(aePriority);
#endif
}

// GAME - 0x43CC80
uint8_t IOTask::GetPriority() const {
#ifdef GAME
    return ThisCall<uint8_t>(0x43CC80, this);
#else
    return GetPriorityFromKey(iKey);
#endif
}

// GAME - 0x4405D0
void IOTask::SetPriority(uint8_t aePriority) {
#ifdef GAME
    ThisCall(0x4405D0, this, aePriority);
#else
    iKey = (uint64_t(aePriority) << 16) + (iKey & 0xFFFFFFFFFF00FFFF);
#endif
}

// GAME - 0x43DBB0
void IOTask::SetKey(uint8_t aeFileIndex, uint32_t auiOffset, uint8_t aePriority, uint16_t ausCounter) {
#ifdef GAME
    ThisCall(0x43DBB0, this, aeFileIndex, auiOffset, aePriority, ausCounter);
#else
    iKey = uint64_t(ausCounter) + (uint64_t(auiOffset) << 24) + (uint64_t(aePriority) << 16) + (uint64_t(aeFileIndex) << 56);
#endif
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
