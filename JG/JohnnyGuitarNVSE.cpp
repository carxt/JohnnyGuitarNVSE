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

bool bIsGECK = false;
_CaptureLambdaVars CaptureLambdaVars;
_UncaptureLambdaVars UncaptureLambdaVars;

NVSEArrayVarInterface* g_arrInterface = NULL;
NVSEStringVarInterface* g_strInterface = NULL;
NVSEMessagingInterface* g_msg = NULL;
NVSEScriptInterface* g_scriptInterface = NULL;
NVSEMessagingInterface* g_msgInterface = NULL;
NVSECommandTableInterface* g_cmdTableInterface = NULL;
uint32_t g_pluginHandle = 0;

void (*ApplyPerkModifiers)(PerkEntryPointID entryPointID, TESObjectREFR* perkOwner, void* arg3, ...) = (void (*)(PerkEntryPointID, TESObjectREFR*, void*, ...))0x5E58F0;
InventoryRef* (*InventoryRefGetForID)(uint32_t refID);

bool (*ExtractArgsEx)(COMMAND_ARGS_EX, ...);

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

	bIsGECK = apNVSE->isEditor != 0;

	return true;
}

EXTERN_DLL_EXPORT bool NVSEPlugin_Load(const NVSEInterface* apNVSE) {
	g_pluginHandle = apNVSE->GetPluginHandle();
	g_msgInterface = static_cast<NVSEMessagingInterface*>(apNVSE->QueryInterface(kInterface_Messaging));
	g_msgInterface->RegisterListener(g_pluginHandle, "NVSE", bIsGECK ? JohnnyMessageHandler::GECK : JohnnyMessageHandler::Game);

	g_scriptInterface = static_cast<NVSEScriptInterface*>(apNVSE->QueryInterface(kInterface_Script));
	g_cmdTableInterface = static_cast<NVSECommandTableInterface*>(apNVSE->QueryInterface(kInterface_CommandTable));
	g_arrInterface = static_cast<NVSEArrayVarInterface*>(apNVSE->QueryInterface(kInterface_ArrayVar));
	g_strInterface = static_cast<NVSEStringVarInterface*>(apNVSE->QueryInterface(kInterface_StringVar));

	JohnnyCommands::Init(apNVSE);

	JohnnyPatches::ReadINI();

	if (JohnnyPatches::bFixJIP) {
		JIPFixes::InitData();
		JIPFixes::InitEarlyHooks(bIsGECK);
	}

	if (!bIsGECK) {
		NVSEDataInterface* pNVSEData = static_cast<NVSEDataInterface*>(apNVSE->QueryInterface(kInterface_Data));
		InventoryRefGetForID = static_cast<InventoryRef * (*)(uint32_t)>(pNVSEData->GetFunc(NVSEDataInterface::kNVSEData_InventoryReferenceGetForRefID));
		CaptureLambdaVars = static_cast<_CaptureLambdaVars>(pNVSEData->GetFunc(NVSEDataInterface::kNVSEData_LambdaSaveVariableList));
		UncaptureLambdaVars = static_cast<_UncaptureLambdaVars>(pNVSEData->GetFunc(NVSEDataInterface::kNVSEData_LambdaUnsaveVariableList));
		ExtractArgsEx = g_scriptInterface->ExtractArgsEx;

		FixedStringsRework::Init();

		JohnnyExtraData::Initialize(pNVSEData);

		JohnnyFixes::Init();
		JohnnyPatches::Init();
		JohnnyGameSettings::Init();
		JohnnyEvents::Init();
		JohnnySerialization::Init(apNVSE);
	}

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
