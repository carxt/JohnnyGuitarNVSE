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

	struct ALIGN4 _ProgressFlags {
		enum _Flags : uint32_t {
			UNLOCKED			= 1u << 0,
			COMPLETED			= 1u << 1,
			COMPLETED_RECURRING = 1u << 2,
			REMOVED_RECURRING	= 1u << 3,
		};

		bool bUnlocked				: 1;
		bool bCompleted				: 1;
		bool bCompletedRecurring	: 1;
		bool bRemovedRecurring		: 1;
	};
	using ProgressFlags = _ProgressFlags::_Flags;

	struct ALIGN4 _ChallengeFlags {
		enum _Flags : uint32_t {
			START_LOCKED		= 1u <<  0,
			RECURRING			= 1u <<  1,
			SHOW_ZERO_PROGRESS	= 1u <<  2,
		};

		bool bStartLocked		: 1;
		bool bRecurring			: 1;
		bool bShowZeroProgress	: 1;
	};
	using ChallengeFlags = _ChallengeFlags::_Flags;

	struct _Type {
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
			COUNT,
		};
	};
	using Type = _Type::Type;

	struct Data {
		Type						eType;
		int32_t						iThreshold;
		Bitfield<_ChallengeFlags>	uiFlags;
		int32_t						iInterval;
		uint16_t					usSpecialA;
		uint16_t					usSpecialB;
		uint16_t					usSpecialC;
	};

	struct ProgressData {
		int32_t						iProgress;
		Bitfield<_ProgressFlags>	uiFlags;
	};

	Data			kData;
	ProgressData	kProgressData;
	TESForm*		pFormA;
	TESForm*		pFormB;

	TESFORM_TYPE(TESChallenge);

	Type GetChallengeType() const;
	void SetChallengeType(Type aeType);

	int32_t GetThreshold() const;
	void SetThreshold(int32_t aiVal);

	bool GetStartsLocked() const;
	void SetStartsLocked(bool abVal);

	bool GetRecurring() const;
	void SetRecurring(bool abVal);

	bool GetShowZeroProgress() const;
	void SetShowZeroProgress(bool abVal);

	int32_t GetInterval() const;
	void SetInterval(int32_t aiVal);

	uint32_t GetSpecialA() const;
	void SetSpecialA(uint16_t ausVal);

	uint32_t GetSpecialB() const;
	void SetSpecialB(uint16_t ausVal);

	uint32_t GetSpecialC() const;
	void SetSpecialC(uint16_t ausVal);

	int32_t GetProgress() const;
	void IncrementProgress(int32_t aiVal);

	int32_t GetUnlocked() const;
	void SetUnlocked(bool abVal);

	int32_t GetCompleted() const;
	void SetCompleted(bool abVal);

	int32_t GetCompletedRecurring() const;
	void SetCompletedRecurring(bool abVal);

	int32_t GetRemovedRecurring() const;
	void SetRemovedRecurring(bool abVal);

	TESForm* GetFormA() const;
	void SetFormA(TESForm* apForm);

	TESForm* GetFormB() const;
	void SetFormB(TESForm* apForm);
};

#ifdef GAME
ASSERT_SIZE(TESChallenge, 0x7C);
#else
ASSERT_SIZE(TESChallenge, 0xB8);
#endif