#include "TESObjectDOOR.hpp"
#include "DoorLock.hpp"

// GAME - 0x407820
TESSound* TESObjectDOOR::GetOpenSound() const {
	return pOpenSound;
}

void TESObjectDOOR::SetOpenSound(TESSound* apSound) {
	pOpenSound = apSound;
}

// GAME - 0x407840
TESSound* TESObjectDOOR::GetCloseSound() const {
	return pCloseSound;
}

void TESObjectDOOR::SetCloseSound(TESSound* apSound) {
	pCloseSound = apSound;
}

// GAME - 0x4FB070
TESSound* TESObjectDOOR::GetLoopSound() const {
	return pLoopSound;
}

void TESObjectDOOR::SetLoopSound(TESSound* apSound) {
	pLoopSound = apSound;
}

bool TESObjectDOOR::IsOblivionGate() const {
	return ucFlags.bOblivionGate;
}

void TESObjectDOOR::SetOblivionGate(bool abVal) {
	ucFlags.bOblivionGate = abVal;
}

// GAME - 0x517FA0
bool TESObjectDOOR::IsAutomaticDoor() const {
	return ucFlags.bAutomatic;
}

void TESObjectDOOR::SetAutomaticDoor(bool abVal) {
	ucFlags.bAutomatic = abVal;
}

// GAME - 0x517FD0
bool TESObjectDOOR::IsHidden() const {
	return ucFlags.bHidden;
}

void TESObjectDOOR::SetHidden(bool abVal) {
	ucFlags.bHidden = abVal;
}

// GAME - 0x518000
bool TESObjectDOOR::IsMinimalUse() const {
	return ucFlags.bMinimalUse;
}

// GAME - 0x518030
void TESObjectDOOR::SetMinimalUse(bool abVal) {
	ucFlags.bMinimalUse = abVal;
}

// GAME - 0x518080
bool TESObjectDOOR::IsSlidingDoor() const {
	return ucFlags.bSlidingDoor;
}

void TESObjectDOOR::SetSlidingDoor(bool abVal) {
	ucFlags.bSlidingDoor = abVal;
}

// GAME - 0x5194D0
bool TESObjectDOOR::IsRandomDoor() const {
	return !kRandomTeleports.IsEmpty();
}

// GAME - 0x519500
bool TESObjectDOOR::RandomlyTeleportsTo(const TESForm* apSpace) const {
	return ThisCall<bool>(0x519500, this, apSpace);
}

// GAME - 0x5195E0
TESObjectREFR* TESObjectDOOR::FindRandomTeleportTarget(TESObjectREFR* apStartDoor, TESObjectREFR* apActionRef) const {
	return ThisCall<TESObjectREFR*>(0x5195E0, this, apStartDoor, apActionRef);
}

// GAME - 0x871A30
const BSSimpleList<TESForm*>* TESObjectDOOR::GetRandomTeleportList() const {
	return &kRandomTeleports;
}

// GAME - 0x871A30
BSSimpleList<TESForm*>* TESObjectDOOR::GetRandomTeleportList() {
	return &kRandomTeleports;
}

// GAME - 0x519550
void TESObjectDOOR::ClearRandomTeleportList() {
	ThisCall(0x519550, this);
}

// GAME - 0x519570
bool TESObjectDOOR::CanBeRandomTeleport(const TESForm* apSpace) {
	return CdeclCall<bool>(0x519570, apSpace);
}

// GAME - 0x518F00
bool TESObjectDOOR::CanActorIgnoreLock(TESObjectREFR* apDoor, Actor* apActor, bool abActivate, bool abMovement) {
	return CdeclCall<bool>(0x518F00, apDoor, apActor, abActivate, abMovement);
}

// GAME - 0x518E60
bool TESObjectDOOR::CanActorIgnoreLock(const DoorLock* apLock, Actor* apActor, TESObjectREFR* apDoor, bool abActivate, bool abMovement) {
	return CdeclCall<bool>(0x518E60, apLock, apActor, apDoor, abActivate, abMovement);
}
