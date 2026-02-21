#pragma once

#include "Setting.hpp"
#include "SettingCollectionList.hpp"

class INISettingCollection : public SettingCollectionList<Setting> {
public:
	static constexpr AddressPtr<Setting, 0x11C77C0> iLastHDRSetting;
	static constexpr AddressPtr<Setting, 0x11C7B08> bUseWaterHDR;
	static constexpr AddressPtr<Setting, 0x11CA2DC> bPrimitivesOn;
	static constexpr AddressPtr<Setting, 0x11D2334> iConcentricLengthMinHard;
	static constexpr AddressPtr<Setting, 0x11D273C> iConcentricLengthMaxVeryEasy;
	static constexpr AddressPtr<Setting, 0x11D2BC8> iConcentricLengthMinAverage;
	static constexpr AddressPtr<Setting, 0x11D2FB8> iConcentricLengthMaxHard;
	static constexpr AddressPtr<Setting, 0x11D321C> iSweetSpotLengthMaxVeryHard;
	static constexpr AddressPtr<Setting, 0x11D3378> iSweetSpotLengthMaxEasy;
	static constexpr AddressPtr<Setting, 0x11D3678> iConcentricLengthMinVeryEasy;
	static constexpr AddressPtr<Setting, 0x11D38C4> iSweetSpotLengthMinVeryHard;
	static constexpr AddressPtr<Setting, 0x11D39A8> iSweetSpotLengthMinAverage;
	static constexpr AddressPtr<Setting, 0x11D4240> iConcentricLengthMinEasy;
	static constexpr AddressPtr<Setting, 0x11D4258> iConcentricLengthMaxEasy;
	static constexpr AddressPtr<Setting, 0x11D43A8> iSweetSpotLengthMinEasy;
	static constexpr AddressPtr<Setting, 0x11D4744> iConcentricLengthMaxVeryHard;
	static constexpr AddressPtr<Setting, 0x11D48C4> iSweetSpotLengthMinHard;
	static constexpr AddressPtr<Setting, 0x11D4AA4> iSweetSpotLengthMinVeryEasy;
	static constexpr AddressPtr<Setting, 0x11D4BA0> iConcentricLengthMaxAverage;
	static constexpr AddressPtr<Setting, 0x11D4BDC> iSweetSpotLengthMaxVeryEasy;
	static constexpr AddressPtr<Setting, 0x11D4C18> iSweetSpotLengthMaxAverage;
	static constexpr AddressPtr<Setting, 0x11D4DD4> iSweetSpotLengthMaxHard;
	static constexpr AddressPtr<Setting, 0x11D50D4> iConcentricLengthMinVeryHard;
	static constexpr AddressPtr<Setting, 0x11DCFF4> fWeaponInteriorFarAttenuationMod;
	static constexpr AddressPtr<Setting, 0x11DD008> fWeaponInteriorNearVolumeMod;
	static constexpr AddressPtr<Setting, 0x11DD034> fWeaponInteriorFarVolumeMod;
	static constexpr AddressPtr<Setting, 0x11DD0AC> fWeaponInteriorNearAttenuationMod;
	static constexpr AddressPtr<Setting, 0x11DF6E0> iDetectionHighNumPicks;
	static constexpr AddressPtr<Setting, 0x11E0824> fPC360ControllerMouseYMult;
	static constexpr AddressPtr<Setting, 0x11E0994> fPC360ControllerMouseXMult;
	static constexpr AddressPtr<Setting, 0x11E0E64> iLowProcessingMilliseconds;
	static constexpr AddressPtr<Setting, 0x11F1C94> fLowPerfCombatantVoiceDistance;
	static constexpr AddressPtr<Setting, 0x11F2B5C> fAvoidanceAvoidNodeCost;
	static constexpr AddressPtr<Setting, 0x11F3368> sDefaultTexAtlas;

	struct AnimationWarning {
		static constexpr AddressPtr<Setting, 0x11C5734> bClampWarning;
		static constexpr AddressPtr<Setting, 0x11C5750> bPriorityWarning;
	};

	struct Archive {
		static constexpr AddressPtr<Setting, 0x11DEBDC> bCheckRuntimeCollisions;
		static constexpr AddressPtr<Setting, 0x11DEC4C> bInvalidateOlderFiles;
		static constexpr AddressPtr<Setting, 0x11DEE3C> bUseArchives;
		static constexpr AddressPtr<Setting, 0x11DEB24> iRetainDirectoryStringTable;
		static constexpr AddressPtr<Setting, 0x11DEC40> iRetainFilenameOffsetTable;
		static constexpr AddressPtr<Setting, 0x11DEAA0> iRetainFilenameStringTable;
		static constexpr AddressPtr<Setting, 0x11DEB94> sArchiveList;
		static constexpr AddressPtr<Setting, 0x11DEC68> sInvalidationFile;
	};

	struct Audio {
		static constexpr AddressPtr<Setting, 0x11F6D9C> bEnableAudio;
		static constexpr AddressPtr<Setting, 0x11F6EBC> bEnableAudioCache;
		static constexpr AddressPtr<Setting, 0x11F7130> bEnableEnviroEffectsOnPC;
		static constexpr AddressPtr<Setting, 0x11F6DFC> bMultiThreadAudio;
		static constexpr AddressPtr<Setting, 0x11F6E5C> bUseAudioDebugInformation;
		static constexpr AddressPtr<Setting, 0x11DD094> fASFadeInTime;
		static constexpr AddressPtr<Setting, 0x11DD050> fASFadeOutTime;
		static constexpr AddressPtr<Setting, 0x11DD044> fASFadeStartTime;
		static constexpr AddressPtr<Setting, 0x11F6E68> fAudioDebugDelay;
		static constexpr AddressPtr<Setting, 0x11DDD0C> fChainLargeMassMin;
		static constexpr AddressPtr<Setting, 0x11DDCEC> fChainMediumMassMin;
		static constexpr AddressPtr<Setting, 0x11DD8E8> fCollisionSoundHeavyThreshold;
		static constexpr AddressPtr<Setting, 0x11DD62C> fCreatureRadioMax;
		static constexpr AddressPtr<Setting, 0x11DD5B0> fCreatureRadioMin;
		static constexpr AddressPtr<Setting, 0x11E060C> fDBVoiceAttenuationIn2D;
		static constexpr AddressPtr<Setting, 0x11F6DC0> fDawnTime;
		static constexpr AddressPtr<Setting, 0x11F6DCC> fDayTime;
		static constexpr AddressPtr<Setting, 0x11DF70C> fDialogHitSoundCooldownMax;
		static constexpr AddressPtr<Setting, 0x11DF73C> fDialogHitSoundCooldownMin;
		static constexpr AddressPtr<Setting, 0x11F6DB4> fDialogMaxDistance;
		static constexpr AddressPtr<Setting, 0x11F6DA8> fDialogMinDistance;
		static constexpr AddressPtr<Setting, 0x11F6E80> fDialogueFadeDecibels;
		static constexpr AddressPtr<Setting, 0x11F6E8C> fDialogueFadeSecondsIn;
		static constexpr AddressPtr<Setting, 0x11F6E98> fDialogueFadeSecondsOut;
		static constexpr AddressPtr<Setting, 0x11C6528> fDialogueHeadPitchExaggeration;
		static constexpr AddressPtr<Setting, 0x11C6534> fDialogueHeadRollExaggeration;
		static constexpr AddressPtr<Setting, 0x11C651C> fDialogueHeadYawExaggeration;
		static constexpr AddressPtr<Setting, 0x11F6DD8> fDuskTime;
		static constexpr AddressPtr<Setting, 0x11DD9BC> fEarthLargeMassMin;
		static constexpr AddressPtr<Setting, 0x11DD918> fEarthMediumMassMin;
		static constexpr AddressPtr<Setting, 0x11F7154> fFilterDistortionGain;
		static constexpr AddressPtr<Setting, 0x11F7160> fFilterPEQGain;
		static constexpr AddressPtr<Setting, 0x11F716C> fFilterdBAttenuation;
		static constexpr AddressPtr<Setting, 0x11DD93C> fGlassLargeMassMin;
		static constexpr AddressPtr<Setting, 0x11DDCC4> fGlassMediumMassMin;
		static constexpr AddressPtr<Setting, 0x11DF6EC> fHardLandingDamageThreshold;
		static constexpr AddressPtr<Setting, 0x11DD97C> fLargeWeaponSpeedMax;
		static constexpr AddressPtr<Setting, 0x11DDCD4> fLargeWeaponWeightMin;
		static constexpr AddressPtr<Setting, 0x11DD084> fMainMenuMusicVolume;
		static constexpr AddressPtr<Setting, 0x11F6E74> fMasterVolumeMult;
		static constexpr AddressPtr<Setting, 0x11DD900> fMaxFootstepDistance;
		static constexpr AddressPtr<Setting, 0x11DD8BC> fMediumWeaponSpeedMax;
		static constexpr AddressPtr<Setting, 0x11DDCB8> fMediumWeaponWeightMin;
		static constexpr AddressPtr<Setting, 0x11DD8CC> fMetalLargeMassMin;
		static constexpr AddressPtr<Setting, 0x11DD8F4> fMetalMediumMassMin;
		static constexpr AddressPtr<Setting, 0x11CC270> fMinSoundVel;
		static constexpr AddressPtr<Setting, 0x11F6DE4> fNightTime;
		static constexpr AddressPtr<Setting, 0x11DD988> fPlayerFootVolume;
		static constexpr AddressPtr<Setting, 0x11DD5A4> fRadioDialogMute;
		static constexpr AddressPtr<Setting, 0x11DD580> fRadioStaticAtOuterRadiusPct;
		static constexpr AddressPtr<Setting, 0x11DD06C> fRegionLoopFadeInTime;
		static constexpr AddressPtr<Setting, 0x11DCFE4> fRegionLoopFadeOutTime;
		static constexpr AddressPtr<Setting, 0x11DD924> fSkinLargeMassMin;
		static constexpr AddressPtr<Setting, 0x11DD9A0> fSkinMediumMassMin;
		static constexpr AddressPtr<Setting, 0x11DD9B0> fStoneLargeMassMin;
		static constexpr AddressPtr<Setting, 0x11DD9C8> fStoneMediumMassMin;
		static constexpr AddressPtr<Setting, 0x11DD9D8> fWoodLargeMassMin;
		static constexpr AddressPtr<Setting, 0x11DD930> fWoodMediumMassMin;
		static constexpr AddressPtr<Setting, 0x11F6EB0> iAttenuationDialogMenuMute;
		static constexpr AddressPtr<Setting, 0x11F6EA4> iAttenuationEffectiveSilence;
		static constexpr AddressPtr<Setting, 0x11F6EC8> iAudioCacheSize;
		static constexpr AddressPtr<Setting, 0x11F6EE0> iAudioHWThread;
		static constexpr AddressPtr<Setting, 0x11DD968> iCollisionSoundTimeDelta;
		static constexpr AddressPtr<Setting, 0x11F713C> iMaxFX;
		static constexpr AddressPtr<Setting, 0x11DDCE0> iMaxImpactSoundCount;
		static constexpr AddressPtr<Setting, 0x11F6ED4> iMaxSizeForCachedSound;
		static constexpr AddressPtr<Setting, 0x11DCFD4> iMusicSynchOverride;
		static constexpr AddressPtr<Setting, 0x11DD060> iMusicTransitionInMS;
		static constexpr AddressPtr<Setting, 0x11DD614> iRadioStationTimeout;
		static constexpr AddressPtr<Setting, 0x11DD5CC> iRadioUpdateInterval;
		static constexpr AddressPtr<Setting, 0x11F7148> iVoiceDecodeBufferSize;
	};

	struct BackgroundLoad {
		static constexpr AddressPtr<Setting, 0x11C9670> bBackgroundCellLoads;
		static constexpr AddressPtr<Setting, 0x11E05EC> bBackgroundLoadLipFiles;
		static constexpr AddressPtr<Setting, 0x11D5A24> bLoadBackgroundFaceGen;
		static constexpr AddressPtr<Setting, 0x11C5EF0> bLoadHelmetsInBackground;
		static constexpr AddressPtr<Setting, 0x11C3C10> bSelectivePurgeUnusedOnFastTravel;
		static constexpr AddressPtr<Setting, 0x11DECAC> bUseBackgroundFileLoader;
		static constexpr AddressPtr<Setting, 0x11D5A10> bUseMultiThreadedFaceGen;
		static constexpr AddressPtr<Setting, 0x11C3D1C> bUseMultiThreadedTrees;
		static constexpr AddressPtr<Setting, 0x11C5778> iAnimationClonePerLoop;
		static constexpr AddressPtr<Setting, 0x1202DA8> iPostProcessMilliseconds;
		static constexpr AddressPtr<Setting, 0x1202DC0> iPostProcessMillisecondsEditor;
		static constexpr AddressPtr<Setting, 0x1202DB4> iPostProcessMillisecondsLoadingQueuedPriority;
		static constexpr AddressPtr<Setting, 0x1202DCC> iPostProcessTaskWarningMilliseconds;
	};

	struct BlurShader {
		static constexpr AddressPtr<Setting, 0x11C71F4> fAlphaAddExterior;
		static constexpr AddressPtr<Setting, 0x11C74F8> fAlphaAddInterior;
		static constexpr AddressPtr<Setting, 0x11C761C> fBlurRadius;
		static constexpr AddressPtr<Setting, 0x11C768C> fSIEmmisiveMult;
		static constexpr AddressPtr<Setting, 0x11C7314> fSISpecularMult;
		static constexpr AddressPtr<Setting, 0x11C774C> fSkyBrightness;
		static constexpr AddressPtr<Setting, 0x11C72A0> fSunBrightness;
		static constexpr AddressPtr<Setting, 0x11C7170> fSunlightDimmer;
		static constexpr AddressPtr<Setting, 0x11C723C> iBlendType;
		static constexpr AddressPtr<Setting, 0x11C740C> iBlurTexSize;
		static constexpr AddressPtr<Setting, 0x11C73B8> iNumBlurpasses;
	};

	struct BlurShaderHDR {
		static constexpr AddressPtr<Setting, 0x11C74C4> fBlurRadius;
		static constexpr AddressPtr<Setting, 0x11C7200> fBrightClamp;
		static constexpr AddressPtr<Setting, 0x11C7230> fBrightScale;
		static constexpr AddressPtr<Setting, 0x11C7698> fEmissiveHDRMult;
		static constexpr AddressPtr<Setting, 0x11C7260> fEyeAdaptSpeed;
		static constexpr AddressPtr<Setting, 0x11C7510> fGrassDimmer;
		static constexpr AddressPtr<Setting, 0x11C74A0> fSIEmmisiveMult;
		static constexpr AddressPtr<Setting, 0x11C7458> fSISpecularMult;
		static constexpr AddressPtr<Setting, 0x11C75BC> fSkyBrightness;
		static constexpr AddressPtr<Setting, 0x11C7758> fSunBrightness;
		static constexpr AddressPtr<Setting, 0x11C7488> fSunlightDimmer;
		static constexpr AddressPtr<Setting, 0x11C71E8> fTargetLUM;
		static constexpr AddressPtr<Setting, 0x11C7574> fTreeDimmer;
		static constexpr AddressPtr<Setting, 0x11C76D8> fUpperLUMClamp;
		static constexpr AddressPtr<Setting, 0x11C71A0> iBlendType;
		static constexpr AddressPtr<Setting, 0x11C7398> iNumBlurpasses;
	};

	struct BlurShaderHDRInterior {
		static constexpr AddressPtr<Setting, 0x11C76E8> fBlurRadius;
		static constexpr AddressPtr<Setting, 0x11C76A4> fBrightClamp;
		static constexpr AddressPtr<Setting, 0x11C74AC> fBrightScale;
		static constexpr AddressPtr<Setting, 0x11C755C> fEmissiveHDRMult;
		static constexpr AddressPtr<Setting, 0x11C720C> fEyeAdaptSpeed;
		static constexpr AddressPtr<Setting, 0x11C73C4> fTargetLUM;
		static constexpr AddressPtr<Setting, 0x11C7148> fUpperLUMClamp;
		static constexpr AddressPtr<Setting, 0x11C7434> iNumBlurpasses;
	};

	struct BudgetCaps {
		static constexpr AddressPtr<Setting, 0x11C5978> bIncludeWaterInMNumberCalculations;
		static constexpr AddressPtr<Setting, 0x11C5B74> fMaxMsUsagePerFrame;
		static constexpr AddressPtr<Setting, 0x11C5B14> fMsActiveRefCount;
		static constexpr AddressPtr<Setting, 0x11C5A2C> fMsActorRefCount;
		static constexpr AddressPtr<Setting, 0x11C5968> fMsAnimatedObjectsCount;
		static constexpr AddressPtr<Setting, 0x11C5C10> fMsDecalCount;
		static constexpr AddressPtr<Setting, 0x11C59AC> fMsEmittersCount;
		static constexpr AddressPtr<Setting, 0x11C5C34> fMsGeometryCount;
		static constexpr AddressPtr<Setting, 0x11C5B68> fMsHavokTriCount;
		static constexpr AddressPtr<Setting, 0x11C59CC> fMsLightCount;
		static constexpr AddressPtr<Setting, 0x11C59F8> fMsLightExcessGeometry;
		static constexpr AddressPtr<Setting, 0x11C5A04> fMsParticlesCount;
		static constexpr AddressPtr<Setting, 0x11C5BB0> fMsRefCount;
		static constexpr AddressPtr<Setting, 0x11C5AA8> fMsTriangleCount;
		static constexpr AddressPtr<Setting, 0x11C5C70> fMsWaterCount;
		static constexpr AddressPtr<Setting, 0x11DEE00> iFPS;
		static constexpr AddressPtr<Setting, 0x11DEECC> iTake;
		static constexpr AddressPtr<Setting, 0x11DEB04> sDirectoryName;
		static constexpr AddressPtr<Setting, 0x11DEE30> sNif;
		static constexpr AddressPtr<Setting, 0x11C5AF0> uActiveRefCount;
		static constexpr AddressPtr<Setting, 0x11C5A84> uActiveRefCountInterior;
		static constexpr AddressPtr<Setting, 0x11C59E0> uActorMemoryBudgetCap;
		static constexpr AddressPtr<Setting, 0x11C5A40> uActorRefCount;
		static constexpr AddressPtr<Setting, 0x11C5BF8> uActorRefCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5C24> uAnimatedObjectsCount;
		static constexpr AddressPtr<Setting, 0x11C5984> uAnimatedObjectsCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5C04> uCityLODBudgetAdjustment;
		static constexpr AddressPtr<Setting, 0x11C5BDC> uDecalCount;
		static constexpr AddressPtr<Setting, 0x11C59B8> uDecalCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5A64> uEmittersCount;
		static constexpr AddressPtr<Setting, 0x11C5B08> uEmittersCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5A58> uGeometryCount;
		static constexpr AddressPtr<Setting, 0x11C5954> uGeometryCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5BBC> uGeometryMemory;
		static constexpr AddressPtr<Setting, 0x11C5C80> uGeometryMemoryInterior;
		static constexpr AddressPtr<Setting, 0x11C59A0> uHavokTriCount;
		static constexpr AddressPtr<Setting, 0x11C5994> uHavokTriCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5B80> uLightCount;
		static constexpr AddressPtr<Setting, 0x11C5BCC> uLightCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5A90> uLightExcessGeometry;
		static constexpr AddressPtr<Setting, 0x11C5BA0> uLightExcessGeometryInterior;
		static constexpr AddressPtr<Setting, 0x11C5B20> uLoadedAreaNonActorMemoryBudgetCap;
		static constexpr AddressPtr<Setting, 0x11C5B3C> uParticlesCount;
		static constexpr AddressPtr<Setting, 0x11C5B8C> uParticlesCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5A1C> uRefCount;
		static constexpr AddressPtr<Setting, 0x11C5AFC> uRefCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5B5C> uTextureMemory;
		static constexpr AddressPtr<Setting, 0x11C5C60> uTextureMemoryInterior;
		static constexpr AddressPtr<Setting, 0x11C59EC> uTriangleCount;
		static constexpr AddressPtr<Setting, 0x11C5A9C> uTriangleCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5AE0> uWastelandLODBudgetAdjustment;
		static constexpr AddressPtr<Setting, 0x11C5A10> uWaterCount;
		static constexpr AddressPtr<Setting, 0x11C5AC4> uWaterCountInterior;
		static constexpr AddressPtr<Setting, 0x11C5C50> uWaterMemory;
		static constexpr AddressPtr<Setting, 0x11C5A4C> uWaterMemoryInterior;
	};

	struct Combat {
		static constexpr AddressPtr<Setting, 0x11C94B0> bAimSights;
		static constexpr AddressPtr<Setting, 0x11F15EC> bDebugCombatArea;
		static constexpr AddressPtr<Setting, 0x11F15A4> bDebugCombatAttackerText;
		static constexpr AddressPtr<Setting, 0x11F1680> bDebugCombatCoverReservations;
		static constexpr AddressPtr<Setting, 0x11F16C0> bDebugCombatCoverReservationsText;
		static constexpr AddressPtr<Setting, 0x11F1674> bDebugCombatCoverSearch;
		static constexpr AddressPtr<Setting, 0x11F168C> bDebugCombatCoverSearch2;
		static constexpr AddressPtr<Setting, 0x11F16E0> bDebugCombatCoverSearchText;
		static constexpr AddressPtr<Setting, 0x11F197C> bDebugCombatDetectionEvents;
		static constexpr AddressPtr<Setting, 0x11F1824> bDebugCombatGroupClusters;
		static constexpr AddressPtr<Setting, 0x11F1878> bDebugCombatGroups;
		static constexpr AddressPtr<Setting, 0x11F1858> bDebugCombatGroups2;
		static constexpr AddressPtr<Setting, 0x11F15B0> bDebugCombatGuardRadius;
		static constexpr AddressPtr<Setting, 0x11F1C4C> bDebugCombatProjectileLOS;
		static constexpr AddressPtr<Setting, 0x11F1814> bDebugCombatSearch;
		static constexpr AddressPtr<Setting, 0x11F1B24> bDebugCombatTargets;
		static constexpr AddressPtr<Setting, 0x11F1C30> bDebugCombatTextColorDark;
		static constexpr AddressPtr<Setting, 0x11F1BA0> bDebugCombatThreats;
		static constexpr AddressPtr<Setting, 0x11F15D0> bDebugCombatUnreachableLocations;
		static constexpr AddressPtr<Setting, 0x11F1764> bDisableCombatDialogue;
		static constexpr AddressPtr<Setting, 0x11F18D8> bDisableCombatGroupStrategies;
		static constexpr AddressPtr<Setting, 0x11DF6C4> bDisableNPCAttacks;
		static constexpr AddressPtr<Setting, 0x11DF858> bDismemberOneLimb;
		static constexpr AddressPtr<Setting, 0x11F1840> bEncounterZoneTargetRestrict;
		static constexpr AddressPtr<Setting, 0x11C94D0> bForceNPCsUseAmmo;
		static constexpr AddressPtr<Setting, 0x11E097C> bIronSightsZoomEnable;
		static constexpr AddressPtr<Setting, 0x11C94A0> bLaserSights;
		static constexpr AddressPtr<Setting, 0x11DF760> bPlayHitLocationIdles;
		static constexpr AddressPtr<Setting, 0x11DF720> bPlayStaggers;
		static constexpr AddressPtr<Setting, 0x11F20EC> bProjectileDebug;
		static constexpr AddressPtr<Setting, 0x11F20B8> bVATSProjectileDebug;
		static constexpr AddressPtr<Setting, 0x11DB114> bVatsAlwaysHit;
		static constexpr AddressPtr<Setting, 0x11E0474> fAimChaseLookingMult;
		static constexpr AddressPtr<Setting, 0x11E0498> fAimDownDegrees;
		static constexpr AddressPtr<Setting, 0x11E048C> fAimUpDegrees;
		static constexpr AddressPtr<Setting, 0x11F1C24> fDebugCombatProjectileLOSTime;
		static constexpr AddressPtr<Setting, 0x11F1C70> fDebugCombatTextSize;
		static constexpr AddressPtr<Setting, 0x11F1A38> fHiPerfNPCTargetLOSTimer;
		static constexpr AddressPtr<Setting, 0x11F1A4C> fHiPerfPCTargetLOSTimer;
		static constexpr AddressPtr<Setting, 0x11DF754> fHitVectorDelay;
		static constexpr AddressPtr<Setting, 0x11E0970> fIronSightsZoomDefault;
		static constexpr AddressPtr<Setting, 0x11F1AD4> fLowPerfNPCTargetLOSTimer;
		static constexpr AddressPtr<Setting, 0x11F1AB0> fLowPerfPCTargetLOSTimer;
		static constexpr AddressPtr<Setting, 0x11DF748> fMinBloodDamage;
		static constexpr AddressPtr<Setting, 0x11F210C> fProjectileDebugDuration;
		static constexpr AddressPtr<Setting, 0x11DF780> iMaxHiPerfCombatCount;
		static constexpr AddressPtr<Setting, 0x11F1A1C> iMaxHiPerfNPCTargetCount;
		static constexpr AddressPtr<Setting, 0x11F1A78> iMaxHiPerfPCTargetCount;
		static constexpr AddressPtr<Setting, 0x11DF838> iShowHitVector;
	};

	struct Controls {
		static constexpr AddressPtr<Setting, 0x11E0B4C> bAlwaysRunByDefault;
		static constexpr AddressPtr<Setting, 0x11F35DC> bBackgroundKeyboard;
		static constexpr AddressPtr<Setting, 0x11F35E8> bBackgroundMouse;
		static constexpr AddressPtr<Setting, 0x11F35D0> bUseJoystick;
		static constexpr AddressPtr<Setting, 0x11E085C> fAnalogMaxRunZonePercent;
		static constexpr AddressPtr<Setting, 0x11E0A78> fAnalogRunZonePercent;
		static constexpr AddressPtr<Setting, 0x11F3618> fForegroundMouseAccelBase;
		static constexpr AddressPtr<Setting, 0x11F360C> fForegroundMouseAccelTop;
		static constexpr AddressPtr<Setting, 0x11F3600> fForegroundMouseBase;
		static constexpr AddressPtr<Setting, 0x11F35F4> fForegroundMouseMult;
		static constexpr AddressPtr<Setting, 0x11E0B94> fForwardBias;
		static constexpr AddressPtr<Setting, 0x11E0840> fJoystickLookLRMult;
		static constexpr AddressPtr<Setting, 0x11E0AF0> fJoystickLookUDMult;
		static constexpr AddressPtr<Setting, 0x11E0B40> fJoystickMoveFBMult;
		static constexpr AddressPtr<Setting, 0x11E0868> fJoystickMoveLRMult;
		static constexpr AddressPtr<Setting, 0x11E091C> fMaxAnalogRunSpeed;
		static constexpr AddressPtr<Setting, 0x11E0B78> fMaxAnalogWalkSpeed;
		static constexpr AddressPtr<Setting, 0x11E09BC> fMinAnalogRunSpeed;
		static constexpr AddressPtr<Setting, 0x11E08AC> fMinAnalogWalkSpeed;
		static constexpr AddressPtr<Setting, 0x11E0964> fPlayerCharacterTurnMult;
		static constexpr AddressPtr<Setting, 0x11E090C> fUFOCamSpeedMult;
		static constexpr AddressPtr<Setting, 0x11D8AA4> fXenonMenuDpadRepeatSpeed;
		static constexpr AddressPtr<Setting, 0x11D8C5C> fXenonMenuMouseXYMult;
		static constexpr AddressPtr<Setting, 0x11D8B14> fXenonMenuStickSpeed;
		static constexpr AddressPtr<Setting, 0x11D8AC8> fXenonMenuStickSpeedMaxMod;
		static constexpr AddressPtr<Setting, 0x11D97A8> fXenonMenuStickSpeedPlayerRotMod;
		static constexpr AddressPtr<Setting, 0x11E0818> fXenonMinLookSpeed;
		static constexpr AddressPtr<Setting, 0x11E0830> iJoystickLookLeftRight;
		static constexpr AddressPtr<Setting, 0x11E0ADC> iJoystickLookUpDown;
		static constexpr AddressPtr<Setting, 0x11E0A20> iJoystickMoveFrontBack;
		static constexpr AddressPtr<Setting, 0x11E09A4> iJoystickMoveLeftRight;
		static constexpr AddressPtr<Setting, 0x11F3624> iLanguage;
		static constexpr AddressPtr<Setting, 0x11E0A90> iXenonHorizLookAccel;
		static constexpr AddressPtr<Setting, 0x11D8B5C> iXenonMenuStickDeadZone;
		static constexpr AddressPtr<Setting, 0x11E08A0> iXenonVertLookAccel;
	};

	struct CopyProtectionStrings {
		static constexpr AddressPtr<Setting, 0x11DEEB4> sCopyProtectionMessage;
		static constexpr AddressPtr<Setting, 0x11DEBB8> sCopyProtectionMessage2;
		static constexpr AddressPtr<Setting, 0x11DEBD0> sCopyProtectionTitle;
		static constexpr AddressPtr<Setting, 0x11DEBFC> sCopyProtectionTitle2;
	};

	struct Debug {
		static constexpr AddressPtr<Setting, 0x11D5A74> bDebugFaceGenCriticalSection;
		static constexpr AddressPtr<Setting, 0x11D5AC4> bDebugFaceGenMultithreading;
		static constexpr AddressPtr<Setting, 0x11DE4E8> bDebugSaveBuffer;
	};

	struct Decals {
		static constexpr AddressPtr<Setting, 0x11C5904> bDebugDecals;
		static constexpr AddressPtr<Setting, 0x11C58D0> bDecalMultithreaded;
		static constexpr AddressPtr<Setting, 0x11C58A8> bDecalOcclusionQuery;
		static constexpr AddressPtr<Setting, 0x11C5834> bDecals;
		static constexpr AddressPtr<Setting, 0x11C5884> bProfileDecals;
		static constexpr AddressPtr<Setting, 0x11C58BC> bSkinnedDecals;
		static constexpr AddressPtr<Setting, 0x11C589C> uMaxSkinDecalPerActor;
		static constexpr AddressPtr<Setting, 0x11C58E4> uMaxSkinDecals;
	};

	struct Display {
		static constexpr AddressPtr<Setting, 0x11C7664> bActorSelfShadowing;
		static constexpr AddressPtr<Setting, 0x11C73A4> bAllow20HairShader;
		static constexpr AddressPtr<Setting, 0x11C7138> bAllow30Shaders;
		static constexpr AddressPtr<Setting, 0x11C7704> bAllowPartialPrecision;
		static constexpr AddressPtr<Setting, 0x11C7418> bAllowScreenShot;
		static constexpr AddressPtr<Setting, 0x1203188> bAutoViewDistance;
		static constexpr AddressPtr<Setting, 0x11C76F8> bDecalsOnSkinnedGeometry;
		static constexpr AddressPtr<Setting, 0x11F94D4> bDo30VFog;
		static constexpr AddressPtr<Setting, 0x11C7368> bDoActorShadows;
		static constexpr AddressPtr<Setting, 0x11C7154> bDoAmbientPass;
		static constexpr AddressPtr<Setting, 0x11C75A4> bDoCanopyShadowPass;
		static constexpr AddressPtr<Setting, 0x11C7544> bDoDiffusePass;
		static constexpr AddressPtr<Setting, 0x11C712C> bDoSpecularPass;
		static constexpr AddressPtr<Setting, 0x11C7380> bDoStaticAndArchShadows;
		static constexpr AddressPtr<Setting, 0x11C71C4> bDoTallGrassEffect;
		static constexpr AddressPtr<Setting, 0x11F94F8> bDoTestHDR;
		static constexpr AddressPtr<Setting, 0x11C7180> bDoTexturePass;
		static constexpr AddressPtr<Setting, 0x11C711C> bDynamicWindowReflections;
		static constexpr AddressPtr<Setting, 0x11C7224> bEquippedTorchesCastShadows;
		static constexpr AddressPtr<Setting, 0x11C74E0> bForce1XShaders;
		static constexpr AddressPtr<Setting, 0x11C7248> bForceMultiPass;
		static constexpr AddressPtr<Setting, 0x11C7538> bForcePow2Textures;
		static constexpr AddressPtr<Setting, 0x11C732C> bIgnoreResolutionCheck;
		static constexpr AddressPtr<Setting, 0x11F94E0> bImageSpaceEffects;
		static constexpr AddressPtr<Setting, 0x11C7774> bLODNoiseAniso;
		static constexpr AddressPtr<Setting, 0x11C710C> bMTRendering;
		static constexpr AddressPtr<Setting, 0x11C7670> bReportBadTangentSpace;
		static constexpr AddressPtr<Setting, 0x11C71DC> bShadowsOnGrass;
		static constexpr AddressPtr<Setting, 0x11DEC98> bShowMenuTextureUse;
		static constexpr AddressPtr<Setting, 0x11C7550> bStaticMenuBackground;
		static constexpr AddressPtr<Setting, 0x11C75B0> bUseFakeFullScreenMotionBlur;
		static constexpr AddressPtr<Setting, 0x11C7504> bUseRefractionShader;
		static constexpr AddressPtr<Setting, 0x11C747C> bUseResolvableDepth;
		static constexpr AddressPtr<Setting, 0x11C726C> bUseShaders;
		static constexpr AddressPtr<Setting, 0x11DEADC> bUseSunbeams;
		static constexpr AddressPtr<Setting, 0x11C77A8> fDecalLOD0;
		static constexpr AddressPtr<Setting, 0x11C5874> fDecalLifetime;
		static constexpr AddressPtr<Setting, 0x1203168> fDefault1stPersonFOV;
		static constexpr AddressPtr<Setting, 0x1203150> fDefaultFOV;
		static constexpr AddressPtr<Setting, 0x120315C> fDefaultWorldFOV;
		static constexpr AddressPtr<Setting, 0x11C7374> fEnvMapLOD1;
		static constexpr AddressPtr<Setting, 0x11C73E8> fEnvMapLOD2;
		static constexpr AddressPtr<Setting, 0x11C7160> fEyeEnvMapLOD1;
		static constexpr AddressPtr<Setting, 0x11C72F0> fEyeEnvMapLOD2;
		static constexpr AddressPtr<Setting, 0x11DAB60> fGammaMax;
		static constexpr AddressPtr<Setting, 0x11DAB98> fGammaMin;
		static constexpr AddressPtr<Setting, 0x11C7464> fLODNoiseMipBias;
		static constexpr AddressPtr<Setting, 0x11C75E0> fLandLOFadeSeconds;
		static constexpr AddressPtr<Setting, 0x11C744C> fLightLODDefaultStartFade;
		static constexpr AddressPtr<Setting, 0x11C74EC> fLightLODMaxStartFade;
		static constexpr AddressPtr<Setting, 0x11C72AC> fLightLODMinStartFade;
		static constexpr AddressPtr<Setting, 0x11C76B4> fLightLODRange;
		static constexpr AddressPtr<Setting, 0x1203144> fNearDistance;
		static constexpr AddressPtr<Setting, 0x120312C> fNoLODFarDistanceMax;
		static constexpr AddressPtr<Setting, 0x1203120> fNoLODFarDistanceMin;
		static constexpr AddressPtr<Setting, 0x1203138> fNoLODFarDistancePct;
		static constexpr AddressPtr<Setting, 0x1203174> fPipboy1stPersonFOV;
		static constexpr AddressPtr<Setting, 0x11DEA8C> fScopeScissorAmount;
		static constexpr AddressPtr<Setting, 0x11C735C> fShadowFadeTime;
		static constexpr AddressPtr<Setting, 0x11C7278> fShadowLODDefaultStartFade;
		static constexpr AddressPtr<Setting, 0x11C71B8> fShadowLODMaxStartFade;
		static constexpr AddressPtr<Setting, 0x11C7294> fShadowLODMinStartFade;
		static constexpr AddressPtr<Setting, 0x11C7400> fShadowLODRange;
		static constexpr AddressPtr<Setting, 0x11C7588> fSkinnedDecalLOD0;
		static constexpr AddressPtr<Setting, 0x11C72FC> fSkinnedDecalLOD1;
		static constexpr AddressPtr<Setting, 0x11C7344> fSkinnedDecalLOD2;
		static constexpr AddressPtr<Setting, 0x11C7494> fSpecularLODDefaultStartFade;
		static constexpr AddressPtr<Setting, 0x11C71D0> fSpecularLODMaxStartFade;
		static constexpr AddressPtr<Setting, 0x11C7440> fSpecularLODMinStartFade;
		static constexpr AddressPtr<Setting, 0x11C7634> fSpecularLODRange;
		static constexpr AddressPtr<Setting, 0x12031A0> iAutoViewHiFrameRate;
		static constexpr AddressPtr<Setting, 0x1203194> iAutoViewLowFrameRate;
		static constexpr AddressPtr<Setting, 0x12031AC> iAutoViewMinDistance;
		static constexpr AddressPtr<Setting, 0x11DEEC0> iDebugTextLeftRightOffset;
		static constexpr AddressPtr<Setting, 0x11DEBAC> iDebugTextTopBottomOffset;
		static constexpr AddressPtr<Setting, 0x11C75D4> iLocationX;
		static constexpr AddressPtr<Setting, 0x11C7654> iLocationY;
		static constexpr AddressPtr<Setting, 0x11C75EC> iNPatchNOrder;
		static constexpr AddressPtr<Setting, 0x11C7470> iNPatchPOrder;
		static constexpr AddressPtr<Setting, 0x11C7100> iNPatches;
		static constexpr AddressPtr<Setting, 0x11C7628> iPresentInterval;
		static constexpr AddressPtr<Setting, 0x11DED08> sDebugText;
		static constexpr AddressPtr<Setting, 0x11DF0F8> sScreenShotBaseName;
		static constexpr AddressPtr<Setting, 0x11C7604> uVideoDeviceIdentifierPart1;
		static constexpr AddressPtr<Setting, 0x11C7640> uVideoDeviceIdentifierPart2;
		static constexpr AddressPtr<Setting, 0x11C7320> uVideoDeviceIdentifierPart3;
		static constexpr AddressPtr<Setting, 0x11C75C8> uVideoDeviceIdentifierPart4;
	};

	struct DistantLOD {
		static constexpr AddressPtr<Setting, 0x11F9650> iDistantLODGroupWidth;
	};

	struct Fonts {
		static constexpr AddressPtr<Setting, 0x11F3414> sFontFile_1;
		static constexpr AddressPtr<Setting, 0x11F3420> sFontFile_2;
		static constexpr AddressPtr<Setting, 0x11F342C> sFontFile_3;
		static constexpr AddressPtr<Setting, 0x11F3438> sFontFile_4;
		static constexpr AddressPtr<Setting, 0x11F3444> sFontFile_5;
		static constexpr AddressPtr<Setting, 0x11F3450> sFontFile_6;
		static constexpr AddressPtr<Setting, 0x11F345C> sFontFile_7;
		static constexpr AddressPtr<Setting, 0x11F3468> sFontFile_8;
	};

	struct FootIK {
		static constexpr AddressPtr<Setting, 0x1267D80> bFootPlacementOn;
		static constexpr AddressPtr<Setting, 0x1267E1C> bRigidBodyController;
		static constexpr AddressPtr<Setting, 0x1267D98> fAnkleOffset;
		static constexpr AddressPtr<Setting, 0x1267DD4> fControllerTetherLen;
		static constexpr AddressPtr<Setting, 0x1267D74> fFootPlantedGain;
		static constexpr AddressPtr<Setting, 0x1267D68> fFootRaisedGain;
		static constexpr AddressPtr<Setting, 0x1267D50> fGroundAscendingGain;
		static constexpr AddressPtr<Setting, 0x1267D5C> fGroundDescendingGain;
		static constexpr AddressPtr<Setting, 0x1267DEC> fMaxFootCastMilliSec;
		static constexpr AddressPtr<Setting, 0x1267DE0> fMaxStepVertError;
		static constexpr AddressPtr<Setting, 0x1267D44> fOnOffGain;
		static constexpr AddressPtr<Setting, 0x1267D8C> fOriginalGroundHeightMS;
		static constexpr AddressPtr<Setting, 0x1267DB0> fPelvisOffsetDamping;
		static constexpr AddressPtr<Setting, 0x1267DA4> fPelvisUpDownBias;
		static constexpr AddressPtr<Setting, 0x1267E10> fRagdollFeedback;
		static constexpr AddressPtr<Setting, 0x1267DBC> fVertErrorGain;
		static constexpr AddressPtr<Setting, 0x1267DC8> iNumFramesFootEaseOut;
	};

	struct GamePlay {
		static constexpr AddressPtr<Setting, 0x11E0B1C> bAllowHavokGrabTheLiving;
		static constexpr AddressPtr<Setting, 0x11E0888> bEssentialTakeNoDamage;
		static constexpr AddressPtr<Setting, 0x11E0988> bHealthBarShowing;
		static constexpr AddressPtr<Setting, 0x11E09B0> bInstantLevelUp;
		static constexpr AddressPtr<Setting, 0x11E0894> bSetDemigodMode;
		static constexpr AddressPtr<Setting, 0x11CB4D4> bShowChallengeUpdates;
		static constexpr AddressPtr<Setting, 0x11E0A30> bTrackProgress;
		static constexpr AddressPtr<Setting, 0x11E01F4> fHealthBarEmittanceFadeTime;
		static constexpr AddressPtr<Setting, 0x11E02C4> fHealthBarEmittanceTime;
		static constexpr AddressPtr<Setting, 0x11E0288> fHealthBarFadeOutSpeed;
		static constexpr AddressPtr<Setting, 0x11E0200> fHealthBarHeight;
		static constexpr AddressPtr<Setting, 0x11E024C> fHealthBarSpeed;
		static constexpr AddressPtr<Setting, 0x11E0218> fHealthBarWidth;
		static constexpr AddressPtr<Setting, 0x11E0A10> iActorsDismemberedPerFrame;
		static constexpr AddressPtr<Setting, 0x11DF804> iDetectionPicks;
		static constexpr AddressPtr<Setting, 0x11E09D4> sTrackProgressPath;
	};

	struct General {
		static constexpr AddressPtr<Setting, 0x11CB81C> bActivateAllQuestScripts;
		static constexpr AddressPtr<Setting, 0x11DF93C> bActorLookWithHavok;
		static constexpr AddressPtr<Setting, 0x11DEED8> bAlwaysActive;
		static constexpr AddressPtr<Setting, 0x11C4C64> bAnimateDoorPhysics;
		static constexpr AddressPtr<Setting, 0x11E08E0> bBorderRegionsEnabled;
		static constexpr AddressPtr<Setting, 0x11DEB54> bCRTMemoryChecks;
		static constexpr AddressPtr<Setting, 0x11DEDBC> bChangeTimeMultSlowly;
		static constexpr AddressPtr<Setting, 0x11CA63C> bCheckCellOffsetsOnInit;
		static constexpr AddressPtr<Setting, 0x11C3CCC> bCheckPurgedTextureList;
		static constexpr AddressPtr<Setting, 0x11C3FF4> bCreateMapsEnable;
		static constexpr AddressPtr<Setting, 0x11C7610> bCreateShaderPackage;
		static constexpr AddressPtr<Setting, 0x11F31C8> bDebugSpectatorThreats;
		static constexpr AddressPtr<Setting, 0x11CA0A8> bDefaultCOCPlacement;
		static constexpr AddressPtr<Setting, 0x11DF7F8> bDisableAllGore;
		static constexpr AddressPtr<Setting, 0x11E09E0> bDisableAutoVanityMode;
		static constexpr AddressPtr<Setting, 0x11C3F58> bDisableDuplicateReferenceCheck;
		static constexpr AddressPtr<Setting, 0x11DEB60> bDisplayBoundingVolumes;
		static constexpr AddressPtr<Setting, 0x11DBAA4> bDrawSpellContact;
		static constexpr AddressPtr<Setting, 0x11DECD8> bEnableBoundingVolumeOcclusion;
		static constexpr AddressPtr<Setting, 0x11CA62C> bExternalLODDataFiles;
		static constexpr AddressPtr<Setting, 0x11CB99C> bFaceGenTexturing;
		static constexpr AddressPtr<Setting, 0x11D59AC> bFaceMipMaps;
		static constexpr AddressPtr<Setting, 0x11DABB0> bFadeInScreenShot;
		static constexpr AddressPtr<Setting, 0x11C5348> bFixAIPackagesOnLoad;
		static constexpr AddressPtr<Setting, 0x11D5A30> bFixFaceNormals;
		static constexpr AddressPtr<Setting, 0x11C4098> bKeepPluginWhenMerging;
		static constexpr AddressPtr<Setting, 0x11D5ADC> bLoadFaceGenHeadEGTFiles;
		static constexpr AddressPtr<Setting, 0x11DED80> bPreCullActors;
		static constexpr AddressPtr<Setting, 0x11C3D40> bPreemptivelyUnloadCells;
		static constexpr AddressPtr<Setting, 0x126FAC8> bPreloadIntroSequence;
		static constexpr AddressPtr<Setting, 0x11C3E64> bQueueWarnings;
		static constexpr AddressPtr<Setting, 0x11DA3B8> bRenderLocalMapContinually;
		static constexpr AddressPtr<Setting, 0x11DFB88> bRunActorMovementDuringRendering;
		static constexpr AddressPtr<Setting, 0x11DFC70> bRunDetectionDuringRendering;
		static constexpr AddressPtr<Setting, 0x11E0E4C> bRunMiddleLowLevelProcess;
		static constexpr AddressPtr<Setting, 0x11DEACC> bRunVTuneTest;
		static constexpr AddressPtr<Setting, 0x11DEFDC> bShowCheckMemoryOutput;
		static constexpr AddressPtr<Setting, 0x11E0A50> bShowGunTarget;
		static constexpr AddressPtr<Setting, 0x11C3DBC> bShowLoadingAreaMessage;
		static constexpr AddressPtr<Setting, 0x11F126C> bTaskletActorAnimMovementUpdates;
		static constexpr AddressPtr<Setting, 0x11DF214> bTaskletActorHavokSync;
		static constexpr AddressPtr<Setting, 0x11F1260> bTaskletActorSceneGraphUpdates;
		static constexpr AddressPtr<Setting, 0x11DF1B8> bTaskletCellTransformsUpdate;
		static constexpr AddressPtr<Setting, 0x11F127C> bTaskletTempEffectsUpdate;
		static constexpr AddressPtr<Setting, 0x11C7218> bTintMipMaps;
		static constexpr AddressPtr<Setting, 0x11DF690> bTrackAllDeaths;
		static constexpr AddressPtr<Setting, 0x11D5AB4> bUseEyeEnvMapping;
		static constexpr AddressPtr<Setting, 0x11D5A44> bUseFaceGenHeads;
		static constexpr AddressPtr<Setting, 0x11DED68> bUseHardDriveCache;
		static constexpr AddressPtr<Setting, 0x11DF6B0> bUseMovementBlockedPackage;
		static constexpr AddressPtr<Setting, 0x11CA118> bUseMultibounds;
		static constexpr AddressPtr<Setting, 0x11DEAB0> bUseMyGamesDirectory;
		static constexpr AddressPtr<Setting, 0x11C5574> bUseOptimizedTextureLoading;
		static constexpr AddressPtr<Setting, 0x11DFB68> bUseThreadedAI;
		static constexpr AddressPtr<Setting, 0x11DED20> bUseThreadedMorpher;
		static constexpr AddressPtr<Setting, 0x11DEAEC> bUseThreadedParticleSystem;
		static constexpr AddressPtr<Setting, 0x11DECBC> bUseThreadedTempEffects;
		static constexpr AddressPtr<Setting, 0x11C555C> bWarnOnMissingFileEntry;
		static constexpr AddressPtr<Setting, 0x11C56FC> fAnimationDefaultBlend;
		static constexpr AddressPtr<Setting, 0x11C5724> fAnimationMult;
		static constexpr AddressPtr<Setting, 0x11DEBA0> fDegradeTexturesDistance;
		static constexpr AddressPtr<Setting, 0x11F2BD0> fLODActorAvoidanceDistance;
		static constexpr AddressPtr<Setting, 0x11DEC58> fUpgradeTexturesDistance;
		static constexpr AddressPtr<Setting, 0x11E0A84> fZoom3rdPersonSnapDist;
		static constexpr AddressPtr<Setting, 0x11DFB34> iAIThread1HWThread;
		static constexpr AddressPtr<Setting, 0x11DFB18> iAIThread2HWThread;
		static constexpr AddressPtr<Setting, 0x11DEE60> iFPSClamp;
		static constexpr AddressPtr<Setting, 0x12677DC> iHWThread1;
		static constexpr AddressPtr<Setting, 0x12677E8> iHWThread2;
		static constexpr AddressPtr<Setting, 0x12677F4> iHWThread3;
		static constexpr AddressPtr<Setting, 0x1267800> iHWThread4;
		static constexpr AddressPtr<Setting, 0x126780C> iHWThread5;
		static constexpr AddressPtr<Setting, 0x1267818> iHWThread6;
		static constexpr AddressPtr<Setting, 0x11E0A9C> iHoursToSleep;
		static constexpr AddressPtr<Setting, 0x126FAE0> iIntroSequencePriority;
		static constexpr AddressPtr<Setting, 0x11DF198> iNumBitsForFullySeen;
		static constexpr AddressPtr<Setting, 0x11C3EA4> iNumHWThreads;
		static constexpr AddressPtr<Setting, 0x126FAD4> iPreloadSizeLimit;
		static constexpr AddressPtr<Setting, 0x1200070> iRenderingThread1HWThread;
		static constexpr AddressPtr<Setting, 0x120007C> iRenderingThread2HWThread;
		static constexpr AddressPtr<Setting, 0x11DAC00> sCharGenQuest;
		static constexpr AddressPtr<Setting, 0x11DEE78> sEssentialFileCacheList;
		static constexpr AddressPtr<Setting, 0x11DE71C> sIntroMovie;
		static constexpr AddressPtr<Setting, 0x11DE72C> sIntroSequence;
		static constexpr AddressPtr<Setting, 0x11C3CB4> sLanguage;
		static constexpr AddressPtr<Setting, 0x11C4030> sLocalMasterPath;
		static constexpr AddressPtr<Setting, 0x11C3F74> sLocalSavePath;
		static constexpr AddressPtr<Setting, 0x11DE740> sMainMenuMovieIntro;
		static constexpr AddressPtr<Setting, 0x11DED5C> sStartingCell;
		static constexpr AddressPtr<Setting, 0x11DEE8C> sStartingCellX;
		static constexpr AddressPtr<Setting, 0x11DEBC4> sStartingCellY;
		static constexpr AddressPtr<Setting, 0x11DEB48> sStartingWorld;
		static constexpr AddressPtr<Setting, 0x11DEBF0> sTestFile1;
		static constexpr AddressPtr<Setting, 0x11DED48> sTestFile10;
		static constexpr AddressPtr<Setting, 0x11DEB88> sTestFile2;
		static constexpr AddressPtr<Setting, 0x11DECF8> sTestFile3;
		static constexpr AddressPtr<Setting, 0x11DEE9C> sTestFile4;
		static constexpr AddressPtr<Setting, 0x11DEC34> sTestFile5;
		static constexpr AddressPtr<Setting, 0x11DEE0C> sTestFile6;
		static constexpr AddressPtr<Setting, 0x11DED14> sTestFile7;
		static constexpr AddressPtr<Setting, 0x11DEE48> sTestFile8;
		static constexpr AddressPtr<Setting, 0x11DEA70> sTestFile9;
		static constexpr AddressPtr<Setting, 0x11DED2C> sUnessentialFileCacheList;
		static constexpr AddressPtr<Setting, 0x11C3C90> uExteriorCellBuffer;
		static constexpr AddressPtr<Setting, 0x11C63CC> uGridsToLoad;
		static constexpr AddressPtr<Setting, 0x11C3E38> uInteriorCellBuffer;
		static constexpr AddressPtr<Setting, 0x11D5A50> uiEGTClampSize;
		static constexpr AddressPtr<Setting, 0x11D59F4> uiFaceGenMaxEGMDataSize;
		static constexpr AddressPtr<Setting, 0x11D5AFC> uiFaceGenMaxEGTDataSize;
	};

	struct GeneralWarnings {
		static constexpr AddressPtr<Setting, 0x11C4048> sGeneralMasterMismatchWarning;
		static constexpr AddressPtr<Setting, 0x11C4024> sMasterMismatchWarning;
	};

	struct GethitShader {
		static constexpr AddressPtr<Setting, 0x11C7350> fBlockedTexOffset;
		static constexpr AddressPtr<Setting, 0x11C7338> fBlurAmmount;
		static constexpr AddressPtr<Setting, 0x11C7710> fHitTexOffset;
	};

	struct GrabIK {
		static constexpr AddressPtr<Setting, 0x1267DF8> fDriveGain;
	};

	struct Grass {
		static constexpr AddressPtr<Setting, 0x11CA4F0> bDrawShaderGrass;
		static constexpr AddressPtr<Setting, 0x11CA480> bGrassPointLighting;
		static constexpr AddressPtr<Setting, 0x11CA4CC> fGrassDefaultStartFadeDistance;
		static constexpr AddressPtr<Setting, 0x11CA498> fGrassFadeRange;
		static constexpr AddressPtr<Setting, 0x11CA4D8> fGrassMaxStartFadeDistance;
		static constexpr AddressPtr<Setting, 0x11CA4AC> fGrassMinStartFadeDistance;
		static constexpr AddressPtr<Setting, 0x11CA510> fGrassWindMagnitudeMax;
		static constexpr AddressPtr<Setting, 0x11CA48C> fGrassWindMagnitudeMin;
		static constexpr AddressPtr<Setting, 0x11C9F38> fTexturePctThreshold;
		static constexpr AddressPtr<Setting, 0x11C8DCC> fWaveOffsetRange;
		static constexpr AddressPtr<Setting, 0x11C9FB8> iGrassDensityEvalSize;
		static constexpr AddressPtr<Setting, 0x11C9F74> iMaxGrassTypesPerTexure;
		static constexpr AddressPtr<Setting, 0x11CA524> iMinGrassSize;
	};

	struct HAVOK {
		static constexpr AddressPtr<Setting, 0x11C3DA0> bAddBipedWhenKeyframed;
		static constexpr AddressPtr<Setting, 0x11CC5A8> bAutoWaterUsesHavokShapes;
		static constexpr AddressPtr<Setting, 0x11E0B64> bDisablePlayerCollision;
		static constexpr AddressPtr<Setting, 0x1267B40> bFindContactPointsOnAdd;
		static constexpr AddressPtr<Setting, 0x1267B28> bHavokDebug;
		static constexpr AddressPtr<Setting, 0x11CA394> bPreventHavokAddAll;
		static constexpr AddressPtr<Setting, 0x11CA3EC> bPreventHavokAddClutter;
		static constexpr AddressPtr<Setting, 0x11D5E84> bTreeTops;
		static constexpr AddressPtr<Setting, 0x11CC188> fCameraCasterFadeSittingRadius;
		static constexpr AddressPtr<Setting, 0x11E09C8> fCameraCasterPlayerSize;
		static constexpr AddressPtr<Setting, 0x11E0934> fCameraCasterSize;
		static constexpr AddressPtr<Setting, 0x1267BD4> fCharControllerWarpDistSqr;
		static constexpr AddressPtr<Setting, 0x11C3D28> fChaseDeltaMult;
		static constexpr AddressPtr<Setting, 0x11DF72C> fJumpAnimDelay;
		static constexpr AddressPtr<Setting, 0x11C3E54> fMaxPickTime;
		static constexpr AddressPtr<Setting, 0x11C3DD8> fMaxPickTimeDebug;
		static constexpr AddressPtr<Setting, 0x11C3DCC> fMaxPickTimeDebugVATS;
		static constexpr AddressPtr<Setting, 0x11C3E94> fMaxPickTimeVATS;
		static constexpr AddressPtr<Setting, 0x1267B34> fMaxTime;
		static constexpr AddressPtr<Setting, 0x11C3D4C> fMoveLimitMass;
		static constexpr AddressPtr<Setting, 0x11C62A8> fOD;
		static constexpr AddressPtr<Setting, 0x11E0574> fQuadrupedPitchMult;
		static constexpr AddressPtr<Setting, 0x11C62FC> fRF;
		static constexpr AddressPtr<Setting, 0x11C629C> fSD;
		static constexpr AddressPtr<Setting, 0x11C62C0> fSE;
		static constexpr AddressPtr<Setting, 0x1267B10> fTimePerSubStep;
		static constexpr AddressPtr<Setting, 0x11C3C3C> iEntityBatchRemoveRate;
		static constexpr AddressPtr<Setting, 0x1267B1C> iMinNumSubSteps;
		static constexpr AddressPtr<Setting, 0x11CC2E8> iSimType;
		static constexpr AddressPtr<Setting, 0x11C3C30> iUpdateType;
	};

	struct Hacking {
		static constexpr AddressPtr<Setting, 0x11D9684> fHackingMinSkillAverage;
		static constexpr AddressPtr<Setting, 0x11D9660> fHackingMinSkillEasy;
		static constexpr AddressPtr<Setting, 0x11D95D4> fHackingMinSkillHard;
		static constexpr AddressPtr<Setting, 0x11D961C> fHackingMinSkillVeryEasy;
		static constexpr AddressPtr<Setting, 0x11D9640> fHackingMinSkillVeryHard;
	};

	struct Havok {
		static constexpr AddressPtr<Setting, 0x1267BA0> bWONameSync;
		static constexpr AddressPtr<Setting, 0x11E05B4> iHavokSkipFrameCountTEST;
	};

	struct HeadTracking {
		static constexpr AddressPtr<Setting, 0x11DF6D0> bDisableHeadTracking;
		static constexpr AddressPtr<Setting, 0x11DF78C> fUpdateDelayNewTargetSecondsMax;
		static constexpr AddressPtr<Setting, 0x11DF700> fUpdateDelayNewTargetSecondsMin;
		static constexpr AddressPtr<Setting, 0x11DF828> fUpdateDelaySecondsMax;
		static constexpr AddressPtr<Setting, 0x11DF810> fUpdateDelaySecondsMin;
		static constexpr AddressPtr<Setting, 0x11DF848> iUpdateActorsPerFrame;
	};

	struct Imagespace {
		static constexpr AddressPtr<Setting, 0x120249C> bDoMotionBlur;
		static constexpr AddressPtr<Setting, 0x11F9688> bDoRadialBlur;
		static constexpr AddressPtr<Setting, 0x12023DC> fRenderDepthMaxDepth;
	};

	struct Interface {
		static constexpr AddressPtr<Setting, 0x11D8AFC> bActivatePickUseGamebryoPick;
		static constexpr AddressPtr<Setting, 0x11D8B94> bAllowConsole;
		static constexpr AddressPtr<Setting, 0x11DA034> bHideUnavailablePerks;
		static constexpr AddressPtr<Setting, 0x11CC628> bUseFuzzyPicking;
		static constexpr AddressPtr<Setting, 0x11D8B78> fActivatePickSphereRadius;
		static constexpr AddressPtr<Setting, 0x11E0B84> fDlgFocus;
		static constexpr AddressPtr<Setting, 0x11E0B28> fDlgHeadingDegStart;
		static constexpr AddressPtr<Setting, 0x11E08C4> fDlgHeadingDegStop;
		static constexpr AddressPtr<Setting, 0x11E08D0> fDlgLookAdj;
		static constexpr AddressPtr<Setting, 0x11E094C> fDlgLookDegStart;
		static constexpr AddressPtr<Setting, 0x11E0900> fDlgLookDegStop;
		static constexpr AddressPtr<Setting, 0x11E0958> fDlgLookMult;
		static constexpr AddressPtr<Setting, 0x11D9748> fHUDShakeMult;
		static constexpr AddressPtr<Setting, 0x11C73D0> fInterfaceTintB;
		static constexpr AddressPtr<Setting, 0x11C77CC> fInterfaceTintG;
		static constexpr AddressPtr<Setting, 0x11C75F8> fInterfaceTintR;
		static constexpr AddressPtr<Setting, 0x11D8B88> fKeyRepeatInterval;
		static constexpr AddressPtr<Setting, 0x11D8B38> fKeyRepeatTime;
		static constexpr AddressPtr<Setting, 0x11DEDE8> fMenuBGBlurRadius;
		static constexpr AddressPtr<Setting, 0x11D3174> fMenuBackgroundOpacity;
		static constexpr AddressPtr<Setting, 0x11C5740> fMenuModeAnimBlend;
		static constexpr AddressPtr<Setting, 0x11D8B08> fMenuPlayerLightAmbientBlue;
		static constexpr AddressPtr<Setting, 0x11D8B6C> fMenuPlayerLightAmbientGreen;
		static constexpr AddressPtr<Setting, 0x11D8BE4> fMenuPlayerLightAmbientRed;
		static constexpr AddressPtr<Setting, 0x11D8ABC> fMenuPlayerLightDiffuseBlue;
		static constexpr AddressPtr<Setting, 0x11D8BB0> fMenuPlayerLightDiffuseGreen;
		static constexpr AddressPtr<Setting, 0x11D8C40> fMenuPlayerLightDiffuseRed;
		static constexpr AddressPtr<Setting, 0x11D3BC8> fPopUpBackgroundOpacity;
		static constexpr AddressPtr<Setting, 0x11DA6DC> fRSMFaceSliderDefaultMax;
		static constexpr AddressPtr<Setting, 0x11DA6A4> fRSMFaceSliderDefaultMin;
		static constexpr AddressPtr<Setting, 0x11DA6CC> fRSMStartingZoom;
		static constexpr AddressPtr<Setting, 0x11CC668> iMaxViewCasterPicksFuzzy;
		static constexpr AddressPtr<Setting, 0x11CC644> iMaxViewCasterPicksGamebryo;
		static constexpr AddressPtr<Setting, 0x11CC61C> iMaxViewCasterPicksHavok;
		static constexpr AddressPtr<Setting, 0x11D8BD8> iSafeZoneX;
		static constexpr AddressPtr<Setting, 0x11D8BFC> iSafeZoneXWide;
		static constexpr AddressPtr<Setting, 0x11D8BF0> iSafeZoneY;
		static constexpr AddressPtr<Setting, 0x11D8BC0> iSafeZoneYWide;
	};

	struct InterfaceFX {
		static constexpr AddressPtr<Setting, 0x11D8AB0> bEnableMenuRenderDebugMode;
		static constexpr AddressPtr<Setting, 0x11D8BA0> bUseImageSpaceMenuFX;
		static constexpr AddressPtr<Setting, 0x11DB1E0> bUseOptimizedMenuRendering;
		static constexpr AddressPtr<Setting, 0x11DB238> fBlurIntensityHUD;
		static constexpr AddressPtr<Setting, 0x11DB218> fBlurIntensityMenus;
		static constexpr AddressPtr<Setting, 0x11DB200> fBlurRadiusHUD;
		static constexpr AddressPtr<Setting, 0x11DB1F0> fBlurRadiusMenus;
		static constexpr AddressPtr<Setting, 0x11DB470> fDefaultBlurIntensity;
		static constexpr AddressPtr<Setting, 0x11DB44C> fDefaultBlurRadius;
		static constexpr AddressPtr<Setting, 0x11DB480> fDefaultBurstDuration;
		static constexpr AddressPtr<Setting, 0x11DB43C> fDefaultBurstIntensity;
		static constexpr AddressPtr<Setting, 0x11DB490> fDefaultScanlineFrequency;
		static constexpr AddressPtr<Setting, 0x11DB414> fDefaultShudderDuration;
		static constexpr AddressPtr<Setting, 0x11DB3B0> fDefaultShudderFrequency;
		static constexpr AddressPtr<Setting, 0x11DB3BC> fDefaultShudderIntensity;
		static constexpr AddressPtr<Setting, 0x11DB4EC> fDefaultVertHoldDuration;
		static constexpr AddressPtr<Setting, 0x11DB3FC> fDefaultVertHoldSpeed;
		static constexpr AddressPtr<Setting, 0x11DB4D0> fDistortDuration;
		static constexpr AddressPtr<Setting, 0x11DB464> fDistortHorizontalScale;
		static constexpr AddressPtr<Setting, 0x11DB520> fDistortVerticalScale;
		static constexpr AddressPtr<Setting, 0x11DB244> fHUDShudderDefaultDuration;
		static constexpr AddressPtr<Setting, 0x11DB224> fHUDShudderDefaultFrequencyX;
		static constexpr AddressPtr<Setting, 0x11DB1D4> fHUDShudderDefaultFrequencyY;
		static constexpr AddressPtr<Setting, 0x11DB250> fHUDShudderDefaultIntensity;
		static constexpr AddressPtr<Setting, 0x11D87DC> fMenuPackerBufferOverflowZone;
		static constexpr AddressPtr<Setting, 0x11D87F0> fMenuPackerBufferSize;
		static constexpr AddressPtr<Setting, 0x11DB458> fMiniBurstDuration;
		static constexpr AddressPtr<Setting, 0x11DB37C> fMiniBurstIntensity;
		static constexpr AddressPtr<Setting, 0x11DB3A4> fPulseBrightenIntensity;
		static constexpr AddressPtr<Setting, 0x11DB424> fPulseRadiusIntensity;
		static constexpr AddressPtr<Setting, 0x11DB408> fPulseRate;
		static constexpr AddressPtr<Setting, 0x11DB25C> fScanlineFrequencyHUD;
		static constexpr AddressPtr<Setting, 0x11DB20C> fScanlineFrequencyMenus;
		static constexpr AddressPtr<Setting, 0x11DB394> fScreenLightBaseIntensity;
		static constexpr AddressPtr<Setting, 0x11DB430> fScreenLightBurstModifier;
		static constexpr AddressPtr<Setting, 0x11DB4A4> fScreenLightPulseModifier;
		static constexpr AddressPtr<Setting, 0x11DB514> fScreenLightRadius;
		static constexpr AddressPtr<Setting, 0x11DB3E8> fScreenLightVertHoldRate;
		static constexpr AddressPtr<Setting, 0x11DB4E0> fShudderChance;
		static constexpr AddressPtr<Setting, 0x11DB4B4> fVertHoldChance;
		static constexpr AddressPtr<Setting, 0x11DB4F8> iDistortMaxInterval;
		static constexpr AddressPtr<Setting, 0x11DB3D8> sScanlineTexture;
	};

	struct LANGUAGE {
		static constexpr AddressPtr<Setting, 0x11C3DE4> sDPad;
		static constexpr AddressPtr<Setting, 0x11C3C84> sFailureMessage;
		static constexpr AddressPtr<Setting, 0x11C3EB4> sSysUtil_AutoSaveWarning;
		static constexpr AddressPtr<Setting, 0x11C3E70> sSysUtil_DirtyDisc;
		static constexpr AddressPtr<Setting, 0x11C3D34> sSysUtil_DiscEject;
		static constexpr AddressPtr<Setting, 0x11C3CD8> sSysUtil_GameDataCorrupt;
		static constexpr AddressPtr<Setting, 0x11C3C9C> sSysUtil_GameDataInsufficientSpace;
		static constexpr AddressPtr<Setting, 0x11C3E48> sSysUtil_Retry;
		static constexpr AddressPtr<Setting, 0x11C3E28> sSysUtil_SaveDataCreateNew;
		static constexpr AddressPtr<Setting, 0x11C3CA8> sSysUtil_SaveDataInsufficientSpace;
		static constexpr AddressPtr<Setting, 0x11C3E88> sThumbstick;
	};

	struct LOD {
		static constexpr AddressPtr<Setting, 0x11DEEA8> bDisplayLODLand;
		static constexpr AddressPtr<Setting, 0x11D5A5C> bUseFaceGenLOD;
		static constexpr AddressPtr<Setting, 0x11DAC38> fActorLODDefault;
		static constexpr AddressPtr<Setting, 0x11DAAF4> fActorLODMax;
		static constexpr AddressPtr<Setting, 0x11DAB1C> fActorLODMin;
		static constexpr AddressPtr<Setting, 0x11C3D60> fDistanceMultiplier;
		static constexpr AddressPtr<Setting, 0x11C3D00> fFadeInThreshold;
		static constexpr AddressPtr<Setting, 0x11C3DF4> fFadeInTime;
		static constexpr AddressPtr<Setting, 0x11C3E18> fFadeOutThreshold;
		static constexpr AddressPtr<Setting, 0x11C3C5C> fFadeOutTime;
		static constexpr AddressPtr<Setting, 0x11DABC0> fItemLODDefault;
		static constexpr AddressPtr<Setting, 0x11DAC24> fItemLODMax;
		static constexpr AddressPtr<Setting, 0x11DABF0> fItemLODMin;
		static constexpr AddressPtr<Setting, 0x11C3BE4> fLODBoundRadiusMult;
		static constexpr AddressPtr<Setting, 0x11DED98> fLODFadeOutActorMultCity;
		static constexpr AddressPtr<Setting, 0x11DED8C> fLODFadeOutActorMultComplex;
		static constexpr AddressPtr<Setting, 0x11DECC8> fLODFadeOutActorMultInterior;
		static constexpr AddressPtr<Setting, 0x11DEE54> fLODFadeOutItemMultCity;
		static constexpr AddressPtr<Setting, 0x11DEB10> fLODFadeOutItemMultComplex;
		static constexpr AddressPtr<Setting, 0x11DEDDC> fLODFadeOutItemMultInterior;
		static constexpr AddressPtr<Setting, 0x11DEC7C> fLODFadeOutObjectMultCity;
		static constexpr AddressPtr<Setting, 0x11DEC24> fLODFadeOutObjectMultComplex;
		static constexpr AddressPtr<Setting, 0x11DEA80> fLODFadeOutObjectMultInterior;
		static constexpr AddressPtr<Setting, 0x11C3BB8> fLODFadeOutPercent;
		static constexpr AddressPtr<Setting, 0x11DEDC8> fLODLandDropAmount;
		static constexpr AddressPtr<Setting, 0x11DEEE8> fLODLandVerticalBias;
		static constexpr AddressPtr<Setting, 0x11F9158> fLODMultTrees;
		static constexpr AddressPtr<Setting, 0x11D5B28> fLodDistance;
		static constexpr AddressPtr<Setting, 0x11DAB6C> fObjectLODDefault;
		static constexpr AddressPtr<Setting, 0x11DAB78> fObjectLODMax;
		static constexpr AddressPtr<Setting, 0x11DAB30> fObjectLODMin;
		static constexpr AddressPtr<Setting, 0x11D5B34> fTalkingDistance;
		static constexpr AddressPtr<Setting, 0x11F9148> iFadeNodeMinNearDistance;
	};

	struct Landscape {
		static constexpr AddressPtr<Setting, 0x11C9F60> bCurrentCellOnly;
		static constexpr AddressPtr<Setting, 0x11C9F80> bPreventSafetyCheck;
		static constexpr AddressPtr<Setting, 0x11CC1D8> fLandFriction;
		static constexpr AddressPtr<Setting, 0x11C9F2C> fLandTextureTilingMult;
		static constexpr AddressPtr<Setting, 0x11C9FC8> iLandBorder1B;
		static constexpr AddressPtr<Setting, 0x11C9F9C> iLandBorder1G;
		static constexpr AddressPtr<Setting, 0x11C9F20> iLandBorder1R;
		static constexpr AddressPtr<Setting, 0x11C9FAC> iLandBorder2B;
		static constexpr AddressPtr<Setting, 0x11CA024> iLandBorder2G;
		static constexpr AddressPtr<Setting, 0x11C9FF4> iLandBorder2R;
		static constexpr AddressPtr<Setting, 0x11CA004> sDefaultLandDiffuseTexture;
		static constexpr AddressPtr<Setting, 0x11C9F8C> sDefaultLandNormalTexture;
	};

	struct Loading {
		static constexpr AddressPtr<Setting, 0x11DA1A0> fLoadingBkgdUpdateInterval;
		static constexpr AddressPtr<Setting, 0x11DA158> fLoadingInitUpdateInterval;
		static constexpr AddressPtr<Setting, 0x11DA118> fLoadingTextUpdateInterval;
		static constexpr AddressPtr<Setting, 0x11DA190> fMainMenuBkgdUpdateInterval;
		static constexpr AddressPtr<Setting, 0x11DA138> iMaxScreens;
		static constexpr AddressPtr<Setting, 0x11DA124> iMaxScreens_MainMenu;
		static constexpr AddressPtr<Setting, 0x11DA108> iNumLocationSpecificScreens;
		static constexpr AddressPtr<Setting, 0x11DA184> sInitialSound;
		static constexpr AddressPtr<Setting, 0x11DA1E0> sMainMenuBackground;
		static constexpr AddressPtr<Setting, 0x11DA0F0> sTitleMusic;
		static constexpr AddressPtr<Setting, 0x11DA1B0> sWelcomeScreen1;
		static constexpr AddressPtr<Setting, 0x11DA1BC> sWelcomeScreen2;
		static constexpr AddressPtr<Setting, 0x11DA1C8> sWelcomeScreen3;
		static constexpr AddressPtr<Setting, 0x11DA1D4> sWelcomeScreen4;
	};

	struct LookIK {
		static constexpr AddressPtr<Setting, 0x1267D20> fAngleMax;
		static constexpr AddressPtr<Setting, 0x1267D2C> fAngleMaxEase;
		static constexpr AddressPtr<Setting, 0x1267D38> fEaseAngleShutOff;
		static constexpr AddressPtr<Setting, 0x1267D08> fMaxTrackingDist;
		static constexpr AddressPtr<Setting, 0x1267D14> fMinTrackingDist;
	};

	struct MAIN {
		static constexpr AddressPtr<Setting, 0x11CAC68> fQuestScriptDelayTime;
	};

	struct MESSAGES {
		static constexpr AddressPtr<Setting, 0x11DEC88> bAllowYesToAll;
		static constexpr AddressPtr<Setting, 0x11DEB3C> bBlockMessageBoxes;
		static constexpr AddressPtr<Setting, 0x11DED74> bSkipInitializationFlows;
		static constexpr AddressPtr<Setting, 0x11DEE20> bSkipProgramFlows;
		static constexpr AddressPtr<Setting, 0x11DEDF4> bUseWindowsMessageBox;
		static constexpr AddressPtr<Setting, 0x11DEE6C> iFileLogging;
	};

	struct Menu {
		static constexpr AddressPtr<Setting, 0x11D94E4> fCreditsScrollSpeed;
		static constexpr AddressPtr<Setting, 0x11D8D38> iConsoleFont;
		static constexpr AddressPtr<Setting, 0x11D8CF0> iConsoleHistorySize;
		static constexpr AddressPtr<Setting, 0x11D8D1C> iConsoleLineSpacing;
		static constexpr AddressPtr<Setting, 0x11D8D44> iConsoleTextXPos;
		static constexpr AddressPtr<Setting, 0x11D8D08> iConsoleTextYPos;
		static constexpr AddressPtr<Setting, 0x11D8CFC> iConsoleVisibleLines;
		static constexpr AddressPtr<Setting, 0x11F33C8> iDebugTextFont;
		static constexpr AddressPtr<Setting, 0x11F33BC> rDebugTextColor;
	};

	struct NavMeshGeneration {
		static constexpr AddressPtr<Setting, 0x11D6CA8> bGlobalNavMeshCheck;
	};

	struct Online {
		static constexpr AddressPtr<Setting, 0x11F3644> bXenonLoadDownloadedContent;
		static constexpr AddressPtr<Setting, 0x11F3638> uXenonPresenceUpdateInterval;
	};

	struct Pathfinding {
		static constexpr AddressPtr<Setting, 0x11D71A0> bBackgroundNavmeshUpdate;
		static constexpr AddressPtr<Setting, 0x11D77CC> bBackgroundPathing;
		static constexpr AddressPtr<Setting, 0x11D7450> bCreateDebugInfo;
		static constexpr AddressPtr<Setting, 0x11D7188> bCutDoors;
		static constexpr AddressPtr<Setting, 0x11D846C> bDrawPathBounds;
		static constexpr AddressPtr<Setting, 0x11D7428> bRebuildPathIfSmootherFailed;
		static constexpr AddressPtr<Setting, 0x11D6E40> bSelectedPathDrawAvoidNodes;
		static constexpr AddressPtr<Setting, 0x11F2BB8> bUseActorAvoidance;
		static constexpr AddressPtr<Setting, 0x11D7444> bUseAlternateSmoothingForPrime;
		static constexpr AddressPtr<Setting, 0x11F2BE0> bUseFartherCheckForAvoidance;
		static constexpr AddressPtr<Setting, 0x11D73E4> bUseObstacleAvoidance;
		static constexpr AddressPtr<Setting, 0x11D7434> bUseOldPathSmoothing;
		static constexpr AddressPtr<Setting, 0x11D73F0> bUsePathSmoothing;
		static constexpr AddressPtr<Setting, 0x11D7404> bUseRayCasts;
		static constexpr AddressPtr<Setting, 0x11D73D8> bUseStraightLineCheckFirst;
		static constexpr AddressPtr<Setting, 0x11F2AC4> fAICombatTurnSpeedScale;
		static constexpr AddressPtr<Setting, 0x11F2AD8> fAITurnSpeedScale;
		static constexpr AddressPtr<Setting, 0x11F2B8C> fAvoidanceAvoidAllRadius;
		static constexpr AddressPtr<Setting, 0x11F2BA8> fAvoidanceConeAngle;
		static constexpr AddressPtr<Setting, 0x11F2B74> fAvoidanceDefaultWaitTime;
		static constexpr AddressPtr<Setting, 0x11F2B1C> fAvoidanceDetectionTime;
		static constexpr AddressPtr<Setting, 0x11F2BC4> fAvoidanceIgnoreMinTime;
		static constexpr AddressPtr<Setting, 0x11F2B3C> fAvoidanceIgnoreTime;
		static constexpr AddressPtr<Setting, 0x11F2B2C> fAvoidanceMinWaitTime;
		static constexpr AddressPtr<Setting, 0x11F2B98> fAvoidanceTimeCheck;
		static constexpr AddressPtr<Setting, 0x11F2AF8> fAvoidanceWiderConeAngle;
		static constexpr AddressPtr<Setting, 0x11F2B10> fCreatureCombatTurnSpeedScale;
		static constexpr AddressPtr<Setting, 0x11F2C10> fCreatureTurnSpeedScale;
		static constexpr AddressPtr<Setting, 0x11D71B0> fObstacleUpdateDeltaWhenMoving;
		static constexpr AddressPtr<Setting, 0x11D7194> fObstacleUpdateDeltaWhenUnknown;
		static constexpr AddressPtr<Setting, 0x11D7084> fPOVSmootherAvoidNodeCost;
		static constexpr AddressPtr<Setting, 0x11F2B68> fRepathingWaitDistance;
		static constexpr AddressPtr<Setting, 0x11F2AB4> fRotationSpeedIncrease;
		static constexpr AddressPtr<Setting, 0x11F2B04> fRunningWiderConeAngle;
	};

	struct Pathing {
		static constexpr AddressPtr<Setting, 0x11D74DC> fFindClosestEdgesRadius;
		static constexpr AddressPtr<Setting, 0x11E029C> fINIDetectDoorsForPathingTime;
	};

	struct Pipboy {
		static constexpr AddressPtr<Setting, 0x11DB2A4> bEnableFlickerPipboy;
		static constexpr AddressPtr<Setting, 0x11DB2CC> bUsePipboyMode;
		static constexpr AddressPtr<Setting, 0x11DB2DC> fBlurIntensityPipboy;
		static constexpr AddressPtr<Setting, 0x11DB328> fBlurRadiusPipboy;
		static constexpr AddressPtr<Setting, 0x11DB2BC> fLightEffectFadeDuration;
		static constexpr AddressPtr<Setting, 0x11DB308> fLightEffectLightFadeDuration;
		static constexpr AddressPtr<Setting, 0x11DB274> fScanlineFrequencyPipboy;
		static constexpr AddressPtr<Setting, 0x11DB2F0> fScrollKnobIncrement;
		static constexpr AddressPtr<Setting, 0x11DB358> fScrollKnobRate;
		static constexpr AddressPtr<Setting, 0x11DB34C> fTabKnobMaxPosition;
		static constexpr AddressPtr<Setting, 0x11DB33C> fTabKnobMinPosition;
		static constexpr AddressPtr<Setting, 0x11DB288> fTabKnobMoveRate;
	};

	struct RagdollAnim {
		static constexpr AddressPtr<Setting, 0x1267C30> bFootIK;
		static constexpr AddressPtr<Setting, 0x1267C3C> bGrabIK;
		static constexpr AddressPtr<Setting, 0x1267C48> bLookIK;
		static constexpr AddressPtr<Setting, 0x1267C60> bPoseMatching;
		static constexpr AddressPtr<Setting, 0x1267C24> bRagdollAnim;
		static constexpr AddressPtr<Setting, 0x1267C54> bRagdollFeedback;
		static constexpr AddressPtr<Setting, 0x1267C90> fAccelerationGain;
		static constexpr AddressPtr<Setting, 0x1267C6C> fCameraDist;
		static constexpr AddressPtr<Setting, 0x1268298> fDesiredVel;
		static constexpr AddressPtr<Setting, 0x12682B0> fDetectionUpdateTimeSec;
		static constexpr AddressPtr<Setting, 0x1267C78> fHierarchyGain;
		static constexpr AddressPtr<Setting, 0x12682A4> fImpulseLimit;
		static constexpr AddressPtr<Setting, 0x1267CA8> fPositionGain;
		static constexpr AddressPtr<Setting, 0x1267CC0> fPositionMaxAngularVelocity;
		static constexpr AddressPtr<Setting, 0x1267CB4> fPositionMaxLinearVelocity;
		static constexpr AddressPtr<Setting, 0x1267CCC> fSnapGain;
		static constexpr AddressPtr<Setting, 0x1267CFC> fSnapMaxAngularDistance;
		static constexpr AddressPtr<Setting, 0x1267CE4> fSnapMaxAngularVelocity;
		static constexpr AddressPtr<Setting, 0x1267CF0> fSnapMaxLinearDistance;
		static constexpr AddressPtr<Setting, 0x1267CD8> fSnapMaxLinearVelocity;
		static constexpr AddressPtr<Setting, 0x1267C84> fVelocityDamping;
		static constexpr AddressPtr<Setting, 0x1267C9C> fVelocityGain;
	};

	struct RagdollFeedback {
		static constexpr AddressPtr<Setting, 0x1267E04> uiFeedbackTimeout;
	};

	struct RenderedMenus {
		static constexpr AddressPtr<Setting, 0x11DB620> bUseRenderedTerminals;
		static constexpr AddressPtr<Setting, 0x11DB5B4> fRaceSexMenuDistortDuration;
		static constexpr AddressPtr<Setting, 0x11DB5CC> fRaceSexMenuHPos;
		static constexpr AddressPtr<Setting, 0x11DB544> fRaceSexMenuScale;
		static constexpr AddressPtr<Setting, 0x11DB594> fRaceSexMenuVPos;
		static constexpr AddressPtr<Setting, 0x11DB570> fRaceSexMenuZoom;
		static constexpr AddressPtr<Setting, 0x11DB5EC> fRenderedTerminalFOV;
		static constexpr AddressPtr<Setting, 0x11DB62C> fRenderedTerminalHPos;
		static constexpr AddressPtr<Setting, 0x11DB674> fRenderedTerminalScanlineScale;
		static constexpr AddressPtr<Setting, 0x11DB614> fRenderedTerminalVPos;
		static constexpr AddressPtr<Setting, 0x11DB65C> fRenderedTerminalZoom;
		static constexpr AddressPtr<Setting, 0x11DB650> fScreenLightBaseIntensity;
		static constexpr AddressPtr<Setting, 0x11DB5F8> fScreenLightColorB;
		static constexpr AddressPtr<Setting, 0x11DB668> fScreenLightColorG;
		static constexpr AddressPtr<Setting, 0x11DB608> fScreenLightColorR;
		static constexpr AddressPtr<Setting, 0x11DB644> fScreenLightRadius;
	};

	struct SaveGame {
		static constexpr AddressPtr<Setting, 0x11DE280> bAllowProfileTransfer;
		static constexpr AddressPtr<Setting, 0x11DE29C> bAllowScriptedAutosave;
		static constexpr AddressPtr<Setting, 0x11DE2B8> bAllowScriptedForceSave;
		static constexpr AddressPtr<Setting, 0x11DE308> bCopySaveGameToHostOrMemStick;
		static constexpr AddressPtr<Setting, 0x11DE248> bDisplayMissingContentDialogue;
		static constexpr AddressPtr<Setting, 0x11DE2FC> bOutputSaveGameScreenshot;
		static constexpr AddressPtr<Setting, 0x11DE0A4> bUseSaveGameHistory;
		static constexpr AddressPtr<Setting, 0x11DE2C8> iSaveGameBackupCount;
		static constexpr AddressPtr<Setting, 0x11DE25C> sSaveGameSafeMarkerID;
	};

	struct ScreenSplatter {
		static constexpr AddressPtr<Setting, 0x11C784C> bBloodSplatterEnabled;
		static constexpr AddressPtr<Setting, 0x11C77F4> bCustomSplatterEnabled;
	};

	struct SpeedTree {
		static constexpr AddressPtr<Setting, 0x11D5CE8> bEnableTrees;
		static constexpr AddressPtr<Setting, 0x11D5D00> bForceFullLOD;
		static constexpr AddressPtr<Setting, 0x11D5D4C> fCanopyShadowGrassMult;
		static constexpr AddressPtr<Setting, 0x11DEB70> fLODTreeMipMapLODBias;
		static constexpr AddressPtr<Setting, 0x11DEC18> fLocalTreeMipMapLODBias;
		static constexpr AddressPtr<Setting, 0x11D5DB8> fTreeForceBranchDimming;
		static constexpr AddressPtr<Setting, 0x11D5D14> fTreeForceCS;
		static constexpr AddressPtr<Setting, 0x11D5D8C> fTreeForceLLA;
		static constexpr AddressPtr<Setting, 0x11D5D24> fTreeForceLeafDimming;
		static constexpr AddressPtr<Setting, 0x11D5C80> fTreeForceMaxBudAngle;
		static constexpr AddressPtr<Setting, 0x11D5C9C> fTreeForceMinBudAngle;
		static constexpr AddressPtr<Setting, 0x11D5CA8> fTreeLODExponent;
		static constexpr AddressPtr<Setting, 0x11D5D98> iCanopyShadowScale;
	};

	struct Surgery3D {
		static constexpr AddressPtr<Setting, 0x11DAE28> fSurgeryPlayerDefaultHPos;
		static constexpr AddressPtr<Setting, 0x11DADFC> fSurgeryPlayerDefaultScale;
		static constexpr AddressPtr<Setting, 0x11DADF0> fSurgeryPlayerDefaultVPos;
		static constexpr AddressPtr<Setting, 0x11DADBC> fSurgeryPlayerZoom;
		static constexpr AddressPtr<Setting, 0x11DAE08> fSurgerySkinHPos;
		static constexpr AddressPtr<Setting, 0x11DAE80> fSurgerySkinScale;
		static constexpr AddressPtr<Setting, 0x11DAE34> fSurgerySkinVPos;
		static constexpr AddressPtr<Setting, 0x11DAE6C> fSurgerySkinZoom;
	};

	struct TerrainManager {
		static constexpr AddressPtr<Setting, 0x11D8760> bKeepLowDetailTerrain;
		static constexpr AddressPtr<Setting, 0x11D869C> bUseDistantObjectBlocks;
		static constexpr AddressPtr<Setting, 0x11D8680> bUseDistantTrees;
		static constexpr AddressPtr<Setting, 0x11D86AC> bUseNewTerrainSystem;
		static constexpr AddressPtr<Setting, 0x11D870C> fDefaultBlockLoadDistanceLow;
		static constexpr AddressPtr<Setting, 0x11D8770> fDefaultTreeLoadDistance;
		static constexpr AddressPtr<Setting, 0x11D86F8> fDetailTextureScale;
		static constexpr AddressPtr<Setting, 0x11D86EC> fHighBlockLoadDistanceLow;
		static constexpr AddressPtr<Setting, 0x11D8718> fHighTreeLoadDistance;
		static constexpr AddressPtr<Setting, 0x11D86C4> fLowBlockLoadDistanceLow;
		static constexpr AddressPtr<Setting, 0x11D8734> fLowTreeLoadDistance;
		static constexpr AddressPtr<Setting, 0x11D86D4> fMorphEndDistanceMult;
		static constexpr AddressPtr<Setting, 0x11D8754> fMorphStartDistanceMult;
		static constexpr AddressPtr<Setting, 0x11D85A8> uDistantTreeBlockCacheSizePerCell;
		static constexpr AddressPtr<Setting, 0x11D8740> uTerrainTextureFadeTime;
	};

	struct TestAllCells {
		static constexpr AddressPtr<Setting, 0x11C4080> bFileCheckModelCollision;
		static constexpr AddressPtr<Setting, 0x11CA3AC> bFileControllerOnRoot;
		static constexpr AddressPtr<Setting, 0x11C3FD4> bFileGoneMessage;
		static constexpr AddressPtr<Setting, 0x11C4054> bFileNeededMessage;
		static constexpr AddressPtr<Setting, 0x11C3F80> bFileShowIcons;
		static constexpr AddressPtr<Setting, 0x11C4060> bFileShowTextures;
		static constexpr AddressPtr<Setting, 0x11C3F98> bFileSkipIconChecks;
		static constexpr AddressPtr<Setting, 0x11C408C> bFileSkipModelChecks;
		static constexpr AddressPtr<Setting, 0x11C3FA8> bFileTestLoad;
		static constexpr AddressPtr<Setting, 0x11C4074> bFileUnusedObject;
	};

	struct VATS {
		static constexpr AddressPtr<Setting, 0x11DF868> bVATSSmartCameraCheckDebug;
		static constexpr AddressPtr<Setting, 0x11DB714> fBlurIntensity;
		static constexpr AddressPtr<Setting, 0x11DB720> fBlurRadius;
		static constexpr AddressPtr<Setting, 0x11DB6D8> fBurstDuration;
		static constexpr AddressPtr<Setting, 0x11DB750> fBurstIntensity;
		static constexpr AddressPtr<Setting, 0x11DB6BC> fDistortDuration;
		static constexpr AddressPtr<Setting, 0x11DB79C> fDistortHorizontalScale;
		static constexpr AddressPtr<Setting, 0x11DB6E4> fDistortVerticalScale;
		static constexpr AddressPtr<Setting, 0x11DB7C4> fPulseIntensity;
		static constexpr AddressPtr<Setting, 0x11DB6C8> fPulseRadius;
		static constexpr AddressPtr<Setting, 0x11DB7D8> fPulseRate;
		static constexpr AddressPtr<Setting, 0x11DB730> fScanModeDuration;
		static constexpr AddressPtr<Setting, 0x11DB694> fScanModeScanlineFrequency;
		static constexpr AddressPtr<Setting, 0x11DB7B4> fScanModeVerticalScale;
		static constexpr AddressPtr<Setting, 0x11DB778> fScanlineFrequency;
		static constexpr AddressPtr<Setting, 0x11DB700> fVATSColorB;
		static constexpr AddressPtr<Setting, 0x11DB768> fVATSColorG;
		static constexpr AddressPtr<Setting, 0x11DB6F4> fVATSColorR;
		static constexpr AddressPtr<Setting, 0x11F2304> fVATSLightAngle;
		static constexpr AddressPtr<Setting, 0x11F222C> fVATSLightDistance;
		static constexpr AddressPtr<Setting, 0x11F220C> fVATSLightElevation;
		static constexpr AddressPtr<Setting, 0x11F2200> fVATSLightLevelMax;
		static constexpr AddressPtr<Setting, 0x11F2298> fVATSLightLevelMin;
		static constexpr AddressPtr<Setting, 0x11DB78C> fVATSTargetPulseRate;
		static constexpr AddressPtr<Setting, 0x11F22CC> fVatsLightColorB;
		static constexpr AddressPtr<Setting, 0x11F22A8> fVatsLightColorG;
		static constexpr AddressPtr<Setting, 0x11F21F4> fVatsLightColorR;
		static constexpr AddressPtr<Setting, 0x11DB75C> iDistortMaxInterval;
		static constexpr AddressPtr<Setting, 0x11DB744> sScanlineTexture;
	};

	struct Voice {
		static constexpr AddressPtr<Setting, 0x11CBE14> sFileTypeGame;
		static constexpr AddressPtr<Setting, 0x11CBDB8> sFileTypeLTF;
		static constexpr AddressPtr<Setting, 0x11CBDE4> sFileTypeLip;
		static constexpr AddressPtr<Setting, 0x11CBE34> sFileTypeSource;
	};

	struct Water {
		static constexpr AddressPtr<Setting, 0x11C7CC0> bForceHighDetailLandReflections;
		static constexpr AddressPtr<Setting, 0x11C7AA8> bForceLowDetailReflections;
		static constexpr AddressPtr<Setting, 0x11C7AE8> bReflectExplosions;
		static constexpr AddressPtr<Setting, 0x11C7C80> bUseBulletWaterDisplacements;
		static constexpr AddressPtr<Setting, 0x11C7B98> bUsePerWorldSpaceWaterNoise;
		static constexpr AddressPtr<Setting, 0x11C7ADC> bUseWater;
		static constexpr AddressPtr<Setting, 0x11C7B48> bUseWaterHiRes;
		static constexpr AddressPtr<Setting, 0x11C7C54> bUseWaterLOD;
		static constexpr AddressPtr<Setting, 0x11C7B20> bUseWaterShader;
		static constexpr AddressPtr<Setting, 0x11C7AB8> fExteriorWaterReflectionThreshold;
		static constexpr AddressPtr<Setting, 0x11C7C3C> fInteriorWaterReflectionThreshold;
		static constexpr AddressPtr<Setting, 0x11C7BD8> fNearWaterIndoorTolerance;
		static constexpr AddressPtr<Setting, 0x11C7BA4> fNearWaterOutdoorTolerance;
		static constexpr AddressPtr<Setting, 0x11C7C6C> fNearWaterUnderwaterFreq;
		static constexpr AddressPtr<Setting, 0x11C7CD8> fNearWaterUnderwaterVolume;
		static constexpr AddressPtr<Setting, 0x11C7C10> fRefractionWaterPlaneBias;
		static constexpr AddressPtr<Setting, 0x11C7B14> fSurfaceTileSize;
		static constexpr AddressPtr<Setting, 0x11C7CCC> fTileTextureDivisor;
		static constexpr AddressPtr<Setting, 0x11C7B54> fWadingWaterQuadSize;
		static constexpr AddressPtr<Setting, 0x11C7CA4> fWadingWaterTextureRes;
		static constexpr AddressPtr<Setting, 0x11C7A7C> fWaterGroupHeightRange;
		static constexpr AddressPtr<Setting, 0x11CA570> iWaterNoiseResolution;
		static constexpr AddressPtr<Setting, 0x11C7C8C> sSurfaceTexture;
		static constexpr AddressPtr<Setting, 0x11C7BEC> uMaxExteriorWaterReflections;
		static constexpr AddressPtr<Setting, 0x11C7AFC> uMaxInteriorWaterReflections;
		static constexpr AddressPtr<Setting, 0x11C7BB0> uNearWaterPoints;
		static constexpr AddressPtr<Setting, 0x11C7B2C> uNearWaterRadius;
		static constexpr AddressPtr<Setting, 0x11C7A9C> uSurfaceFPS;
	};

	struct Weather {
		static constexpr AddressPtr<Setting, 0x11CCB8C> bPrecipitation;
		static constexpr AddressPtr<Setting, 0x11C3CF4> fAlphaReduce;
		static constexpr AddressPtr<Setting, 0x11CCE7C> fSunBaseSize;
		static constexpr AddressPtr<Setting, 0x11CCE50> fSunGlareSize;
		static constexpr AddressPtr<Setting, 0x11C3E0C> sBumpFadeColor;
		static constexpr AddressPtr<Setting, 0x11C3C20> sEnvReduceColor;
		static constexpr AddressPtr<Setting, 0x11C3C50> sLerpCloseColor;
	};

	struct bLightAttenuation {
		static constexpr AddressPtr<Setting, 0x11C8FC0> bOutQuadInLin;
		static constexpr AddressPtr<Setting, 0x11C9060> bUseConstant;
		static constexpr AddressPtr<Setting, 0x11C8FF0> bUseLinear;
		static constexpr AddressPtr<Setting, 0x11C9028> bUseQuadratic;
		static constexpr AddressPtr<Setting, 0x11C9000> fConstantValue;
		static constexpr AddressPtr<Setting, 0x11C8FCC> fFlickerMovement;
		static constexpr AddressPtr<Setting, 0x11C8FB0> fLinearRadiusMult;
		static constexpr AddressPtr<Setting, 0x11C908C> fLinearValue;
		static constexpr AddressPtr<Setting, 0x11C906C> fQuadraticRadiusMult;
		static constexpr AddressPtr<Setting, 0x11C9040> fQuadraticValue;
		static constexpr AddressPtr<Setting, 0x11C9054> uLinearMethod;
		static constexpr AddressPtr<Setting, 0x11C907C> uQuadraticMethod;
	};
};