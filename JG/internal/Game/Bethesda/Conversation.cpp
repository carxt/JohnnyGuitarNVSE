#include "Conversation.hpp"

// GAME - 0x83B830
Conversation::Conversation() {
	ThisCall(0x83B830, this);
}

// GAME - 0x83B8D0
Conversation::~Conversation() {
	ThisCall(0x83B8D0, this);
}

// GAME - 0x83B9A0
bool Conversation::FirstItem() {
	return ThisCall<bool>(0x83B9A0, this);
}

// GAME - 0x83C7E0
bool Conversation::NextItem() {
	return ThisCall<bool>(0x83C7E0, this);
}

// GAME = 0x83C820
DialogueItem* Conversation::GetCurrentItem() const {
	return ThisCall<DialogueItem*>(0x83C820, this);
}

// GAME - 0x83B9F0
bool Conversation::GetNext() {
	return ThisCall<bool>(0x83B9F0, this);
}

// GAME - 0x83BAC0
DialogueItem* Conversation::GetDialogueItemByIndex(uint16_t ausIndex) const {
	return ThisCall<DialogueItem*>(0x83BAC0, this, ausIndex);
}

// GAME - 0x83B930
void Conversation::ClearList() {
	ThisCall(0x83B930, this);
}
