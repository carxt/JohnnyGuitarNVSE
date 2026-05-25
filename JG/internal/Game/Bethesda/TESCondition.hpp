#pragma once

#include "BSSimpleList.hpp"

class TESConditionItem;
class TESObjectREFR;

class TESCondition {
public:
	BSSimpleList<TESConditionItem*> kHead;

	const BSSimpleList<TESConditionItem*>* GetHead() const {
		return &kHead;
	}

	BSSimpleList<TESConditionItem*>* GetHead() {
		return &kHead;
	}

	bool IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const;

	bool IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, bool& abDipositionFailure, bool abEssentialPropertiesOnly) const;
};

ASSERT_SIZE(TESCondition, 0x8);

class TESObjectREFR;
class TESGlobal;

struct FunctionData {
	union Parameter {
		float		fValue;
		uint32_t	uiNumber;
		void*		pPointer;
	};

	uint16_t	usFunction;
	Parameter	uParam[2];
};

ASSERT_SIZE(FunctionData, 0xC);

enum class CONDITION_RUN_ON : uint32_t {
	SUBJECT,
	TARGET,
	REFERENCE,
	COMBAT_TARGET,
	LINKED_REFERENCE,
};

enum class CONDITION_COMPARISON : uint32_t {
	EQUAL,
	NOT_EQUAL,
	GREATER_THAN,
	GREATER_THAN_OR_EQUAL,
	LESS_THAN,
	LESS_THAN_OR_EQUAL
};

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
		};

		bool bOr					: 1;
		bool bRunOnTarget			: 1;
		bool bUseGlobal				: 1;
		bool bRunOnReference		: 1;
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

	bool IsTrue(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, bool& abDipositionFailure) const;

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