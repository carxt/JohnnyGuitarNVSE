#include "BSStream.hpp"

// GAME - 0x43CFD0
// GECK - 0x43EAE0
BSStream* BSStream::Create(BSStream* apThis) {
#ifdef GAME
    return ThisCall<BSStream*>(0x43CFD0, apThis);
#else
    return ThisCall<BSStream*>(0x43EAE0, apThis);
#endif
}
