#pragma once

// All functions are thread-local
namespace BSScrapMemory {

	// For manual initialization;
	// By default, automatically called once by the first allocation
	extern bool initialize();

	// Returns true if caller thread's ScrapHeap can fit given amount
	[[nodiscard]] extern bool __fastcall hasSpace(size_t size);

	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* __cdecl malloc(size_t size);
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* __cdecl calloc(size_t num, size_t size);
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* __cdecl aligned_alloc(size_t alignment, size_t size);

	extern __declspec(noalias) void __cdecl free(void* ptr);
	extern __declspec(noalias) void __cdecl free_sized(void* ptr, size_t size);
	extern __declspec(noalias) void __cdecl	aligned_free(void* ptr);
	extern __declspec(noalias) void __cdecl free_aligned_sized(void* ptr, size_t alignment, size_t size);

	extern __declspec(noalias) size_t __cdecl msize(void* ptr);

	template <typename T>
	[[nodiscard]] inline bool __fastcall hasSpace(size_t count = 1) {
		return BSScrapMemory::hasSpace(sizeof(T) * count);
	};

	template <typename T>
	[[nodiscard]] inline __declspec(allocator) __declspec(restrict) T* __cdecl malloc(size_t count = 1) {
		return static_cast<T*>(BSScrapMemory::malloc(sizeof(T) * count));
	};

	template <typename T>
	[[nodiscard]] inline __declspec(allocator) __declspec(restrict) T* __cdecl calloc(size_t count = 1) {
		return static_cast<T*>(BSScrapMemory::calloc(count, sizeof(T)));
	};

	template <typename T>
	[[nodiscard]] inline __declspec(allocator) __declspec(restrict) T* __cdecl aligned_alloc() {
		return static_cast<T*>(BSScrapMemory::aligned_alloc(alignof(T), sizeof(T)));
	};

	template <typename T, const uint32_t ConstructorPtr = 0, typename... Args>
	[[nodiscard]] inline __declspec(restrict) T* create(Args &&... args) {
		T* ptr = BSScrapMemory::malloc<T>();
		if constexpr (ConstructorPtr) {
			ThisCall(ConstructorPtr, ptr, std::forward<Args>(args)...);
		}
		else {
			memset(ptr, 0, sizeof(T));
		}
		return ptr;
	}

	template <typename T, const uint32_t DestructorPtr = 0, typename... Args>
	inline void destroy(T* ptr, Args &&... args) {
		if constexpr (DestructorPtr) {
			ThisCall(DestructorPtr, ptr, std::forward<Args>(args)...);
		}
		BSScrapMemory::free(ptr);
	}

	template <typename T, const uint32_t ConstructorPtr = 0, typename... Args>
	[[nodiscard]] inline __declspec(restrict) T* create_aligned(Args &&... args) {
		T* ptr = BSScrapMemory::aligned_alloc<T>();
		if constexpr (ConstructorPtr) {
			ThisCall(ConstructorPtr, ptr, std::forward<Args>(args)...);
		}
		else {
			memset(ptr, 0, sizeof(T));
		}
		return ptr;
	}

	template <typename T, const uint32_t DestructorPtr = 0, typename... Args>
	inline void destroy_aligned(T* ptr, Args &&... args) {
		if constexpr (DestructorPtr) {
			ThisCall(DestructorPtr, ptr, std::forward<Args>(args)...);
		}
		BSScrapMemory::aligned_free(ptr);
	}
}