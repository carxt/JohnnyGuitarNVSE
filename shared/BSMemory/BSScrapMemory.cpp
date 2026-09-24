#include "BSScrapMemory.hpp"
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOSERVICE
#define NOMCX
#define NOIME
#include "Windows.h"
#endif

#pragma optimize("y", on)

namespace BSScrapMemory {

	// -------------------------------------------------------------------------
	// Internal globals and functions
	// -------------------------------------------------------------------------
	static INIT_ONCE		kInitOnce = INIT_ONCE_STATIC_INIT;
	static void*			pMemoryManager = nullptr;
	static void* __fastcall	InitAllocator(void* apThis);

	struct alignas(4) ScrapHeap {
		const char* pBufferStart;
		const char* pStackPos;
		const char* pBufferEnd;
		void*		pLastBlock;
	};

	namespace CurrentMemoryManager {
		static ScrapHeap*	(__thiscall* GetThreadScrapHeap)(void* apThis) = reinterpret_cast<decltype(GetThreadScrapHeap)>(InitAllocator);
	}

	namespace CurrentScrapHeap {
		// While default value is 8MiB, it is completely arbitrary, and replaceable by mods
		static uint32_t* pMaxMemory = nullptr;

		static void*		(__thiscall* Allocate)(ScrapHeap* apThis, size_t size, size_t alignment) = nullptr;
		static void			(__thiscall* Deallocate)(ScrapHeap* apThis, void* ptr) = nullptr;
		static size_t		(__thiscall* Size)(ScrapHeap* apThis, void* ptr) = nullptr;

		static inline uint32_t GetMaxMemory() { 
			assert(pMaxMemory);
			return *pMaxMemory; 
		}

		static inline uint32_t __fastcall GetAllocatedMemory(ScrapHeap* apScrapHeap) {
			return apScrapHeap->pStackPos - apScrapHeap->pBufferStart;
		}

		static inline bool __fastcall HasSpace(ScrapHeap* apScrapHeap, size_t size) {
			return (size + CurrentScrapHeap::GetAllocatedMemory(apScrapHeap)) < CurrentScrapHeap::GetMaxMemory();
		}
	}

	// -------------------------------------------------------------------------
	// Functions made to be used by the user
	// They are also used to replace new and delete operators
	// -------------------------------------------------------------------------
	__declspec(allocator) __declspec(restrict) void* malloc(size_t size) {
		ScrapHeap* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		assert(pHeap);
		assert(size < CurrentScrapHeap::GetMaxMemory());
		assert(CurrentScrapHeap::HasSpace(pHeap, size));
		return CurrentScrapHeap::Allocate(pHeap, size, 4);
	}

	__declspec(allocator) __declspec(restrict) void* calloc(size_t num, size_t size) {
		const size_t stSize = num * size;
		void* pMemory = malloc(stSize);
		assert(pMemory);

		if (pMemory)
			memset(pMemory, 0, stSize);

		return pMemory;
	}

	__declspec(allocator) __declspec(restrict) void* aligned_alloc(size_t alignment, size_t size) {
		assert(pMemoryManager);
		assert(size < CurrentScrapHeap::GetMaxMemory());

		ScrapHeap* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		assert(pHeap);
		assert(CurrentScrapHeap::HasSpace(pHeap, size));
		return CurrentScrapHeap::Allocate(pHeap, size, alignment);
	}

	__declspec(noalias) void free(void* ptr) {
		assert(pMemoryManager);
		assert(ptr);

		if (!ptr)
			return;

		ScrapHeap* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		assert(pHeap);

		CurrentScrapHeap::Deallocate(pHeap, ptr);
	}

	__declspec(noalias) void __cdecl free_sized(void* ptr, size_t size) {
		free(ptr);
	}

	__declspec(noalias) void aligned_free(void* ptr) {
		free(ptr);
	}

	void __cdecl free_aligned_sized(void* ptr, size_t alignment, size_t size) {
		return aligned_free(ptr);
	}

	__declspec(noalias) size_t msize(void* ptr) {
		assert(pMemoryManager);

		ScrapHeap* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		assert(pHeap);

		return CurrentScrapHeap::Size(pHeap, ptr);
	}

	// -------------------------------------------------------------------------
	// Functions made to initialize the allocator
	// Compatible with both game and GECK
	// -------------------------------------------------------------------------

	// This function sets up correct addresses based on the program
	static BOOL WINAPI BSScrapAllocatorInitializer(PINIT_ONCE InitOnce, PVOID Parameter, PVOID* Context) {
		constexpr uint32_t uiMatchPattern = 0x56413F2E;
		if (*reinterpret_cast<uint32_t*>(0xEB6610) == uiMatchPattern) {
			// GECK
			pMemoryManager								= reinterpret_cast<void*>(0xF21B5C);
			CurrentScrapHeap::Allocate					= reinterpret_cast<decltype(CurrentScrapHeap::Allocate)>(0x8559C0);
			CurrentScrapHeap::Deallocate				= reinterpret_cast<decltype(CurrentScrapHeap::Deallocate)>(0x855B30);
			CurrentScrapHeap::Size						= reinterpret_cast<decltype(CurrentScrapHeap::Size)>(0x855C30);
			CurrentScrapHeap::pMaxMemory				= reinterpret_cast<uint32_t*>(0x8563F1);
			CurrentMemoryManager::GetThreadScrapHeap	= reinterpret_cast<decltype(CurrentMemoryManager::GetThreadScrapHeap)>(0x854540);
		}
		else {
			// Game
			pMemoryManager								= reinterpret_cast<void*>(0x11F6238);
			CurrentScrapHeap::Allocate					= reinterpret_cast<decltype(CurrentScrapHeap::Allocate)>(0xAA54A0);
			CurrentScrapHeap::Deallocate				= reinterpret_cast<decltype(CurrentScrapHeap::Deallocate)>(0xAA5610);
			CurrentScrapHeap::Size						= reinterpret_cast<decltype(CurrentScrapHeap::Size)>(0xAA5710);
			CurrentScrapHeap::pMaxMemory				= reinterpret_cast<uint32_t*>(0xAA5ED1);
			CurrentMemoryManager::GetThreadScrapHeap	= reinterpret_cast<decltype(CurrentMemoryManager::GetThreadScrapHeap)>(0xAA42E0);
		}

		if (!static_cast<char*>(pMemoryManager)[0]) {
#ifdef NDEBUG
			DebugBreak();
#else
			assert(false && "Tried to use thread-local ScrapHeap before MemoryManager's initialization!");
#endif
			return FALSE;
		}

		return TRUE;
	}

	__declspec(noinline) bool initialize() {
		return InitOnceExecuteOnce(&kInitOnce, BSScrapAllocatorInitializer, nullptr, nullptr);
	}

	bool __fastcall hasSpace(size_t size) {
		ScrapHeap* pHeap = CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
		assert(pHeap);

		return CurrentScrapHeap::HasSpace(pHeap, size);
	}

	static void* __fastcall InitAllocator(void* apThis) {
		initialize();
		return CurrentMemoryManager::GetThreadScrapHeap(pMemoryManager);
	}

}

#pragma optimize("", on)