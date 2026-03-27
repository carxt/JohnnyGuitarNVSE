#pragma once

#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESDescription.hpp"
#include "ActorValue.hpp"

class TESSkill : public TESForm, public TESDescription, public TESTexture {
public:
	TESSkill();
	~TESSkill();

	struct Data {
		ActorValue::Index	eSkill;
		ActorValue::Index	eAttribute;
		uint32_t			eSpecialization;
		float				fActionValue[2];
	};

	Data			kData;
	TESDescription	kDescriptions[4];

	TESFORM_TYPE(TESSkill);
};

ASSERT_SIZE(TESSkill, 0x60);