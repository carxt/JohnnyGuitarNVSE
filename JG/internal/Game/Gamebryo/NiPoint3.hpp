#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint2;
class NiPoint4;

class SPEC_EMPTY_BASES NiPoint3 : public BSMemObject {
public:
	NiPoint3() noexcept;
	explicit NiPoint3(float afValue) noexcept;
	NiPoint3(float afX, float afY, float afZ) noexcept;
	NiPoint3(const NiPoint3& arOther) noexcept;
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

	float& operator[](uint32_t i) noexcept;
	const float& operator[](uint32_t i) const noexcept;

	explicit operator float*() noexcept;

	bool operator==(const NiPoint3& arOther) const noexcept;

	NiPoint3 operator-() const noexcept;

	NiPoint3 operator+(const NiPoint3& arOther) const noexcept;
	NiPoint3 operator-(const NiPoint3& arOther) const noexcept;
	float	operator*(const NiPoint3& arOther) const noexcept;
	NiPoint3 operator/(const NiPoint3& arOther) const noexcept;

	NiPoint3 operator+(float afVal) const noexcept;
	NiPoint3 operator-(float afVal) const noexcept;
	NiPoint3 operator*(float afVal) const noexcept;
	NiPoint3 operator/(float afVal) const noexcept;

	NiPoint3& operator+=(const NiPoint3& arOther) noexcept;
	NiPoint3& operator-=(const NiPoint3& arOther) noexcept;
	NiPoint3& operator*=(const NiPoint3& arOther) noexcept;
	NiPoint3& operator/=(const NiPoint3& arOther) noexcept;

	NiPoint3& operator+=(float afVal) noexcept;
	NiPoint3& operator-=(float afVal) noexcept;
	NiPoint3& operator*=(float afVal) noexcept;
	NiPoint3& operator/=(float afVal) noexcept;

	friend NiPoint3 operator*(float afVal, const NiPoint3& arVec) noexcept;

	void operator=(const NiPoint2& arOther) noexcept;

	bool IsOk() const noexcept;

	float Length() const noexcept;
	float XYLength() const noexcept;
	float SqrLength() const noexcept;
	float SqrXYLength() const noexcept;

	int32_t LengthCheck(float afLength) const noexcept;
	int32_t LengthCheck(const NiPoint3& arOther, float afLength) const noexcept;

	float Dot(const NiPoint3& arOther) const noexcept;
	float DotXY(const NiPoint3& arOther) const noexcept;

	NiPoint3 Cross(const NiPoint3& arOther) const noexcept;
	NiPoint3 UnitCross(const NiPoint3& arOther) const noexcept;

	void Unitize() noexcept;
	float UnitizeGetLength() noexcept;
	static void UnitizeVector(NiPoint3& arVector) noexcept;
	static void UnitizeVectors(NiPoint3* apVectors, uint32_t auiCount, uint32_t auiStride) noexcept;

	float Distance(const NiPoint3& arOther) const noexcept;
	float SqrDistance(const NiPoint3& arOther) const noexcept;

	bool CloseEnough(const NiPoint3& arOther, float afDelta) const noexcept;
	bool CloseEnoughXY(const NiPoint3& arOther, float afDelta) const noexcept;
};

ASSERT_SIZE(NiPoint3, 0xC);