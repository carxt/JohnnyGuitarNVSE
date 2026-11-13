#pragma once

// NiConcepts
namespace NiC {

	template<class T>
	concept NiItemBase = std::is_default_constructible_v<T> && std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>;

	template<class T>
	concept NiItemZero = !std::is_pointer_v<T> && std::is_constructible_v<T, uint32_t> && requires (T a) { a = uint32_t(0); };

	template<class T>
	concept NiItemNullPtr = std::is_pointer_v<T> || (std::is_constructible_v<T, nullptr_t> && std::is_assignable_v<T, nullptr_t>);

	template<class T>
	concept NiItem = (NiItemZero<T> || NiItemNullPtr<T>) && NiItemBase<T>;

	template<class T>
	concept NiMapItem = NiItem<T>;

	template<class T>
	concept NiMapKey = NiItemBase<T> && std::equality_comparable<T> && requires (T a) { size_t(a); };

	template<class T>
	using PickEmptyType = std::conditional_t<NiC::NiItemZero<T>, uint32_t, nullptr_t>;

};