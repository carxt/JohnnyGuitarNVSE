#pragma once

#include "BSSimpleList.hpp"
#include "BGSSaveLoadFile.hpp"
#include "BSStringT.hpp"

struct BGSSaveLoadFileEntry {
	const char* pFileName;
	bool		bLoaded;
	bool		bCorrupt;
	uint32_t	uiSaveNumber;
	const char* pPlayerName;
	const char* pPlayerTitle;
	const char* pLocation;
	const char* pTime;
};

class BGSSaveLoadManager {
public:
	BGSSaveLoadManager();
	~BGSSaveLoadManager();

	BSSimpleList<BGSSaveLoadFileEntry*>*	pSaveGames;
	uint32_t								uiSaveGameCount;
	uint32_t								uiCurrentSaveGameNumber;
	bool									bSimulatedMode;
	bool									bAutosaveDisabledForDiskspace;
	bool									bHandledCorrupt;
	uint8_t									ucAutoSaveTimer;
	uint8_t									ucForceSaveTimer;
	uint8_t									ucSystemSaveTimer;
	const char*								pMostRecentSaveGame;
	int32_t									iMostRecentSaveGameDeviceID;
	bool									bSysUtilHasSaveData;
	BGSSaveLoadFile*						pSaveLoadFile;
	bool									bReturnedFromSysUtil;
	bool									bSysUtilLoadDataComplete;
	bool									bStartMenuLoading;
	void*									pSysUtilSaveCompleteCallback;
	void*									pSysUtilLoadCompleteCallback;
	BSString								strSaveName;

	static BGSSaveLoadManager* GetSingleton();

	uint8_t GetMinorVersion() const;
	void GetFullFileName(const char* apFilename, char* apFullPath);
	void GetFullPath(const char* apFilename, char* apFullPath, bool abTemp);
	void GetSaveDirectoryPath(char* apPath);
};

ASSERT_SIZE(BGSSaveLoadManager, 0x38);