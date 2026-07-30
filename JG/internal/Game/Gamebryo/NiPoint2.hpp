#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint3;
class NiPoint4;

class SPEC_EMPTY_BASES NiPoint2 : public BSMemObject {
public:
	NiPoint2() noexcept;
	explicit NiPoint2(float afVal) noexcept;
	NiPoint2(float afX, float afY) noexcept;
	NiPoint2(const NiPoint2& arOther) noexcept;
	explicit NiPoint2(const NiPoint3& arOther) noexcept;
	explicit NiPoint2(const NiPoint4& arOther) noexcept;

	float x;
	float y;

	static const NiPoint2 ZERO;
	static const NiPoint2 UNIT_X;
	static const NiPoint2 UNIT_Y;

	float& operator[](uint32_t i) noexcept;
	const float& operator[](uint32_t i) const noexcept;

	explicit operator float*() noexcept;

	bool operator==(const NiPoint2& arOther) const noexcept;

	NiPoint2 operator-() const noexcept;

	NiPoint2 operator+(const NiPoint2& arOther) const noexcept;
	NiPoint2 operator-(const NiPoint2& arOther) const noexcept;
	float	operator*(const NiPoint2& arOther) const noexcept;
	NiPoint2 operator/(const NiPoint2& arOther) const noexcept;

	NiPoint2 operator+(float afVal) const noexcept;
	NiPoint2 operator-(float afVal) const noexcept;
	NiPoint2 operator*(float afVal) const noexcept;
	NiPoint2 operator/(float afVal) const noexcept;

	NiPoint2& operator+=(const NiPoint2& arOther) noexcept;
	NiPoint2& operator-=(const NiPoint2& arOther) noexcept;
	NiPoint2& operator*=(const NiPoint2& arOther) noexcept;
	NiPoint2& operator/=(const NiPoint2& arOther) noexcept;

	NiPoint2& operator+=(float afVal) noexcept;
	NiPoint2& operator-=(float afVal) noexcept;
	NiPoint2& operator*=(float afVal) noexcept;
	NiPoint2& operator/=(float afVal) noexcept;

	friend NiPoint2 operator*(float afVal, const NiPoint2& arVec) noexcept;

	bool IsOk() const noexcept;

	float Length() const noexcept;
	float SqrLength() const noexcept;

	float Dot(const NiPoint2& arOther) const noexcept;

	float Unitize() noexcept;
};

ASSERT_SIZE(NiPoint2, 0x8);