#include "BGSTextureSet.hpp"

// GAME - 0x56A860
bool BGSTextureSet::HasDecalData() const {
    return pDecalData != nullptr;
}

// GAME - 0x56A880
DecalData* BGSTextureSet::GetDecalData() const {
    return ThisCall<DecalData*>(0x56A880, this);
}

// GAME - 0x592CF0
BSTextureSet* BGSTextureSet::GetAsShaderTextureSet() {
    return static_cast<BSTextureSet*>(this);
}

// GAME - 0x592D20
BSShaderTextureSet* BGSTextureSet::CreateShaderTextureSet() const {
    return ThisCall<BSShaderTextureSet*>(0x592D20, this);
}

// GAME - 0x593220
BGSTextureSet* BGSTextureSet::GetNullTextureSet() {
    return pNullTextureSet;
}
