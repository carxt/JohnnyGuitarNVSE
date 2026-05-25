#pragma once

#include "TESCondition.hpp"
#include "TESDescription.hpp"
#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESIcon.hpp"

class Actor;
class BGSPerkEntry;

class BGSPerk : public TESForm, public TESFullName, public TESDescription, public TESIcon {
public:
	BGSPerk();
	~BGSPerk();

	struct Data {
		bool	bTrait;
		int8_t	cLevel;
		uint8_t	ucNumRanks;
		bool	bPlayable;
		bool	bHidden;
	};

	Data						kData;
	TESCondition				kConditions;
	BSSimpleList<BGSPerkEntry*>	kPerkEntries;

	TESFORM_TYPE(BGSPerk);

	uint8_t GetNumRanks() const;

	int8_t GetLevel() const;

	bool GetIsTrait() const;

	bool GetIsPlayable() const;

	bool IsPerkHidden() const;

	bool IsPerkAvailable(TESObjectREFR* apActionRef) const;

	bool IsPerkAttainable(TESObjectREFR* apActionRef) const;

	BGSPerkEntry* GetPerkEntryByRank(uint8_t aucRank) const;

	bool AddPerkEntry(BGSPerkEntry* apEntry);

	void AddPerkEntryPoints(Actor* apActor, uint8_t aucRank, bool abAlt);

	void ApplyPerk(Actor* apActor, uint8_t aucOldRank, uint8_t aucNewRank, bool abAlt);

	void RemovePerk(Actor* apActor, bool abAlt);

	void BuildDescriptionString(char* apBuffer, uint32_t auiBufferSize);
};

ASSERT_SIZE(BGSPerk, 0x50);