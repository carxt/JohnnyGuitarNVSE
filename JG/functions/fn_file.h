#pragma once
// Functions that operate on files
DEFINE_COMMAND_PLUGIN(MD5File, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SHA1File, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetPixelFromBMP, , false, kParams_BMP);
DEFINE_COMMAND_PLUGIN(GetTextureWidth, , false, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetTextureHeight, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetTextureFormat, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetTextureMipMapCount, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(PlaySoundFile, , false, kParams_OneString_ThreeOptionalInts);
DEFINE_COMMAND_PLUGIN(StopSoundFile, , false, nullptr);
DEFINE_COMMAND_PLUGIN(IsBSALoaded, , false, kParams_OneString);
DEFINE_COMMAND_PLUGIN(PlaySoundFromPath, , false, kParams_OneString_OneOptionalFloat_FourOptionalInts);
DEFINE_COMMAND_PLUGIN(PlaySound3DFromPath, , true, kParams_OneString_OneOptionalFloat_ThreeOptionalInts);
DEFINE_COMMAND_PLUGIN(StopSoundFromPath, , false, kParams_OneString_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(StopSound3DFromPath, , true, kParams_OneString_OneOptionalFloat);
DEFINE_COMMAND_PLUGIN(IsSoundPlayingFromPath, , false, kParams_OneString_OneOptionalObjectRef);
#include <filesystem>
#include "GameSound.h"

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
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, FileFinder::ARCHIVE_TYPE_ALL_);
		if (file != nullptr) {
			DWORD mipMapCount = 0;
			file->Seek(0x1C, 1);
			file->DoRead(&mipMapCount, sizeof(mipMapCount));
			*result = mipMapCount;
			if (IsConsoleMode()) Console_Print("GetTextureMipMapCount >> %.f", *result);
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
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, FileFinder::ARCHIVE_TYPE_ALL_);
		if (file != nullptr) {
			char format = 0;
			file->Seek(0x57, 1);
			file->DoRead(&format, 1);
			*result = format - '0';
			if (IsConsoleMode()) Console_Print("GetTextureFormat >> %.f", *result);
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
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, FileFinder::ARCHIVE_TYPE_ALL_);
		if (file != nullptr) {
			DWORD width = 0;
			file->Seek(0x10, 1);
			file->DoRead(&width, sizeof(width));
			*result = width;
			if (IsConsoleMode()) Console_Print("GetTextureWidth >> %.f", *result);
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
		BSFile* file = FileFinder::GetSingleton()->GetFile(path, FileFinder::OpenMode::READ_ONLY, -1, FileFinder::ARCHIVE_TYPE_ALL_);
		if (file != nullptr) {
			DWORD height = 0;
			file->Seek(0x0C, 1);
			file->DoRead(&height, sizeof(height));
			*result = height;
			if (IsConsoleMode()) Console_Print("GetTextureHeight >> %.f", *result);
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
		if (IsConsoleMode())
			Console_Print(outHash);
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
		if (IsConsoleMode())
			Console_Print(outHash);
		g_strInterface->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}

bool Cmd_GetPixelFromBMP_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH] = {};
	char RED[VarNameSize], GREEN[VarNameSize], BLUE[VarNameSize];
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
	char path[MAX_PATH] = {};
	int voiceFlag = 0;
	int systemFlag = 0;
	int loopFlag = 0;
	int bDontCacheFlag = 0;
	float fadeInTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &fadeInTime, &voiceFlag, &systemFlag, &loopFlag, &bDontCacheFlag) && path[0]) {
		bool bVoiceFlag = (voiceFlag > 0);
		bool bSystemFlag = (systemFlag > 0);
		bool bLoopFlag = (loopFlag > 0);
		uint32_t audioFlags = BSAudioManager::kAudioFlags_2D | BSAudioManager::kAudioFlags_100;
		if (bVoiceFlag) {
			audioFlags |= BSAudioManager::kAudioFlags_IsVoice;
		}
		if (bSystemFlag) {
			audioFlags |= BSAudioManager::kAudioFlags_SystemSound;
		}
		if (bLoopFlag) {
			audioFlags |= BSAudioManager::kAudioFlags_Loop;
		}
		if (bDontCacheFlag) {
			audioFlags |= BSAudioManager::kAudioFlags_DontCache;
		}
		BSSoundHandle handle = BSWin32Audio::GetSingleton()->GetSoundHandleByFilePath(path, BSAudioManager::AudioFlags(audioFlags), nullptr);
		if (fadeInTime <= 0) {
			handle.Play(false);
		}
		else {
			int time = fadeInTime * 1000.0;
			handle.FadeInPlay(time);
		}
		*result = 1;
	}
	return true;
}

bool Cmd_PlaySound3DFromPath_Execute(COMMAND_ARGS) {
	char path[MAX_PATH] = {};
	int voiceFlag = 0;
	int loopFlag = 0;
	int bDontCacheFlag = 0;
	float fadeInTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &fadeInTime, &voiceFlag, &loopFlag, &bDontCacheFlag) && path[0]) {
		TESObjectREFR* ref = thisObj;
		if (ref == nullptr) {
			ref = (TESObjectREFR*)PlayerCharacter::GetSingleton();
		}
		if (ref->GetRefNiNode()) {
			bool bVoiceFlag = (voiceFlag > 0);
			bool bLoopFlag = (loopFlag > 0);
			uint32_t audioFlags = BSAudioManager::kAudioFlags_3D | BSAudioManager::kAudioFlags_100;
			if (bVoiceFlag) {
				audioFlags |= BSAudioManager::kAudioFlags_IsVoice;
			}
			if (bLoopFlag) {
				audioFlags |= BSAudioManager::kAudioFlags_Loop;
			}
			if (bDontCacheFlag) {
				audioFlags |= BSAudioManager::kAudioFlags_DontCache;
			}
			BSSoundHandle handle = BSWin32Audio::GetSingleton()->GetSoundHandleByFilePath(path, BSAudioManager::AudioFlags(audioFlags), nullptr);
			handle.SetPosition(*ref->GetPos());
			handle.SetObjectToFollow(ref->GetRefNiNode());
			if (fadeInTime <= 0) {
				handle.Play(false);
			}
			else {
				int time = fadeInTime * 1000.0;
				handle.FadeInPlay(time);
			}
			*result = 1;
		}
	}
	return true;
}

bool Cmd_StopSoundFromPath_Execute(COMMAND_ARGS) {
	char path[MAX_PATH] = {};
	float fadeOutTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &fadeOutTime) && path[0]) {
		CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
		BSGameSound* pSound;
		uint32_t uiKey;
		auto kIter = BSAudioManager::Get()->playingSounds.GetFirstPos();
		while (kIter) {
			BSAudioManager::Get()->playingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->filePath, path) == 0) {
				BSSoundHandle handle;
				handle.uiSoundID = pSound->mapKey;

				if (fadeOutTime <= 0) {
					handle.Stop();
				}
				else {
					int time = fadeOutTime * 1000.0;
					handle.FadeOutAndRelease(time);
				}
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_StopSound3DFromPath_Execute(COMMAND_ARGS) {
	char path[MAX_PATH] = {};
	float fadeOutTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &fadeOutTime) && path[0]) {
		TESObjectREFR* ref = thisObj;
		if (ref == nullptr)
			ref = PlayerCharacter::GetSingleton();

		CSLock lock(BSAudioManager::Get()->kMessageProcessingCS);
		BSGameSound* pSound;
		uint32_t uiKey;
		auto kIter = BSAudioManager::Get()->playingSounds.GetFirstPos();
		while (kIter) {
			BSAudioManager::Get()->playingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->filePath, path) == 0) {
				NiPointer<NiAVObject> spObj;
				if (!BSAudioManager::Get()->soundPlayingObjects.GetAt(pSound->mapKey, spObj) || !spObj->IsFadeNode())
					continue;

				if (static_cast<BSFadeNode*>(spObj.m_pObject)->linkedObj == ref) {
					BSSoundHandle handle;
					handle.uiSoundID = pSound->mapKey;
					if (fadeOutTime <= 0) {
						handle.Stop();
					}
					else {
						int time = fadeOutTime * 1000.0;
						handle.FadeOutAndRelease(time);
					}
					*result = 1;
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
				if (pSound && _stricmp(pSound->filePath, path) == 0) {
					*result = 1;
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

				BSFadeNode* fadeNode = static_cast<BSFadeNode*>(spObject.m_pObject);
				if (fadeNode->linkedObj != ref)
					continue;

				if (BSAudioManager::Get()->playingSounds.GetAt(uiKey, pSound) && pSound && _stricmp(pSound->filePath, path) == 0) {
					*result = 1;
					return true;
				}
			}
		}
	}
	return true;
}
