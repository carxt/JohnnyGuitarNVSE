#pragma once

class ScrapHeap {
public:
	ScrapHeap() noexcept;
	ScrapHeap(uint32_t auiReserveSize) noexcept;
	~ScrapHeap() noexcept;

	struct Block {
		enum Flags : uint32_t {
			SIZE		= 0x7FFFFFFF,
			DEALLOCATED = 0x80000000,
		};

		Bitfield32	uiSizeAndFlags;
		Block*		pPrevious;

		bool		IsFree() const { return uiSizeAndFlags.Get(DEALLOCATED); }
		void		SetFree(bool abFree) { uiSizeAndFlags.Set(DEALLOCATED, abFree); }
		uint32_t	GetSize() const { return uiSizeAndFlags.Get(SIZE); }
	};

	struct FreeBlock : Block {
		FreeBlock* pLeft;
		FreeBlock* pRight;
	};

	char*	pMemHeap;
	char*	pCurrentStackLoc;
	char*	pEndHeap;
	Block*	pLastBlock;

	template <typename T>
	[[nodiscard]] __declspec(restrict) __declspec(allocator) T* AllocateT(uint32_t auiCount = 1, uint32_t auiAlignment = alignof(T)) noexcept {
		return static_cast<T*>(Allocate(auiCount * sizeof(T), auiAlignment));
	}
	[[nodiscard]] __declspec(restrict) __declspec(allocator) void*	Allocate(uint32_t auiSize, uint32_t auiAlignment = 4) noexcept;

	void		Deallocate(void* apMem) noexcept;

	bool		IsOwner(const void* apMem) const noexcept;

	uint32_t	GetAllocatedMemory() const noexcept;

	uint32_t	Size(const void* apMem) const noexcept;

	uint32_t	GetAllocationCount() const noexcept;

	bool		HasSpaceAvailable(uint32_t auiSize) const noexcept;

	static uint32_t GetMinMemory() noexcept;
	static uint32_t GetMaxMemory() noexcept;

private:
	// Not actual globals, reading values inlined into functions
	// This is to support modded overrides if needed
#ifdef GAME
	static constexpr AddressPtr<uint32_t, 0xAA56D2> uiMinMemory;
	static constexpr AddressPtr<uint32_t, 0xAA5ED1> uiMaxMemory;
#else
	static constexpr AddressPtr<uint32_t, 0x855BF2> uiMinMemory;
	static constexpr AddressPtr<uint32_t, 0x8563F1> uiMaxMemory;
#endif
};

[[nodiscard]] __declspec(restrict) __declspec(allocator) inline void* operator new(std::size_t auiCount, ScrapHeap& arHeap) {
	return arHeap.Allocate(auiCount);
}

inline void operator delete(void* apMemory, ScrapHeap& arHeap) {
	arHeap.Deallocate(apMemory);
}

ASSERT_SIZE(ScrapHeap, 0x10);
ASSERT_SIZE(ScrapHeap::Block, 0x8);