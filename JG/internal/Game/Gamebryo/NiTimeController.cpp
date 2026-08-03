#include "NiTimeController.hpp"

void NiTimeController::SetAnimType(AnimType aeType) {
	m_usFlags.eAnimType = aeType;
	SetActive(aeType == AnimType::APP_TIME);
}

NiTimeController::AnimType NiTimeController::GetAnimType() const {
	return static_cast<AnimType>(m_usFlags.eAnimType);
}

void NiTimeController::SetCycleType(CycleType aeType) {
	m_usFlags.eCycleType = aeType;
}

NiTimeController::CycleType NiTimeController::GetCycleType() const {
	return static_cast<CycleType>(m_usFlags.eCycleType);
}

// GAME - 0x47AA40
void NiTimeController::SetActive(bool abActive) {
	m_usFlags.bActive = abActive;
}

// GAME - 0x4F05A0
bool NiTimeController::GetActive() const {
	return m_usFlags.bActive;
}

// GAME - 0x566930
void NiTimeController::SetComputeScaledTime(bool abComputeScaledTime) {
	m_usFlags.bComputeScaledTime = abComputeScaledTime;
}

bool NiTimeController::GetComputeScaledTime() const {
	return m_usFlags.bComputeScaledTime;
}

// GAME - 0xA36250
// GECK - 0x7E75E0
bool NiTimeController::DontDoUpdate(float afTime) {
#ifdef GAME
	return ThisCall<bool>(0xA36250, this, afTime);
#else
	return ThisCall<bool>(0x7E75E0, this, afTime);
#endif
}

NiTimeController* NiTimeController::GetNext() const { 
	return m_spNext; 
}

void NiTimeController::SetNext(NiTimeController* apNext) { 
	m_spNext = apNext; 
}

// GAME - 0xA6D2D0
void NiTimeController::StartAnimations(NiAVObject* apObject) {
#ifdef GAME
	CdeclCall(0xA6D2D0, apObject);
#else
	StartAnimations(apObject, -FLT_MAX);
#endif
}

// GAME - 0xA6D390
// GECK - 0x828430
void NiTimeController::StartAnimations(NiAVObject* apObject, float afTime) {
#ifdef GAME
	CdeclCall(0xA6D390, apObject, afTime);
#else
	CdeclCall(0x828430, apObject, afTime);
#endif
}

void NiTimeController::SetManagerControlledBit(bool abManagerControlled) {
	m_usFlags.bManagerControlled = abManagerControlled;
}

bool NiTimeController::GetManagerControlledBit() const {
	return m_usFlags.bManagerControlled;
}
