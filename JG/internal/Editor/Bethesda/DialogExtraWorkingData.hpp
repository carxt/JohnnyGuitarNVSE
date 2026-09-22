#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraWorkingData : public BSExtraData {
public:
	void*	pDataA;
	void*	pDataB;

	BSEXTRA_TYPE(DialogExtraWorkingData);
};

ASSERT_SIZE(DialogExtraWorkingData, 0x14);