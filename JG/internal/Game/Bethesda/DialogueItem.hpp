#pragma once

#include "BSSimpleList.hpp"
#include "DialogueResponse.hpp"

class TESTopicInfo;
class TESTopic;
class TESQuest;
class Actor;

class DialogueItem {
public:
	BSSimpleList<DialogueResponse*>		kResponses;
	BSSimpleList<DialogueResponse*>*	pCurrentResponse;
	TESTopicInfo*						pTopicInfo;
	TESTopic*							pTopic;
	TESQuest*							pQuest;
	Actor*								pSpeaker;

	bool FirstResponse();
	bool NextResponse();
	DialogueResponse* GetCurrentItem() const;
};

ASSERT_SIZE(DialogueItem, 0x1C);