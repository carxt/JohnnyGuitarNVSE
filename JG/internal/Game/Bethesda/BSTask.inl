#pragma once

#include "BSTask.hpp"

// GAME - 0x92C870
template<typename T>
inline void BSTask<T>::IncRefCount() {
	InterlockedIncrement(&uiRefCount);
}

// GAME - 0x44DD60
// GECK - 0x4BBB60
template<typename T>
inline void BSTask<T>::DecRefCount() {
	if (!InterlockedDecrement(&uiRefCount))
		delete this;
}

// GAME - 0x449190
template<typename T>
inline bool BSTask<T>::SwitchState(BS_TASK_STATE aeCurrentState, BS_TASK_STATE aeNewState) {
	return InterlockedCompareExchange(reinterpret_cast<LONG*>(&eState), LONG(aeNewState), LONG(aeCurrentState)) == aeCurrentState;
}

// GAME - 0x69B080
template<typename T>
inline bool BSTask<T>::IsPending() const {
	return eState == BS_TASK_STATE_PENDING;
}

// GAME - 0x5287E0
template<typename T>
inline bool BSTask<T>::IsCompleted() const {
	return eState == BS_TASK_STATE_COMPLETED;
}

template<typename T>
inline bool BSTask<T>::IsCancelled() const {
	return eState == BS_TASK_STATE_CANCELED;
}

// GAME - 0x44E0D0
template<typename T>
inline T BSTask<T>::GetKey() const {
	return iKey;
}

template<typename T>
inline uint8_t BSTask<T>::GetFileIndexFromKey() const {
	return (iKey >> 56) & 0xFF;
}
