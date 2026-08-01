#pragma once

#include "Utilities.h"
#include "GameForms.h"
#include "Bethesda/Script.hpp"

class ScriptLocals;
struct ScriptVar;
class ScriptCompileData;

struct ScriptRunner
{
	uint32_t				unk00;			// 00
	TESForm				*baseForm;		// 04
	ScriptLocals		*eventList;		// 08
	uint32_t				unk10;			// 10
	Script				*script;		// 14
	uint32_t				unk18;			// 18	= 6 after failed to evaluate expression
	uint32_t				unk1C;			// 1C
	uint32_t				stackDepth;		// 20
	uint32_t				stack[10];		// 24
	uint32_t				stack2Depth;	// 4C
	uint32_t				stack2[10];		// 50
	uint32_t				stack3[10];		// 78
	uint8_t				unkA0;			// A0
	uint8_t				unkA1;			// A1	is set during runLine if CmdExecute.byt025 is not NULL
	uint8_t				padA2[2];		// A2
};

struct ConditionEntry
{
	struct Data
	{
		union Param
		{
			float	number;
			TESForm	* form;
		};

		// ### TODO: this
		uint32_t		operatorAndFlags;	// 00
		float		comparisonValue;	// 04
		uint16_t		functionIndex;		// 08 is opcode & 0x0FFF
		uint16_t		unk0A;
		Param		param1;				// 0C
		Param		param2;				// 10
		uint32_t		unk14;
	};

	Data			* data;
	ConditionEntry	* next;
};