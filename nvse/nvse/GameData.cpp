#include "GameData.h"

DataHandler* DataHandler::Get() {
	DataHandler** g_dataHandler = (DataHandler**)0x011C3F2C;
	return *g_dataHandler;
}

class LoadedModFinder {
	const char* m_stringToFind;

public:
	LoadedModFinder(const char* str) : m_stringToFind(str) {}

	bool Accept(ModInfo* modInfo) {
		return _stricmp(modInfo->name, m_stringToFind) == 0;
	}
};

const ModInfo* DataHandler::LookupModByName(const char* modName) {
	auto finder = LoadedModFinder(modName);
	return modList.modInfoList.Find(finder);
}

const ModInfo** DataHandler::GetActiveModList() {
	static const ModInfo* activeModList[0x100] = { 0 };

	if (!(*activeModList)) {
		UInt16 index = 0;
		for (index = 0; index < DataHandler::Get()->modList.modInfoList.Count(); index++) {
			ModInfo* entry = DataHandler::Get()->modList.modInfoList.GetNthItem(index);
			if (entry->IsLoaded())
				activeModList[index] = entry;
		}
	}

	return activeModList;
}

UInt8 DataHandler::GetModIndex(const char* modName) {
	ListNode<ModInfo>* iter = modList.modInfoList.Head();
	ModInfo* modInfo;
	do {
		modInfo = iter->data;
		if (modInfo && StrEqualCI(modInfo->name, modName))
			return modInfo->modIndex;
	} while (iter = iter->next);
	return 0xFF;
}

const char* DataHandler::GetNthModName(UInt32 modIndex) {
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

UInt8 DataHandler::GetActiveModCount() const {
	return modList.modInfoList.Count();
}

ModInfo::ModInfo() {
	//
};

ModInfo::~ModInfo() {
	//
};