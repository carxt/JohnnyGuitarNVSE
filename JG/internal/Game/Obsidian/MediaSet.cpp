#include "MediaSet.hpp"

MediaSet::Type MediaSet::GetType() const {
    return Type(eType);
}

void MediaSet::SetType(Type aeType) {
    eType = aeType;
}

TESSound* MediaSet::GetSound1() const {
    return pSound1;
}

void MediaSet::SetSound1(TESSound* apSound) {
    pSound1 = apSound;
}


TESSound* MediaSet::GetSound2() const {
    return pSound2;
}

void MediaSet::SetSound2(TESSound* apSound) {
    pSound2 = apSound;
}
