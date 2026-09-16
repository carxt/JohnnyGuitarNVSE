#include "SkyTextureManager.hpp"

// GAME - 0x63FB70
// GECK - 0x683B70
void SkyTextureManager::LoadTextureInBackground(NiPointer<NiTexture>& arTexture, const char* apTexturePath) {
#ifdef GAME
	CdeclCall(0x63FB70, &arTexture, apTexturePath);
#else
	CdeclCall(0x683B70, &arTexture, apTexturePath);
#endif
}
