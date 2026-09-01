#include "BSXFlags.hpp"

// GAME - 0x448A60
uint32_t BSXFlags::GetFlags(uint32_t auiFlags) const {
	return reinterpret_cast<const Bitfield32&>(m_iValue).Get(auiFlags);
}

// GAME - 0x519230
void BSXFlags::SetFlags(uint32_t auiFlags, bool abVal) {
	reinterpret_cast<Bitfield32&>(m_iValue).Set(auiFlags, abVal);
}

// GAME - 0x519270
void BSXFlags::ClearFlags(uint32_t auiFlags) {
	reinterpret_cast<Bitfield32&>(m_iValue).Clear(auiFlags);
}

// GAME - 0x549690
bool BSXFlags::GetAnimated() const {
	return GetFlags(ANIMATED);
}

bool BSXFlags::GetHavok() const {
	return GetFlags(HAVOK);
}

bool BSXFlags::GetRagdoll() const {
	return GetFlags(RAGDOLL);
}

bool BSXFlags::GetComplex() const {
	return GetFlags(COMPLEX);
}

// GAME - 0x448A40
bool BSXFlags::GetAddon() const {
	return GetFlags(ADDON);
}

// GAME - 0x4B5FA0
bool BSXFlags::GetEditorMarker() const {
	return GetFlags(EDITOR_MARKER);
}

bool BSXFlags::GetDynamic() const {
	return GetFlags(DYNAMIC);
}

bool BSXFlags::GetArticulated() const {
	return GetFlags(ARTICULATED);
}

// GAME - 0x8978D0
bool BSXFlags::GetIKTarget() const {
	return GetFlags(IK_TARGET);
}

const NiFixedString& BSXFlags::GetTag() {
	return *pTag;
}

// GAME - 0xC43490
// GECK - 0x9DFDD0
BSXFlags* BSXFlags::Find(const NiObjectNET* apObject) {
#ifdef GAME
	return CdeclCall<BSXFlags*>(0xC43490, apObject);
#else
	return CdeclCall<BSXFlags*>(0x9DFDD0, apObject);
#endif
}

// GAME - 0x624B70
uint32_t BSXFlags::GetFlags(const NiObjectNET* apObject, uint32_t auiFlags) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x624B70, apObject, auiFlags);
#else
	const BSXFlags* pFlags = Find(apObject);
	return pFlags ? pFlags->GetFlags(auiFlags) : 0;
#endif
}
