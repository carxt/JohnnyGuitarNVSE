#pragma once

#include "BSSimpleList.hpp"
#include "FastModifierCollection.hpp"
#include "Modifier.hpp"

struct ModifierList : public BSSimpleList<Modifier*> {
public:
	ModifierList();
	~ModifierList();

	struct _ClampStyle {
		enum Style : uint32_t {
			CLAMP_ABOVE_ZERO = 0, // > 0 to 0
			CLAMP_BELOW_ZERO = 1, // < 0 to 0
			CLAMP_NONE		 = 2,
		};
	};
	using ClampStyle = _ClampStyle::Style;

	bool					bAllowEmpty;
	FastModifierCollection* pFastModifiers;

	Modifier* GetModifierItem(int8_t acActorValue) const;
	float GetModifier(int8_t acActorValue, bool& abFound) const;
	float GetModifier(int8_t acActorValue) const;

	void SetModifier(int8_t acActorValue, float afValue);
	void AdjustModifier(int8_t acActorValue, float afValue, ClampStyle aeClamp);

	void AddModifier(Modifier* apModifier);
	void AddFastModifier(int8_t acActorValue, Modifier* apModifier);

	void DeleteModifier(Modifier* apModifier);
	void DeleteAllModifiers();

	static float ModifyAndClamp(float afValue, float afDelta, ClampStyle aeClamp);
};

ASSERT_SIZE(ModifierList, 0x10);