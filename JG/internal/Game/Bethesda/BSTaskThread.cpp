#include "BSTaskThread.hpp"

// GAME - 0x442600
void BSTaskThread::SignalTask() {
	if (!kTaskSemaphore.GetCount())
		kTaskSemaphore.Signal();
}

// GAME - 0x4424C0
void BSTaskThread::WaitTask() {
	kTaskSemaphore.Wait();
}

// GAME - 0x442530
void BSTaskThread::SignalPause() {
	kPauseSemaphore.Signal();
}

// GAME - 0x442510
void BSTaskThread::WaitPause() {
	kPauseSemaphore.Wait();
}

bool BSTaskThread::TestPauseSemaphore() {
	return kPauseSemaphore.Test();
}
