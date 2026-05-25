#include "NiGlobalStringTable.hpp"

// GAME - 0xA5B690
// GECK - 0x81B0C0
NiGlobalStringTable::GlobalStringHandle NiGlobalStringTable::AddString(const char* apString) noexcept {
#ifdef GAME
    return CdeclCall<GlobalStringHandle>(0xA5B690, apString);
#else
	return CdeclCall<GlobalStringHandle>(0x81B0C0, apString);
#endif
}

// GAME - 0xA5B460
// GECK - 0x81AF10
void NiGlobalStringTable::RemoveUnusedStrings() noexcept {
#ifdef GAME
    CdeclCall(0xA5B460);
#else
    CdeclCall(0x81AF10);
#endif
}

// GAME - 0x43BA60
void NiGlobalStringTable::IncRefCount(GlobalStringHandle& arHandle) noexcept {
    if (!arHandle) [[unlikely]]
        return;

    InterlockedIncrement(reinterpret_cast<size_t*>(GetRealBufferStart(arHandle)));
}

// GAME - 0x4381D0
void NiGlobalStringTable::DecRefCount(GlobalStringHandle& arHandle) noexcept {
    if (!arHandle) [[unlikely]]
        return;

    InterlockedDecrement(reinterpret_cast<size_t*>(GetRealBufferStart(arHandle)));
}

uint32_t NiGlobalStringTable::GetLength(const GlobalStringHandle& arHandle) noexcept {
    if (!arHandle) [[unlikely]]
		return 0;

	size_t* pBuffer = reinterpret_cast<size_t*>(GetRealBufferStart(arHandle));
	return static_cast<uint32_t>(pBuffer[1]);
}

// GAME - 0x438210
char* NiGlobalStringTable::GetRealBufferStart(const GlobalStringHandle& arHandle) noexcept {
    return (static_cast<char*>(arHandle) - 2 * sizeof(size_t));
}
