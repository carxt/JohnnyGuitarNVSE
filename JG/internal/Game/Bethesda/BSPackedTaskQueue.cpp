#include "BSPackedTaskQueue.hpp"

// GAME - 0x87A890
bool BSPackedTaskQueue::AddTask(BSPackedTask& arTask) {
    return kQueue.Push(arTask);
}

// GAME - 0x86CDD0
void BSPackedTaskQueue::Wait() {
    kSemaphore.Wait();
}
