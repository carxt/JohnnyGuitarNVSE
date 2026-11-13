#include "BGSBodyPartData.hpp"
#ifdef EDITOR
#include "BGSBodyPart.hpp"
#endif

#ifdef GAME
// GAME - 0x6A9540
BGSBodyPart* const* BGSBodyPartData::GetBodyParts() const {
	return pBodyParts;
}
#else
// GECK - 0x546260
const BSSimpleList<BGSBodyPart*>* BGSBodyPartData::GetBodyParts() const {
	return &kBodyParts;
}

// GECK - 0x546260
BSSimpleList<BGSBodyPart*>* BGSBodyPartData::GetBodyParts() {
	return &kBodyParts;
}
#endif

// GAME - 0x4FD380
BGSRagdoll* BGSBodyPartData::GetRagdollData() const {
	return pRagdollData;
}

// GAME - 0x5E50F0
BGSBodyPart* BGSBodyPartData::GetBodyPart(BODY_PART_TYPE aeLimb) const {
#ifdef GAME
	return ThisCall<BGSBodyPart*>(0x5E50F0, this, aeLimb);
#else
	for (auto pIter = GetBodyParts(); pIter && !pIter->IsEmpty(); pIter = pIter->GetNext()) {
		BGSBodyPart* pPart = pIter->GetItem();
		if (pPart->GetPartType() == aeLimb)
			return pPart;
	}
	return nullptr;
#endif
}

// GAME - 0x5E5130
BGSBodyPart* BGSBodyPartData::GetBodyPart(ActorValue::Index aeActorValue) const {
#ifdef GAME
	return ThisCall<BGSBodyPart*>(0x5E5130, this, aeActorValue);
#else
	for (auto pIter = GetBodyParts(); pIter && !pIter->IsEmpty(); pIter = pIter->GetNext()) {
		BGSBodyPart* pPart = pIter->GetItem();
		if (pPart->GetActorValue() == aeActorValue)
			return pPart;
	}
	return nullptr;
#endif
}

// GAME - 0x5E5220
void BGSBodyPartData::AddBodyPart(BGSBodyPart* apPart) {
#ifdef GAME
	ThisCall(0x5E5220, this, apPart);
#else
	if (apPart && apPart->GetPartType() < BODY_PART_TYPE::COUNT)
		kBodyParts.AddTail(apPart);
#endif
}

#ifdef GAME
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
#endif