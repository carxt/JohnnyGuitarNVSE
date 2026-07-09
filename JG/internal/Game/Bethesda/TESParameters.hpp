#pragma once

class Script;

struct FunctionData {
	union Parameter {
		float		fValue;
		uint32_t	uiNumber;
		void* pPointer;
	};

	uint16_t	usFunction;
	Parameter	uParam[2];
};

ASSERT_SIZE(FunctionData, 0xC);

class TESParameters {
public:
	static uint32_t GetParamCount(const FunctionData* apData);
	static bool		GetParamIsTESForm(const FunctionData* apData, uint32_t auiParam);
	static bool		GetParamIsReference(const FunctionData* apData, uint32_t auiParam);
	static bool		GetParamIsScriptVariable(const FunctionData* apData, uint32_t auiParam);
	static Script*	GetScriptFromParam(uint32_t auiParam, const FunctionData* apData);
};