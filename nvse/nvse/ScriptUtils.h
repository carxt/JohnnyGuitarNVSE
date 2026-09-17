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

// these are used in ParamInfo to specify expected Token_Type of args to commands taking NVSE expressions as args
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