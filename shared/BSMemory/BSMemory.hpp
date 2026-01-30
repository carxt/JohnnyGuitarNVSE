#pragma once

namespace BSMemory {
	extern [[nodiscard]] __declspec(allocator) __declspec(restrict) void* malloc(std::size_t size);
	extern [[nodiscard]] __declspec(allocator) __declspec(restrict) void* calloc(std::size_t size);
	extern [[nodiscard]] __declspec(allocator) __declspec(restrict) void* aligned_alloc(size_t alignment, std::size_t size);
	extern [[nodiscard]] __declspec(allocator) __declspec(restrict) void* realloc(void* ptr, std::size_t new_size);

	extern __declspec(noalias) void	aligned_free(void* ptr);

	extern __declspec(noalias) void free(void* ptr);

	extern __declspec(noalias) std::size_t msize(void* ptr);

	template <typename T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* malloc() {
		return static_cast<T*>(BSMemory::malloc(sizeof(T)));
	};

	template <typename T>
	[[nodiscard]] __declspec(allocator) __declspec(restrict) T* malloc(std::size_t count) {
		return static_cast<T*>(BSMemory::malloc(sizeof(T) * count));
	};

	template <typename T, const uint32_t ConstructorPtr = 0, typename... Args>
	[[nodiscard]] __declspec(restrict) T* create(Args &&... args) {
		auto* ptr = BSMemory::malloc<T>();
		if constexpr (ConstructorPtr) {
			ThisCall(ConstructorPtr, ptr, std::forward<Args>(args)...);
		}
		else {
			memset(ptr, 0, sizeof(T));
		}
		return static_cast<T*>(ptr);
	}

	template <typename T, const uint32_t DestructorPtr = 0, typename... Args>
	void destroy(T* ptr, Args &&... args) {
		if constexpr (DestructorPtr) {
			ThisCall(DestructorPtr, ptr, std::forward<Args>(args)...);
		}
		BSMemory::free(ptr);
	}
}

template<typename T>
class BSMemoryAllocator : public std::allocator<T> {
public:
	using value_type = T;
	BSMemoryAllocator() = default;
	template<typename U>
	BSMemoryAllocator(const BSMemoryAllocator<U>&) {}
	[[nodiscard]] T* allocate(std::size_t n) {
		return BSMemory::malloc<T>(n);
	}
	void deallocate(T* p, std::size_t) noexcept {
		BSMemory::free(p);
	}
};

#define BS_ALLOCATORS \
_VCRT_EXPORT_STD _NODISCARD _Ret_notnull_ _Post_writable_byte_size_(_Size) _VCRT_ALLOCATOR \
void* __CRTDECL operator new(size_t _Size) { return BSMemory::malloc(_Size); } \
_VCRT_EXPORT_STD _NODISCARD _Ret_notnull_ _Post_writable_byte_size_(_Size) _VCRT_ALLOCATOR \
void* __CRTDECL operator new[](size_t _Size) { return BSMemory::malloc(_Size); } \
void* __CRTDECL operator new(size_t _Size, ::std::align_val_t _Al) { return BSMemory::aligned_alloc(static_cast<size_t>(_Al), _Size); } \
void* __CRTDECL operator new(size_t _Size, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept { return BSMemory::aligned_alloc(static_cast<size_t>(_Al), _Size); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block) noexcept { BSMemory::free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, ::std::nothrow_t const&) noexcept { BSMemory::free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block) noexcept { BSMemory::free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, ::std::nothrow_t const&) noexcept { BSMemory::free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, size_t _Size) noexcept { BSMemory::free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, size_t _Size) noexcept { BSMemory::free(_Block); }\
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, size_t _Size, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, size_t _Size, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); }