#pragma once

class TESForm;

class TESRecipeComponent {
public:
	uint32_t	uiQuantity;
	TESForm*	pItem;

	uint32_t GetQuantity() const;
	void SetQuantity(uint32_t auiQuantity);

	TESForm* GetItem() const;
	void SetItem(TESForm* apItem);
};

ASSERT_SIZE(TESRecipeComponent, 0x8);