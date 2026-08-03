#include "NiQuaternion.hpp"
#include "NiMatrix3.hpp"

// GAME - 0x11F49EC
const NiQuaternion NiQuaternion::ZERO = NiQuaternion(0.0f, 0.0f, 0.0f, 0.0f);

// GAME - 0x11A9EA4
const NiQuaternion NiQuaternion::IDENTITY = NiQuaternion(1.0f, 0.0f, 0.0f, 0.0f);

NiQuaternion::NiQuaternion() noexcept {}

// GAME - 0xA6DB50
NiQuaternion::NiQuaternion(float afW, float afX, float afY, float afZ) noexcept : m_fW(afW), m_fX(afX), m_fY(afY), m_fZ(afZ) {};

NiQuaternion::NiQuaternion(float afAngle, const NiPoint3& arAxis) noexcept {
    FromAngleAxis(afAngle, arAxis);
}

// GAME - 0xA38560
// GECK - 0x7E6BB0
void NiQuaternion::Normalize() {
    const float fLength = m_fW * m_fW + m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ;
    const float fInvLength = 1.f / std::sqrt(fLength);
    *this = *this * fInvLength;
}

// GAME - 0xA4FF00
// GECK - 0x8007B0
void NiQuaternion::FastNormalize() {
#ifdef GAME
	ThisCall(0xA4FF00, this);
#else
	ThisCall(0x8007B0, this);
#endif
}

// GAME - 0xA6DE50
// GECK - 0x8276F0
void NiQuaternion::ToAngleAxis(float& afAngle, NiPoint3& arAxis) const {
#ifdef GAME
    ThisCall(0xA6DE50, this, &afAngle, &arAxis);
#else
    ThisCall(0x8276F0, this, &afAngle, &arAxis);
#endif
}

void NiQuaternion::FromAngleAxis(float afAngle, const NiPoint3& arAxis) {
    const float fHalfAngle = afAngle * 0.5f;
    const float fSin = std::sin(fHalfAngle);
    const float fCos = std::cos(fHalfAngle);
    m_fW = fCos;
    m_fX = arAxis.x * fSin;
    m_fY = arAxis.y * fSin;
    m_fZ = arAxis.z * fSin;
}

// GAME - 0x4F0180
// GECK - 0x539650
void NiQuaternion::ToRotation(NiMatrix3& arMatrix) const {
#ifdef GAME
    ThisCall(0x4F0180, this, &arMatrix);
#else
    ThisCall(0x539650, this, &arMatrix);
#endif
}

// GAME - 0xA6DF40
// GECK - 0x8277E0
void NiQuaternion::FromRotation(const NiMatrix3& arMatrix) {
#ifdef GAME
    ThisCall(0xA6DF40, this, &arMatrix);
#else
    ThisCall(0x8277E0, this, &arMatrix);
#endif
}

// GAME - 0xA6E330
// GECK - 0x827BD0
void NiQuaternion::Slerp(float afT, const NiQuaternion& arA, const NiQuaternion& arB) {
#ifdef GAME
	ThisCall(0xA6E330, this, afT, &arA, &arB);
#else
	ThisCall(0x827BD0, this, afT, &arA, &arB);
#endif
}
