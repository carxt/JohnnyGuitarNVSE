#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESDescription.hpp"
#include "Bethesda/TESScriptableForm.hpp"
#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/TESFullName.hpp"

class TESChallenge : public TESForm, public TESFullName, public TESDescription, public TESScriptableForm, public TESIcon, public BGSMessageIcon {
public:
	TESChallenge();
	~TESChallenge();

	struct ALIGN4 ChallengeFlags {
		enum _Flags : uint32_t {
			LOCKED			= 1u << 0,
			COMPLETED		= 1u << 1,

			NO_RECURRING	= 1u << 3,
		};

		bool bLocked		: 1;
		bool bCompleted		: 1;
		bool				: 1;
		bool bNoRecurring	: 1;
	};
	using ChallengeFlag = ChallengeFlags::_Flags;

	struct ALIGN4 ChallengeDataFlags {
		enum _Flags : uint32_t {
			START_DISABLED		= 1u <<  0,
			RECURRING			= 1u <<  1,
			SHOW_ZERO_PROGRESS	= 1u <<  2,
		};

		bool bStartDisabled		: 1;
		bool bRecurring			: 1;
		bool bShowZeroProgress	: 1;
	};
	using ChallengeDataFlag = ChallengeDataFlags::_Flags;

	enum Type : uint32_t {
		KILL_FROM_A_FORM_LIST		= 0,
		KILL_A_SPECIFIC_FORMID		= 1,
		KILL_ANY_IN_A_CATEGORY		= 2,
		HIT_AN_ENEMY				= 3,
		DISCOVER_A_MAP_MARKER		= 4,
		USE_AN_ITEM					= 5,
		ACQUIRE_AN_ITEM				= 6,
		USE_A_SKILL					= 7,
		DO_DAMAGE					= 8,
		USE_AN_ITEM_FROM_A_LIST		= 9,
		ACQUIRE_AN_ITEM_FROM_A_LIST	= 10,
		MISCELLANEOUS_STAT			= 11,
		CRAFT_USING_AN_ITEM			= 12,
		SCRIPTED_CHALLENGE			= 13,
	};

	struct ChallengeData {

		Type							eType;
		uint32_t						uiThreshold;
		Bitfield<ChallengeDataFlags>	uiFlags;
		uint32_t						uiInterval;
		uint16_t						usValue1;
		uint16_t						usValue2;
		uint16_t						usValue3;
	};

	ChallengeData				kData;
	uint32_t					uiAmount;
	Bitfield<ChallengeFlags>	uiChallengeFlags;
	TESForm*					pFormA;
	TESForm*					pFormB;

	TESFORM_TYPE(TESChallenge);
};

ASSERT_SIZE(TESChallenge, 0x7C);