#include "BSExtraData.hpp"

// GAME - 0x4F1540
EXTRA_DATA_TYPE BSExtraData::GetExtraType() const {
	return static_cast<EXTRA_DATA_TYPE>(eType);
}

// GAME - 0x44DDC0
BSExtraData* BSExtraData::GetNext() const {
	return pNext;
}
