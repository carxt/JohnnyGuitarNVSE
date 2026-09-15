#pragma once

#include "BSSimpleList.hpp"
#include "TESParameters.hpp"
#include "BSEnums.hpp"

class TESConditionItem;
class TESObjectREFR;
class TESForm;

class TESCondition {
public:
	BSSimpleList<TESConditionItem*> kHead;
#ifdef EDITOR
	uint8_t							unk08;
#endif

	const BSSimpleList<TESConditionItem*>* GetHead() const {
		return &kHead;
	}
	BSSimpleList<TESConditionItem*>* GetHead() {
		return &kHead;
	}

#ifdef GAME
	bool IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const;
#endif

#ifdef EDITOR
	void RegisterForm(TESForm* apForm);
#endif

	static const char* GetComparisonConditionSymbol(CONDITION_COMPARISON aeComparison);

private:
#ifdef GAME
	static constexpr AddressPtr<const char*, 0x119C020, 6> pComparisonConditionSymbols;
#else
	static constexpr AddressPtr<const char*, 0xE918B8, 6> pComparisonConditionSymbols;
#endif
};

#ifdef GAME
ASSERT_SIZE(TESCondition, 0x8);
#else
ASSERT_SIZE(TESCondition, 0xC);
#endif

class TESObjectREFR;
class TESGlobal;

struct ConditionItemData {
	union Comparison {
		float		fValue;
		TESGlobal*  pGlobal;
	};

	struct ALIGN1 _ConditionItemDataFlags {
		enum Flags : uint8_t {
			OR						= 1u << 0,
			RUN_ON_TARGET			= 1u << 1,
			USE_GLOBAL				= 1u << 2,
			RUN_ON_REFERENCE		= 1u << 3,

			COMPARISON_CONDITION_POS	= 5,
			COMPARISON_CONDITION_MASK	= 0xE0,
		};

		bool	bOr						: 1;
		bool	bRunOnTarget			: 1;
		bool	bUseGlobal				: 1;
		bool	bRunOnReference			: 1;
		bool							: 1;
		uint8_t	eComparisonCondition	: 3;
	};
	using ConditionItemDataFlags = _ConditionItemDataFlags::Flags;

	Bitfield<_ConditionItemDataFlags>	ucType;
	Comparison							uComparisonValue;
	FunctionData						kFunctionData;
	uint32_t							eRunOn;
	TESObjectREFR*						pReference;
};

ASSERT_SIZE(ConditionItemData, 0x1C);

class TESConditionItem {
public:
	ConditionItemData	kData;
	TESConditionItem*	pNext;

	CONDITION_RUN_ON GetRunOn() const;

	uint32_t GetConditionFunction() const;
	void SetConditionFunction(uint16_t ausFunction);

	CONDITION_COMPARISON GetComparisonCondition() const;
	void SetComparisonCondition(CONDITION_COMPARISON aeComparison);
	
	float GetComparisonValue() const;
	void SetComparisonValueFloat(float afValue);

	bool GetOr() const;
	bool GetValueIsGlobal() const;
};

ASSERT_SIZE(TESConditionItem, 0x20);