#pragma once

#include "BSTask.hpp"

// GAME - 0x449090
template<typename T>
inline BSTask<T>::BSTask() : uiRefCount(0), eState(BS_TASK_STATE_PENDING), iKey(0) {
	InterlockedIncrement(&uiTotalTaskCount);
}

// GAME - 0x4490E0
template<typename T>
inline BSTask<T>::~BSTask() {
	InterlockedDecrement(&uiTotalTaskCount);
}

template<typename T>
inline void BSTask<T>::Cancel(BS_TASK_STATE aeState, BSTask<T>* apParent) {
}

template<typename T>
inline bool BSTask<T>::GetDescription(const char* apDescription, size_t aiBufferSize) {
	return false;
}
