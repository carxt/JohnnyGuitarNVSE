#include "BSScrapMemory.hpp"
#include <shared_mutex>

namespace BSScrapMemory {

	// -------------------------------------------------------------------------
	// Internal globals and functions
	// -------------------------------------------------------------------------
	std::shared_mutex	kAllocInitLock;
	void*				pMemoryManager = nullptr;
	bool				bInitialized = false;
	void* __fastcall	InitAllocator(void* apThis);
	void*				BSScrapAllocatorInitializer();

	namespace CurrentMemoryManager {
		void*	(__thiscall* GetThreadScrapHeap)(void* apThis) = (void* (__thiscall*)(void*))InitAllocator;
	}

	namespace CurrentScrapHeap {
		void*	(__thiscall* Allocate)(void* apThis, std::size_t size, std::size_t alignment) = nullptr;
		void	(__thiscall* Deallocate)(void* apThis, void* ptr) = nullptr;
	}

	// -------------------------------------------------------------------------
	// Functions made to be used by the user
	// These functions use game's memory manager to manage memory
	// They are used to replace new and delete operators
	// -------------------------------------------------------------------------
	__declspec(allocator) __declspec(restrict) void* malloc(std::size_t size) {
		void* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		return CurrentScrapHeap::Allocate(pHeap, size, 4);
	}

	__declspec(allocator) __declspec(restrict) void* calloc(std::size_t size) {
		void* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		void* pMemory = CurrentScrapHeap::Allocate(pHeap, size, 4);
		if (pMemory)
			memset(pMemory, 0, size);
		return pMemory;
	}

	__declspec(allocator) __declspec(restrict) void* aligned_alloc(std::size_t alignment, std::size_t size) {
		void* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		return CurrentScrapHeap::Allocate(pHeap, size, alignment);
	}

	__declspec(noalias) void aligned_free(void* ptr) {
		free(ptr);
	}

	__declspec(noalias) void free(void* ptr) {
		void* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		CurrentScrapHeap::Deallocate(pHeap, ptr);
	}

	__declspec(noalias) std::size_t msize(void* ptr) {
		return *(static_cast<std::uint32_t*>(ptr) - 2) & 0x7FFFFFFF;
	}

	// -------------------------------------------------------------------------
	// Functions made to initialize the allocator
	// Compatible with both game and GECK
	// -------------------------------------------------------------------------

	void* __fastcall InitAllocator(void* apThis) {
		void* pAllocator = BSScrapAllocatorInitializer();
		if (!pAllocator)
			return nullptr;
		return CurrentMemoryManager::GetThreadScrapHeap(pAllocator);
	}

	// This function sets up correct addresses based on the program
	__declspec(noinline) void* BSScrapAllocatorInitializer() {
		std::lock_guard kLock(kAllocInitLock);
		if (bInitialized)
			return pMemoryManager;

		if (*reinterpret_cast<uint8_t*>(0x401190) != 0x55) {
			// Is GECK
			pMemoryManager = reinterpret_cast<void*>(0xF21B5C);
			CurrentScrapHeap::Allocate = (void* (__thiscall*)(void*, size_t, size_t))0x8559C0;
			CurrentScrapHeap::Deallocate = (void(__thiscall*)(void*, void*))0x855B30;
			CurrentMemoryManager::GetThreadScrapHeap = (void* (__thiscall*)(void*))0x854540;
		}
		else {
			pMemoryManager = reinterpret_cast<void*>(0x11F6238);
			CurrentScrapHeap::Allocate = (void* (__thiscall*)(void*, size_t, size_t))0xAA54A0;
			CurrentScrapHeap::Deallocate = (void(__thiscall*)(void*, void*))0xAA5610;
			CurrentMemoryManager::GetThreadScrapHeap = (void* (__thiscall*)(void*))0xAA42E0;
		}

		bInitialized = true;

		if (!static_cast<char*>(pMemoryManager)[0]) {
#ifdef _DEBUG
			MessageBoxA(NULL, "Tried to use thread-specific ScrapHeap before MemoryManager's initialization!", "Error", MB_OK | MB_ICONERROR);
#endif
			DebugBreak();
		}

		return pMemoryManager;
	}

}