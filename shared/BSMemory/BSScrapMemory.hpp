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

template<typename T>
class BSScrapAllocator : public std::allocator<T> {
public:
	using value_type = T;
	BSScrapAllocator() = default;

	template<typename U>
	BSScrapAllocator(const BSScrapAllocator<U>&) {}
	
	[[nodiscard]] __declspec(allocator) inline T* allocate(std::size_t n) {
		return BSScrapMemory::malloc<T>(n);
	}

	[[nodiscard]] constexpr std::allocation_result<T*> allocate_at_least(const std::size_t n) {
		return { allocate(n), n };
	}

	inline void deallocate(T* p, std::size_t) noexcept {
		BSScrapMemory::free(p);
	}
};

template<typename T>
class BSScrapBuffer {
public:
	inline BSScrapBuffer(std::size_t size) : size(size) {
		data = BSScrapMemory::malloc<T>(size);
		if constexpr (!std::is_trivially_constructible_v<T>) {
			for (std::size_t i = 0; i < size; i++) {
				new (&data[i]) T();
			}
		}
	}
	inline ~BSScrapBuffer() {
		if constexpr (!std::is_trivially_destructible_v<T>) {
			for (std::size_t i = 0; i < size; i++) {
				data[i].~T();
			}
		}
		BSScrapMemory::free(data);
	}

	inline T* get() {
		return data;
	}

	inline T& operator[](std::size_t index) {
		return data[index];
	}

private:
	T*			data;
	std::size_t size;
};