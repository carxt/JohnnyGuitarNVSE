#pragma once

#include "BSSimpleList.hpp"
#include "FastModifierCollection.hpp"
#include "Modifier.hpp"

struct ModifierList : public BSSimpleList<Modifier*> {
public:
	ModifierList();
	~ModifierList();

	enum ClampStyle : uint32_t {
		CLAMP_ABOVE_ZERO = 0, // Clamps values > 0 to 0
		CLAMP_BELOW_ZERO = 1, // Clamps values < 0 to 0
		CLAMP_NONE		 = 2, // No clamping
	};

	bool					bAllowEmpty;
	FastModifierCollection* pFastModifiers;

	Modifier* GetModifierItem(uint8_t aucActorValue) const;
	float GetModifier(uint8_t aucActorValue, bool& abFound) const;
	float GetModifier(uint8_t aucActorValue) const;

	void SetModifier(uint8_t aucActorValue, float afValue);
	void AdjustModifier(uint8_t aucActorValue, float afValue, ClampStyle aeClamp);

	void AddModifier(Modifier* apModifier);
	void AddFastModifier(uint8_t aucActorValue, Modifier* apModifier);

	void DeleteModifier(Modifier* apModifier);
	void DeleteAllModifiers();

	static float ModifyAndClamp(float afValue, float afDelta, ClampStyle aeClamp);
};

ASSERT_SIZE(ModifierList, 0x10);