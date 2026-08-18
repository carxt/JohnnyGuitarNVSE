#pragma once

#include "TESObjectCELL.hpp"

class BGSLightingTemplate : public TESForm {
public:
	BGSLightingTemplate();
	~BGSLightingTemplate();

	TESObjectCELL::InteriorData kData;

	TESFORM_TYPE(BGSLightingTemplate);
};

ASSERT_SIZE(BGSLightingTemplate, 0x44);