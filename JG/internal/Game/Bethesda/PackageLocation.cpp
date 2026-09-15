#include "PackageLocation.hpp"

// GAME - 0x67F030
// GECK - 0x49E610
PackageLocation::PackageLocation() {
#ifdef GAME
	ThisCall(0x67F030, this);
#else
	ThisCall(0x49E610, this);
#endif
}

// GAME - 0x67F110
// GECK - 0x49E6B0
PackageLocation::~PackageLocation() {
#ifdef GAME
	ThisCall(0x67F110, this);
#else
	ThisCall(0x49E6B0, this);
#endif
}

// GAME - 0x67F140
// GECK - 0x49E6D0
void PackageLocation::SetLocType(PACKAGE_LOCATION_TYPE aeType) {
#ifdef GAME
	ThisCall(0x67F140, this, aeType);
#else
	ThisCall(0x49E6D0, this, aeType);
#endif
}

PACKAGE_LOCATION_TYPE PackageLocation::GetLocType() const {
	return static_cast<PACKAGE_LOCATION_TYPE>(eLocationType);
}

// GAME - 0x67F3C0
void PackageLocation::SetLocReference(TESObjectREFR* apReference) {
#ifdef GAME
	ThisCall(0x67F3C0, this, apReference);
#else
	eLocationType = PACKAGE_LOCATION_TYPE::REFERENCE;
	uObject.pReference = apReference;
#endif
}

// GAME - 0x67F1F0
// GAME - 0x49E740
void PackageLocation::SetRadius(uint32_t auiRadius) {
#ifdef GAME
	ThisCall(0x67F1F0, this, auiRadius);
#else
	ThisCall(0x49E740, this, auiRadius);
#endif
}

// GAME - 0x67F1C0
// GECK - 0x49E720
uint32_t PackageLocation::GetRadius() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x67F1C0, this);
#else
	return ThisCall<uint32_t>(0x49E720, this);
#endif
}