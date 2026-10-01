#include "PlayerCharacter.hpp"

PlayerCharacter* PlayerCharacter::GetSingleton() {
	return *reinterpret_cast<PlayerCharacter**>(0x011DEA3C);
}

// GAME - 0x950BB0
NiAVObject* PlayerCharacter::Get3D(bool abFirstPerson) const {
	return ThisCall<NiAVObject*>(0x950BB0, this, abFirstPerson);
}

// GAME - 0x950B00
BipedAnim* PlayerCharacter::GetBiped(bool abFirstPerson) const {
	return ThisCall<BipedAnim*>(0x950B00, this, abFirstPerson);
}

// GAME - 0x950A60
Animation* PlayerCharacter::GetAnimation(bool abFirstPerson) const {
	return ThisCall<Animation*>(0x950A60, this, abFirstPerson);
}

// GAME - 0x874900
float PlayerCharacter::Get1stPersonFOV() const {
	return ThisCall<float>(0x874900, this);
}

// GAME - 0x710AB0
float PlayerCharacter::GetWorldFOV() const {
	return ThisCall<float>(0x710AB0, this);
}

// GAME - 0x967AE0
bool PlayerCharacter::IsPipboyActive() const {
	return ThisCall<bool>(0x967AE0, this);
}

// GAME - 0x4EAF60
bool PlayerCharacter::Is3rdPerson() const {
	return b3rdPerson;
}

// GAME - 0x524D10
bool PlayerCharacter::IsActually3rdPerson() const {
	return bActually3rdPerson;
}

// GAME - 0x950340
void PlayerCharacter::ForceTemp3rdPerson(bool abResetVanity) {
	ThisCall(0x950340, this, abResetVanity);
}

// GAME - 0x950090
bool PlayerCharacter::IsVanityMode() const {
	return ThisCall<bool>(0x950090, this);
}

// GAME - 0x94DF60
bool PlayerCharacter::IsSleepingOrResting() const {
	return ThisCall<bool>(0x94DF60, this);
}

// GAME - 0x93A740
bool PlayerCharacter::GetUnderAIControl() const {
	return ThisCall<bool>(0x93A740, this);
}

// GAME - 0x967090
PlayerCharacter::PerceivedActor* PlayerCharacter::IsActorPerceived(Actor* apActor) const {
	return ThisCall<PerceivedActor*>(0x967090, this, apActor);
}

// GAME - 0x966F20
void PlayerCharacter::InsertPerceivedActor(Actor* apActor, bool abIsHostile, bool abIsUndetected) {
	ThisCall(0x966F20, this, apActor, abIsHostile, abIsUndetected);
}

// GAME - 0x967350
void PlayerCharacter::RemovePerceivedActor(Actor* apActor) {
	ThisCall(0x967350, this, apActor);
}

// GAME - 0x969930
AudioMarkerInfo* PlayerCharacter::GetCurrentMusicMarker() {
	return ThisCall<AudioMarkerInfo*>(0x969930, this);
}

// GAME - 0x962720
bool PlayerCharacter::IsPlayerFollower(Actor* apActor) {
	return ThisCall<bool>(0x962720, this, apActor);
}

// GAME - 0x952E60
void PlayerCharacter::SetPlayerMapMarker(NiPoint3 akLocation, TESForm* apSpace) {
	ThisCall(0x952E60, this, akLocation, apSpace);
}

// GAME - 0x952F90
void PlayerCharacter::RemovePlayerMapMarker() {
	ThisCall(0x952F90, this);
}
