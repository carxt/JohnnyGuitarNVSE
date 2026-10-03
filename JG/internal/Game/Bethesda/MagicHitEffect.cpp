#include "MagicHitEffect.hpp"

// GAME - 0x9611E0
ActiveEffect* MagicHitEffect::GetActiveEffect() const {
    return pActiveEffect;
}

// GAME - 0x441110
TESObjectREFR* MagicHitEffect::GetTarget() const {
    return pTarget;
}

// GAME - 0x543C30
bool MagicHitEffect::GetFinished() const {
    return bFinished;
}
