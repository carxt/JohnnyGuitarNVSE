#include "BackgroundCloneThread.hpp"

// GAME - 0x446DE0
uint32_t BackgroundCloneThread::GetQueuedCount() const {
    return uiRunningCount + pProcessTaskQueue->GetCount();
}