#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint2;
class NiPoint3;

class SPEC_EMPTY_BASES NiPoint4 : public BSMemObject {
public:
	inline NiPoint4() noexcept;
	inline explicit NiPoint4(float afValue) noexcept;
	inline NiPoint4(float afX, float afY, float afZ, float afW) noexcept;
	explicit NiPoint4(const NiPoint2& arOther) noexcept;
	explicit NiPoint4(const NiPoint3& arOther) noexcept;
	explicit NiPoint4(const NiPoint3& arOther, float afW) noexcept;
	inline NiPoint4(const NiPoint4& arOther) noexcept;

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

	inline float& operator[](uint32_t i) noexcept;
	inline const float& operator[](uint32_t i) const noexcept;

	inline explicit operator float*() noexcept;

	inline bool operator==(const NiPoint4& arOther) const noexcept;

	inline NiPoint4 operator-() const noexcept;

	inline NiPoint4 operator+(const NiPoint4& arOther) const noexcept;
	inline NiPoint4 operator-(const NiPoint4& arOther) const noexcept;
	inline float	operator*(const NiPoint4& arOther) const noexcept;
	inline NiPoint4 operator/(const NiPoint4& arOther) const noexcept;

	inline NiPoint4 operator+(float afVal) const noexcept;
	inline NiPoint4 operator-(float afVal) const noexcept;
	inline NiPoint4 operator*(float afVal) const noexcept;
	inline NiPoint4 operator/(float afVal) const noexcept;

	inline NiPoint4& operator+=(const NiPoint4& arOther) noexcept;
	inline NiPoint4& operator-=(const NiPoint4& arOther) noexcept;
	inline NiPoint4& operator*=(const NiPoint4& arOther) noexcept;
	inline NiPoint4& operator/=(const NiPoint4& arOther) noexcept;

	inline NiPoint4& operator+=(float afVal) noexcept;
	inline NiPoint4& operator-=(float afVal) noexcept;
	inline NiPoint4& operator*=(float afVal) noexcept;
	inline NiPoint4& operator/=(float afVal) noexcept;

	inline friend NiPoint4 operator*(float afVal, const NiPoint4& arVec) noexcept;

	void operator=(const NiPoint2& arOther) noexcept;
	void operator=(const NiPoint3& arOther) noexcept;

	inline float Length() const noexcept;
	inline float XYLength() const noexcept;
	inline float XYZLength() const noexcept;
	inline float SqrLength() const noexcept;
	inline float SqrXYLength() const noexcept;
	inline float SqrXYZLength() const noexcept;

	inline float Dot(const NiPoint4& arOther) const noexcept;

	inline NiPoint4 Cross(const NiPoint4& arOther) const noexcept;
	inline NiPoint4 UnitCross(const NiPoint4& arOther) const noexcept;

	inline void Unitize() noexcept;
	inline float UnitizeGetLength() noexcept;
};

ASSERT_SIZE(NiPoint4, 0x10);

#include "NiPoint4.inl"