#include "BGSMusicType.hpp"

// GAME - 0x830080
float BGSMusicType::GetAttenuation() const {
    if (fAttenuation <= 0.f)
        return fAttenuation;
    else
        return -fAttenuation;
}

void BGSMusicType::SetAttenuation(float afAttenuation) {
	fAttenuation = afAttenuation;
}

// GAME - 0x830050
bool BGSMusicType::GetLooping() const {
    return fAttenuation > 0.f;
}

// GAME - 0x591A40
const char* BGSMusicType::GetRandomEntry() const {
    return ThisCall<const char*>(0x591A40, this);
}
