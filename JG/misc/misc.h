#pragma once

class Script;
struct ScriptEventList;
#define PASS_VARARGS  scriptObj, eventList
#define VARARGS Script *scriptObj, ScriptEventList *eventList

//All thanks to jazzisparis for the code, since it's way faster than tanf.

extern float tan_p(float angle);

extern float dTan(float angle);

extern float fastDTan(float value);

extern void setVarByName(VARARGS, const char* var_name, float value);

//Only ready for a 24-bit BMP, will check for non-24 bit later.
//Also currently doesn't handle negative height/width BMPs, will fix later
extern bool ReadBMP24(char* filename, unsigned long& R, unsigned long& G, unsigned long& B, unsigned long PixelW, unsigned long PixelH);

//changed tables to only loop through the ones that actually need it, credits to jazzisparis

static const UInt32 TESForm_Vtables[] =
{
	0x101144C,	//	BGSDehydrationStage
	0x10115B4,  //	BGSHungerStage
	0x10116FC,	//	BGSSleepDeprevationStage
	0x1011964,	//	AlchemyItem
	0x1012834,	//	EffectSetting
	0x1012EA4,	//	EnchantmentItem
	0x1013F8C,	//	SpellItem
	0x102397C,	//	TESRegion
	0x1024214,	//	BGSAddonNode
	0x1024834,	//	BGSDebris
	0x1024A94,	//	BGSExplosion
	0x1024CEC,  //  BGSMovableStatic
	0x1024F4C,	//	BGSPlaceableWater
	0x10251AC,	//	BGSProjectile
	0x102535C,	//	BGSStaticCollection
	0x1025594,	//	BGSTalkingActivator
	0x1025914,	//	BGSTerminal
	0x1026064,	//	TESAmmo
	0x10263DC,	//	TESCasinoChips
	0x1026574,	//	TESCasino
	0x10266E4,	//	TESCombatStyle
	0x102685C,	//	TESEffectShader
	0x1026A4C,	//	TESFlora
	0x1026D0C,	//	TESFurniture
	0x102814C,	//	TESGrass
	0x1028444,	//	TESKey
	0x102864C,	//	TESLevCharacter
	0x102886C,	//	TESLevCreature
	0x1028A64,	//	TESLevItem
	0x1028C5C,	//	TESLevSpell
	0x1028EE4,	//	TESObjectLIGH
	0x1029D5C,	//	TESObjectACTI
	0x102A0A4,	//	TESObjectANIO
	0x102A31C,	//	TESObjectARMA
	0x102A62C,	//	TESObjectARMO
	0x102A9C4,	//	TESObjectBOOK
	0x102AEB4,	//	TESObjectCONT
	0x102B1FC,	//	TESObjectDOOR
	0x102B5AC,	//	TESObjectIMOD
	0x102B844,	//	TESObjectMISC
	0x102BA2C,	//	TESObjectSTAT
	0x102BC94,	//	TESObjectTREE
	0x102C51C,	//	TESObjectWEAP
	0x102CBBC,	//	BGSEncounterZone
	0x102CD94,	//	BGSLightingTemplate
	0x102D5C4,	//	TESClimate
	0x102D7F4,	//	TESImageSpace
	0x102D97C,	//	TESImageSpaceModifier
	0x102DCD4,	//	TESObjectLAND
	0x102E6C4,	//	TESLandTexture
	0x102F55C,  //  TESObjectREFR
	0x103140C,	//	TESWaterForm
	0x103168C,	//	TESWeather
	0x10320FC,	//	BGSAcousticSpace
	0x103245C,	//	BGSCameraPath
	0x10327F4,	//	BGSCameraShot
	0x1032F6C,	//	BGSImpactData
	0x103323C,	//	BGSImpactDataSet
	0x10334B4,	//	BGSListForm
	0x1033654,	//	BGSMenuIcon
	0x10337C4,	//	BGSMessage
	0x103397C,	//	BGSMusicType
	0x1033B34,	//	BGSRadiationStage
	0x1033D1C,	//	BGSTextureSet
	0x10340C4,	//	MediaLocationController
	0x10342EC,	//	MediaSet
	0x103449C,	//	TESAmmoEffect
	0x103478C,	//	TESCaravanCard
	0x10349B4,	//	TESCaravanMoney
	0x1034B4C,	//	TESCaravanDeck
	0x10366CC,	//	TESLoadScreen
	0x1036854,	//	TESLoadScreenType
	0x10369DC,	//	TESRecipeCategory
	0x1036B2C,	//	TESRecipe
	0x1037094,	//	Script
	0x1045504,	//	BGSBodyPartData
	0x10464B4,	//	BGSHeadPart
	0x104664C,	//	BGSIdleMarker
	0x1046874,	//	BGSNote
	0x1046EC4,	//	BGSPerk
	0x10470EC,	//	BGSRagdoll
	0x104891C,	//	TESChallenge
	0x1048BB4,	//	TESClass
	0x1048F5C,	//	TESCreature
	0x104973C,	//	TESEyes
	0x10498DC,	//	TESFaction
	0x1049B9C,	//	TESHair
	0x104A2F4,	//	TESNPC
	0x104AC44,  //	TESQuest
	0x104BA24,	//	TESReputation
	0x104CC0C,	//	TESSkill
	0x104D5B4,	//	TESTopicInfo
	0x1067A2C,  //  ActorValueInfo
	0x106847C,	//	TESPackage
	0x107A554,  //  MagicBallProjectile
	0x107A8F4,  //  MagicBoltProjectile
	0x107AD84,  //  MagicFogProjectile
	0x107B394,  //  MagicProjectile
	0x107B8C4,  //  MagicSprayProjectile
	0x1084254,  //  Actor
	0x1085954,  //  ArrowProjectile
	0x1086A6C,  //  Character
	0x10870AC,  //  Creature
	0x108A49C,  //  MobileObject
	0x108AA3C,  //  PlayerCharacter
	0x108C3C4,  //  BeamProjectile
	0x108EA64,  //  ContinuousBeamProjectile
	0x108EE04,  //  Explosion
	0x108F2F4,  //  FlameProjectile
	0x108F674,  //  GrenadeProjectile
	0x108FA44,  //  MissileProjectile
	0x10900DC,  //  Projectile
};