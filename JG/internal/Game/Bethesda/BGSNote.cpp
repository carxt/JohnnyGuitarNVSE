#include "BGSNote.hpp"

// GAME - 0x5E8D40
BGSNote::NoteType BGSNote::GetNoteType() const {
    return eNoteType;
}

// GAME - 0x5E8F90
void BGSNote::SetNoteType(BGSNote::NoteType aeType) {
	ThisCall(0x5E8F90, this, aeType);
}

// GAME - 0x5E9100
TESSound* BGSNote::GetNoteSound() const {
	return GetNoteType() == NoteType::SOUND ? pNoteSound : nullptr;
}

// GAME - 0x5E9130
void BGSNote::SetNoteSound(TESSound* apSound) {
	ThisCall(0x5E9130, this, apSound);
}

// GAME - 0x5E91D0
TESDescription* BGSNote::GetNoteText() const {
	return GetNoteType() == NoteType::TEXT ? pNoteText : nullptr;
}

// GAME - 0x5E9200
void BGSNote::SetNoteText(TESDescription* apText) {
	ThisCall(0x5E9200, this, apText);
}

// GAME - 0x5E9160
TESTexture* BGSNote::GetNoteImage() const {
	return GetNoteType() == NoteType::IMAGE ? pNotePicture : nullptr;
}

// GAME - 0x5E9190
void BGSNote::SetNoteImage(TESTexture* apImage) {
	ThisCall(0x5E9190, this, apImage);
}

// GAME - 0x5E9240
TESTopic* BGSNote::GetNoteTopic() const {
	return GetNoteType() == NoteType::VOICE ? pNoteTopic : nullptr;
}

// GAME - 0x5E9270
void BGSNote::SetNoteTopic(TESTopic* apTopic) {
	ThisCall(0x5E9270, this, apTopic);
}

// GAME - 0x5E92A0
TESActorBase* BGSNote::GetNoteSpeaker() const {
	return GetNoteType() == NoteType::VOICE ? pSpeaker : nullptr;
}

// GAME - 0x5E92D0
void BGSNote::SetNoteSpeaker(TESActorBase* apSpeaker) {
	ThisCall(0x5E92D0, this, apSpeaker);
}

// GAME - 0x798420
bool BGSNote::GetHasBeenRead() const {
	return bHasBeenRead;
}

// GAME - 0x5E9300
void BGSNote::SetHasBeenRead(bool abRead) {
    ThisCall(0x5E9300, this, abRead);
}
