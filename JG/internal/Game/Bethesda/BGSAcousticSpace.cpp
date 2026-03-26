#include "BGSAcousticSpace.hpp"

// GAME - 0x58A200
bool BGSAcousticSpace::IsInterior() const {
    return bIsInterior;
}

// GAME - 0x792780
void BGSAcousticSpace::SetInterior(bool abInterior) {
    bIsInterior = abInterior;
}

// GAME - 0x5F36F0
TESSound* BGSAcousticSpace::GetDawnSound() const {
    return pDawnSound;
}

// GAME - 0x8D7DC0
void BGSAcousticSpace::SetDawnSound(TESSound* apSound) {
	pDawnSound = apSound;
}

// GAME - 0x9E32D0
TESSound* BGSAcousticSpace::GetNoonSound() const {
    return pNoonSound;
}

// GAME - 0x40E500
void BGSAcousticSpace::SetNoonSound(TESSound* apSound) {
	pNoonSound = apSound;
}

// GAME - 0x639B40
TESSound* BGSAcousticSpace::GetDuskSound() const {
    return pDuskSound;
}

// GAME - 0x409480
void BGSAcousticSpace::SetDuskSound(TESSound* apSound) {
	pDuskSound = apSound;
}

// GAME - 0x8D6F30
TESSound* BGSAcousticSpace::GetNightSound() const {
    return pNightSound;
}

// GAME - 0x87CE80
void BGSAcousticSpace::SetNightSound(TESSound* apSound) {
	pNightSound = apSound;
}

// GAME - 0x8041A0
TESSound* BGSAcousticSpace::GetWallaSound() const {
    return pWallaSound;
}

// GAME - 0x8D8040
void BGSAcousticSpace::SetWallaSound(TESSound* apSound) {
	pWallaSound = apSound;
}

// GAME - 0x68A830
int32_t BGSAcousticSpace::GetWallaPopulation() const {
	return iWallaPopulation;
}

// GAME - 0x58E430
void BGSAcousticSpace::SetWallaPopulation(int32_t aiPopulation) {
	iWallaPopulation = aiPopulation;
}

// GAME - 0x6733E0
TESRegion* BGSAcousticSpace::GetRegion() const {
    return pRegion;
}

// GAME - 0x673400
void BGSAcousticSpace::SetRegion(TESRegion* apRegion) {
	pRegion = apRegion;
}

// GAME - 0x68A810
uint32_t BGSAcousticSpace::GetEnvironmentType() const {
    return eEnvironmentType;
}

// GAME - 0x589F50
void BGSAcousticSpace::SetEnvironmentType(uint32_t aeType) {
	eEnvironmentType = aeType;
}
