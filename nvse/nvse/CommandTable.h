#pragma once

#include <unordered_map>
#include <vector>

#include "Bethesda/Script.hpp"

class TESObjectREFR;
class Script;
class ScriptLocals;
struct SCRIPT_LINE;
class ScriptCompileData;
struct PluginInfo;

enum CommandReturnType : uint8_t
{
	kRetnType_Default,
	kRetnType_Form,
	kRetnType_String,
	kRetnType_Array,
	kRetnType_ArrayIndex,
	kRetnType_Ambiguous,

	kRetnType_Max
};

const char* CommandReturnTypeToString(CommandReturnType in);

struct SCRIPT_FUNCTION;

#define USE_EXTRACT_ARGS_EX NVSE_CORE

#define COMMAND_ARGS_EX		SCRIPT_PARAMETER* apParameters, const char* apCompiledParams, uint32_t& arOffset, Script* apScript, ScriptLocals* apScriptLocals
#define PASS_COMMAND_ARGS	apParameters, apCompiledParams, apRef, apContainer, apScript, apScriptLocals, arResult, arOffset
#define PASS_CMD_ARGS_EVAL	apRef, apParam1, apParam2, arResult
#define EXTRACT_ARGS_EX		apParameters, apCompiledParams, arOffset, apScript, apScriptLocals
#define PASS_FMTSTR_ARGS	apParameters, apCompiledParams, arOffset, apScript, apScriptLocals
#if USE_EXTRACT_ARGS_EX
#define EXTRACT_ARGS		EXTRACT_ARGS_EX
#else
#define EXTRACT_ARGS		apParameters, apCompiledParams, arOffset, apRef, apContainer, apScript, apScriptLocals
#endif

//Macro to make SCRIPT_FUNCTION definitions a bit less tedious

#define DEFINE_CMD_FULL(name, altName, description, refRequired, usParamCount, apParameters, parser) \
	extern bool Cmd_ ## name ## _Execute(COMMAND_ARGS); \
	static SCRIPT_FUNCTION (kCommandInfo_ ## name) = { \
	#name, \
	#altName, \
	0, \
	#description, \
	refRequired, \
	usParamCount, \
	apParameters, \
	HANDLER(Cmd_ ## name ## _Execute), \
	parser, \
	NULL, \
	0 \
	};

#define DEFINE_CMD_FULL_VER(name, altName, description, refRequired, usParamCount, apParameters, parser, major, minor, beta) \
	extern bool Cmd_ ## name ## _ ## major ## _ ## minor ## _ ## beta ## _Execute(COMMAND_ARGS); \
	static SCRIPT_FUNCTION (kCommandInfo_ ## name ## _ ## major ## _ ## minor ## _ ## beta) = { \
	#name, \
	#altName, \
	0, \
	#description, \
	refRequired, \
	usParamCount, \
	apParameters, \
	HANDLER(Cmd_ ## name ## _ ## major ## _ ## minor ## _ ## beta ## _Execute), \
	parser, \
	NULL, \
	0 \
	};

#define DEFINE_CMD_ALIAS(name, altName, description, refRequired, apParameters) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, Cmd_Default_Parse)	

#define DEFINE_CMD_ALT_EXP(name, altName, description, refRequired, apParameters) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, Cmd_Expression_Parse)	

#define DEFINE_CMD(name, description, refRequired, apParameters) \
	DEFINE_CMD_FULL(name, , description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, Cmd_Default_Parse)

#define DEFINE_COMMAND_EXP(name, description, refRequired, apParameters) \
	DEFINE_CMD_ALT_EXP(name, , description, refRequired, apParameters)

#define DEFINE_CMD_VER_EXP(name, description, refRequired, apParameters, major, minor, beta) \
	DEFINE_CMD_FULL_VER(name, , description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, Cmd_Expression_Parse, major, minor, beta)

#define DEFINE_COMMAND_PLUGIN(name, description, refRequired, apParameters) \
	DEFINE_CMD_FULL(name, , description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, NULL)

#define DEFINE_COMMAND_ALT_PLUGIN(name, altName, description, refRequired, apParameters) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, NULL)

#define DEFINE_COMMAND_PLUGIN_EXP(name, description, refRequired, apParameters) \
	DEFINE_CMD_FULL(name, , description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, Cmd_Expression_Plugin_Parse)

#define DEFINE_COMMAND_ALT_PLUGIN_EXP(name, altName, description, refRequired, apParameters) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, (apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0, apParameters, Cmd_Expression_Plugin_Parse)

// for commands which can be used as conditionals
#define DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, apParameters, parser) \
	extern bool Cmd_ ## name ## _Execute(COMMAND_ARGS); \
	extern bool Cmd_ ## name ## _Eval(COMMAND_ARGS_EVAL); \
	static SCRIPT_FUNCTION (kCommandInfo_ ## name) = { \
	#name,	\
	#altName,		\
	0,		\
	#description,	\
	refRequired,	\
	(apParameters) ? (sizeof(apParameters) / sizeof(SCRIPT_PARAMETER)) : 0,	\
	apParameters,	\
	HANDLER(Cmd_ ## name ## _Execute),	\
	parser,	\
	HANDLER_EVAL(Cmd_ ## name ## _Eval),	\
	1	\
	};

#define DEFINE_CMD_ALT_COND(name, altName, description, refRequired, apParameters) \
	DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, apParameters, Cmd_Default_Parse)

#define DEFINE_CMD_ALT_COND_PLUGIN(name, altName, description, refRequired, apParameters) \
	DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, apParameters, NULL)

#define DEFINE_CMD_COND(name, description, refRequired, apParameters) \
	DEFINE_CMD_ALT_COND(name, , description, refRequired, apParameters)

#define DEFINE_CMD_COND_PLUGIN(name, description, refRequired, apParameters) \
	DEFINE_CMD_ALT_COND_ANY(name, , description, refRequired, apParameters, NULL)
bool Cmd_Default_Execute(COMMAND_ARGS);

bool Cmd_Default_Parse(uint32_t auiParamCount, SCRIPT_PARAMETER* apParameters, SCRIPT_LINE* apScriptLine, ScriptCompileData* apCompileData);
const Cmd_Parse Cmd_Expression_Plugin_Parse = (Cmd_Parse)0x08000000;
bool Cmd_Default_Eval(COMMAND_ARGS_EVAL);


#ifdef RUNTIME
#define HANDLER(x)	x
#define HANDLER_EVAL(x)	x
#else
#define HANDLER(x)	Cmd_Default_Execute
#define HANDLER_EVAL(x)	Cmd_Default_Eval
#endif