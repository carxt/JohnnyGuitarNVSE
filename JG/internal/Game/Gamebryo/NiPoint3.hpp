#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint2;
class NiPoint4;

class SPEC_EMPTY_BASES NiPoint3 : public BSMemObject {
public:
	constexpr NiPoint3() noexcept;
	constexpr explicit NiPoint3(float afValue) noexcept;
	constexpr NiPoint3(float afX, float afY, float afZ) noexcept;
	constexpr NiPoint3(const NiPoint3& arOther) noexcept;
	explicit NiPoint3(const NiPoint2& arOther) noexcept;
	explicit NiPoint3(const NiPoint4& arOther) noexcept;

	float x;
	float y;
	float z;
	
	static const NiPoint3 UNIT_X;
	static const NiPoint3 UNIT_Y;
	static const NiPoint3 UNIT_Z;
	static const NiPoint3 UNIT_ALL;
	static const NiPoint3 ZERO;

	constexpr float& operator[](uint32_t i) noexcept;
	constexpr const float& operator[](uint32_t i) const noexcept;

	constexpr explicit operator float*() noexcept;

	constexpr bool operator==(const NiPoint3& arOther) const noexcept;

	constexpr NiPoint3 operator-() const noexcept;

	constexpr NiPoint3 operator+(const NiPoint3& arOther) const noexcept;
	constexpr NiPoint3 operator-(const NiPoint3& arOther) const noexcept;
	constexpr float	operator*(const NiPoint3& arOther) const noexcept;
	constexpr NiPoint3 operator/(const NiPoint3& arOther) const noexcept;

	constexpr NiPoint3 operator+(float afVal) const noexcept;
	constexpr NiPoint3 operator-(float afVal) const noexcept;
	constexpr NiPoint3 operator*(float afVal) const noexcept;
	constexpr NiPoint3 operator/(float afVal) const noexcept;

	constexpr NiPoint3& operator+=(const NiPoint3& arOther) noexcept;
	constexpr NiPoint3& operator-=(const NiPoint3& arOther) noexcept;
	constexpr NiPoint3& operator*=(const NiPoint3& arOther) noexcept;
	constexpr NiPoint3& operator/=(const NiPoint3& arOther) noexcept;

	constexpr NiPoint3& operator+=(float afVal) noexcept;
	constexpr NiPoint3& operator-=(float afVal) noexcept;
	constexpr NiPoint3& operator*=(float afVal) noexcept;
	constexpr NiPoint3& operator/=(float afVal) noexcept;

	constexpr friend NiPoint3 operator*(float afVal, const NiPoint3& arVec) noexcept;

	void operator=(const NiPoint2& arOther) noexcept;

	constexpr float Length() const noexcept;
	constexpr float XYLength() const noexcept;
	constexpr float SqrLength() const noexcept;
	constexpr float SqrXYLength() const noexcept;

	constexpr float Dot(const NiPoint3& arOther) const noexcept;

	constexpr NiPoint3 Cross(const NiPoint3& arOther) const noexcept;
	constexpr NiPoint3 UnitCross(const NiPoint3& arOther) const noexcept;

	constexpr void Unitize() noexcept;
	constexpr float UnitizeGetLength() noexcept;
	static void UnitizeVector(NiPoint3& arVector) noexcept;
	static void UnitizeVectors(NiPoint3* apVectors, uint32_t auiCount, uint32_t auiStride) noexcept;

	constexpr float Distance(const NiPoint3& arOther) const noexcept;
	constexpr float SqrDistance(const NiPoint3& arOther) const noexcept;
};

ASSERT_SIZE(NiPoint3, 0xC);

#include "NiPoint3.inl"