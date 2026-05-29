#pragma once

#include "TESCondition.hpp"
#include "MagicSystem.hpp"
#include "ActorValue.hpp"
#include "BSStringT.hpp"

class Actor;
class EffectSetting;

struct EffectItemData {
	int32_t				iMagnitude;
	int32_t				iArea;
	int32_t				iDuration;
	MagicSystem::Range	eRange;
	ActorValue::Index	eActorValue;
};

class EffectItem {
public:
	EffectItem();
	~EffectItem();

	EffectItemData	kData;
	EffectSetting*	pEffectSetting;
	float			fRawCost;
	TESCondition	kConditions;

	int32_t GetMagnitude() const;
	bool SetMagnitude(int32_t aiMagnitude);
	
	int32_t GetArea() const;
	bool SetArea(int32_t aiArea);

	int32_t GetDuration() const;
	bool SetDuration(int32_t aiDuration);

	MagicSystem::Range GetRange() const;
	bool SetRange(MagicSystem::Range aeRange);

	ActorValue::Index GetActorValueIndex() const;
	void SetActorValueIndex(ActorValue::Index aeIndex);

	EffectSetting* GetEffectSetting() const;

	float GetCost();
	float GetRawCost();

	const TESCondition* GetConditions() const;
	TESCondition* GetConditions();

	ActorValue::Index GetAssociatedSkill() const;

	BSString GetEffectName() const;
};

ASSERT_SIZE(EffectItem, 0x24);