#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"

class TESAmmoEffect : public TESForm, public TESFullName {
public:
	TESAmmoEffect();
	~TESAmmoEffect();

	struct Data {
		AMMO_EFFECT_TYPE	eType;
		AMMO_OPERATION_TYPE	eOperation;
		float				fValue;
	};

	Data kData;

	TESFORM_TYPE(TESAmmoEffect);

	AMMO_OPERATION_TYPE GetOperation() const;
	void SetOperation(AMMO_OPERATION_TYPE aeOperation);

	AMMO_EFFECT_TYPE GetEffectType() const;
	void SetEffectType(AMMO_EFFECT_TYPE aeType);

	float GetEffectValue() const;
	void SetEffectValue(float afValue);

#ifdef GAME
	void BuildMenuString(char* apBuffer, uint32_t auiBufferSize) const;

	static float ApplyAmmoEffect(AMMO_EFFECT_TYPE aeType, BSSimpleList<TESAmmoEffect*>* apEffects, float afDamage);
#endif
};

#ifdef GAME
ASSERT_SIZE(TESAmmoEffect, 0x30);
#else
ASSERT_SIZE(TESAmmoEffect, 0x44);
#endif