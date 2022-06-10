#pragma once

#define PASS_VARARGS  scriptObj, eventList
#define VARARGS Script *scriptObj, ScriptEventList *eventList

//All thanks to jazzisparis for the code, since it's way faster than tanf.

inline float tan_p(float angle) {
	angle *= kDbl4dPI;
	double ang2 = angle * angle;
	return angle * (211.849369664121 - 12.5288887278448 * ang2) / (269.7350131214121 + ang2 * (ang2 - 71.4145309347748));
}

__forceinline float dTan(float angle) {
	{
		while (angle > kDblPIx2)
			angle -= kDblPIx2;

		int octant = int(angle * kDbl4dPI);
		switch (octant) {
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

void setVarByName(VARARGS, const char* var_name, float value) {
	ListNode<VariableInfo>* traverse = scriptObj->varList.Head();
	VariableInfo* varInfo;
	do {
		varInfo = traverse->data;
		if (varInfo) {
			if (!strcmp(((char*)varInfo->name.CStr()), var_name)) {
				ScriptVar* scv = eventList->GetVariable(varInfo->idx);
				if (scv) {
					scv->data = value;
					break;
				}
			}
		}
	} while (traverse = traverse->next);
}

//Only ready for a 24-bit BMP, will check for non-24 bit later.
//Also currently doesn't handle negative height/width BMPs, will fix later
bool ReadBMP24(char* filename, unsigned long& R, unsigned long& G, unsigned long& B, unsigned long PixelW, unsigned long PixelH) {
	FILE* f = fopen(filename, "rb");

	if (f == NULL)
		return false;
	char info[54];
	fread(info, sizeof(char), 54, f);
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	if (width < PixelW || height < PixelH) return false;
	int XPadding = (width * 3 + 3) & (~3);
	BYTE* data = new BYTE[XPadding];
	PixelH = height - (PixelH + 1);
	fseek(f, XPadding * PixelH, SEEK_CUR);
	fread(data, sizeof(BYTE), XPadding, f);
	UInt32 PosX = PixelW * 3;
	B = data[PosX];
	G = data[PosX + 1];
	R = data[PosX + 2];
	fclose(f);
	delete data;
	return true;
}

//changed tables to only loop through the ones that actually need it, credits to jazzisparis

const UInt32 TESForm_Vtables[] =
{
	0x103168C,	//	TESWeather
	0x103140C,	//	TESWaterForm
	0x104D5B4,	//	TESTopicInfo
	0x104CC0C,	//	TESSkill
	0x104BA24,	//	TESReputation
	0x102397C,	//	TESRegion
	0x10369DC,	//	TESRecipeCategory
	0x1036B2C,	//	TESRecipe
	0x106847C,	//	TESPackage
	0x102C51C,	//	TESObjectWEAP
	0x102BC94,	//	TESObjectTREE
	0x102BA2C,	//	TESObjectSTAT
	0x102B844,	//	TESObjectMISC
	0x1028EE4,	//	TESObjectLIGH
	0x102DCD4,	//	TESObjectLAND
	0x102B5AC,	//	TESObjectIMOD
	0x102B1FC,	//	TESObjectDOOR
	0x102AEB4,	//	TESObjectCONT
	0x102A9C4,	//	TESObjectBOOK
	0x102A62C,	//	TESObjectARMO
	0x102A31C,	//	TESObjectARMA
	0x102A0A4,	//	TESObjectANIO
	0x1029D5C,	//	TESObjectACTI
	0x104A2F4,	//	TESNPC
	0x1036854,	//	TESLoadScreenType
	0x10366CC,	//	TESLoadScreen
	0x1028C5C,	//	TESLevSpell
	0x1028A64,	//	TESLevItem
	0x102886C,	//	TESLevCreature
	0x102864C,	//	TESLevCharacter
	0x102E6C4,	//	TESLandTexture
	0x1028444,	//	TESKey
	0x102D97C,	//	TESImageSpaceModifier
	0x102D7F4,	//	TESImageSpace
	0x1049B9C,	//	TESHair
	0x102814C,	//	TESGrass
	0x1026D0C,	//	TESFurniture
	0x10498DC,	//	TESFaction
	0x104973C,	//	TESEyes
	0x102685C,	//	TESEffectShader
	0x1048F5C,	//	TESCreature
	0x10266E4,	//	TESCombatStyle
	0x102D5C4,	//	TESClimate
	0x1048BB4,	//	TESClass
	0x104891C,	//	TESChallenge
	0x10263DC,	//	TESCasinoChips
	0x1026574,	//	TESCasino
	0x10349B4,	//	TESCaravanMoney
	0x1034B4C,	//	TESCaravanDeck
	0x103478C,	//	TESCaravanCard
	0x103449C,	//	TESAmmoEffect
	0x1026064,	//	TESAmmo
	0x1013F8C,	//	SpellItem
	0x1037094,	//	Script
	0x10342EC,	//	MediaSet
	0x10340C4,	//	MediaLocationController
	0x1012EA4,	//	EnchantmentItem
	0x1012834,	//	EffectSetting
	0x1033D1C,	//	BGSTextureSet
	0x1025914,	//	BGSTerminal
	0x1025594,	//	BGSTalkingActivator
	0x102535C,	//	BGSStaticCollection
	0x10116FC,	//	BGSSleepDeprevationStage
	0x10470EC,	//	BGSRagdoll
	0x10251AC,	//	BGSProjectile
	0x1024F4C,	//	BGSPlaceableWater
	0x1046EC4,	//	BGSPerk
	0x1046874,	//	BGSNote
	0x103397C,	//	BGSMusicType
	0x10337C4,	//	BGSMessage
	0x1033654,	//	BGSMenuIcon
	0x10334B4,	//	BGSListForm
	0x102CD94,	//	BGSLightingTemplate
	0x103323C,	//	BGSImpactDataSet
	0x1032F6C,	//	BGSImpactData
	0x104664C,	//	BGSIdleMarker
	0x10464B4,	//	BGSHeadPart
	0x1024A94,	//	BGSExplosion
	0x102CBBC,	//	BGSEncounterZone
	0x1024834,	//	BGSDebris
	0x10327F4,	//	BGSCameraShot
	0x103245C,	//	BGSCameraPath
	0x1045504,	//	BGSBodyPartData
	0x1024214,	//	BGSAddonNode
	0x10320FC,	//	BGSAcousticSpace
	0x1011964,	//	AlchemyItem
	0x1024CEC,  //  BGSMovableStatic
	0x1067A2C,  //  ActorValueInfo
};

//special for references, so it only uses persistent ones
const UInt32 TESObjectREFR_Vtables[] =
{
	0x102F55C,    //    TESObjectREFR
	0x1086A6C,    //    Character
	0x10870AC,    //    Creature
	0x108AA3C,    //    PlayerCharacter
	0x108F674,    //    GrenadeProjectile
};
