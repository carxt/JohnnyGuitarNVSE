#include <memory>
#include <mutex>
#include <shared_mutex>
#include "nvse/PluginAPI.h"
#include "nvse/GameAPI.h"
#include "nvse/CommandTable.h"
#include "nvse/GameForms.h"
#include "nvse/GameObjects.h"
#include "nvse/GameEffects.h"
#include "nvse/GameData.h"
#include "nvse/GameExtraData.h"
#include "nvse/GameTasks.h"
#include "nvse/GameProcess.h"
#include "nvse/GameRTTI.h"
#include "nvse/GameOSDepend.h"
#include "nvse/GameUI.h"
#include "nvse/GameUI.cpp"
#include "nvse/GameScript.h"
#include "nvse/SafeWrite.h"
#include "nvse/ScriptUtils.h"
#include "misc/WorldToScreen.h"
#include "misc/misc.h"
#include "misc/EditorIDs.h"
#include "internal/decoding.h"
#include "JohnnyGuitarNVSE.h"
#include "nvse/ParamInfos.h"
#include "functions/fn_av.h"
#include "functions/fn_form.h"
#include "functions/fn_utility.h"
#include "functions/fn_math.h"
#include "functions/fn_file.h"
#include "functions/fn_gameplay.h"
#include "functions/fn_mediaset.h"
#include "functions/fn_region.h"
#include "functions/fn_terminal.h"
#include "functions/fn_ui.h"
#include "events/LambdaVariableContext.h"
#include "events/JohnnyEventPredefinitions.h"
#include "events/JohnnyEvents.h"

HMODULE JohnnyHandle;
IDebugLog		gLog;
_CaptureLambdaVars CaptureLambdaVars;
_UncaptureLambdaVars UncaptureLambdaVars;
NiTMap<const char*, TESForm*>** g_gameFormEditorIDsMap = reinterpret_cast<NiTMap<const char*, TESForm*>**>(0x11C54C8);

void MessageHandler(NVSEMessagingInterface::Message* msg)
{

	switch (msg->type)
	{

	case NVSEMessagingInterface::kMessage_NewGame:
	case NVSEMessagingInterface::kMessage_PostLoadGame:
	{
		isShowLevelUp = true;
		PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
		ThisStdCall(0x8C17C0, g_thePlayer); // reevaluate reload speed modifiers
		ThisStdCall(0x8C1940, g_thePlayer); // reevaluate equip speed modifiers

		for (const auto& EventInfo : g_EventsArray)
		{
			if (EventInfo->GetFlags() & BaseEventInformation::eFlag_FlushOnLoad)
			{
				EventInfo->FlushEventCallbacks();
			}
		}
			
		bArrowKeysDisabled = false;
		RestoreDisabledPlayerControlsHUDFlags();
		SaveGameUMap.clear();
		break;
	}
	case NVSEMessagingInterface::kMessage_PreLoadGame:
	{
		disableMuzzleLights = 0; //reset the muzzle hook every time
		break;
	}
	case NVSEMessagingInterface::kMessage_MainGameLoop:
		for (const auto& EventInfo : g_EventsArray)
		{
			EventInfo->AddQueuedEvents();
			EventInfo->DeleteEvents();
		}
		break;
	case NVSEMessagingInterface::kMessage_DeferredInit:
	{
		g_thePlayer = PlayerCharacter::GetSingleton();
		g_processManager = (ProcessManager*)0x11E0E80;
		g_interfaceManager = InterfaceManager::GetSingleton();
		g_bsWin32Audio = BSWin32Audio::GetSingleton();
		g_dataHandler = DataHandler::Get();
		g_audioManager = (BSAudioManager*)0x11F6EF0;
		g_currentSky = (Sky**)0x11DEA20;
		g_gameTimeGlobals = (GameTimeGlobals*)0x11DE7B8;
		g_VATSCameraData = (VATSCameraData*)0x11F2250;
		g_initialTickCount = GetTickCount();
		break;
	}
	default:
		break;
	}

}

extern "C" {

	bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info)
	{
		// fill out the info structure
		gLog.Open("JohnnyGuitarNVSE.log");
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "JohnnyGuitarNVSE";
		info->version = 410;

		if (nvse->isNogore)
		{
			_ERROR("NV noGore is unsupported");
			return false;
		}
		int version = nvse->nvseVersion;
		double s_nvseVersion = (version >> 24) + (((version >> 16) & 0xFF) * 0.1) + (((version & 0xFF) >> 4) * 0.01);
		if (version < 0x6020030)
		{
			_ERROR("NVSE version is outdated (v%.2f). This plugin requires v6.1 minimum.", s_nvseVersion);
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


	bool NVSEPlugin_Load(const NVSEInterface* nvse)
	{
		((NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging))->RegisterListener(nvse->GetPluginHandle(), "NVSE", MessageHandler);
		char filename[MAX_PATH];
		GetModuleFileNameA(NULL, filename, MAX_PATH);
		strcpy((char*)(strrchr(filename, '\\') + 1), "Data\\nvse\\plugins\\JohnnyGuitar.ini");
		loadEditorIDs = GetPrivateProfileInt("MAIN", "bLoadEditorIDs", 1, filename);
		fixHighNoon = 0;
		fixFleeing = GetPrivateProfileInt("MAIN", "bFixFleeing", 1, filename);
		fixItemStacks = GetPrivateProfileInt("MAIN", "bFixItemStackCount", 1, filename);
		fixNPCShootingAngle = GetPrivateProfileInt("MAIN", "bFixNPCShootingAngle", 1, filename);
		capLoadScreensTo60 = GetPrivateProfileInt("MAIN", "b60FPSDuringLoading", 0, filename);
		noMuzzleFlashCooldown = GetPrivateProfileInt("MAIN", "bNoMuzzleFlashCooldown", 0, filename);
		resetVanityCam = GetPrivateProfileInt("MAIN", "bReset3rdPersonCamera", 0, filename);
		JGGameCamera.WorldMatrx = new JGWorldToScreenMatrix;
		JGGameCamera.CamPos = new JGCameraPosition;
		SaveGameUMap.reserve(0xFF);
		nvse->SetOpcodeBase(0x3100);

		REG_CMD(JGLegacyWorldToScreen);
		REG_CMD(ToggleLevelUpMenu);
		REG_CMD(IsLevelUpMenuEnabled);
		REG_CMD(GetBaseEffectAV);
		REG_CMD(GetBaseEffectArchetype);
		REG_CMD(IsCellVisited);
		REG_CMD(IsCellExpired);
		REG_TYPED_CMD(MD5File, String);
		REG_TYPED_CMD(SHA1File, String);
		REG_CMD(TogglePipBoy);
		REG_CMD(GetCalculatedWeaponDPS);
		REG_CMD(GetInteriorLightingTraitNumeric);
		REG_CMD(SetInteriorLightingTraitNumeric);
		REG_CMD(GetPixelFromBMP);
		REG_TYPED_CMD(GetWorldSpaceMapTexture, String);
		REG_CMD(Jump);
		REG_CMD(SetCameraShake);
		REG_CMD(StopVATSCam);
		REG_CMD(GetIMODAnimatable);
		REG_CMD(SetIMODAnimatable);
		REG_TYPED_CMD(GetEditorID, String);
		REG_CMD(GetJohnnyPatch);
		REG_CMD(SetVelEx);
		REG_CMD(UwUDelete);
		REG_CMD(GetMediaSetTraitNumeric);
		REG_CMD(SetMediaSetTraitNumeric);
		REG_TYPED_CMD(GetMediaSetTraitString, String);
		REG_CMD(SetMediaSetTraitString);
		REG_TYPED_CMD(GetMediaSetTraitSound, Form);
		REG_CMD(SetMediaSetTraitSound);
		REG_TYPED_CMD(GetWeapon1stPersonModel, Form);
		REG_CMD(SetWeapon1stPersonModel);
		REG_TYPED_CMD(GetBufferedCellsAlt, Array);
		REG_CMD(GetTimePlayed);
		REG_CMD(GetActorValueModifierAlt);
		REG_CMD(AsmBreak);
		REG_CMD(RefAddr);
		REG_TYPED_CMD(GetMusicTypePath, String);
		REG_CMD(GetMusicTypeDB);
		REG_CMD(SetMusicTypeDB);
		REG_TYPED_CMD(EditorIDToFormID, Form);
		REG_CMD(GetRegionWeatherOverride);
		REG_CMD(SetRegionWeatherOverride);
		REG_CMD(GetRegionWeatherPriority);
		REG_CMD(SetRegionWeatherPriority);
		REG_CMD(IsWeatherInRegion);
		REG_CMD(RemoveRegionWeather);
		REG_CMD(AddRegionWeather);
		REG_TYPED_CMD(GetRegionWeathers, Array);
		REG_CMD(ClearRegionWeathers);
		REG_CMD(StopSoundAlt);
		REG_CMD(RemovePrimitive);
		REG_CMD(GetPrimitiveType);
		REG_CMD(GetBaseScale);
		REG_TYPED_CMD(GetCustomMapMarker, Form);
		REG_CMD(UnsetAV);
		REG_CMD(UnforceAV);
		REG_CMD(ToggleNthPipboyLight);
		REG_CMD(SetBipedIconPathAlt);
		REG_CMD(GetFacegenModelFlag);
		REG_CMD(SetFacegenModelFlag);
		REG_TYPED_CMD(GetRaceBodyModelPath, String);
		REG_CMD(SetEquipType);
		REG_TYPED_CMD(GetFactionMembers, Array);
		REG_TYPED_CMD(GetRaceHeadModelPath, String);
		REG_CMD(GetDefaultHeapSize);
		REG_CMD(Get3DDistanceBetweenNiNodes);
		REG_CMD(Get3DDistanceToNiNode);
		REG_CMD(Get3DDistanceFromHitToNiNode);
		REG_CMD(GetVector3DDistance);
		REG_CMD(GetLinearVelocity);
		REG_CMD(GetLifeState);
		REG_CMD(GetRaceFlag);
		REG_CMD(SetRaceFlag);
		REG_TYPED_CMD(GetContainerSound, Form);
		REG_CMD(SetContainerSound);
		REG_CMD(SetJohnnyOnDyingEventHandler);
		REG_CMD(SetJohnnyOnStartQuestEventHandler);
		REG_CMD(SetJohnnyOnStopQuestEventHandler);
		REG_CMD(DisableMuzzleFlashLights);
		REG_CMD(SetCustomMapMarkerIcon);
		REG_CMD(GetCreatureCombatSkill);
		REG_CMD(SetExplosionSound);
		REG_CMD(SetProjectileSound);
		REG_CMD(SetWeaponWorldModelPath);
		REG_CMD(Clamp);
		REG_CMD(Remap);
		REG_CMD(Lerp);
		REG_CMD(SetJohnnySeenDataEventHandler);
		REG_CMD(SetJohnnyOnLimbGoneEventHandler);
		REG_CMD(Sign);
		REG_CMD(AddTerminalMenuItem);
		REG_TYPED_CMD(GetTerminalMenuItemText, String);
		REG_CMD(SetTerminalMenuItemText);
		REG_TYPED_CMD(GetTerminalMenuItemNote, Form);
		REG_CMD(SetTerminalMenuItemNote);
		REG_TYPED_CMD(GetTerminalMenuItemSubmenu, Form);
		REG_CMD(SetTerminalMenuItemSubmenu);
		REG_CMD(GetRunSpeed);
		REG_CMD(DisableMenuArrowKeys);
		REG_CMD(EnableMenuArrowKeys);
		REG_CMD(GetQuestFailed);
		REG_CMD(SetJohnnyOnChallengeCompleteEventHandler);
		REG_CMD(GetTerminalMenuItemCount);
		REG_CMD(GetPipBoyMode);
		REG_CMD(GetWeaponVATSTraitNumeric);
		REG_CMD(SetWeaponVATSTraitNumeric);
		REG_CMD(RemoveTerminalMenuItem);
		REG_CMD(SetWorldSpaceMapTexture);
		REG_CMD(GetFormOverrideIndex);
		REG_CMD(SetJohnnyOnCrosshairEventHandler);
		REG_CMD(GetSequenceAnimGroup);
		REG_CMD(QueueObjectiveText);
		REG_CMD(QueueCinematicText);
		REG_TYPED_CMD(ar_SortEditor, Array);
		REG_CMD(SetUIUpdateSound);
		REG_CMD(GetActorValueAlt);
		REG_CMD(ModActorValueAlt);
		REG_CMD(SetActorValueAlt);
		REG_CMD(ForceActorValueAlt);
		REG_CMD(DamageActorValueAlt);
		REG_CMD(RestoreActorValueAlt);
		REG_CMD(HighlightBodyPartAlt);
		REG_CMD(DeactivateAllHighlightsAlt);
		REG_CMD(SetJohnnyOnCompleteQuestEventHandler);
		REG_CMD(SetJohnnyOnFailQuestEventHandler);
		REG_CMD(IsDLLLoaded);
		REG_CMD(SetJohnnyOnSettingsUpdateEventHandler);
		REG_CMD(GetQuestDelay);
		REG_CMD(GetNearestCompassHostileDirection);
		REG_TYPED_CMD(GetNearestCompassHostile, Form);
		REG_CMD(RefreshIdle);
		REG_CMD(SetNoteRead);
		REG_CMD(SetDisablePlayerControlsHUDVisibilityFlags);
		REG_CMD(GetCameraTranslation);
		REG_CMD(IsCompassHostile);
		REG_CMD(SetMessageIconPath);
		REG_TYPED_CMD(GetMessageIconPath, String);
		REG_CMD(ExitGameAlt);
		REG_CMD(ToggleCombatMusic);
		REG_CMD(IsCombatMusicEnabled);
		REG_CMD(SetJohnnyOnAddPerkEventHandler);
		REG_CMD(SetJohnnyOnRemovePerkEventHandler);
		REG_CMD(IsHostilesNearby);
		REG_CMD(ModNthTempEffectTimeLeft);
		REG_TYPED_CMD(GetWeaponWorldModelPath, String);
		REG_TYPED_CMD(GetBodyPartTraitString, String);
		REG_CMD(GetActorEffectType);
		REG_CMD(GetTextureWidth);
		REG_CMD(GetTextureHeight);
		REG_CMD(GetTextureFormat);
		REG_CMD(GetTextureMipMapCount);
		REG_CMD(GetCalculatedSpread);
		REG_CMD(SendStealingAlarm);
		REG_CMD(ApplyWeaponPoison);
		REG_TYPED_CMD(GetTalkingActivatorActor, Form);
		REG_TYPED_CMD(GetPlayerKarmaTitle, String);
		REG_TYPED_CMD(GetCompassHostiles, Array);
		REG_CMD(ToggleDisableSaves);
		REG_CMD(SetJohnnyOnRenderUpdateEventHandler);
		REG_CMD(WorldToScreen);
		REG_CMD(GetFaceGenNthProperty);
		REG_CMD(SetFaceGenNthProperty);
		REG_CMD(FaceGenRefreshAppearance);
		REG_CMD(SendTrespassAlarmAlt);
		REG_CMD(IsCrimeOrEnemy);
		REG_TYPED_CMD(GetAvailablePerks, Array);
		g_scriptInterface = (NVSEScriptInterface*)nvse->QueryInterface(kInterface_Script);
		g_cmdTableInterface = (NVSECommandTableInterface*)nvse->QueryInterface(kInterface_CommandTable);
		s_strArgBuf = (char*)malloc((sizeof(char)) * 1024);
		g_arrInterface = (NVSEArrayVarInterface*)nvse->QueryInterface(kInterface_ArrayVar);
		g_strInterface = (NVSEStringVarInterface*)nvse->QueryInterface(kInterface_StringVar);

		if (!nvse->isEditor) {
			NVSEDataInterface* nvseData = (NVSEDataInterface*)nvse->QueryInterface(kInterface_Data);
			InventoryRefGetForID = (InventoryRef * (*)(UInt32))nvseData->GetFunc(NVSEDataInterface::kNVSEData_InventoryReferenceGetForRefID);
			CaptureLambdaVars = (_CaptureLambdaVars)nvseData->GetFunc(NVSEDataInterface::kNVSEData_LambdaSaveVariableList);
			UncaptureLambdaVars = (_UncaptureLambdaVars)nvseData->GetFunc(NVSEDataInterface::kNVSEData_LambdaUnsaveVariableList);
			HandleGameHooks();
			HandleEventHooks();
			ExtractArgsEx = g_scriptInterface->ExtractArgsEx;
		}
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
		case (DLL_PROCESS_ATTACH):
			JohnnyHandle = (HMODULE)hDllHandle;
			DisableThreadLibraryCalls((HMODULE)hDllHandle);
			break;
		}
		return TRUE;
	}
};