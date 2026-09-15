#pragma once

#include "Utilities.h"
#include "GameForms.h"

class ScriptLocals;
struct ScriptVar;
struct ScriptBuffer;

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

// 6C
struct QuestStageItem
{
	uint32_t			unk00;			// 00
	ConditionEntry	conditionList;	// 04
	Script			resultScript;	// 0C
	uint32_t			unk5C;			// 5C disk offset to log text records? consistent within a single quest
	uint8_t			index;			// 60 sequential
	bool			hasLogText;		// 61
	uint8_t			unk62[2];		// 62 pad?
	uint32_t			logDate;		// 64
	TESQuest		* owningQuest;	// 68;
};

// 41C
struct ScriptLineBuffer
{
	static const uint32_t	kBufferSize = 0x200;

	uint32_t				lineNumber;			// 000 counts blank lines too
	char				paramText[0x200];	// 004 portion of line text following command
	uint32_t				paramTextLen;		// 204
	uint32_t				lineOffset;			// 208
	uint8_t				dataBuf[0x200];		// 20C
	uint32_t				dataOffset;			// 40C
	uint32_t				cmdOpcode;			// 410 not initialized. Opcode of command being parsed
	uint32_t				callingRefIndex;	// 414 not initialized. Zero if cmd not invoked with dot syntax
	uint32_t				unk418;				// 418

	// these write data and update dataOffset
	bool Write(const void* buf, uint32_t bufsize);
	bool WriteFloat(double buf);
	bool WriteString(const char* buf);
	bool Write32(uint32_t buf);
	bool Write16(uint16_t buf);
	bool WriteByte(uint8_t buf);
};