#include "JohnnyCommands.hpp"
#include <PluginAPI.h>

#include "functions/fn_av.h"
#include "functions/fn_book.h"
#include "functions/fn_dial.h"
#include "functions/fn_event.h"
#include "functions/fn_file.h"
#include "functions/fn_form.h"
#include "functions/fn_gamebryo.h"
#include "functions/fn_gameplay.h"
#include "functions/fn_math.h"
#include "functions/fn_mediaset.h"
#include "functions/fn_region.h"
#include "functions/fn_terminal.h"
#include "functions/fn_ui.h"
#include "functions/fn_utility.h"

#include "JG/JohnnyPluginData.hpp"
#include "JG/DisabledSaves.hpp"
#include "JG/CustomHUDShake.hpp"
#include "JG/AnimActivationHeight.hpp"

#define REG_CMD(name) apNVSE->RegisterCommand(&kCommandInfo_##name);
#define REG_TYPED_CMD(name, type) apNVSE->RegisterTypedCommand(&kCommandInfo_##name,kRetnType_##type);

ExpressionEvaluatorUtils s_expEvalUtils;

namespace JohnnyCommands {

	void InitCommandData() {
		AnimActivationHeight::Init();
	}

	void Init(const NVSEInterface* apNVSE) {
		if (apNVSE->isEditor == 0) {
			InitCommandData();
			apNVSE->InitExpressionEvaluatorUtils(&s_expEvalUtils);
		}

		apNVSE->SetOpcodeBase(JohnnyPluginData::JG_OPCODE_BASE);

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
		REG_CMD(NullArgs); //formerly UwUDelete.
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
		REG_CMD(FaceGenGetNthProperty);
		REG_CMD(FaceGenSetNthProperty);
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
		REG_CMD(SetBlockTransform);
		REG_CMD(RefAddrxData);
		REG_CMD(AudioMarkerGetController);
		REG_CMD(AudioMarkerSetController);
		REG_CMD(AudioMarkerGetProperty);
		REG_CMD(AudioMarkerSetProperty);
		REG_CMD(IsRadioRefPlaying);
		REG_CMD(TuneRadioRef);
		REG_TYPED_CMD(GetAllGameRadios, Array);
		REG_TYPED_CMD(GetAvailableRadios, Array);
		REG_CMD(SetJohnnyOnRadioPostSoundAttachEventHandler);
		REG_CMD(AudioMarkerGetCurrent);
		REG_CMD(HideItemBarterEx);
		REG_CMD(IsItemBarterHiddenEx);
		REG_CMD(GetCurrentFurnitureRef);
		REG_CMD(SetCameraShakeNoHUDShudder);
		REG_CMD(GameGetSecondsPassed);
		REG_CMD(SetJohnnyOnKeyboardControllerSelectionChangeEventHandler);
		REG_CMD(IsBSALoaded);
		REG_TYPED_CMD(GetTempIngestibleEffects, Array);
		REG_CMD(PlaySoundFade);
		REG_TYPED_CMD(GetPointInNavMesh, Array);
		REG_TYPED_CMD(GetNearestNavMeshTriangle, Array);
		REG_TYPED_CMD(GetAltTexturesEx, Array);
		REG_CMD(HasHealthDamageEffect);
		REG_CMD(SetAlwaysRun);
		REG_CMD(SetAutoMove);
		REG_CMD(SetActorMovementFlags);
		REG_CMD(PushUIQuestToTop);
		REG_CMD(SetExtraAccuracyPenaltyMult);
		REG_CMD(RemoveExtraAccuracyPenaltyMult);
		REG_CMD(SetJohnnyOnSleepWaitEventHandler);
		REG_CMD(GetExtraAccuracyPenaltyMult);
		REG_CMD(SetCustomMapMarker);
		REG_CMD(ClearCustomMapMarker);
		REG_CMD(EjectCasing);
		REG_TYPED_CMD(GetNoteSpeaker, Form);
		REG_CMD(SetNoteSpeaker);
		REG_CMD(GetNoteType);
		REG_CMD(SetNoteType);
		REG_TYPED_CMD(GetNoteSound, Form);
		REG_CMD(SetNoteSound);
		REG_TYPED_CMD(GetNoteTopic, Form);
		REG_CMD(SetNoteTopic);
		REG_TYPED_CMD(GetNoteImage, String);
		REG_CMD(SetNoteImage);
		REG_TYPED_CMD(GetNoteQuestList, Array);
		REG_CMD(AddNoteQuest);
		REG_CMD(RemoveNoteQuest);
		REG_CMD(SetHUDShudderPower);
		REG_CMD(GetHUDShudderPower);
		REG_CMD(SetDialogResponseOverrideValues); // do not document
		REG_CMD(SetMediaLocationControllerOverride); // do not document
		REG_CMD(ClearMediaLocationControllerOverride); // do not document
		REG_CMD(GetCasinoWinnings);
		REG_CMD(SetCasinoWinnings);
		REG_CMD(GetAcousticSpace);
		REG_CMD(SetAcousticSpace);
		REG_CMD(SetCameraTranslate);
		REG_CMD(SetCameraRotate);
		REG_CMD(PlayHolotape);
		REG_CMD(StopHolotape);
		REG_CMD(SetOnTakeBackItemEventHandler);
		REG_TYPED_CMD(GetCasinoDeckTexture, String);
		REG_CMD(SetCasinoDeckTexture);
		REG_TYPED_CMD(GetCasinoChip, Form);
		REG_CMD(SetCasinoChip);
		REG_TYPED_CMD(GetCustomMapMarkerIcon, String);
		REG_CMD(GetSleepWaitMenuState);
		REG_CMD(SetOnNPCResponseEventHandler);
		REG_CMD(PlaySoundFromPath);
		REG_CMD(PlaySound3DFromPath);
		REG_CMD(StopSoundFromPath);
		REG_CMD(StopSound3DFromPath);
		REG_CMD(IsSoundPlayingFromPath);
		REG_CMD(SetOnGeneralSubtitleEventHandler);
		REG_CMD(PathToRef);
		REG_CMD(SetOnReputationChangeEventHandler);
		REG_CMD(IsNiSequenceActive);
		REG_CMD(GetHotkeySlot);
		REG_CMD(SetOnNPCActorValueChangeEventHandler);
		REG_CMD(GetGrenadeHoldTime);
		REG_CMD(RemoveHighlightedRef);
		REG_CMD(GetSaidOnce);
		REG_CMD(SetSaidOnce);
		REG_TYPED_CMD(GetTopicInfo, Array);
		REG_CMD(IsMenuPaused);
		REG_CMD(IsInDialogueWithPlayer);
		REG_CMD(SetHUDVisibilityOverride);
		REG_CMD(GetHUDVisibilityOverride);
		REG_CMD(UpdateRepairMenu);
		REG_TYPED_CMD(GetWeaponsForMod, Array);
		REG_CMD(GetMineArmedEx);
		REG_CMD(SetMusicTypePath);
		REG_TYPED_CMD(GetParentTopic, Form);
		REG_CMD(GetCameraShotTraitNumeric);
		REG_CMD(SetCameraShotTraitNumeric);
		REG_CMD(GetCameraShotFlags);
		REG_CMD(SetCameraShotFlags);
		REG_CMD(GetCameraShotPath);
		REG_CMD(SetCameraShotPath);
		REG_TYPED_CMD(GetCameraShotImageSpaceModifier, Form);
		REG_CMD(SetCameraShotImageSpaceModifier);
		REG_CMD(SetAlphaPropertyValue);
		REG_CMD(GetAlphaPropertyValue);
		REG_CMD(SetStencilPropertyValue);
		REG_CMD(GetStencilPropertyValue);
		REG_CMD(PathToPoint);
		REG_CMD(GetYieldTimer);
		REG_CMD(SetYieldTimer);
		REG_CMD(SetSwitchNodeIndex);
		REG_CMD(GetSwitchNodeIndex);
		REG_CMD(SetNiLODLevel);
		REG_CMD(GetNiLODLevel);
		REG_CMD(SetWeaponScopeUIModel);
		REG_CMD(ToggleWeaponScopeUIModel);
		REG_CMD(ClearWeaponScopeUIModel);
		REG_CMD(UpdateScenegraph);
		REG_TYPED_CMD(GetNiBound, Array);
		REG_CMD(CallPerRef);
		REG_CMD(CallPerRefEx);
		REG_CMD(CallPerMobileObject);
		REG_CMD(CallPerMobileObjectEx);
		REG_CMD(Update3DAlt);
		REG_CMD(SetNiPSysModifierValue);
		REG_TYPED_CMD(GetNiPSysModifierValue, Default);
		REG_TYPED_CMD(ar_Shuffle, Array);
		REG_CMD(GetRecipeCategoryFlags);
		REG_CMD(GetCurrentSkyColor);
		REG_CMD(RemapLand);
		REG_CMD(SetParticleEmitterSpawnRate);
		REG_CMD(GetParticleEmitterSpawnRate);
		REG_TYPED_CMD(GetItemEffectString, String);
		REG_CMD(ApplyModelTextureSwap);
		REG_CMD(StopIdleLoop);
		REG_CMD(SetIKState);
		REG_CMD(GetIKState);
		REG_CMD(IsCarryable);
		REG_CMD(PickIdleEx);
		REG_CMD(GetUsedItemHeight);
		REG_CMD(GetMenuItemListIndex);
		REG_CMD(SelectMenuItemListIndex);
		REG_CMD(StopNiSequence);
		REG_CMD(GetPCInRootWorldspace);
		REG_TYPED_CMD(GetPCRootWorldspace, Form);
		REG_TYPED_CMD(GetAltTextures, Array);
		REG_CMD(SetAltTexture);
		REG_CMD(ClearAltTexture);
		REG_CMD(SetNiLightValue);
		REG_CMD(GetNiLightValue);
		REG_CMD(SetNiLightColor);
		REG_CMD(GetNiLightColor);
	}

}

#undef REG_TYPED_CMD
#undef REG_CMD