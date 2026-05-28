#include "NiSourceTexture.hpp"

// GAME - 0xA5FE30
// GECK - 0x811660
NiSourceTexture* NiSourceTexture::CreateTexture(NiFile* apFile, const char* apPath, const FormatPrefs& arPrefs, bool abLoadDirectToRendererHint) {
#ifdef GAME
    return CdeclCall<NiSourceTexture*>(0xA5FE30, apFile, apPath, &arPrefs, abLoadDirectToRendererHint);
#else
    return CdeclCall<NiSourceTexture*>(0x811660, apFile, apPath, &arPrefs, abLoadDirectToRendererHint);
#endif
}

// GAME - 0xA5FD70
// GECK - 0x8115A0
NiSourceTexture* NiSourceTexture::Create(const NiFixedString& arFilename, const FormatPrefs& arPrefs, bool abLoadDirectToRendererHint, bool abSrcRendererDataIsPersistent) {
#ifdef GAME
    return CdeclCall<NiSourceTexture*>(0xA5FD70, &arFilename, &arPrefs, abLoadDirectToRendererHint, abSrcRendererDataIsPersistent);
#else
	return CdeclCall<NiSourceTexture*>(0x8115A0, &arFilename, &arPrefs, abLoadDirectToRendererHint, abSrcRendererDataIsPersistent);
#endif
}