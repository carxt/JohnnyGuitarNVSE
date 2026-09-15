#pragma once

class TESForm;

struct ReconstructFormData {
	TESForm*	pForm	= nullptr;
	uint32_t	uiFlags = 0;
};

ASSERT_SIZE(ReconstructFormData, 0x8);