#include "TESFurniture.hpp"

// GAME - 0x509450
bool TESFurniture::GetMarkerEnabled(uint32_t auiIndex) const {
#ifdef GAME
	return ThisCall<bool>(0x509450, this, auiIndex);
#else
	if (auiIndex < 30)
		return uiFurnitureFlags.GetBit(auiIndex);
	return false;
#endif
}

void TESFurniture::SetMarkerEnabled(uint32_t auiIndex, bool abEnabled) {
	if (auiIndex < 30)
		uiFurnitureFlags.SetBit(auiIndex, abEnabled);
}

// GAME - 0x5093F0
bool TESFurniture::CanSitOn() const {
#ifdef GAME
	return ThisCall<bool>(0x5093F0, this);
#else
	return uiFurnitureFlags.bCanSitOn;
#endif
}

void TESFurniture::SetCanSitOn(bool abVal) {
	uiFurnitureFlags.bCanSitOn = abVal;
}

// GAME - 0x509420
bool TESFurniture::CanSleepOn() const {
#ifdef GAME
	return ThisCall<bool>(0x509420, this);
#else
	return uiFurnitureFlags.bCanSleepOn;
#endif
}

void TESFurniture::SetCanSleepOn(bool abVal) {
	uiFurnitureFlags.bCanSleepOn = abVal;
}

#ifdef GAME
// GAME - 0x5099C0
float TESFurniture::GetMarkerHeadingOffset(uint32_t auiIndex) const {
	return ThisCall<float>(0x5099C0, this, auiIndex);
}

// GAME - 0x509920
NiPoint3 TESFurniture::GetMarkerTargetOffset(uint32_t auiIndex, float afScale) const {
	return ThisCall<NiPoint3>(0x509920, this, auiIndex, afScale);
}
#endif

// GAME - 0x509510
bool TESFurniture::IsSitMarker(uint32_t auiIndex) {
#ifdef GAME
	return CdeclCall<bool>(0x509510, auiIndex);
#else
	return auiIndex >= 10 && auiIndex <= 20 || auiIndex == 26;
#endif
}

// GAME - 0x5094F0
bool TESFurniture::IsSleepMarker(uint32_t auiIndex) {
#ifdef GAME
	return CdeclCall<bool>(0x5094F0, auiIndex);
#else
	return auiIndex < 10;
#endif
}
