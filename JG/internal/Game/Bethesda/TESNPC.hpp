#pragma once

#include "TESActorBase.hpp"
#include "TESRaceForm.hpp"
#include "Gamebryo/NiTPrimitiveArray.hpp"
#include "Gamebryo/NiTexture.hpp"
#include "FaceGen/FR2MatrixVTC.hpp"

class TESNPC;
class NiObject;
class BSFaceGenNiNode;
class TESClass;
class BGSHeadPart;
class FaceGenUndo;
class BipedAnim;
class TESHair;
class TESEyes;

class TESNPC : public TESActorBase, public TESRaceForm {
public:
	TESNPC();
	~TESNPC();

	struct Data {
		uint8_t	ucSkillValues[14];
		uint8_t	ucSkillOffsets[14];
	};

	Data							kData;
	TESClass*						pClass;
	FR2MatrixVTC<float>				kRaceFaceOffsetCoord[2][2];
	FR2MatrixVTC<float>			  (*pAlternateFaceOffsetCoord)[2][2];
	TESHair*						pHair;
	float							fHairLength;
	TESEyes*						pEyes;
	NiPointer<BSFaceGenNiNode>		spHeadBiped;
	NiPointer<BSFaceGenNiNode>		spHeadSkinned;
	NiPointer<NiTexture>			spBodyModTexture;
	uint16_t						usLastRaceFaceNum;
	TESCombatStyle*					pCombatStyle;
	uint32_t						uiHairColor;
	BSSimpleList<BGSHeadPart*>		kHeadParts;
	uint32_t						eImpactMaterialType;
	uint32_t						uiFileOffset;
	TESRace*						pOriginalRace;
	TESNPC*							pFaceNPC;
	float							fHeight;
	float							fWeight;
	NiTPrimitiveArray<FaceGenUndo*>	kFaceGenUndos;

	TESFORM_TYPE(TESNPC);

	TESClass* GetClass() const;
	void SetClass(TESNPC* apClass);

	TESHair* GetHair() const;
	void SetHair(TESHair* apHair);

	TESCombatStyle* GetCombatStyle() const;
	
	TESRace* GetRace() const;

	float GetHeight() const;
	float GetRaceHeight() const;

	float GetWeight() const;

	void GetFaceCoord(FR2MatrixVTC<float> (&arCoords)[2][2]) const;
};

ASSERT_SIZE(TESNPC, 0x20C);