#pragma once

#include "DialogueItem.hpp"

class Conversation {
public:
	Conversation();
	~Conversation();

	BSSimpleList<DialogueItem*>		kDialogueItems;
	BSSimpleList<DialogueItem*>*	pCurrentItem;

	bool FirstItem();
	bool NextItem();
	DialogueItem* GetCurrentItem() const;
	bool GetNext();
	DialogueItem* GetDialogueItemByIndex(uint16_t ausIndex) const;

	void ClearList();
};

ASSERT_SIZE(Conversation, 0xC);
