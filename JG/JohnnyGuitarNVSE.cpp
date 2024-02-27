#include <windows.h>
#include <tchar.h>
#include <psapi.h>
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
#include "nvse/GameScript.h"
#include "nvse/SafeWrite.h"
#include "nvse/ScriptUtils.h"
#include "misc/WorldToScreen.h"
#include "events/LambdaVariableContext.h"
#include "events/JohnnyEventPredefinitions.h"
#include "misc/misc.h"
#include "misc/EditorIDs.h"
#include "internal/decoding.h"
#include "nvse/GameSettings.h"
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
#include "functions/fn_book.h"
#include "functions/fn_dial.h"
#include "events/CustomEventFilters.h"
#include "events/JohnnyEvents.h"
#include "internal/serialization.h"
HMODULE JohnnyHandle;
_CaptureLambdaVars CaptureLambdaVars;
_UncaptureLambdaVars UncaptureLambdaVars;
NiTMap<const char*, TESForm*>** g_gameFormEditorIDsMap = reinterpret_cast<NiTMap<const char*, TESForm*>**>(0x11C54C8);
#define JG_VERSION 500
void MessageHandler(NVSEMessagingInterface::Message* msg) {
	switch (msg->type) {
		case NVSEMessagingInterface::kMessage_NewGame:
		case NVSEMessagingInterface::kMessage_PreLoadGame:
		{
			disableMuzzleLights = 0; //reset the muzzle hook every time
			bArrowKeysDisabled = false;
			isShowLevelUp = true;
			ThisStdCall(0x8C17C0, g_thePlayer); // reevaluate reload speed modifiers
			ThisStdCall(0x8C1940, g_thePlayer); // reevaluate equip speed modifiers

			OnDyingHandler->FlushEventCallbacks();
			OnLimbGoneHandler->FlushEventCallbacks();
			OnCrosshairHandler->FlushEventCallbacks();
			OnPLChangeHandler->FlushEventCallbacks();
			RestoreDisabledPlayerControlsHUDFlags();
			SaveGameUMap.clear();
			ResetMiscStatMap();
			haircutSetList.dFlush();
			beardSetList.dFlush();
			break;
		}
		case NVSEMessagingInterface::kMessage_MainGameLoop:
			for (const auto& EventInfo : EventsArray) {
				EventInfo->AddQueuedEvents();
				EventInfo->DeleteEvents();
			}
			if (!g_statsMenu) g_statsMenu = StatsMenu::Get();
			if (g_statsMenu && g_interfaceManager && g_interfaceManager->IsMenuVisible(kMenuType_Stats) && recalculateStatFilters) {
				recalculateStatFilters = 0;
				g_statsMenu->miscStatIDList.Filter(ShouldHideStat);

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
			DumpModules();
			Console_Print("JohnnyGuitar version: %.2f", ((float)JG_VERSION / 100));
			break;
		}
		default:
			break;
	}
}

extern "C" {
	bool NVSEPlugin_Query(const NVSEInterface* nvse, PluginInfo* info) {
		// fill out the info structure
		gLog.Create("JohnnyGuitarNVSE.log");
#if _DEBUG
		s_debug.Create("JohnnyGuitarNVSE_debug.log");
#endif
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "JohnnyGuitarNVSE";
		info->version = JG_VERSION;

		if (nvse->isNogore) {
			PrintLog("German NoGore release of the game is not supported");
			return false;
		}

		if (nvse->nvseVersion < 0x6020030) {
			PrintLog("NVSE version is outdated. This plugin requires v6.2.3 minimum.");
			return false;
		}

		if (!nvse->isEditor) {
			if (nvse->runtimeVersion < RUNTIME_VERSION_1_4_0_525) {
				PrintLog("incorrect New Vegas version (got %08X need at least %08X)", nvse->runtimeVersion, RUNTIME_VERSION_1_4_0_525);
				return false;
			}
		}
		else {
			if (nvse->editorVersion < CS_VERSION_1_4_0_518) {
				PrintLog("incorrect GECK version (got %08X need at least %08X)", nvse->editorVersion, CS_VERSION_1_4_0_518);
				return false;
			}
		};

		// version checks pass
		PrintLog("JohnnyGuitarNVSE %u Loaded succesfully.", info->version);
		char filename[MAX_PATH];
		GetModuleFileNameA(JohnnyHandle, filename, MAX_PATH);
		return true;
	}

	bool NVSEPlugin_Load(const NVSEInterface* nvse) {
		((NVSEMessagingInterface*)nvse->QueryInterface(kInterface_Messaging))->RegisterListener(nvse->GetPluginHandle(), "NVSE", MessageHandler);
		char filename[MAX_PATH];
		GetModuleFileNameA(NULL, filename, MAX_PATH);
		strncpy(g_workingDir, filename, (strlen(filename)-13));
		strcpy((char*)(strrchr(filename, '\\') + 1), "Data\\nvse\\plugins\\JohnnyGuitar.ini");
		loadEditorIDs = 1;
		fixHighNoon = 0;
		fixFleeing = GetPrivateProfileInt("MAIN", "bFixFleeing", 1, filename);
		fixItemStacks = GetPrivateProfileInt("MAIN", "bFixItemStackCount", 1, filename);
		fixNPCShootingAngle = GetPrivateProfileInt("MAIN", "bFixNPCShootingAngle", 1, filename);
		capLoadScreensToFrametime = GetPrivateProfileInt("MAIN", "iIncreaseFPSLimitLoadScreen", 0, filename);
		noMuzzleFlashCooldown = GetPrivateProfileInt("MAIN", "bNoMuzzleFlashCooldown", 0, filename);
		resetVanityCam = GetPrivateProfileInt("MAIN", "bReset3rdPersonCamera", 0, filename);
		enableRadioSubtitles = GetPrivateProfileInt("MAIN", "bEnableRadioSubtitles", 0, filename);
		removeMainMenuMusic = GetPrivateProfileInt("MAIN", "bRemoveMainMenuMusic", 0, filename);
		fixDeathSounds = GetPrivateProfileInt("MAIN", "bFixDeathVoicelines", 1, filename);
		patchPainedPlayer = GetPrivateProfileInt("MAIN", "bRemovePlayerPainExpression", 0, filename);
		iDeathSoundMAXTimer = GetPrivateProfileInt("DeathResponses", "iDeathSoundMAXTimer", 10, filename); //Hidden, don't actually expose it in the INI
		//bDisableDeathResponses = GetPrivateProfileInt("DeathResponses", "bDisableDeathResponses", 0, filename);
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
		REG_CMD(GetThresholdedActorValue);
		REG_CMD(GetEffectShaderTraitNumeric);
		REG_CMD(SetEffectShaderTraitNumeric);
		REG_TYPED_CMD(GetEffectShaderTexturePath, String);
		REG_CMD(SetEffectShaderTexturePath);
		REG_CMD(GetSystemColor);
		REG_CMD(RGBtoHSV);
		REG_CMD(HSVtoRGB);
		REG_CMD(GetLocationSpecificLoadScreensOnly);
		REG_TYPED_CMD(GetArmorAltTextures, Array);
		REG_CMD(GetIdleMarkerTraitNumeric);
		REG_TYPED_CMD(GetIdleMarkerAnimations, Array);
		REG_CMD(SetIdleMarkerTraitNumeric);
		REG_CMD(SetIdleMarkerAnimation);
		REG_CMD(SetIdleMarkerAnimations);
		REG_TYPED_CMD(GetWeaponAltTextures, Array);
		REG_TYPED_CMD(GetRefActivationPromptOverride, String);
		REG_CMD(SetRefActivationPromptOverride);
		REG_CMD(GetTerminalMenuItemFlags);
		REG_CMD(SetTerminalMenuItemFlags);
		REG_TYPED_CMD(GetLocationName, String);
		REG_TYPED_CMD(GetRegionMapName, String);
		REG_CMD(SetRegionMapName);
		REG_CMD(GetRGBColor);
		REG_TYPED_CMD(GetPlayingEffectShaders, Array);
		REG_CMD(GetBookFlags);
		REG_CMD(SetBookFlags);
		REG_CMD(GetBookSkill);
		REG_CMD(SetBookSkill);
		REG_CMD(SetOnActorValueChangeEventHandler);
		REG_CMD(RefreshTerminalMenu);
		REG_CMD(SetRefEncounterZone);
		REG_TYPED_CMD(GetRefEncounterZone, Form);
		REG_CMD(SetCellEncounterZone);
		REG_CMD(SetWorldspaceEncounterZone);
		REG_TYPED_CMD(GetWorldspaceEncounterZone, Form);
		REG_CMD(UpdateCrosshairPrompt);
		REG_CMD(GetLightingTemplateTraitNumeric);
		REG_CMD(SetLightingTemplateTraitNumeric);
		REG_TYPED_CMD(GetLightingTemplateCell, Form);
		REG_CMD(SetLightingTemplateCell);
		REG_CMD(RemoveScopeModelPath);
		REG_TYPED_CMD(GetNthRegionWeatherType, Form);
		REG_CMD(GetNthRegionWeatherChance);
		REG_TYPED_CMD(GetNthRegionWeatherGlobal, Form);
		REG_CMD(PlaySoundFile);
		REG_CMD(StopSoundFile);
		REG_CMD(StopSoundLooping);
		REG_CMD(GetSystemColorAlt);
		REG_CMD(SetCustomReputationChangeIcon);
		REG_CMD(SetArmorAltTexture);
		REG_CMD(SetWeaponAltTexture);
		REG_CMD(ClearWeaponAltTexture);
		REG_CMD(ClearArmorAltTexture);
		REG_CMD(AddNavmeshObstacle);
		REG_CMD(RemoveNavmeshObstacle);
		REG_CMD(RollCredits);
		REG_CMD(GetFactionFlags);
		REG_CMD(SetFactionFlags);
		REG_TYPED_CMD(GetLandTextureUnderFeet, Form);
		REG_CMD(SetOnProcessLevelChangeEventHandler);
		REG_CMD(GetExtraMiscStat);
		REG_CMD(ModExtraMiscStat);
		REG_CMD(GetMoonPhase);
		REG_TYPED_CMD(GetFormRecipesAlt, Array);
		REG_CMD(RewardKarmaAlt);
		REG_CMD(GetPackedPlayerFOV);
		REG_CMD(DialogResponseAddRelatedTopic);
		REG_TYPED_CMD(DialogResponseRelatedGetAll, Array);
		REG_CMD(GetPlayerCamFOV);
		REG_CMD(ShowBarberMenuEx);
		REG_CMD(InitExtraMiscStat);
		REG_CMD(TriggerScreenSplatterEx);
		REG_CMD(SetViewmodelClipDistance);
		REG_CMD(GetViewmodelClipDistance);
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
			SerializationInit(nvse);
		}
		return true;
	}
	BOOL WINAPI DllMain(
		HANDLE  hDllHandle,
		DWORD   dwReason,
		LPVOID  lpreserved
	) {
		switch (dwReason) {
			case (DLL_PROCESS_ATTACH):
				JohnnyHandle = (HMODULE)hDllHandle;
				DisableThreadLibraryCalls((HMODULE)hDllHandle);
				break;
		}
		return TRUE;
	}
};
