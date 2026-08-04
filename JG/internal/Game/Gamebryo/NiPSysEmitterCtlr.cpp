#include "NiPSysEmitterCtlr.hpp"

// GAME - 0x639B60
NiFloatInterpolator* NiPSysEmitterCtlr::GetBirthRateInterpolator() const {
    return ThisCall<NiFloatInterpolator*>(0x639B60, this);
}
