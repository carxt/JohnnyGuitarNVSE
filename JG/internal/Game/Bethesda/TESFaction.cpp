#include "TESFaction.hpp"

bool TESFaction::GetFlag(uint32_t auiFlag) const {
    return kData.uiFlags.Get(auiFlag);
}

// GAME - 0x47D720
bool TESFaction::GetPCExpelled() const {
    return kData.uiFlags.bPCExpelled;
}
