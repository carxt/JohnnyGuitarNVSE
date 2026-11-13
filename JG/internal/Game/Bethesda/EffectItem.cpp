#include "EffectItem.hpp"
#include "EffectSetting.hpp"

// GAME - 0x404390
// GECK - 0x66CD80
int32_t EffectItem::GetMagnitude() const {
#ifdef GAME
	return ThisCall<int32_t>(0x404390, this);
#else
	return ThisCall<int32_t>(0x66CD80, this);
#endif
}

// GAME - 0x4043D0
bool EffectItem::SetMagnitude(int32_t aiMagnitude) {
#ifdef GAME
	return ThisCall<bool>(0x4043D0, this, aiMagnitude);
#else
	if (!pEffectSetting->GetFlag(EffectSetting::EffectFlags::NO_MAGNITUDE) && aiMagnitude >= 0) {
		kData.iMagnitude = aiMagnitude;
		fRawCost = -1.f;
		return true;
	}
	return false;
#endif
}

// GAME - 0x404420
// GECK - 0x66CDA0
int32_t EffectItem::GetArea() const {
#ifdef GAME
	return ThisCall<int32_t>(0x404420, this);
#else
	return ThisCall<int32_t>(0x66CDA0, this);
#endif
}

// GAME - 0x404470
bool EffectItem::SetArea(int32_t aiArea) {
#ifdef GAME
	return ThisCall<bool>(0x404470, this, aiArea);
#else
	if (!pEffectSetting->GetFlag(EffectSetting::EffectFlags::NO_AREA) && aiArea >= 0) {
		kData.iArea = aiArea;
		fRawCost = -1.f;
		return true;
	}
	return false;
#endif
}

// GAME - 0x4044D0
// GECK - 0x66CDC0
int32_t EffectItem::GetDuration() const {
#ifdef GAME
	return ThisCall<int32_t>(0x4044D0, this);
#else
	return ThisCall<int32_t>(0x66CDC0, this);
#endif
}

// GAME - 0x404510
bool EffectItem::SetDuration(int32_t aiDuration) {
#ifdef GAME
	return ThisCall<bool>(0x404510, this, aiDuration);
#else
	if (!pEffectSetting->GetFlag(EffectSetting::EffectFlags::NO_DURATION) && aiDuration >= 0) {
		kData.iArea = aiDuration;
		fRawCost = -1.f;
		return true;
	}
	return false;
#endif
}

// GAME - 0x84E3A0
MagicSystem::Range EffectItem::GetRange() const {
	return kData.eRange;
}

// GAME - 0x404560
// GECK - 0x66CDE0
bool EffectItem::SetRange(MagicSystem::Range aeRange) {
#ifdef GAME
	return ThisCall<bool>(0x404560, this, aeRange);
#else
	return ThisCall<bool>(0x66CDE0, this, aeRange);
#endif
}

// GAME - 0x403EA0
// GECK - 0x65B820
ActorValue::Index EffectItem::GetActorValueIndex() const {
#ifdef GAME
	return ThisCall<ActorValue::Index>(0x403EA0, this);
#else
	return ThisCall<ActorValue::Index>(0x65B820, this);
#endif
}

// GAME - 0x437730
void EffectItem::SetActorValueIndex(ActorValue::Index aeIndex) {
	kData.eActorValue = aeIndex;
}

// GAME - 0x825C00
EffectSetting* EffectItem::GetEffectSetting() const {
	return pEffectSetting;
}

// GAME - 0x403F80
// GECK - 0x66D460
float EffectItem::GetCost() {
#ifdef GAME
	return ThisCall<float>(0x403F80, this);
#else
	return ThisCall<float>(0x66D460, this);
#endif
}

// GAME - 0x403F00
// GECK - 0x66D3D0
float EffectItem::GetRawCost() {
#ifdef GAME
	return ThisCall<float>(0x403F00, this);
#else
	return ThisCall<float>(0x66D3D0, this);
#endif
}

// GAME - 0x409140
const TESCondition* EffectItem::GetConditions() const {
	return &kConditions;
}

// GAME - 0x409140
TESCondition* EffectItem::GetConditions() {
	return &kConditions;
}

// GAME - 0x404650
// GECK - 0x66CBB0
ActorValue::Index EffectItem::GetAssociatedSkill() const {
#ifdef GAME
	return ThisCall<ActorValue::Index>(0x404650, this);
#else
	return ThisCall<ActorValue::Index>(0x66CBB0, this);
#endif
}

// GAME - 0x404670
// GECK - 0x66D8C0
BSString EffectItem::GetEffectName() const {
#ifdef GAME
	return ThisCall<BSString>(0x404670, this);
#else
	return ThisCall<BSString>(0x66D8C0, this);
#endif
}
