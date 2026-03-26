#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"

class TESAmmoEffect : public TESForm, public TESFullName {
public:
	TESAmmoEffect();
	~TESAmmoEffect();

	struct Data {
		uint32_t	eType;
		uint32_t	eOperation;
		float		fValue;
	};

	Data kData;

	TESFORM_TYPE(TESAmmoEffect);

	AMMO_OPERATION_TYPE GetOperation() const;
	void SetOperation(AMMO_OPERATION_TYPE aeOperation);

	AMMO_EFFECT_TYPE GetEffectType() const;
	void SetEffectType(AMMO_EFFECT_TYPE aeType);

	float GetEffectValue() const;
	void SetEffectValue(float afValue);
};

ASSERT_SIZE(TESAmmoEffect, 0x30);