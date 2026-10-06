#include "TESObjectANIO.hpp"
#ifdef GAME
#include "TESIdleForm.hpp"
#endif

TESIdleForm* TESObjectANIO::GetIdleAnim() const {
    return pIdleAnim;
}

void TESObjectANIO::SetIdleAnim(TESIdleForm* apIdle) {
    pIdleAnim = apIdle;
}

// GECK - 0x5F3B80
const char* TESObjectANIO::GetIdleAnimEditorID() const {
#ifdef GAME
    return pIdleAnim ? pIdleAnim->GetFormEditorID() : "";
#else
    return ThisCall<const char*>(0x5F3B80, this);
#endif
}

// GAME - 0x46FDD0
bool TESObjectANIO::GetUsesIdle(TESIdleForm* apIdle) const {
#ifdef GAME
    return ThisCall<bool>(0x46FDD0, this, apIdle);
#else
    return pIdleAnim == apIdle;
#endif
}
