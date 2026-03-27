#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESDescription.hpp"
#include "TESTexture.hpp"
#include "TESAttributes.hpp"

class TESClass : public TESForm, public TESFullName, public TESDescription, public TESTexture, public TESAttributes {
public:
	TESClass();
	~TESClass();

	struct ALIGN1 _ClassFlags {
		enum Flags : uint8_t{
			PLAYABLE = 1u << 0,
			GUARD	 = 1u << 1,
		};

		bool bPlayable	: 1;
		bool bGuard		: 1;
	};
	using ClassFlags = _ClassFlags::Flags;

	struct ALIGN4 _ServiceFlags {
		enum Flags : uint32_t {
			WEAPONS		= 1u << 0,
			ARMOR		= 1u << 1,
			ALCOHOL		= 1u << 2,
			BOOKS		= 1u << 3,
			FOOD		= 1u << 4,
			CHEMS		= 1u << 5,
			STIMPAKS	= 1u << 6,
			LIGHTS		= 1u << 7,
			APPARATUS	= 1u << 8,

			MISC		= 1u << 10,
			SPELLS		= 1u << 11,
			MAGIC_ITEMS	= 1u << 12,
			POTIONS		= 1u << 13,
			TRAINING	= 1u << 14,

			RECHARGE	= 1u << 16,
			REPAIR		= 1u << 17,
		};

		bool bWeapons		: 1;
		bool bArmor			: 1;
		bool bAlcohol		: 1;
		bool bBooks			: 1;
		bool bFood			: 1;
		bool bChems			: 1;
		bool bStimpaks		: 1;
		bool bLights		: 1;
		bool bApparatus		: 1;
		bool 				: 1;
		bool bMisc			: 1;
		bool bSpells		: 1;
		bool bMagicItems	: 1;
		bool bPotions		: 1;
		bool bTraining		: 1;
		bool 				: 1;
		bool bRecharge		: 1;
		bool bRepair		: 1;
	};
	using ServiceFlags = _ServiceFlags::Flags;

	struct Data {
		uint32_t				uiTagSkills[4];
		Bitfield<_ClassFlags>	ucFlags;
		Bitfield<_ServiceFlags>	uiServices;
		bool					bTeaches;
		uint8_t					ucTrainingLevel;
	};

	Data kData;

	TESFORM_TYPE(TESClass);
};

ASSERT_SIZE(TESClass, 0x60);