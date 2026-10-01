#pragma once

#include <xmemory>

#include "BSMemory.hpp"
#include "BSScrapMemory.hpp"

template<typename T>
class BSMemoryAllocator : public std::allocator<T> {
public:
	using value_type = T;
	BSMemoryAllocator() = default;

	template<typename U>
	BSMemoryAllocator(const BSMemoryAllocator<U>&) {}

	[[nodiscard]] __declspec(allocator) inline T* allocate(std::size_t n) {
		return BSMemory::malloc<T>(n);
	}

	[[nodiscard]] constexpr std::allocation_result<T*> allocate_at_least(const std::size_t n) {
		return { allocate(n), n };
	}

	inline void deallocate(T* p, std::size_t) noexcept {
		BSMemory::free(p);
	}
};

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
	inline BSScrapBuffer(size_t count) {
		if (BSScrapMemory::hasSpace<T>(count)) [[likely]] {
			dataCount = count;
			data = BSScrapMemory::malloc<T>(count);
			if constexpr (!std::is_trivially_constructible_v<T>) {
				for (size_t i = 0; i < count; i++) {
					new (&data[i]) T();
				}
			}
		}
		else [[unlikely]] {
			dataCount = 0;
			data = nullptr;
			assert(false);
		}
	}
	inline ~BSScrapBuffer() {
		if constexpr (!std::is_trivially_destructible_v<T>) {
			for (size_t i = 0; i < dataCount; i++) {
				data[i].~T();
			}
		}
		BSScrapMemory::free(data);
	}

	inline T* get() {
		return data;
	}

	inline T& operator[](size_t index) {
		return data[index];
	}

private:
	T*		data;
	size_t	dataCount;
};