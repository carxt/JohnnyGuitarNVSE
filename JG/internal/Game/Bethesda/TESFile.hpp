#pragma once

#include "BSSimpleList.hpp"
#include "BSStringT.hpp"
#include "Gamebryo/NiTPointerMap.hpp"

class TESObjectCELL;
class TESForm;
class BSFile;

struct FORM {
	FORM() { ZeroMemory(this, sizeof(FORM)); }

	uint32_t	uiRecordType;
	uint32_t	uiDataSize;
	Bitfield32	uiFormFlags;
	uint32_t	uiFormID;
	uint32_t	uiVersionControl;
	uint16_t	usFormVersion;
	uint16_t	usVCVersion;
};

struct FORM_GROUP {
	FORM		kGroupInfo;
	uint32_t	uiGroupOffset;
};

class TESFile {
public:
	struct FileHeader {
		FileHeader() : fVersion(1.34f), uiRecordCount(0), uiNextFormID(0x800) {}

		float		fVersion;
		uint32_t	uiRecordCount;
		uint32_t	uiNextFormID;
	};

	struct ALIGN4 _FileFlags {
		enum Flags : uint32_t{
			MASTER			= 1u << 0,
			ALTERED			= 1u << 1,
			CHECKED			= 1u << 2,
			ACTIVE			= 1u << 3,
			OPTIMIZED		= 1u << 4,
			TEMP_ID_OWNER	= 1u << 5,
			ENDIAN_SWAPPED	= 1u << 6,
			LOCALIZED		= 1u << 7,
			SMALL			= 1u << 8,
			OVERLAY 		= 1u << 9,
		};

		bool bMaster		: 1;
		bool bAltered		: 1;
		bool bChecked		: 1;
		bool bActive		: 1;
		bool bOptimized		: 1;
		bool bTempIDOwner	: 1;
		bool bEndianSwapped : 1;
		bool bLocalized		: 1;
		bool bSmall			: 1;
		bool bOverlay		: 1;
	};
	using FileFlags = _FileFlags::Flags;

	uint32_t							eLastError;
	TESFile*							pThreadSafeParent;
	NiTPointerMap<uint32_t, TESFile*>*	pThreadSafeFileMap;
	BSFile*								pLockedFile;
	BSFile*								pFile;
	struct TESBitArrayFile*				pFormUserDataBitArray;
	struct TESBitArrayFile*				pFormVersionBitArray;
	struct TESBitArrayFile*				pFormIDBitArray;
	char								cFilename[260];
	char								cPath[260];
	char*								pBuffer;
	uint32_t							uiBufferAllocSize;
	uint32_t							uiFirstCellOffset;
	uint32_t							uiCurrCellOffset;
	TESObjectCELL*						pCurrCell;
	uint32_t							uiCurrRefOffset;
	FORM								kCurrentForm;
	uint32_t							eCurrentChunkID;
	uint32_t							uiActualChunkSize;
	uint32_t							uiFileSize;
	uint32_t							uiFileOffset;
	uint32_t							uiFormOffset;
	uint32_t							uiChunkOffset;
	FORM								kSaveForm;
	uint32_t							uiSaveFormOffset;
	uint32_t							uiSaveChunkOffset;
	BSSimpleList<FORM_GROUP*>			kGroupList;
	bool								bHasGroups;
	bool								bMustEndianConvert;
	bool								bCloseFileOverride;
	WIN32_FIND_DATAA					kFileData;
	FileHeader							kHeader;
	Bitfield<_FileFlags>				uiFlags;
	BSSimpleList<const char*>			kListMasters;
	BSSimpleList<const FILETIME*>		kMastersData;
	uint32_t							uiMasterCount;
	TESFile**							ppMasters;
	_FILETIME							kDeletedFormTime;
	uint8_t								ucCompileIndex;
	BSString							strAuthor;
	BSString							strDescription;
	void*								pDecompressedFormBuffer;
	uint32_t							uiDecompressedFormBufferSize;
#ifdef GAME
	bool								bMaybeShouldBeReloaded;
#else
	TESFile*							pUnkTESFile_428;
	bool								bMaybeShouldBeReloaded;
	uint32_t*							pOwnedForms;
	uint32_t							uiOwnedFormCount;
#endif

	const char* GetName() const { return cFilename; }

	TESFile* GetThreadSafeFile();

	TESFile* GetThreadSafeParent() const;

	bool IsMaster() const;
};

ASSERT_SIZE(WIN32_FIND_DATA, 0x140);
#ifdef GAME
ASSERT_SIZE(TESFile, 0x42C);
#else
ASSERT_SIZE(TESFile, 0x438);
#endif

typedef TESFile ModInfo;