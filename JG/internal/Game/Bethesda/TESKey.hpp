#pragma once

#include "TESObjectMISC.hpp"

class TESKey : public TESObjectMISC {
public:
	TESKey();
	~TESKey();

	TESFORM_TYPE(TESKey);
};

ASSERT_SIZE(TESKey, 0xAC);