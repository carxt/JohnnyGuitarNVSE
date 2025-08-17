#pragma once

#include "BSStringT.hpp"
#include "BSSimpleList.hpp"

class TESQuest;
class TESTopicInfo;
class TESTopic;
class DialogueResponse;

class MenuTopic {
public:
	BSString							strDialogue;
	bool								byte8;
	bool								byte9;
	bool								byteA;
	BSSimpleList<DialogueResponse*>		kResponses;
	TESQuest*							pQuest;
	TESTopicInfo*						pTopicInfo;
	TESTopic*							pTopic;
	BSSimpleList<DialogueResponse*>*	pFirstResponse;
	bool								byte24;
	bool								bNotSaidOnce;
	TESTopic*							pTopic28;

	DialogueResponse* GetCurrentResponse() const;
	bool NextResponse();
};

ASSERT_SIZE(MenuTopic, 0x2C);