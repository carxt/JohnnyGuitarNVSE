#pragma once

#include "TESForm.hpp"

class BGSTextureSet;
class TESGrass;

class TESLandTexture : public TESForm {
public:
	TESLandTexture();
	~TESLandTexture();

	struct HavokData {
		uint8_t	eMaterialType;
		uint8_t	ucFriction;
		uint8_t	ucRestitution;
	};

	BGSTextureSet*			pTextureSet;
	HavokData				kHavokData;
	uint8_t					ucSpecularExponent;
	BSSimpleList<TESGrass*>	kGrass;
#ifdef EDITOR
	BSSimpleList<void*>		unk3C;
	uint32_t				uiRefCount;
#endif

	TESFORM_TYPE(TESLandTexture);

	BGSTextureSet* GetTextureSet() const;
	void SetTextureSet(BGSTextureSet* apTextureSet);

	HK_MATERIAL_TYPE GetHavokMaterialType() const;
	void SetHavokMaterialType(HK_MATERIAL_TYPE aeType);

	float GetHavokFrictionValue() const;
	void SetHavokFrictionValue(float afFriction);

	float GetHavokRestitutionValue() const;
	void SetHavokRestitutionValue(float afRestitution);

	uint8_t GetSpecularExponent() const;
	void SetSpecularExponent(uint8_t aucVal);

	const BSSimpleList<TESGrass*>* GetGrassList() const;
	BSSimpleList<TESGrass*>* GetGrassList();

	void AddGrass(TESGrass* apGrass);
	void RemoveGrass(TESGrass* apGrass);
};

#ifdef GAME
ASSERT_SIZE(TESLandTexture, 0x28);
#else
ASSERT_SIZE(TESLandTexture, 0x48);
#endif