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
BGSBipedModelList* BGSBipedModelList::GetFormAsBipedModelList(TESForm* apForm) {
	return CdeclCall<BGSBipedModelList*>(0x475020, apForm);
}
