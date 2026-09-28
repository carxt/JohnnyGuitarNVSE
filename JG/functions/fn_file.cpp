#include "fn_file.h"
#include "Bethesda/BSAudio.hpp"
#include "Bethesda/BSGameSound.hpp"
#include "Bethesda/BSAudioManager.hpp"
#include "Bethesda/FileFinder.hpp"
#include "Bethesda/Interface.hpp"
#include "Bethesda/PlayerCharacter.hpp"

#include <misc/misc.h>
#include <utility.h>

#include <mutex>

bool Cmd_IsBSALoaded_Execute(COMMAND_ARGS) {
	char path[MAX_PATH] = {};
	char fixPath[MAX_PATH];
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path) && path[0]) {
		snprintf(fixPath, MAX_PATH, "DATA\\%s", path);
		DWORD* archive = CdeclCall<DWORD*>(0xAF5320, fixPath); // ArchiveManager::GetArchiveByName
		if (archive != nullptr) {
			*result = 1;
		}
	}
	return true;
}

bool Cmd_StopSoundFile_Execute(COMMAND_ARGS) {
	*result = 0;
	CdeclCall<void>(0x8304A0);
	*result = 1;
	return true;
}
bool Cmd_PlaySoundFile_Execute(COMMAND_ARGS) {
	char path[MAX_PATH] = {};
	*result = 0;
	uint32_t forcePlay = 0;
	uint32_t shouldLoop = 0;
	uint32_t playInMainMenu = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &forcePlay, &shouldLoop, &playInMainMenu) && path[0]) {
		int type = playInMainMenu > 0 ? 8 : 6;
		CdeclCall<void>(0x8300C0, type, path, 1000, shouldLoop, forcePlay, 0.0, 0);
		*result = 1;
	}
	return true;
}
void resolveTexturePath(char* path, uint32_t bufferSize) {
	if (StrBeginsCI(path, "data\\")) {
		strcpy_s(path, bufferSize, path + 5);

	}
	if (StrBeginsCI(path, "textures\\") == 0) {
		char fixPath[MAX_PATH];
		strcpy_s(fixPath, path);
		sprintf_s(path, bufferSize, "textures\\%s", fixPath);
	}
}

bool Cmd_GetTextureMipMapCount_Execute(COMMAND_ARGS) {
	*result = 0;
	char path[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path) && path[0]) {
		resolveTexturePath(path, sizeof(path));
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (file != nullptr) {
			DWORD mipMapCount = 0;
			file->Seek(0x1C, 1);
			file->DoRead(&mipMapCount, sizeof(mipMapCount));
			*result = mipMapCount;
			if (Script::GetConsoleOuput()) Interface::PrintLine("GetTextureMipMapCount >> %.f", *result);
			file->Destructor(true);
		}
	}
	return true;
}
bool Cmd_GetTextureFormat_Execute(COMMAND_ARGS) {
	*result = 0;
	char path[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path) && path[0]) {
		resolveTexturePath(path, sizeof(path));
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (file != nullptr) {
			char format = 0;
			file->Seek(0x57, 1);
			file->DoRead(&format, 1);
			*result = format - '0';
			if (Script::GetConsoleOuput()) Interface::PrintLine("GetTextureFormat >> %.f", *result);
			file->Destructor(true);
		}
	}
	return true;
}
bool Cmd_GetTextureWidth_Execute(COMMAND_ARGS) {
	*result = 0;
	char path[MAX_PATH] = {};
	//char fixPath[MAX_PATH];
	uint32_t useDataTextures = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &useDataTextures) && path[0]) {
		resolveTexturePath(path, sizeof(path));
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (file != nullptr) {
			DWORD width = 0;
			file->Seek(0x10, 1);
			file->DoRead(&width, sizeof(width));
			*result = width;
			if (Script::GetConsoleOuput()) Interface::PrintLine("GetTextureWidth >> %.f", *result);
			file->Destructor(true);
		}
	}
	return true;
}

bool Cmd_GetTextureHeight_Execute(COMMAND_ARGS) {
	*result = 0;
	char path[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path) && path[0]) {
		resolveTexturePath(path, sizeof(path));
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, ARCHIVE_TYPE::TEXTURES);
		if (file != nullptr) {
			DWORD height = 0;
			file->Seek(0x0C, 1);
			file->DoRead(&height, sizeof(height));
			*result = height;
			if (Script::GetConsoleOuput()) Interface::PrintLine("GetTextureHeight >> %.f", *result);
			file->Destructor(true);
		}
	}
	return true;
}

bool Cmd_MD5File_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH] = {};
	char outHash[0x21] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path) && path[0]) {
		if (strstr(path, "..\\")) return true;
		char* lastSlash = (char*)(strrchr(filename, '\\') + 1);
		uint32_t length = MAX_PATH - (lastSlash - filename);
		strcpy_s(lastSlash, length, path);
		GetMD5File(filename, outHash);
		if (Script::GetConsoleOuput())
			Interface::PrintLine(outHash);
		g_strInterface->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}

bool Cmd_SHA1File_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH] = {};
	char outHash[0x29] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path) && path[0]) {
		if (strstr(path, "..\\")) return true;
		char* lastSlash = (char*)(strrchr(filename, '\\') + 1);
		uint32_t length = MAX_PATH - (lastSlash - filename);
		strcpy_s(lastSlash, length, path);
		GetSHA1File(filename, outHash);
		if (Script::GetConsoleOuput())
			Interface::PrintLine(outHash);
		g_strInterface->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}

bool Cmd_GetPixelFromBMP_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH] = {};
	char RED[64], GREEN[64], BLUE[64];
	uint32_t width = 0, height = 0;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &RED, &GREEN, &BLUE, &width, &height) && path[0]) {
		char* lastSlash = (char*)(strrchr(filename, '\\') + 1);
		uint32_t length = MAX_PATH - (lastSlash - filename);
		strcpy_s(lastSlash, length, path);
		DWORD R = 0, G = 0, B = 0;
		if (ReadBMP24(filename, R, G, B, width, height)) {
			setVarByName(PASS_VARARGS, RED, R);
			setVarByName(PASS_VARARGS, GREEN, G);
			setVarByName(PASS_VARARGS, BLUE, B);
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
		Bitfield32 uiAudioFlags = BSGameSound::TypeFlags::IS_2D | BSGameSound::TypeFlags::ONE_SHOT;
		uiAudioFlags.Set<BSGameSound::TypeFlags::VOICE>(bVoice > 0);
		uiAudioFlags.Set<BSGameSound::TypeFlags::SYSTEM_SOUND>(bSystemSound > 0);
		uiAudioFlags.Set<BSGameSound::TypeFlags::LOOP>(bLoop > 0);
		uiAudioFlags.Set<BSGameSound::TypeFlags::DONT_CACHE>(bDontCache > 0);

		BSSoundHandle hSound = BSAudio::GetSingleton()->GetSoundHandleByFilePath(cPath, uiAudioFlags, nullptr);
		if (fFadeInTime <= 0)
			hSound.Play(false);
		else
			hSound.FadeInPlay(fFadeInTime * 1000);
		*result = 1;
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
		TESObjectREFR* pRef = thisObj;
		if (!pRef)
			pRef = PlayerCharacter::GetSingleton();

		NiAVObject* pRef3D = pRef->Get3DVerySimple();
		if (pRef3D) {
			Bitfield32 uiAudioFlags = BSGameSound::TypeFlags::IS_3D | BSGameSound::TypeFlags::ONE_SHOT;
			uiAudioFlags.Set<BSGameSound::TypeFlags::VOICE>(bVoice > 0);
			uiAudioFlags.Set<BSGameSound::TypeFlags::LOOP>(bLoop > 0);
			uiAudioFlags.Set<BSGameSound::TypeFlags::DONT_CACHE>(bDontCache > 0);

			BSSoundHandle hSound = BSAudio::GetSingleton()->GetSoundHandleByFilePath(cPath, uiAudioFlags, nullptr);
			hSound.SetPosition(pRef->GetLocationOnReference());
			hSound.SetObjectToFollow(pRef3D);
			if (fFadeInTime <= 0)
				hSound.Play(false);
			else
				hSound.FadeInPlay(fFadeInTime * 1000);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_StopSoundFromPath_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	float fFadeOutTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeOutTime) && cPath[0]) {
		BSAudioManager* pMgr = BSAudioManager::GetSingleton();
		std::scoped_lock kLock(pMgr->kProcessingCritSection);
		BSGameSound* pSound = nullptr;
		uint32_t uiKey;
		auto kIter = pMgr->kPlayingSounds.GetFirstPos();
		while (kIter) {
			pMgr->kPlayingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
				BSSoundHandle hSound(pSound->GetID());
				if (fFadeOutTime <= 0)
					hSound.Stop();
				else
					hSound.FadeOutAndRelease(fFadeOutTime * 1000);
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_StopSound3DFromPath_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	float fFadeOutTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeOutTime) && cPath[0]) {
		TESObjectREFR* pRef = thisObj;
		if (pRef == nullptr)
			pRef = PlayerCharacter::GetSingleton();

		BSAudioManager* pMgr = BSAudioManager::GetSingleton();
		std::scoped_lock kLock(pMgr->kProcessingCritSection);
		BSGameSound* pSound = nullptr;
		uint32_t uiKey;
		auto kIter = pMgr->kPlayingSounds.GetFirstPos();
		while (kIter) {
			pMgr->kPlayingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
				NiPointer<NiAVObject> spObj;
				if (!pMgr->kMovingObjects.GetAt(pSound->GetID(), spObj) || !spObj->IsFadeNode())
					continue;

				if (static_cast<BSFadeNode*>(spObj.m_pObject)->pLinkedObj == pRef) {
					BSSoundHandle hSound(pSound->GetID());
					if (fFadeOutTime <= 0) {
						hSound.Stop();
					}
					else {
						uint32_t uiTime = fFadeOutTime * 1000.0;
						hSound.FadeOutAndRelease(uiTime);
					}
					*result = 1;
				}
			}
		}
	}
	return true;
}

bool Cmd_IsSoundPlayingFromPath_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	TESObjectREFR* pRef = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &pRef) && cPath[0]) {
		BSAudioManager* pMgr = BSAudioManager::GetSingleton();
		std::scoped_lock kLock(pMgr->kProcessingCritSection);
		BSGameSound* pSound = nullptr;
		uint32_t uiKey;
		auto kIter = pMgr->kPlayingSounds.GetFirstPos();
		if (!pRef) {
			while (kIter) {
				pMgr->kPlayingSounds.GetNext(kIter, uiKey, pSound);
				if (pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
					*result = 1;
					return true;
				}
			}
		}
		else {
			auto kObjIter = pMgr->kMovingObjects.GetFirstPos();
			while (kObjIter) {
				NiPointer<NiAVObject> spObject;
				pMgr->kMovingObjects.GetNext(kObjIter, uiKey, spObject);
				if (!spObject || !spObject->IsFadeNode())
					continue;

				BSFadeNode* pFadeNode = static_cast<BSFadeNode*>(spObject.m_pObject);
				if (pFadeNode->pLinkedObj != pRef)
					continue;

				if (pMgr->kPlayingSounds.GetAt(uiKey, pSound) && pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
					*result = 1;
					return true;
				}
			}
		}
	}
	return true;
}