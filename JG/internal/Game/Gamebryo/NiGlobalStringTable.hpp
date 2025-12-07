#pragma once

#include "NiMemObject.hpp"

#if !JIP_CHANGES
#include "NiTArray.hpp"
#include "NiCriticalSection.hpp"
#endif

class NiFixedString;

// Replaced by JIP
class NiGlobalStringTable : public NiMemObject {
public:
	typedef char* GlobalStringHandle;

#if !JIP_CHANGES
	NiTPrimitiveArray<GlobalStringHandle>	m_kHashArray[512];
	NiCriticalSection						m_kCriticalSection;
#endif

	static GlobalStringHandle AddString(const char* pcString);
	static void IncRefCount(GlobalStringHandle& arHandle);
	static void DecRefCount(GlobalStringHandle& arHandle);
	static uint32_t GetLength(const GlobalStringHandle& arHandle);

	static char* GetRealBufferStart(const GlobalStringHandle& arHandle);
};

#if !JIP_CHANGES
ASSERT_SIZE(NiGlobalStringTable, 0x2100);
#endif