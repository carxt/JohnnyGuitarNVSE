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
			PC_ATTACKED		= 1u << 5,
			PC_MURDERED		= 1u << 6,

			TRACK_CRIME		= 1u << 8,
			ALLOW_SELL		= 1u << 9,
		};

		bool bHiddenFromPC	: 1;
		bool bEvil			: 1;
		bool bSpecialCombat : 1;
		bool bPCExpelled	: 1;
		bool bPCAnEnemy		: 1;
		bool bPCAttacked	: 1;
		bool bPCMurdered	: 1;
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
	void SetFlag(uint32_t auiFlag, bool abVal);

	bool GetIsEvil() const;
	void SetIsEvil(bool abVal);

	bool GetSpecialCombat() const;
	void SetSpecialCombat(bool abVal);

	bool GetPCExpelled() const;
	void SetPCExpelled(bool abVal);

	bool GetPCAnEnemy() const;
	void SetPCAnEnemy(bool abVal);

	bool GetPCAttacked() const;
	void SetPCAttacked(bool abVal);

	bool GetPCMurdered() const;
	void SetPCMurdered(bool abVal);

	bool GetTrackCrime() const;
	void SetTrackCrime(bool abVal);

	bool GetAllowSell() const;
	void SetAllowSell(bool abVal);

	TESReputation* GetReputation() const;
	void SetReputation(TESReputation* apReputation);

	int32_t GetMinorCrime() const;
	void SetMinorCrime(int32_t aiCount);

	int32_t GetMajorCrime() const;
	void SetMajorCrime(int32_t aiCount);

#ifdef GAME
	void AddMinorCrime(int32_t aiCount, bool abModRep);
	void AddMajorCrime(int32_t aiCount, bool abModRep);

	void SetFactionReaction(TESFaction* apFaction, int32_t aiReaction);
	void ModFactionReaction(TESFaction* apFaction, int32_t aiReaction);
#endif

	FIGHT_REACTION GetFactionFightReaction(TESFaction* apFaction) const;
#ifdef GAME
	void SetFactionFightReaction(TESFaction* apFaction, FIGHT_REACTION aeFightReaction);
#endif
};

#ifdef GAME
ASSERT_SIZE(TESFaction, 0x4C);
#else
ASSERT_SIZE(TESFaction, 0x60);
#endif