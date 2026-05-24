#pragma once

#include "NiMemObject.hpp"

#if !JIP_CHANGES
#include "NiTArray.hpp"
#include "NiCriticalSection.hpp"
#endif

class NiFixedString;

// Replaced by JIP and JG
class SPEC_EMPTY_BASES NiGlobalStringTable : public NiMemObject {
public:
	typedef char* GlobalStringHandle;

#if !JIP_CHANGES
	NiTPrimitiveArray<GlobalStringHandle>	m_kHashArray[512];
	NiCriticalSection						m_kCriticalSection;
#endif

#ifdef GAME
	static constexpr AddressPtr<uint32_t, 0x11F42C4> uiTotalStrings;
	static constexpr AddressPtr<uint32_t, 0x11F42C8> uiTotalCollisions;
#else
	static constexpr AddressPtr<uint32_t, 0xF20174> uiTotalStrings;
	static constexpr AddressPtr<uint32_t, 0xF20178> uiTotalCollisions;
#endif

	static GlobalStringHandle AddString(const char* apString) noexcept;
	static void RemoveUnusedStrings() noexcept;

	static void IncRefCount(GlobalStringHandle& arHandle) noexcept;
	static void DecRefCount(GlobalStringHandle& arHandle) noexcept;
	static uint32_t GetLength(const GlobalStringHandle& arHandle) noexcept;

	static char* GetRealBufferStart(const GlobalStringHandle& arHandle) noexcept;
};

#if !JIP_CHANGES
ASSERT_SIZE(NiGlobalStringTable, 0x2100);
#endif