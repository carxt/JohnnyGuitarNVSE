#include "NiDefaultAVObjectPalette.hpp"

// GAME - 0xA2ED80
// GECK - 0x7DE050
NiDefaultAVObjectPalette* NiDefaultAVObjectPalette::Create(NiAVObject* apScene, uint32_t auiSize) {
#ifdef GAME
	return NiCreate<NiDefaultAVObjectPalette, 0xA2ED80>(apScene, auiSize);
#else
	return NiCreate<NiDefaultAVObjectPalette, 0x7DE050>(apScene, auiSize);
#endif
}

// GAME - 0xA6E960
// GECK - 0x828F90
void NiDefaultAVObjectPalette::ResetAndFillFromScenegraph() {
#ifdef GAME
	ThisCall(0xA6E960, this);
#else
	ThisCall(0x828F90, this);
#endif
}
