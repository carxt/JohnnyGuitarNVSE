#include "BGSProjectile.hpp"

// GAME - 0x4EA950
const BGSProjectile::Data& BGSProjectile::GetData() const {
	return kData;
}

// GAME - 0x4FD420
bool BGSProjectile::IsFlagSet(uint32_t auiFlag) const {
	return GetData().uiFlags.IsSet(auiFlag);
}

// GAME - 0x9A7F80
bool BGSProjectile::GetHitScan() const {
	return GetData().uiFlags.bHitScan;
}

// GAME - 0x4FD360
bool BGSProjectile::GetHasExplosion() const {
	return GetData().uiFlags.bHasExplosion;
}

// GAME - 0x975300
bool BGSProjectile::GetHasExplosionAltTrigger() const {
	return GetData().uiFlags.bHasExplosionAltTrigger;
}

// GAME - 0x9BAF30
bool BGSProjectile::GetHasMuzzleFlash() const {
	return GetData().uiFlags.bHasMuzzleFlash;
}

// GAME - 0x4FDF20
bool BGSProjectile::GetCanTurnOff() const {
	return GetData().uiFlags.bCanTurnOff;
}

// GAME - 0x4FDF40
bool BGSProjectile::GetCanPickup() const {
	return GetData().uiFlags.bCanPickUp;
}

// GAME - 0x9BC870
bool BGSProjectile::GetSupersonic() const {
	return GetData().uiFlags.bSupersonic;
}

// GAME - 0x9B7C90
bool BGSProjectile::GetPinsLimbs() const {
	return GetData().uiFlags.bPinsLimbs;
}

bool BGSProjectile::GetPassThroughSmallTransparent() const {
	return GetData().uiFlags.bPassThroughSmallTransparent;
}

// GAME - 0x5DE080
bool BGSProjectile::GetDetonates() const {
	return GetData().uiFlags.bDetonates;
}

// GAME - 0x9B88E0
bool BGSProjectile::GetRotates() const {
	return GetData().uiFlags.bRotates;
}

// GAME - 0x4FD380
TESObjectLIGH* BGSProjectile::GetLight() const {
	return GetData().pLight;
}

TESObjectLIGH* BGSProjectile::GetMuzzleFlashLight() const {
	return GetData().pMuzzleFlashLight;
}

float BGSProjectile::GetMuzzleFlashDuration() const {
	return GetData().fMuzzleFlashDuration;
}

// GAME - 0x4FD3C0
BGSExplosion* BGSProjectile::GetExplosion() const {
	return GetData().pExplosionForm;
}
