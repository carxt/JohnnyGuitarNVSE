#include "BGSNote.hpp"

// GAME - 0x5E8D40
BGSNote::Type BGSNote::GetNoteType() const {
    return eNoteType;
}

// GAME - 0x5E8F90
// GECK - 0x54C4E0
void BGSNote::SetNoteType(BGSNote::Type aeType) {
#ifdef GAME
	ThisCall(0x5E8F90, this, aeType);
#else
	ThisCall(0x54C4E0, this, aeType);
#endif
}

// GAME - 0x5E9100
TESSound* BGSNote::GetNoteSound() const {
	return GetNoteType() == Type::SOUND ? pNoteSound : nullptr;
}

// GAME - 0x5E9130
// GECK - 0x54B050
void BGSNote::SetNoteSound(TESSound* apSound) {
#ifdef GAME
	ThisCall(0x5E9130, this, apSound);
#else
	ThisCall(0x54B050, this, apSound);
#endif
}

// GAME - 0x5E91D0
// GECK - 0x54B0B0
TESDescription* BGSNote::GetNoteText() const {
	return GetNoteType() == Type::TEXT ? pNoteText : nullptr;
}

// GAME - 0x5E9200
// GECK - 0x54B0D0
void BGSNote::SetNoteText(TESDescription* apText) {
#ifdef GAME
	ThisCall(0x5E9200, this, apText);
#else
	ThisCall(0x54B0D0, this, apText);
#endif
}

// GAME - 0x5E9160
// GECK - 0x54B070
TESTexture* BGSNote::GetNoteImage() const {
	return GetNoteType() == Type::IMAGE ? pNotePicture : nullptr;
}

// GAME - 0x5E9190
// GECK - 0x54B090
void BGSNote::SetNoteImage(TESTexture* apImage) {
#ifdef GAME
	ThisCall(0x5E9190, this, apImage);
#else
	ThisCall(0x54B090, this, apImage);
#endif
}

// GAME - 0x5E9240
TESTopic* BGSNote::GetNoteTopic() const {
	return GetNoteType() == Type::VOICE ? pNoteTopic : nullptr;
}

// GAME - 0x5E9270
// GECK - 0x54B110
void BGSNote::SetNoteTopic(TESTopic* apTopic) {
#ifdef GAME
	ThisCall(0x5E9270, this, apTopic);
#else
	ThisCall(0x54B110, this, apTopic);
#endif
}

// GAME - 0x5E92A0
TESActorBase* BGSNote::GetNoteSpeaker() const {
	return GetNoteType() == Type::VOICE ? pSpeaker : nullptr;
}

// GAME - 0x5E92D0
// GECK - 0x54B150
void BGSNote::SetNoteSpeaker(TESActorBase* apSpeaker) {
#ifdef GAME
	ThisCall(0x5E92D0, this, apSpeaker);
#else
	ThisCall(0x54B150, this, apSpeaker);
#endif
}

// GAME - 0x798420
bool BGSNote::GetHasBeenRead() const {
	return bHasBeenRead;
}

// GAME - 0x5E9300
void BGSNote::SetHasBeenRead(bool abRead) {
#ifdef GAME
    ThisCall(0x5E9300, this, abRead);
#else
	bHasBeenRead = abRead;
#endif
}
