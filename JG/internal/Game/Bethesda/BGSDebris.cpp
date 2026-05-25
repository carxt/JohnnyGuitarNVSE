#include "BGSDebris.hpp"

// GAME - 0x4FA6F0
void BGSDebris::SpawnDebris(TESObjectCELL* apCell, const NiPoint3& arLocation, uint32_t auiParticleCount, float afScale) {
	ThisCall(0x4FA6F0, this, apCell, &arLocation, auiParticleCount, afScale);
}
