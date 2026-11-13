#include "Tile3D.hpp"

// GAME - 0x78A1F0
bool Tile3D::IsPlaying() const {
    return ThisCall<bool>(0x78A1F0, this);
}

// GAME - 0xA20CC0
bool Tile3D::PlaySequence(const char* apSequenceName) {
    return ThisCall<bool>(0xA20CC0, this, apSequenceName);
}

// GAME - 0xA20ED0
bool Tile3D::UpdateSequence(float afValue, bool abIsPercentage) {
    return ThisCall<bool>(0xA20ED0, this, afValue, abIsPercentage);
}
