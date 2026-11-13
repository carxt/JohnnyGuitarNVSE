#pragma once

#include "BSExtraData.hpp"
#include "BGSPrimitive.hpp"

class ExtraPrimitive : public BSExtraData {
public:
	ExtraPrimitive();
	~ExtraPrimitive();

	BGSPrimitive* pPrimitive;

	BSEXTRA_TYPE(ExtraPrimitive);
};

ASSERT_SIZE(ExtraPrimitive, 0x10);