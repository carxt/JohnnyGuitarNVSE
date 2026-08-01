#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"
#include "BGSPreloadable.hpp"
#include "ActorValue.hpp"

class BGSBodyPart;
class BGSRagdoll;
class NiAVObject;

class BGSBodyPartData : public TESForm, public TESModel, public BGSPreloadable {
public:
	BGSBodyPartData();
	~BGSBodyPartData();

	BGSBodyPart*	pBodyParts[BODY_PART_TYPE::COUNT];
	BGSRagdoll*		pRagdollData;

	TESFORM_TYPE(BGSBodyPartData);

	BGSBodyPart* const* GetPartArray() const;

	BGSRagdoll* GetRagdollData() const;

	BGSBodyPart* GetBodyPart(BODY_PART_TYPE aeLimb) const;
	BGSBodyPart* GetBodyPart(ActorValue::Index aeActorValue) const;
	void AddBodyPart(BGSBodyPart* apPart);

	void BuildIKPartList(BSSimpleList<BGSBodyPart*>* apOutList) const;

	void ShowChildLimbs(NiAVObject* apParentObject, NiAVObject* apRootObject, BODY_PART_TYPE aeParentLimb, NiAVObject* apObject) const;
	void HideChildLimbs(NiAVObject* apParentObject, NiAVObject* apRootObject, BODY_PART_TYPE aeParentLimb, NiAVObject* apObject) const;
};

ASSERT_SIZE(BGSBodyPartData, 0x74);