#pragma once

#include "MagicItemForm.hpp"

class EnchantmentItem : public MagicItemForm {
public:
	EnchantmentItem();
	~EnchantmentItem();

	virtual void	Endian();

	struct ALIGN1 _Flags {
		enum Flags {
			EXTEND_DURATION	= 1u << 1,
			HIDE_EFFECT		= 1u << 2,
		};

		bool					: 1;
		bool bExtendDuration	: 1;
		bool bHideEffect		: 1;
	};
	using Flags = _Flags::Flags;

	struct Data {
		MagicSystem::CastingType	eType;
		int32_t						iChargeOverride;
		int32_t						iCostOverride;
		Bitfield<_Flags>			ucFlags;
	};

	Data	kData;

	TESFORM_TYPE(EnchantmentItem);
};

ASSERT_SIZE(EnchantmentItem, 0x44);