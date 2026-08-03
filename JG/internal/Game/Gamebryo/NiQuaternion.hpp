#pragma once

#include "NiMemObject.hpp"

class NiPoint3;
class NiMatrix3;

class SPEC_EMPTY_BASES NiQuaternion : public NiMemObject {
public:
	NiQuaternion() noexcept;
	NiQuaternion(float afW, float afX, float afY, float afZ) noexcept;
	NiQuaternion(float afAngle, const NiPoint3& arAxis) noexcept;

	float m_fW;
	float m_fX;
	float m_fY;
	float m_fZ;

	static const NiQuaternion ZERO;
	static const NiQuaternion IDENTITY;

	NiQuaternion operator+(const NiQuaternion& rhs) const {
		return NiQuaternion(m_fW + rhs.m_fW, m_fX + rhs.m_fX, m_fY + rhs.m_fY, m_fZ + rhs.m_fZ);
	}

	NiQuaternion operator-(const NiQuaternion& rhs) const {
		return NiQuaternion(m_fW - rhs.m_fW, m_fX - rhs.m_fX, m_fY - rhs.m_fY, m_fZ - rhs.m_fZ);
	}

	NiQuaternion operator*(const float& rhs) const {
		return NiQuaternion(m_fW * rhs, m_fX * rhs, m_fY * rhs, m_fZ * rhs);
	}

	NiQuaternion operator/(const float& rhs) const {
		return NiQuaternion(m_fW / rhs, m_fX / rhs, m_fY / rhs, m_fZ / rhs);
	}

	NiQuaternion& operator+=(const NiQuaternion& rhs) {
		m_fW += rhs.m_fW;
		m_fX += rhs.m_fX;
		m_fY += rhs.m_fY;
		m_fZ += rhs.m_fZ;
		return *this;
	}

	NiQuaternion& operator-=(const NiQuaternion& rhs) {
		m_fW -= rhs.m_fW;
		m_fX -= rhs.m_fX;
		m_fY -= rhs.m_fY;
		m_fZ -= rhs.m_fZ;
		return *this;
	}

	NiQuaternion& operator*=(const float& rhs) {
		m_fW *= rhs;
		m_fX *= rhs;
		m_fY *= rhs;
		m_fZ *= rhs;
		return *this;
	}

	NiQuaternion& operator/=(const float& rhs) {
		m_fW /= rhs;
		m_fX /= rhs;
		m_fY /= rhs;
		m_fZ /= rhs;
		return *this;
	}

	bool operator==(const NiQuaternion& rhs) const {
		return m_fW == rhs.m_fW && m_fX == rhs.m_fX && m_fY == rhs.m_fY && m_fZ == rhs.m_fZ;
	}

	bool operator!=(const NiQuaternion& rhs) const {
		return m_fW != rhs.m_fW || m_fX != rhs.m_fX || m_fY != rhs.m_fY || m_fZ != rhs.m_fZ;
	}

	NiQuaternion& operator=(const NiQuaternion& rhs) {
		m_fW = rhs.m_fW;
		m_fX = rhs.m_fX;
		m_fY = rhs.m_fY;
		m_fZ = rhs.m_fZ;
		return *this;
	}

	NiQuaternion& operator=(const float& rhs) {
		m_fW = rhs;
		m_fX = rhs;
		m_fY = rhs;
		m_fZ = rhs;
		return *this;
	}

	void Snap() {
		constexpr float epsilon = 1e-08f;
		if (abs(m_fX) <= epsilon && m_fX != 0.0f)
			m_fX = 0.0f;

		if (abs(m_fY) <= epsilon && m_fY != 0.0f)
			m_fY = 0.0f;

		if (abs(m_fZ) <= epsilon && m_fZ != 0.0f)
			m_fZ = 0.0f;

		if (abs(m_fW) <= epsilon && m_fW != 0.0f)
			m_fW = 0.0f;
	}

	void Normalize();

	void FastNormalize();

	void ToAngleAxis(float& afAngle, NiPoint3& arAxis) const;

	void FromAngleAxis(float afAngle, const NiPoint3& arAxis);

	void ToRotation(NiMatrix3& arMatrix) const;

	void FromRotation(const NiMatrix3& arMatrix);

	void Slerp(float afT, const NiQuaternion& arA, const NiQuaternion& arB);
};