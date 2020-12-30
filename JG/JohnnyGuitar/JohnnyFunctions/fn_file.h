#pragma once
// Functions that operate on files
DEFINE_COMMAND_PLUGIN(MD5File, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SHA1File, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetPixelFromBMP, , 0, 6, kParamsBMPArgs);
DEFINE_COMMAND_PLUGIN(UwUDelete, , 0, 2, kParamsJohnny_OneString_OneInt);

#include <filesystem>
bool Cmd_UwUDelete_Execute(COMMAND_ARGS) {
	int fileOrFolder = 0;
	char filename[MAX_PATH];
	UInt8 modIdx = scriptObj->GetOverridingModIdx();
	if (modIdx == 0xFF) return true;
	DataHandler* g_dataHandler = DataHandler::Get();
	if (strcmp("UwU.esp", g_dataHandler->GetNthModName(modIdx))) return true;
	if (ExtractArgs(EXTRACT_ARGS, &filename, &fileOrFolder)) {
		if (strstr(filename, "..\\")) return true;
		char filepath[MAX_PATH];
		GetModuleFileNameA(NULL, filepath, MAX_PATH);
		strcpy((char*)(strrchr(filepath, '\\') + 1), "Data\\Config\\UwUDaddy\\");
		strcat(filepath, filename);
		if (fileOrFolder == 1) {
			strcat(filepath, ".ini");
			remove(filepath);
		}
		else if (fileOrFolder == 2) {
			std::filesystem::remove_all(filepath);
		}
	}
	return true;
}

bool Cmd_MD5File_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH];
	char outHash[0x21];
	if (ExtractArgs(EXTRACT_ARGS, &path)) {
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
		GetMD5File(filename, outHash);
		if (IsConsoleMode())
			Console_Print(outHash);
		StrIfc->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}

bool Cmd_SHA1File_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH];
	char outHash[0x29];
	if (ExtractArgs(EXTRACT_ARGS, &path)) {
		strcpy((char*)(strrchr(filename, '\\') + 1), path);
		GetSHA1File(filename, outHash);
		if (IsConsoleMode())
			Console_Print(outHash);
		StrIfc->Assign(PASS_COMMAND_ARGS, outHash);
	}
	return true;
}

bool Cmd_GetPixelFromBMP_Execute(COMMAND_ARGS) {
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	char path[MAX_PATH];
	char RED[VarNameSize], GREEN[VarNameSize], BLUE[VarNameSize];
	UInt32 width = 0, height = 0;

	if (ExtractArgs(EXTRACT_ARGS, &path, &RED, &GREEN, &BLUE, &width, &height)) {
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