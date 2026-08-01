#include "BGSBodyPartData.hpp"

// GAME - 0x6A9540
BGSBodyPart* const* BGSBodyPartData::GetPartArray() const {
	return pBodyParts;
}

// GAME - 0x4FD380
BGSRagdoll* BGSBodyPartData::GetRagdollData() const {
	return pRagdollData;
}

// GAME - 0x5E50F0
BGSBodyPart* BGSBodyPartData::GetBodyPart(BODY_PART_TYPE aeLimb) const {
	return ThisCall<BGSBodyPart*>(0x5E50F0, this, aeLimb);
}

// GAME - 0x5E5130
BGSBodyPart* BGSBodyPartData::GetBodyPart(ActorValue::Index aeActorValue) const {
	return ThisCall<BGSBodyPart*>(0x5E5130, this, aeActorValue);
}

// GAME - 0x5E5220
void BGSBodyPartData::AddBodyPart(BGSBodyPart* apPart) {
	ThisCall(0x5E5220, this, apPart);
}

// GAME - 0x5E5320
void BGSBodyPartData::BuildIKPartList(BSSimpleList<BGSBodyPart*>* apOutList) const {
	ThisCall(0x5E5320, this, apOutList);
}

// GAME - 0x5E5750
void BGSBodyPartData::ShowChildLimbs(NiAVObject* apParentObject, NiAVObject* apRootObject, BODY_PART_TYPE aeParentLimb, NiAVObject* apObject) const {
	ThisCall(0x5E5750, this, apParentObject, apRootObject, aeParentLimb, apObject);
}

// GAME - 0x5E55E0
void BGSBodyPartData::HideChildLimbs(NiAVObject* apParentObject, NiAVObject* apRootObject, BODY_PART_TYPE aeParentLimb, NiAVObject* apObject) const {
	ThisCall(0x5E55E0, this, apParentObject, apRootObject, aeParentLimb, apObject);
}
