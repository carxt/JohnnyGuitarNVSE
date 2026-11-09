#pragma once

// BSConcepts
namespace BSC {

	// ListBox and ListBoxItem
	template<class T>
	concept LBItem = std::integral<T> || std::is_enum_v<T> || std::is_pointer_v<T> || std::is_null_pointer_v<T>;

};