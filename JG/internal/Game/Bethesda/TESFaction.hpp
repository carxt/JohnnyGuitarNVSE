#pragma once

#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESReactionForm.hpp"
#include "TESTexture.hpp"

class TESReputation;

class FactionRankData {
public:
	BSString	strName;
	BSString	strFemaleName;
	TESTexture	kInsignia;
};

class TESFaction : public TESForm, public TESFullName, public TESReactionForm {
public:
	TESFaction();
	~TESFaction();

	struct ALIGN4 _FactionFlags {
		enum Flags : uint32_t {
			HIDDEN_FROM_PC	= 1u << 0,
			EVIL			= 1u << 1,
			SPECIAL_COMBAT	= 1u << 2,
			PC_EXPELLED		= 1u << 3,
			PC_AN_ENEMY		= 1u << 4,
			PC_ATTACK		= 1u << 5,
			PC_MURDER		= 1u << 6,

			TRACK_CRIME		= 1u << 8,
			ALLOW_SELL		= 1u << 9,
		};

		bool bHiddenFromPC	: 1;
		bool bEvil			: 1;
		bool bSpecialCombat : 1;
		bool bPCExpelled	: 1;
		bool bPCAnEnemy		: 1;
		bool bPCAttack		: 1;
		bool bPCMurder		: 1;
		bool 				: 1;
		bool bTrackCrime	: 1;
		bool bAllowSell		: 1;
	};
	using FactionFlags = _FactionFlags::Flags;

	struct Data {
		Bitfield<_FactionFlags> uiFlags;
	};

	Data							kData;
	TESReputation*					pReputation;
	BSSimpleList<FactionRankData*>	kRanks;
	int32_t							iMajorCrime;
	int32_t							iMinorCrime;

	TESFORM_TYPE(TESFaction);

	bool GetFlag(uint32_t auiFlag) const;

	bool GetPCExpelled() const;
};

ASSERT_SIZE(TESFaction, 0x4C);