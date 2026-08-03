#include "IOManager.hpp"

IOManager* IOManager::GetSingleton() {
#ifdef GAME
    return *reinterpret_cast<IOManager**>(0x1202D98);
#else
    return *reinterpret_cast<IOManager**>(0xF2CDC4);
#endif
}

// GAME - 0x446DA0
uint32_t IOManager::GetPostProcessQueueCount() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x446DA0, this);
#else
    return pPostProcessQueue->GetCount();
#endif
}

// GAME - 0x43D6B0
// GECK - 0x4C4DB0
void IOManager::AddPostProcessTask(IOTask* apTask) {
#ifdef GAME
    ThisCall(0x43D6B0, this, apTask);
#else
    ThisCall(0x4C4DB0, this, apTask);
#endif
}

// GAME - 0xC3DF40
// GECK - 0x9D9B80
void IOManager::RequeueTask(IOTask* apTask, IO_TASK_PRIORITY aeNewPriority) {
#ifdef GAME
    ThisCall(0xC3DF40, this, apTask, aeNewPriority);
#else
    ThisCall(0x9D9B80, this, apTask, aeNewPriority);
#endif
}

// GAME - 0xC3DBF0
// GECK - 0x9D9830
bool IOManager::UpdateQueue() {
#ifdef GAME
    return ThisCall<bool>(0xC3DBF0, this);
#else
    return ThisCall<bool>(0x9D9830, this);
#endif
}

// GAME - 0xC3E310
// GECK - 0x9D9F50
void IOManager::Pause() {
#ifdef GAME
    ThisCall(0xC3E310, this);
#else
    ThisCall(0x9D9F50, this);
#endif
}

// GAME - 0xC3E340
// GECK - 0x9D9F80
void IOManager::Resume() {
#ifdef GAME
    ThisCall(0xC3E340, this);
#else
    ThisCall(0x9D9F80, this);
#endif
}

// GAME - 0x448DE0
bool IOManager::IsLoadingQueuedPriority() const {
    return eLoadingQueuedPriority != IO_TASK_PRIORITY::COUNT;
}
