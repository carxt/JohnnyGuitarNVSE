#pragma once

#include "GameTypes.h"
#include "GameScript.h"
#include "Bethesda/ScriptLocals.hpp"
#include <string>

struct SCRIPT_PARAMETER;
class TESForm;
class TESObjectREFR;
class BaseExtraList;

#define playerID	0x7
#define playerRefID 0x14

#if 1
static const uint32_t s_Console__Print = 0x0071D0A0;
#elif EDITOR
#else
#error
#endif

extern bool extraTraces;

void Console_Print(const char* fmt, ...);

#if RUNTIME

typedef bool (*_ExtractArgs)(SCRIPT_PARAMETER* apParameters, void* apCompiledParams, uint32_t* arg2, TESObjectREFR* arg3, TESObjectREFR* arg4, Script* script, ScriptLocals* apScriptLocals, ...);
extern const _ExtractArgs ExtractArgs;

typedef TESForm* (*_CreateFormInstance)(uint8_t type);
extern const _CreateFormInstance CreateFormInstance;

bool IsConsoleMode();
bool GetConsoleEcho();
void SetConsoleEcho(bool doEcho);

typedef char* (*_GetActorValueName)(uint32_t actorValueCode);
extern const _GetActorValueName GetActorValueName;
uint32_t GetActorValueMax(uint32_t actorValueCode);

typedef void (*_ShowMessageBox_Callback)(void);
extern const _ShowMessageBox_Callback ShowMessageBox_Callback;

// unk1 = 0
// unk2 = 0
// callback = may be NULL apparently
// unk4 = 0
// unk5 = 0x17 (why?)
// unk6 = 0
// unk7 = 0
// then buttons
// then NULL
typedef bool (*_ShowMessageBox)(const char* message, uint32_t unk1, uint32_t unk2, _ShowMessageBox_Callback callback, uint32_t unk4, uint32_t unk5, float unk6, float unk7, ...);
extern const _ShowMessageBox ShowMessageBox;

// set to scriptObj->GetFormID() after calling ShowMessageBox()
// GetButtonPressed checks this before returning a value, if it doesn't match it returns -1
typedef uint32_t* _ShowMessageBox_pScriptRefID;
extern const _ShowMessageBox_pScriptRefID ShowMessageBox_pScriptRefID;
typedef uint8_t* _ShowMessageBox_button;
extern const _ShowMessageBox_button ShowMessageBox_button;

// unk1 = 0
// unk3 = 0, "UIVATSInsufficientAP" (sound?)
// duration = 2
// unk5 = 0
typedef bool (*_QueueUIMessage)(const char* msgText, uint32_t iconType, const char* iconPath, const char* soundPath, float displayTime, uint8_t unk5);
extern const _QueueUIMessage QueueUIMessage;

const uint32_t kMaxMessageLength = 0x4000;
#endif

struct NVSEStringVarInterface;
// Problem: plugins may want to use %z specifier in format strings, but don't have access to StringVarMap
// Could change params to ExtractFormatStringArgs to include an NVSEStringVarInterface* but
//  this would break existing plugins
// Instead allow plugins to register their NVSEStringVarInterface for use
// I'm sure there is a better way to do this but I haven't found it
void RegisterStringVarInterface(NVSEStringVarInterface* intfc);

struct ScriptVar {
	uint32_t		id;
	void* next;
	double		data;
};


ScriptLocals* EventListFromForm(TESForm* form);

typedef bool (*_MarkBaseExtraListScriptEvent)(TESForm* target, BaseExtraList* extraList, uint32_t eventMask);
extern const _MarkBaseExtraListScriptEvent MarkBaseExtraListScriptEvent;

struct ExtractedParam {
	// float/double types are kept as pointers
	// this avoids problems with storing invalid floats/doubles in to the fp registers which has a side effect
	// of corrupting data

	enum {
		kType_Unknown = 0,
		kType_String,		// str
		kType_Imm32,		// imm
		kType_Imm16,		// imm
		kType_Imm8,			// imm
		kType_ImmDouble,	// immDouble
		kType_Form,			// form
	};

	uint8_t	type;
	bool	isVar;	// if true, data is stored in var, otherwise it's immediate

	union {
		// immediate
		uint32_t			imm;
		const double* immDouble;
		TESForm* form;
		struct {
			const char* buf;
			uint32_t		len;
		} str;

		// variable
		struct {
			ScriptVar* var;
			ScriptLocals* parent;
		} var;
	} data;
};

enum EActorVals {
	eActorVal_Aggression = 0,
	eActorVal_Confidence = 1,
	eActorVal_Energy = 2,
	eActorVal_Responsibility = 3,
	eActorVal_Mood = 4,

	eActorVal_Strength = 5,
	eActorVal_Perception = 6,
	eActorVal_Endurance = 7,
	eActorVal_Charisma = 8,
	eActorVal_Intelligence = 9,
	eActorVal_Agility = 10,
	eActorVal_Luck = 11,
	eActorVal_SpecialStart = eActorVal_Strength,
	eActorVal_SpecialEnd = eActorVal_Luck,

	eActorVal_ActionPoints = 12,
	eActorVal_CarryWeight = 13,
	eActorVal_CritChance = 14,
	eActorVal_HealRate = 15,
	eActorVal_Health = 16,
	eActorVal_MeleeDamage = 17,
	eActorVal_DamageResistance = 18,
	eActorVal_PoisonResistance = 19,
	eActorVal_RadResistance = 20,
	eActorVal_SpeedMultiplier = 21,
	eActorVal_Fatigue = 22,
	eActorVal_Karma = 23,
	eActorVal_XP = 24,

	eActorVal_Head = 25,
	eActorVal_Torso = 26,
	eActorVal_LeftArm = 27,
	eActorVal_RightArm = 28,
	eActorVal_LeftLeg = 29,
	eActorVal_RightLeg = 30,
	eActorVal_Brain = 31,
	eActorVal_BodyPartStart = eActorVal_Head,
	eActorVal_BodyPartEnd = eActorVal_Brain,

	eActorVal_Barter = 32,
	eActorVal_BigGuns = 33,
	eActorVal_EnergyWeapons = 34,
	eActorVal_Explosives = 35,
	eActorVal_Lockpick = 36,
	eActorVal_Medicine = 37,
	eActorVal_MeleeWeapons = 38,
	eActorVal_Repair = 39,
	eActorVal_Science = 40,
	eActorVal_Guns = 41,
	eActorVal_Sneak = 42,
	eActorVal_Speech = 43,
	eActorVal_Survival = 44,
	eActorVal_Unarmed = 45,
	eActorVal_SkillsStart = eActorVal_Barter,
	eActorVal_SkillsEnd = eActorVal_Unarmed,

	eActorVal_InventoryWeight = 46,
	eActorVal_Paralysis = 47,
	eActorVal_Invisibility = 48,
	eActorVal_Chameleon = 49,
	eActorVal_NightEye = 50,
	eActorVal_Turbo = 51,
	eActorVal_FireResistance = 52,
	eActorVal_WaterBreathing = 53,
	eActorVal_RadLevel = 54,
	eActorVal_BloodyMess = 55,
	eActorVal_UnarmedDamage = 56,
	eActorVal_Assistance = 57,

	eActorVal_ElectricResistance = 58,
	eActorVal_FrostResistance = 59,

	eActorVal_EnergyResistance = 60,
	eActorVal_EMPResistance = 61,
	eActorVal_Var1Medical = 62,
	eActorVal_Var2 = 63,
	eActorVal_Var3 = 64,
	eActorVal_Var4 = 65,
	eActorVal_Var5 = 66,
	eActorVal_Var6 = 67,
	eActorVal_Var7 = 68,
	eActorVal_Var8 = 69,
	eActorVal_Var9 = 70,
	eActorVal_Var10 = 71,

	eActorVal_IgnoreCrippledLimbs = 72,
	eActorVal_Dehydration = 73,
	eActorVal_Hunger = 74,
	eActorVal_Sleepdeprevation = 75,
	eActorVal_Damagethreshold = 76,
	eActorVal_FalloutMax = eActorVal_Damagethreshold,
	eActorVal_NoActorValue = 256,
};

// 914
class ConsoleManager {
public:
#if RUNTIME
	MEMBER_FN_PREFIX(ConsoleManager);
	DEFINE_MEMBER_FN(Print, void, s_Console__Print, const char* fmt, va_list args);
#endif

	ConsoleManager();
	~ConsoleManager();

	struct TextNode {
		TextNode* next;
		TextNode* prev;
		BSString		text;
	};

	struct TextList {
		TextNode* first;
		TextNode* last;
		uint32_t		count;
	};

	void* scriptContext;		// 000
	TextList	printedLines;		// 004
	TextList	inputHistory;		// 010
	uint32_t		unk01C;				// 01C
	uint32_t		unk020;				// 020
	uint32_t		unk024;				// 024
	uint32_t		unk028[571];		// 028

	static ConsoleManager* GetSingleton(void);
};
static_assert(sizeof(ConsoleManager) == 0x914);

// A plugin author requested the ability to use OBSE format specifiers to format strings with the args
// coming from a source other than script.
// So changed ExtractFormattedString to take an object derived from following class, containing the args
// Probably doesn't belong in GameAPI.h but utilizes a bunch of stuff defined here and can't think of a better place for it
class FormatStringArgs {
public:
	enum argType {
		kArgType_Float,
		kArgType_Form		// TESForm*
	};

	virtual bool Arg(argType asType, void* outResult) = 0;	// retrieve next arg
	virtual bool SkipArgs(uint32_t numToSkip) = 0;			// skip specified # of args
	virtual bool HasMoreArgs() = 0;
	virtual std::string GetFormatString() = 0;						// return format string
};

// concrete class used for extracting script args
class ScriptFormatStringArgs : public FormatStringArgs {
public:
	virtual bool Arg(argType asType, void* outResult);
	virtual bool SkipArgs(uint32_t numToSkip);
	virtual bool HasMoreArgs();
	virtual std::string GetFormatString();

	ScriptFormatStringArgs(uint32_t _numArgs, uint8_t* _scriptData, Script* _scriptObj, ScriptLocals* _eventList);
	uint32_t GetNumArgs();
	uint8_t* GetScriptData();

private:
	uint32_t			numArgs;
	uint8_t* scriptData;
	Script* scriptObj;
	ScriptLocals* apScriptLocals;
	std::string fmtString;
};
bool SCRIPT_ASSERT(bool expr, Script* script, const char* errorMsg, ...);

bool ExtractSetStatementVar(Script* script, ScriptLocals* apScriptLocals, void* scriptDataIn, double* outVarData, uint8_t* outModIndex = NULL, bool shortPath = false);

class ChangesMap;
class InteriorCellNewReferencesMap;
class ExteriorCellNewReferencesMap;
class NumericIDBufferMap;

class NiBinaryStream {
public:
	NiBinaryStream();
	~NiBinaryStream();

	virtual void		Destructor(bool freeMemory);		// 00
	virtual bool		FileIsGood(void);					// 04
	virtual void		SeekCur(int32_t delta);				// 08
	virtual uint32_t	GetPosition() const;				// 0C
	virtual void		SetEndianSwap(bool useAlt);			// 10

//	void	** m_vtbl;		// 000
	uint32_t	m_offset;		// 004
	void* m_readProc;	// 008 - function pointer
	void* m_writeProc;	// 00C - function pointer
};

class NiFile : public NiBinaryStream {
public:
	NiFile();
	~NiFile();

	virtual void		Seek(int32_t aiOffset, int32_t aiWhence);
	virtual const char* GetFilename() const;
	virtual uint32_t		GetFileSize();

	uint32_t	m_bufSize;	// 010
	uint32_t	m_uiBufferReadSize;	// 014 - Total read in buffer
	uint32_t	m_uiPos;	// 018 - Consumed from buffer
	uint32_t	m_uiAbsolutePos;	// 01C
	void*	m_buffer;	// 020
	FILE*	m_File;		// 024
	uint32_t	m_eMode;
	bool	m_bGood;
};

static_assert(sizeof(NiFile) == 0x30);
// 158
class BSFile : public NiFile {
public:
	BSFile();
	~BSFile();

	virtual bool	Open(bool arg1, bool arg2);	// 20
	virtual bool	OpenByFilePointer(FILE* apFile);
	virtual uint32_t	GetSize();
	virtual uint32_t	ReadString(BSString& arString, uint32_t auiMaxLength);
	virtual uint32_t	ReadStringAlt(BSString& arString, uint32_t auiMaxLength);
	virtual uint32_t	GetLine(char* apBuffer, uint32_t auiMaxBytes, uint8_t aucMark);
	virtual uint32_t	WriteString(BSString& arString, bool abBinary);
	virtual uint32_t	WriteStringAlt(BSString& arString, bool abBinary);
	virtual bool	IsReadable();
	virtual uint32_t	DoRead(void* apBuffer, uint32_t auiBytes);
	virtual uint32_t	DoWrite(const void* apBuffer, uint32_t auiBytes);

	bool		bUseAuxBuffer;				// 02D
	void*		pAuxBuffer;
	int32_t		iAuxTrueFilePos;
	DWORD		dword3C;
	DWORD		dword40;
	char		cFileName[260];
	uint32_t		uiResult;
	uint32_t		uiIOSize;
	uint32_t		uiTrueFilePos;
	uint32_t		uiFileSize;
};

static_assert(sizeof(BSFile) == 0x158);

class BSArchiveHeader
{
public:
	BSArchiveHeader();
	~BSArchiveHeader();
};

// 70
class BSArchive : public BSArchiveHeader
{
public:
	BSArchive();
	~BSArchive();

	uint32_t unk00; // 00	160
	uint32_t unk04; // 04	164
	uint32_t unk08; // 08	168
	uint32_t unk0C; // 0C	16C
	uint32_t unk10; // 10	170
	uint32_t unk14; // 14	174
	uint32_t unk18; // 18	178
	uint32_t unk1C; // 1C	17C
	uint16_t fileTypesMask; // 20	180
	uint16_t word22; // 22	182
	uint32_t unk24[19]; // 24	184
};

static_assert(sizeof(BSArchive) == 0x70);

// 1D0
class Archive : public BSFile
{
public:
	Archive();
	~Archive();

	NiRefObject refObject; // 158
	BSArchive archive; // 160
};

static_assert(sizeof(Archive) == 0x1D0);

// 160
class ArchiveFile : public BSFile
{
public:
	ArchiveFile();
	~ArchiveFile();

	uint32_t unk158; // 158
	uint32_t unk15C; // 15C
};

static_assert(sizeof(ArchiveFile) == 0x160);

// 178
class CompressedArchiveFile : public ArchiveFile
{
public:
	CompressedArchiveFile();
	~CompressedArchiveFile();

	void* ptr160; // 160
	void* ptr164; // 164
	uint32_t streamLength; // 168
	uint32_t unk16C; // 16C
	uint32_t streamOffset; // 170
	uint32_t unk174; // 174
};

static_assert(sizeof(CompressedArchiveFile) == 0x178);

//
struct ToBeNamed {
	char		m_path[0x104];	// 0000
	BSFile* m_file;			// 0104
	uint32_t		m_unk0108;		// 0108
	uint32_t		m_offset;		// 010C
};

// Form type class: use to preload some information for created objects (?) refr and Cells
struct formTypeClassData {
	typedef uint8_t EncodedID[3];	// Codes the refID on 3 bytes, as used in changed forms and save refID mapping

	struct Data01 // Applies to CELL where changeFlags bit30 (Detached CELL) and bit29 (CHANGE_CELL_EXTERIOR_CHAR) are set
	{
		uint16_t	worldspaceIndex;	// 00 Index into visitedWorldspaces		goes into unk000
		uint8_t	coordX;				// 02	goes into unk004
		uint8_t	coordY;				// 03	goes into unk008, paired with 002
		uint8_t	detachTime;			// 04	goes into unk00C
	};

	struct Data02 // Applies to CELL where changeFlags bit30 (Detached CELL) and bit 28 (CHANGE_CELL_EXTERIOR_SHORT) are set and changeFlags bit29 is clear
	{
		uint16_t	worldspaceIndex;	// 00 Index into visitedWorldspaces		goes into unk000
		uint16_t	coordX;				// 02	goes into unk004
		uint16_t	coordY;				// 03	goes into unk008, paired with 002
		uint32_t	detachTime;			// 04	goes into unk00C
	};

	// The difference between the two preceding case seems to be how big the data (coordinates?) are

	struct Data03 // Applies to CELL where changeFlags bit30 (Detached CELL) is set and changeFlags bit28 and bit29 are clear
	{
		uint32_t	detachTime;	// 00	goes into unk00C. Null goes into unk000, 004 and 008
	};

	struct Data04 // Applies to references where changeFlags bit3 (CHANGE_REFR_CELL_CHANGED) is clear and
					// either bit1 (CHANGE_REFR_MOVE) or bit2 (CHANGE_REFR_HAVOK_MOVE) is set
	{
		EncodedID	cellOrWorldspaceID;	// 000	goes into unk000, Null goes into unk004, 008, 00C, 010 and byt02C
		float		posX;	// 003	goes into unk014
		float		posY;	// 007	goes into unk018, associated with unk003
		float		posZ;	// 00B	goes into unk01C, associated with unk003	(pos?)
		float		rotX;	// 00F	goes into unk020
		float		rotY;	// 013	goes into unk024, associated with unk00F
		float		rotZ;	// 017	goes into unk028, associated with unk00F	(rot?)
	};

	struct Data05 // Applies to created objects (ie 0xFFnnnnnn)
	{
		EncodedID	cellOrWorldspaceID;	// 000	goes into unk000
		float		posX;	// 003	goes into unk014
		float		posY;	// 007	goes into unk018, associated with unk003
		float		posZ;	// 00B	goes into unk01C, associated with unk003	(pos?)
		float		rotX;	// 00F	goes into unk020
		float		rotY;	// 013	goes into unk024, associated with unk024
		float		rotZ;	// 017	goes into unk028, associated with unk028	(rot?)
		uint8_t		flags;	// 01B	goes into unk02C	bit0 always set, bit1 = ESP or persistent, bit2 = Byt081 true
		EncodedID	baseFormID;	// 01C	goes into unk004, Null goes into unk008, 00C and 010
	};

	struct Data06 // Applies to references whose changeFlags bit3 (CHANGE_REFR_CELL_CHANGED) is set
	{
		EncodedID	cellOrWorldspace;		// 000	goes into unk000
		float		posX;					// 003	goes into unk014
		float		posY;					// 007	goes into unk018, associated with unk003
		float		posZ;					// 00B	goes into unk01C, associated with unk003	(pos?)
		float		rotX;					// 00F	goes into unk020
		float		rotY;					// 013	goes into unk024, associated with unk00F
		float		rotZ;					// 017	goes into unk028, associated with unk00F	(rot?)
		EncodedID	newCellOrWorldspaceID;	// 01C	goes into unk008
		int16_t		coordX;					// 01E	goes into unk00C
		int16_t		coordY;					// 020	goes into unk010, Null goes into unk004 and byt02C
	};

	struct Data00  // Every other cases (no data)
	{};

	union Data {
		Data00	data00;
		Data01	data01;
		Data02	data02;
		Data03	data03;
		Data04	data04;
		Data05	data05;
		Data06	data06;
	};

	Data data;	// 00
};

struct PreloadCELLdata	// Unpacked and decoded version of Data01, 02 end 03
{
	uint32_t	worldspaceID;	// 000
	int32_t	coordX;			// 004
	int32_t	coordY;			// 008
	uint32_t	detachTime;		// 00C
};

struct PreloadREFRdata	// Unpacked and decoded version of Data04, 05 and 06
{
	uint32_t	cellOrWorldspaceID;		// 000
	uint32_t	baseFormID;				// 004
	uint32_t	newCellOrWorldspaceID;	// 008
	int32_t	coordX;					// 00C
	int32_t	coordY;					// 010
	float	posXcoordX;				// 014
	float	posYcoordY;				// 018
	float	posZ;					// 01C
	float	rotX;					// 020
	float	rotY;					// 024
	float	rotZ;					// 028
	uint8_t	flg02C;					// 02C
};

union preloadData {
	PreloadCELLdata	cell;
	PreloadREFRdata	refr;
};

class BGSLoadGameBuffer {
public:
	BGSLoadGameBuffer();
	~BGSLoadGameBuffer();

	virtual uint8_t			GetSaveFormVersion(void);	// replaced in descendant
	virtual TESForm* getForm(void);				// only implemented in descendants
	virtual TESObjectREFR* getREFR(void);				// only implemented in descendants
	virtual Actor* getActor(void);				// only implemented in descendants

	char* chunk;			// 004
	uint32_t	chunkSize;		// 008
	uint32_t	chunkConsumed;	// 00C
};

struct BGSFormChanges {
	uint32_t	changeFlags;
	uint32_t	unk004;			// Pointer to the changed record or the save record ?
};

struct	BGSSaveLoadChangesMap {
	NiTPointerMap<uint32_t, BGSFormChanges*> kChangeMap;
};

// 030
class BGSLoadFormBuffer : public BGSLoadGameBuffer {
public:
	BGSLoadFormBuffer();
	~BGSLoadFormBuffer();

	typedef uint8_t EncodedID[3];
	struct Header	// 00C
	{
		EncodedID	encodeID;			// 00
		uint32_t		changeFlags;		// 03
		uint8_t		codedTypeAndLength;	// 07
		uint8_t		formVersion;		// 08
		uint8_t		pad009[3];			// 09
	};

	uint32_t			refID;				// 010
	Header			header;				// 014
	uint32_t			bufferSize;			// 020
	TESForm* form;				// 024
	uint32_t			flg028;				// 028	bit1 form invalid
	BGSFormChanges* currentFormChange;	// 02C
};

class BGSSaveFormBuffer : public BGSLoadGameBuffer {
	BGSSaveFormBuffer();
	~BGSSaveFormBuffer();
};	// in BGSSaveGameBuffer there is a 010, which look like a counter (ChunkCount ?), then the Header

#if 1
const uint32_t _SaveGameManager_ConstructSavegameFilename = 0x0084FF90;
const uint32_t _SaveGameManager_ConstructSavegamePath = 0x0084FF30;
#elif EDITOR
#else
#error
#endif

class BGSCellNumericIDArrayMap : public NiTMap<uint32_t, BSSimpleArray<uint32_t>*> {
public:
};

class BGSLoadGameSubBuffer;
class BGSReconstructFormsInFileMap;
class BGSReconstructFormsInAllFilesMap;
class BGSSaveLoadFormIDMap;
class BGSSaveLoadQueuedSubBufferMap;
class BGSSaveLoadHistory;

class BGSSaveLoadGame	// 0x011DDF38
{
public:
	BGSSaveLoadGame();
	~BGSSaveLoadGame();

	typedef uint32_t	RefID;
	typedef uint32_t	IndexRefID;
	struct RefIDIndexMapping	// reversible map between refID and loaded form index
	{
		NiTMap<RefID, IndexRefID>* map000;	// 000
		NiTMap<IndexRefID, RefID>* map010;	// 010
		uint32_t			            countRefID;	// 020
	};

	struct SaveChapters	// 06E	chapter table in save
	{
		struct RefIDArray	// List of all refID referenced in save for tranlation in RefIDIndexMapping
		{
			uint32_t	count;	// 000
			RefID	IDs[1];	// 004
		};

		RefIDArray* arr000;	// 000
		RefIDArray* arr004;	// 004
	};

	struct BGSSaveLoadReferencesMap {
		NiTPointerMap<uint32_t, uint32_t>					kMovedReferencesMap;
		BGSCellNumericIDArrayMap							kInteriorReferencesMap;
		NiTPointerMap<uint32_t, BGSCellNumericIDArrayMap*>	kWorldspaceReferencesMap;
	};

	struct ALIGN4 _GlobalFlags {
		enum Flags : uint32_t {
			GLOBAL_BLOCK_CHANGES	= 1u << 0,
			SAVE_GAME_LOADING		= 1u << 1,
			SAVE_GAME_SAVING		= 1u << 2,
			INITING_FORMS			= 1u << 3,
			DEFER_INIT_FORMS		= 1u << 4,
			POSITIONING_PLAYER		= 1u << 5,
			PLAYER_LOCATION_INVALID = 1u << 6,
			SAVE_LOAD_FAILED		= 1u << 7,
		};

		bool bGlobalBlockChanges	: 1;
		bool bSaveGameLoading		: 1;
		bool bSaveGameSaving		: 1;
		bool bInitingForms			: 1;
		bool bDeferInitForms		: 1;
		bool bPositioningPlayer		: 1;
		bool bPlayerLocationInvalid : 1;
		bool bSaveLoadFailed		: 1;
	};
	using GlobalFlags = _GlobalFlags::Flags;

	BGSSaveLoadChangesMap*					pChangesMap;
	BGSSaveLoadChangesMap*					pOldChangesMap;
	BGSSaveLoadFormIDMap*					pFormIDMap;
	BGSSaveLoadFormIDMap*					pWorldspaceFormIDMap;
	BGSSaveLoadReferencesMap*				pReferencesMap;
	BGSSaveLoadQueuedSubBufferMap*			pQueuedSubBuffersMap;
	NiTMap<uint32_t, uint32_t>*				pChangedFormIDMap;
	BGSSaveLoadHistory*						pHistory;
	BGSReconstructFormsInAllFilesMap*		pReconstructForms;
	BSSimpleArray<BGSLoadFormBuffer*>		kChangedForms;
	NiTMap<uint32_t, Actor*>				kQueuedInitPackageLocationsActorMap;
	uint8_t									ucSaveMods[255];
	uint8_t									ucLoadedMods[255];
	Bitfield<_GlobalFlags>					uiGlobalFlags;
	uint8_t									ucCurrentMinorVersion;

	static BGSSaveLoadGame* GetSingleton() {
		return *reinterpret_cast<BGSSaveLoadGame**>(0x11DDF38);
	}

	bool GetSaveGameLoading() const {
		return uiGlobalFlags.bSaveGameLoading;
	}
};

ASSERT_SIZE(BGSSaveLoadGame, 0x24C);

#if RUNTIME
class SaveGameManager {
public:
	SaveGameManager();
	~SaveGameManager();

	static SaveGameManager* GetSingleton();
	MEMBER_FN_PREFIX(SaveGameManager);
	DEFINE_MEMBER_FN(ConstructSavegameFilename, void, _SaveGameManager_ConstructSavegameFilename,
		const char* filename, char* outputBuf, bool bTempFile);
	DEFINE_MEMBER_FN(ConstructSavegamePath, void, _SaveGameManager_ConstructSavegamePath, char* outputBuf);

	struct SaveGameData {
		const char* name;		// 00
		uint32_t		unk04;		// 04
		uint32_t		saveNumber;	// 08 index?
		const char* pcName;	// 0C
		const char* pcTitle;	// 10
		const char* location;	// 14
		const char* time;		// 18
	};

	tList<SaveGameData>* saveList;		// 00
	uint32_t					numSaves;		// 04
	uint32_t					unk08;			// 08
	uint8_t					unk0C;			// 0C	flag for either opened or writable or useSeparator (|)
	uint8_t					unk0D;
	uint8_t					unk0E;
	uint8_t					unk0F;
	/*
		const char				* unk10;		// 10 name of most recently loaded/saved game?
		uint32_t					unk14;			// 14 init to -1
		uint8_t					unk18;			// 18
		uint8_t					pad19[3];
		uint8_t					unk20;			// 20 init to 1
		uint8_t					unk21;
		uint8_t					pad22[2];
		uint32_t					unk24;			// 24
		uint32_t					unk28;			// 28
	*/
};

std::string GetSavegamePath();

#endif

enum Coords {
	kCoords_X = 0,	// 00
	kCoords_Y,		// 01
	kCoords_Z,		// 02
	kCoords_Max		// 03
};

struct NavMeshVertex {
	float coords[kCoords_Max];	// 000
};	// 00C

enum Vertices {
	kVertices_0 = 0,	// 00
	kVertices_1,		// 01
	kVertices_2,		// 02
	kVertices_Max		// 03
};

enum Sides {
	kSides_0_1 = 0,	// 00
	kSides_1_2,		// 01
	kSides_2_0,		// 02
	kSides_Max		// 03
};

struct NavMeshTriangle {
	enum Flags {
		DISABLED = 0x20,
	};

	int16_t		sVertices[3];
	int16_t		sSides[3];
	uint32_t	uiFlags;
};	// Alloc'd by 0x10

class NavMeshInfo;

struct EdgeExtraInfo {
	struct Connection {
		NavMeshInfo* pNavMeshInfo;
		int16_t			sTriangle;
	};

	int32_t		unk000;
	Connection	kConnectTo;
};	// Alloc'd by 0x0C

struct NavMeshTriangleDoorPortal {
	TESObjectREFR* door;	// 00
	uint16_t			unk004;	// 04
	uint16_t			pad006;	// 06
};	// Alloc'd to 0x08

struct NavMeshCloseDoorInfo {
	uint32_t	unk000;	// 00
	uint32_t	unk004;	// 04
};	// Alloc'd to 0x08

struct NavMeshPOVData;
class ObstacleData;
struct ObstacleUndoData;

struct NavMeshStaticAvoidNode {
	uint32_t	unk000;	// 00
	uint32_t	unk004;	// 04
	uint32_t	unk008;	// 08
	uint32_t	unk00C;	// 0C
	uint32_t	unk010;	// 10
	uint32_t	unk014;	// 14
	uint32_t	unk018;	// 18
	uint32_t	unk01C;	// 1C
	uint32_t	unk020;	// 20
	uint32_t	unk024;	// 24
};	// Alloc'd to 0x28
