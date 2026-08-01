#pragma once

#include "TESForm.hpp"
#include "BSStringT.hpp"

class ExtraDataList;
class ScriptLocals;
class ScriptVariable;
class TESQuest;
struct SCRIPT_REFERENCED_OBJECT;
class ScriptCompiler;
class ScriptCompileData;
struct ScriptOperator;

struct SCRIPT_HEADER {
	uint32_t	uiVariableCount;
	uint32_t	uiReferenceCount;
	uint32_t	uiDataSize;
	uint32_t	uiLastVariableID;
	bool		bIsQuestScript;
	bool		bIsMagicEffectScript;
	bool		bIsCompiled;
};

class Script : public TESForm {
public:
	Script();
	~Script();

	SCRIPT_HEADER								kHeader;
	char*										pText;
	uint8_t*									pData;
	float										fProfilerTimer;
	float										fQuestScriptDelay;
	float										fQuestScriptGetSecondsBuffer;
	TESQuest*									pQuest;
	BSSimpleList<SCRIPT_REFERENCED_OBJECT*>		kReferences;
	BSSimpleList<ScriptVariable*>				kVariables;

	TESFORM_TYPE(Script);

#ifdef GAME
	static constexpr AddressPtr<bool, 0x118C685> bIsScriptProcessing;
#endif

	const SCRIPT_HEADER* GetHeader() const;
	SCRIPT_HEADER* GetHeader();

	bool GetIsCompiled() const;

	char* GetText() const;

	float GetProfilerTimer() const;

	float GetQuestScriptGetSecondsBuffer() const;

	BSSimpleList<ScriptVariable*>* GetVariableList();

	BSSimpleList<SCRIPT_REFERENCED_OBJECT*>* GetReferencedObjectList();

	bool IsUserDefinedFunction() const;

	ScriptLocals* CreateLocalsList();

	void Init(ScriptCompileData* apData);

	void CompileAndRun(ScriptCompiler* apCompiler, SCRIPT_COMPILER_NAME aeCompilerName, TESObjectREFR* apOwnerRef);

	bool Run(TESObjectREFR* apOwner, ScriptLocals* apLocals, TESObjectREFR* apOwnerContainer, bool abIsPartialScript);

	static bool SetActionFlag(TESForm* apForm, ExtraDataList* apList, uint32_t aeEvent);
};

ASSERT_SIZE(Script, 0x54);

struct SCRIPT_LOCAL {
	uint32_t				uiVarID;
	SCRIPT_LOCAL*			pNext;
	union {
		double				dValue;
		uint32_t			uiFormID;
	};
	SCRIPT_VARIABLE_TYPE	eType; // Originally bool bIsInteger
};

ASSERT_SIZE(SCRIPT_LOCAL, 0x18);

struct ACTION_OBJECT {
	TESForm*		pForm;
	Bitfield32		uiFlags;
};

ASSERT_SIZE(ACTION_OBJECT, 0x8);

struct SCRIPT_EFFECT_DATA {
	bool	bScriptEffectStart;
	bool	bScriptEffectFinish;
	float	fSecondsElapsed;
};

ASSERT_SIZE(SCRIPT_EFFECT_DATA, 0x8);

struct SCRIPT_REFERENCED_OBJECT {
	BSString	strEditorID;
	TESForm*	pForm;
	uint32_t	uiVarID;
};

ASSERT_SIZE(SCRIPT_REFERENCED_OBJECT, 0x10);

class ScriptVariable {
public:
	SCRIPT_LOCAL	kData;
	BSString		strName;
};

ASSERT_SIZE(ScriptVariable, 0x20);

struct SCRIPT_LINE {
	uint32_t	uiLineNumber;
	char		cLine[512];
	uint32_t	uiSize;
	uint32_t	uiOffset;
	char		cOutput[512];
	uint32_t	uiOutputSize;
	uint32_t	uiOPCode;
	uint32_t	uiRefObjectIndex;
	uint32_t	eScriptError;
};

ASSERT_SIZE(SCRIPT_LINE, 0x41C);


struct SCRIPT_PARAMETER {
	const char* pParamName;
	uint32_t	eParamType;
	bool		bIsOptional;
};

ASSERT_SIZE(SCRIPT_PARAMETER, 0xC);
#if 1
#define COMMAND_ARGS		SCRIPT_PARAMETER* apParameters, const char* apCompiledParams, TESObjectREFR* apRef, TESObjectREFR* apContainer, Script* apScript, ScriptLocals* apScriptLocals, double& arResult, uint32_t& arOffset
#define COMMAND_ARGS_PARSE	uint32_t auiParamCount, SCRIPT_PARAMETER* apParameters, SCRIPT_LINE* apScriptLine, ScriptCompileData* apCompileData
#define COMMAND_ARGS_EVAL	TESObjectREFR* apRef, void* apParam1, void* apParam2, double& arResult

using Cmd_Execute	= bool (__cdecl*)(COMMAND_ARGS);
using Cmd_Parse		= bool (__cdecl*)(COMMAND_ARGS_PARSE);
using Cmd_Eval		= bool (__cdecl*)(COMMAND_ARGS_EVAL);

struct SCRIPT_FUNCTION {
	const char*			pFunctionName;
	const char*			pShortName;
	uint32_t			uiOpcode;
	const char*			pHelpString;
	bool				bReferenceFunction;
	uint16_t			usParamCount;
	SCRIPT_PARAMETER*	pParameters;
	Cmd_Execute			pExecuteFunction;
	Cmd_Parse			pCompileFunction;
	Cmd_Eval			pConditionFunction;
	uint32_t			uiFlags;
};

ASSERT_SIZE(SCRIPT_FUNCTION, 0x28);
#endif