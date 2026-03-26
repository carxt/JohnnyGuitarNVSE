#pragma once

#include "TESForm.hpp"

class BGSEncounterZone : public TESForm {
public:
	BGSEncounterZone();
	~BGSEncounterZone();

	struct ALIGN1 _ZoneFlags {
		enum Flags : uint8_t {
			NEVER_RESET					= 1u << 0,
			MATCH_PC_BELOW_MIN_LEVEL	= 1u << 1,
		};

		bool bNeverReset		: 1;
		bool bStrictMinLevel	: 1;
	};
	using ZoneFlags = _ZoneFlags::Flags;

	struct ZoneData {
		TESForm*				pOwner;
		uint8_t					ucOwnerRank;
		uint8_t					ucMinLevel;
		Bitfield<_ZoneFlags>	ucFlags;
	};

	struct GameData {
		uint32_t uiDetachTime;
		uint32_t uiAttachTime;
		uint32_t uiResetTime;
		uint16_t usZoneLevel;
	};

	ZoneData kData;
	GameData kGameData;

	TESFORM_TYPE(BGSEncounterZone);

	static BGSEncounterZone* GetNoZone();

	TESForm* GetOwnerForm() const;
	void SetOwnerForm(TESForm* apOwner);

	uint8_t GetOwnerFactionRank() const;
	void SetOwnerFactionRank(uint8_t aucOwnerRank);

	uint8_t GetMinLevel() const;
	void SetMinLevel(uint8_t aucMinLevel);

	bool GetNeverReset() const;
	void SetNeverReset(bool abVal);

	bool GetMatchPCBelowMin() const;
	void SetMatchPCBelowMin(bool abVal);

	uint32_t GetDetachTime() const;
	void SetDetachTime(uint32_t auiDetachTime);

	uint32_t GetAttachTime() const;
	void SetAttachTime(uint32_t auiAttachTime);

	uint16_t GetZoneLevel() const;
	void SetZoneLevel(uint16_t ausZoneLevel);

	uint16_t GetCalcedZoneLevel() const;

private:
	static constexpr AddressPtr<BGSEncounterZone*, 0x11C9520> pNoZone;
};

ASSERT_SIZE(BGSEncounterZone, 0x30);