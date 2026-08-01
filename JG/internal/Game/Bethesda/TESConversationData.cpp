#include "TESConversationData.hpp"

// GAME - 0x6815C0
const BSSimpleList<TESTopic*>* TESConversationData::GetLinkFrom() const {
    return &kLinkFrom;
}

// GAME - 0x6815C0
BSSimpleList<TESTopic*>* TESConversationData::GetLinkFrom() {
	return &kLinkFrom;
}

// GAME - 0x413F40
const BSSimpleList<TESTopic*>* TESConversationData::GetLinkTo() const {
	return &kLinkTo;
}

// GAME - 0x413F40
BSSimpleList<TESTopic*>* TESConversationData::GetLinkTo() {
	return &kLinkTo;
}

// GAME - 0x460140
const BSSimpleList<TESTopic*>* TESConversationData::GetFollowUp() const {
	return &kFollowUp;
}

// GAME - 0x460140
BSSimpleList<TESTopic*>* TESConversationData::GetFollowUp() {
	return &kFollowUp;
}

// GAME - 0x61C330
void TESConversationData::ClearLists() {
	ThisCall(0x61C330, this);
}
