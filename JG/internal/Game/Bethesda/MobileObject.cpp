#include "MobileObject.hpp"
#include "CFilter.hpp"

// GAME - 0x8D8520
BaseProcess* MobileObject::GetCurrentAIProcess() const {
    return pCurrentProcess;
}

// GAME - 0x407800
void MobileObject::SetCurrentAIProcess(BaseProcess* apProcess) {
	pCurrentProcess = apProcess;
}

// GAME - 0x9344A0
TESPackage* MobileObject::GetCurrentPackage() const {
	return ThisCall<TESPackage*>(0x9344A0, this);
}

// GAME - 0x931850
PROCESS_TYPE MobileObject::GetCurrentProcessType() const {
	return ThisCall<PROCESS_TYPE>(0x931850, this);
}

// GAME - 0x9334B0
PROCESS_TYPE MobileObject::GetDesiredProcessLevel() const {
	return ThisCall<PROCESS_TYPE>(0x9334B0, this);
}

float MobileObject::GetLastTimeProcessed() const {
    if (pCurrentProcess)
        return pCurrentProcess->GetLastTimeProcessed();
    else
        return -1.f;
}

// GAME - 0x4FD380
MobileObject* MobileObject::GetDialogueItemTarget() const {
	return pDialogueItemTarget;
}

// GAME - 0x57BD60
void MobileObject::SetDialogueItemTarget(MobileObject* apTarget) {
	pDialogueItemTarget = apTarget;
}

// GAME - 0x574900
bool MobileObject::IsTalkingActivator() const { 
    return bTalkingActivator; 
}

// GAME - 0x898280
void MobileObject::SetTalkingActivator(bool abVal) {
	bTalkingActivator = abVal;
}

// GAME - 0x5E3FA0
TESObjectREFR* MobileObject::GetTalkingActivator() const { 
    return pTalkingActivator; 
}

// GAME - 0x4FBF00
void MobileObject::SetTalkingActivatorRef(TESObjectREFR* apRef) {
	pTalkingActivator = apRef;
}

// GAME - 0x4BC4A0
void MobileObject::SetSoundCallBack(int8_t acCallback) {
	cSoundCallbackSet = acCallback;
}

// GAME - 0x936AA0
void MobileObject::SetSoundCallBackSuccess(bool abSuccess) {
	bSoundCallbackSuccess = abSuccess;
}

// GAME - 0x5A4520
bool MobileObject::GetShouldUseEmotionAnimation() const {
    return bUseEmotion;
}

// GAME - 0x8A5CF0
void MobileObject::SetShouldUseEmotionAnimation(bool abVal) {
	bUseEmotion = abVal;
}

// GAME - 0x437BB0
bool MobileObject::GetRunsInLow() const {
    return bRunsInLow;
}

// GAME - 0x931ED0
CFilter MobileObject::GetCollisionFilter() const {
	return ThisCall<CFilter>(0x931ED0, this);
}

// GAME - 0x9306D0
bhkCharacterController* MobileObject::GetCharController() const {
	return ThisCall<bhkCharacterController*>(0x9306D0, this);
}

// GAME - 0x86D490
void MobileObject::SetRotation(const NiPoint3& arRotation) {
	ThisCall(0x86D490, this, &arRotation);
}

// GAME - 0x931FB0
void MobileObject::SetChaseBip(bool abVal) {
    ThisCall(0x931FB0, this, abVal);
}

// GAME - 0x936DA0
float MobileObject::GetActualHeading() const {
    return ThisCall<float>(0x936DA0, this);
}

// GAME - 0x931D30
void MobileObject::ModHeading(float afModAngle) {
	ThisCall(0x931D30, this, afModAngle);
}

// GAME - 0x931D70
float MobileObject::GetLooking() const {
	return ThisCall<float>(0x931D70, this);
}

// GAME - 0x931D90
void MobileObject::SetLooking(float afAngle) {
	ThisCall(0x931D90, this, afAngle);
}

// GAME - 0x931E50
void MobileObject::ModLooking(float afModAngle) {
	ThisCall(0x931E50, this, afModAngle);
}

// GAME - 0x9337B0
bool MobileObject::IsInAir() const {
    return ThisCall<bool>(0x9337B0, this);
}

// GAME - 0x92F160
bool MobileObject::IsTalking() const {
    return ThisCall<bool>(0x92F160, this);
}

// GAME - 0x9336C0
bool MobileObject::IsinDialogue() const {
	return ThisCall<bool>(0x9336C0, this);
}

// GAME - 0x933840
bool MobileObject::IsInDialogueWithPlayer() const {
    return ThisCall<bool>(0x933840, this);
}

// GAME - 0x9316C0
void MobileObject::SetPackageStartLocationFromCurrentLocation() {
	ThisCall(0x9316C0, this);
}
