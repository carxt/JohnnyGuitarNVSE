#pragma once

#include "TESForm.hpp"
#include "IOTask.hpp"

class BGSTextureSet;
class TESGrass;
class QueuedFile;

class TESLandTexture : public TESForm {
public:
	TESLandTexture();
	~TESLandTexture();

	struct HavokData {
		uint8_t	ucMaterialType;
		uint8_t	ucFriction;
		uint8_t	ucRestitution;
	};

	BGSTextureSet*			pTextureSet;
	HavokData				kHavokData;
	uint8_t					ucSpecularExponent;
	BSSimpleList<TESGrass*>	kGrass;

	TESFORM_TYPE(TESLandTexture);
};

ASSERT_SIZE(TESLandTexture, 0x28);