#pragma once

#include "BSEnums.hpp"
#include "BSSoundHandle.hpp"
#include "BSAudioListener.hpp"
#include "BSAudioSynchTimer.hpp"

class TESSound;
class BSGameSound;

class BSAudio {
public:
	using pfnGetLoopPoints_t			= bool(__cdecl*)(TESSound* apSound, uint32_t& arStart, uint32_t& arEnd);
	using pfnFormIDCallback_t			= bool(__cdecl*)(FormID auiFormID, char* apOutFilePath, uint32_t& arTypeFlags, TESSound*& arSound);
	using pfnEDIDCallback_t				= bool(__cdecl*)(const char* apEDID, char* apOutFilePath, uint32_t& arTypeFlags, TESSound*& arSound);
	using pfnRandomFilenameCallback_t	= bool(__cdecl*)(char* apOutFilePath);
	using pfnSettingsCallback_t			= uint32_t(__cdecl*)(BSSoundHandle& arHandle, TESSound* apSound, uint32_t* apModifierFlags);
	using pfnSynchPausedCallback_t		= void(__cdecl*)();
	using pfnSynchUnPausedCallback_t	= void(__cdecl*)();

	BSAudio();
	virtual						~BSAudio();
	virtual void				Init(HWND apWindow);
	virtual void				Shutdown();
	virtual void				SetLoopPointCallback(pfnGetLoopPoints_t apFunc);
	virtual pfnGetLoopPoints_t	GetLoopPointCallback() const;
	virtual BSGameSound*		CreateNewGameSound(const char* apPath) = 0;
	virtual void				FixSoundPath(char* apPath) = 0;
	virtual void 				PrintDebugInfo();

	bool						bAudioEnabled;
	bool						bInitialized;
	bool						bMultiThread;
	uint32_t					uiMusicStartOffset;
	BOOL						bSeekMusic;
	BSAudioListener*			pListener;
	BSAudioSynchTimer			kSynchTimer;
	pfnFormIDCallback_t			pfnFormIDCallback;
	pfnEDIDCallback_t			pfnEDIDCallback;
	pfnRandomFilenameCallback_t	pfnRandomFilenameCallback;
	pfnSettingsCallback_t		pfnSettingsCallback;
	pfnSynchPausedCallback_t	pfnSynchPausedCallback;
	pfnSynchUnPausedCallback_t	pfnSynchUnPausedCallback;

	static BSAudio* GetSingleton();

	uint32_t GetSynchTime() const;

	BSSoundHandle GetSoundHandleByFormID(FormID auiFormID, uint32_t auiSoundTypeFlags);
	BSSoundHandle GetSoundHandleByEditorID(const char* apEditorID, uint32_t auiSoundTypeFlags);
	BSSoundHandle GetSoundHandleByFilePath(const char* apPath, uint32_t auiSoundTypeFlags, TESSound* apSound);

	void Precache(FormID auiFormID, uint32_t auiSoundTypeFlags);
	void Precache(const char* apEditorID, uint32_t auiSoundTypeFlags);
	void Precache(const char* apPath, uint32_t auiSoundTypeFlags, TESSound* apSound);

	BSSoundHandle SpawnSoundReference(FormID auiFormID, uint32_t auiSoundTypeFlags, NiPoint3 akPosition, uint32_t auiID = 0);

	void EnterDialogue();
	void ExitDialogue();
};

ASSERT_SIZE(BSAudio, 0x38);