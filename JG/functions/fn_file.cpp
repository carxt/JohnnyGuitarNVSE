#include "fn_file.h"
#include "Bethesda/FileFinder.hpp"
#include "Bethesda/Interface.hpp"
#include "Bethesda/Archive.hpp"
#include "Bethesda/ArchiveManager.hpp"

#include <misc/misc.h>
#include <utility.h>

bool Cmd_IsBSALoaded_Execute(COMMAND_ARGS) {
	char cPath[MAX_PATH] = {};
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		char cFullPath[MAX_PATH];
		our_snprintf(cFullPath, sizeof(cFullPath), "DATA\\%s", cPath);
		if (ArchiveManager::GetArchiveByName(cFullPath))
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
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		resolveTexturePath(cPath, sizeof(cPath));
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cPath, NiFile::OpenMode::READ_ONLY, UINT32_MAX, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			uint32_t uiMipCount = 0;
			pFile->Seek(0x1C, SEEK_CUR);
			pFile->ReadF(&uiMipCount, sizeof(uiMipCount));
			*result = uiMipCount;
			if (Script::GetConsoleOuput())
				Interface::PrintLine("GetTextureMipMapCount >> %.f", *result);
			
			delete pFile;
		}
	}
	return true;
}

bool Cmd_GetTextureFormat_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		resolveTexturePath(cPath, sizeof(cPath));
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cPath, NiFile::OpenMode::READ_ONLY, UINT32_MAX, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			char cFormat = 0;
			pFile->Seek(0x57, SEEK_CUR);
			pFile->ReadF(&cFormat, sizeof(cFormat));

			*result = cFormat - '0';

			if (Script::GetConsoleOuput()) 
				Interface::PrintLine("GetTextureFormat >> %.f", *result);

			delete pFile;
		}
	}
	return true;
}

bool Cmd_GetTextureWidth_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	BOOL bUseDataTextures = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &bUseDataTextures) && cPath[0]) {
		resolveTexturePath(cPath, sizeof(cPath));
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cPath, NiFile::OpenMode::READ_ONLY, UINT32_MAX, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			uint32_t uiWidth = 0;
			pFile->Seek(0x10, SEEK_CUR);
			pFile->ReadF(&uiWidth, sizeof(uiWidth));
			
			*result = uiWidth;

			if (Script::GetConsoleOuput()) 
				Interface::PrintLine("GetTextureWidth >> %.f", *result);

			delete pFile;
		}
	}
	return true;
}

bool Cmd_GetTextureHeight_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath) && cPath[0]) {
		resolveTexturePath(cPath, sizeof(cPath));
		BSFile* pFile = FileFinder::GetSingleton()->GetFile(cPath, NiFile::OpenMode::READ_ONLY, UINT32_MAX, ARCHIVE_TYPE::TEXTURES);
		if (pFile) {
			uint32_t uiHeight = 0;
			pFile->Seek(0x0C, 1);
			pFile->ReadF(&uiHeight, sizeof(uiHeight));

			*result = uiHeight;

			if (Script::GetConsoleOuput())
				Interface::PrintLine("GetTextureHeight >> %.f", *result);

			delete pFile;
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