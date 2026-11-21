#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint3;
class NiPoint4;

class SPEC_EMPTY_BASES NiPoint2 : public BSMemObject {
public:
	constexpr NiPoint2() noexcept;
	constexpr explicit NiPoint2(float afVal) noexcept;
	constexpr NiPoint2(float afX, float afY) noexcept;
	constexpr NiPoint2(const NiPoint2& arOther) noexcept;
	explicit NiPoint2(const NiPoint3& arOther) noexcept;
	explicit NiPoint2(const NiPoint4& arOther) noexcept;

	float x;
	float y;

	static const NiPoint2 ZERO;
	static const NiPoint2 UNIT_X;
	static const NiPoint2 UNIT_Y;

	constexpr float& operator[](uint32_t i) noexcept;
	constexpr const float& operator[](uint32_t i) const noexcept;

	constexpr explicit operator float*() noexcept;

	constexpr bool operator==(const NiPoint2& arOther) const noexcept;

	constexpr NiPoint2 operator-() const noexcept;

	constexpr NiPoint2 operator+(const NiPoint2& arOther) const noexcept;
	constexpr NiPoint2 operator-(const NiPoint2& arOther) const noexcept;
	constexpr float	operator*(const NiPoint2& arOther) const noexcept;
	constexpr NiPoint2 operator/(const NiPoint2& arOther) const noexcept;

	constexpr NiPoint2 operator+(float afVal) const noexcept;
	constexpr NiPoint2 operator-(float afVal) const noexcept;
	constexpr NiPoint2 operator*(float afVal) const noexcept;
	constexpr NiPoint2 operator/(float afVal) const noexcept;

	constexpr NiPoint2& operator+=(const NiPoint2& arOther) noexcept;
	constexpr NiPoint2& operator-=(const NiPoint2& arOther) noexcept;
	constexpr NiPoint2& operator*=(const NiPoint2& arOther) noexcept;
	constexpr NiPoint2& operator/=(const NiPoint2& arOther) noexcept;

	constexpr NiPoint2& operator+=(float afVal) noexcept;
	constexpr NiPoint2& operator-=(float afVal) noexcept;
	constexpr NiPoint2& operator*=(float afVal) noexcept;
	constexpr NiPoint2& operator/=(float afVal) noexcept;

	constexpr friend NiPoint2 operator*(float afVal, const NiPoint2& arVec) noexcept;

	constexpr float Length() const noexcept;
	constexpr float SqrLength() const noexcept;

	constexpr float Dot(const NiPoint2& arOther) const noexcept;

	constexpr float Unitize() noexcept;
};

ASSERT_SIZE(NiPoint2, 0x8);

#include "NiPoint2.inl"