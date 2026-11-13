#pragma once

#include "TESForm.hpp"
#include "TESIcon.hpp"

class BGSMenuIcon : public TESForm, public TESIcon {
public:
	BGSMenuIcon();
	~BGSMenuIcon();

	TESFORM_TYPE(BGSMenuIcon);
};

#ifdef GAME
ASSERT_SIZE(BGSMenuIcon, 0x24);
#else
ASSERT_SIZE(BGSMenuIcon, 0x48);
#endif