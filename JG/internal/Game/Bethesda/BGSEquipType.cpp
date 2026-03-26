#include "BGSEquipType.hpp"

// GAME - 0x726070
uint32_t BGSEquipType::GetEquipType() const {
    return eEquipType;
}

// GAME - 0x6ECD40
void BGSEquipType::SetEquipType(uint32_t aeEquipType) {
	eEquipType = aeEquipType;
}

// GAME - 0x479430
uint32_t BGSEquipType::GetEquipType(const TESForm* apForm) {
	return CdeclCall<uint32_t>(0x479430, apForm);
}

// GAME - 0x479510
BGSMenuIcon* BGSEquipType::GetEquipTypeIcon(uint32_t aeType) {
	return CdeclCall<BGSMenuIcon*>(0x479510, aeType);
}

// GAME - 0x479540
const char* BGSEquipType::GetEquipTypeIconFilename(uint32_t aeType) {
	return CdeclCall<const char*>(0x479540, aeType);
}
