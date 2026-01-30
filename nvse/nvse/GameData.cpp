#include "GameData.h"

DataHandler* DataHandler::Get() {
	DataHandler** g_dataHandler = (DataHandler**)0x011C3F2C;
	return *g_dataHandler;
}

class LoadedModFinder {
	const char* m_stringToFind;

public:
	LoadedModFinder(const char* str) : m_stringToFind(str) {}

	bool Accept(const ModInfo* modInfo) const {
		return _stricmp(modInfo->name, m_stringToFind) == 0;
	}
};

const ModInfo* DataHandler::LookupModByName(const char* modName) {
	return modList.modInfoList.Find(LoadedModFinder(modName));
}

const ModInfo** DataHandler::GetActiveModList() {
	static const ModInfo* activeModList[0x100] = { 0 };

	if (!(*activeModList)) {
		uint16_t index = 0;
		for (index = 0; index < DataHandler::Get()->modList.modInfoList.Count(); index++) {
			ModInfo* entry = DataHandler::Get()->modList.modInfoList.GetNthItem(index);
			if (entry->IsLoaded())
				activeModList[index] = entry;
		}
	}

	return activeModList;
}

uint8_t DataHandler::GetModIndex(const char* modName) {
	ListNode<ModInfo>* iter = modList.modInfoList.Head();
	ModInfo* modInfo;
	do {
		modInfo = iter->data;
		if (modInfo && StrEqualCI(modInfo->name, modName))
			return modInfo->modIndex;
	} while (iter = iter->next);
	return 0xFF;
}

const char* DataHandler::GetNthModName(uint32_t modIndex) {
	const ModInfo** activeModList = GetActiveModList();
	if (modIndex < GetActiveModCount() && activeModList[modIndex])
		return activeModList[modIndex]->name;
	else
		return "";
}

struct IsModLoaded {
	bool Accept(ModInfo* pModInfo) const {
		return pModInfo->IsLoaded();
	}
};

uint8_t DataHandler::GetActiveModCount() const {
	return modList.modInfoList.Count();
}

ModInfo::ModInfo() {
	//
};

ModInfo::~ModInfo() {
	//
};