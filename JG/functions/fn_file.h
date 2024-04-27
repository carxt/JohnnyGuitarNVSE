#pragma once
// Functions that operate on files
DEFINE_COMMAND_PLUGIN(MD5File, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SHA1File, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetPixelFromBMP, , 0, 6, kParams_BMP);
DEFINE_COMMAND_PLUGIN(UwUDelete, , 0, 2, kParams_OneString_OneInt); 
DEFINE_COMMAND_PLUGIN(GetTextureWidth, , 0, 2, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetTextureHeight, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetTextureFormat, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetTextureMipMapCount, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(PlaySoundFile, , 0, 3, kParams_OneString_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(StopSoundFile, , 0, 0, NULL);
#include <filesystem>

bool Cmd_StopSoundFile_Execute(COMMAND_ARGS) {
	*result = 0;
	CdeclCall<void>(0x8304A0);
	*result = 1;
	return true;
}
bool Cmd_PlaySoundFile_Execute(COMMAND_ARGS) {
	char path[MAX_PATH];
	*result = 0;
	UInt32 forcePlay = 0;
	UInt32 shouldLoop = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &forcePlay, &shouldLoop)) {
		CdeclCall<void>(0x8300C0, 6, path, 1000, shouldLoop, forcePlay, 0.0, 0);
		*result = 1;
	}
	return true;
}
void resolveTexturePath(char* path) {
	if (StrBeginsCI(path, "data\\")) {
		strcpy(path, path + 5);

	}
	if (StrBeginsCI(path, "textures\\") == 0) {
		char fixPath[MAX_PATH];
		strcpy(fixPath, path);
		sprintf(path, "textures\\%s", fixPath);
	}
}

bool Cmd_GetTextureMipMapCount_Execute(COMMAND_ARGS) {
	*result = 0;
	char path[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path)) {
		resolveTexturePath(path);
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
	char path[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path)) {
		resolveTexturePath(path);
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
	char path[MAX_PATH];
	char fixPath[MAX_PATH];
	UInt32 useDataTextures = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &useDataTextures)) {
		resolveTexturePath(path);
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
	char path[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path)) {
		resolveTexturePath(path);
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
bool Cmd_UwUDelete_Execute(COMMAND_ARGS) {
	*result = 0;
	int fileOrFolder = 0;
	char filename[MAX_PATH];
	UInt8 modIdx = scriptObj->GetOverridingModIdx();
	if (modIdx == 0xFF) return true;
	if (strcmp("UwU.esp", g_dataHandler->GetNthModName(modIdx))) return true;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &filename, &fileOrFolder)) {
		if (strstr(filename, "..\\")) return true;
		char filepath[MAX_PATH];
		GetModuleFileNameA(NULL, filepath, MAX_PATH);
		strcpy((char*)(strrchr(filepath, '\\') + 1), "Data\\Config\\UwUDaddy\\");
		strcat(filepath, filename);
		if (fileOrFolder == 1) {
			strcat(filepath, ".ini");
			remove(filepath);
			*result = 1;
		}
		else if (fileOrFolder == 2) {
			std::filesystem::remove_all(filepath);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_MD5File_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH];
	char outHash[0x21];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path)) {
		if (strstr(path, "..\\")) return true;
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
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
	char path[MAX_PATH];
	char outHash[0x29];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path)) {
		if (strstr(path, "..\\")) return true;
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
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
	char path[MAX_PATH];
	char RED[VarNameSize], GREEN[VarNameSize], BLUE[VarNameSize];
	UInt32 width = 0, height = 0;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &path, &RED, &GREEN, &BLUE, &width, &height)) {
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
		UInt32 R = 0, G = 0, B = 0;
		if (ReadBMP24(filename, R, G, B, width, height)) {
			setVarByName(PASS_VARARGS, RED, R);
			setVarByName(PASS_VARARGS, GREEN, G);
			setVarByName(PASS_VARARGS, BLUE, B);
		}
	}
	return true;
}