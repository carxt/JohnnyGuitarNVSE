#include "BGSTalkingActivator.hpp"

// GAME - 0x4FEDC0
bool BGSTalkingActivator::IsRadioStation() const {
    return uiFormFlags.Get<FormFlags::RADIO_STATION>();
}

// GAME - 0x4FEE20
bool BGSTalkingActivator::IsNonPipboyRadioStation() const {
    return IsRadioStation() && GetNonPipboyRadio();
}

// GAME - 0x516BF0
TESObjectREFR* BGSTalkingActivator::GetTempRef() const {
    return pTempRef;
}

// GAME - 0x4FF0E0
void BGSTalkingActivator::SetTempRef(TESObjectREFR* apRef) {
    ThisCall(0x4FF0E0, this, apRef);
}

// GAME - 0x9185E0
BGSVoiceType* BGSTalkingActivator::GetVoiceType() const {
    return pVoiceType;
}

// GAME - 0x4FEBF0
void BGSTalkingActivator::SetVoiceType(BGSVoiceType* apVoiceType) {
    pVoiceType = apVoiceType;
}

// GAME - 0x4FF070
MobileObject* BGSTalkingActivator::AddMobileObjectExtra(TESObjectREFR* apRef) {
    return ThisCall<MobileObject*>(0x4FF070, this, apRef);
}

// GAME - 0x4FF150
void BGSTalkingActivator::AddRadioStation(TESObjectREFR* apRef) {
    CdeclCall(0x4FF150, apRef);
}

// GAME - 0x4FF1A0
void BGSTalkingActivator::GetRadioStationsInRangeOfRef(TESObjectREFR* apListener, BSSimpleList<TESObjectREFR*>* apRadioStations, BSSimpleList<float>* apDistances) {
    CdeclCall(0x4FF1A0, apListener, apRadioStations, apDistances);
}

// GAME - 0x4FEDE0
bool BGSTalkingActivator::IsRadioStation(const TESForm* apForm, int32_t aiData) {
    return CdeclCall<bool>(0x4FEDE0, apForm, aiData);
}

// GAME - 0x4FEE60
bool BGSTalkingActivator::IsNonPipboyRadioStation(const TESForm* apForm, int32_t aiData) {
    return CdeclCall<bool>(0x4FEE60, apForm, aiData);
}
