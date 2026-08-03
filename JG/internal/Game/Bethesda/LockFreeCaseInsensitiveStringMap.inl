#pragma once

#include "LockFreeCaseInsensitiveStringMap.hpp"

#pragma region LockFreeCaseInsensitiveStringMap

template<class T>
inline LockFreeCaseInsensitiveStringMap<T>::LockFreeCaseInsensitiveStringMap(uint32_t auiMaxThreads, uint32_t auiBucketCount, uint32_t auiDeleteBatchSize) : LockFreeStringMap<T>(auiMaxThreads, auiBucketCount, auiDeleteBatchSize) {}

template<class T>
inline LockFreeCaseInsensitiveStringMap<T>::~LockFreeCaseInsensitiveStringMap() {
	this->RemoveAll(true);
}

template<class T>
inline bool LockFreeCaseInsensitiveStringMap<T>::GetAt(const char* apKey, T& arData) {
	char cBuffer[1000];
	char* pLowerCase = cBuffer;
	while (*apKey) {
		*pLowerCase++ = tolower(apKey);
		++apKey;
	}
	*pLowerCase = 0;
	return LockFreeMap<const char*, T>::GetAt(pLowerCase, arData);
}

template<class T>
inline bool LockFreeCaseInsensitiveStringMap<T>::SetAtAlt(const char* apKey, const T& arData, bool abReplaceExisting) {
	char cBuffer[1000];
	char* pLowerCase = cBuffer;
	while (*apKey) {
		*pLowerCase++ = tolower(apKey);
		++apKey;
	}
	*pLowerCase = 0;
	return LockFreeMap<const char*, T>::SetAtAlt(pLowerCase, arData, abReplaceExisting);
}

template<class T>
inline bool LockFreeCaseInsensitiveStringMap<T>::RemoveAt(const char* apKey) {
	char cBuffer[1000];
	char* pLowerCase = cBuffer;
	while (*apKey) {
		*pLowerCase++ = tolower(apKey);
		++apKey;
	}
	*pLowerCase = 0;
	return LockFreeMap<const char*, T>::RemoveAt(pLowerCase);
}

template<class T>
inline uint32_t LockFreeCaseInsensitiveStringMap<T>::GetBucketForKey(const char* apKey) {
	uint32_t uiHash = 0;
	while (*apKey) {
		uiHash = 33 * uiHash + tolower(*apKey++);
	}

	const uint32_t uiBucketCount = this->GetNumBuckets();
	return uiHash - (uiHash / uiBucketCount) * uiBucketCount;
}

template<class T>
inline const char* LockFreeCaseInsensitiveStringMap<T>::CopyKey(const char* apKey) {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	const uint32_t uiBufferSize = strlen(apKey) + 1;
	char* pCopy = new char[uiBufferSize];
	while (*apKey) {
		*pCopy++ = tolower(*apKey);
		++apKey;
	}
	*pCopy = 0;
	return pCopy;
}

#pragma endregion