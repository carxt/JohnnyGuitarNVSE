#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint2;
class NiPoint3;

class SPEC_EMPTY_BASES NiPoint4 : public BSMemObject {
public:
	constexpr NiPoint4() noexcept;
	constexpr explicit NiPoint4(float afValue) noexcept;
	constexpr NiPoint4(float afX, float afY, float afZ, float afW) noexcept;
	explicit NiPoint4(const NiPoint2& arOther) noexcept;
	explicit NiPoint4(const NiPoint3& arOther) noexcept;
	explicit NiPoint4(const NiPoint3& arOther, float afW) noexcept;
	constexpr NiPoint4(const NiPoint4& arOther) noexcept;

	float x;
	float y;
	float z;
	float w;
	
	static const NiPoint4 UNIT_X;
	static const NiPoint4 UNIT_Y;
	static const NiPoint4 UNIT_Z;
	static const NiPoint4 UNIT_W;
	static const NiPoint4 UNIT_ALL;
	static const NiPoint4 ZERO;

	constexpr float& operator[](uint32_t i) noexcept;
	constexpr const float& operator[](uint32_t i) const noexcept;

	constexpr explicit operator float*() noexcept;

	constexpr bool operator==(const NiPoint4& arOther) const noexcept;

	constexpr NiPoint4 operator-() const noexcept;

	constexpr NiPoint4 operator+(const NiPoint4& arOther) const noexcept;
	constexpr NiPoint4 operator-(const NiPoint4& arOther) const noexcept;
	constexpr float	operator*(const NiPoint4& arOther) const noexcept;
	constexpr NiPoint4 operator/(const NiPoint4& arOther) const noexcept;

	constexpr NiPoint4 operator+(float afVal) const noexcept;
	constexpr NiPoint4 operator-(float afVal) const noexcept;
	constexpr NiPoint4 operator*(float afVal) const noexcept;
	constexpr NiPoint4 operator/(float afVal) const noexcept;

	constexpr NiPoint4& operator+=(const NiPoint4& arOther) noexcept;
	constexpr NiPoint4& operator-=(const NiPoint4& arOther) noexcept;
	constexpr NiPoint4& operator*=(const NiPoint4& arOther) noexcept;
	constexpr NiPoint4& operator/=(const NiPoint4& arOther) noexcept;

	constexpr NiPoint4& operator+=(float afVal) noexcept;
	constexpr NiPoint4& operator-=(float afVal) noexcept;
	constexpr NiPoint4& operator*=(float afVal) noexcept;
	constexpr NiPoint4& operator/=(float afVal) noexcept;

	constexpr friend NiPoint4 operator*(float afVal, const NiPoint4& arVec) noexcept;

	void operator=(const NiPoint2& arOther) noexcept;
	void operator=(const NiPoint3& arOther) noexcept;

	constexpr float Length() const noexcept;
	constexpr float XYLength() const noexcept;
	constexpr float XYZLength() const noexcept;
	constexpr float SqrLength() const noexcept;
	constexpr float SqrXYLength() const noexcept;
	constexpr float SqrXYZLength() const noexcept;

	constexpr float Dot(const NiPoint4& arOther) const noexcept;

	constexpr NiPoint4 Cross(const NiPoint4& arOther) const noexcept;
	constexpr NiPoint4 UnitCross(const NiPoint4& arOther) const noexcept;

	constexpr void Unitize() noexcept;
	constexpr float UnitizeGetLength() noexcept;
};

ASSERT_SIZE(NiPoint4, 0x10);

#include "NiPoint4.inl"