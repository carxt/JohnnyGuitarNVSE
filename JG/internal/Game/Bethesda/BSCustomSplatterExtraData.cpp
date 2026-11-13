#include "BSCustomSplatterExtraData.hpp"

BSCustomSplatterExtraData* BSCustomSplatterExtraData::Create(BSSplatterData& arData) {
    return NiCreate<BSCustomSplatterExtraData, 0x4DEA80>(&arData);
}

// GAME - 0x4DE890
const NiFixedString& BSCustomSplatterExtraData::GetTag() {
    return *pTag;
}