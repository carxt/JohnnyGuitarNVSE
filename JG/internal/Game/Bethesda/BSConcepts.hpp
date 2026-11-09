#pragma once

#include "Gamebryo/NiConcepts.hpp"

// BSConcepts
namespace BSC {

	// BSSimpleList
	template<class T>
	concept BSLItem = NiC::NiItem<T>;

	// BSMap
	template<class T>
	concept BSMapItem = NiC::NiMapItem<T>;

	// BSMap
	template<class T>
	concept BSMapKey = NiC::NiMapKey<T>;

	// ListBox and ListBoxItem
	template<class T>
	concept LBItem = std::integral<T> || std::is_enum_v<T> || std::is_pointer_v<T> || std::is_null_pointer_v<T>;

};