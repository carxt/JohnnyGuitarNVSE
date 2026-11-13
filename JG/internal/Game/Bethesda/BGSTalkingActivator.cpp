#include "BGSTalkingActivator.hpp"

// GAME - 0x4FEDC0
bool BGSTalkingActivator::IsRadioStation() const {
#ifdef GAME
    return ThisCall<bool>(0x4FEDC0, this);
#else
    return uiFormFlags.Get<FormFlags::RADIO_STATION>();
#endif
}

// GAME - 0x4FEE20
bool BGSTalkingActivator::IsNonPipboyRadioStation() const {
#ifdef GAME
    return ThisCall<bool>(0x4FEE20, this);
#else
    return IsRadioStation() && GetNonPipboyRadio();
#endif
}

// GAME - 0x516BF0
TESObjectREFR* BGSTalkingActivator::GetTempRef() const {
    return pTempRef;
}

// GAME - 0x4FF0E0
void BGSTalkingActivator::SetTempRef(TESObjectREFR* apRef) {
#ifdef GAME
    ThisCall(0x4FF0E0, this, apRef);
#else
    pTempRef = apRef;
#endif
}

// GAME - 0x9185E0
BGSVoiceType* BGSTalkingActivator::GetVoiceType() const {
    return pVoiceType;
}

// GAME - 0x4FEBF0
void BGSTalkingActivator::SetVoiceType(BGSVoiceType* apVoiceType) {
    pVoiceType = apVoiceType;
}

#ifdef GAME
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
#endif

// GAME - 0x4FEDE0
// GECK - 0x5DB640
bool BGSTalkingActivator::IsRadioStation(const TESForm* apForm, int32_t aiData) {
#ifdef GAME
    return CdeclCall<bool>(0x4FEDE0, apForm, aiData);
#else
    return CdeclCall<bool>(0x5DB640, apForm, aiData);
#endif
}

// GAME - 0x4FEE60
bool BGSTalkingActivator::IsNonPipboyRadioStation(const TESForm* apForm, int32_t aiData) {
#ifdef GAME
    return CdeclCall<bool>(0x4FEE60, apForm, aiData);
#else
    if (apForm && apForm->GetFormType() == FORM_TYPE::BGSTalkingActivator) {
        const BGSTalkingActivator* pActivator = static_cast<const BGSTalkingActivator*>(apForm);
        if (pActivator->IsRadioStation())
            return pActivator->IsNonPipboyRadioStation();
    }
    return false;
#endif
}
