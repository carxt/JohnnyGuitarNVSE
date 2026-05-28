#pragma once

#include "Bethesda/TESForm.hpp"

class TESRecipeCategory : public TESForm, public TESFullName {
public:
	TESRecipeCategory();
	~TESRecipeCategory();

	struct ALIGN1 _CategoryFlags {
		enum Flags : uint8_t {
			SUBCATEGORY = 1u << 0,
		};

		bool bSubCategory : 1;
	};
	using CategoryFlags = _CategoryFlags::Flags;

	Bitfield<_CategoryFlags> ucFlags;

	TESFORM_TYPE(TESRecipeCategory);
};

ASSERT_SIZE(TESRecipeCategory, 0x28);