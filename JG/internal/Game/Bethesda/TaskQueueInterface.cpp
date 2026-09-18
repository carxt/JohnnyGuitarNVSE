#include "TaskQueueInterface.hpp"

// GAME - 0x4537B0
TaskQueueInterface* TaskQueueInterface::GetSingleton() {
	return *reinterpret_cast<TaskQueueInterface**>(0x11DF1A8);
}

// GAME - 0x87ACB0
void TaskQueueInterface::QueueBiped3DDetach(NiAVObject* apObject) {
	ThisCall(0x87ACB0, this, apObject);
}