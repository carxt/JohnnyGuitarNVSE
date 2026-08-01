#pragma once

#include "Gamebryo/NiTPrimitiveArray.hpp"
#include "BGSTextureModel.hpp"
#include "FaceGen/FR2MatrixVTC.hpp"
#include "BSSimpleArray.hpp"
#include "TESAttributes.hpp"
#include "TESDescription.hpp"
#include "TESEyes.hpp"
#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESHair.hpp"
#include "TESModel.hpp"
#include "TESReactionForm.hpp"
#include "TESSpellList.hpp"
#include "TESTexture.hpp"

class TESNPC;
class BGSVoiceType;
class FaceGenUndo;

class TESRace : public TESForm, public TESFullName, public TESDescription, public TESSpellList, public TESReactionForm {
public:
	TESRace();
	~TESRace();

	struct _HeadPart {
		enum Part {
			HEAD			= 0,
			EAR				= 1,
			MOUTH			= 2,
			TEETH_LOWER		= 3,
			TEETH_UPPER		= 4,
			TONGUE			= 5,
			EYE_LEFT		= 6,
			EYE_RIGHT		= 7,
			COUNT,
			HAIR			= 9,
		};
	};
	using HeadPart = _HeadPart::Part;
	
	struct _BodyPart {
		enum Part {
			UPPER_BODY	= 0,
			LEFT_HAND	= 1,
			RIGHT_HAND	= 2,
			COUNT,
		};
	};
	using BodyPart = _BodyPart::Part;

	struct ALIGN4 _RaceFlags {
		enum Flags : uint32_t {
			PLAYABLE	= 1u << 0,
			CHILD		= 1u << 2,
		};

		bool bPlayable	: 1;
		bool 			: 1;
		bool bChild		: 1;
	};
	using RaceFlags = _RaceFlags::Flags;

	struct SkillBonus {
		int8_t	cActorValue;
		int8_t	cMod;
	};

	struct Data {
		SkillBonus				kSkillBonus[7];
		float					fHeight[SEX::COUNT];
		float					fWeight[SEX::COUNT];
		Bitfield<_RaceFlags>	uiFlags;
	};

	Data							kData;
	TESAttributes					kAttributes[SEX::COUNT];	
	BSSimpleList<TESHair*>			kHairList;				
	TESHair*						pDefaultHair[SEX::COUNT];
	uint8_t							ucDefaultHairColor[SEX::COUNT];
	float							fClampFaceGeoValues[2];
	BSSimpleList<TESEyes*>			kEyes;
	TESModel						kHeadModels[SEX::COUNT][HeadPart::COUNT];
	TESTexture						kHeadTextures[SEX::COUNT][HeadPart::COUNT];
	TESTexture						kBodyPartsTextures[SEX::COUNT][BodyPart::COUNT];
	TESModel						kBodyModels[SEX::COUNT][BodyPart::COUNT];
	BGSTextureModel					kBodyTexture[SEX::COUNT];
	FaceGenCoords					kMeanFaceCoordFemale;
	FaceGenCoords					kMeanFaceCoordMale;
	uint16_t						usFaceCoordNum;
	BGSVoiceType*					pDefaultVoiceType[SEX::COUNT];
	TESRace*						pOldRace;
	TESRace*						pYoungRace;
	BSString						strEditorID;
	NiTPrimitiveArray<FaceGenUndo*>	kFaceGenUndos;

	TESFORM_TYPE(TESRace);

	const SkillBonus* GetSkillBonus(uint32_t auiIndex) const;
	SkillBonus* GetSkillBonus(uint32_t auiIndex);

	float GetHeight(SEX aeSex) const;
	void SetHeight(SEX aeSex, float afVal);

	float GetWeight(SEX aeSex) const;
	void SetWeight(SEX aeSex, float afVal);

	bool GetPlayable() const;
	void SetPlayable(bool abVal);

	bool GetChildRace() const;
	void SetChildRace(bool abVal);

	const TESAttributes* GetMaleAttributes() const;
	TESAttributes* GetMaleAttributes();

	const TESAttributes* GetFemaleAttributes() const;
	TESAttributes* GetFemaleAttributes();

	const BSSimpleList<TESHair*>* GetHairList() const;
	BSSimpleList<TESHair*>* GetHairList();
	void ClearHairList();

	TESHair* GetRaceHair(uint32_t auiFormID) const;
	void AddHair(TESHair* apHair);

	TESHair* GetDefaultHair(SEX aeSex) const;
	void SetDefaultHair(SEX aeSex, TESHair* apHair);

	uint8_t GetDefaultHairColor(SEX aeSex) const;
	void SetDefaultHairColor(SEX aeSex, uint8_t aucColor);

	float GetClampFaceGeoValue() const;
	void SetClampFaceGeoValue(float afVal);

	float GetClampFaceGeoValue2() const;
	void SetClampFaceGeoValue2(float afVal);

	const BSSimpleList<TESEyes*>* GetEyeColorList() const;
	BSSimpleList<TESEyes*>* GetEyeColorList();
	void ClearEyeColorList();

	TESEyes* GetRaceEyeColor(uint32_t auiFormID) const;
	void AddEyeColor(TESEyes* apHair);

	TESModel* GetHeadPartModel(SEX aeSex, HeadPart aePart) const;
	void SetHeadPartModel(SEX aeSex, HeadPart aePart, const char* apPath);
	
	TESTexture* GetHeadPartTexture(SEX aeSex, HeadPart aePart) const;
	void SetHeadPartTexture(SEX aeSex, HeadPart aePart, const char* apPath);

	TESTexture* GetBodyPartTexture(SEX aeSex, BodyPart aePart) const;
	void SetBodyPartTexture(SEX aeSex, BodyPart aePart, const char* apPath);

	TESModel* GetBodyPartModel(SEX aeSex, BodyPart aePart) const;
	void GetBodyPartModel(SEX aeSex, BodyPart aePart, const char* apPath);

	BGSTextureModel* GetBodyTextureModel(SEX aeSex) const;
	void SetBodyTextureModel(SEX aeSex, const char* apPath);

	const FaceGenCoords* GetMeanFaceCoord(SEX aeSex) const;
	FaceGenCoords* GetMeanFaceCoord(SEX aeSex);

	BGSVoiceType* GetDefaultVoiceType(SEX aeSex) const;
	void SetDefaultVoiceType(SEX aeSex, BGSVoiceType* apVoice);

	TESRace* GetOlderRace() const;
	TESRace* GetYoungerRace() const;
};

ASSERT_SIZE(TESRace, 0x524);