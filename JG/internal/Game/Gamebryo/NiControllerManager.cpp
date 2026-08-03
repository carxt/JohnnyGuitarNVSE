#include "NiControllerManager.hpp"

// GAME - 0xA2EFA0
// GECK - 0x7DE270
NiControllerManager* NiControllerManager::Create(NiAVObject* apTarget, bool abCumulativeAnimations) {
#ifdef GAME
	return NiCreate<NiControllerManager, 0xA2EFA0>(apTarget, abCumulativeAnimations);
#else
	return NiCreate<NiControllerManager, 0x7DE270>(apTarget, abCumulativeAnimations);
#endif
}

// GAME - 0x490D90
// GECK - 0x50DA20
NiAVObject* NiControllerManager::GetAccumRoot() const {
#ifdef GAME
	return ThisCall<NiAVObject*>(0x490D90, this);
#else
	return ThisCall<NiAVObject*>(0x50DA20, this);
#endif
}

// GAME - 0x47A520
NiControllerSequence* NiControllerManager::GetSequenceByName(const NiFixedString& arName) const {
	NiControllerSequence* pOut = nullptr;
	m_kIndexMap.GetAt(arName.m_kHandle, pOut);
	return pOut;
}

// GAME - 0x495D20
NiControllerSequence* NiControllerManager::GetSequenceAt(uint32_t auiIndex) const {
	return m_kSequenceArray.GetAt(auiIndex);
}

// GAME - 0x495D00
uint32_t NiControllerManager::GetSequenceCount() const {
	return m_kSequenceArray.GetSize();
}

// GAME - 0xA2E1B0
// GECK - 0x7DD450
bool NiControllerManager::Morph(NiControllerSequence* apSourceSequence, NiControllerSequence* apDestSequence, float afDuration, int32_t aiPriority, float afSourceWeight, float afDestWeight) {
#ifdef GAME
	return ThisCall<bool>(0xA2E1B0, this, apSourceSequence, apDestSequence, afDuration, aiPriority, afSourceWeight, afDestWeight);
#else
	return ThisCall<bool>(0x7DD450, this, apSourceSequence, apDestSequence, afDuration, aiPriority, afSourceWeight, afDestWeight);
#endif
}

// GAME - 0xA2E280
// GECK - 0x7DD520
bool NiControllerManager::CrossFade(NiControllerSequence* apSourceSequence, NiControllerSequence* apDestSequence, float afDuration, int32_t aiPriority, bool abStartOver, float afWeight, NiControllerSequence* apTimeSyncSeq) {
#ifdef GAME
	return ThisCall<bool>(0xA2E280, this, apSourceSequence, apDestSequence, afDuration, aiPriority, abStartOver, afWeight, apTimeSyncSeq);
#else
	return ThisCall<bool>(0x7DD520, this, apSourceSequence, apDestSequence, afDuration, aiPriority, abStartOver, afWeight, apTimeSyncSeq);
#endif
}

// GAME - 0xA2F170
// GECK - 0x7DE440
NiControllerSequence* NiControllerManager::CreateTempBlendSequence(NiControllerSequence* apSequence, NiControllerSequence* apSequenceToSynchronize) {
#ifdef GAME
	return ThisCall<NiControllerSequence*>(0xA2F170, this, apSequence, apSequenceToSynchronize);
#else
	return ThisCall<NiControllerSequence*>(0x7DE440, this, apSequence, apSequenceToSynchronize);
#endif
}

// GAME - 0xA2F800
// GECK - 0x7DEAD0
bool NiControllerManager::BlendFromPose(NiControllerSequence* apSequence, float afDestFrame, float afDuration, int32_t aiPriority, NiControllerSequence* apSequenceToSynchronize) {
#ifdef GAME
	return ThisCall<bool>(0xA2F800, this, apSequence, afDestFrame, afDuration, aiPriority, apSequenceToSynchronize);
#else
	return ThisCall<bool>(0x7DEAD0, this, apSequence, afDestFrame, afDuration, aiPriority, apSequenceToSynchronize);
#endif
}

// GAME - 0xA2F0C0
// GECK - 0x7DE390
bool NiControllerManager::AddSequence(NiControllerSequence* apSequence, const NiFixedString& arName, bool abStoreTargets) {
#ifdef GAME
	return ThisCall<bool>(0xA2F0C0, this, apSequence, &arName, abStoreTargets);
#else
	return ThisCall<bool>(0x7DE390, this, apSequence, &arName, abStoreTargets);
#endif
}

// GAME - 0xA2EC50
// GECK - 0x7DDE90
void NiControllerManager::RemoveSequence(NiControllerSequence* apSequence) {
#ifdef GAME
	ThisCall(0xA2EC50, this, apSequence);
#else
	ThisCall(0x7DDE90, this, apSequence);
#endif
}

// GAME - 0xA2E7D0
// GECK - 0x7DD940
void NiControllerManager::RemoveSequence(NiControllerSequence* apSequence, NiControllerSequencePtr& arOut) {
#ifdef GAME
	ThisCall(0xA2E7D0, this, apSequence, &arOut);
#else
	ThisCall(0x7DD940, this, apSequence, &arOut);
#endif
}

// GAME - 0x47AAB0
// GECK - 0x40F7F0
bool NiControllerManager::ActivateSequence(NiControllerSequence* apSequence, int32_t aiPriority, bool abStartOver, float afWeight, float afEaseInTime, NiControllerSequence* apTimeSyncSeq) {
#ifdef GAME
	return ThisCall<bool>(0x47AAB0, this, apSequence, aiPriority, abStartOver, afWeight, afEaseInTime, apTimeSyncSeq);
#else
	return ThisCall<bool>(0x40F7F0, this, apSequence, aiPriority, abStartOver, afWeight, afEaseInTime, apTimeSyncSeq);
#endif
}

// GAME - 0x47B220
// GECK - 0x40F820
bool NiControllerManager::DeactivateSequence(NiControllerSequence* apSequence, float afEaseOutTime) {
#ifdef GAME
	return ThisCall<bool>(0x47B220, this, apSequence, afEaseOutTime);
#else
	return ThisCall<bool>(0x40F820, this, apSequence, afEaseOutTime);
#endif
}

// GAME - 0xA2E420
// GECK - 0x7DD6C0
bool NiControllerManager::DeactivateTransSourceSequence(float afEaseOutTime) {
#ifdef GAME
	return ThisCall<bool>(0xA2E420, this, afEaseOutTime);
#else
	return ThisCall<bool>(0x7DD6C0, this, afEaseOutTime);
#endif
}

// GAME - 0x48FEF0
// GECK - 0x40F8F0
void NiControllerManager::DeactivateAll(float afEaseOutTime) {
#ifdef GAME
	ThisCall(0x48FEF0, this, afEaseOutTime);
#else
	ThisCall(0x40F8F0, this, afEaseOutTime);
#endif
}
