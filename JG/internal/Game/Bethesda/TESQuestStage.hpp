#pragma once

#include "BSSimpleList.hpp"
#include "TESQuestStageItem.hpp"

class TESQuestStage {
public:
	struct Data {
		uint8_t	ucIndex;
		bool	bIsDone;
	};

	Data								kData;
	BSSimpleList<TESQuestStageItem*>	kStageItems;

	uint8_t GetIndex() const;

	bool GetDone() const;
	void SetDone(bool abVal);
	void SetDone(TESQuest* apQuest, bool abAllItems);

	const BSSimpleList<TESQuestStageItem*>* GetStageItemList() const;
	BSSimpleList<TESQuestStageItem*>* GetStageItemList();

	TESQuestStageItem* GetStageItem(uint8_t aucIndex) const;
};

ASSERT_SIZE(TESQuestStage, 0xC)