#pragma once

#include "TESFile.hpp"
#include "BGSSaveLoadFormIDMap.hpp"
#include "BSSimpleArray.hpp"
#include "Gamebryo/NiTPointerMap.hpp"

class BGSCellNumericIDArrayMap;
class BGSLoadGameSubBuffer;
class BGSReconstructFormsInFileMap;
class BGSReconstructFormsInAllFilesMap;
class BGSSaveLoadQueuedSubBufferMap;
class BGSSaveLoadHistory;
class BGSLoadFormBuffer;
class BGSSaveLoadChangesMap;
class BGSSaveLoadFile;
class BGSSaveLoadReferencesMap;
class Actor;
class TESObjectCELL;
class TESFile;

class BGSSaveLoadGame {
public:
	BGSSaveLoadGame();
	~BGSSaveLoadGame();

	struct ALIGN4 _GlobalFlags {
		enum Flags : uint32_t {
			GLOBAL_BLOCK_CHANGES	= 1u << 0,
			SAVE_GAME_LOADING		= 1u << 1,
			SAVE_GAME_SAVING		= 1u << 2,
			INITING_FORMS			= 1u << 3,
			DEFER_INIT_FORMS		= 1u << 4,
			POSITIONING_PLAYER		= 1u << 5,
			PLAYER_LOCATION_INVALID = 1u << 6,
			SAVE_LOAD_FAILED		= 1u << 7,
		};

		bool bGlobalBlockChanges	: 1;
		bool bSaveGameLoading		: 1;
		bool bSaveGameSaving		: 1;
		bool bInitingForms			: 1;
		bool bDeferInitForms		: 1;
		bool bPositioningPlayer		: 1;
		bool bPlayerLocationInvalid : 1;
		bool bSaveLoadFailed		: 1;
	};
	using GlobalFlags = _GlobalFlags::Flags;

	struct ALIGN4 _ThreadFlags {
		enum Flags : uint32_t {
			THREAD_BLOCK_CHANGES	= 1u << 0,
			LOADING_MOVED_REFS		= 1u << 1,
			RECONSTRUCTING_FORMS	= 1u << 2,
		};
	};
	using ThreadFlags = _ThreadFlags::Flags;

	BGSSaveLoadChangesMap*						pChangesMap;
	BGSSaveLoadChangesMap*						pOldChangesMap;
	BGSSaveLoadFormIDMap*						pFormIDMap;
	BGSSaveLoadFormIDMap*						pWorldspaceFormIDMap;
	BGSSaveLoadReferencesMap*					pReferencesMap;
	BGSSaveLoadQueuedSubBufferMap*				pQueuedSubBuffersMap;
	NiTMap<uint32_t, uint32_t>*					pChangedFormIDMap;
	BGSSaveLoadHistory*							pHistory;
	BGSReconstructFormsInAllFilesMap*			pReconstructForms;
	BSSimpleArray<BGSLoadFormBuffer*>			kChangedForms;
	NiTMap<uint32_t, Actor*>					kQueuedInitPackageLocationsActorMap;
#if ESL_SUPPORT || OVERLAY_SUPPORT
	BSSimpleArray<TESFile*>						kFiles;
	BSSimpleArray<TESFile*>						kSmallFiles;
	Bitfield8									ucLoadOrderChanges;
	uint8_t										padding[478];
#else
	uint8_t										ucSaveMods[255];
	uint8_t										ucLoadedMods[255];
#endif
	Bitfield<_GlobalFlags>						uiGlobalFlags;
	uint8_t										ucCurrentMinorVersion;

	static BGSSaveLoadGame* GetSingleton();

	bool GetGlobalAllowChanges() const;
	bool GetSaveGameLoading() const;
	bool GetSaveGameSaving() const;
	bool GetInitingForms() const;
	bool GetDeferInitForms() const;
	bool GetPositioningPlayerCharacter() const;
	bool GetPlayerLocationInvalid() const;
	bool GetSaveLoadFailed() const;

	bool GetThreadAllowChanges();
	[[nodiscard("Previous value")]] bool SetThreadAllowChanges(bool abEnable);

	bool GetLoadingMovedRefs();
	bool GetReconstructingForms();

#if ESL_SUPPORT || OVERLAY_SUPPORT
	TESFile* GetSaveMod(uint8_t aucIndex) const;
#if ESL_SUPPORT
	TESFile* GetSmallSaveMod(uint16_t ausIndex) const;

	bool SupportsSmallPlugins() const;
#endif

#else
	uint8_t GetSaveMod(uint8_t aucIndex) const;
#endif

	void InitForms(bool abLowPriority);
	void LoadCell(TESObjectCELL* apCell);
};

ASSERT_SIZE(BGSSaveLoadGame, 0x24C);