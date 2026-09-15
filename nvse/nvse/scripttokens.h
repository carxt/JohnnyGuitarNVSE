#pragma once

#if _DEBUG
#define DBG_EXPR_LEAKS 1
extern int32_t TOKEN_COUNT;
extern int32_t EXPECTED_TOKEN_COUNT;
extern int32_t FUNCTION_CONTEXT_COUNT;
#endif

#include "GameScript.h"
#include "CommandTable.h"
#include "GameForms.h"
#include "ArrayVar.h"

#if RUNTIME
#include "StringVar.h"
#include "GameAPI.h"

#endif

struct Operator;
struct SliceToken;
struct ArrayElementToken;
struct ForEachContext;
class ExpressionEvaluator;
struct ScriptToken;

enum OperatorType : uint8_t
{
	kOpType_Min		= 0,

	kOpType_Assignment	= 0,
	kOpType_LogicalOr,
	kOpType_LogicalAnd,
	kOpType_Slice,
	kOpType_Equals,
	kOpType_NotEqual,
	kOpType_GreaterThan,
	kOpType_LessThan,
	kOpType_GreaterOrEqual,
	kOpType_LessOrEqual,
	kOpType_BitwiseOr,
	kOpType_BitwiseAnd,
	kOpType_LeftShift,
	kOpType_RightShift,
	kOpType_Add,
	kOpType_Subtract,
	kOpType_Multiply,
	kOpType_Divide,
	kOpType_Modulo,
	kOpType_Exponent,
	kOpType_Negation,
	kOpType_LogicalNot,
	kOpType_LeftParen,
	kOpType_RightParen,
	kOpType_LeftBracket,
	kOpType_RightBracket,
	kOpType_In,				// '<-'
	kOpType_ToString,		// '$'
	kOpType_PlusEquals,
	kOpType_TimesEquals,
	kOpType_DividedEquals,
	kOpType_ExponentEquals,
	kOpType_MinusEquals,
	kOpType_ToNumber,		// '#'
	kOpType_Dereference,	// unary '*'
	kOpType_MemberAccess,	// stringmap->string, shortcut for stringmap["string"]
	kOpType_MakePair,		// 'a::b', e.g. for defining key-value pairs for map structures
	kOpType_Box,			// unary; wraps a value in a single-element array

	kOpType_LeftBrace,
	kOpType_RightBrace,

	kOpType_Max
};

enum Token_Type : uint8_t
{
	kTokenType_Number	= 0,
	kTokenType_Boolean,
	kTokenType_String,
	kTokenType_Form,
	kTokenType_Ref,
	kTokenType_Global,
	kTokenType_Array,
	kTokenType_ArrayElement,
	kTokenType_Slice,
	kTokenType_Command,
	kTokenType_Variable,
	kTokenType_NumericVar,
	kTokenType_RefVar,
	kTokenType_StringVar,
	kTokenType_ArrayVar,
	kTokenType_Ambiguous,
	kTokenType_Operator,
	kTokenType_ForEachContext,

	// numeric literals can optionally be encoded as one of the following
	// all are converted to _Number on evaluation
	kTokenType_Byte,
	kTokenType_Short,		// 2 bytes
	kTokenType_Int,			// 4 bytes

	kTokenType_Pair,
	kTokenType_AssignableString,

	kTokenType_Invalid,
	kTokenType_Max = kTokenType_Invalid,

	// sigil value, returned when an empty expression is parsed
	kTokenType_Empty = kTokenType_Max + 1,
};