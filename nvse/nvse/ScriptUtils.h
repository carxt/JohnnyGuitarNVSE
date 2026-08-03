#pragma once

/*
	Expressions are evaluated according to a set of rules stored in lookup tables. Each type of operand can 
	be resolved to zero or more	"lower" types as defined by ConversionRule. Operators use OperationRules based
	on the types of each operand to	determine the result type. Types can be ambiguous at compile-time (array 
	elements, command results) but always resolve to a concrete type at run-time. Rules are applied in the order 
	they are defined until the first one matching the operands is encountered. At run-time this means the routines
	which perform the operations can know that the operands are of the expected type.
*/

struct Operator;
class ScriptLocals;
class ExpressionEvaluator;
struct UserFunctionParam;
struct FunctionInfo;
struct FunctionContext;
class FunctionCaller;

#include "ScriptTokens.h"
#include <stack>

#if RUNTIME
#include <cstdarg>
#endif

// these are used in SCRIPT_PARAMETER to specify expected Token_Type of args to commands taking NVSE expressions as args
enum {
	kNVSEParamType_Number =		(1 << kTokenType_Number) | (1 << kTokenType_Ambiguous),
	kNVSEParamType_Boolean =	(1 << kTokenType_Boolean) | (1 << kTokenType_Ambiguous),
	kNVSEParamType_String =		(1 << kTokenType_String) | (1 << kTokenType_Ambiguous),
	kNVSEParamType_Form =		(1 << kTokenType_Form) | (1 << kTokenType_Ambiguous),
	kNVSEParamType_Array =		(1 << kTokenType_Array) | (1 << kTokenType_Ambiguous),
	kNVSEParamType_ArrayElement = 1 << (kTokenType_ArrayElement) | (1 << kTokenType_Ambiguous),
	kNVSEParamType_Slice =		1 << kTokenType_Slice,
	kNVSEParamType_Command =	1 << kTokenType_Command,
	kNVSEParamType_Variable =	1 << kTokenType_Variable,
	kNVSEParamType_NumericVar =	1 << kTokenType_NumericVar,
	kNVSEParamType_RefVar =		1 << kTokenType_RefVar,
	kNVSEParamType_StringVar =	1 << kTokenType_StringVar,
	kNVSEParamType_ArrayVar =	1 << kTokenType_ArrayVar,
	kNVSEParamType_ForEachContext = 1 << kTokenType_ForEachContext,

	kNVSEParamType_Collection = kNVSEParamType_Array | kNVSEParamType_String,
	kNVSEParamType_ArrayVarOrElement = kNVSEParamType_ArrayVar | kNVSEParamType_ArrayElement,
	kNVSEParamType_ArrayIndex = kNVSEParamType_String | kNVSEParamType_Number,
	kNVSEParamType_BasicType = kNVSEParamType_Array | kNVSEParamType_String | kNVSEParamType_Number | kNVSEParamType_Form,
	kNVSEParamType_NoTypeCheck = 0,

	kNVSEParamType_FormOrNumber = kNVSEParamType_Form | kNVSEParamType_Number,
	kNVSEParamType_StringOrNumber = kNVSEParamType_String | kNVSEParamType_Number,
	kNVSEParamType_Pair	=	1 << kTokenType_Pair,
};

#define NVSE_EXPR_MAX_ARGS 20		// max # of args we'll accept to a commmand

// wraps a dynamic SCRIPT_PARAMETER array
struct DynamicParamInfo
{
private:
	static const uint32_t kMaxParams = 15;	// Should be linked to NVSE_EXPR_MAX_ARGS ?

	SCRIPT_PARAMETER	m_paramInfo[kMaxParams];
	uint32_t		m_numParams;

public:
	DynamicParamInfo(std::vector<UserFunctionParam> &params);
	DynamicParamInfo() : m_numParams(0) { }

	SCRIPT_PARAMETER* Params()	{	return m_paramInfo;	}
	uint32_t NumParams()	{ return m_numParams;	}
};

class ExpressionEvaluator
{
	enum { kMaxArgs = NVSE_EXPR_MAX_ARGS };

	enum {
		kFlag_SuppressErrorMessages	= 1 << 0,
		kFlag_ErrorOccurred			= 1 << 1,
		kFlag_StackTraceOnError		= 1 << 2,
	};

	uint32_t				m_flags;
	uint8_t				* m_scriptData;
	uint32_t				* m_opcodeOffsetPtr;
	double				* m_result;
	TESObjectREFR		* m_thisObj;
	TESObjectREFR		* m_containingObj;
	uint8_t				* m_data;
	ScriptToken			* m_args[kMaxArgs];
	SCRIPT_PARAMETER			* m_params;
	uint8_t				m_numArgsExtracted;
	CommandReturnType	m_expectedReturnType;
	uint16_t				m_baseOffset;
	ExpressionEvaluator	* m_parent;

	uint8_t*			&Data()	{ return m_data;	}
	CommandReturnType GetExpectedReturnType() { CommandReturnType type = m_expectedReturnType; m_expectedReturnType = kRetnType_Default; return type; }

	void PushOnStack();
	void PopFromStack();
public:
	static bool	Active();

	ExpressionEvaluator(COMMAND_ARGS);
	~ExpressionEvaluator();

	Script			* script;
	ScriptLocals	* eventList;

	void			Error(const char* fmt, ...);
	bool			HasErrors() { return (m_flags & kFlag_ErrorOccurred) != 0; }

	// extract args compiled by ExpressionParser
	bool			ExtractArgs();

	// extract args to function which normally uses Cmd_Default_Parse but has been compiled instead by ExpressionParser
	// bConvertTESForms will be true if invoked from ExtractArgs(), false if from ExtractArgsEx()
	bool			ExtractDefaultArgs(va_list varArgs, bool bConvertTESForms);

	// convert an extracted argument to type expected by ExtractArgs/Ex() and store in varArgs
	bool			ConvertDefaultArg(ScriptToken* arg, SCRIPT_PARAMETER* info, bool bConvertTESForms, va_list& varArgs);

	// extract formatted string args compiled with compiler override
	bool ExtractFormatStringArgs(va_list varArgs, uint32_t fmtStringPos, char* fmtStringOut, uint32_t maxParams);

	ScriptToken*	Evaluate();			// evaluates a single argument/token

	ScriptToken*	Arg(uint32_t idx) { return idx < kMaxArgs ? m_args[idx] : NULL; }
	uint8_t			NumArgs() { return m_numArgsExtracted; }
	void			SetParams(SCRIPT_PARAMETER* newParams)	{	m_params = newParams;	}
	void			ExpectReturnType(CommandReturnType type) { m_expectedReturnType = type; }
	void			ToggleErrorSuppression(bool bSuppress);
	void			PrintStackTrace();

	TESObjectREFR*	ThisObj() { return m_thisObj; }
	TESObjectREFR*	ContainingObj() { return m_containingObj; }

	uint8_t		ReadByte();
	uint16_t		Read16();
	double		ReadFloat();
	std::string	ReadString();
	int8_t		ReadSignedByte();
	int16_t		ReadSigned16();
	uint32_t		Read32();
	int32_t		ReadSigned32();
};

bool BasicTokenToElem(ScriptToken* token, ArrayElement& elem, ExpressionEvaluator* context);

void ShowRuntimeError(Script* script, const char* fmt, ...);
bool PrecompileScript(ScriptCompileData* buf);

// NVSE analogue for Cmd_Default_Parse, accepts expressions as args
bool Cmd_Expression_Parse(uint32_t auiParamCount, SCRIPT_PARAMETER* apParameters, SCRIPT_LINE* apScriptLine, ScriptCompileData* apCompileData);

extern Operator s_operators[];

