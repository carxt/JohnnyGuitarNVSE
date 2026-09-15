#include "BGSProjectile.hpp"

// GAME - 0x4EA950
const BGSProjectile::Data& BGSProjectile::GetData() const {
	return kData;
}

// GAME - 0x4EA950
BGSProjectile::Data& BGSProjectile::GetData() {
	return kData;
}

// GAME - 0x4FD420
bool BGSProjectile::GetFlag(uint32_t auiFlag) const {
	return GetData().uiFlags.IsSet(auiFlag);
}

void BGSProjectile::SetFlag(uint32_t auiFlag, bool abVal) {
	GetData().uiFlags.Set(auiFlag, abVal);
}

// GAME - 0x9A7F80
bool BGSProjectile::GetHitScan() const {
	return kData.uiFlags.bHitScan;
}

// GAME - 0x4FD360
bool BGSProjectile::GetHasExplosion() const {
	return kData.uiFlags.bHasExplosion;
}

// GAME - 0x975300
bool BGSProjectile::GetHasExplosionAltTrigger() const {
	return kData.uiFlags.bHasExplosionAltTrigger;
}

// GAME - 0x9BAF30
bool BGSProjectile::GetHasMuzzleFlash() const {
	return kData.uiFlags.bHasMuzzleFlash;
}

// GAME - 0x4FDF20
bool BGSProjectile::GetCanTurnOff() const {
	return kData.uiFlags.bCanTurnOff;
}

// GAME - 0x4FDF40
bool BGSProjectile::GetCanPickup() const {
	return kData.uiFlags.bCanPickUp;
}

// GAME - 0x9BC870
bool BGSProjectile::GetSupersonic() const {
	return kData.uiFlags.bSupersonic;
}

// GAME - 0x9B7C90
bool BGSProjectile::GetPinsLimbs() const {
	return kData.uiFlags.bPinsLimbs;
}

// GAME - 0x9C2E60
bool BGSProjectile::GetPassThroughSmallTransparent() const {
	return kData.uiFlags.bPassThroughSmallTransparent;
}

// GAME - 0x5DE080
bool BGSProjectile::GetHasExplosionDetonates() const {
	return kData.uiFlags.bExplosionDetonates;
}

// GAME - 0x9B88E0
bool BGSProjectile::GetHasRotation() const {
	return kData.uiFlags.bRotates;
}

// GAME - 0x4FD4F0
BGSProjectile::MotionType BGSProjectile::GetMotionType() const {
	return MotionType(kData.uiFlags.Get(ProjectileFlags::MOTION_TYPE_MASK));
}

void BGSProjectile::SetMotionType(MotionType aeType) {
	kData.uiFlags.Clear(ProjectileFlags::MOTION_TYPE_MASK);
	kData.uiFlags.Set(aeType);
}

// GAME - 0x966980
float BGSProjectile::GetGravity() const {
#ifdef GAME
	return ThisCall<float>(0x966980, this);
#else
	if (kData.uiFlags.bMotionGrenade)
		return 1.f;

	return kData.fGravity;
#endif
}

void BGSProjectile::SetGravity(float afGravity) {
	kData.fGravity = afGravity;
}

// GAME - 0x69EF80
float BGSProjectile::GetSpeed() const {
	return kData.fSpeed;
}

void BGSProjectile::SetSpeed(float afSpeed) {
	kData.fSpeed = afSpeed;
}

// GAME - 0x9A7C40
float BGSProjectile::GetRange() const {
	return kData.fRange;
}

void BGSProjectile::SetRange(float afRange) {
	kData.fRange = afRange;
}

// GAME - 0x4FD380
TESObjectLIGH* BGSProjectile::GetLight() const {
	return kData.pLight;
}

// GAME - 0x57BD60
void BGSProjectile::SetLight(TESObjectLIGH* apLight) {
	kData.pLight = apLight;
}

// GAME - 0x4FD3A0
TESObjectLIGH* BGSProjectile::GetMuzzleFlashLight() const {
	return kData.pMuzzleFlashLight;
}

// GAME - 0x4FEBB0
void BGSProjectile::SetMuzzleFlashLight(TESObjectLIGH* apLight) {
	kData.pMuzzleFlashLight = apLight;
}

// GAME - 0x6A78F0
float BGSProjectile::GetTracerChance() const {
	return kData.fTracerChance;
}

void BGSProjectile::SetTracerChance(float afVal) {
	kData.fTracerChance = afVal;
}

// GAME - 0x45CD80
float BGSProjectile::GetExplosionProximity() const {
	return kData.fExplosionProximity;
}

void BGSProjectile::SetExplosionProximity(float afVal) {
	kData.fExplosionProximity = afVal;
}

// GAME - 0x644790
float BGSProjectile::GetExplosionTimer() const {
	return kData.fExplosionTimer;
}

void BGSProjectile::SetExplosionTimer(float afVal) {
	kData.fExplosionTimer = afVal;
}

// GAME - 0x4FD3C0
BGSExplosion* BGSProjectile::GetExplosion() const {
	return kData.pExplosionType;
}

// GAME - 0x4FB090
void BGSProjectile::SetExplosion(BGSExplosion* apExplosion) {
	kData.pExplosionType = apExplosion;
}

// GAME - 0x4FD3E0
TESSound* BGSProjectile::GetActiveSound() const {
	return kData.pActiveSoundLoop;
}

// GAME - 0x857230
void BGSProjectile::SetActiveSound(TESSound* apSound) {
	kData.pActiveSoundLoop = apSound;
}

// GAME - 0x507E10
float BGSProjectile::GetMuzzleFlashDuration() const {
	return kData.fMuzzleFlashDuration;
}

void BGSProjectile::SetMuzzleFlashDuration(float afVal) {
	kData.fMuzzleFlashDuration = afVal;
}

// GAME - 0x6CA4E0
float BGSProjectile::GetFadeOutTime() const {
	return kData.fFadeOutTime;
}

void BGSProjectile::SetFadeOutTime(float afVal) {
	kData.fFadeOutTime = afVal;
}

// GAME - 0x644930
float BGSProjectile::GetImpactForce() const {
	return kData.fImpactForce;
}

void BGSProjectile::SetImpactForce(float afVal) {
	kData.fImpactForce = afVal;
}

// GAME - 0x810FD0
TESSound* BGSProjectile::GetCountdownSound() const {
	return kData.pActiveSoundLoop;
}

// GAME - 0x4078A0
void BGSProjectile::SetCountdownSound(TESSound* apSound) {
	kData.pActiveSoundLoop = apSound;
}

// GAME - 0x586150
TESSound* BGSProjectile::GetDeactivateSound() const {
	return kData.pDeactivateSound;
}

// GAME - 0x810570
void BGSProjectile::SetDeactivateSound(TESSound* apSound) {
	kData.pDeactivateSound = apSound;
}

// GAME - 0x4FD400
TESObjectWEAP* BGSProjectile::GetDefaultWeaponSource() const {
	return kData.pDefaultWeapSrc;
}

// GAME - 0x500A20
void BGSProjectile::SetDefaultWeaponSource(TESObjectWEAP* apWeapon) {
	kData.pDefaultWeapSrc = apWeapon;
}

// GAME - 0x812870
float BGSProjectile::GetRotationX() const {
	return kData.fRotationX;
}

void BGSProjectile::SetRotationX(float afVal) {
	kData.fRotationX = afVal;
}

// GAME - 0x9B88A0
float BGSProjectile::GetRotationY() const {
	return kData.fRotationY;
}

void BGSProjectile::SetRotationY(float afVal) {
	kData.fRotationY = afVal;
}

// GAME - 0x9B88C0
float BGSProjectile::GetRotationZ() const {
	return kData.fRotationZ;
}

void BGSProjectile::SetRotationZ(float afVal) {
	kData.fRotationZ = afVal;
}

// GAME - 0x6D2C20
float BGSProjectile::GetBounceMultiplier() const {
	return kData.fBounceMultiplier;
}

void BGSProjectile::SetBounceMultiplier(float afVal) {
	kData.fBounceMultiplier = afVal;
}

// GAME - 0x6AB360
const TESModel* BGSProjectile::GetMuzzleFlashModel() const {
	return &kMuzzleFlash;
}

// GAME - 0x6AB360
TESModel* BGSProjectile::GetMuzzleFlashModel() {
	return &kMuzzleFlash;
}

// GAME - 0x9AD610
SOUND_LEVEL BGSProjectile::GetSoundLevel() const {
	return eSoundLevel;
}

void BGSProjectile::SetSoundLevel(SOUND_LEVEL aeLevel) {
	eSoundLevel = aeLevel;
}

#ifdef GAME
bool BGSProjectile::DecideIsTracer() const {
	return ThisCall<bool>(0x4FDF60, this);
}
#endif
