#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESForm;

class TESDescription : public BaseFormComponent {
public:
	TESDescription();
	~TESDescription();

	virtual const char* GetDescription(TESForm* apForm, uint32_t auiChunkID);

	uint32_t	uiFileOffset;
};

ASSERT_SIZE(TESDescription, 0x8);