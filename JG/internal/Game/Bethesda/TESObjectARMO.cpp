#include "TESObjectARMO.hpp"

// GAME - 0x4BFD80
bool TESObjectARMO::GetModulatesVoice() const {
	return kData.ucFlags.bModulatesVoice;
}

// GAME - 0x514410
// GECK - 0x5F4B20
uint8_t TESObjectARMO::GetArmorWeight() const {
#ifdef GAME
	return ThisCall<uint8_t>(0x514410, this);
#else
	return ThisCall<uint8_t>(0x5F4B20, this);
#endif
}

// GAME - 0x4BE060
float TESObjectARMO::GetArmorRating() const {
	return GetCalculatedArmorRating();
}

// GAME - 0x4BE080
float TESObjectARMO::GetCalculatedArmorRating() const {
	return kData.usArmorRating / 100.f;
}

// GAME - 0x4BE180
float TESObjectARMO::GetDamageThreshold() const {
	return kData.fDamageThreshold;
}

// GAME - 0x512D40
TESSound* TESObjectARMO::GetFoleySound(FoleySound::Type aeType) const {
	return ThisCall<TESSound*>(0x512D40, this, aeType);
}
