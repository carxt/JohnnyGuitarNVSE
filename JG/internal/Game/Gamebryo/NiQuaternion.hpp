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

	inline explicit operator float*() noexcept;

	inline bool operator==(const NiQuaternion& arOther) const noexcept;

	inline NiQuaternion operator-() const noexcept;

	inline NiQuaternion operator+(const NiQuaternion& arOther) const noexcept;
	inline NiQuaternion operator-(const NiQuaternion& arOther) const noexcept;
	inline NiQuaternion operator*(const NiQuaternion& arOther) const noexcept;

	inline NiQuaternion operator*(float afVal) const noexcept;
	inline NiQuaternion operator/(float afVal) const noexcept;

	inline NiQuaternion& operator+=(const NiQuaternion& arOther) noexcept;
	inline NiQuaternion& operator-=(const NiQuaternion& arOther) noexcept;

	inline NiQuaternion& operator*=(float afVal) noexcept;

	inline NiQuaternion& operator/=(float afVal) noexcept;

	inline friend NiQuaternion operator*(float afVal, const NiQuaternion& arOther) noexcept;

	inline NiQuaternion& operator=(const NiQuaternion& arOther) noexcept;
	inline NiQuaternion& operator=(float afVal) noexcept;

	void Snap() noexcept;

	void Normalize() noexcept;

	void FastNormalize() noexcept;

	void ToAngleAxis(float& afAngle, NiPoint3& arAxis) const noexcept;

	void FromAngleAxis(float afAngle, const NiPoint3& arAxis) noexcept;

	void ToRotation(NiMatrix3& arMatrix) const noexcept;

	void FromRotation(const NiMatrix3& arMatrix) noexcept;

	void Slerp(float afT, const NiQuaternion& arA, const NiQuaternion& arB) noexcept;
};

ASSERT_SIZE(NiQuaternion, 0x10);

#include "NiQuaternion.inl"