#include "NiObjectNET.hpp"

// GAME - 0xA5C570
// GECK - 0x818D30
NiTimeController* NiObjectNET::GetController(const NiRTTI* apRTTI) const {
#ifdef GAME
	return ThisCall<NiTimeController*>(0xA5C570, this, apRTTI);
#else
	return ThisCall<NiTimeController*>(0x818D30, this, apRTTI);
#endif
}

// GAME - 0xA5C480
// GECK - 0x818C40
void NiObjectNET::RemoveController(NiTimeController* apController) {
#ifdef GAME
	ThisCall(0xA5C480, this, apController);
#else
	ThisCall(0x818C40, this, apController);
#endif
}

// GAME - 0xA5BDD0
// GECK - 0x8185B0
NiExtraData* NiObjectNET::GetExtraData(const NiFixedString& arKey) const {
#ifdef GAME
	return ThisCall<NiExtraData*>(0xA5BDD0, this, &arKey);
#else
	return ThisCall<NiExtraData*>(0x8185B0, this, &arKey);
#endif
}

// GAME - 0xA5BCA0
// GECK - 0x818480
bool NiObjectNET::AddExtraData(NiExtraData* apExtraData) {
#ifdef GAME
    return ThisCall<bool>(0xA5BCA0, this, apExtraData);
#else
	return ThisCall<bool>(0x818480, this, apExtraData);
#endif
}

// GAME - 0xA5BC40
// GECK - 0x818420
bool NiObjectNET::AddExtraData(const NiFixedString& arKey, NiExtraData* apExtraData) {
#ifdef GAME
    return ThisCall<bool>(0xA5BC40, this, &arKey, apExtraData);
#else
	return ThisCall<bool>(0x818420, this, &arKey, apExtraData);
#endif
}

// GAME - 0xA5BE90
// GECK - 0x818670
bool NiObjectNET::RemoveExtraData(const NiFixedString& arKey) {
#ifdef GAME
	return ThisCall<bool>(0xA5BE90, this, &arKey);
#else
	return ThisCall<bool>(0x818670, this, &arKey);
#endif
}

// GAME - 0xA5B990
// GECK - 0x818170
void NiObjectNET::DeleteExtraData(uint16_t ausIndex) {
#ifdef GAME
    ThisCall(0xA5B990, this, ausIndex);
#else
	ThisCall(0x818170, this, ausIndex);
#endif
}

// GAME - 0xA5BFA0
void NiObjectNET::RemoveAllExtraData() {
	ThisCall(0xA5BFA0, this);
}

// GAME - 0x4AD1B0
NiObjectNET::CopyType NiObjectNET::GetDefaultCopyType() {
#ifdef GAME
    return *reinterpret_cast<CopyType*>(0x11F4300);
#else
	return *reinterpret_cast<CopyType*>(0xF1FE00);
#endif
}

// GAME - 0x4AD1C0
char NiObjectNET::GetDefaultAppendCharacter() {
#ifdef GAME
    return *reinterpret_cast<char*>(0x11A94A8);
#else
	return *reinterpret_cast<char*>(0xEB46F3);
#endif
}
