#pragma once

#include "BSSimpleList.hpp"
#include "TESQuestStageItem.hpp"

class TESQuestStage {
public:
	struct Data {
		uint8_t	ucIndex;
		bool	bIsDone;
	};

#ifdef EDITOR
	TESQuest*							pOwner;
#endif
	Data								kData;
	BSSimpleList<TESQuestStageItem*>	kStageItems;

#ifdef EDITOR
	TESQuest* GetOwnerQuest() const;
#endif

	uint8_t GetIndex() const;

	bool GetDone() const;
	void SetDone(bool abVal);
#ifdef GAME
	void SetDone(TESQuest* apQuest, bool abAllItems);
#endif

	const BSSimpleList<TESQuestStageItem*>* GetStageItemList() const;
	BSSimpleList<TESQuestStageItem*>* GetStageItemList();

#ifdef GAME
	TESQuestStageItem* GetStageItem(uint8_t aucIndex) const;
#endif
};

#ifdef GAME
ASSERT_SIZE(TESQuestStage, 0xC)
#else
ASSERT_SIZE(TESQuestStage, 0x10)
#endif