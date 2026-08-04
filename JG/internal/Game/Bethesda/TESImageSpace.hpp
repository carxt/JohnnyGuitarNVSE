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

ASSERT_SIZE(TESImageSpace, 0xB0);