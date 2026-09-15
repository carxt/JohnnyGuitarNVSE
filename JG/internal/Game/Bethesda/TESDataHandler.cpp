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

	uint32_t i = 0;
	if (auiIndex) {
		while (true) {
			pIter = pIter->GetNext();
			if (!pIter)
				break;

			if (pIter->GetItem() && ++i < auiIndex)
				continue;

			return pIter->GetItem();
		}
	}
	else {
		if (pIter)
			return pIter->GetItem();
	}

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

	BSSimpleList<TESFile*>* pIter = GetFileList();
	while (pIter && pIter->GetItem()) {
		TESFile* pFile = pIter->GetItem();
		if (pFile && !_stricmp(pFile->GetName(), apFileName))
			return pFile;

		pIter = pIter->GetNext();
	}

	return nullptr;
#endif
}

uint32_t TESDataHandler::GetCompiledFileCount() const {
	return kCompiledFiles.GetFileCount();
}

// GAME - 0x465010
// GECK - 0x4CDFA0
TESFile* TESDataHandler::GetCompiledFile(uint32_t auiIndex) const {
	return kCompiledFiles.GetFile(auiIndex);
}

TESFile* TESDataHandler::GetCompiledFileForFormID(uint32_t auiFormID) const {
	const uint8_t ucIndex = FormID_View(auiFormID).GetCompileIndex();
	if (ucIndex == 0xFF)
		return nullptr;

#if ESL_SUPPORT
	if (ucIndex == 0xFE && SupportsSmallPugins()) {
		const uint16_t usSmallIndex = FormID_View(auiFormID).GetSmallIndex();
		return kCompiledFiles.GetSmallFile(usSmallIndex);
	}
#endif
	return kCompiledFiles.GetFile(ucIndex);
}

#if ESL_SUPPORT
uint32_t TESDataHandler::GetSmallCompiledFileCount() const {
	if (SupportsSmallPugins())
		return kCompiledFiles.GetSmallFileCount();
	return 0;
}

TESFile* TESDataHandler::GetSmallFile(uint32_t auiIndex) const {
	if (SupportsSmallPugins())
		return kCompiledFiles.GetSmallFile(auiIndex);
	return nullptr;
}
#endif

#if OVERLAY_SUPPORT
uint32_t TESDataHandler::GetOverlayFileCount() const {
	if (SupportsOverlayPugins())
		return kCompiledFiles.GetOverlayFileCount();
	return 0;
}

TESFile* TESDataHandler::GetOverlayFile(uint32_t auiIndex) const {
	if (SupportsOverlayPugins())
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
#if ESL_SUPPORT || OVERLAY_SUPPORT
	if (TESDataHandler::HasExtendedPlugins())
		return kNormalFiles.GetSize();

	return uiCompiledFileCount;
#else
	return uiCompiledFileCount;
#endif
}

TESFile* __fastcall CompiledFiles::GetFile(uint32_t auiIndex) const {
	ASSUME_ASSERT(auiIndex < 0xFF);
#if ESL_SUPPORT || OVERLAY_SUPPORT
	if (auiIndex >= GetFileCount())
		return nullptr;

	if (TESDataHandler::HasExtendedPlugins())
		return kNormalFiles.GetAt(auiIndex);

	return pFileArray[auiIndex];
#else
	return pFileArray[auiIndex];
#endif
}

#if ESL_SUPPORT
uint32_t __fastcall CompiledFiles::GetSmallFileCount() const {
	assert(TESDataHandler::HasExtendedPlugins());
	return kSmallFiles.GetSize();
}

TESFile* __fastcall CompiledFiles::GetSmallFile(uint32_t auiIndex) const {
	assert(TESDataHandler::HasExtendedPlugins());
	if (auiIndex >= GetSmallFileCount())
		return nullptr;

	return kSmallFiles.GetAt(auiIndex);
}
#endif

#if OVERLAY_SUPPORT
uint32_t __fastcall CompiledFiles::GetOverlayFileCount() const {
	assert(TESDataHandler::HasOverlayPluginSupport());
	return kOverlayFiles.GetSize();
}

TESFile* __fastcall CompiledFiles::GetOverlayFile(uint32_t auiIndex) const {
	assert(TESDataHandler::HasOverlayPluginSupport());
	if (auiIndex >= GetOverlayFileCount())
		return nullptr;

	return kOverlayFiles.GetAt(auiIndex);
}
#endif

#if ESL_SUPPORT || OVERLAY_SUPPORT
void CompiledFiles::Initialize() {
	new (&kNormalFiles) BSSimpleArray<TESFile*>(0, 0);

	new (&kSmallFiles) BSSimpleArray<TESFile*>(0, 0);

	new (&kOverlayFiles) BSSimpleArray<TESFile*>(0, 0);

	memset(padding, 0xDEADBEEF, sizeof(padding));
}
#endif