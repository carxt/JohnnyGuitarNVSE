#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint2;
class NiPoint4;

class SPEC_EMPTY_BASES NiPoint3 : public BSMemObject {
public:
	inline NiPoint3() noexcept;
	inline explicit NiPoint3(float afValue) noexcept;
	inline NiPoint3(float afX, float afY, float afZ) noexcept;
	inline NiPoint3(const NiPoint3& arOther) noexcept;
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

	inline float& operator[](uint32_t i) noexcept;
	inline const float& operator[](uint32_t i) const noexcept;

	inline explicit operator float*() noexcept;

	inline bool operator==(const NiPoint3& arOther) const noexcept;

	inline NiPoint3 operator-() const noexcept;

	inline NiPoint3 operator+(const NiPoint3& arOther) const noexcept;
	inline NiPoint3 operator-(const NiPoint3& arOther) const noexcept;
	inline float	operator*(const NiPoint3& arOther) const noexcept;
	inline NiPoint3 operator/(const NiPoint3& arOther) const noexcept;

	inline NiPoint3 operator+(float afVal) const noexcept;
	inline NiPoint3 operator-(float afVal) const noexcept;
	inline NiPoint3 operator*(float afVal) const noexcept;
	inline NiPoint3 operator/(float afVal) const noexcept;

	inline NiPoint3& operator+=(const NiPoint3& arOther) noexcept;
	inline NiPoint3& operator-=(const NiPoint3& arOther) noexcept;
	inline NiPoint3& operator*=(const NiPoint3& arOther) noexcept;
	inline NiPoint3& operator/=(const NiPoint3& arOther) noexcept;

	inline NiPoint3& operator+=(float afVal) noexcept;
	inline NiPoint3& operator-=(float afVal) noexcept;
	inline NiPoint3& operator*=(float afVal) noexcept;
	inline NiPoint3& operator/=(float afVal) noexcept;

	inline friend NiPoint3 operator*(float afVal, const NiPoint3& arVec) noexcept;

	void operator=(const NiPoint2& arOther) noexcept;

	inline float Length() const noexcept;
	inline float XYLength() const noexcept;
	inline float SqrLength() const noexcept;
	inline float SqrXYLength() const noexcept;

	inline float Dot(const NiPoint3& arOther) const noexcept;

	inline NiPoint3 Cross(const NiPoint3& arOther) const noexcept;
	inline NiPoint3 UnitCross(const NiPoint3& arOther) const noexcept;

	inline void Unitize() noexcept;
	inline float UnitizeGetLength() noexcept;
	static void UnitizeVector(NiPoint3& arVector) noexcept;
	static void UnitizeVectors(NiPoint3* apVectors, uint32_t auiCount, uint32_t auiStride) noexcept;

	inline float Distance(const NiPoint3& arOther) const noexcept;
	inline float SqrDistance(const NiPoint3& arOther) const noexcept;
};

ASSERT_SIZE(NiPoint3, 0xC);

#include "NiPoint3.inl"