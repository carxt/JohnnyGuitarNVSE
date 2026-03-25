#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint3;
class NiPoint4;

class SPEC_EMPTY_BASES NiPoint2 : public BSMemObject {
public:
	inline NiPoint2() noexcept;
	inline explicit NiPoint2(float afVal) noexcept;
	inline NiPoint2(float afX, float afY) noexcept;
	inline NiPoint2(const NiPoint2& arOther) noexcept;
	explicit NiPoint2(const NiPoint3& arOther) noexcept;
	explicit NiPoint2(const NiPoint4& arOther) noexcept;

	float x;
	float y;

	static const NiPoint2 ZERO;
	static const NiPoint2 UNIT_X;
	static const NiPoint2 UNIT_Y;

	inline float& operator[](uint32_t i) noexcept;
	inline const float& operator[](uint32_t i) const noexcept;

	inline explicit operator float*() noexcept;

	inline bool operator==(const NiPoint2& arOther) const noexcept;

	inline NiPoint2 operator-() const noexcept;

	inline NiPoint2 operator+(const NiPoint2& arOther) const noexcept;
	inline NiPoint2 operator-(const NiPoint2& arOther) const noexcept;
	inline float	operator*(const NiPoint2& arOther) const noexcept;
	inline NiPoint2 operator/(const NiPoint2& arOther) const noexcept;

	inline NiPoint2 operator+(float afVal) const noexcept;
	inline NiPoint2 operator-(float afVal) const noexcept;
	inline NiPoint2 operator*(float afVal) const noexcept;
	inline NiPoint2 operator/(float afVal) const noexcept;

	inline NiPoint2& operator+=(const NiPoint2& arOther) noexcept;
	inline NiPoint2& operator-=(const NiPoint2& arOther) noexcept;
	inline NiPoint2& operator*=(const NiPoint2& arOther) noexcept;
	inline NiPoint2& operator/=(const NiPoint2& arOther) noexcept;

	inline NiPoint2& operator+=(float afVal) noexcept;
	inline NiPoint2& operator-=(float afVal) noexcept;
	inline NiPoint2& operator*=(float afVal) noexcept;
	inline NiPoint2& operator/=(float afVal) noexcept;

	inline friend NiPoint2 operator*(float afVal, const NiPoint2& arVec) noexcept;

	inline float Length() const noexcept;
	inline float SqrLength() const noexcept;

	inline float Dot(const NiPoint2& arOther) const noexcept;

	inline float Unitize() noexcept;
};

ASSERT_SIZE(NiPoint2, 0x8);

#include "NiPoint2.inl"