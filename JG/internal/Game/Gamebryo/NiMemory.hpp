#pragma once

[[nodiscard]] extern __declspec(allocator) void*	NiNew(size_t stSize);
[[nodiscard]] extern __declspec(allocator) void*	NiAlloc(size_t stSize);
[[nodiscard]] extern __declspec(allocator) void*	NiAlignedAlloc(size_t stSize, size_t stAlignment);
extern void											NiFree(void* pvMem);
extern void											NiAlignedFree(void* pvMem);
extern void											NiDelete(void* pvMem, size_t stElementSize);

template <typename T_Data>
[[nodiscard]] __declspec(restrict) __declspec(allocator) T_Data* NiNew() {
	return reinterpret_cast<T_Data*>(NiNew(sizeof(T_Data)));
}

template <typename T_Data>
[[nodiscard]] __declspec(restrict) __declspec(allocator) T_Data* NiAlloc(uint32_t auiCount = 1) {
	return reinterpret_cast<T_Data*>(NiAlloc(sizeof(T_Data) * auiCount));
}

template <typename T, const uint32_t ConstructorPtr = 0, typename... Args>
[[nodiscard]] __declspec(restrict) T* NiCreate(Args &&... args) {
	T* pAlloc = NiNew<T>();
	if constexpr (ConstructorPtr) {
		ThisCall(ConstructorPtr, pAlloc, std::forward<Args>(args)...);
	}
	else {
		memset(pAlloc, 0, sizeof(T));
	}
	return static_cast<T*>(pAlloc);
}