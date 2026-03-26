#include "BGSEncounterZone.hpp"

// GAME - 0x546A90
BGSEncounterZone* BGSEncounterZone::GetNoZone() {
    return pNoZone;
}

// GAME - 0x9611E0
TESForm* BGSEncounterZone::GetOwnerForm() const {
    return kData.pOwner;
}

void BGSEncounterZone::SetOwnerForm(TESForm* apOwner) {
	kData.pOwner = apOwner;
}

// GAME - 0x567AB0
uint8_t BGSEncounterZone::GetOwnerFactionRank() const {
    return kData.ucOwnerRank;
}

void BGSEncounterZone::SetOwnerFactionRank(uint8_t aucOwnerRank) {
	kData.ucOwnerRank = aucOwnerRank;
}

// GAME - 0x663A50
uint8_t BGSEncounterZone::GetMinLevel() const {
    return kData.ucMinLevel;
}

void BGSEncounterZone::SetMinLevel(uint8_t aucMinLevel) {
	kData.ucMinLevel = aucMinLevel;
}

// GAME - 0x526320
bool BGSEncounterZone::GetNeverReset() const {
    return kData.ucFlags.bNeverReset;
}

// GAME - 0x5DAC10
void BGSEncounterZone::SetNeverReset(bool abVal) {
    kData.ucFlags.bNeverReset = abVal;
}

// GAME - 0x526250
bool BGSEncounterZone::GetMatchPCBelowMin() const {
    return kData.ucFlags.bStrictMinLevel;
}

void BGSEncounterZone::SetMatchPCBelowMin(bool abVal) {
	kData.ucFlags.bStrictMinLevel = abVal;
}

// GAME - 0x7AF430
uint32_t BGSEncounterZone::GetDetachTime() const {
    return kGameData.uiDetachTime;
}

// GAME - 0x526070
void BGSEncounterZone::SetDetachTime(uint32_t auiDetachTime) {
	ThisCall(0x526070, this, auiDetachTime);
}

uint32_t BGSEncounterZone::GetAttachTime() const {
    return kGameData.uiAttachTime;
}

// GAME - 0x5260A0
void BGSEncounterZone::SetAttachTime(uint32_t auiAttachTime) {
	ThisCall(0x5260A0, this, auiAttachTime);
}

// GAME - 0x567EC0
uint16_t BGSEncounterZone::GetZoneLevel() const {
	return ThisCall<uint16_t>(0x567EC0, this);
}

// GAME - 0x526160
void BGSEncounterZone::SetZoneLevel(uint16_t ausZoneLevel) {
	ThisCall(0x526160, this, ausZoneLevel);
}

// GAME - 0x526190
uint16_t BGSEncounterZone::GetCalcedZoneLevel() const {
    return ThisCall<uint16_t>(0x526190, this);
}
