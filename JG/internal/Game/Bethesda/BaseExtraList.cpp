#include "BaseExtraList.hpp"

// GAME - 0x40FE80
bool BaseExtraList::HasExtra(uint8_t aucType) const {
#if JIP_CHANGES
	constexpr uint32_t ARRAY_SIZE = 19;
#else
	constexpr uint32_t ARRAY_SIZE = 21;
#endif

	uint32_t uiIndex = aucType >> 3;
	return uiIndex < ARRAY_SIZE && ucPresenceBitfield[uiIndex].GetBit(aucType & 7);
}

// GAME - 0x410220
// GECK - 0x4A9410
BSExtraData* BaseExtraList::GetExtraData(uint8_t aucType) const {
#ifdef GAME
	return ThisCall<BSExtraData*>(0x410220, this, aucType);
#else
	return ThisCall<BSExtraData*>(0x4A9410, this, aucType);
#endif
}

// GAME - 0x410020
// GECK - 0x4AC250
void BaseExtraList::RemoveExtra(BSExtraData* apExtra, bool abDelete) {
#ifdef GAME
	ThisCall(0x410020, this, apExtra, abDelete);
#else
	ThisCall(0x4AC250, this, apExtra, abDelete);
#endif
}

// GAME - 0x410140
// GECK - 0x4A9340
void BaseExtraList::RemoveExtra(uint8_t aucType) {
#ifdef GAME
	ThisCall(0x410140, this, aucType);
#else
	ThisCall(0x4A9340, this, aucType);
#endif
}

// GAME - 0x40FF60
// GECK - 0x4A9270
BSExtraData* BaseExtraList::AddExtra(BSExtraData* apExtra) {
#ifdef GAME
	return ThisCall<BSExtraData*>(0x40FF60, this, apExtra);
#else
	return ThisCall<BSExtraData*>(0x4A9270, this, apExtra);
#endif
}

// GAME - 0x40FAE0
// GECK - 0x4A91B0
void BaseExtraList::RemoveAll(bool abDelete) {
#ifdef GAME
	ThisCall(0x40FAE0, this, abDelete);
#else
	ThisCall(0x4A91B0, this, abDelete);
#endif
}

// GAME - 0x40FCB0
void BaseExtraList::RemoveAllDefault(bool abDelete) {
#ifdef GAME
	ThisCall(0x40FCB0, this, abDelete);
#else
	FUNCTION_UNKOWN
#endif
}
