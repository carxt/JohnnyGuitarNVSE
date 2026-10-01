#include "fn_file.h"
#include "Bethesda/FileFinder.hpp"
#include "Bethesda/Interface.hpp"

#include <misc/misc.h>
#include <utility.h>

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