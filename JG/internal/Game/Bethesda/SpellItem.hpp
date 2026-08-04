#pragma once

#include "MagicItemForm.hpp"

class SpellItem : public MagicItemForm {
public:
	SpellItem();
	~SpellItem();

	virtual void	Endian();

	struct ALIGN1 _SpellFlags {
		enum Flags {
			ALWAYS_SUCCEEDS		= 1u << 1,
			PC_STARTSPELL		= 1u << 2,
			IMMUNE_TO_SILENCE	= 1u << 3,
			IGNORE_LOS_CHECK	= 1u << 4,
			IGNORE_RESISTANCE	= 1u << 5,
			NO_ABSORB_REFLECT	= 1u << 6,
			FORCE_TOUCH_EXPLODE	= 1u << 7,
		};

		bool						: 1;
		bool bAlwaysSucceeds		: 1;
		bool bPCStartSpell			: 1;
		bool bImmuneToSilence		: 1;
		bool bIgnoreLOSCheck		: 1;
		bool bIgnoreResistance		: 1;
		bool bNoAbsorbReflect		: 1;
		bool bForceTouchExplode		: 1;
	};
	using SpellFlags = _SpellFlags::Flags;

	struct Data {
		MagicSystem::SpellType	eType;
		int32_t					iCostOverride;
		uint32_t				eLevelOverride;
		Bitfield<_SpellFlags>	ucFlags;
	};

	Data kData;

	TESFORM_TYPE(SpellItem);
};

ASSERT_SIZE(SpellItem, 0x44);