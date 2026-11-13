#include "Clouds.hpp"

// GAME - 0x63A610
void Clouds::ForceTransTextureUpdate() {
	bForceTransTextureUpdate = true;
}

// GAME - 0x634930
// GECK - 0x67C1C0
void Clouds::ClearTransTextures() {
#ifdef GAME
	ThisCall(0x634930, this);
#else
	ThisCall(0x67C1C0, this);
#endif
}

// GAME - 0x6349E0
// GECK - 0x67CAC0
void Clouds::RemoveTextures() {
#ifdef GAME
	ThisCall(0x6349E0, this);
#else
	ThisCall(0x67CAC0, this);
#endif
}