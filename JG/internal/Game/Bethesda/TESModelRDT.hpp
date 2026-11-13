#pragma once

#include "TESModel.hpp"

class TESModelRDT : public TESModel {
public:
	TESModelRDT();
	~TESModelRDT();
};

ASSERT_SIZE(TESModelRDT, sizeof(TESModel));