#include "NiPlane.hpp"

// GAME - 0xA69940
NiPlane::NiPlane() : m_kNormal(NiPoint3::ZERO), m_fConstant(0.0f) {}

// GAME - 0xA69970
NiPlane::NiPlane(const NiPoint3& arNormal, float afConstant) : m_kNormal(arNormal), m_fConstant(afConstant) {}

// GAME - 0xA69990
NiPlane::NiPlane(const NiPoint3& arNormal, const NiPoint3& arPoint) : m_kNormal(arNormal), m_fConstant(arNormal.Dot(arPoint)) {}

// GAME - 0xA699D0
NiPlane::NiPlane(const NiPoint3& arPoint0, const NiPoint3& arPoint1, const NiPoint3& arPoint2) {
	NiPoint3 kDif1 = arPoint1 - arPoint0;
	NiPoint3 kDif2 = arPoint2 - arPoint1;
	m_kNormal = kDif1.UnitCross(kDif2);
	m_fConstant = m_kNormal * arPoint0;
}

// GAME - 0x4B6160
float NiPlane::Distance(const NiPoint3& arPoint) const {
	return m_kNormal * arPoint - m_fConstant;
}

// GAME - 0x49DA80
// GECK - 0x5120B0
NiPlane::Sides NiPlane::WhichSide(const NiPoint3& arPoint) const {
	float fDistance = m_kNormal.Dot(arPoint) - m_fConstant;
	if (fDistance >= 0.f)
		return static_cast<Sides>(fDistance > 0.f);
	else
		return NEGATIVE_SIDE;
}
