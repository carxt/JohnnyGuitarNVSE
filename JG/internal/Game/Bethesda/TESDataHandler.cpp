#include "TESDataHandler.hpp"

TESDataHandler* TESDataHandler::GetSingleton() {
#ifdef GAME
    return *reinterpret_cast<TESDataHandler**>(0x11C3F2C);
#else
	return *reinterpret_cast<TESDataHandler**>(0xED3B0C);
#endif
}

// GAME - 0x45DFC0
BSSimpleList<TESFile*>* TESDataHandler::GetFileList() {
	return &kFiles;
}

// GAME - 0x45DFC0
const BSSimpleList<TESFile*>* TESDataHandler::GetFileList() const {
	return &kFiles;
}

// GECK - 0x4CF380
TESFile* TESDataHandler::GetListFile(uint32_t auiIndex) const {
#ifdef GAME
	const BSSimpleList<TESFile*>* pIter = GetFileList();
	for (uint32_t i = 0; i < auiIndex; ++i) {
		pIter = pIter->GetNext();
		if (!pIter || !pIter->GetItem())
			break;
	}

	if (pIter)
		return pIter->GetItem();
	return nullptr;
#else
	return ThisCall<TESFile*>(0x4CF380, this, auiIndex);
#endif
}

// GAME - 0x462F40
TESFile* TESDataHandler::GetListFile(const char* apFileName) const {
#ifdef GAME
	return ThisCall<TESFile*>(0x462F40, this, apFileName);
#else
	if (!apFileName)
		return nullptr;

	const BSSimpleList<TESFile*>* pIter = GetFileList();
	while (pIter && pIter->GetItem()) {
		TESFile* pFile = pIter->GetItem();
		if (pFile && !_stricmp(pFile->GetName(), apFileName))
			return pFile;

		pIter = pIter->GetNext();
	}

	return nullptr;
#endif
}

// GAME - 0x51F550
uint32_t TESDataHandler::GetCompiledFileCount() const {
	return kCompiledFiles.GetFileCount();
}

// GAME - 0x465010
// GECK - 0x4CDFA0
TESFile* TESDataHandler::GetCompiledFile(uint32_t auiIndex) const {
#ifdef GAME
	return ThisCall<TESFile*>(0x465010, this, auiIndex);
#else
	return ThisCall<TESFile*>(0x4CDFA0, this, auiIndex);
#endif
}

TESFile* TESDataHandler::GetCompiledFileForFormID(FormID auiFormID) const {
	const uint8_t ucIndex = FormID_View(auiFormID).GetCompileIndex();
	if (ucIndex == 0xFF)
		return nullptr;

#if TESFILE_NEW_TYPES
	if (SupportsNewFileTypes()) {
		if (ucIndex == 0xFD) {
			const uint8_t ucMediumIndex = FormID_View(auiFormID).GetMediumIndex();
			return kCompiledFiles.GetMediumFile(ucMediumIndex);
		}
		else if (ucIndex == 0xFE) {
			const uint16_t usSmallIndex = FormID_View(auiFormID).GetSmallIndex();
			return kCompiledFiles.GetSmallFile(usSmallIndex);
		}
	}
#endif
	return kCompiledFiles.GetFile(ucIndex);
}

#if TESFILE_NEW_TYPES
uint32_t TESDataHandler::GetSmallCompiledFileCount() const {
	if (SupportsNewFileTypes())
		return kCompiledFiles.GetSmallFileCount();
	return 0;
}

TESFile* TESDataHandler::GetSmallFile(uint32_t auiIndex) const {
	if (SupportsNewFileTypes())
		return kCompiledFiles.GetSmallFile(auiIndex);
	return nullptr;
}

uint32_t TESDataHandler::GetMediumCompiledFileCount() const {
	if (SupportsNewFileTypes())
		return kCompiledFiles.GetMediumFileCount();
	return 0;
}

TESFile* TESDataHandler::GetMediumFile(uint32_t auiIndex) const {
	if (SupportsNewFileTypes())
		return kCompiledFiles.GetMediumFile(auiIndex);
	return nullptr;
}

uint32_t TESDataHandler::GetOverlayFileCount() const {
	if (SupportsNewFileTypes())
		return kCompiledFiles.GetOverlayFileCount();
	return 0;
}

TESFile* TESDataHandler::GetOverlayFile(uint32_t auiIndex) const {
	if (SupportsNewFileTypes())
		return kCompiledFiles.GetOverlayFile(auiIndex);
	return nullptr;
}
#endif

// GAME - 0x740940
TESRegionDataManager* TESDataHandler::GetRegionDataManager() const {
	return pRegionDataManager;
}

// GAME - 0x4603B0
// GECK - 0x4DA6C0
bool TESDataHandler::AddFormToDataHandler(TESForm* apForm) {
#ifdef GAME
	return ThisCall<bool>(0x4603B0, this, apForm);
#else
	return ThisCall<bool>(0x4DA6C0, this, apForm);
#endif
}

uint32_t __fastcall CompiledFiles::GetFileCount() const {
#if TESFILE_NEW_TYPES
	if (TESDataHandler::HasNewFileTypeSupport())
		return kNormalFiles.GetSize();
#endif
	return uiCompiledFileCount;
}

TESFile* __fastcall CompiledFiles::GetFile(uint32_t auiIndex) const {
	if (auiIndex >= GetFileCount())
		return nullptr;

#if TESFILE_NEW_TYPES
	if (TESDataHandler::HasNewFileTypeSupport())
		return kNormalFiles.GetAt(auiIndex);
#endif
	return pFileArray[auiIndex];
}

#if TESFILE_NEW_TYPES
uint32_t __fastcall CompiledFiles::GetSmallFileCount() const {
	assert(TESDataHandler::HasNewFileTypeSupport());
	return kSmallFiles.GetSize();
}

TESFile* __fastcall CompiledFiles::GetSmallFile(uint32_t auiIndex) const {
	assert(TESDataHandler::HasNewFileTypeSupport());
	if (auiIndex >= GetSmallFileCount())
		return nullptr;

	return kSmallFiles.GetAt(auiIndex);
}

uint32_t __fastcall CompiledFiles::GetMediumFileCount() const {
	assert(TESDataHandler::HasNewFileTypeSupport());
	return kMediumFiles.GetSize();
}

TESFile* __fastcall CompiledFiles::GetMediumFile(uint32_t auiIndex) const {
	assert(TESDataHandler::HasNewFileTypeSupport());
	if (auiIndex >= GetMediumFileCount())
		return nullptr;

	return kMediumFiles.GetAt(auiIndex);
}

uint32_t __fastcall CompiledFiles::GetOverlayFileCount() const {
	assert(TESDataHandler::HasNewFileTypeSupport());
	return kOverlayFiles.GetSize();
}

TESFile* __fastcall CompiledFiles::GetOverlayFile(uint32_t auiIndex) const {
	assert(TESDataHandler::HasNewFileTypeSupport());
	if (auiIndex >= GetOverlayFileCount())
		return nullptr;

	return kOverlayFiles.GetAt(auiIndex);
}
#endif