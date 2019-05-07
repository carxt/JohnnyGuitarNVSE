#pragma once

const double
kDblZero = 0,
kDblPI = 3.141592653589793,
kDblPIx2 = 6.283185307179586,
kDblPIx3d2 = 4.71238898038469,
kDblPId2 = 1.5707963267948966,
kDblPId4 = 0.7853981633974483,
kDblPId6 = 0.5235987755982989,
kDblPId12 = 0.26179938779914946,
kDbl2dPI = 0.6366197723675814,
kDbl4dPI = 1.2732395447351628,
kDblTanPId6 = 0.5773502691896257,
kDblTanPId12 = 0.2679491924311227,
kDblPId180 = 0.017453292519943295;

//All thanks to jazzisparis for the code, since it's way faster than tanf.

inline float tan_p(float angle)
{
	angle *= kDbl4dPI;
	double ang2 = angle * angle;
	return angle * (211.849369664121 - 12.5288887278448 * ang2) / (269.7350131214121 + ang2 * (ang2 - 71.4145309347748));
}


 
 __forceinline float dTan(float angle) {
	 {
		 while (angle > kDblPIx2)
			 angle -= kDblPIx2;

		 int octant = int(angle * kDbl4dPI);
		 switch (octant)
		 {
		 case 0:
			 return tan_p(angle);
		 case 1:
			 return 1.0 / tan_p(kDblPId2 - angle);
		 case 2:
			 return -1.0 / tan_p(angle - kDblPId2);
		 case 3:
			 return -tan_p(kDblPI - angle);
		 case 4:
			 return tan_p(angle - kDblPI);
		 case 5:
			 return 1.0 / tan_p(kDblPIx3d2 - angle);
		 case 6:
			 return -1.0 / tan_p(angle - kDblPIx3d2);
		 default:
			 return -tan_p(kDblPIx2 - angle);
		 }
	 }
 }

float fastDTan(float value) {
	bool sign = (value < 0);
	if (sign) value = -value;
	float tempRes = dTan(value * kDblPId180);
	return (sign ? -tempRes : tempRes);
}


//As defined in NVSE.


#define PASS_VARARGS  scriptObj, eventList
#define VARARGS Script *scriptObj, ScriptEventList *eventList



void setVarByName(VARARGS, const char *var_name, float value)
{
	for (Script::VarInfoEntry *entry = &(scriptObj->varList); entry; entry = entry->next)
	{
		if (!strcmp(((char*)entry->data->name.CStr()), var_name))
		{
			eventList->GetVariable(entry->data->idx)->data = value;
			break;
		}
	}
}


//This is useful when you don't want to bother with DYNAMIC_CAST and you don't need it. 
//These are the values of each first member of the game's classes, which are pointers to vftables
//All thanks to jazzisparis.

enum
{
	kVtbl_BGSTextureSet = 0x1033D1C,
	kVtbl_BGSMenuIcon = 0x1033654,
	kVtbl_TESGlobal = 0x1036524,
	kVtbl_TESClass = 0x1048BB4,
	kVtbl_TESFaction = 0x10498DC,
	kVtbl_BGSHeadPart = 0x10464B4,
	kVtbl_TESHair = 0x1049B9C,
	kVtbl_TESEyes = 0x104973C,
	kVtbl_TESRace = 0x104B4BC,
	kVtbl_TESSound = 0x1044FFC,
	kVtbl_BGSAcousticSpace = 0x10320FC,
	kVtbl_TESSkill = 0x104CC0C,
	kVtbl_EffectSetting = 0x1012834,
	kVtbl_Script = 0x1037094,
	kVtbl_TESLandTexture = 0x102E6C4,
	kVtbl_EnchantmentItem = 0x1012EA4,
	kVtbl_SpellItem = 0x1013F8C,
	kVtbl_TESObjectACTI = 0x1029D5C,
	kVtbl_BGSTalkingActivator = 0x1025594,
	kVtbl_BGSTerminal = 0x1025914,
	kVtbl_TESObjectARMO = 0x102A62C,
	kVtbl_TESObjectBOOK = 0x102A9C4,
	kVtbl_TESObjectCLOT = 0x102AC0C,
	kVtbl_TESObjectCONT = 0x102AEB4,
	kVtbl_TESObjectDOOR = 0x102B1FC,
	kVtbl_IngredientItem = 0x1013284,
	kVtbl_TESObjectLIGH = 0x1028EE4,
	kVtbl_TESObjectMISC = 0x102B844,
	kVtbl_TESObjectSTAT = 0x102BA2C,
	kVtbl_BGSStaticCollection = 0x102535C,
	kVtbl_BGSMovableStatic = 0x1024E84,
	kVtbl_BGSPlaceableWater = 0x1024F4C,
	kVtbl_TESGrass = 0x102814C,
	kVtbl_TESObjectTREE = 0x102BC94,
	kVtbl_TESFlora = 0x1026BD0,
	kVtbl_TESFurniture = 0x1026D0C,
	kVtbl_TESObjectWEAP = 0x102C51C,
	kVtbl_TESAmmo = 0x1026064,
	kVtbl_TESNPC = 0x104A2F4,
	kVtbl_TESCreature = 0x1048F5C,
	kVtbl_TESLevCreature = 0x102886C,
	kVtbl_TESLevCharacter = 0x102864C,
	kVtbl_TESKey = 0x1028444,
	kVtbl_AlchemyItem = 0x1011964,
	kVtbl_BGSIdleMarker = 0x104664C,
	kVtbl_BGSNote = 0x1046874,
	kVtbl_BGSConstructibleObject = 0x10245A4,
	kVtbl_BGSProjectile = 0x10251AC,
	kVtbl_TESLevItem = 0x1028A64,
	kVtbl_TESWeather = 0x103168C,
	kVtbl_TESClimate = 0x102D5C4,
	kVtbl_TESRegion = 0x102397C,
	kVtbl_NavMeshInfoMap = 0x106BB8C,
	kVtbl_TESObjectCELL = 0x102E9B4,
	kVtbl_TESObjectREFR = 0x102F55C,
	kVtbl_Character = 0x1086A6C,
	kVtbl_Creature = 0x10870AC,
	kVtbl_MissileProjectile = 0x108FA44,
	kVtbl_GrenadeProjectile = 0x108F674,
	kVtbl_BeamProjectile = 0x108C3C4,
	kVtbl_FlameProjectile = 0x108F2F4,
	kVtbl_TESWorldSpace = 0x103195C,
	kVtbl_TESObjectLAND = 0x102DCD4,
	kVtbl_NavMesh = 0x106A0B4,
	kVtbl_TESTopic = 0x104D19C,
	kVtbl_TESTopicInfo = 0x104D5B4,
	kVtbl_TESQuest = 0x104AC44,
	kVtbl_TESIdleForm = 0x1049D0C,
	kVtbl_TESPackage = 0x106847C,
	kVtbl_TESCombatStyle = 0x10266E4,
	kVtbl_TESLoadScreen = 0x10366CC,
	kVtbl_TESLevSpell = 0x1028C5C,
	kVtbl_TESObjectANIO = 0x102A0A4,
	kVtbl_TESWaterForm = 0x103140C,
	kVtbl_TESEffectShader = 0x102685C,
	kVtbl_BGSExplosion = 0x1024A94,
	kVtbl_BGSDebris = 0x1024834,
	kVtbl_TESImageSpace = 0x102D7F4,
	kVtbl_TESImageSpaceModifier = 0x102D97C,
	kVtbl_BGSListForm = 0x10334B4,
	kVtbl_BGSPerk = 0x1046EC4,
	kVtbl_BGSBodyPartData = 0x1045504,
	kVtbl_BGSAddonNode = 0x1024214,
	kVtbl_ActorValueInfo = 0x1067A2C,
	kVtbl_BGSRadiationStage = 0x1033B34,
	kVtbl_BGSCameraShot = 0x10327F4,
	kVtbl_BGSCameraPath = 0x103245C,
	kVtbl_BGSVoiceType = 0x104733C,
	kVtbl_BGSImpactData = 0x1032F6C,
	kVtbl_BGSImpactDataSet = 0x103323C,
	kVtbl_TESObjectARMA = 0x102A31C,
	kVtbl_BGSEncounterZone = 0x102CBBC,
	kVtbl_BGSMessage = 0x10337C4,
	kVtbl_BGSRagdoll = 0x10470EC,
	kVtbl_BGSLightingTemplate = 0x102CD94,
	kVtbl_BGSMusicType = 0x103397C,
	kVtbl_TESObjectIMOD = 0x102B5AC,
	kVtbl_TESReputation = 0x104BA24,
	kVtbl_ContinuousBeamProjectile = 0x108EA64,
	kVtbl_TESRecipe = 0x1036B2C,
	kVtbl_TESRecipeCategory = 0x10369DC,
	kVtbl_TESCasinoChips = 0x10263DC,
	kVtbl_TESCasino = 0x1026574,
	kVtbl_TESLoadScreenType = 0x1036854,
	kVtbl_MediaSet = 0x10342EC,
	kVtbl_MediaLocationController = 0x10340C4,
	kVtbl_TESChallenge = 0x104891C,
	kVtbl_TESAmmoEffect = 0x103449C,
	kVtbl_TESCaravanCard = 0x103478C,
	kVtbl_TESCaravanMoney = 0x10349B4,
	kVtbl_TESCaravanDeck = 0x1034B4C,
	kVtbl_BGSDehydrationStage = 0x101144C,
	kVtbl_BGSHungerStage = 0x10115B4,
	kVtbl_BGSSleepDeprevationStage = 0x10116FC,
	kVtbl_PlayerCharacter = 0x108AA3C,

	kVtbl_BGSQuestObjective = 0x1047088,
	kVtbl_TESModelTextureSwap = 0x101D124,
	kVtbl_BGSPrimitiveBox = 0x101E8C4,
	kVtbl_BGSPrimitiveSphere = 0x101EA64,
	kVtbl_BGSPrimitivePlane = 0x101E75C,
	kVtbl_MagicShaderHitEffect = 0x107B70C,

	kVtbl_BGSQuestPerkEntry = 0x1046B84,
	kVtbl_BGSAbilityPerkEntry = 0x1046C44,
	kVtbl_BGSEntryPointPerkEntry = 0x1046D0C,
	kVtbl_BGSEntryPointFunctionDataOneValue = 0x10462C0,
	kVtbl_BGSEntryPointFunctionDataTwoValue = 0x1046300,
	kVtbl_BGSEntryPointFunctionDataLeveledList = 0x1046320,
	kVtbl_BGSEntryPointFunctionDataActivateChoice = 0x1046340,

	kVtbl_ExtraSeenData = 0x1014294,
	kVtbl_ExtraSpecialRenderFlags = 0x1014458,
	kVtbl_ExtraPrimitive = 0x10151B4,
	kVtbl_ExtraLinkedRef = 0x1015CC0,
	kVtbl_ExtraRadius = 0x1015208,
	kVtbl_ExtraCellWaterType = 0x1014270,
	kVtbl_ExtraCellImageSpace = 0x1014258,
	kVtbl_ExtraCellMusicType = 0x1014234,
	kVtbl_ExtraCellClimate = 0x101424C,
	kVtbl_ExtraTerminalState = 0x1015190,
	kVtbl_ExtraCellAcousticSpace = 0x1014240,
	kVtbl_ExtraOriginalReference = 0x1015BC4,
	kVtbl_ExtraContainerChanges = 0x1015BB8,
	kVtbl_ExtraWorn = 0x1015BDC,
	kVtbl_ExtraHealth = 0x10158E4,
	kVtbl_ExtraLock = 0x101589C,
	kVtbl_ExtraCount = 0x10158D8,
	kVtbl_ExtraTeleport = 0x10158A8,
	kVtbl_ExtraWeaponModFlags = 0x10159A4,
	kVtbl_ExtraHotkey = 0x101592C,
	kVtbl_ExtraCannotWear = 0x1015BF4,
	kVtbl_ExtraOwnership = 0x10158B4,
	kVtbl_ExtraRank = 0x10158CC,
	kVtbl_ExtraAction = 0x1015BAC,
	kVtbl_ExtraFactionChanges = 0x1015F30,
	kVtbl_ExtraScript = 0x1015914,
	kVtbl_ExtraObjectHealth = 0x1015184,

	kVtbl_SeenData = 0x1083FC4,

	kVtbl_TileMenu = 0x106ED44,

	kVtbl_MessageMenu = 0x107566C,
	kVtbl_InventoryMenu = 0x10739B4,
	kVtbl_StatsMenu = 0x106FFD4,
	kVtbl_HUDMainMenu = 0x1072DF4,
	kVtbl_LoadingMenu = 0x1073EBC,
	kVtbl_ContainerMenu = 0x10721AC,
	kVtbl_DialogMenu = 0x107257C,
	kVtbl_SleepWaitMenu = 0x10763AC,
	kVtbl_StartMenu = 0x1076D1C,
	kVtbl_LockpickMenu = 0x107439C,
	kVtbl_QuantityMenu = 0x10701C4,
	kVtbl_MapMenu = 0x1074D44,
	kVtbl_LevelUpMenu = 0x1073CDC,
	kVtbl_RepairMenu = 0x1075C5C,
	kVtbl_RaceSexMenu = 0x1075974,
	kVtbl_CharGenMenu = 0x1071BB4,
	kVtbl_TextEditMenu = 0x1070034,
	kVtbl_BarterMenu = 0x10706EC,
	kVtbl_SurgeryMenu = 0x1070084,
	kVtbl_HackingMenu = 0x10728F4,
	kVtbl_VATSMenu = 0x10700D4,
	kVtbl_ComputersMenu = 0x1072004,
	kVtbl_RepairServicesMenu = 0x1075DB4,
	kVtbl_TutorialMenu = 0x106FF84,
	kVtbl_SpecialBookMenu = 0x1070124,
	kVtbl_ItemModMenu = 0x1073B7C,
	kVtbl_LoveTesterMenu = 0x1070174,
	kVtbl_CompanionWheelMenu = 0x1071D0C,
	kVtbl_TraitSelectMenu = 0x1077ABC,
	kVtbl_RecipeMenu = 0x107048C,
	kVtbl_SlotMachineMenu = 0x10764DC,
	kVtbl_BlackjackMenu = 0x10708FC,
	kVtbl_RouletteMenu = 0x1075F7C,
	kVtbl_CaravanMenu = 0x107108C,
	kVtbl_TraitMenu = 0x10779BC,

	kVtbl_NiNode = 0x109B5AC,
	kVtbl_BSFadeNode = 0x10A8F90,
	kVtbl_NiControllerManager = 0x109619C,

	kVtbl_hkpAabbPhantom = 0x10CC004,
	kVtbl_hkpSimpleShapePhantom = 0x10CE15C,
	kVtbl_hkpCachingShapePhantom = 0x10D087C,
	kVtbl_hkpRigidBody = 0x10C7888,
	kVtbl_hkpSphereMotion = 0x10C6D54,
	kVtbl_hkpBoxMotion = 0x10C6DC4,
	kVtbl_hkpThinBoxMotion = 0x10C6E34,
	kVtbl_ahkpCharacterProxy = 0x10C83E8,
};



