#include "JohnnyGuitarNVSE.h"
#include "decoding.h"
#include "nvse_version.h"

#include "Bethesda/AutoMemContext.hpp"

#include "events/LambdaVariableContext.h"
#include "events/JohnnyEvents.hpp"

#include "JG/FixedStringsRework.hpp"
#include "JG/JohnnyCommands.hpp"
#include "JG/JohnnyExtraData.hpp"
#include "JG/JohnnyFixes.hpp"
#include "JG/JohnnyGameSettings.hpp"
#include "JG/JohnnyMessageHandler.hpp"
#include "JG/JohnnyPatches.hpp"
#include "JG/JohnnyPluginData.hpp"
#include "JG/JohnnySerialization.hpp"
#include "JG/TaskQueue.hpp"

#include "JIP/JIPFixes.hpp"

BS_ALLOCATORS

IDebugLog	   gLog(JohnnyPluginData::JG_LOG_PATH);

#ifdef GAME
void (*ApplyPerkModifiers)(PerkEntryPointID entryPointID, TESObjectREFR* perkOwner, void* arg3, ...) = (void (*)(PerkEntryPointID, TESObjectREFR*, void*, ...))0x5E58F0;
InventoryRef* (*InventoryRefGetForID)(uint32_t refID);
TESObjectREFR* (__stdcall* InventoryRefCreateEntry)(TESObjectREFR* container, TESForm* itemForm, uint32_t countDelta, ExtraDataList* xData);

_CaptureLambdaVars CaptureLambdaVars;
_UncaptureLambdaVars UncaptureLambdaVars;

bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);

NVSEArrayVarInterface* g_arrInterface = NULL;
NVSEScriptInterface* g_scriptInterface = NULL;
#endif
NVSEStringVarInterface* g_strInterface = NULL;
NVSEMessagingInterface* g_msgInterface = NULL;
NVSECommandTableInterface* g_cmdTableInterface = NULL;
NVSEDataInterface* g_dataInterface = NULL;
uint32_t g_pluginHandle = 0;

// Runs during NVSEPlugin_Load
void OnNVSELoadInit(const NVSEInterface* apNVSE) {
	JohnnyPatches::ReadINI();

	g_pluginHandle = apNVSE->GetPluginHandle();
	g_msgInterface = static_cast<NVSEMessagingInterface*>(apNVSE->QueryInterface(kInterface_Messaging));
	g_msgInterface->RegisterListener(g_pluginHandle, "NVSE", JohnnyMessageHandler::Handler);
	g_cmdTableInterface = static_cast<NVSECommandTableInterface*>(apNVSE->QueryInterface(kInterface_CommandTable));
	g_dataInterface = static_cast<NVSEDataInterface*>(apNVSE->QueryInterface(kInterface_Data));
#ifdef GAME
	g_scriptInterface = static_cast<NVSEScriptInterface*>(apNVSE->QueryInterface(kInterface_Script));
	g_arrInterface = static_cast<NVSEArrayVarInterface*>(apNVSE->QueryInterface(kInterface_ArrayVar));
	g_strInterface = static_cast<NVSEStringVarInterface*>(apNVSE->QueryInterface(kInterface_StringVar));

	InventoryRefGetForID = static_cast<InventoryRef * (*)(uint32_t)>(g_dataInterface->GetFunc(NVSEDataInterface::kNVSEData_InventoryReferenceGetForRefID));
	InventoryRefCreateEntry = static_cast<TESObjectREFR * (__stdcall*)(TESObjectREFR*, TESForm*, uint32_t, ExtraDataList*)>(g_dataInterface->GetFunc(NVSEDataInterface::kNVSEData_InventoryReferenceCreateEntry));
	CaptureLambdaVars = static_cast<_CaptureLambdaVars>(g_dataInterface->GetFunc(NVSEDataInterface::kNVSEData_LambdaSaveVariableList));
	UncaptureLambdaVars = static_cast<_UncaptureLambdaVars>(g_dataInterface->GetFunc(NVSEDataInterface::kNVSEData_LambdaUnsaveVariableList));
	ExtractArgsEx = g_scriptInterface->ExtractArgsEx;

	JohnnySerialization::Init(apNVSE);
#endif

	JohnnyCommands::Init(apNVSE);
}

// Runs on program's WinMain
// For the game, it's on NVSEPlugin_Load itself
// For GECK, NVSEPlugin_Load works like game's NVSEPlugin_Preload, so a hook is needed to init at a similar point to the game
void OnMainInit() {
	if (JohnnyPatches::bFixJIP) {
		JIPFixes::InitData();
		JIPFixes::InitEarlyHooks();
	}

	FixedStringsRework::Init();
	JohnnyExtraData::Initialize(g_dataInterface);
	JohnnyFixes::Init();
	JohnnyPatches::Init();
	JohnnyGameSettings::Init();
#ifdef GAME
	JohnnyEvents::Init();
#endif
}

#ifndef GAME
// Detour MessageHandler::Init - it's the first function called in GECK's WinMain, after CLI arguments have been read
// Runs after GECK Extender
HookUtils::CallDetour kGECKWinMainDetour;
void __cdecl OnGECKMain(bool a1, bool a2, bool a3, bool a4, void* a5) {
	OnMainInit();
	CdeclCall(kGECKWinMainDetour, a1, a2, a3, a4, a5);
}
#endif

EXTERN_DLL_EXPORT bool NVSEPlugin_Query(const NVSEInterface* apNVSE, PluginInfo* apInfo) {
	apInfo->infoVersion = PluginInfo::kInfoVersion;
	apInfo->name = JohnnyPluginData::JG_PLUGIN_NAME;
	apInfo->version = JohnnyPluginData::JG_VERSION;

	if (apNVSE->isNogore) {
		MessageBoxA(nullptr, "German NoGore release of the game is not supported", JohnnyPluginData::JG_FULL_NAME, MB_OK | MB_ICONERROR);
		return false;
	}

	if (apNVSE->nvseVersion < PACKED_NVSE_VERSION) {
		char cBuffer[128];
		sprintf_s(cBuffer, "NVSE version is outdated. This plugin requires v%i.%i.%i minimum.", NVSE_VERSION_INTEGER, NVSE_VERSION_INTEGER_MINOR, NVSE_VERSION_INTEGER_BETA);
		MessageBoxA(nullptr, cBuffer, JohnnyPluginData::JG_FULL_NAME, MB_OK | MB_ICONERROR);
		return false;
	}

	if (!apNVSE->isEditor) {
		if (apNVSE->runtimeVersion < RUNTIME_VERSION_1_4_0_525) {
			_MESSAGE("incorrect New Vegas version (got %08X need at least %08X)", apNVSE->runtimeVersion, RUNTIME_VERSION_1_4_0_525);
			return false;
		}
	}
	else {
		if (apNVSE->editorVersion < CS_VERSION_1_4_0_518) {
			_MESSAGE("incorrect GECK version (got %08X need at least %08X)", apNVSE->editorVersion, CS_VERSION_1_4_0_518);
			return false;
		}
	};

	// version checks pass
	_MESSAGE("JohnnyGuitarNVSE %u Loaded successfully.", apInfo->version);

#ifdef GAME
	return apNVSE->isEditor == FALSE;
#else
	return apNVSE->isEditor == TRUE;
#endif
}

EXTERN_DLL_EXPORT bool NVSEPlugin_Load(const NVSEInterface* apNVSE) {
	OnNVSELoadInit(apNVSE);
#ifdef GAME
	OnMainInit();
#else
	kGECKWinMainDetour.ReplaceCall(0x445AE1, OnGECKMain);
#endif
	return true;
}

BOOL WINAPI DllMain(
	HANDLE  hDllHandle,
	DWORD   dwReason,
	LPVOID  lpreserved
) {
	if (dwReason == DLL_PROCESS_ATTACH)
		DisableThreadLibraryCalls((HMODULE)hDllHandle);
	return TRUE;
}
