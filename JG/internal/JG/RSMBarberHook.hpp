#pragma once
#include "JG\JGSetList.hpp"
#include "GameForms.h"

namespace RSMBarberHook {
	void Install();
	void Reset();
	void Load(BGSListForm* pList);
	void ShowMenu(uint32_t flags);
};
