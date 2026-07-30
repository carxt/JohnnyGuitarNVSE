#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint2;
class NiPoint3;

class SPEC_EMPTY_BASES NiPoint4 : public BSMemObject {
public:
	NiPoint4() noexcept;
	explicit NiPoint4(float afValue) noexcept;
	NiPoint4(float afX, float afY, float afZ, float afW) noexcept;
	explicit NiPoint4(const NiPoint2& arOther) noexcept;
	explicit NiPoint4(const NiPoint3& arOther) noexcept;
	explicit NiPoint4(const NiPoint3& arOther, float afW) noexcept;
	NiPoint4(const NiPoint4& arOther) noexcept;

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

	float& operator[](uint32_t i) noexcept;
	const float& operator[](uint32_t i) const noexcept;

	explicit operator float*() noexcept;

	bool operator==(const NiPoint4& arOther) const noexcept;

	NiPoint4 operator-() const noexcept;

	NiPoint4 operator+(const NiPoint4& arOther) const noexcept;
	NiPoint4 operator-(const NiPoint4& arOther) const noexcept;
	float	operator*(const NiPoint4& arOther) const noexcept;
	NiPoint4 operator/(const NiPoint4& arOther) const noexcept;

	NiPoint4 operator+(float afVal) const noexcept;
	NiPoint4 operator-(float afVal) const noexcept;
	NiPoint4 operator*(float afVal) const noexcept;
	NiPoint4 operator/(float afVal) const noexcept;

	NiPoint4& operator+=(const NiPoint4& arOther) noexcept;
	NiPoint4& operator-=(const NiPoint4& arOther) noexcept;
	NiPoint4& operator*=(const NiPoint4& arOther) noexcept;
	NiPoint4& operator/=(const NiPoint4& arOther) noexcept;

	NiPoint4& operator+=(float afVal) noexcept;
	NiPoint4& operator-=(float afVal) noexcept;
	NiPoint4& operator*=(float afVal) noexcept;
	NiPoint4& operator/=(float afVal) noexcept;

	friend NiPoint4 operator*(float afVal, const NiPoint4& arVec) noexcept;

	void operator=(const NiPoint2& arOther) noexcept;
	void operator=(const NiPoint3& arOther) noexcept;

	bool IsOk() const noexcept;

	float Length() const noexcept;
	float XYLength() const noexcept;
	float XYZLength() const noexcept;
	float SqrLength() const noexcept;
	float SqrXYLength() const noexcept;
	float SqrXYZLength() const noexcept;

	float Dot(const NiPoint4& arOther) const noexcept;

	NiPoint4 Cross(const NiPoint4& arOther) const noexcept;
	NiPoint4 UnitCross(const NiPoint4& arOther) const noexcept;

	void Unitize() noexcept;
	float UnitizeGetLength() noexcept;
};

ASSERT_SIZE(NiPoint4, 0x10);