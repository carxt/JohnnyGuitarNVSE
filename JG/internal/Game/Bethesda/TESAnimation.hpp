#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"

class TESAnimation : public BaseFormComponent {
public:
	TESAnimation();
	~TESAnimation();

#ifdef EDITOR
	BSSimpleList<void*>		  kUnk04;
#endif
	BSSimpleList<const char*> kKFPaths;
};

#ifdef GAME
ASSERT_SIZE(TESAnimation, 0xC);
#else
ASSERT_SIZE(TESAnimation, 0x14);
#endif