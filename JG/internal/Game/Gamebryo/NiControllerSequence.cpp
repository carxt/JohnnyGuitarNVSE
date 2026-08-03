#include "NiControllerSequence.hpp"

// GAME - 0xA32A10
// GECK - 0x7DA660
NiControllerSequence* NiControllerSequence::Create(const NiFixedString& arName, uint32_t auiArraySize, uint32_t auiArrayGrowBy) {
#ifdef GAME
	return NiCreate<NiControllerSequence, 0xA32A10>(&arName, auiArraySize, auiArrayGrowBy);
#else
	return NiCreate<NiControllerSequence, 0x7DA660>(&arName, auiArraySize, auiArrayGrowBy);
#endif
}

// GAME - 0xA34F20
// GECK - 0x7DCB30
bool NiControllerSequence::Activate(char acPriority, bool abStartOver, float afWeight, float afEaseInTime, NiControllerSequence* apTimeSyncSeq, bool asbTransition) {
#ifdef GAME
    return ThisCall<bool>(0xA34F20, this, acPriority, abStartOver, afWeight, afEaseInTime, apTimeSyncSeq, asbTransition);
#else
	return ThisCall<bool>(0x7DCB30, this, acPriority, abStartOver, afWeight, afEaseInTime, apTimeSyncSeq, asbTransition);
#endif
}

// GAME - 0xA351D0
// GECK - 0x7DCDE0
bool NiControllerSequence::StartMorph(NiControllerSequence* apDestSequence, float afDuration, int32_t aiPriority, float afSourceWeight, float afDestWeight) {
#ifdef GAME
	return ThisCall<bool>(0xA351D0, this, apDestSequence, afDuration, aiPriority, afSourceWeight, afDestWeight);
#else
	return ThisCall<bool>(0x7DCDE0, this, apDestSequence, afDuration, aiPriority, afSourceWeight, afDestWeight);
#endif
}

// GAME - 0xA350D0
// GECK - 0x7DCCE0
bool NiControllerSequence::StartBlend(NiControllerSequence* apDestSequence, float afDuration, float afDestFrame, int32_t aiPriority, float afSourceWeight, float afDestWeight, NiControllerSequence* apTimeSyncSeq) {
#ifdef GAME
	return ThisCall<bool>(0xA350D0, this, apDestSequence, afDuration, afDestFrame, aiPriority, afSourceWeight, afDestWeight, apTimeSyncSeq);
#else
	return ThisCall<bool>(0x7DCCE0, this, apDestSequence, afDuration, afDestFrame, aiPriority, afSourceWeight, afDestWeight, apTimeSyncSeq);
#endif
}

void NiControllerSequence::GetInterpInfoAt(uint32_t auiIndex, const char*& pcAVObjectName, const char*& pcPropertyType, const char*& pcCtlrType, const char*& pcCtlrID, const char*& pcInterpolatorID) {
    IDTag& kTag = m_pkIDTagArray[auiIndex];
    pcAVObjectName = kTag.m_kAVObjectName.m_kHandle;
    pcPropertyType = kTag.m_kPropertyType.m_kHandle;
    pcCtlrType = kTag.m_kCtlrType.m_kHandle;
    pcCtlrID = kTag.m_kCtlrID.m_kHandle;
    pcInterpolatorID = kTag.m_kInterpolatorID.m_kHandle;
}

// GAME - 0x5F5F80
NiAVObject* NiControllerSequence::GetAccumRoot() const {
    return m_pkAccumRoot;
}

// GAME - 0xA32BC0
// GECK - 0x7DA7D0
uint32_t NiControllerSequence::AddInterpolator(NiInterpolator* apInterpolator, IDTag& arTag, uint8_t aucPriority) {
#ifdef GAME
    return ThisCall<uint32_t>(0xA32BC0, this, apInterpolator, &arTag, aucPriority);
#else
	return ThisCall<uint32_t>(0x7DA7D0, this, apInterpolator, &arTag, aucPriority);
#endif
}

// GAME - 0x4937A0
NiInterpolator* NiControllerSequence::GetInterpolatorAt(uint32_t auiIndex) const {
    return m_pkInterpArray[auiIndex].m_spInterpolator;
}

void NiControllerSequence::SetControllerAt(NiInterpController* apInterpCtlr, uint32_t auiIndex) {
	m_pkInterpArray[auiIndex].m_spInterpCtlr = apInterpCtlr;
}

void NiControllerSequence::ReplaceInterpolatorAt(NiInterpolator* apInterp, uint32_t auiIndex) {
    m_pkInterpArray[auiIndex].m_spInterpolator = apInterp;
}

NiInterpController* NiControllerSequence::GetControllerAt(uint32_t auiIndex) const {
    return m_pkInterpArray[auiIndex].m_spInterpCtlr;
}

// GAME - 0x8D6F30
NiControllerManager* NiControllerSequence::GetOwner() const {
    return m_pkOwner;
}

bool NiControllerSequence::SetOwner(NiControllerManager* pkOwner) {
	return m_pkOwner = pkOwner;
}

// GAME - 0x413F40
const NiFixedString& NiControllerSequence::GetName() const {
    return m_kName;
}

// GAME - 0x43B9F0
// GECK - 0x818130
void NiControllerSequence::SetName(const NiFixedString& arName) {
#ifdef GAME
    ThisCall(0x43B9F0, this, &arName);
#else
    ThisCall(0x818130, this, &arName);
#endif
}

// GAME - 0xA32C70
// GECK - 0x7DA880
void NiControllerSequence::StoreTargets(NiAVObject* apRoot) {
#ifdef GAME
    ThisCall(0xA32C70, this, apRoot);
#else
	ThisCall(0x7DA880, this, apRoot);
#endif
}

// GAME - 0xA30970
// GECK - 0x7D8460
float NiControllerSequence::ComputeScaledTime(float afTime, bool abStoreLastTime) {
#ifdef GAME
    return ThisCall<float>(0xA30970, this, afTime, abStoreLastTime);
#else
	return ThisCall<float>(0x7D8460, this, afTime, abStoreLastTime);
#endif
}

// GAME - 0x8041A0
NiControllerSequence::AnimState NiControllerSequence::GetState() const {
    return m_eState;
}

// GAME - 0xA312D0
NiControllerSequence::IDTag::IDTag(const NiFixedString& arAVObjectName, const NiFixedString& arPropertyType, const NiFixedString& arCtlrType, const NiFixedString& arCtlrID, const NiFixedString& arInterpolatorID) {
    ClearValues();
    m_kAVObjectName     = arAVObjectName;
    m_kPropertyType     = arPropertyType;
    m_kCtlrType         = arCtlrType;
    m_kCtlrID           = arCtlrID;
    m_kInterpolatorID   = arInterpolatorID;
}

NiControllerSequence::IDTag::IDTag(const IDTag& arOther) {
    m_kAVObjectName     = arOther.m_kAVObjectName;
    m_kPropertyType     = arOther.m_kPropertyType;
    m_kCtlrType         = arOther.m_kCtlrType;
    m_kCtlrID           = arOther.m_kCtlrID;
    m_kInterpolatorID   = arOther.m_kInterpolatorID;
}

// GAME - 0xA30640
void NiControllerSequence::IDTag::ClearValues() {
    m_kAVObjectName     = nullptr;
    m_kPropertyType     = nullptr;
    m_kCtlrType         = nullptr;
    m_kCtlrID           = nullptr;
    m_kInterpolatorID   = nullptr;
}
