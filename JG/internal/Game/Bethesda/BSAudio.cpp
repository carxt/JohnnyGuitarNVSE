#include "BSAudio.hpp"

// GAME - 0x453A70
BSAudio* BSAudio::GetSingleton() {
#ifdef GAME
	return *reinterpret_cast<BSAudio**>(0x11F6D98);
#else
	return *reinterpret_cast<BSAudio**>(0xF226C0);
#endif
}

// GAME - 0xAD79B0
void BSAudio::SetEnvironment(uint32_t aeType) {
	if (pListener)
		pListener->SetEnvironmentType(aeType);
}

// GAME - 0xAD73B0
// GECK - 0x884DA0
BSSoundHandle BSAudio::GetSoundHandleByFormID(FormID auiFormID, uint32_t auiTypeFlags) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD73B0, this, auiFormID, auiTypeFlags);
#else
	return ThisCall<BSSoundHandle>(0x884DA0, this, auiFormID, auiTypeFlags);
#endif
}

// GAME - 0xAD7550
// GECK - 0x884F40
BSSoundHandle BSAudio::GetSoundHandleByEditorID(const char* apEditorID, uint32_t auiTypeFlags) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD7550, this, apEditorID, auiTypeFlags);
#else
	return ThisCall<BSSoundHandle>(0x884F40, this, apEditorID, auiTypeFlags);
#endif
}

// GAME - 0xAD7480
// GECK - 0x884E70
BSSoundHandle BSAudio::GetSoundHandleByFilePath(const char* apPath, uint32_t auiTypeFlags, TESSound* apSound) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD7480, this, apPath, auiTypeFlags);
#else
	return ThisCall<BSSoundHandle>(0x884E70, this, apPath, auiTypeFlags);
#endif
}

// GAME - 0xAD8050
// GECK - 0x885A40
void BSAudio::Precache(FormID auiFormID, uint32_t auiTypeFlags) {
#ifdef GAME
	ThisCall(0xAD8050, this, auiFormID, auiTypeFlags);
#else
	ThisCall(0x885A40, this, auiFormID, auiTypeFlags);
#endif
}

// GAME - 0xAD7FA0
// GECK - 0x885990
void BSAudio::Precache(const char* apEditorID, uint32_t auiTypeFlags) {
#ifdef GAME
	ThisCall(0xAD7FA0, this, apEditorID, auiTypeFlags);
#else
	ThisCall(0x885990, this, apEditorID, auiTypeFlags);
#endif
}

// GAME - 0xAD8100
// GECK - 0x885AF0
void BSAudio::Precache(const char* apPath, uint32_t auiTypeFlags, TESSound* apSound) {
#ifdef GAME
	ThisCall(0xAD8100, this, apPath, auiTypeFlags, apSound);
#else
	ThisCall(0x885AF0, this, apPath, auiTypeFlags, apSound);
#endif
}

// GAME - 0xAD7620
// GECK - 0x885010
BSSoundHandle BSAudio::SpawnSoundReference(FormID auiFormID, uint32_t auiTypeFlags, NiPoint3 akPosition, uint32_t auiID) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD7620, this, auiFormID, auiTypeFlags, akPosition, auiID);
#else
	return ThisCall<BSSoundHandle>(0x885010, this, auiFormID, auiTypeFlags, akPosition, auiID);
#endif
}

// GAME - 0xAD8480
// GECK - 0x885E70
void BSAudio::MuteType(uint32_t aeSoundTypes, uint32_t auiFadeDuration, uint32_t auiMillibels) {
#ifdef GAME
	ThisCall(0xAD8480, this, aeSoundTypes, auiFadeDuration, auiMillibels);
#else
	ThisCall(0x885E70, this, aeSoundTypes, auiFadeDuration, auiMillibels);
#endif
}

// GAME - 0xAD84B0
// GECK - 0x885EA0
void BSAudio::UnMuteType(uint32_t aeSoundTypes, uint32_t auiFadeDuration) {
#ifdef GAME
	ThisCall(0xAD84B0, this, aeSoundTypes, auiFadeDuration);
#else
	ThisCall(0x885EA0, this, aeSoundTypes, auiFadeDuration);
#endif
}