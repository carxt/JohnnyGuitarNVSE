#include "NiTransform.hpp"

// GAME - 0x476A80
NiTransform::NiTransform() {
}

// GAME - 0x62C250
// GECK - 0x5D6EC0
NiTransform NiTransform::operator*(const NiTransform& arOther) const noexcept {
	NiTransform kResult;
	kResult.m_fScale = m_fScale * arOther.m_fScale;
	kResult.m_kRotate = m_kRotate * arOther.m_kRotate;
	kResult.m_kTranslate = m_kTranslate + m_fScale * (m_kRotate * arOther.m_kTranslate);
	return kResult;
};

// GAME - 0xA86BF0
// GECK - 0x82E830
void NiTransform::MakeIdentity() noexcept {
	m_kRotate		= NiMatrix3::IDENTITY;
	m_kTranslate	= NiPoint3::ZERO;
	m_fScale		= 1.f;
}

// GAME - 0x4B4880
// GECK - 0x488080
void NiTransform::Invert(NiTransform& arDest) const noexcept {
	arDest.m_kRotate = m_kRotate.Transpose();
	arDest.m_fScale = 1.f / m_fScale;
	arDest.m_kTranslate = arDest.m_fScale * (arDest.m_kRotate * -m_kTranslate);
}