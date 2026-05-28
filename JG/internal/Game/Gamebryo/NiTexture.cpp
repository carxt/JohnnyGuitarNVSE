#include "NiTexture.hpp"

// GAME - 0x456510
NiTexture* NiTexture::GetListHead() {
#ifdef GAME
	return *reinterpret_cast<NiTexture**>(0x11F4500);
#else
	return *reinterpret_cast<NiTexture**>(0xF1FF00);
#endif
}

NiTexture* NiTexture::GetListTail() {
#ifdef GAME
	return *reinterpret_cast<NiTexture**>(0x11F4504);
#else
	return *reinterpret_cast<NiTexture**>(0xF1FF04);
#endif
}