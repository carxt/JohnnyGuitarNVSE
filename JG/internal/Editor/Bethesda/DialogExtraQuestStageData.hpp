#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraSubWindow;

class DialogExtraQuestStageData : public BSExtraData {
public:
	DWORD					dwordC;
	DWORD					dword10;
	DWORD					dword14;
	DWORD					dword18;
	DWORD					dword1C;
	DialogExtraSubWindow*	pSubWindow;
	DWORD					dword24;

	BSEXTRA_TYPE(DialogExtraQuestStageData);
};

ASSERT_SIZE(DialogExtraQuestStageData, 0x28);