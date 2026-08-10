#pragma once

#include "Utilities.h"
#include "GameForms.h"

class ScriptLocals;
struct ScriptVar;
struct ScriptBuffer;

#if 1
#define SCRIPT_SIZE 0x54
static const uint32_t kScript_ExecuteFnAddr = 0x005AC1E0;
#elif RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525ng
#define SCRIPT_SIZE 0x54
static const uint32_t kScript_ExecuteFnAddr = 0x005AC390;
#elif EDITOR
#define SCRIPT_SIZE 0x48
static const uint32_t kScript_SetTextFnAddr = 0x005C27B0;
#else
#error
#endif

// 54 / 48
class Script : public TESForm
{
public:
	Script();
	~Script();

	// members

	struct RefVariable
	{
		BSString		name;		// 00 variable name/editorID (not used at run-time)
		TESForm		*form;		// 08
		uint32_t		varIdx;		// 0C always zero in editor

		void	Resolve(ScriptLocals * eventList);
	};

	struct RefVarList : tList<RefVariable>
	{
		RefVariable *GetRefVariableByName(const char *name);
		uint32_t GetIndex(RefVariable *refVar);
	};

	enum
	{
		eVarType_Float = 0,			//ref is also zero
		eVarType_Integer,

		// NVSE, return values only
		eVarType_String,
		eVarType_Array,
		eVarType_Ref,

		eVarType_Invalid
	};

	typedef tList<VariableInfo> VarInfoList;

	// 14
	struct ScriptInfo
	{
		uint32_t	unk0;			// 00 (18)
		uint32_t	numRefs;		// 04 (1C)
		uint32_t	dataLength;		// 08 (20)
		uint32_t	varCount;		// 0C (24)
		uint16_t	type;			// 10 (28)
		uint16_t	unk12;			// 12 (2A)
	};

	enum
	{
		eType_Object =	0,
		eType_Quest =	1,
		eType_Magic =	0x100,
		eType_Unk =		0x10000,
	};
#if !RUNTIME
	uint32_t			unk028;					//     /     / 028
#endif
	ScriptInfo		info;					// 018 / 018 / 02C
	char			*text;					// 02C / 02C / 040
	uint8_t			*data;					// 030 / 030 / 044
#if RUNTIME
	float			unk34;					// 034
	float			questDelayTimeCounter;	// 038      - init'd to fQuestDelayTime, decremented by frametime each frame
	float			secondsPassed;			// 03C      - only if you've modified fQuestDelayTime
	TESQuest		*quest;					// 040
#endif
	RefVarList		refList;				// 044 / 034 / 048 - ref variables and immediates
	VarInfoList		varList;				// 04C / 03C / 050 - local variable list
#if !RUNTIME
	void			*unk050;				//     /     / 050
	uint8_t			unk054;					//	   /     / 054
	uint8_t			pad055[3];
#endif

	RefVariable		*GetVariable(uint32_t reqIdx);
	VariableInfo	*GetVariableInfo(uint32_t idx);

	uint32_t			AddVariable(TESForm *form);
	void			CleanupVariables(void);

	uint32_t			Type() const {return info.type;}
	bool			IsObjectScript() const {return info.type == eType_Object;}
	bool			IsQuestScript() const {return info.type == eType_Quest;}
	bool			IsMagicScript() const {return info.type == eType_Magic;}
	bool			IsUnkScript() const {return info.type == eType_Unk;}

	VariableInfo	*GetVariableByName(const char *varName);
	//uint32_t			GetVariableType(VariableInfo *var);
	ScriptVar		*AddVariable(ScriptLocals *eventList, uint32_t ownerID, uint8_t modIdx);
	uint32_t			GetDataLength();

	static bool	RunScriptLine(const char *text, TESObjectREFR *object = NULL);
	static bool	RunScriptLine2(const char *text, TESObjectREFR *object = NULL, bool bSuppressOutput = true);

	// no changed flags (TESForm flags)
	MEMBER_FN_PREFIX(Script);
#if 1
	// arg3 appears to be true for result scripts (runs script even if dataLength <= 4)
	DEFINE_MEMBER_FN(Execute, bool, kScript_ExecuteFnAddr, TESObjectREFR* thisObj, ScriptLocals* eventList, TESObjectREFR* containingObj, bool arg3);
	DEFINE_MEMBER_FN(Constructor, Script *, 0x005AA0F0);
	DEFINE_MEMBER_FN(SetText, void, 0x005ABE50, const char * text);
	DEFINE_MEMBER_FN(Run, bool, 0x005AC400, void * scriptContext, bool unkAlwaysOne, TESObjectREFR * object);
	DEFINE_MEMBER_FN(Destructor, void, 0x005AA1A0);
#elif RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525ng
	DEFINE_MEMBER_FN(Execute, bool, kScript_ExecuteFnAddr, TESObjectREFR* thisObj, ScriptLocals* eventList, TESObjectREFR* containingObj, bool arg3);
	DEFINE_MEMBER_FN(Constructor, Script *, 0x005AA220);
	DEFINE_MEMBER_FN(SetText, void, 0x005AC000, const char * text);
	DEFINE_MEMBER_FN(Run, bool, 0x005AC5B0, void * scriptContext, bool unkAlwaysOne, TESObjectREFR * object);
	DEFINE_MEMBER_FN(Destructor, void, 0x005AA2D0);
#elif EDITOR
#else
#error
#endif
	ScriptLocals	*CreateEventList();
};

#ifdef GAME
static_assert(sizeof(Script) == SCRIPT_SIZE);
#endif

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

#if RUNTIME
static_assert(sizeof(QuestStageItem) == (SCRIPT_SIZE + 0x1C));
#endif

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

// size 0x58? Nothing initialized beyond 0x50.
struct ScriptBuffer
{	
	template <typename tData> struct Node
	{
		tData		* data;
		Node<tData>	* next;
	};

	char					*scriptText;		// 000
	uint32_t					textOffset;			// 004 
	uint32_t					unk008;				// 008
	BSString					scriptName;			// 00C
	uint32_t					unk014;				// 014
	uint16_t					unk018;				// 018
	uint16_t					unk01A;				// 01A
	uint32_t					curLineNumber;		// 01C 
	uint8_t					*scriptData;		// 020 pointer to 0x4000-byte array
	uint32_t					dataOffset;			// 024
	uint32_t					unk028;				// 028
	uint32_t					numRefs;			// 02C
	uint32_t					unk030;				// 030
	uint32_t					varCount;			// 034 script->varCount
	uint8_t					scriptType;			// 038 script->type
	uint8_t					unk039;				// 039 script->unk35
	uint8_t					unk03A[2];
	Script::VarInfoList		vars;				// 03C
	Script::RefVarList		refVars;			// 044 probably ref vars
	uint32_t					unk04C;				// 04C num lines?
	Node<ScriptLineBuffer>	lines;				// 050
	// nothing else initialized

	// convert a variable or form to a RefVar, add to refList if necessary
	Script::RefVariable* ResolveRef(const char* refName);
	uint32_t GetRefIdx(Script::RefVariable *refVar);
	//uint32_t GetVariableType(VariableInfo *varInfo, Script::RefVariable *refVar);
};

//uint32_t GetDeclaredVariableType(const char* varName, const char* scriptText);	// parses scriptText to determine var type
//Script* GetScriptFromForm(TESForm* form);

