#pragma once

#include "GameTypes.h"
#include "GameScript.h"
#include <string>

#include "Bethesda/BSArchive.hpp"
#include "Bethesda/BSFileEntry.hpp"
#include "Bethesda/BSCriticalSection.hpp"

struct ParamInfo;
class TESForm;
class TESObjectREFR;
class BaseExtraList;

const uint32_t kMaxMessageLength = 0x4000;

struct ScriptVar {
	uint32_t		id;
	void* next;
	double		data;
};

// only records individual objects if there's a block that matches it
// ### how can it tell?
class ScriptLocals {
public:
	enum {
		kEvent_OnAdd = 1,
		kEvent_OnEquip = 2,
		kEvent_OnActorEquip = 2,
		kEvent_OnDrop = 4,
		kEvent_OnUnequip = 8,
		kEvent_OnActorUnequip = 8,

		kEvent_OnDeath = 0x10,
		kEvent_OnMurder = 0x20,
		kEvent_OnCombatEnd = 0x40,			// See 0x008A083C
		kEvent_OnHit = 0x80,			// See 0x0089AB12

		kEvent_OnHitWith = 0x100,			// TESObjectWEAP*	0x0089AB2F
		kEvent_OnPackageStart = 0x200,
		kEvent_OnPackageDone = 0x400,
		kEvent_OnPackageChange = 0x800,

		kEvent_OnLoad = 0x1000,
		kEvent_OnMagicEffectHit = 0x2000,			// EffectSetting* 0x0082326F
		kEvent_OnSell = 0x4000,			// 0x0072FE29 and 0x0072FF05, linked to 'Barter Amount Traded' Misc Stat
		kEvent_OnStartCombat = 0x8000,

		kEvent_OnOpen = 0x10000,		// while opening some container, not all
		kEvent_OnClose = 0x20000,
		kEvent_SayToDone = 0x40000,		// in Func0050 0x005791C1 in relation to SayToTopicInfo (OnSayToDone? or OnSayStart/OnSayEnd?)
		kEvent_OnGrab = 0x80000,		// 0x0095FACD and 0x009604B0 (same func which is called from PlayerCharacter_func001B and 0021)

		kEvent_OnRelease = 0x100000,		// 0x0047ACCA in relation to container
		kEvent_OnDestructionStageChange = 0x200000,		// 0x004763E7/0x0047ADEE
		kEvent_OnFire = 0x400000,		// 0x008BAFB9 (references to package use item and use weapon are close)

		kEvent_OnTrigger = 0x10000000,		// 0x005D8D6A	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerEnter = 0x20000000,		// 0x005D8D50	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerLeave = 0x40000000,		// 0x0062C946	OnTriggerLeave ?
		kEvent_OnReset = 0x80000000		// 0x0054E5FB
	};

	struct Event {
		TESForm* object;
		uint32_t		eventMask;
	};

	struct Struct10 {
		bool	effectStart;
		bool	effectFinish;
		uint8_t	unk03[6];
	};

	typedef tList<Event> EventList;
	typedef tList<ScriptVar> VarList;

	Script* m_script;		// 00
	uint32_t			m_unk1;			// 04
	EventList* m_eventList;	// 08
	VarList* m_vars;		// 0C
	Struct10* unk010;		// 10

	ScriptVar* GetVariable(uint32_t id);
};

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
	uint32_t	m_uiCurrentFilePos;	// 01C
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

class BSHash;
class ArchiveFile;

// 1D0
class Archive : public BSFile, public NiRefObject, public BSArchive {
public:
	Archive();
	~Archive();

	struct ALIGN1 _ArchiveFlags {
		enum Flags : uint8_t {
			DISABLED				= 1u << 0,
			PRIMARY					= 1u << 2,
			SECONDARY				= 1u << 3,
			HAS_DIRECTORY_STRINGS	= 1u << 4,
			HAS_FILE_STRINGS		= 1u << 5,
		};

		bool bDisabled				: 1;
		bool						: 1;
		bool bPrimary				: 1;
		bool bSecondary				: 1;
		bool bHasDirectoryStrings	: 1;
		bool bHasFileStrings		: 1;
	};
	using ArchiveFlags = _ArchiveFlags::Flags;

	time_t					ulArchiveFileTime;
	uint32_t				uiFileNameArrayOffset;
	uint32_t				uiLastDirectoryIndex;
	uint32_t				uiLastFileIndex;
	BSCriticalSection		kArchiveCriticalSection;
	Bitfield<_ArchiveFlags>	ucArchiveFlags;
	char*					pDirectoryStringArray;
	uint32_t*				pDirectoryStringOffsets;
	char*					pFileNameStringArray;
	uint32_t**				pFileNameStringOffsets;
	uint32_t				uiID;

	bool IsType(ARCHIVE_TYPE aeArchiveType) const {
		return usArchiveType.Get(aeArchiveType);
	}

	bool IsType(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex) const {
		return usArchiveType.GetBit(aeArchiveTypeIndex);
	}

	void SetHasDirectoryStrings(bool abHasDirectoryStrings) {
		ucArchiveFlags.bHasDirectoryStrings = abHasDirectoryStrings;
	}

	bool GetHasDirectoryStrings() const {
		return ucArchiveFlags.bHasDirectoryStrings;
	}

	void SetHasFileStrings(bool abHasFileStrings) {
		ucArchiveFlags.bHasFileStrings = abHasFileStrings;
	}

	bool GetHasFileStrings() const {
		return ucArchiveFlags.bHasFileStrings;
	}

	const char* GetFileNameForFileEntry(BSFileEntry* apFileEntry) {
#ifdef GAME
		return ThisCall<const char*>(0xAF9BA0, this, apFileEntry);
#else
		return ThisCall<const char*>(0x8A8580, this, apFileEntry);
#endif
	}

	bool FindFile(const BSHash& arDirectoryHash, const BSHash& arFileNameHash, uint32_t& arDirectoryID, uint32_t& arFileID, const char* apFileName) {
#ifdef GAME
		return ThisCall<bool>(0xAF9BF0, this, &arDirectoryHash, &arFileNameHash, &arDirectoryID, &arFileID, apFileName);
#else
		return ThisCall<bool>(0x8A85D0, this, &arDirectoryHash, &arFileNameHash, &arDirectoryID, &arFileID, apFileName);
#endif
	}

	ArchiveFile* GetFile(uint32_t auiDirectoryIndex, uint32_t auiFileIndex, uint32_t auiBufferSize, const char* apFileName) {
#ifdef GAME
		return ThisCall<ArchiveFile*>(0xAFA550, this, auiDirectoryIndex, auiFileIndex, auiBufferSize, apFileName);
#else
		return ThisCall<ArchiveFile*>(0x8A8F30, this, auiDirectoryIndex, auiFileIndex, auiBufferSize, apFileName);
#endif
	}

	BSFileEntry* GetFileEntryForFile(const BSHash& arDirectoryHash, const BSHash& arFileNameHash, const char* apFileName) {
#ifdef GAME
		return ThisCall<BSFileEntry*>(0xAFA6E0, this, &arDirectoryHash, &arFileNameHash, apFileName);
#else
		return ThisCall<BSFileEntry*>(0x8A90C0, this, &arDirectoryHash, &arFileNameHash, apFileName);
#endif
	}

	const char* GetDirectoryString(uint32_t auiDirectoryIndex) {
#ifdef GAME
		return ThisCall<const char*>(0xAF94C0, this, auiDirectoryIndex);
#else
		return ThisCall<const char*>(0x8A7EA0, this, auiDirectoryIndex);
#endif
	}

	const char* GetFileString(uint32_t auiDirectoryIndex, uint32_t auiFileIndex) {
#ifdef GAME
		return ThisCall<const char*>(0xAF96D0, this, auiDirectoryIndex, auiFileIndex);
#else
		return ThisCall<const char*>(0x8A80B0, this, auiDirectoryIndex, auiFileIndex);
#endif
	}
};

static_assert(sizeof(Archive) == 0x1D0);

// 160
class ArchiveFile : public BSFile
{
public:
	ArchiveFile();
	~ArchiveFile();

	NiPointer<Archive>	spArchive;
	uint32_t			uiArchiveOffset;
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

enum Coords {
	kCoords_X = 0,	// 00
	kCoords_Y,		// 01
	kCoords_Z,		// 02
	kCoords_Max		// 03
};