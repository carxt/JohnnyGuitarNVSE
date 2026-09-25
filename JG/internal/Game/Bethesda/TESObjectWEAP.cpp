#include "TESObjectWEAP.hpp"

// GAME - 0x446390
WEAPON_TYPE TESObjectWEAP::GetWeaponType() const {
	return static_cast<WEAPON_TYPE>(kData.eWeaponType);
}

// GAME - 0x46DCC0
void TESObjectWEAP::SetWeaponType(WEAPON_TYPE aeType) {
	kData.eWeaponType = aeType;
}

// GAME - 0x524B60
uint8_t TESObjectWEAP::GetAmmoPerShot() const {
#ifdef GAME
	return ThisCall<uint8_t>(0x524B60, this);
#else
	return kData.ucAmmoPerShot;
#endif
}

void TESObjectWEAP::SetAmmoPerShot(uint8_t aucVal) {
	kData.ucAmmoPerShot = aucVal;
}

// GAME - 0x8D85E0
// GECK - 0x5FF4D0
ActorValue::Index TESObjectWEAP::GetWeaponSkill() const {
	return kData.eWeaponSkill;
}

void TESObjectWEAP::SetWeaponSkill(ActorValue::Index aeIndex) {
	kData.eWeaponSkill = aeIndex;
}

// GAME - 0x6450C0
bool TESObjectWEAP::IsMeleeWeapon() const {
#ifdef GAME
	return ThisCall<bool>(0x6450C0, this);
#else
	return kData.eWeaponType <= WEAPON_TYPE::TWO_HAND_MELEE;
#endif
}

// GAME - 0x4C0C30
bool TESObjectWEAP::IsRangedWeapon() const {
#ifdef GAME
	return ThisCall<bool>(0x4C0C30, this);
#else
	auto eWeaponType = kData.eWeaponType;
	return eWeaponType >= WEAPON_TYPE::ONE_HAND_PISTOL && eWeaponType <= WEAPON_TYPE::ONE_HAND_THROWN;
#endif
}

// GAME - 0x4C0C60
bool TESObjectWEAP::IsGunWeapon() const {
#ifdef GAME
	return ThisCall<bool>(0x4C0C60, this);
#else
	auto eWeaponType = kData.eWeaponType;
	return eWeaponType >= WEAPON_TYPE::ONE_HAND_PISTOL && eWeaponType <= WEAPON_TYPE::TWO_HAND_LAUNCHER;
#endif
}

// GAME - 0x4C0BF0
// GECK - 0x529D90
bool TESObjectWEAP::IsThrownWeapon() const {
#ifdef GAME
	return ThisCall<bool>(0x4C0BF0, this);
#else
	return ThisCall<bool>(0x529D90, this);
#endif
}

bool TESObjectWEAP::GetIgnoreResist() const {
	return kData.ucFlags.bIgnoreWeapResist;
}

void TESObjectWEAP::SetIgnoreResist(bool abVal) {
	kData.ucFlags.bIgnoreWeapResist = abVal;
}

// GAME - 0x524B40
bool TESObjectWEAP::GetIsAutomaticWeapon() const {
#ifdef GAME
	return ThisCall<bool>(0x524B40, this);
#else
	return kData.ucFlags.bIsAutomatic;
#endif
}

// GAME - 0x645320
void TESObjectWEAP::SetIsAutomaticWeapon(bool abVal) {
	kData.ucFlags.bIsAutomatic = abVal;
}

// GAME - 0x4AD010
bool TESObjectWEAP::GetHasScope() const {
#ifdef GAME
	return ThisCall<bool>(0x4AD010, this);
#else
	return kData.ucFlags.bHasScope;
#endif
}

void TESObjectWEAP::SetHasScope(bool abVal) {
	kData.ucFlags.bHasScope;
}

// GAME - 0x891B70
bool TESObjectWEAP::GetCantDrop() const {
#ifdef GAME
	return ThisCall<bool>(0x891B70, this);
#else
	return kData.ucFlags.bCantDrop;
#endif
}

void TESObjectWEAP::SetCantDrop(bool abVal) {
	kData.ucFlags.bCantDrop = abVal;
}

// GAME - 0x4AB730
bool TESObjectWEAP::GetHideBackpack() const {
#ifdef GAME
	return ThisCall<bool>(0x4AB730, this);
#else
	return kData.ucFlags.bHideBackpack;
#endif
}

void TESObjectWEAP::SetHideBackpack(bool abVal) {
	kData.ucFlags.bHideBackpack = abVal;
}

// GAME - 0x46E8C0
bool TESObjectWEAP::GetIsEmbeddedWeapon() const {
#ifdef GAME
	return ThisCall<bool>(0x46E8C0, this);
#else
	return kData.ucFlags.bEmbeddedWeapon;
#endif
}

void TESObjectWEAP::SetIsEmbeddedWeapon(bool abVal) {
	kData.ucFlags.bEmbeddedWeapon = abVal;
}

// GAME - 0x8B2BF0
bool TESObjectWEAP::GetUse1stPersonISAnims() const {
#ifdef GAME
	return ThisCall<bool>(0x8B2BF0, this);
#else
	return !kData.ucFlags.bNo1stPersonISAnims;
#endif
}

void TESObjectWEAP::SetUse1stPersonISAnims(bool abVal) {
	kData.ucFlags.bNo1stPersonISAnims = !abVal;
}

// GAME - 0x47BCF0
bool TESObjectWEAP::GetIsPlayable() const {
#ifdef GAME
	return ThisCall<bool>(0x47BCF0, this);
#else
	return !kData.ucFlags.bNonPlayable;
#endif
}

void TESObjectWEAP::SetIsPlayable(bool abVal) {
	kData.ucFlags.bNonPlayable = !abVal;
}

// GAME - 0x8BCA70
bool TESObjectWEAP::GetIsPlayerOnly() const {
#ifdef GAME
	return ThisCall<bool>(0x8BCA70, this);
#else
	return kData.uiFlagsEx.bPlayerOnly;
#endif
}

void TESObjectWEAP::SetIsPlayerOnly(bool abVal) {
	kData.uiFlagsEx.bPlayerOnly = abVal;
}

// GAME - 0x8A8E30
bool TESObjectWEAP::GetNPCsUseAmmo() const {
#ifdef GAME
	return ThisCall<bool>(0x8A8E30, this);
#else
	return kData.uiFlagsEx.bNPCsUseAmmo;
#endif
}

// GAME - 0x51F590
void TESObjectWEAP::SetNPCsUseAmmo(bool abVal) {
#ifdef GAME
	ThisCall(0x51F590, this, abVal);
#else
	kData.uiFlagsEx.bNPCsUseAmmo = abVal;
#endif
}

// GAME - 0x897890
bool TESObjectWEAP::GetNoJamAfterReload() const {
#ifdef GAME
	return ThisCall<bool>(0x897890, this);
#else
	return kData.uiFlagsEx.bNoJamAfterReload;
#endif
}

void TESObjectWEAP::SetNoJamAfterReload(bool abVal) {
	kData.uiFlagsEx.bNoJamAfterReload = abVal;
}

// GAME - 0x66DD80
bool TESObjectWEAP::GetOverrideAP() const {
#ifdef GAME
	return ThisCall<bool>(0x66DD80, this);
#else
	return kData.uiFlagsEx.bOverrideActionPoints;
#endif
}

void TESObjectWEAP::SetOverrideAP(bool abVal) {
	kData.uiFlagsEx.bOverrideActionPoints = abVal;
}

// GAME - 0x898FD0
bool TESObjectWEAP::GetIsMinorCrime() const {
#ifdef GAME
	return ThisCall<bool>(0x898FD0, this);
#else
	return kData.uiFlagsEx.bMinorCrime;
#endif
}

void TESObjectWEAP::SetIsMinorCrime(bool abVal) {
	kData.uiFlagsEx.bMinorCrime = abVal;
}

// GAME - 0x647790
bool TESObjectWEAP::GetIsRangeFixed() const {
#ifdef GAME
	return ThisCall<bool>(0x647790, this);
#else
	return kData.uiFlagsEx.bFixedRange;
#endif
}

void TESObjectWEAP::SetIsRangeFixed(bool abVal) {
	kData.uiFlagsEx.bFixedRange = abVal;
}

// GAME - 0x646230
bool TESObjectWEAP::GetPreventUseInNormalCombat() const {
#ifdef GAME
	return ThisCall<bool>(0x646230, this);
#else
	return kData.uiFlagsEx.bNotUsedNormalCombat;
#endif
}

void TESObjectWEAP::SetPreventUseInNormalCombat(bool abVal) {
	kData.uiFlagsEx.bNotUsedNormalCombat = abVal;
}

bool TESObjectWEAP::GetOverrideDamageToWeaponMult() const {
	return kData.uiFlagsEx.bOverrideDamageToWeapon;
}

void TESObjectWEAP::SetOverrideDamageToWeaponMult(bool abVal) {
	kData.uiFlagsEx.bOverrideDamageToWeapon = abVal;
}

// GAME - 0x8B2C10
bool TESObjectWEAP::GetUse3rdPersonISAnims() const {
#ifdef GAME
	return ThisCall<bool>(0x8B2C10, this);
#else
	return !kData.uiFlagsEx.bNo3rdPersonISAnims;
#endif
}

void TESObjectWEAP::SetUse3rdPersonISAnims(bool abVal) {
	kData.uiFlagsEx.bNo3rdPersonISAnims = !abVal;
}

// GAME - 0x645C80
bool TESObjectWEAP::GetBurstShot() const {
#ifdef GAME
	return ThisCall<bool>(0x645C80, this);
#else
	return kData.uiFlagsEx.bBurstShot;
#endif
}

void TESObjectWEAP::SetBurstShot(bool abVal) {
	kData.uiFlagsEx.bBurstShot = abVal;
}

bool TESObjectWEAP::GetAlternateRumble() const {
	return kData.uiFlagsEx.bAlternateRumble;
}

void TESObjectWEAP::SetAlternateRumble(bool abVal) {
	kData.uiFlagsEx.bAlternateRumble = abVal;
}

// GAME - 0x7F5190
bool TESObjectWEAP::GetLongVATSBurst() const {
#ifdef GAME
	return ThisCall<bool>(0x7F5190, this);
#else
	return kData.uiFlagsEx.bLongVATSBurst;
#endif
}

void TESObjectWEAP::SetLongVATSBurst(bool abVal) {
	kData.uiFlagsEx.bLongVATSBurst = abVal;
}

// GAME - 0x9442C0
bool TESObjectWEAP::GetHasNightScope() const {
#ifdef GAME
	return ThisCall<bool>(0x9442C0, this);
#else
	return kData.uiFlagsEx.bHasNightScope;
#endif
}

void TESObjectWEAP::SetHasNightScope(bool abVal) {
	kData.uiFlagsEx.bHasNightScope = abVal;
}

// GAME - 0x4AD030
bool TESObjectWEAP::GetHasModScope() const {
#ifdef GAME
	return ThisCall<bool>(0x4AD030, this);
#else
	return kData.uiFlagsEx.bHasModScope;
#endif
}

void TESObjectWEAP::SetHasModScope(bool abVal) {
	kData.uiFlagsEx.bHasModScope = abVal;
}

// GAME - 0x645C20
uint16_t TESObjectWEAP::GetCriticalDamage() const {
	return kCriticalData.usCriticalDamage;
}

void TESObjectWEAP::SetCriticalDamage(uint16_t ausVal) {
	kCriticalData.usCriticalDamage = ausVal;
}

// GAME - 0x8D1EB0
float TESObjectWEAP::GetCriticalChanceMult() const {
	return kCriticalData.fCriticalChanceMult;
}

void TESObjectWEAP::SetCriticalChanceMult(float afVal) {
	kCriticalData.fCriticalChanceMult = afVal;
}

// GAME - 0x9B73B0
bool TESObjectWEAP::GetCriticalEffectOnDeath() const {
	return kCriticalData.bEffectOnDeath;
}

void TESObjectWEAP::SetCriticalEffectOnDeath(bool abVal) {
	kCriticalData.bEffectOnDeath = abVal;
}

// GAME - 0x51F4D0
SpellItem* TESObjectWEAP::GetCriticalEffect() const {
	return kCriticalData.pEffect;
}

// GAME - 0x51F4F0
void TESObjectWEAP::SetCriticalEffect(SpellItem* apEffect) {
	kCriticalData.pEffect = apEffect;
}

// GAME - 0x522D80
// GECK - 0x5FF4E0
TESModel* TESObjectWEAP::GetWorldTESModel() const {
#ifdef GAME
	return ThisCall<TESModel*>(0x522D80, this);
#else
	return ThisCall<TESModel*>(0x5FF4E0, this);
#endif
}

// GAME - 0x522DF0
// GECK - 0x5FF510
TESModel* TESObjectWEAP::GetModTESModel(uint8_t aucSlots, bool abAllowMeleeMods) const {
#ifdef GAME
	return ThisCall<TESModel*>(0x522DF0, this, aucSlots, abAllowMeleeMods);
#else
	return ThisCall<TESModel*>(0x5FF510, this, aucSlots, abAllowMeleeMods);
#endif
}

// GAME - 0x4600D0
const TESModel* TESObjectWEAP::GetShellCasingModel() const {
	return &kShellCasingModel;
}

// GAME - 0x4600D0
TESModel* TESObjectWEAP::GetShellCasingModel() {
	return &kShellCasingModel;
}

// GAME - 0x504E60
const TESModel* TESObjectWEAP::GetScopeModel() const {
	return &kScopeModel;
}

// GAME - 0x504E60
TESModel* TESObjectWEAP::GetScopeModel() {
	return &kScopeModel;
}

// GAME - 0x51F550
TESEffectShader* TESObjectWEAP::GetScopeEffect() const {
	return pScopeEffect;
}

// GAME - 0x51F570
void TESObjectWEAP::SetScopeEffect(TESEffectShader* apEffect) {
	pScopeEffect = apEffect;
}

// GAME - 0x5215A0
TESSound* TESObjectWEAP::GetAttackSound(bool abModded) const {
#ifdef GAME
	return ThisCall<TESSound*>(0x5215A0, this, abModded);
#else
	return abModded ? pAttackSoundMod : pAttackSound;
#endif
}

// GAME - 0x5215D0
void TESObjectWEAP::SetAttackSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x5215D0, this, apSound);
#else
	pAttackSound = apSound;
#endif
}

// GAME - 0x522440
TESSound* TESObjectWEAP::GetDistantAttackSound(bool abModded) const {
#ifdef GAME
	return ThisCall<TESSound*>(0x522440, this, abModded);
#else
	return abModded ? pAttackSoundDistant : pAttackSoundDistantMod;
#endif
}

// GAME - 0x5215F0
void TESObjectWEAP::SetDistantAttackSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x5215F0, this, apSound);
#else
	pAttackSoundDistant = apSound;
#endif
}

// GAME - 0x522470
TESSound* TESObjectWEAP::GetAttackSound2D(bool abModded) const {
#ifdef GAME
	return ThisCall<TESSound*>(0x522470, this, abModded);
#else
	return abModded ? pAttackSound2D : pAttackSound2DMod;
#endif
}

// GAME - 0x5C8A30
void TESObjectWEAP::SetAttackSound2D(TESSound* apSound) {
	pAttackSound2D = apSound;
}

// GAME - 0x5224C0
TESSound* TESObjectWEAP::GetAttackFailSound() const {
#ifdef GAME
	return ThisCall<TESSound*>(0x5224C0, this);
#else
	return pAttackFailSound;
#endif
}

// GAME - 0x521670
void TESObjectWEAP::SetAttackFailSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x521670, this, apSound);
#else
	pAttackFailSound = apSound;
#endif
}

// GAME - 0x5224E0
TESSound* TESObjectWEAP::GetMeleeBlockSound() const {
#ifdef GAME
	return ThisCall<TESSound*>(0x5224E0, this);
#else
	return pMeleeBlockSound;
#endif
}

// GAME - 0x521690
void TESObjectWEAP::SetMeleeBlockSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x521690, this, apSound);
#else
	pMeleeBlockSound = apSound;
#endif
}

// GAME - 0x522500
TESSound* TESObjectWEAP::GetIdleSound() const {
#ifdef GAME
	return ThisCall<TESSound*>(0x522500, this);
#else
	return pIdleSound;
#endif
}

// GAME - 0x5216B0
void TESObjectWEAP::SetIdleSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x5216B0, this, apSound);
#else
	pIdleSound = apSound;
#endif
}

// GAME - 0x522520
TESSound* TESObjectWEAP::GetEquipSound() const {
#ifdef GAME
	return ThisCall<TESSound*>(0x522520, this);
#else
	return pEquipSound;
#endif
}

// GAME - 0x5216D0
void TESObjectWEAP::SetEquipSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x5216D0, this, apSound);
#else
	pEquipSound = apSound;
#endif
}

// GAME - 0x522540
TESSound* TESObjectWEAP::GetUnequipSound() const {
#ifdef GAME
	return ThisCall<TESSound*>(0x522540, this);
#else
	return pUnequipSound;
#endif
}

// GAME - 0x5216F0
void TESObjectWEAP::SetUnequipSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x5216F0, this, apSound);
#else
	pUnequipSound = apSound;
#endif
}

// GAME - 0x521630
TESSound* TESObjectWEAP::GetModAttackSound() const {
	return pAttackSoundMod;
}

// GAME - 0x521610
void TESObjectWEAP::SetModAttackSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x521610, this, apSound);
#else
	pAttackSoundMod = apSound;
#endif
}

// GAME - 0x8D8A60
TESSound* TESObjectWEAP::GetModDistantAttackSound() const {
	return pAttackSoundDistantMod;
}

// GAME - 0x8D8A80
void TESObjectWEAP::SetModDistantAttackSound(TESSound* apSound) {
	pAttackSoundDistantMod = apSound;
}

// GAME - 0x5224A0
TESSound* TESObjectWEAP::GetModAttackSound2D() const {
	return pAttackSound2DMod;
}

// GAME - 0x8D8AA0
void TESObjectWEAP::SetModAttackSound2D(TESSound* apSound) {
	pAttackSound2DMod = apSound;
}

// GAME - 0x51F610
ANIM_GROUP_TYPE TESObjectWEAP::GetHandGripAnim() const {
	return static_cast<ANIM_GROUP_TYPE>(kData.eHandGripAnim);
}

void TESObjectWEAP::SetHandGripAnim(ANIM_GROUP_TYPE aeAnim) {
	kData.eHandGripAnim = aeAnim;
}

// GAME - 0x51F5F0
// GECK - 0x5FF490
ANIM_GROUP_TYPE TESObjectWEAP::GetAttackAnim() const {
	return static_cast<ANIM_GROUP_TYPE>(kData.eAttackAnim);
}

void TESObjectWEAP::SetAttackAnim(ANIM_GROUP_TYPE aeAnim) {
	kData.eAttackAnim = aeAnim;
}

// GAME - 0x51E2A0
ANIM_GROUP_TYPE TESObjectWEAP::GetReloadAnim(bool abModValue) const {
#ifdef GAME
	return ThisCall<ANIM_GROUP_TYPE>(0x51E2A0, this, abModValue);
#else
	uint8_t ucAnim = kData.ucReloadAnim;
	if (abModValue && kData.ucModReloadAnim != ANIM_GROUP_TYPE::NONE)
		ucAnim = kData.ucModReloadAnim;
	return static_cast<ANIM_GROUP_TYPE>(ucAnim + ANIM_GROUP_TYPE::_RELOAD_START);
#endif
}

void TESObjectWEAP::SetReloadAnim(ANIM_GROUP_TYPE aeAnim) {
	kData.ucReloadAnim = aeAnim - ANIM_GROUP_TYPE::_RELOAD_START;
	bIsLoopingReload = aeAnim >= ANIM_GROUP_TYPE::_LOOPING_RELOAD_START && aeAnim <= ANIM_GROUP_TYPE::_RELOAD_START;
}

void TESObjectWEAP::SetModReloadAnim(ANIM_GROUP_TYPE aeAnim) {
	kData.ucModReloadAnim = aeAnim - ANIM_GROUP_TYPE::_RELOAD_START;
}

// GAME - 0x8D8AC0
BGSImpactDataSet* TESObjectWEAP::GetImpactDataSet() const {
	return pImpactDataSet;
}

// GAME - 0x8D8AE0
void TESObjectWEAP::SetImpactDataSet(BGSImpactDataSet* apSet) {
	pImpactDataSet = apSet;
}

// GAME - 0x8D8B00
TESObjectSTAT* TESObjectWEAP::Get1stPersonObject() const {
	return p1stPersonObject;
}

// GAME - 0x521710
void TESObjectWEAP::Set1stPersonObject(TESObjectSTAT* apObject) {
	p1stPersonObject = apObject;
}

// GAME - 0x4AB500
TESObjectSTAT* TESObjectWEAP::Get1stPersonModObject(uint8_t aucSlots) const {
#ifdef GAME
	return ThisCall<TESObjectSTAT*>(0x4AB500, this, aucSlots);
#else
	const Bitfield8& rSlots = reinterpret_cast<Bitfield8&>(aucSlots);
	if (rSlots.Get<ModSlot::MOD_1>()) {
		if (rSlots.Get<ModSlot::MOD_2>()) {
			if (rSlots.Get<ModSlot::MOD_3>())
				return p1stPersonMod123Object;
			else
				return p1stPersonMod12Object;
		}
		else if (rSlots.Get<ModSlot::MOD_3>()) {
			return p1stPersonMod13Object;
		}
		else {
			return p1stPersonMod1Object;
		}
	}
	else if (rSlots.Get<ModSlot::MOD_2>()) {
		if (rSlots.Get<ModSlot::MOD_3>())
			return p1stPersonMod23Object;
		else
			return p1stPersonMod2Object;
	}
	else if (rSlots.Get<ModSlot::MOD_3>()) {
		return p1stPersonMod3Object;
	}
	else {
		return p1stPersonObject;
	}
#endif
}

// GAME - 0x5214D0
void TESObjectWEAP::Set1stPersonModObject(uint8_t aucSlots, TESObjectSTAT* apObject) {
#ifdef GAME
	ThisCall(0x5214D0, this, aucSlots, apObject);
#else
	const Bitfield8& rSlots = reinterpret_cast<Bitfield8&>(aucSlots);
	if (rSlots.Get<ModSlot::MOD_1>()) {
		if (rSlots.Get<ModSlot::MOD_2>()) {
			if (rSlots.Get<ModSlot::MOD_3>())
				p1stPersonMod123Object = apObject;
			else
				p1stPersonMod12Object = apObject;
		}
		else if (rSlots.Get<ModSlot::MOD_3>()) {
			p1stPersonMod13Object = apObject;
		}
		else {
			p1stPersonMod1Object = apObject;
		}
	}
	else if (rSlots.Get<ModSlot::MOD_2>()) {
		if (rSlots.Get<ModSlot::MOD_3>())
			p1stPersonMod23Object = apObject;
		else
			p1stPersonMod2Object = apObject;
	}
	else if (rSlots.Get<ModSlot::MOD_3>()) {
		p1stPersonMod3Object = apObject;
	}
#endif
}

// GAME - 0x4BD570
TESObjectIMOD* TESObjectWEAP::GetModItem(ModSlot aeSlot) const {
#ifdef GAME
	return ThisCall<TESObjectIMOD*>(0x4BD570, this, aeSlot);
#else
	switch (aeSlot) {
		case ModSlot::MOD_1:
			return pModObjects[0];
		case ModSlot::MOD_2:
			return pModObjects[1];
		case ModSlot::MOD_3:
			return pModObjects[2];
	}
	return nullptr;
#endif
}

// GAME - 0x521480
void TESObjectWEAP::SetModItem(ModSlot aeSlot, TESObjectIMOD* apMod) {
#ifdef GAME
	ThisCall(0x521480, this, aeSlot, apMod);
#else
	switch (aeSlot) {
		case ModSlot::MOD_1:
			pModObjects[0] = apMod;
			break;
		case ModSlot::MOD_2:
			pModObjects[1] = apMod;
			break;
		case ModSlot::MOD_3:
			pModObjects[2] = apMod;
			break;
	}
#endif
}

// GAME - 0x522C00
const char* TESObjectWEAP::GetEmbeddedWeaponNode() const {
#ifdef GAME
	return ThisCall<const char*>(0x522C00, this);
#else
	if (GetIsEmbeddedWeapon())
		return strEmbeddedWeaponNode.GetString();
	return nullptr;
#endif
}

void TESObjectWEAP::SetEmbeddedWeaponNode(const char* apNodeName) {
	if (GetIsEmbeddedWeapon())
		strEmbeddedWeaponNode.Set(apNodeName);
}

// GAME - 0x522560
SOUND_LEVEL TESObjectWEAP::GetSoundLevel(bool abModded) const {
#ifdef GAME
	return ThisCall<SOUND_LEVEL>(0x522560, this, abModded);
#else
	return abModded ? SOUND_LEVEL::SILENT : eSoundLevel;
#endif
}

void TESObjectWEAP::SetSoundLevel(SOUND_LEVEL aeLevel) {
	eSoundLevel = aeLevel;
}

#ifdef GAME
// GAME - 0x525620
int32_t TESObjectWEAP::GetSoundLevelValue(bool abSilent, bool abSilencer) const {
	return ThisCall<int32_t>(0x525620, this, abSilent, abSilencer);
}
#endif

// GAME - 0x51F510
SpellItem* TESObjectWEAP::GetVATSSpecialAttackEffect() const {
	return kVATSData.pEffect;
}

// GAME - 0x51F530
void TESObjectWEAP::SetVATSSpecialAttackEffect(SpellItem* apEffect) {
	kVATSData.pEffect = apEffect;
}

// GAME - 0x7EBD30
float TESObjectWEAP::GetVATSSpecialAttackSkillRequirement() const {
	return kVATSData.fSkillReq;
}

void TESObjectWEAP::SetVATSSpecialAttackSkillRequirement(float afVal) {
	kVATSData.fSkillReq = afVal;
}

// GAME - 0x7EBD10
float TESObjectWEAP::GetVATSSpecialAttackAPCost() const {
	return kVATSData.fActionPoints;
}

void TESObjectWEAP::SetVATSSpecialAttackAPCost(float afVal) {
	kVATSData.fActionPoints = afVal;
}

// GAME - 0x8D9140
float TESObjectWEAP::GetVATSSpecialAttackDamageMultiplier() const {
	return kVATSData.fDamageMult;
}

void TESObjectWEAP::SetVATSSpecialAttackDamageMultiplier(float afVal) {
	kVATSData.fDamageMult = afVal;
}

bool TESObjectWEAP::GetVATSSpecialAttackSilent() const {
	return kVATSData.bIsSilent;
}

void TESObjectWEAP::SetVATSSpecialAttackSilent(bool abVal) {
	kVATSData.bIsSilent = abVal;
}

bool TESObjectWEAP::GetVATSSpecialAttackModRequirement() const {
	return kVATSData.bModRequired;
}

void TESObjectWEAP::SetVATSSpecialAttackModRequirement(bool abVal) {
	kVATSData.bModRequired = abVal;
}

#ifdef GAME
// GAME - 0x525AE0
BGSProjectile* TESObjectWEAP::GetProjectile(ActorValueOwner* apActorValueOwner) const {
	return ThisCall<BGSProjectile*>(0x525AE0, this, apActorValueOwner);
}
#endif

// GAME - 0x525A90
// GECK - 0x600060
BGSProjectile* TESObjectWEAP::GetProjectile(Actor* apActor) const {
#ifdef GAME
	return ThisCall<BGSProjectile*>(0x525A90, this, apActor);
#else
	return ThisCall<BGSProjectile*>(0x600060, this, apActor);
#endif
}

// GAME - 0x525980
// GECK - 0x600050
TESAmmo* TESObjectWEAP::GetCurrentAmmo(Actor* apActor) const {
#ifdef GAME
	return ThisCall<TESAmmo*>(0x525980, this, apActor);
#else
	return ThisCall<TESAmmo*>(0x600050, this, apActor);
#endif
}

// GAME - 0x522C80
// GECK - 0x601670
COMBAT_WEAPON_TYPE TESObjectWEAP::GetCombatWeaponType() const {
#ifdef GAME
	return ThisCall<COMBAT_WEAPON_TYPE>(0x522C80, this);
#else
	return ThisCall<COMBAT_WEAPON_TYPE>(0x601670, this);
#endif
}

// GAME - 0x4BD9D0
float TESObjectWEAP::GetModValue(ModSlot aeSlot, uint8_t aucValue) const {
#ifdef GAME
	return ThisCall<float>(0x4BD9D0, this, aeSlot, aucValue);
#else
	for (uint32_t i = 0; i < 3; ++i) {
		if (aeSlot != 1u << i)
			continue;

		if (aucValue == 0)
			return kData.fValue1Mod[i];
		else if (aucValue == 1)
			return kData.fValue2Mod[i];
	}
	return 0.f;
#endif
}

// GAME - 0x4BCF60
float TESObjectWEAP::GetModEffectValue(WEAPON_MOD_EFFECT_TYPE aeEffect, uint8_t aucValue) const {
#ifdef GAME
	return ThisCall<float>(0x4BCF60, this, aeEffect, aucValue);
#else
	for (uint32_t i = 0; i < 3; ++i) {
		if (kData.eEffectMods[i] != aeEffect)
			continue;

		if (aucValue == 0)
			return kData.fValue1Mod[i];
		else if (aucValue == 1)
			return kData.fValue2Mod[i];
	}
	return 0.f;
#endif
}

// GAME - 0x4BE380
float TESObjectWEAP::GetWeight(bool abModded) {
#ifdef GAME
	return ThisCall<float>(0x4BE380, this, abModded);
#else
	float fWeight = GetFormWeight();
	if (abModded)
		fWeight =- GetModEffectValue(WEAPON_MOD_EFFECT_TYPE::DECREASE_WEIGHT, 0);
	return fWeight;
#endif
}

#ifdef GAME
// GAME - 0x524DB0
void TESObjectWEAP::EjectShellCasing(TESObjectREFR* apReference) {
	ThisCall(0x524DB0, this, apReference);
}
#endif