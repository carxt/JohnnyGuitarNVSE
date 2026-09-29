#include "TESAnimGroup.hpp"

// GAME - 0x5F2420
// GECK - 0x55EAB0
ANIM_GROUP_TYPE TESAnimGroup::GetType() const {
    return GetType(usType);
}

// GAME - 0x5F23A0
// GECK - 0x55EA90
ANIM_GROUP_MOVE TESAnimGroup::GetMove() const {
    return GetMove(usType);
}

// GAME - 0x5F23E0
ANIM_GROUP_WEAPON TESAnimGroup::GetWeapon() const {
    return GetWeapon(usType);
}

// GAME - 0x4937C0
bool TESAnimGroup::IsAimAction() const {
    return IsAimAction(usType);
}

bool TESAnimGroup::IsIronSightsAction() const {
    return IsIronSightsAction(usType);
}

// GAME - 0x4937E0
bool TESAnimGroup::IsAttackAction() const {
    return IsAttackAction(usType);
}

bool TESAnimGroup::IsAttackSpinAction() const {
    return IsAttackSpinAction(usType);
}

// GAME - 0x5F26C0
// GECK - 0x55E6B0
bool TESAnimGroup::IsPowerAttack() const {
#ifdef GAME
    return ThisCall<bool>(0x5F26C0, this);
#else
    return ThisCall<bool>(0x55E6B0, this);
#endif
}

bool TESAnimGroup::IsReloadAction() const {
    return IsReloadAction(usType);
}

bool TESAnimGroup::IsIdleAnim() const {
    return IsIdleAnim(usType);
}

// GAME - 0x5F4DB0
bool TESAnimGroup::IsJumpingLandAnim() const {
    return ThisCall<bool>(0x5F4DB0, this);
}

// GAME - 0x5F4D60
bool TESAnimGroup::IsJumpingLoopAnim() const {
    return ThisCall<bool>(0x5F4D60, this);
}

// GAME - 0x5F4C70
// GECK - 0x55E970
float TESAnimGroup::GetSpeed() const {
    return kSpeed.Length();
}

bool TESAnimGroup::IsMovementSequence() const {
    return GetType() >= ANIM_GROUP_TYPE::_MOVEMENT_START && GetType() <= ANIM_GROUP_TYPE::_MOVEMENT_END;
}

// GAME - 0x5F2370
// GECK - 0x55E5A0
uint16_t TESAnimGroup::AnimGroup(ANIM_GROUP_MOVE aeMove, ANIM_GROUP_WEAPON aeWeapon, ANIM_GROUP_TYPE aeGroup, bool abPowerArmor) {
    return AnimGroup_View(aeMove, aeWeapon, aeGroup, abPowerArmor).Get();
}

// GAME - 0x5F2440
// GECK - 0x55E5F0
ANIM_GROUP_TYPE TESAnimGroup::GetType(uint16_t ausGroup) {
    return AnimGroup_View(ausGroup).GetType();
}

// GAME - 0x5F23C0
// GECK - 0x55E5C0
ANIM_GROUP_MOVE TESAnimGroup::GetMove(uint16_t ausGroup) {
    return AnimGroup_View(ausGroup).GetMove();
}

// GAME - 0x5F2400
// GECK - 0x55E5D0
ANIM_GROUP_WEAPON TESAnimGroup::GetWeapon(uint16_t ausGroup) {
    return AnimGroup_View(ausGroup).GetWeapon();
}

// GAME - 0x5F2630
bool TESAnimGroup::IsAimAction(uint16_t ausGroup) {
    return CdeclCall<bool>(0x5F2630, ausGroup);
}

// GAME - 0x5F2720
// GECK - 0x55EAF0
bool TESAnimGroup::IsIronSightsAction(uint16_t ausGroup) {
#ifdef GAME
    return CdeclCall<bool>(0x5F2720, ausGroup);
#else
    return CdeclCall<bool>(0x55EAF0, ausGroup);
#endif
}

// GAME - 0x5F2750
bool TESAnimGroup::IsIronSightsAction(ANIM_GROUP_TYPE aeGroup) {
    return CdeclCall<bool>(0x5F2750, aeGroup);
}

// GAME - 0x5F2540
bool TESAnimGroup::IsAttackAction(uint16_t ausGroup) {
    return CdeclCall<bool>(0x5F2540, ausGroup);
}

// GAME - 0x5F25A0
bool TESAnimGroup::IsAttackAction(ANIM_GROUP_ACTION_TYPE aeType) {
    return CdeclCall<bool>(0x5F25A0, aeType);
}

// GAME - 0x5F25D0
bool TESAnimGroup::IsAttackSpinAction(uint16_t ausGroup) {
    return CdeclCall<bool>(0x5F25D0, ausGroup);
}

// GAME - 0x5F2610
bool TESAnimGroup::IsAttackSpinAction(ANIM_GROUP_ACTION_TYPE aeType) {
    return CdeclCall<bool>(0x5F2610, aeType);
}

// GAME - 0x5F2670
bool TESAnimGroup::IsPowerAttackAction(uint16_t ausGroup) {
    return CdeclCall<bool>(0x5F2670, ausGroup);
}

// GAME - 0x5F26B0
bool TESAnimGroup::IsPowerAttackAction(ANIM_GROUP_ACTION_TYPE aeType) {
    return CdeclCall<bool>(0x5F26B0, aeType);
}

bool TESAnimGroup::IsReloadAction(uint16_t ausGroup) {
    if (ausGroup == 255)
        return false;

    return IsReloadAction(GetType(ausGroup));
}

// GAME - 0x5F2700
bool TESAnimGroup::IsReloadAction(ANIM_GROUP_TYPE aeGroup) {
    return CdeclCall<bool>(0x5F2700, aeGroup);
}

// GAME - 0x5F4CC0
bool TESAnimGroup::IsIdleAnim(uint16_t ausGroup) {
    return CdeclCall<bool>(0x5F4CC0, ausGroup);
}