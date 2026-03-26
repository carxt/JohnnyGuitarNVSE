#pragma once

#include "BaseFormComponent.hpp"

class BGSClipRoundsForm : public BaseFormComponent {
public:
	BGSClipRoundsForm();
	~BGSClipRoundsForm();

	uint8_t	ucClipRounds;

	uint8_t GetFormClipRounds() const;
	void SetFormClipRounds(uint8_t aucClipRounds);
};

ASSERT_SIZE(BGSClipRoundsForm, 0x8);