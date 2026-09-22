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