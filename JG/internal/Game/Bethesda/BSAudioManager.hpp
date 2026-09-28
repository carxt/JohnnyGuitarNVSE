#pragma once

#include "BSSoundHandle.hpp"
#include "BSSoundMessage.hpp"
#include "BSSoundInfo.hpp"
#include "BSCriticalSection.hpp"
#include "Gamebryo/NiTPointerMap.hpp"
#include "Gamebryo/NiTList.hpp"
#include "Gamebryo/NiAVObject.hpp"

class BSGameSound;
class BSSoundHandle;
class BSAudioManagerThread;
class AudioLoadTask;
class TESSound;

class SoundMessageStack {
public:
	uint32_t		uiCount;
	bool			bBottomless;
	BSSoundMessage* pTop;
	uint32_t		uiTimeLastAllocated;
};

using SoundMessageList = NiTPointerList<BSSoundMessage*>;

class BSAudioManager {
public:
	BSAudioManager();
	virtual ~BSAudioManager();

	struct PAUSE_ENTRY {
		enum ComparisonType : uint16_t {
			EXACT	= 1,
			ANY		= 2,
		};

		Bitfield32	uiFlags;
		uint16_t	usState;
	};

	struct _Volumes {
		enum Volumes {
			MASTER			= 0,

			// Setting-controlled volumes
			FOOTSTEP		= 1,
			VOICE			= 2,
			EFFECTS			= 3,
			MUSIC			= 4,
			RADIO			= 5,
			
			VATS			= 6,

			// Additional multipliers
			MULT_FOOTSTEP	= 7,
			MULT_VOICE		= 8,
			MULT_EFFECTS	= 9,
			MULT_MUSIC		= 10,
			MULT_RADIO		= 11,

			TOTAL_COUNT,
		};
	};
	using Volumes = _Volumes::Volumes;

	uint32_t								uiMessageListIndex;
	uint32_t								uiMessageProcessingListIndex;
	SoundMessageList						kMessages[2];
	SoundMessageStack						kFreeMessages;
	SoundMessageStack						kFreeQueuedMessages;
	SoundMessageStack						kGarbageMessages;
	NiTPointerMap<uint32_t, BSGameSound*>	kPlayingSounds;
	NiTPointerMap<uint32_t, BSSoundInfo*>	kSoundStates;
	NiTPointerMap<uint32_t, BSSoundInfo*>	kStateUpdates;
	NiTPointerMap<uint32_t, NiAVObjectPtr>	kMovingObjects;
	NiTPointerList<BSGameSound*>			kCachedSounds;
	uint32_t								uiUsedCacheSize;
	Bitfield32								uiWeatherFlags;
	float									fGameHour;
	BSCriticalSection						kMessageCritSection;
	BSCriticalSection						kStateCritSection;
	BSCriticalSection						kCacheCritSection;
	BSCriticalSection						kProcessingCritSection;
	BSCriticalSection						kCacheLoadTaskCritSection;
	NiTPointerList<AudioLoadTask*>			kCacheLoadTaskList;
	uint32_t								uiDelayTimerDelta;
	bool									bPrecacheCompleted;
	bool									bListenerMoved;
	uint32_t								uiThreadID;
	BSAudioManagerThread*					pUpdateThread;
	float									fVolumes[Volumes::TOTAL_COUNT];
	Bitfield32								uiMuteMask; // BSGameSound::TypeFlags that should be faded out
	bool									bDialogueFade;
	bool									bListenerUnderwater;
	PAUSE_ENTRY*							pPauseEntries;
	uint32_t								uiPauseListSize;
	uint32_t								uiNextID;
	bool									bIgnoreGlobalTimeMultiplier;

	static BSAudioManager* GetSingleton();

	BSSoundHandle GetSoundHandleByFormID(uint32_t auiFormID, uint32_t auiSoundTypeFlags);
	BSSoundHandle GetSoundHandleByEditorID(const char* apEditorID, uint32_t auiSoundTypeFlags);
	BSSoundHandle GetSoundHandleByFilePath(const char* apPath, uint32_t auiSoundTypeFlags, TESSound* apSound);
};

ASSERT_SIZE(BSAudioManager, 0x188);