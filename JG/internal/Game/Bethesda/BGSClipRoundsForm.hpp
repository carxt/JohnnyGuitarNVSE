#pragma once

#include "BaseFormComponent.hpp"

class BGSClipRoundsForm : public BaseFormComponent {
public:
	BGSClipRoundsForm();
	~BGSClipRoundsForm();

	uint8_t	ucClipRounds;

	uint32_t GetFormClipRounds() const;
	void SetFormClipRounds(uint32_t auiClipRounds);

	static uint32_t GetFormClipRounds(const TESForm* apForm);
};

ASSERT_SIZE(BGSClipRoundsForm, 0x8);