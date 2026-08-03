#include "NiAdditionalGeometryData.hpp"

// GAME - 0xBA63E0
// GECK - 0x67E290
NiAdditionalGeometryData* NiAdditionalGeometryData::Create(uint16_t ausVertCount, uint32_t auiObjectCount) {
#ifdef GAME
    return NiCreate<NiAdditionalGeometryData, 0xBA63E0>(ausVertCount, auiObjectCount);
#else
	return NiCreate<NiAdditionalGeometryData, 0x67E290>(ausVertCount, auiObjectCount);
#endif
}

// GAME - 0x537BF0
// GECK - 0x729EE0
NiAdditionalGeometryData* NiAdditionalGeometryData::Create(uint16_t ausVertCount) {
#ifdef GAME
	return NiCreate<NiAdditionalGeometryData, 0x537BF0>(ausVertCount);
#else
	return NiCreate<NiAdditionalGeometryData, 0x729EE0>(ausVertCount);
#endif
}

// GAME - 0xA72BB0
// GECK - 0x82B030
bool NiAdditionalGeometryData::SetDataBlock(uint32_t auiIndex, uint8_t* apData, uint32_t auiTotalSize, bool abCopyData) {
#ifdef GAME
    return ThisCall<bool>(0xA72BB0, this, auiIndex, apData, auiTotalSize, abCopyData);
#else
	return ThisCall<bool>(0x82B030, this, auiIndex, apData, auiTotalSize, abCopyData);
#endif
}

// GAME - 0xA72CA0
// GECK - 0x82B120
void NiAdditionalGeometryData::SetDataBlockCount(uint32_t auiCount) {
#ifdef GAME
    ThisCall(0xA72CA0, this, auiCount);
#else
    ThisCall(0x82B120, this, auiCount);
#endif
}

// GAME - 0xA730E0
// GECK - 0x82B560
void NiAdditionalGeometryData::SetDataStreamCount(uint32_t auiCount) {
#ifdef GAME
    ThisCall(0xA730E0, this, auiCount);
#else
    ThisCall(0x82B560, this, auiCount);
#endif
}

// GAME - 0xA72720
// GECK - 0x82ABA0
bool NiAdditionalGeometryData::GetDataStream(uint32_t auiStreamIndex, uint8_t*& apData, uint32_t& arType, uint16_t& arCount, uint32_t& arTotalSize, uint32_t& arUnitSize, uint32_t& arStride) const {
#ifdef GAME
    return ThisCall<bool>(0xA72720, this, auiStreamIndex, &apData, &arType, &arCount, &arTotalSize, &arUnitSize, &arStride);
#else
    return ThisCall<bool>(0x82ABA0, this, auiStreamIndex, &apData, &arType, &arCount, &arTotalSize, &arUnitSize, &arStride);
#endif
}

// GAME - 0xA726A0
// GECK - 0x82AB20
bool NiAdditionalGeometryData::SetDataStream(uint32_t auiStreamIndex, uint32_t auiBlockIndex, uint32_t auiBlockOffset, Types auiType, uint16_t ausCount, uint32_t auiUnitSize, uint32_t auiStride) {
#ifdef GAME
    return ThisCall<bool>(0xA726A0, this, auiStreamIndex, auiBlockIndex, auiBlockOffset, auiType, ausCount, auiUnitSize, auiStride);
#else
    return ThisCall<bool>(0x82AB20, this, auiStreamIndex, auiBlockIndex, auiBlockOffset, auiType, ausCount, auiUnitSize, auiStride);
#endif
}