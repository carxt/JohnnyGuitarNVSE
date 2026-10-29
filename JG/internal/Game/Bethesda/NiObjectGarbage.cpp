#include "NiObjectGarbage.hpp"

// GAME - 0xC45830
void NiObjectGarbage::Add(NiRefObject* apObject) {
	CdeclCall(0xC45830, apObject);
}

// GAME - 0xC45AB0
bool NiObjectGarbage::IsEmpty() {
	return CdeclCall<bool>(0xC45AB0);
}

// GAME - 0xC45AD0
uint32_t NiObjectGarbage::GetCount() {
	return CdeclCall<uint32_t>(0xC45AD0);
}

// GAME - 0xC459D0
void NiObjectGarbage::ClearAll(bool abTryLock) {
	CdeclCall(0xC459D0, abTryLock);
}
