#include "TESObjectANIO.hpp"

TESIdleForm* TESObjectANIO::GetIdleAnim() const {
    return pIdleAnim;
}

void TESObjectANIO::SetIdleAnim(TESIdleForm* apIdle) {
    pIdleAnim = apIdle;
}

// GAME - 0x46FDD0
bool TESObjectANIO::GetUsesIdle(TESIdleForm* apIdle) const {
#ifdef GAME
    return ThisCall<bool>(0x46FDD0, this, apIdle);
#else
    return pIdleAnim == apIdle;
#endif
}
