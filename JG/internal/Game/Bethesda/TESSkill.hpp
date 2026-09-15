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
		ActorValue::Index		eSkill;
		ActorValue::Index		eAttribute;
		SKILL_SPECIALIZATION	eSpecialization;
		float					fActionValue[2];
	};

	Data			kData;
	TESDescription	kDescriptions[4];

	TESFORM_TYPE(TESSkill);
};

#ifdef GAME
ASSERT_SIZE(TESSkill, 0x60);
#else
ASSERT_SIZE(TESSkill, 0xAC);
#endif