#include "ProcessArray.hpp"

// GAME - 0x968670
MobileObject* ProcessArray::GetItem(uint32_t auiIndex) const {
	return kMobileObjects.GetAt(auiIndex);
}

// GAME - 0x5DE0F0
uint32_t ProcessArray::GetHead(PROCESS_LEVEL aeLevel) const {
	return uiHeads[aeLevel];
}

// GAME - 0x5BE5C0
uint32_t ProcessArray::GetTail(PROCESS_LEVEL aeLevel) const {
	return uiTails[aeLevel];
}

// GAME - 0x55B980
uint32_t ProcessArray::GetSize() const {
	return uiTails[PROCESS_LEVEL::LOW];
}

// GAME - 0x96AB20
PROCESS_LEVEL ProcessArray::GetProcessLevelFromIndex(uint32_t auiIndex) const {
	return ThisCall<PROCESS_LEVEL>(0x96AB20, this, auiIndex);
}

// GAME - 0x96ABC0
uint32_t ProcessArray::GetIndexFromObject(MobileObject* apObject, PROCESS_LEVEL aeLevel) const {
	return ThisCall<uint32_t>(0x96ABC0, this, apObject, aeLevel);
}