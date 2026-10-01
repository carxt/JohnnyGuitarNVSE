#include "BGSBipedModelList.hpp"

// GAME - 0x726070
BGSListForm* BGSBipedModelList::GetBipedModelList() const {
	return pModelList;
}

// GAME - 0x6ECD40
void BGSBipedModelList::SetBipedModelList(BGSListForm* apModelList) {
	pModelList = apModelList;
}

// GAME - 0x475020
// GECK - 0x4E34D0
BGSBipedModelList* BGSBipedModelList::GetFormAsBipedModelList(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<BGSBipedModelList*>(0x475020, apForm);
#else
	return CdeclCall<BGSBipedModelList*>(0x4E34D0, apForm);
#endif
}
