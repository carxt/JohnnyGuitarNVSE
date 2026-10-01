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

#ifdef GAME
	BGSBodyPart*				pBodyParts[BODY_PART_TYPE::COUNT];
#else
	BSSimpleList<BGSBodyPart*>	kBodyParts;
#endif
	BGSRagdoll*					pRagdollData;

	TESFORM_TYPE(BGSBodyPartData);

#ifdef GAME
	BGSBodyPart* const* GetBodyParts() const;
#else
	const BSSimpleList<BGSBodyPart*>* GetBodyParts() const;
	BSSimpleList<BGSBodyPart*>* GetBodyParts();
#endif

	BGSRagdoll* GetRagdollData() const;

	BGSBodyPart* GetBodyPart(BODY_PART_TYPE aeLimb) const;
	BGSBodyPart* GetBodyPart(ActorValue::Index aeActorValue) const;
	void AddBodyPart(BGSBodyPart* apPart);

#ifdef GAME
	void BuildIKPartList(BSSimpleList<BGSBodyPart*>* apOutList) const;

	void ShowChildLimbs(NiAVObject* apParentObject, NiAVObject* apRootObject, BODY_PART_TYPE aeParentLimb, NiAVObject* apObject) const;
	void HideChildLimbs(NiAVObject* apParentObject, NiAVObject* apRootObject, BODY_PART_TYPE aeParentLimb, NiAVObject* apObject) const;
#endif
};

#ifdef GAME
ASSERT_SIZE(BGSBodyPartData, 0x74);
#else
ASSERT_SIZE(BGSBodyPartData, 0x60);
#endif