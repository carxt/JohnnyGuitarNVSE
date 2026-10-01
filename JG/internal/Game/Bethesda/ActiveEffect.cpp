#include "ActiveEffect.hpp"

// GAME - 0x6B9130
float ActiveEffect::GetElapsedTime() const {
	return fElapsedTime;
}

// GAME - 0x4F5D90
void ActiveEffect::SetElapsedTime(float afTime) {
	fElapsedTime = afTime;
}

// GAME - 0x44DDC0
MagicItem* ActiveEffect::GetSpell() const {
	return pSpell;
}

// GAME - 0x84E3A0
EffectItem* ActiveEffect::GetEffectItem() const {
	return pEffect;
}

// GAME - 0x833C20
bool ActiveEffect::IsActive() const {
	return bActive;
}

// GAME - 0x824060
bool ActiveEffect::IsStarted() const {
	return bStarted;
}

// GAME - 0x705CF0
bool ActiveEffect::IsDone() const {
	return bDone;
}

// GAME - 0x495460
float ActiveEffect::GetMagnitude() const {
	return fMagnitude;
}

// GAME - 0x804CB0
void ActiveEffect::SetMagnitude(float afMagnitude) {
	fMagnitude = afMagnitude;
}

// GAME - 0x7DF1F0
float ActiveEffect::GetDuration() const {
	return fDuration;
}

// GAME - 0x693D50
void ActiveEffect::SetDuration(float afDuration) {
	fDuration = afDuration;
}

// GAME - 0x59BB30
MagicTarget* ActiveEffect::GetTarget() const {
	return pTarget;
}

// GAME - 0x45CD60
MagicCaster* ActiveEffect::GetCaster() const {
	return pCaster;
}

// GAME - 0x55B980
MagicSystem::SpellType ActiveEffect::GetSpellType() const {
	return eSpellType;
}

// GAME - 0x639B40
TESBoundObject* ActiveEffect::GetEnchantmentSource() const {
	return pSource;
}

// GAME - 0x8041A0
MagicItem* ActiveEffect::GetDisplacementSpell() const {
	return pDisplacementSpell;
}

// GAME - 0x7DF1D0
EffectSetting* ActiveEffect::GetEffectSetting() const {
	return ThisCall<EffectSetting*>(0x7DF1D0, this);
}

// GAME - 0x804210
void ActiveEffect::Dispel(bool abImmediate) {
	ThisCall(0x804210, this, abImmediate);
}
