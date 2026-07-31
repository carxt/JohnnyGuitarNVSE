#pragma once

#include "BSSimpleList.hpp"

class TESQuest;

class QuestUpdateManager {
public:
	struct _UpdateType {
		enum Type {
			QUEST_ADDED		= 0,
			QUEST_COMPLETED	= 1,
			QUEST_FAILED	= 2,
			CUSTOM			= 3,
			COUNT,
		};
	};
	using UpdateType = _UpdateType::Type;

	struct _TextJustification {
		enum Type {
			LEFT	= 0,
			CENTER	= 1,
			RIGHT	= 2,
		};
	};
	using TextJustification = _TextJustification::Type;

	struct _QueuePriority {
		enum Type {
			NOW		= 0,
			NORMAL	= 1,
			LAST	= 2,
		};
	};
	using QueuePriority = _QueuePriority::Type;

	struct QuestUpdate {
		TESQuest*			pQuest;
		UpdateType			eUpdateType;
		char				cCustomTextTitle[260];
		char				cCustomTextSubtitle[260];
		TextJustification	eCustomTextJustification;
		QueuePriority		eCustomQueuePriority;
		uint32_t			eCustomTextTitleFont;
		uint32_t			eCustomTextSubtitleFont;
		char				cCustomSoundHandleName[260];
	};

	static constexpr AddressPtr<BSSimpleList<QuestUpdate*>, 0x11D970C> kQuestNames;
};

ASSERT_SIZE(QuestUpdateManager::QuestUpdate, 0x324);