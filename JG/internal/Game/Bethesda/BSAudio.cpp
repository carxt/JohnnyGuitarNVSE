#include "BSAudio.hpp"

// GAME - 0x453A70
BSAudio* BSAudio::GetSingleton() {
#ifdef GAME
	return *reinterpret_cast<BSAudio**>(0x11F6D98);
#else
	return *reinterpret_cast<BSAudio**>(0xF226C0);
#endif
}

// GAME - 0x63D040
uint32_t BSAudio::GetSynchTime() const {
	return kSynchTimer.GetSynchTime();
}

// GAME - 0xAD73B0
// GECK - 0x884DA0
BSSoundHandle BSAudio::GetSoundHandleByFormID(FormID auiFormID, uint32_t auiSoundTypeFlags) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD73B0, this, auiFormID, auiSoundTypeFlags);
#else
	return ThisCall<BSSoundHandle>(0x884DA0, this, auiFormID, auiSoundTypeFlags);
#endif
}

// GAME - 0xAD7550
// GECK - 0x884F40
BSSoundHandle BSAudio::GetSoundHandleByEditorID(const char* apEditorID, uint32_t auiSoundTypeFlags) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD7550, this, apEditorID, auiSoundTypeFlags);
#else
	return ThisCall<BSSoundHandle>(0x884F40, this, apEditorID, auiSoundTypeFlags);
#endif
}

// GAME - 0xAD7480
// GECK - 0x884E70
BSSoundHandle BSAudio::GetSoundHandleByFilePath(const char* apPath, uint32_t auiSoundTypeFlags, TESSound* apSound) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD7480, this, apPath, auiSoundTypeFlags, apSound);
#else
	return ThisCall<BSSoundHandle>(0x884E70, this, apPath, auiSoundTypeFlags, apSound);
#endif
}

// GAME - 0xAD8050
// GECK - 0x885A40
void BSAudio::Precache(FormID auiFormID, uint32_t auiSoundTypeFlags) {
#ifdef GAME
	ThisCall(0xAD8050, this, auiFormID, auiSoundTypeFlags);
#else
	ThisCall(0x885A40, this, auiFormID, auiSoundTypeFlags);
#endif
}

// GAME - 0xAD7FA0
// GECK - 0x885990
void BSAudio::Precache(const char* apEditorID, uint32_t auiSoundTypeFlags) {
#ifdef GAME
	ThisCall(0xAD7FA0, this, apEditorID, auiSoundTypeFlags);
#else
	ThisCall(0x885990, this, apEditorID, auiSoundTypeFlags);
#endif
}

// GAME - 0xAD8100
// GECK - 0x885AF0
void BSAudio::Precache(const char* apPath, uint32_t auiSoundTypeFlags, TESSound* apSound) {
#ifdef GAME
	ThisCall(0xAD8100, this, apPath, auiSoundTypeFlags, apSound);
#else
	ThisCall(0x885AF0, this, apPath, auiSoundTypeFlags, apSound);
#endif
}


// GAME - 0xAD7620
// GECK - 0x885010
BSSoundHandle BSAudio::SpawnSoundReference(FormID auiFormID, uint32_t auiSoundTypeFlags, NiPoint3 akPosition, uint32_t auiID) {
#ifdef GAME
	return ThisCall<BSSoundHandle>(0xAD7620, this, auiFormID, auiSoundTypeFlags, akPosition, auiID);
#else
	return ThisCall<BSSoundHandle>(0x885010, this, auiFormID, auiSoundTypeFlags, akPosition, auiID);
#endif
}

// GAME - 0xAD85A0
// GECK - 0x885F90
void BSAudio::EnterDialogue() {
#ifdef GAME
	ThisCall(0xAD85A0, this);
#else
	ThisCall(0x885F90, this);
#endif
}

// GAME - 0xAD8650
// GECK - 0x886040
void BSAudio::ExitDialogue() {
#ifdef GAME
	ThisCall(0xAD8650, this);
#else
	ThisCall(0x886040, this);
#endif
}
