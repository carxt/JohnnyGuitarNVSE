#pragma once

#include "Gamebryo/NiSmartPointer.hpp"

class TESModel;
class NiNode;

class Precipitation {
public:
	Precipitation();
	virtual ~Precipitation();

	NiPointer<NiNode>	spCurrentPrecip;
	NiPointer<NiNode>	spLastPrecip;
	NiNode*				pParent;
	float				fBirthRate;
	TESModel*			pCurrentModel;
};

ASSERT_SIZE(Precipitation, 0x18);