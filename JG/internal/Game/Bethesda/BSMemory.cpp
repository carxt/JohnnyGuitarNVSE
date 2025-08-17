#include "BSMemory.hpp"
#include <mutex>

// -------------------------------------------------------------------------
// Internal globals and functions
// -------------------------------------------------------------------------
std::mutex			kAllocInitLock;
void*				pMemoryManager = nullptr;
bool				bInitialized = false;
void* __fastcall	InitAllocator(void* pThis, void*, size_t stSize);
void*				BSAllocatorInitializer();
int(__cdecl*		CreateHeap)(uint32_t aeSerialize);

namespace CurrentMemManager {
	void* (__thiscall*	Allocate)(void* pThis, size_t stSize) = (void* (__thiscall *)(void*,size_t))InitAllocator;
	void* (__thiscall*	ReAllocate)(void* pThis, void* pvMem, size_t stSize) = nullptr;
	void(__thiscall*	Deallocate)(void* pThis, void* pvMem) = nullptr;
	size_t(__thiscall*	Size)(void* pThis, void* pvMem) = nullptr;
}

// -------------------------------------------------------------------------
// Functions made to be used by the user
// These functions use game's memory manager to manage memory
// They are used to replace new and delete operators
// -------------------------------------------------------------------------
void* BSNew(size_t stSize) {
	return CurrentMemManager::Allocate(pMemoryManager, stSize);
}

void* BSNewAligned(size_t stAlign, size_t stSize) {
	uint8_t* pMemory = static_cast<uint8_t*>(BSNew(stSize + stAlign));
	uint32_t uiAlignment = stAlign - (reinterpret_cast<uint8_t>(pMemory) & (stAlign - 1));
	pMemory[uint8_t(uiAlignment) - 1] = uiAlignment;
	return &pMemory[uint8_t(uiAlignment)];
}

void* BSReallocate(void* pvMem, size_t stSize) {
	return CurrentMemManager::ReAllocate(pMemoryManager, pvMem, stSize);
}

void BSFree(void* pvMem) {
	CurrentMemManager::Deallocate(pMemoryManager, pvMem);
}

size_t BSSize(void* pvMem) {
	return CurrentMemManager::Size(pMemoryManager, pvMem);
}

// -------------------------------------------------------------------------
// Functions made to initialize the allocator
// Compatible with both game and GECK
// -------------------------------------------------------------------------

// This function is used to create game's heap if it doesn't exist
// It's possible to load the plugin before game is even initialized
// In those cases, malloc fails due to lack of heap - that's why we need to create it manually
_declspec(noinline) void CreateHeapIfNotExisting(uint32_t auiHeapAddress, uint32_t auiCallAddress, uint32_t auiJumpAddress) {
	if (*(HANDLE*)auiHeapAddress)
		return;

	CreateHeap(true);

	auto PatchMemoryNop = [](uint32_t address, size_t size) {
		DWORD d = 0;
		VirtualProtect((LPVOID)address, size, PAGE_EXECUTE_READWRITE, &d);

		for (SIZE_T i = 0; i < size; i++)
			*(volatile BYTE*)(address + i) = 0x90;

		VirtualProtect((LPVOID)address, size, d, &d);

		FlushInstructionCache(GetCurrentProcess(), (LPVOID)address, size);
	};

	auto SafeWrite8 = [](SIZE_T addr, SIZE_T data) {
		SIZE_T	oldProtect;

		VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
		*((uint8_t*)addr) = data;
		VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
	};

	PatchMemoryNop(auiCallAddress, 5);
	SafeWrite8(auiJumpAddress, 0xEB);
}

void* __fastcall InitAllocator(void* pThis, void*, size_t stSize) {
	void* pAllocator = BSAllocatorInitializer();
	if (pAllocator)
		return CurrentMemManager::Allocate(pAllocator, stSize);
	return nullptr;
}

// This function sets up correct addresses based on the program
_declspec(noinline) void* BSAllocatorInitializer() {
	std::lock_guard<std::mutex> kLock(kAllocInitLock);
	if (bInitialized)
		return pMemoryManager;

	if (*reinterpret_cast<uint8_t*>(0x401190) != 0x55) {
		// Is GECK
		pMemoryManager					= reinterpret_cast<void*>(0xF21B5C);
		CurrentMemManager::Allocate		= (void* (__thiscall*)(void*, size_t))0x8540A0;
		CurrentMemManager::ReAllocate	= (void* (__thiscall*)(void*, void*, size_t))0x8543B0;
		CurrentMemManager::Deallocate	= (void(__thiscall*)(void*, void*))0x8542C0;
		CurrentMemManager::Size			= (size_t(__thiscall*)(void*, void*))0x854720;
		CreateHeap						= (int(__cdecl*)(uint32_t))0xC770C3;

		CreateHeapIfNotExisting(0xF9907C, 0xC62B21, 0xC62B29);
	}
	else {
		pMemoryManager					= reinterpret_cast<void*>(0x11F6238);
		CurrentMemManager::Allocate		= (void* (__thiscall*)(void*, size_t))0xAA3E40;
		CurrentMemManager::ReAllocate	= (void* (__thiscall*)(void*, void*, size_t))0xAA4150;
		CurrentMemManager::Deallocate	= (void(__thiscall*)(void*, void*))0xAA4060;
		CurrentMemManager::Size			= (size_t(__thiscall*)(void*, void*))0xAA44C0;
		CreateHeap						= (int(__cdecl*)(uint32_t))0xEDDB6A;

		CreateHeapIfNotExisting(0x12705BC, 0xECC3CB, 0xECC3D3);
	}

	bInitialized = true;
	return pMemoryManager;
}