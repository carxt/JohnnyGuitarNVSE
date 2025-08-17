#include "Conversation.hpp"

// GAME - 0x83B830
Conversation::Conversation() {
	pCurrentItem = nullptr;
}

// GAME - 0x83B8D0
Conversation::~Conversation() {
	ClearList();
}

// GAME - 0x83B9A0
bool Conversation::FirstItem() {
	pCurrentItem = kDialogueItems.GetHead();
	return pCurrentItem && pCurrentItem->GetItem() != nullptr;
}

// GAME - 0x83C7E0
bool Conversation::NextItem() {
	if (pCurrentItem)
		pCurrentItem = pCurrentItem->GetNext();

	return pCurrentItem != nullptr;
}

// GAME = 0x83C820
DialogueItem* Conversation::GetCurrentItem() const {
	if (pCurrentItem)
		return pCurrentItem->GetItem();
	return nullptr;
}

// GAME - 0x83B9F0
bool Conversation::GetNext() {
	if (pCurrentItem)
		pCurrentItem = pCurrentItem->GetNext();
	return pCurrentItem && pCurrentItem->GetItem();
}

// GAME - 0x83BAC0
DialogueItem* Conversation::GetDialogueItemByIndex(uint16_t ausIndex) const {
	uint16_t usIndex = 0;
	const BSSimpleList<DialogueItem*>* pIter = kDialogueItems.GetHead();
	while (pIter && !pIter->IsEmpty()) {
		if (usIndex == ausIndex)
			return pIter->GetItem();
		pIter = pIter->GetNext();
	}
	return nullptr;
}

// GAME - 0x83B930
void Conversation::ClearList() {
	ThisCall(0x83B930, this);
}
