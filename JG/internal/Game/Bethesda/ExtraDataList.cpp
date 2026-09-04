#include "ExtraDataList.hpp"

ExtraDataList* ExtraDataList::Create() {
#ifdef GAME
	return BSMemory::create<ExtraDataList, 0x410360>();
#else
	return BSMemory::create<ExtraDataList, 0x4AC340>();
#endif
}

// GAME - 0x411EC0
// GECK - 0x4B1CB0
void ExtraDataList::CopyList(ExtraDataList* apCopy) {
#ifdef GAME
	ThisCall(0x411EC0, this, apCopy);
#else
	ThisCall(0x4B1CB0, this, apCopy);
#endif
}

#ifdef GAME
// GAME - 0x4121E0
void ExtraDataList::CopyListForContainer(ExtraDataList* apCopy, bool abDontRemove) {
	ThisCall(0x4121E0, this, apCopy, abDontRemove);
}
#endif

// GAME - 0x412490
// GECK - 0x4B1D10
void ExtraDataList::CopyListForReference(ExtraDataList* apCopy, bool abRemove) {
#ifdef GAME
	ThisCall(0x412490, this, apCopy, abRemove);
#else
	ThisCall(0x4B1D10, this, apCopy, abRemove);
#endif
}

// GAME - 0x419D10
// GECK - 0x4AA130
void ExtraDataList::SetPoison(AlchemyItem* apPoison) {
#ifdef GAME
	ThisCall(0x419D10, this, apPoison);
#else
	ThisCall(0x4AA130, this, apPoison);
#endif
}

// GAME - 0x41AF30
void ExtraDataList::RemovePoison() {
#ifdef GAME
	ThisCall(0x41AF30, this);
#else
	RemoveExtra(EXTRA_DATA_TYPE::ExtraPoison);
#endif
}

// GAME - 0x421D20
// GECK - 0x4AB920
TESForm* ExtraDataList::GetEmittanceSource() const {
#ifdef GAME
	return ThisCall<TESForm*>(0x421D20, this);
#else
	return ThisCall<TESForm*>(0x4AB920, this);
#endif
}

// GAME - 0x421D50
// GECK - 0x4AB940
void ExtraDataList::SetEmittanceSource(TESForm* apSource) {
#ifdef GAME
	ThisCall(0x421D50, this, apSource);
#else
	ThisCall(0x4AB940, this, apSource);
#endif
}
