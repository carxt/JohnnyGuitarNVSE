#include "fn_file.h"
#ifdef GAME
#include "GameSound.h"
#include <Bethesda/FileFinder.hpp>
#include <misc/misc.h>

bool Cmd_IsBSALoaded_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		char cFullPath[MAX_PATH];
		our_snprintf(cFullPath, sizeof(cFullPath), "DATA\\%s", cPath);
		DWORD* pArchive = CdeclCall<DWORD*>(0xAF5320, cFullPath); // ArchiveManager::GetArchiveByName
		if (pArchive)
			arResult = 1;
	}
	return true;
}

bool Cmd_StopSoundFile_Execute(COMMAND_ARGS) {
	CdeclCall(0x8304A0);
	arResult = 1;
	return true;
}
bool Cmd_PlaySoundFile_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	BOOL bForcePlay = 0;
	BOOL bLoop = 0;
	BOOL bPlayInMainMenu = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &bForcePlay, &bLoop, &bPlayInMainMenu) && cPath[0]) {
		int eType = bPlayInMainMenu > 0 ? 8 : 6;
		CdeclCall(0x8300C0, eType, cPath, 1000, bLoop, bForcePlay, 0.f, 0);
		arResult = 1;
	}
	return true;
}

bool __cdecl StandardizeTexturePath(const char* apInPath, char* apOutPath, uint32_t auiBufferSize) {
	return CdeclCall<bool>(0xAF4200, apInPath, apOutPath, auiBufferSize);
}

template <uint32_t N>
inline bool StandardizeTexturePath(const char* apInPath, char(&arOutPath)[N]) noexcept {
	return StandardizeTexturePath(apInPath, arOutPath, N);
}

bool Cmd_GetTextureMipMapCount_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		char cTexturePath[MAX_PATH];
		StandardizeTexturePath(cPath, cTexturePath);
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cTexturePath, NiFile::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			uint32_t uiMipCount = 0;
			pFile->Seek(0x1C, SEEK_CUR);
			pFile->Read(&uiMipCount, sizeof(uiMipCount));
			delete pFile;

			arResult = uiMipCount;

			if (IsConsoleMode())
				Console_Print("GetTextureMipMapCount >> %.f", arResult);
		}
	}
	return true;
}
bool Cmd_GetTextureFormat_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		char cTexturePath[MAX_PATH];
		StandardizeTexturePath(cPath, cTexturePath);
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cTexturePath, NiFile::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			char cFormat = 0;
			pFile->Seek(0x57, SEEK_CUR);
			pFile->Read(&cFormat, sizeof(cFormat));
			delete pFile;

			arResult = cFormat - '0';

			if (IsConsoleMode())
				Console_Print("GetTextureFormat >> %.f", arResult);
		}
	}
	return true;
}
bool Cmd_GetTextureWidth_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	uint32_t useDataTextures;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &useDataTextures) && cPath[0]) {
		char cTexturePath[MAX_PATH];
		StandardizeTexturePath(cPath, cTexturePath);
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cTexturePath, NiFile::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			uint32_t uiWidth = 0;
			pFile->Seek(0x10, SEEK_CUR);
			pFile->Read(&uiWidth, sizeof(uiWidth));
			delete pFile;

			arResult = uiWidth;

			if (IsConsoleMode()) 
				Console_Print("GetTextureWidth >> %.f", arResult);
		}
	}
	return true;
}

bool Cmd_GetTextureHeight_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		char cTexturePath[MAX_PATH];
		StandardizeTexturePath(cPath, cTexturePath);
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cTexturePath, NiFile::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			DWORD uiHeight = 0;
			pFile->Seek(0xC, SEEK_CUR);
			pFile->Read(&uiHeight, sizeof(uiHeight));
			delete pFile;

			arResult = uiHeight;

			if (IsConsoleMode()) 
				Console_Print("GetTextureHeight >> %.f", arResult);
		}
	}
	return true;
}

bool Cmd_MD5File_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	char cHash[0x21] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		if (strstr(cPath, "..\\")) 
			return true;

		char cFileName[MAX_PATH];
		GetModuleFileNameA(NULL, cFileName, MAX_PATH);

		char* pLastSlash = strrchr(cFileName, '\\') + 1;
		uint32_t uiLength = MAX_PATH - (pLastSlash - cFileName);
		strcpy_s(pLastSlash, uiLength, cPath);
		GetMD5File(cFileName, cHash);

		if (IsConsoleMode())
			Console_Print(cHash);

		g_strInterface->Assign(PASS_COMMAND_ARGS, cHash);
	}
	return true;
}

bool Cmd_SHA1File_Execute(COMMAND_ARGS) {;
	char cPath[MAX_PATH] = {};
	char cHash[0x29] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		if (strstr(cPath, "..\\")) 
			return true;

		char cFileName[MAX_PATH];
		GetModuleFileNameA(NULL, cFileName, MAX_PATH);

		char* pLastSlash = strrchr(cFileName, '\\') + 1;
		uint32_t uiLength = MAX_PATH - (pLastSlash - cFileName);
		strcpy_s(pLastSlash, uiLength, cPath);
		GetSHA1File(cFileName, cHash);

		if (IsConsoleMode())
			Console_Print(cHash);

		g_strInterface->Assign(PASS_COMMAND_ARGS, cHash);
	}
	return true;
}

bool Cmd_GetPixelFromBMP_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	char cRed[64], cGreen[64], cBlue[64];
	uint32_t uiWidth = 0, uiHeight = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &cRed, &cGreen, &cBlue, &uiWidth, &uiHeight) && cPath[0]) {
		char cFileName[MAX_PATH];
		GetModuleFileNameA(NULL, cFileName, MAX_PATH);

		char* pLastSlash = (char*)(strrchr(cFileName, '\\') + 1);
		uint32_t uiLength = MAX_PATH - (pLastSlash - cFileName);
		strcpy_s(pLastSlash, uiLength, cPath);

		DWORD uiRed = 0, uiGreen = 0, uiBlue = 0;
		if (ReadBMP24(cFileName, uiRed, uiGreen, uiBlue, uiWidth, uiHeight)) {
			setVarByName(PASS_VARARGS, cRed, uiRed);
			setVarByName(PASS_VARARGS, cGreen, uiGreen);
			setVarByName(PASS_VARARGS, cBlue, uiBlue);
		}
	}
	return true;
}

bool Cmd_PlaySoundFromPath_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	BOOL bVoice = FALSE;
	BOOL bSystemSound = FALSE;
	BOOL bLoop = FALSE;
	BOOL bDontCache = FALSE;
	float fFadeInTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeInTime, &bVoice, &bSystemSound, &bLoop, &bDontCache) && cPath[0]) {
		const bool bVoiceFlag = (bVoice > 0);
		const bool bSystemFlag = (bSystemSound > 0);
		const bool bLoopFlag = (bLoop > 0);
		uint32_t uiSoundFlags = BSAudioManager::kAudioFlags_2D | BSAudioManager::kAudioFlags_100;
		if (bVoiceFlag)
			uiSoundFlags |= BSAudioManager::kAudioFlags_IsVoice;

		if (bSystemFlag)
			uiSoundFlags |= BSAudioManager::kAudioFlags_SystemSound;

		if (bLoopFlag)
			uiSoundFlags |= BSAudioManager::kAudioFlags_Loop;

		if (bDontCache)
			uiSoundFlags |= BSAudioManager::kAudioFlags_DontCache;

		BSSoundHandle kHandle = BSAudio::GetSingleton()->GetSoundHandleByFilePath(cPath, BSAudioManager::AudioFlags(uiSoundFlags), nullptr);
		if (fFadeInTime <= 0.f) {
			kHandle.Play(false);
		}
		else {
			kHandle.FadeInPlay(fFadeInTime * 1000);
		}
		arResult = 1;
	}
	return true;
}

bool Cmd_PlaySound3DFromPath_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	BOOL bVoice = FALSE;
	BOOL bLoop = FALSE;
	BOOL bDontCache = FALSE;
	float fFadeInTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeInTime, &bVoice, &bLoop, &bDontCache) && cPath[0]) {
		TESObjectREFR* pRef = apRef;
		if (!pRef)
			pRef = PlayerCharacter::GetSingleton();

		if (pRef->Get3DVerySimple()) {
			const bool bVoiceFlag = (bVoice > 0);
			const bool bLoopFlag = (bLoop > 0);
			uint32_t uiSoundFlags = BSAudioManager::kAudioFlags_3D | BSAudioManager::kAudioFlags_100;
			if (bVoiceFlag)
				uiSoundFlags |= BSAudioManager::kAudioFlags_IsVoice;

			if (bLoopFlag)
				uiSoundFlags |= BSAudioManager::kAudioFlags_Loop;

			if (bDontCache)
				uiSoundFlags |= BSAudioManager::kAudioFlags_DontCache;

			BSSoundHandle kHandle = BSAudio::GetSingleton()->GetSoundHandleByFilePath(cPath, BSAudioManager::AudioFlags(uiSoundFlags), nullptr);
			kHandle.SetPosition(pRef->GetPosition());
			kHandle.SetObjectToFollow(pRef->Get3DVerySimple());
			if (fFadeInTime <= 0) {
				kHandle.Play(false);
			}
			else {
				kHandle.FadeInPlay(fFadeInTime * 1000);
			}
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_StopSoundFromPath_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	float fFadeOutTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeOutTime) && cPath[0]) {
		CSLock kLock(BSAudioManager::Get()->kMessageProcessingCS);
		BSGameSound* pSound;
		uint32_t uiKey;
		auto kIter = BSAudioManager::Get()->playingSounds.GetFirstPos();
		while (kIter) {
			BSAudioManager::Get()->playingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->cFilePath, cPath) == 0) {
				BSSoundHandle kHandle;
				kHandle.uiSoundID = pSound->mapKey;

				if (fFadeOutTime <= 0) {
					kHandle.Stop();
				}
				else {
					int time = fFadeOutTime * 1000.0;
					kHandle.FadeOutAndRelease(time);
				}
				arResult = 1;
			}
		}
	}
	return true;
}

bool Cmd_StopSound3DFromPath_Execute(COMMAND_ARGS) {
	char path[MAX_PATH] = {};
	float fadeOutTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &fadeOutTime) && path[0]) {
		TESObjectREFR* ref = apRef;
		if (ref == nullptr)
			ref = PlayerCharacter::GetSingleton();

		CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
		BSGameSound* pSound;
		uint32_t uiKey;
		auto kIter = BSAudioManager::Get()->playingSounds.GetFirstPos();
		while (kIter) {
			BSAudioManager::Get()->playingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->cFilePath, path) == 0) {
				NiPointer<NiAVObject> spObj;
				if (!BSAudioManager::Get()->soundPlayingObjects.GetAt(pSound->mapKey, spObj) || !spObj->IsFadeNode())
					continue;

				if (static_cast<BSFadeNode*>(spObj.m_pObject)->GetReference() == ref) {
					BSSoundHandle kHandle(pSound->mapKey);
					if (fadeOutTime <= 0) {
						kHandle.Stop();
					}
					else {
						int time = fadeOutTime * 1000.0;
						kHandle.FadeOutAndRelease(time);
					}
					arResult = 1;
				}
			}
		}
	}
	return true;
}

bool Cmd_IsSoundPlayingFromPath_Execute(COMMAND_ARGS) {
	char path[MAX_PATH] = {};
	TESObjectREFR* ref = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &ref) && path[0]) {
		CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
		BSGameSound* pSound = nullptr;
		uint32_t uiKey;
		auto kIter = BSAudioManager::Get()->playingSounds.GetFirstPos();
		if (ref == nullptr) {
			while (kIter) {
				BSAudioManager::Get()->playingSounds.GetNext(kIter, uiKey, pSound);
				if (pSound && _stricmp(pSound->cFilePath, path) == 0) {
					arResult = 1;
					return true;
				}
			}
		}
		else {
			NiPointer<NiAVObject> spObject;
			auto kObjIter = BSAudioManager::Get()->soundPlayingObjects.GetFirstPos();
			while (kObjIter) {
				BSAudioManager::Get()->soundPlayingObjects.GetNext(kObjIter, uiKey, spObject);
				if (!spObject || !spObject->IsFadeNode())
					continue;

				BSFadeNode* pFadeNode = static_cast<BSFadeNode*>(spObject.m_pObject);
				if (pFadeNode->GetReference() != ref)
					continue;

				if (BSAudioManager::Get()->playingSounds.GetAt(uiKey, pSound) && pSound && _stricmp(pSound->cFilePath, path) == 0) {
					arResult = 1;
					return true;
				}
			}
		}
	}
	return true;
}
#endif