#include "TESFile.hpp"

#if ESL_SUPPORT || OVERLAY_SUPPORT
#include "Shared/Utils/DebugLog.hpp"
#endif

// GAME - 0x4739B0
// GECK - 0x4E2E40
TESFile* TESFile::GetThreadSafeFile() {
#ifdef GAME
	return ThisCall<TESFile*>(0x4739B0, this);
#else
	return ThisCall<TESFile*>(0x4E2E40, this);
#endif
}

// GAME - 0x473C70
// GECK - 0x4DEA80
TESFile* TESFile::GetThreadSafeParent() const {
#ifdef GAME
	return ThisCall<TESFile*>(0x473C70, this);
#else
	return ThisCall<TESFile*>(0x4DEA80, this);
#endif
}

// GAME - 0x471A10
// GECK - 0x4DE2F0
TESFile* TESFile::GetIndexFile(uint32_t auiIndex) const {
#ifdef GAME
	return ThisCall<TESFile*>(0x471A10, this, auiIndex);
#else
	return ThisCall<TESFile*>(0x4DE2F0, this, auiIndex);
#endif
}

// GAME - 0x471C20
// GECK - 0x4DE370
bool TESFile::IsMaster() const {
	return uiFlags.bMaster;
}

void TESFile::SetMaster(bool abMaster) {
	uiFlags.bMaster = abMaster;
}

#if ESL_SUPPORT
bool TESFile::IsSmallFile() const {
	return uiFlags.bSmall;
}

void TESFile::SetSmallFile(bool abSmallFile) {
	uiFlags.bSmall = abSmallFile;
}
#endif

#if OVERLAY_SUPPORT
bool TESFile::IsOverlay() const {
	return uiFlags.bOverlay;
}

void TESFile::SetOverlay(bool abOverlay) {
	uiFlags.bOverlay = abOverlay;
}
#endif

// GAME - 0x473250
// GECK - 0x4DE700
uint8_t TESFile::GetCompileIndex() const {
#ifdef GAME
	return ucCompileIndex;
#else
	return ThisCall<uint8_t>(0x4DE700, this);
#endif
}

// GAME - 0x473210
// GECK - 0x4DE6D0
void TESFile::SetCompileIndex(uint8_t aucIndex) {
	kHeader.uiNextFormID = kHeader.uiNextFormID & 0xFFFFFF | (aucIndex << 24);
	ucCompileIndex = aucIndex;
}

uint16_t TESFile::GetSmallCompileIndex() const {
	return usSmallCompileIndex;
}

void TESFile::SetSmallCompileIndex(uint16_t ausIndex) {
	usSmallCompileIndex = ausIndex;
}

// GAME - 0x470C70
// GECK - 0x4E20A0
bool TESFile::OpenTES(uint32_t aeAccessMode, bool abLock) {
#ifdef GAME
	return ThisCall<bool>(0x470C70, this, aeAccessMode, abLock);
#else
	return ThisCall<bool>(0x4E20A0, this, aeAccessMode, abLock);
#endif
}

void TESFile::AdjustFormIDFileIndex(FormID& auiFormID) const {
	FormID_View& vFormID = reinterpret_cast<FormID_View&>(auiFormID);
	const TESFile* pIndexFile = this;
#if OVERLAY_SUPPORT
	if (IsOverlay()) {
		pIndexFile = GetIndexFile(1);
		if (!pIndexFile)
			pIndexFile = this;
		_MESSAGE("[ TESFile::AdjustFormIDFileIndex ] Overlay file %s - using %s master for %08X", this->GetName(), pIndexFile->GetName(), auiFormID);
	}
#endif

#if ESL_SUPPORT
	if (pIndexFile->IsSmallFile()) {
		vFormID.SetCompileIndex(0xFE);
		vFormID.SetSmallIndex(pIndexFile->GetSmallCompileIndex());
		if (!IsOverlay())
			_MESSAGE("[ TESFile::AdjustFormIDFileIndex ] Small file (%s): %08X", pIndexFile->GetName(), auiFormID);
		return;
	}
#endif

	const uint8_t ucIndex = pIndexFile->GetCompileIndex();
	vFormID.SetCompileIndex(ucIndex);
}

// GAME - 0x474060
TESFile* TESFile::GetFileForTempID(FormID auiTempID) {
	return CdeclCall<TESFile*>(0x474060, auiTempID);
}
