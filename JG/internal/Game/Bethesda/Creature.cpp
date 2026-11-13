#include "Creature.hpp"
#include "TESCreature.hpp"

TESCreature* Creature::GetActorBase() const {
	return static_cast<TESCreature*>(GetObjectReference());
}

// GAME - 0x8D46F0
float Creature::GetWeaponSkill() const {
	return ThisCall<float>(0x8D46F0, this);
}

// GAME - 0x8D4F70
float Creature::GetMovementAnimationSpeed(ANIM_GROUP_TYPE aeAnimGroup) const {
	return ThisCall<float>(0x8D4F70, this, aeAnimGroup);
}

// GAME - 0x8D4A80
ActorValue::Index Creature::MapActorValue(ActorValue::Index aeIndex) const {
	return ThisCall<ActorValue::Index>(0x8D4A80, this, aeIndex);
}
