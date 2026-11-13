#pragma once

#include "BSSimpleList.hpp"

class TESTopic;

class TESConversationData {
public:
	BSSimpleList<TESTopic*>	kLinkFrom;
	BSSimpleList<TESTopic*>	kLinkTo;
	BSSimpleList<TESTopic*>	kFollowUp;

	const BSSimpleList<TESTopic*>* GetLinkFrom() const;
	BSSimpleList<TESTopic*>* GetLinkFrom();

	const BSSimpleList<TESTopic*>* GetLinkTo() const;
	BSSimpleList<TESTopic*>* GetLinkTo();

	const BSSimpleList<TESTopic*>* GetFollowUp() const;
	BSSimpleList<TESTopic*>* GetFollowUp();

	void ClearLists();
};

ASSERT_SIZE(TESConversationData, 0x18);