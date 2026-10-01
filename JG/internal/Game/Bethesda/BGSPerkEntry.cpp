#include "BGSPerkEntry.hpp"

// GAME - 0x4F1540
uint8_t BGSPerkEntry::GetRank() const {
    return ucRank;
}

// GAME - 0x4F6DE0
uint8_t BGSPerkEntry::GetPriority() const {
    return ucPriority;
}
