#include "BGSIdleCollection.hpp"

// GAME - 0x479E80
BGSIdleCollection::PickType BGSIdleCollection::GetPickType() const {
	return ucIdleFlags.ePickType;
}

void BGSIdleCollection::SetPickType(PickType aeType) {
	ucIdleFlags.ePickType = aeType;
}

// GAME - 0x929D20
bool BGSIdleCollection::GetDoOnce() const {
	return ucIdleFlags.bDoOnce;
}

void BGSIdleCollection::SetDoOnce(bool abVal) {
	ucIdleFlags.bDoOnce = abVal;
}

// GAME - 0x92B440
uint32_t BGSIdleCollection::GetIdleCount() const {
	return ucIdleCount;
}

// GAME - 0x47A030
uint32_t BGSIdleCollection::GetIdlesForActor(Actor* apActor, TESObjectREFR* apTargetRef, BSSimpleArray<TESIdleForm*>* apOutIdleArray) const {
	return ThisCall<uint32_t>(0x47A030, this, apActor, apTargetRef, apOutIdleArray);
}

// GAME - 0x479FB0
bool BGSIdleCollection::HasIdleForActor(Actor* apActor, TESObjectREFR* apTargetRef) const {
	return ThisCall<bool>(0x479FB0, this, apActor, apTargetRef);
}
