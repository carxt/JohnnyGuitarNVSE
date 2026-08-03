#pragma once

#include "ThreadSpecificInterfaceManager.hpp"
#include "AutoMemContext.hpp"

// GAME - 0xC42180
template<typename T>
inline ThreadSpecificInterfaceManager<T>::ThreadSpecificInterfaceManager(uint32_t auiMaxThreads) {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);

	uiThreadCount = 0;
	uiMaxThreads = auiMaxThreads;

	pInterfaces = new ThreadSpecificInterface[auiMaxThreads];

	uiTLSIndex = TlsAlloc();
}

// GAME - 0x6665C0
template<typename T>
inline ThreadSpecificInterfaceManager<T>::~ThreadSpecificInterfaceManager() {
	for (uint32_t i = 0; i < uiMaxThreads; i++) {
		if (pInterfaces[i].pInterface)
			delete pInterfaces[i].pInterface;
	}

	delete[] pInterfaces;

	TlsFree(uiTLSIndex);
}

template<typename T>
inline uint32_t ThreadSpecificInterfaceManager<T>::GetMaxThreads() const {
	return uiMaxThreads;
}

// GAME - 0xC41610
template<typename T>
inline T* ThreadSpecificInterfaceManager<T>::AddInterface(InterfacedClass* apClass) {
	T* pInterface = nullptr;
	uint32_t uiThread = InterlockedIncrement(&uiThreadCount) - 1;
	if (uiThread >= uiMaxThreads) {
#ifdef _DEBUG
		_MESSAGE("Could not add new interface for thread %08X in ThreadSpecificInterfaceManager::AddInterface.  Max threads is: %i\n", GetCurrentThreadId(), uiMaxThreads);
#endif
		return pInterface;
	}

	pInterface = static_cast<T*>(apClass->AllocateInterface(uiThread));
	pInterfaces[uiThread].pInterface = pInterface;
	pInterfaces[uiThread].uiThreadID = GetCurrentThreadId();
	TlsSetValue(uiTLSIndex, pInterface);
	return pInterface;
}

// GAME - 0x44D5C0
template<typename T>
inline T* ThreadSpecificInterfaceManager<T>::GetInterface(InterfacedClass* apClass) {
	T* pInterface = static_cast<T*>(TlsGetValue(uiTLSIndex));
	if (pInterface)
		return pInterface;

	return AddInterface(apClass);
};