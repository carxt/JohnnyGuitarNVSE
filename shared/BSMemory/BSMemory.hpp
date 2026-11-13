#pragma once

namespace BSMemory {

	// For manual initialization;
	// By default, automatically called once by the first allocation
	extern bool initialize();

	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* __cdecl malloc(size_t size);
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* __cdecl calloc(size_t num, size_t size);
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* __cdecl aligned_alloc(size_t alignment, size_t size);
	[[nodiscard]] extern __declspec(allocator) __declspec(restrict) void* __cdecl realloc(void* ptr, size_t new_size);

	extern __declspec(noalias) void __cdecl free(void* ptr);
	extern __declspec(noalias) void __cdecl free_sized(void* ptr, size_t size);
	extern __declspec(noalias) void __cdecl	aligned_free(void* ptr);
	extern __declspec(noalias) void __cdecl free_aligned_sized(void* ptr, size_t alignment, size_t size);

	extern __declspec(noalias) size_t __cdecl msize(void* ptr);

	template <typename T>
	[[nodiscard]] inline __declspec(allocator) __declspec(restrict) T* __cdecl malloc(size_t count = 1) {
		return static_cast<T*>(BSMemory::malloc(sizeof(T) * count));
	};

	template <typename T>
	[[nodiscard]] inline __declspec(allocator) __declspec(restrict) T* __cdecl calloc(size_t count) {
		return static_cast<T*>(BSMemory::calloc(count, sizeof(T)));
	};

	template <typename T>
	[[nodiscard]] inline __declspec(allocator) __declspec(restrict) T* __cdecl aligned_alloc() {
		return static_cast<T*>(BSMemory::aligned_alloc(alignof(T), sizeof(T)));
	};

	template <typename T, const uint32_t ConstructorPtr = 0, typename... Args>
	[[nodiscard]] inline __declspec(restrict) T* create(Args &&... args) {
		T* ptr = BSMemory::malloc<T>();
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
		BSMemory::free(ptr);
	}

	template <typename T, const uint32_t ConstructorPtr = 0, typename... Args>
	[[nodiscard]] inline __declspec(restrict) T* create_aligned(Args &&... args) {
		T* ptr = BSMemory::aligned_alloc<T>();
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
		BSMemory::aligned_free(ptr);
	}
}

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
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, size_t _Size) noexcept { BSMemory::free_sized(_Block, _Size); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, size_t _Size) noexcept { BSMemory::free_sized(_Block, _Size); }\
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, ::std::align_val_t _Al, ::std::nothrow_t const&) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete(void* _Block, size_t _Size, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); } \
_VCRT_EXPORT_STD void __CRTDECL operator delete[](void* _Block, size_t _Size, ::std::align_val_t _Al) noexcept { BSMemory::aligned_free(_Block); }