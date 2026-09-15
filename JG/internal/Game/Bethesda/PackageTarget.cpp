#include "PackageTarget.hpp"

// GAME - 0x67FF70
// GECK - 0x4A0580
PackageTarget::PackageTarget() {
#ifdef GAME
	ThisCall(0x67FF70, this);
#else
	ThisCall(0x4A0580, this);
#endif
}

// GAME - 0x483710
// GECK - 0x846650
PackageTarget::~PackageTarget() {
}

// GAME - 0x6800B0
// GECK - 0x4A05E0
void PackageTarget::SetTargType(PACKAGE_TARGET_TYPE aeType) {
#ifdef GAME
	ThisCall(0x6800B0, this, aeType);
#else
	ThisCall(0x4A05E0, this, aeType);
#endif
}

// GAME - 0x519B00
// GECK - 0x4A05A0
PACKAGE_TARGET_TYPE PackageTarget::GetTargType() const {
	return static_cast<PACKAGE_TARGET_TYPE>(eTargetType);
}

// GAME - 0x680110
void PackageTarget::SetTargReference(TESObjectREFR* apReference) {
#ifdef GAME
	ThisCall(0x680110, this, apReference);
#else
	if (GetTargType() == PACKAGE_TARGET_TYPE::REFERENCE)
		uObject.pReference = apReference;
#endif
}

// GAME - 0x680020
TESObjectREFR* PackageTarget::GetTargReference() const {
#ifdef GAME
	return ThisCall<TESObjectREFR*>(0x680020, this);
#else
	if (GetTargType() == PACKAGE_TARGET_TYPE::REFERENCE)
		return uObject.pReference;
	return nullptr;
#endif
}