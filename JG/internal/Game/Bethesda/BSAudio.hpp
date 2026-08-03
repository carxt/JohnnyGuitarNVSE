#pragma once

#include "BSMemObject.hpp"
#include "BSSoundHandle.hpp"
#include "BSAudioListener.hpp"
#include "BSAudioSynchTimer.hpp"

using FormID = uint32_t;

class TESSound;
class BSGameSound;

class BSAudio {
public:
	using pfnLoopPointsCallback_t		= bool(__cdecl*)(void*, void*, void*);
	using pfnIDCallback_t				= bool(__cdecl*)(FormID, char*, void*, void**);
	using pfnNameCallback_t				= bool(__cdecl*)(const char*, char*, void*, void**);
	using pfnRandomFilenameCallback_t	= bool(__cdecl*)(char*);
	using pfnSettingsCallback_t			= uint32_t(__cdecl*)(BSSoundHandle&, void*, void*);
	using pfnSynchPausedCallback_t		= void(__cdecl*)();
	using pfnSynchUnPausedCallback_t	= void(__cdecl*)();

	BSAudio();
	virtual							~BSAudio();
	virtual void					Init(HWND ahWindow);
	virtual void					Shutdown();
	virtual void					SetLoopPointCallback(pfnLoopPointsCallback_t apCallback);
	virtual pfnLoopPointsCallback_t	GetLoopPointCallback() const;
	virtual BSGameSound*			CreateNewGameSound(const char* apPath);
	virtual void					FixSoundPath(char* apPath);
	virtual void 					PrintDebugInfo();

	bool						bAudioEnabled;
	bool						bInitialized;
	bool						bMultiThread;
	uint32_t					uiMusicStartOffset;
	bool						bSeekMusic;
	BSAudioListener*			pListener;
	BSAudioSynchTimer			kSynchTimer;
	pfnIDCallback_t				pfnIDCallback;
	pfnNameCallback_t			pfnNameCallback;
	pfnRandomFilenameCallback_t	pfnRandomFilenameCallback;
	pfnSettingsCallback_t		pfnSettingsCallback;
	pfnSynchPausedCallback_t	pfnSynchPausedCallback;
	pfnSynchUnPausedCallback_t	pfnSynchUnPausedCallback;

	static BSAudio* GetSingleton();

	void SetEnvironment(uint32_t aeType);

	BSSoundHandle GetSoundHandleByFormID(FormID auiFormID, uint32_t auiTypeFlags);
	BSSoundHandle GetSoundHandleByEditorID(const char* apEditorID, uint32_t auiTypeFlags);
	BSSoundHandle GetSoundHandleByFilePath(const char* apPath, uint32_t auiTypeFlags, TESSound* apSound);
	
	void Precache(FormID auiFormID, uint32_t auiTypeFlags);
	void Precache(const char* apEditorID, uint32_t auiTypeFlags);
	void Precache(const char* apPath, uint32_t auiTypeFlags, TESSound* apSound);

	BSSoundHandle SpawnSoundReference(FormID auiFormID, uint32_t auiTypeFlags, NiPoint3 akPosition, uint32_t auiID = 0);

	void MuteType(uint32_t aeSoundTypes, uint32_t auiFadeDuration, uint32_t auiMillibels);
	void UnMuteType(uint32_t aeSoundTypes, uint32_t auiFadeDuration);
};

ASSERT_SIZE(BSAudio, 0x38);