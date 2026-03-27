#include "TESObjectACTI.hpp"

// GAME - 0x5110E0
BSString TESObjectACTI::GetActivationPrompt() const {
	return strActivationPrompt;
}

// GAME - 0x510EA0
void TESObjectACTI::SetActivationPrompt(BSString aPrompt) {
	strActivationPrompt.Set(aPrompt);
}

void TESObjectACTI::SetDangerous(bool abVal) {
	uiFormFlags.Set(FormFlags::DANGEROUS, abVal);
}

bool TESObjectACTI::GetNoVoiceFilter() const {
	return uiFormFlags.IsSet(FormFlags::NO_VOICE_FILTER);
}

void TESObjectACTI::SetNoVoiceFilter(bool abVal) {
	uiFormFlags.Set(FormFlags::NO_VOICE_FILTER, abVal);
}

// GAME - 0x5113D0
bool TESObjectACTI::GetNonPipboyRadio() const {
	return uiFormFlags.IsSet(FormFlags::NON_PIPBOY_RADIO);
}

void TESObjectACTI::SetNonPipboyRadio(bool abVal) {
	uiFormFlags.Set(FormFlags::NON_PIPBOY_RADIO, abVal);
}

// GAME - 0x511370
void TESObjectACTI::SetContinuousBroadcast(bool abVal) {
	ThisCall(0x511370, this, abVal);
}

// GAME - 0x4FD3A0
TESSound* TESObjectACTI::GetLoopingSound() const {
    return pSoundLoop;
}

// GAME - 0x4FEBB0
void TESObjectACTI::SetLoopingSound(TESSound* apSound) {
	pSoundLoop = apSound;
}

// GAME - 0x407820
TESSound* TESObjectACTI::GetActivateSound() const {
	return pSoundActivate;
}

// GAME - 0x442A80
void TESObjectACTI::SetActivateSound(TESSound* apSound) {
	pSoundActivate = apSound;
}

// GAME - 0x407840
TESSound* TESObjectACTI::GetRadioTemplate() const {
	return pRadioTemplate;
}

// GAME - 0x4FEBD0
void TESObjectACTI::SetRadioTemplate(TESSound* apSound) {
	pRadioTemplate = apSound;
}

// GAME - 0x8AC890
void TESObjectACTI::SetWaterType(TESWaterForm* apWater) {
	pWaterForm = apWater;
}

// GAME - 0x4FD3C0
BGSTalkingActivator* TESObjectACTI::GetRadioStation() const {
	return pRadioStation;
}

// GAME - 0x4FB090
void TESObjectACTI::SetRadioStation(BGSTalkingActivator* apStation) {
	pRadioStation = apStation;
}