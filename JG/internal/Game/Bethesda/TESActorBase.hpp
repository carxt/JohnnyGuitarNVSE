#pragma once

#include "ActorValueOwner.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSTouchSpellForm.hpp"
#include "TESActorBaseData.hpp"
#include "TESAIForm.hpp"
#include "TESAnimation.hpp"
#include "TESAttributes.hpp"
#include "TESBoundAnimObject.hpp"
#include "TESContainer.hpp"
#include "TESFullName.hpp"
#include "TESHealthForm.hpp"
#include "TESModel.hpp"
#include "TESScriptableForm.hpp"
#include "TESSpellList.hpp"

class BGSBodyPartData;
class TESCombatStyle;

class TESActorBase : public TESBoundAnimObject, public TESActorBaseData, public TESContainer,
	public BGSTouchSpellForm, public TESSpellList, public TESAIForm, public TESHealthForm, public TESAttributes,
	public TESAnimation, public TESFullName, public TESModel, public TESScriptableForm, public ActorValueOwner, public BGSDestructibleObjectForm {
public:
	TESActorBase();
	~TESActorBase();

	virtual BGSBodyPartData*	GetBodyPartData() const;
	virtual void				SetBodyPartData(BGSBodyPartData* apData);
	virtual TESCombatStyle*		GetCombatStyle() const;
	virtual void				SetCombatStyle(TESCombatStyle* apCombatStyle);
	virtual void				SetActorValueF(ActorValue::Index aeIndex, float afValue);
	virtual void				SetActorValueI(ActorValue::Index aeIndex, int32_t aiValue);
	virtual void				ModActorValueF(ActorValue::Index aeIndex, float afValue);
	virtual void				ModActorValueI(ActorValue::Index aeIndex, int32_t aiValue);

	SEX GetSex() const;
};

ASSERT_SIZE(TESActorBase, 0x10C);