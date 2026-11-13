#include "MediaSet.hpp"

MediaSet::Type MediaSet::GetType() const {
    return eType;
}

void MediaSet::SetType(Type aeType) {
    eType = aeType;
}

TESSound* MediaSet::GetSoundA() const {
    return pSoundA;
}

void MediaSet::SetSoundA(TESSound* apSound) {
    pSoundA = apSound;
}

TESSound* MediaSet::GetSoundB() const {
    return pSoundB;
}

void MediaSet::SetSoundB(TESSound* apSound) {
    pSoundB = apSound;
}
