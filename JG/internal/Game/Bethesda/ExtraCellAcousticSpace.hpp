#pragma once

#include "BSExtraData.hpp"

class BGSAcousticSpace;

class ExtraCellAcousticSpace : public BSExtraData {
public:
	ExtraCellAcousticSpace();
	~ExtraCellAcousticSpace();

	BGSAcousticSpace* pSpace;

	BSEXTRA_TYPE(ExtraCellAcousticSpace);
};

ASSERT_SIZE(ExtraCellAcousticSpace, 0x10);