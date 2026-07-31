#include "NiAVObject.hpp"
#include "NiBound.hpp"

// GAME - 0x6A9540
const NiTransform& NiAVObject::GetLocalTransform() const {
	return m_kLocal;
}

// GAME - 0x461130
const NiTransform& NiAVObject::GetWorldTransform() const {
	return m_kWorld;
}

const float NiAVObject::GetLocalScale() const {
	return m_kLocal.m_fScale;
}

// GAME - 0x440490
void NiAVObject::SetLocalScale(float afScale) {
	m_kLocal.m_fScale = std::abs(afScale);
}

const float NiAVObject::GetWorldScale() const {
	return m_kWorld.m_fScale;
}

void NiAVObject::SetWorldScale(float afScale) {
	m_kWorld.m_fScale = std::abs(afScale);
}

// GAME - 0x43C490
const NiPoint3& NiAVObject::GetLocalTranslate() const {
	return m_kLocal.m_kTranslate;
}

// GAME - 0x440460
void NiAVObject::SetLocalTranslate(const NiPoint3& arPos) {
	m_kLocal.m_kTranslate = arPos;
}

// GAME - 0x4BC1F0
void NiAVObject::SetLocalTranslate(float afX, float afY, float afZ) {
	m_kLocal.m_kTranslate = { afX, afY, afZ };
}

const NiPoint3& NiAVObject::GetWorldTranslate() const {
	return m_kWorld.m_kTranslate;
}

// GAME - 0x4F00E0
void NiAVObject::SetWorldTranslate(const NiPoint3& arPos) {
	m_kWorld.m_kTranslate = arPos;
}

// GAME - 0x6A9540
const NiMatrix3& NiAVObject::GetLocalRotate() const {
	return m_kLocal.m_kRotate;
}

// GAME - 0x43FA80
void NiAVObject::SetLocalRotate(const NiMatrix3& arRot) {
	m_kLocal.m_kRotate = arRot;
}

void NiAVObject::SetLocalRotate(float afX, float afY, float afZ) {
	m_kLocal.m_kRotate.FromEulerAnglesXYZ(afX, afY, afZ);
}

// GAME - 0x6404B0
void NiAVObject::SetLocalRotate(float afAngle, float afX, float afY, float afZ) {
	m_kLocal.m_kRotate.MakeRotation(afAngle, afX, afY, afZ);
}

void NiAVObject::SetLocalRotateDeg(float afX, float afY, float afZ) {
	m_kLocal.m_kRotate.FromEulerAnglesXYZ(afX * 0.0174527f, afY * 0.0174527f, afZ * 0.0174527f);
}

// GAME - Inlined at 0xA0B85A
void NiAVObject::SetRotateAboutCenter(const NiMatrix3& arRot, const NiPoint3& arCenter, const NiPoint3& arTranslate) {
	NiMatrix3 kLocalRot = GetLocalRotate();
	m_kLocal.m_kTranslate = (arTranslate + arCenter) - (kLocalRot * arCenter);
}

// GAME - 0x461130
const NiMatrix3& NiAVObject::GetWorldRotate() const {
	return m_kWorld.m_kRotate;
}

// GAME - 0x688430
void NiAVObject::SetWorldRotate(const NiMatrix3& arRot) {
	m_kWorld.m_kRotate = arRot;
}

// GAME - 0x9611E0
NiNode* NiAVObject::GetParent() {
	return m_pkParent;
}

// GAME - 0x9611E0
const NiNode* NiAVObject::GetParent() const {
	return m_pkParent;
}

// GAME - 0xA59D00
// GECK - 0x80DE00
void NiAVObject::AttachParent(NiNode* apParent) {
#ifdef GAME
	ThisCall(0xA59D00, this, apParent);
#else
	ThisCall(0x80DE00, this, apParent);
#endif
}

// GAME - 0x50F5A0
// GECK - 0x80DEB0
void NiAVObject::DetachParent() {
	m_pkParent = nullptr;
}

// GAME - 0xA59D30
// GECK - 0x80DE30
NiProperty* NiAVObject::GetProperty(NiProperty::PropertyType aePropertyType) const {
#ifdef GAME
	return ThisCall<NiProperty*>(0xA59D30, this, aePropertyType);
#else
	return ThisCall<NiProperty*>(0x80DE30, this, aePropertyType);
#endif
}

// GAME - 0x439410
// GECK - 0x4121E0
void NiAVObject::AttachProperty(NiProperty* apProperty) {
#ifdef GAME
	ThisCall(0x439410, this, apProperty);
#else
	ThisCall(0x4121E0, this, apProperty);
#endif
}

// GAME - 0x654640
// GECK - 0x68D440
void NiAVObject::DetachProperty(NiProperty* apProperty) {
#ifdef GAME
	ThisCall(0x654640, this, apProperty);
#else
	ThisCall(0x68D440, this, apProperty);
#endif
}

// GAME - 0xA5B230
// GECK - 0x80F2B0
void NiAVObject::RemoveProperty(NiProperty::PropertyType aePropertyType) {
#ifdef GAME
	ThisCall(0xA5B230, this, aePropertyType);
#else
	ThisCall(0x80F2B0, this, aePropertyType);
#endif
}

// GAME - 0xA5AAC0
// GECK - 0x80EB40
void NiAVObject::RemoveProperty(NiProperty::PropertyType aePropertyType, NiPointer<NiProperty>& arRemovedProperty) {
#ifdef GAME
	ThisCall(0xA5AAC0, this, aePropertyType, &arRemovedProperty);
#else
	ThisCall(0x80EB40, this, aePropertyType, &arRemovedProperty);
#endif
}

// GAME - 0xA5A040
// GECK - 0x80E140
void NiAVObject::UpdateProperties() {
#ifdef GAME
	ThisCall(0xA5A040, this);
#else
	ThisCall(0x80E140, this);
#endif
}

// GAME - 0xA5A170
// GECK - 0x80E270
void NiAVObject::PushLocalProperties(NiPropertyState* apParentState, bool abCopyOnChange, NiPropertyState*& apOut) {
#ifdef GAME
	ThisCall(0xA5A170, this, apParentState, abCopyOnChange, &apOut);
#else
	ThisCall(0x80E270, this, apParentState, abCopyOnChange, &apOut);
#endif
}

// GAME - 0xA5A110
// GECK - 0x80E210
bool NiAVObject::HasPropertyController() const {
#ifdef GAME
	return ThisCall<bool>(0xA5A110, this);
#else
	return ThisCall<bool>(0x80E210, this);
#endif
}

// GAME - 0xA5A0E0
// GAME - 0x80E1E0
bool NiAVObject::HasTransformController() const {
#ifdef GAME
	return ThisCall<bool>(0xA5A0E0, this);
#else
	return ThisCall<bool>(0x80E1E0, this);
#endif
}

// GAME - 0x43D450
// GECK - 0x446A10
const NiBound& NiAVObject::GetWorldBound() const {
	return m_pWorldBound ? *m_pWorldBound : kNullBound;
}

// GAME - 0x5467E0
// GECK - 0x43D920
void NiAVObject::CreateBoundIfNone() {
#ifdef GAME
	ThisCall(0x5467E0, this);
#else
	ThisCall(0x43D920, this);
#endif
}

// GAME - 0x6838B0
bhkNiCollisionObject* NiAVObject::GetCollisionObject() const {
	return m_spCollisionObject;
}

// GAME - 0x62BC90
// GECK - 0x48A410
void NiAVObject::SetCollisionObject(bhkNiCollisionObject* apCollisionObject) {
#ifdef GAME
	ThisCall(0x62BC90, this, apCollisionObject);
#else
	ThisCall(0x48A410, this, apCollisionObject);
#endif
}

// GAME - 0xA59C60
// GECK - 0x80DD60
void NiAVObject::Update(NiUpdateData& arData) {
#ifdef GAME
	ThisCall(0xA59C60, this, &arData);
#else
	ThisCall(0x80DD60, this, &arData);
#endif
}

// GAME - 0xA59C90
// GECK - 0x80DD90
void NiAVObject::UpdateSelected(NiUpdateData& arData) {
#ifdef GAME
	ThisCall(0xA59C90, this, &arData);
#else
	ThisCall(0x80DD90, this, &arData);
#endif
}

void NiAVObject::DoSelectedUpdate(NiUpdateData& arData, uint32_t auiFlags) {
	if (GetSelectiveUpdate()) {
		if (GetSelectiveUpdateRigid())
			UpdateRigidDownwardPass(arData, auiFlags);
		else
			UpdateSelectedDownwardPass(arData, auiFlags);
	}
}

// GAME - 0xA68BF0
// GECK - 0x8243B0
void NiAVObject::UpdateWorldLoc() {
#ifdef GAME
	ThisCall(0xA68BF0, this);
#else
	ThisCall(0x8243B0, this);
#endif
}

// GAME - 0x4EFF50
// GECK - 0x539940
void NiAVObject::UpdateObjectControllers(NiUpdateData& arData, bool abUpdateProperties) {
#ifdef GAME
	ThisCall(0x4EFF50, this, &arData, abUpdateProperties);
#else
	ThisCall(0x539940, this, &arData, abUpdateProperties);
#endif

}

// GAME - 0xA59E00
// GECK - 0x80DF00
void NiAVObject::Cull(NiCullingProcess& arCuller) {
#ifdef GAME
	ThisCall(0xA59E00, this, &arCuller);
#else
	ThisCall(0x80DF00, this, &arCuller);
#endif
}

// GAME - 0x4B2960
bool NiAVObject::IsVisualObject() const {
	return m_pWorldBound && m_pWorldBound->m_iRadius;
}

bool NiAVObject::IsUnCulledVisualObject() const {
	return (GetAlwaysDraw() || IsVisualObject()) && !GetAppCulled();
}


// FLAGS

void NiAVObject::SetBit(uint32_t auiData, bool abVal) {
	m_uiFlags.Set(auiData, abVal);
}

bool NiAVObject::GetBit(uint32_t auiData) const {
	return m_uiFlags.IsSet(auiData);
}

// GAME - 0x450F90
// GECK - 0x44EF10
void NiAVObject::SetAppCulled(bool abVal) {
	m_uiFlags.bAppCulled = abVal;
}

// GAME - 0x456610
bool NiAVObject::GetAppCulled() const {
	return m_uiFlags.bAppCulled;
}

// GAME - 0x4902F0
void NiAVObject::SetSelectiveUpdate(bool abVal) {
	m_uiFlags.bSelUpdate = abVal;
}

// GAME - 0x4F0140
bool NiAVObject::GetSelectiveUpdate() const {
	return m_uiFlags.bSelUpdate;
}

void NiAVObject::SetSelectiveUpdateTransforms(bool abVal) {
	m_uiFlags.bSelUpdateTransforms = abVal;
}

bool NiAVObject::GetSelectiveUpdateTransforms() const {
	return m_uiFlags.bSelUpdateTransforms;
}

void NiAVObject::SetSelectiveUpdateControllers(bool abVal) {
	m_uiFlags.bSelUpdateController = abVal;
}

bool NiAVObject::GetSelectiveUpdateControllers() const {
	return m_uiFlags.bSelUpdateController;
}

void NiAVObject::SetSelectiveUpdateRigid(bool abVal) {
	m_uiFlags.bSelUpdateRigid = abVal;
}

bool NiAVObject::GetSelectiveUpdateRigid() const {
	return m_uiFlags.bSelUpdateRigid;
}

// GAME - 0x635FE0
void NiAVObject::SetDisplayObject(bool abVal) {
	m_uiFlags.bDisplayObject = abVal;
}

// GAME - 0x6366B0
bool NiAVObject::GetDisplayObject() const {
	return m_uiFlags.bDisplayObject;
}

void NiAVObject::SetDisableSorting(bool abVal) {
	m_uiFlags.bDisableSorting = abVal;
}

bool NiAVObject::GetDisableSorting() const {
	return m_uiFlags.bDisableSorting;
}

void NiAVObject::SetSelUpdTransformsOverride(bool abVal) {
	m_uiFlags.bSelUpdateTransformsOverride = abVal;
}

bool NiAVObject::GetSelUpdTransformsOverride() const {
	return m_uiFlags.bSelUpdateTransformsOverride;
}

void NiAVObject::SetTransIsIdentity(bool abVal) {
	m_uiFlags.bTransIsIdentity = abVal;
}

bool NiAVObject::GetTransIsIdentity() const {
	return m_uiFlags.bTransIsIdentity;
}

void NiAVObject::SetNoDecals(bool abVal) {
	m_uiFlags.bNoDecals = abVal;
}

// GAME - 0x4A19D0
bool NiAVObject::GetNoDecals() const {
	return m_uiFlags.bNoDecals;
}

// GAME - 0x546780
void NiAVObject::SetAlwaysDraw(bool abVal) {
	m_uiFlags.bAlwaysDraw = abVal;
	CreateBoundIfNone();
	if (abVal)
		m_pWorldBound->SetRadius(1.f);
}

// GAME - 0x876810
bool NiAVObject::GetAlwaysDraw() const {
	return m_uiFlags.bAlwaysDraw;
}

void NiAVObject::SetPreProcessedNode(bool abVal) {
	m_uiFlags.bPreprocessedNode = abVal;
}

bool NiAVObject::GetPreProcessedNode() const {
	return m_uiFlags.bPreprocessedNode;
}

// GAME - 0x5467C0
void NiAVObject::SetFixedBound(bool abVal) {
	m_uiFlags.bFixedBound = abVal;
}

bool NiAVObject::GetFixedBound() const {
	return m_uiFlags.bFixedBound;
}

// GAME - 0x476B00
void NiAVObject::SetFadedIn(bool abVal) {
	m_uiFlags.bFadedIn = abVal;
}

// GAME - 0x7FF8E0
bool NiAVObject::GetFadedIn() const {
	return m_uiFlags.bFadedIn;
}

// GAME - 0x49EE80
void NiAVObject::SetIgnoreFade(bool abVal) {
	m_uiFlags.bIgnoreFade = abVal;
}

// GAME - 0x5AA910
bool NiAVObject::GetIgnoreFade() const {
	return m_uiFlags.bIgnoreFade;
}

void NiAVObject::SetLODFadingOut(bool abVal) {
	m_uiFlags.bLODFadingOut = abVal;
}

bool NiAVObject::GetLODFadingOut() const {
	return m_uiFlags.bLODFadingOut;
}

// GAME - 0x4EF970
void NiAVObject::SetHasMovingSound(bool abVal) {
	m_uiFlags.bHasMovingSound = abVal;
}

// GAME - 0x570EA0
bool NiAVObject::GetHasMovingSound() const {
	return m_uiFlags.bHasMovingSound;
}

void NiAVObject::SetHasPropertyController(bool abVal) {
	m_uiFlags.bHasPropertyController = abVal;
}

// GAME - 0x4F0000
bool NiAVObject::GetHasPropertyController() const {
	return m_uiFlags.bHasPropertyController;
}

void NiAVObject::SetHasOrphanedBound(bool abVal) {
	m_uiFlags.bOrphanedBound = abVal;
}

bool NiAVObject::GetHasOrphanedBound() const {
	return m_uiFlags.bOrphanedBound;
}

// GAME - 0x8D6F10
void NiAVObject::SetNotVisible(bool abVal) {
	m_uiFlags.bNotVisible = abVal;
}

// GAME - 0x552470
bool NiAVObject::GetNotVisible() const {
	return m_uiFlags.bNotVisible;
}

// GAME - 0x5468B0
void NiAVObject::SetIgnoresPicking(bool abVal) {
	m_uiFlags.bIgnoresPicking = abVal;
}

bool NiAVObject::GetIgnoresPicking() const {
	return m_uiFlags.bIgnoresPicking;
}

void NiAVObject::SetWorldBoundChange(bool abVal) {
	m_uiFlags.bWorldBoundChange = abVal;
}

bool NiAVObject::GetWorldBoundChange() const {
	return m_uiFlags.bWorldBoundChange;
}

void NiAVObject::SetNoShadows(bool abVal) {
	m_uiFlags.bNoShadows = abVal;
}

bool NiAVObject::GetNoShadows() const {
	return m_uiFlags.bNoShadows;
}

// GAME - 0x938160
void NiAVObject::SetPlayerBone(bool abVal) {
	m_uiFlags.bPlayerBone = abVal;
}

bool NiAVObject::GetIsPlayerBone() const {
	return m_uiFlags.bPlayerBone;
}

// GAME - 0x4F2620
void NiAVObject::SetRelevantImposter(bool abVal) {
	m_uiFlags.bRelevantImposter = abVal;
}

bool NiAVObject::GetRelevantImposter() const {
	return m_uiFlags.bRelevantImposter;
}

// GAME - 0x868740
void NiAVObject::AddGarbageMark() {
	InterlockedExchange(&m_uiRefCount, m_uiRefCount | 0x40000000u);
}

// GAME - 0x868CE0
void NiAVObject::RemoveGarbageMark() {
	InterlockedExchange(&m_uiRefCount, m_uiRefCount & ~0x40000000u);
}