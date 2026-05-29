#include "EffectItem.hpp"

// GAME - 0x404390
int32_t EffectItem::GetMagnitude() const {
	return ThisCall<int32_t>(0x404390, this);
}

// GAME - 0x4043D0
bool EffectItem::SetMagnitude(int32_t aiMagnitude) {
	return ThisCall<bool>(0x4043D0, this, aiMagnitude);
}

// GAME - 0x404420
int32_t EffectItem::GetArea() const {
	return ThisCall<int32_t>(0x404420, this);
}

// GAME - 0x404470
bool EffectItem::SetArea(int32_t aiArea) {
	return ThisCall<bool>(0x404470, this, aiArea);
}

// GAME - 0x4044D0
int32_t EffectItem::GetDuration() const {
	return ThisCall<int32_t>(0x4044D0, this);
}

// GAME - 0x404510
bool EffectItem::SetDuration(int32_t aiDuration) {
	return ThisCall<bool>(0x404510, this, aiDuration);
}

// GAME - 0x84E3A0
MagicSystem::Range EffectItem::GetRange() const {
	return kData.eRange;
}

// GAME - 0x404560
bool EffectItem::SetRange(MagicSystem::Range aeRange) {
	return ThisCall<bool>(0x404560, this, aeRange);
}

// GAME - 0x403EA0
ActorValue::Index EffectItem::GetActorValueIndex() const {
	return ThisCall<ActorValue::Index>(0x403EA0, this);
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
float EffectItem::GetCost() {
	return ThisCall<float>(0x403F80, this);
}

// GAME - 0x403F00
float EffectItem::GetRawCost() {
	return ThisCall<float>(0x403F00, this);
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
ActorValue::Index EffectItem::GetAssociatedSkill() const {
	return ThisCall<ActorValue::Index>(0x404650, this);
}

// GAME - 0x404670
BSString EffectItem::GetEffectName() const {
	return ThisCall<BSString>(0x404670, this);
}
