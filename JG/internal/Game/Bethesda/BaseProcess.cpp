#include "BaseProcess.hpp"

// GAME - 0x45CD60
PROCESS_TYPE BaseProcess::GetProcessLevel() const {
	return static_cast<PROCESS_TYPE>(eProcessLevel);
}

// GAME - 0x8ACED0
bool BaseProcess::GetCachedFlag(uint32_t auiFlag) const {
	return ThisCall<bool>(0x8ACED0, this, auiFlag);
}

// GAME - 0x8ACFA0
void BaseProcess::SetCachedFlag(uint32_t auiFlag, bool abSet) {
	ThisCall(0x8ACFA0, this, auiFlag, abSet);
}

void BaseProcess::GetLastProcessedDate(uint32_t& arDay, uint32_t& arMonth, uint32_t& arYear) const {
	arYear	= uiDateLastProcessed >> 13;
	arMonth = uiDateLastProcessed >> 9 & 0xF;
	arDay	= uiDateLastProcessed & 0xFF;
}
