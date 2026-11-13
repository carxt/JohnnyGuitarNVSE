#include "BGSEquipType.hpp"

#ifndef GAME
#include "BGSMenuIcon.hpp"
static constexpr AddressPtr<BGSMenuIcon*, 0xED3D78, 14> pEquipTypeMenuIcons;
#endif

// GAME - 0x726070
BGSEquipType::Type BGSEquipType::GetEquipType() const {
    return eEquipType;
}

// GAME - 0x6ECD40
void BGSEquipType::SetEquipType(Type aeEquipType) {
	eEquipType = aeEquipType;
}

#ifdef GAME
// GAME - 0x479430
BGSEquipType::Type BGSEquipType::GetEquipType(const TESForm* apForm) {
	return CdeclCall<Type>(0x479430, apForm);
}
#endif

// GAME - 0x479510
BGSMenuIcon* BGSEquipType::GetEquipTypeIcon(Type aeType) {
#ifdef GAME
	return CdeclCall<BGSMenuIcon*>(0x479510, aeType);
#else
	if (aeType < Type::COUNT)
		return pEquipTypeMenuIcons[aeType];
	return nullptr;
#endif
}

// GAME - 0x479540
const char* BGSEquipType::GetEquipTypeIconFilename(Type aeType) {
#ifdef GAME
	return CdeclCall<const char*>(0x479540, aeType);
#else
	BGSMenuIcon* pIcon = GetEquipTypeIcon(aeType);
	if (pIcon)
		return pIcon->GetTextureName();
	return "";
#endif
}
