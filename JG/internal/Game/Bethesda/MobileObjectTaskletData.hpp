#pragma once

#include "BSCriticalSection.hpp"
#include "BSTCommonLLMessageQueue.hpp"
#include "BSWin32TaskletData.hpp"
#include "MobileObjectMessage.hpp"
#include "BSSimpleList.hpp"

class MobileObject;

// Unused
class MobileObjectTaskletData : public BSWin32TaskletData {
public:
	MobileObjectTaskletData(BSTFreeList<MobileObjectMessage>* apList);
	~MobileObjectTaskletData() override;

	virtual void HandleCountMessage(uint32_t auiObjectCount);
	virtual void HandleMobMessage(MobileObject* apObject);
	virtual void HandleEndMessage(uint32_t auiThreadNumber);

	BSSimpleList<MobileObject*>*					pMobList;
	BSTCommonLLMessageQueue<MobileObjectMessage>	kMessageQueue;
	uint32_t										uiHighActorCount;
	uint32_t										eType;
};

ASSERT_SIZE(MobileObjectTaskletData, 0x38);