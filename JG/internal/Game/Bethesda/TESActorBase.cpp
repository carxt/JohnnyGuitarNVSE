#include "TESActorBase.hpp"

// GAME - 0x5F0CC0
// GECK - 0x55D9E0
SEX TESActorBase::GetSex() const {
#ifdef GAME
    return ThisCall<SEX>(0x5F0CC0, this);
#else
    return ThisCall<SEX>(0x55D9E0, this);
#endif
}

// GAME - 0x5F0B00
// GECK - 0x55D950
int32_t TESActorBase::GetHealth() const {
#ifdef GAME
    return ThisCall<int32_t>(0x5F0B00, this);
#else
    return ThisCall<int32_t>(0x55D950, this);
#endif
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
