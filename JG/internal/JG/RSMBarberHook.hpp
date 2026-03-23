#pragma once
#include "JG\JGSetList.hpp"
namespace RSMBarberHook {
	extern JGSetList<DWORD> haircutSetList;
	extern JGSetList<DWORD> beardSetList;
	void Install();
	void Reset();
};
