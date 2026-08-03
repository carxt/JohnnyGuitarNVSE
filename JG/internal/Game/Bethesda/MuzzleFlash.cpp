#include "MuzzleFlash.hpp"
#include "Gamebryo/NiAVObject.hpp"

// GAME - 0x9373F0
bool MuzzleFlash::GetEnabled() const {
	return bEnabled;
}

// GAME - 0x560CF0
void MuzzleFlash::SetDurationTimer(float afVal) {
	fDurationTimer = afVal;
}

// GAME - 0x43B230
NiAVObject* MuzzleFlash::Get3D() const {
	return sp3D;
}

// GAME - 0x825C00
BGSProjectile* MuzzleFlash::GetProjectile() const {
	return pProjectile;
}

// GAME - 0x9611E0
TESObjectWEAP* MuzzleFlash::GetWeaponSource() const {
	return pSourceWeapon;
}

// GAME - 0x441110
TESObjectREFR* MuzzleFlash::GetParentRef() const {
	return pParentRef;
}

// GAME - 0x9BAEE0
TESModel* MuzzleFlash::GetMuzzleFlashModel() const {
	return ThisCall<TESModel*>(0x9BAEE0, this);
}

// GAME - 0x9BB7F0
void MuzzleFlash::AttachLight() {
	ThisCall(0x9BB7F0, this);
}

// GAME - 0x9BB850
void MuzzleFlash::DetachLight() {
	ThisCall(0x9BB850, this);
}

// GAME - 0x9BB690
void MuzzleFlash::Enable() {
	ThisCall(0x9BB690, this);
}

//  GAME - 0x9BB080
void MuzzleFlash::Update(float afTimeDelta, TESObjectREFR* apParentRef) {
	ThisCall(0x9BB080, this, afTimeDelta, apParentRef);
}

// GAME - 0x9BB6D0
void MuzzleFlash::SpawnMuzzleFlash(TESObjectREFR* apParentRef, Projectile* apProjectile) {
	CdeclCall(0x9BB6D0, apParentRef, apProjectile);
}
