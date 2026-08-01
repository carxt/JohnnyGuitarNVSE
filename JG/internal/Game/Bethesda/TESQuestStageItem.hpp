#pragma once

#include "TESCondition.hpp"
#include "Script.hpp"
#include "Calendar.hpp"

class TESForm;
class TESQuest;

class TESQuestStageItem {
public:
	struct ALIGN1 _QuestStageFlags {
		enum Flags : uint8_t {
			END_QUEST	= 1u << 0,
			FAIL_QUEST	= 1u << 1,
		};

		bool bEndQuest	: 1;
		bool bFailQuest	: 1;
	};
	using QuestStageFlags = _QuestStageFlags::Flags;

	struct Data {
		Bitfield<_QuestStageFlags>	ucFlags;
	};

	Data			kData;
	TESCondition	kConditions;
	Script			kScript;
	uint32_t		uiFileOffset;
	uint8_t			ucIndex;
	bool			bHasLogEntry;
	Date*			pLogDate;
	TESQuest*		pOwner;
	TESQuest*		pNextQuest;

	bool GetEndQuest() const;

	bool GetFailQuest() const;

	const TESCondition* GetConditions() const;
	TESCondition* GetConditions();

	const Script* GetResultScript() const;
	Script* GetResultScript();

	uint8_t GetIndex() const;
	void SetIndex(uint8_t aucIndex);

	bool GetHasLogEntry() const;
	void SetHasLogEntry(bool abVal);

	Date* GetLogDate() const;
	void SetLogDate(Date* apDate);

	TESQuest* GetOwner() const;
	
	TESQuest* GetNextQuest() const;
	void SetNextQuest(TESQuest* apQuest);

	const char* GetLogEntry(TESForm* apOwner);
};

ASSERT_SIZE(TESQuestStageItem, 0x74);