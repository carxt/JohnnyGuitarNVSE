#pragma once

#include "TESForm.hpp"
#include "ImageSpaceParameterData.hpp"

class TESImageSpace : public TESForm {
public:
	TESImageSpace();
	~TESImageSpace();

	ImageSpaceParameterData kData;

	TESFORM_TYPE(TESImageSpace);
};

#ifdef GAME
ASSERT_SIZE(TESImageSpace, 0xB0);
#else
ASSERT_SIZE(TESImageSpace, 0xC4);
#endif