#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"

class TESAnimation : public BaseFormComponent {
public:
	TESAnimation();
	~TESAnimation();

	BSSimpleList<const char*> kKFPaths;
};

ASSERT_SIZE(TESAnimation, 0xC);