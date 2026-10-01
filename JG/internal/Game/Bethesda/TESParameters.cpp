#include "TESParameters.hpp"

// GAME - 0x682270
// GECK - 0x4A58A0
uint32_t TESParameters::GetParamCount(const FunctionData* apData) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x682270, apData);
#else
	return CdeclCall<uint32_t>(0x4A58A0, apData);
#endif
}

// GAME - 0x6822A0
// GECK - 0x4A58C0
bool TESParameters::GetParamIsTESForm(const FunctionData* apData, uint32_t auiParam) {
#ifdef GAME
	return CdeclCall<bool>(0x6822A0, apData, auiParam);
#else
	return CdeclCall<bool>(0x4A58C0, apData, auiParam);
#endif
}

// GAME - 0x682320
// GECK - 0x4A5920
bool TESParameters::GetParamIsReference(const FunctionData* apData, uint32_t auiParam) {
#ifdef GAME
	return CdeclCall<bool>(0x682320, apData, auiParam);
#else
	return CdeclCall<bool>(0x4A5920, apData, auiParam);
#endif
}

#ifdef GAME
// GAME - 0x682380
bool TESParameters::GetParamIsScriptVariable(const FunctionData* apData, uint32_t auiParam) {
	return CdeclCall<bool>(0x682380, apData, auiParam);
}
#endif

// GAME - 0x6823D0
// GECK - 0x4A5970
Script* TESParameters::GetScriptFromParam(uint32_t auiParam, const FunctionData* apData) {
#ifdef GAME
	return CdeclCall<Script*>(0x6823D0, auiParam, apData);
#else
	return CdeclCall<Script*>(0x4A5970, auiParam, apData);
#endif
}
