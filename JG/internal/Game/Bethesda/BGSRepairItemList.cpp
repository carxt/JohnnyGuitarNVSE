#include "BGSRepairItemList.hpp"

// GAME - 0x726070
BGSListForm* BGSRepairItemList::GetRepairItemList() const {
	return pRepairList;
}

// GAME - 0x6ECD40
void BGSRepairItemList::SetRepairItemList(BGSListForm* apRepairList) {
	pRepairList = apRepairList;
}

#ifdef GAME
// GAME - 0x47BA80
bool BGSRepairItemList::HasRepairItem(const TESForm* apForm) const {
	return ThisCall<bool>(0x47BA80, apForm);
}

// GAME - 0x47BAC0
BGSRepairItemList* BGSRepairItemList::GetFormAsRepairItemList(const TESForm* apForm) {
	return CdeclCall<BGSRepairItemList*>(0x47BAC0, apForm);
}

// GAME - 0x47BB50
bool BGSRepairItemList::CanItemRepairForm(const TESForm* apRepairItem, const TESForm* apForm) {
	return CdeclCall<bool>(0x47BB50, apRepairItem, apForm);
}
#endif