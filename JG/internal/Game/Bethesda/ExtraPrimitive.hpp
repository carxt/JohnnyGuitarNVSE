#pragma once

#include "BSExtraData.hpp"

class BGSPrimitive;

class ExtraPrimitive : public BSExtraData {
public:
	ExtraPrimitive();
	~ExtraPrimitive();

	BGSPrimitive *pPrimitive;

	BSEXTRA_TYPE(ExtraPrimitive);
};

ASSERT_SIZE(ExtraPrimitive, 0x10);