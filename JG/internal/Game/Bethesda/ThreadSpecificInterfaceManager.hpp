#pragma once

#include "BSMemObject.hpp"
#include "InterfacedClass.hpp"

template <typename T>
class ThreadSpecificInterfaceManager {
public:
	struct ThreadSpecificInterface {
		uint32_t	uiThreadID	= 0;
		T*			pInterface	= nullptr;
	};

	ThreadSpecificInterfaceManager(uint32_t auiMaxThreads);
	~ThreadSpecificInterfaceManager();

	uint32_t					uiMaxThreads;
	uint32_t					uiTLSIndex;
	ThreadSpecificInterface*	pInterfaces;
	uint32_t					uiThreadCount;

	uint32_t GetMaxThreads() const;

	T* AddInterface(InterfacedClass* apClass);

	T* GetInterface(InterfacedClass* apClass);
};

#include "ThreadSpecificInterfaceManager.inl"

ASSERT_SIZE(ThreadSpecificInterfaceManager<void>, 0x10)
ASSERT_SIZE(ThreadSpecificInterfaceManager<void>::ThreadSpecificInterface, 0x8)