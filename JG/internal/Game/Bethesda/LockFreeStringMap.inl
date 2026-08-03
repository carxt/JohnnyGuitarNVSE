#pragma once

#include "LockFreeStringMap.hpp"

#pragma region LockFreeStringMapIterator

template<class T>
inline LockFreeStringMap<T>::LockFreeStringMapIterator::LockFreeStringMapIterator() : LockFreeMap<const char*, T>::LockFreeMapIterator() {
	this->tLastKey = cBuffer;
	cBuffer[0] = 0;
}

template<class T>
inline LockFreeStringMap<T>::LockFreeStringMapIterator::~LockFreeStringMapIterator() {}

template<class T>
inline void LockFreeStringMap<T>::LockFreeStringMapIterator::ClearKey() {
	cBuffer[0] = 0;
};

#pragma endregion

#pragma region LockFreeStringMap

template<class T>
inline LockFreeStringMap<T>::LockFreeStringMap(uint32_t auiMaxThreads, uint32_t auiBucketCount, uint32_t auiDeleteBatchSize) : LockFreeMap<const char*, T>(auiMaxThreads, auiBucketCount, auiDeleteBatchSize) {
}

template<class T>
inline LockFreeStringMap<T>::~LockFreeStringMap() {
	this->RemoveAll(true);
}

template<class T>
inline uint32_t LockFreeStringMap<T>::GetBucketForKey(const char* apKey) {
	uint32_t uiHash = 0;
	while (*apKey) {
		uiHash = 33 * uiHash + *apKey++;
	}

	const uint32_t uiBucketCount = this->GetNumBuckets();
	return uiHash - (uiHash / uiBucketCount) * uiBucketCount;
}

template<class T>
inline void LockFreeStringMap<T>::DeleteKey(const char* apKey) {
	delete[] apKey;
}

template<class T>
inline const char* LockFreeStringMap<T>::CopyKey(const char* apKey) {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	const uint32_t uiBufferSize = strlen(apKey) + 1;
	char* pCopy = new char[uiBufferSize];
	strcpy_s(pCopy, uiBufferSize, apKey);
	return pCopy;
}

template<class T>
inline void LockFreeStringMap<T>::CopyKeyDirect(const char* apKey, const char*& arCopiedKey) {
	strcpy_s(const_cast<char*>(arCopiedKey), 256, apKey);
}

template<class T>
inline bool LockFreeStringMap<T>::IsKeyGreaterOrEqual(const char* apKey1, const char* apKey2) const {
	return strcmp(apKey1, apKey2) >= 0;
}

template<class T>
inline bool LockFreeStringMap<T>::IsKeyEqual(const char* apKey1, const char* apKey2) const {
	return strcmp(apKey1, apKey2) == 0;
}

#pragma endregion