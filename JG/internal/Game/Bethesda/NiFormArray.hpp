#pragma once

#include "Gamebryo/NiTLargePrimitiveArray.hpp"

class TESForm;

class NiFormArray : public NiTLargePrimitiveArray<TESForm*> {
public:
	TESForm* GetFormAt(uint32_t auiIndex) const;
	void InsertFormAt(uint32_t auiIndex, TESForm* apForm);

	uint32_t GetIndexForForm(const TESForm* apForm) const;
};

ASSERT_SIZE(NiFormArray, 0x18);