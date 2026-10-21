#pragma once

#include "BSSimpleArray.hpp"
#include "ReconstructFormData.hpp"

class BGSReconstructedForms {
public:
	BSSimpleArray<ReconstructFormData> kForms[2];
};

ASSERT_SIZE(BGSReconstructedForms, 0x20);