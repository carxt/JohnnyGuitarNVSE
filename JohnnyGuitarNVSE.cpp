
#include "nvse/PluginAPI.h"
#include "nvse/GameAPI.h"
#include "nvse/CommandTable.h"
#include "nvse/GameObjects.h"
#include "nvse/GameData.h"
#include "nvse/GameForms.h"
#include "nvse/GameExtraData.h"
#include "nvse/GameTasks.h"
#include "nvse/GameRTTI.h"
#include "nvse/GameOSDepend.h"
#include "nvse/GameUI.h"
#include "nvse/GameScript.h"
#include "nvse/SafeWrite.h"
#include "nvse/NiObjects.h"
#include "JohnnyGuitar/misc.h"
#include "JohnnyGuitar/WorldToScreen.h"
#include "JohnnyGuitar/JohnnyGuitarNVSE.h"
#include "JohnnyGuitar/JohnnyParams.h"
#include "JohnnyGuitar/JohnnyFunctions.h"
#include "JohnnyGuitar/md5/md5.h"
#include "JohnnyGuitar/sha1/sha1.h"
HMODULE JohnnyHandle;
IDebugLog		gLog;
int J_bRemoveRedOutline = 0;
int J_bRemoveTags = 0;	

void MessageHandler(NVSEMessagingInterface::Message* msg)
{
	
	switch (msg->type)
	{

	case NVSEMessagingInterface::kMessage_NewGame:
	case NVSEMessagingInterface::kMessage_PostLoadGame:
		isShowLevelUp = true;
		break;
	}

}

extern "C"{
bool NVSEPlugin_Query(const NVSEInterface * nvse, PluginInfo * info)
{
	// fill out the info structure
	gLog.Open("JohnnyGuitarNVSE.log");
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "JohnnyGuitarNVSE";
	info->version = 1;

	if (nvse->isNogore) 
	{
		_ERROR("Unsupported");
		return false;
	}

	if (nvse->nvseVersion < NVSE_VERSION_INTEGER)
	{
		_ERROR("NVSE version too old (got %08X expected at least %08X)", nvse->nvseVersion, NVSE_VERSION_INTEGER);
		return false;
	}

	if (!nvse->isEditor)
	{
		if (nvse->runtimeVersion < RUNTIME_VERSION_1_4_0_525)
		{
			_ERROR("incorrect runtime version (got %08X need at least %08X)", nvse->runtimeVersion, RUNTIME_VERSION_1_4_0_525);
			return false;
		}
	}
	else
	{
		if (nvse->editorVersion < CS_VERSION_1_4_0_518)
		{
			_ERROR("incorrect editor version (got %08X need at least %08X)", nvse->editorVersion, CS_VERSION_1_4_0_518);
			return false;
		}
	};

	// version checks pass
	_MESSAGE("JohnnyGuitarNVSE Loaded succesfully.\nJohnnyGuitarNVSE plugin version: %u\n", info->version);
	char filename[MAX_PATH];
	GetModuleFileNameA(JohnnyHandle, filename, MAX_PATH);
	return true;
}


bool NVSEPlugin_Load(const NVSEInterface * nvse)
{
	((NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging))->RegisterListener(nvse->GetPluginHandle(), "NVSE", MessageHandler);
	NiPointBuffer = (NiPoint3*) malloc(sizeof(NiPoint3));
	char filename[MAX_PATH];
	GetModuleFileNameA(NULL, filename, MAX_PATH);
	strcpy((char *)(strrchr(filename, '\\') + 1), "Data\\nvse\\plugins\\JohnnyGuitar.ini)");
	nvse->SetOpcodeBase(0x3100);
	REG_CMD(WorldToScreen);
	REG_CMD(ToggleLevelUpMenu);
	REG_CMD(IsLevelUpMenuEnabled);
	REG_CMD(GetBaseEffectAV);
	REG_CMD(GetBaseEffectArchetype);
	REG_CMD(IsCellVisited);
	REG_CMD(IsCellExpired);
	REG_CMD(MD5File);
	REG_CMD(SHA1File);
	StrArgBuf = (char*) malloc((sizeof(char))*1024);
	ArrIfc = (NVSEArrayVarInterface*)nvse->QueryInterface(kInterface_ArrayVar);
	StrIfc = (NVSEStringVarInterface*)nvse->QueryInterface(kInterface_StringVar);
	g_script = (NVSEScriptInterface*)nvse->QueryInterface(kInterface_Script);
	CmdIfc = (NVSECommandTableInterface*)nvse->QueryInterface(kInterface_CommandTable);
	if (!nvse->isEditor)	HandleGameHooks();
	return true;
}
	BOOL WINAPI DllMain(
		HANDLE  hDllHandle,
		DWORD   dwReason,
		LPVOID  lpreserved
		)
	{
		switch (dwReason)
		{
		case (DLL_PROCESS_ATTACH) :
			JohnnyHandle = (HMODULE)hDllHandle;
			break;
		}
		return TRUE;
	}
};





