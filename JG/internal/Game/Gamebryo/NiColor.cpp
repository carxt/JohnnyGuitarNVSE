#include "NiColor.hpp"

const NiColor NiColor::WHITE = NiColor(1,1,1);
const NiColor NiColor::RED = NiColor(1, 0, 0);
const NiColor NiColor::GREEN = NiColor(0, 1, 0);
const NiColor NiColor::BLUE = NiColor(0, 0, 1);
const NiColor NiColor::CYAN = NiColor(0, 1, 1);
const NiColor NiColor::MAGENTA = NiColor(1, 0, 1);
const NiColor NiColor::YELLOW = NiColor(1, 1, 0);
const NiColor NiColor::BLACK = NiColor(0, 0, 0);

// GAME - 0xA696C0
// GECK - 0x80F4C0
const char* NiColor::GetViewerStrings(const char* apText) {
#ifdef GAME
    return ThisCall<const char*>(0xA696C0, this, apText);
#else
	return ThisCall<const char*>(0x80F4C0, this, apText);
#endif
}
