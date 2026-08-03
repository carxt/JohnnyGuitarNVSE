#include "TESActorBase.hpp"

// GAME - 0x5F0CC0
// GECK - 0x55D9E0
SEX TESActorBase::GetSex() const {
    if (GetFormType() == FORM_TYPE::TESNPC)
        return SEX(IsFemale());

    return SEX::NONE;
}

// GAME - 0x5F0B00
// GECK - 0x55D950
int32_t TESActorBase::GetHealth() const {
    return GetFormHealth();
}

// GAME - 0x5F0D60
// GECK - 0x55DA40
float TESActorBase::GetDesirability(TESForm* apForm) const {
#ifdef GAME
    return ThisCall<float>(0x5F0D60, this, apForm);
#else
    return ThisCall<float>(0x55DA40, this, apForm);
#endif
}
