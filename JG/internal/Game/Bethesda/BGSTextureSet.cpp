#include "BGSTextureSet.hpp"

const TESTexture* BGSTextureSet::GetTESTexture(TextureType aeTexture) const {
    if (aeTexture < TextureType::COUNT)
        return &kTextures[aeTexture];
    return nullptr;
}

// GAME - 0x592CC0
// GECK - 0x5B0B10
void BGSTextureSet::SetBGSTextureFilename(TextureType aeTexture, const char* apName) {
#ifdef GAME
    ThisCall(0x592CC0, this, aeTexture, apName);
#else
    ThisCall(0x5B0B10, this, aeTexture, apName);
#endif
}

// GAME - 0x56A860
bool BGSTextureSet::HasDecalData() const {
    return pDecalData != nullptr;
}

// GAME - 0x56A880
DecalData* BGSTextureSet::GetDecalData() const {
#ifdef GAME
    return ThisCall<DecalData*>(0x56A880, this);
#else
    return pDecalData ? pDecalData : DecalData::GetDefaultDecalData();
#endif
}

// GAME - 0x592CF0
BSTextureSet* BGSTextureSet::GetAsShaderTextureSet() {
    return static_cast<BSTextureSet*>(this);
}

// GAME - 0x592D20
// GECK - 0x5B0ED0
BSShaderTextureSet* BGSTextureSet::CreateShaderTextureSet() const {
#ifdef GAME
    return ThisCall<BSShaderTextureSet*>(0x592D20, this);
#else
    return ThisCall<BSShaderTextureSet*>(0x5B0ED0, this);
#endif
}

// GAME - 0x593220
// GECK - 0x5B00A0
BGSTextureSet* BGSTextureSet::GetNullTextureSet() {
#ifdef GAME
    return CdeclCall<BGSTextureSet*>(0x593220);
#else
    return CdeclCall<BGSTextureSet*>(0x5B00A0);
#endif
}
