#pragma once

#include "BGSSaveGameBuffer.hpp"
#include "BGSSaveLoadFormHeader.hpp"
#include "BSEnums.hpp"

class BGSSaveFormBuffer : public BGSSaveGameBuffer {
public:
	BGSSaveFormBuffer();
	~BGSSaveFormBuffer();

	BGSSaveLoadFormHeader	kHeader;
	TESForm*				pForm;

	void SetHeader(uint32_t auiFormID, uint32_t auiChangeFlags, FORM_TYPE aeFormType, uint8_t aucVersion);

	void SetForm(TESForm* apForm);

	BGSChangeFlags GetChangeFlags() const;

	void RemoveChange(uint32_t auiFlags);
};

ASSERT_SIZE(BGSSaveFormBuffer, 0x24);