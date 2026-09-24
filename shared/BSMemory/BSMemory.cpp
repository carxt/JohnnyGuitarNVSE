#include "BSMemory.hpp"
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOSERVICE
#define NOMCX
#define NOIME
#include "Windows.h"
#endif

#pragma warning(push)
#pragma warning(disable : 4302)
#pragma optimize("y", on)

namespace BSMemory { 

	// -------------------------------------------------------------------------
	// Internal globals and functions
	// -------------------------------------------------------------------------
	static INIT_ONCE		kInitOnce = INIT_ONCE_STATIC_INIT;
	static void*			pMemoryManager = nullptr;
	static void* __fastcall	InitAllocator(void* apThis, void*, size_t size);

	namespace CurrentMemManager {
		static void*	(__thiscall* Allocate)(void* apThis, size_t size) = reinterpret_cast<decltype(Allocate)>(InitAllocator);
		static void*	(__thiscall* ReAllocate)(void* apThis, void* ptr, size_t new_size) = nullptr;
		static void		(__thiscall* Deallocate)(void* apThis, void* ptr) = nullptr;
		static size_t	(__thiscall* Size)(void* apThis, void* ptr) = nullptr;

		static inline uint32_t GetMaxAllocSize() { return 0xFFFFFFF; }
	}

	// -------------------------------------------------------------------------
	// Functions made to be used by the user
	// They are also used to replace new and delete operators
	// -------------------------------------------------------------------------
	__declspec(allocator) __declspec(restrict) void* __cdecl malloc(size_t size) {
		assert(size <= CurrentMemManager::GetMaxAllocSize());

		return CurrentMemManager::Allocate(pMemoryManager, size);
	}

	__declspec(allocator) __declspec(restrict) void* __cdecl calloc(size_t num, size_t size) {
		const size_t stSize = num * size;
		void* pMemory = malloc(stSize);
		assert(pMemory);

		if (pMemory)
			memset(pMemory, 0, stSize);

		return pMemory;
	}

	__declspec(allocator) __declspec(restrict) void* __cdecl aligned_alloc(size_t alignment, size_t size) {
		assert(alignment > 0 && alignment <= UINT8_MAX);

		uint8_t* pMemory = static_cast<uint8_t*>(malloc(size + alignment));
		const uint8_t ucAlignment = reinterpret_cast<uint8_t&>(alignment);
		const uint8_t ucFinalAlignment = ucAlignment - (reinterpret_cast<uint8_t>(pMemory) & (ucAlignment - 1));
		pMemory[ucFinalAlignment - 1] = ucFinalAlignment;
		return &pMemory[ucFinalAlignment];
	}

	__declspec(allocator) __declspec(restrict) void* __cdecl realloc(void* ptr, size_t new_size) {
		assert(pMemoryManager);
		assert(new_size <= CurrentMemManager::GetMaxAllocSize());

		return CurrentMemManager::ReAllocate(pMemoryManager, ptr, new_size);
	}

	__declspec(noalias) void __cdecl free(void* ptr) {
		assert(pMemoryManager);
		assert(ptr);

		if (!ptr)
			return;

		CurrentMemManager::Deallocate(pMemoryManager, ptr);
	}

	__declspec(noalias) void __cdecl free_sized(void* ptr, size_t size) {
		free(ptr);
	}

	__declspec(noalias) void __cdecl aligned_free(void* ptr) {
		assert(pMemoryManager);
		assert(ptr);

		if (!ptr)
			return;

		uint8_t* pMemory = static_cast<uint8_t*>(ptr);
		pMemory = pMemory - pMemory[-1];
		free(pMemory);
	}

	void __cdecl free_aligned_sized(void* ptr, size_t alignment, size_t size) {
		return aligned_free(ptr);
	}

	__declspec(noalias) size_t __cdecl msize(void* ptr) {
		assert(pMemoryManager);

		return CurrentMemManager::Size(pMemoryManager, ptr);
	}

	// -------------------------------------------------------------------------
	// Functions made to initialize the allocator
	// Compatible with both game and GECK
	// -------------------------------------------------------------------------

	// This function is used to create process's heap if it doesn't exist
	// It's possible to load the plugin before program is even initialized (Game's NVSEPlugin_Preload and GECK's NVSEPlugin_Query/Load run before CRT initialization)
	// In those cases, malloc fails due to lack of heap - that's why we need to create it manually
	static __declspec(noinline) void __fastcall CreateHeapIfNotExisting(uint32_t auiCreateHeapAddress, uint32_t auiHeapAddress, uint32_t auiCallAddress, uint32_t auiJumpAddress) {
		if (*reinterpret_cast<HANDLE*>(auiHeapAddress))
			return;
		
		auto CreateHeap = reinterpret_cast<HANDLE(__cdecl*)(uint32_t)>(auiCreateHeapAddress);
		CreateHeap(true);

		auto PatchMemoryNop = [](uint32_t address, size_t size) {
			DWORD oldProtect;
			VirtualProtect(LPVOID(address), size, PAGE_EXECUTE_READWRITE, &oldProtect);
			for (size_t i = 0; i < size; i++)
				*reinterpret_cast<volatile BYTE*>(address + i) = 0x90;
			VirtualProtect(LPVOID(address), size, oldProtect, &oldProtect);

			FlushInstructionCache(GetCurrentProcess(), LPVOID(address), size);
		};

		auto SafeWrite8 = [](size_t address, uint8_t data) {
			DWORD oldProtect;
			VirtualProtect(LPVOID(address), 4, PAGE_EXECUTE_READWRITE, &oldProtect);
			*reinterpret_cast<uint8_t*>(address) = data;
			VirtualProtect(LPVOID(address), 4, oldProtect, &oldProtect);
		};

		PatchMemoryNop(auiCallAddress, 5);
		SafeWrite8(auiJumpAddress, 0xEB);
	}

	// This function sets up correct addresses based on the program
	static BOOL WINAPI BSAllocatorInitializer(PINIT_ONCE InitOnce, PVOID Parameter, PVOID* Context) {
		constexpr uint32_t uiMatchPattern = 0x56413F2E;
		if (*reinterpret_cast<uint32_t*>(0xEB6610) == uiMatchPattern) {
			// GECK
			pMemoryManager					= reinterpret_cast<void*>(0xF21B5C);
			CurrentMemManager::Allocate		= reinterpret_cast<decltype(CurrentMemManager::Allocate)>(0x8540A0);
			CurrentMemManager::ReAllocate	= reinterpret_cast<decltype(CurrentMemManager::ReAllocate)>(0x8543B0);
			CurrentMemManager::Deallocate	= reinterpret_cast<decltype(CurrentMemManager::Deallocate)>(0x8542C0);
			CurrentMemManager::Size			= reinterpret_cast<decltype(CurrentMemManager::Size)>(0x854720);
			CreateHeapIfNotExisting(0xC770C3, 0xF9907C, 0xC62B21, 0xC62B29);
		}
		else {
			// Game
			pMemoryManager					= reinterpret_cast<void*>(0x11F6238);
			CurrentMemManager::Allocate		= reinterpret_cast<decltype(CurrentMemManager::Allocate)>(0xAA3E40);
			CurrentMemManager::ReAllocate	= reinterpret_cast<decltype(CurrentMemManager::ReAllocate)>(0xAA4150);
			CurrentMemManager::Deallocate	= reinterpret_cast<decltype(CurrentMemManager::Deallocate)>(0xAA4060);
			CurrentMemManager::Size			= reinterpret_cast<decltype(CurrentMemManager::Size)>(0xAA44C0);
			CreateHeapIfNotExisting(0xEDDB6A, 0x12705BC, 0xECC3CB, 0xECC3D3);
		}

		return TRUE;
	}

	__declspec(noinline) bool initialize() {
		return InitOnceExecuteOnce(&kInitOnce, BSAllocatorInitializer, nullptr, nullptr);
	}

	static void* __fastcall InitAllocator(void* apThis, void*, size_t size) {
		initialize();
		return CurrentMemManager::Allocate(pMemoryManager, size);
	}
}

#pragma optimize("", on)
#pragma warning(pop)