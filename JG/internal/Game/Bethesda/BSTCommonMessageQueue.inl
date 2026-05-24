#pragma once

#include "BSTCommonMessageQueue.hpp"

template<class T>
inline BSTCommonMessageQueue<T>::BSTCommonMessageQueue() {
}

template<class T>
inline BSTCommonMessageQueue<T>::~BSTCommonMessageQueue() {
}

// GAME - 0x9054A0
template<class T>
inline bool BSTCommonMessageQueue<T>::Push(const T& arMessage) {
	kLock.Lock();
	bool bResult = DoTryPush(arMessage);
	kLock.Unlock();
	return bResult;
}

// GAME - 0x6EC0D0
template<class T>
inline bool BSTCommonMessageQueue<T>::TryPush(const T& arMessage) {
	if (!kLock.TryLock())
		return false;

	bool bResult = DoTryPush(arMessage);
	kLock.Unlock();
	return bResult;
}

// GAME - 0x905510
template<class T>
inline bool BSTCommonMessageQueue<T>::Pop(T& arMessage) {
	kLock.Lock();
	bool bResult = DoTryPop(arMessage);
	kLock.Unlock();
	return bResult;
}

// GAME - 0x6EC390
template<class T>
inline bool BSTCommonMessageQueue<T>::TryPop(T& arMessage) {
	if (!kLock.TryLock())
		return false;

	bool bResult = DoTryPop(arMessage);
	kLock.Unlock();
	return bResult;
}

template<class T>
inline bool BSTCommonMessageQueue<T>::DoTryPush(const T& arMessage) {
	return false;
}

template<class T>
inline bool BSTCommonMessageQueue<T>::DoTryPop(T& arMessage) {
	return false;
}
