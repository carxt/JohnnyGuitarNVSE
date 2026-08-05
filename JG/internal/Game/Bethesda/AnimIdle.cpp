#include "AnimIdle.hpp"

// GAME - 0x84E3A0
ANIM_IDLE_PLAY_TYPE AnimIdle::GetType() const {
    return ePlayType;
}

// GAME - 0x6FA820
KFModel* AnimIdle::GetKFModel() const {
    return spKFModel;
}

// GAME - 0x825C00
ANIM_GROUP_SECTION AnimIdle::GetSection() const {
    return eGroupSection;
}

// GAME - 0x490E40
BSAnimGroupSequence* AnimIdle::GetSequence() const {
    return spSequence;
}

// GAME - 0x43E750
TESObjectANIO* AnimIdle::GetAnimObject(uint32_t auiIndex) const {
    return pAnimObjects[auiIndex];
}

// GAME - 0x55B980
TESIdleForm* AnimIdle::GetIdleForm() const {
    return pIdleForm;
}