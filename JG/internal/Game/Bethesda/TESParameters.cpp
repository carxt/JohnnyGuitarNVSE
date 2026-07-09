#include "TESParameters.hpp"

// GAME - 0x682270
uint32_t TESParameters::GetParamCount(const FunctionData* apData) {
	return CdeclCall<uint32_t>(0x682270, apData);
}

// GAME - 0x6822A0
bool TESParameters::GetParamIsTESForm(const FunctionData* apData, uint32_t auiParam) {
	return CdeclCall<bool>(0x6822A0, apData, auiParam);
}

// GAME - 0x682320
bool TESParameters::GetParamIsReference(const FunctionData* apData, uint32_t auiParam) {
	return CdeclCall<bool>(0x682320, apData, auiParam);
}

// GAME - 0x682380
bool TESParameters::GetParamIsScriptVariable(const FunctionData* apData, uint32_t auiParam) {
	return CdeclCall<bool>(0x682380, apData, auiParam);
}

// GAME - 0x6823D0
Script* TESParameters::GetScriptFromParam(uint32_t auiParam, const FunctionData* apData) {
	return CdeclCall<Script*>(0x6823D0, auiParam, apData);
}
