#include "BSAudioManager.hpp"

// GAME - 0xAD9060
// GECK - 0x886AE0
BSAudioManager* BSAudioManager::GetSingleton() {
#ifdef GAME
    return CdeclCall<BSAudioManager*>(0xAD9060);
#else
    return CdeclCall<BSAudioManager*>(0x886AE0);
#endif
}

// GAME - 0xAE5870
// GECK - 0x8932F0
BSSoundHandle BSAudioManager::GetSoundHandleByFormID(uint32_t auiFormID, uint32_t auiSoundTypeFlags) {
#ifdef GAME
    return ThisCall<BSSoundHandle>(0xAE5870, this, auiFormID, auiSoundTypeFlags);
#else
    return ThisCall<BSSoundHandle>(0x8932F0, this, auiFormID, auiSoundTypeFlags);
#endif
}

// GAME - 0xAE5680
// GECK - 0x893100
BSSoundHandle BSAudioManager::GetSoundHandleByEditorID(const char* apEditorID, uint32_t auiSoundTypeFlags) {
#ifdef GAME
    return ThisCall<BSSoundHandle>(0xAE5680, this, apEditorID, auiSoundTypeFlags);
#else
	return ThisCall<BSSoundHandle>(0x893100, this, apEditorID, auiSoundTypeFlags);
#endif
}

// GAME - 0xAE5A50
// GECK - 0x8934D0
BSSoundHandle BSAudioManager::GetSoundHandleByFilePath(const char* apPath, uint32_t auiSoundTypeFlags, TESSound* apSound) {
#ifdef GAME
    return ThisCall<BSSoundHandle>(0xAE5A50, this, apPath, auiSoundTypeFlags, apSound);
#else
	return ThisCall<BSSoundHandle>(0x8934D0, this, apPath, auiSoundTypeFlags, apSound);
#endif
}