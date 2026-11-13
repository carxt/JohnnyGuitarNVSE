#pragma once

#include "TESObjectARMO.hpp"

class TESObjectARMA : public TESObjectARMO {
public:
	TESFORM_TYPE(TESObjectARMA);
};

ASSERT_SIZE(TESObjectARMA, sizeof(TESObjectARMO));