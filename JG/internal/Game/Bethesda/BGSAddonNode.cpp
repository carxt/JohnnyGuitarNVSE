#include "BGSAddonNode.hpp"

// GAME - 0x68A830
uint32_t BGSAddonNode::GetIndex() const {
	return uiIndex;
}

// GAME - 0x58E430
void BGSAddonNode::SetIndex(uint32_t auiIndex) {
	uiIndex = auiIndex;
}

// GAME - 0x6A1B60
TESSound* BGSAddonNode::GetSound() const {
	return pSound;
}

void BGSAddonNode::SetSound(TESSound* apSound) {
	pSound = apSound;
}

// GAME - 0x448BF0
bool BGSAddonNode::IsMasterParticleSystem() const {
	return kData.ucFlags.bIsMasterParticleSystem;
}

// GAME - 0x45A1A0
uint16_t BGSAddonNode::GetMasterParticleCap() const {
	return kData.usMasterParticleCap;
}


// GAME - 0x59E300
uint32_t BGSAddonNode::GetParticleSystemIndex() const {
	return uiParticleSystemIndex;
}