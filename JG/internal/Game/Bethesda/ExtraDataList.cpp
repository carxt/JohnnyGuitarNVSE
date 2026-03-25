#include "ExtraDataList.hpp"

ExtraDataList* ExtraDataList::Create() {
	return BSMemory::create<ExtraDataList, 0x410360>();
}

// GAME - 0x411EC0
void ExtraDataList::CopyList(ExtraDataList* apCopy) {
	ThisCall(0x411EC0, this, apCopy);
}

// GAME - 0x4121E0
void ExtraDataList::CopyListForContainer(ExtraDataList* apCopy, bool abDontRemove) {
	ThisCall(0x4121E0, this, apCopy, abDontRemove);
}

// GAME - 0x412490
void ExtraDataList::CopyListForReference(ExtraDataList* apCopy, bool abRemove) {
	ThisCall(0x412490, this, apCopy, abRemove);
}