#include "BGSEquipType.hpp"

// GAME - 0x726070
BGSEquipType::Type BGSEquipType::GetEquipType() const {
    return eEquipType;
}

// GAME - 0x6ECD40
void BGSEquipType::SetEquipType(Type aeEquipType) {
	eEquipType = aeEquipType;
}

// GAME - 0x479430
BGSEquipType::Type BGSEquipType::GetEquipType(const TESForm* apForm) {
	return CdeclCall<Type>(0x479430, apForm);
}

// GAME - 0x479510
BGSMenuIcon* BGSEquipType::GetEquipTypeIcon(Type aeType) {
	return CdeclCall<BGSMenuIcon*>(0x479510, aeType);
}

// GAME - 0x479540
const char* BGSEquipType::GetEquipTypeIconFilename(Type aeType) {
	return CdeclCall<const char*>(0x479540, aeType);
}
