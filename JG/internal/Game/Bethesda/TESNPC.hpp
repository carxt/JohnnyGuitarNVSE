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
	FaceGenCoords					kRaceFaceOffsetCoord;
	FaceGenCoords*					pAlternateFaceOffsetCoord;
	TESHair*						pHair;
	float							fHairLength;
	TESEyes*						pEyeColor;
	NiPointer<BSFaceGenNiNode>		spHeadBiped;
	NiPointer<BSFaceGenNiNode>		spHeadSkinned;
	NiPointer<NiTexture>			spBodyModTexture;
	uint16_t						usLastRaceFaceNum;
	TESCombatStyle*					pCombatStyle;
	uint32_t						uiHairColor;
	BSSimpleList<BGSHeadPart*>		kHeadParts;
	IMPACT_MATERIAL_TYPE			eBloodImpactMaterial;
#ifdef GAME
	uint32_t						uiFileOffset;
	TESRace*						pOriginalRace;
	TESNPC*							pFaceNPC;
#endif
	float							fHeight;
	float							fWeight;
	NiTPrimitiveArray<FaceGenUndo*>	kFaceGenUndos;

	TESFORM_TYPE(TESNPC);

	TESClass* GetClass() const;
	void SetClass(TESClass* apClass);

	FaceGenCoords* GetAlternateOffsetFaceCoord() const;
	void SetAlternateOffsetFaceCoord(FaceGenCoords* apCoords);

	TESHair* GetHair() const;
	void SetHair(TESHair* apHair);

	float GetHairLength() const;

	TESEyes* GetEyeColor() const;
	void SetEyeColor(TESEyes* apEyes);

	TESCombatStyle* GetCombatStyle() const;
	
	TESRace* GetRace() const;

	uint32_t GetHairColor() const;
	void SetHairColor(uint32_t auiColor);

	const BSSimpleList<BGSHeadPart*>* GetHeadPartList() const;
	BSSimpleList<BGSHeadPart*>* GetHeadPartList();

	float GetHeight() const;
	float GetRaceHeight() const;
	void SetHeight(float afHeight);

	float GetWeight() const;
	void SetWeight(float afWeight);

	void GetFaceCoord(FaceGenCoords &arCoords) const;

	FaceGenCoords* GetOffsetFaceCoord();

	void CopyHeadData(TESNPC* apSource);

#ifdef GAME
	void SwitchRace(TESRace* apRace, Actor* apActor);
#endif

	void ReplaceRefModel(TESObjectREFR* apRef);

	uint32_t GetFormHealthLeveled(bool abAddBase);
};

#ifdef GAME
ASSERT_SIZE(TESNPC, 0x20C);
#else
ASSERT_SIZE(TESNPC, 0x234);
#endif