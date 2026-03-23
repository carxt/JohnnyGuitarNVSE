#pragma once
#include <unordered_map>
#include "JG\JGSetList.hpp"

namespace BarterFilter {
	enum Flags {
		kDoNotHideLeft = 1 << 0,
		kDoNotHideRight
	};
	extern std::unordered_map<DWORD, JGSetList<DWORD>> leftList;
	extern std::unordered_map<DWORD, JGSetList<DWORD>> rightList;
	void Install();
	void Reset();
}