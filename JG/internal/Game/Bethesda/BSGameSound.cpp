#include "BSGameSound.hpp"

uint32_t BSGameSound::GetID() const {
    return uiSoundID;
}

bool BSGameSound::Is2DRadiusSound() const {
	return uiTypeFlags.b2D && uiTypeFlags.b2DRadius;
}

bool BSGameSound::Is3DSound() const {
	return uiTypeFlags.b3D;
}

bool BSGameSound::IsPlayable() const {
	return uiStateFlags.bReady && uiStateFlags.bValid;
}

bool BSGameSound::IsOneShot() const {
	return uiTypeFlags.bOneShot;
}

bool BSGameSound::IsSimpleLoop() const {
	return uiTypeFlags.bLoop;
}

bool BSGameSound::IsEnvelopeLoop() const {
	return uiTypeFlags.bEnvelopeSlow || uiTypeFlags.bEnvelopeFast;
}

bool BSGameSound::IsEnvelopeLoopFast() const {
	return uiTypeFlags.bEnvelopeFast;
}

bool BSGameSound::IsEnvelopeLoopSlow() const {
	return uiTypeFlags.bEnvelopeSlow;
}

bool BSGameSound::IsLoopingSound() const {
	return IsSimpleLoop() || IsEnvelopeLoop();
}

bool BSGameSound::IsInaudible() const {
	return uiStateFlags.bInaudible;
}

const char* BSGameSound::GetFileName() const {
	return cFileName;
}
