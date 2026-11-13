#pragma once

#include "NiQuaternion.hpp"

inline NiQuaternion::operator float*() noexcept {
	return &m_fW;
}

// GAME - 0xA92660
inline bool NiQuaternion::operator==(const NiQuaternion& arOther) const noexcept {
	return m_fW == arOther.m_fW && m_fX == arOther.m_fX && m_fY == arOther.m_fY && m_fZ == arOther.m_fZ;
}

// GAME - 0xA6DBD0
inline NiQuaternion NiQuaternion::operator-() const noexcept {
	return NiQuaternion(-m_fW, -m_fX, -m_fY, -m_fZ);
}

// GAME - 0xA6DB70
inline NiQuaternion NiQuaternion::operator+(const NiQuaternion& arOther) const noexcept {
    return NiQuaternion(m_fW + arOther.m_fW, m_fX + arOther.m_fX, m_fY + arOther.m_fY, m_fZ + arOther.m_fZ);
}

// GAME - 0xA6DBA0
inline NiQuaternion NiQuaternion::operator-(const NiQuaternion& arOther) const noexcept {
	return NiQuaternion(m_fW - arOther.m_fW, m_fX - arOther.m_fX, m_fY - arOther.m_fY, m_fZ - arOther.m_fZ);
}

// GAME - 0xA2BCF0
inline NiQuaternion NiQuaternion::operator*(const NiQuaternion& arOther) const noexcept {
	return NiQuaternion(
		m_fW * arOther.m_fW - m_fX * arOther.m_fX - m_fY * arOther.m_fY - m_fZ * arOther.m_fZ,
		m_fW * arOther.m_fX + m_fX * arOther.m_fW + m_fY * arOther.m_fZ - m_fZ * arOther.m_fY,
		m_fW * arOther.m_fY + m_fY * arOther.m_fW + m_fZ * arOther.m_fX - m_fX * arOther.m_fZ,
		m_fW * arOther.m_fZ + m_fZ * arOther.m_fW + m_fX * arOther.m_fY - m_fY * arOther.m_fX
	);
}

// GAME - 0xA39120
inline NiQuaternion NiQuaternion::operator*(float afVal) const noexcept {
	return NiQuaternion(m_fW * afVal, m_fX * afVal, m_fY * afVal, m_fZ * afVal);
}

inline NiQuaternion NiQuaternion::operator/(float afVal) const noexcept {
	return NiQuaternion(m_fW / afVal, m_fX / afVal, m_fY / afVal, m_fZ / afVal);
}

inline NiQuaternion& NiQuaternion::operator+=(const NiQuaternion& arOther) noexcept {
	m_fW += arOther.m_fW;
	m_fX += arOther.m_fX;
	m_fY += arOther.m_fY;
	m_fZ += arOther.m_fZ;
	return *this;
}

inline NiQuaternion& NiQuaternion::operator-=(const NiQuaternion& arOther) noexcept {
	m_fW -= arOther.m_fW;
	m_fX -= arOther.m_fX;
	m_fY -= arOther.m_fY;
	m_fZ -= arOther.m_fZ;
	return *this;
}

inline NiQuaternion& NiQuaternion::operator*=(float afVal) noexcept {
	m_fW *= afVal;
	m_fX *= afVal;
	m_fY *= afVal;
	m_fZ *= afVal;
	return *this;
}

inline NiQuaternion& NiQuaternion::operator/=(float afVal) noexcept {
	m_fW /= afVal;
	m_fX /= afVal;
	m_fY /= afVal;
	m_fZ /= afVal;
	return *this;
}

inline NiQuaternion operator*(float afVal, const NiQuaternion& arOther) noexcept {
	return NiQuaternion(afVal * arOther.m_fW, afVal * arOther.m_fX, afVal * arOther.m_fY, afVal * arOther.m_fZ);
}

inline NiQuaternion& NiQuaternion::operator=(const NiQuaternion& arOther) noexcept {
	m_fW = arOther.m_fW;
	m_fX = arOther.m_fX;
	m_fY = arOther.m_fY;
	m_fZ = arOther.m_fZ;
	return *this;
}

inline NiQuaternion& NiQuaternion::operator=(float afVal) noexcept {
	m_fW = afVal;
	m_fX = afVal;
	m_fY = afVal;
	m_fZ = afVal;
	return *this;
}