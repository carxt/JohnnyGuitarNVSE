#pragma once

namespace BSScrapMemory {
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* malloc(std::size_t size);
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* calloc(std::size_t size);
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* aligned_alloc(size_t alignment, std::size_t size);

	extern __declspec(noalias) void	aligned_free(void* ptr);

	extern __declspec(noalias) void free(void* ptr);

	extern __declspec(noalias) std::size_t msize(void* ptr);

	template <typename T>
	[[nodiscard]] inline __declspec(restrict) __declspec(allocator) T* malloc() {
		return static_cast<T*>(BSScrapMemory::malloc(sizeof(T)));
	};

	template <typename T>
	[[nodiscard]] inline __declspec(restrict) __declspec(allocator) T* malloc(std::size_t count) {
		return static_cast<T*>(BSScrapMemory::malloc(sizeof(T) * count));
	};

	template <typename T, const uint32_t ConstructorPtr = 0, typename... Args>
	[[nodiscard]] inline __declspec(restrict) T* create(Args &&... args) {
		auto* ptr = BSScrapMemory::malloc<T>();
		if constexpr (ConstructorPtr) {
			ThisCall(ConstructorPtr, ptr, std::forward<Args>(args)...);
		}
		else {
			memset(ptr, 0, sizeof(T));
		}
		return static_cast<T*>(ptr);
	}

	template <typename T, const uint32_t DestructorPtr = 0, typename... Args>
	inline void destroy(T* ptr, Args &&... args) {
		if constexpr (DestructorPtr) {
			ThisCall(DestructorPtr, ptr, std::forward<Args>(args)...);
		}
		BSScrapMemory::free(ptr);
	}
}