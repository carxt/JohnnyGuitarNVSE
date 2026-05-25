#pragma once

#include "TESForm.hpp"
#include "BGSPreloadable.hpp"

class BGSImpactData;

class BGSImpactDataSet : public TESForm, public BGSPreloadable {
public:
	BGSImpactDataSet();
	~BGSImpactDataSet();

	BGSImpactData* pImpactDatas[12];

	TESFORM_TYPE(BGSImpactDataSet);
};

ASSERT_SIZE(BGSImpactDataSet, 0x4C);