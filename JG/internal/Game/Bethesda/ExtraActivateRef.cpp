#include "ExtraActivateRef.hpp"

// GAME - 0x433A00
// GECK - 0x4B6E10
RefActivateData* ExtraActivateRef::GetData(TESObjectREFR* apRef) const {
#ifdef GAME
    return ThisCall<RefActivateData*>(0x433A00, this, apRef);
#else
    return ThisCall<RefActivateData*>(0x4B6E10, this, apRef);
#endif
}