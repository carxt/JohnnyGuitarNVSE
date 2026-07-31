#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint3;
class NiPoint4;
class NiColor;

class SPEC_EMPTY_BASES NiColorA : public BSMemObject {
public:
	NiColorA() noexcept;
	explicit NiColorA(float afValue) noexcept;
	explicit NiColorA(float afR, float afG, float afB) noexcept;
	NiColorA(float afR, float afG, float afB, float afA) noexcept;
	NiColorA(const NiColorA& arOther) noexcept;
	explicit NiColorA(const NiPoint3& arOther) noexcept;
	explicit NiColorA(const NiPoint4& arOther) noexcept;
	explicit NiColorA(const NiColor& arOther) noexcept;

	float r;
	float g;
	float b;
	float a;

	static const NiColorA BLACK;
	static const NiColorA WHITE;
	static const NiColorA RED;
	static const NiColorA GREEN;
	static const NiColorA BLUE;
	static const NiColorA YELLOW;
	static const NiColorA MAGENTA;
	static const NiColorA CYAN;

	float& operator[](uint32_t i) noexcept;
	const float& operator[](uint32_t i) const noexcept;

	explicit operator float* () noexcept;

	bool operator==(const NiColorA& arOther) const noexcept;

	NiColorA operator-() const noexcept;

	NiColorA operator+(const NiColorA& arOther) const noexcept;
	NiColorA operator-(const NiColorA& arOther) const noexcept;
	NiColorA operator*(const NiColorA& arOther) const noexcept;
	NiColorA operator/(const NiColorA& arOther) const noexcept;

	NiColorA operator+(float afVal) const noexcept;
	NiColorA operator-(float afVal) const noexcept;
	NiColorA operator*(float afVal) const noexcept;
	NiColorA operator/(float afVal) const noexcept;

	NiColorA& operator+=(const NiColorA& arOther) noexcept;
	NiColorA& operator-=(const NiColorA& arOther) noexcept;
	NiColorA& operator*=(const NiColorA& arOther) noexcept;
	NiColorA& operator/=(const NiColorA& arOther) noexcept;

	NiColorA& operator+=(float afVal) noexcept;
	NiColorA& operator-=(float afVal) noexcept;
	NiColorA& operator*=(float afVal) noexcept;
	NiColorA& operator/=(float afVal) noexcept;

	friend NiColorA operator*(float afVal, const NiColorA& arOther) noexcept;

	void Scale() noexcept;

	void Clamp() noexcept;
};

ASSERT_SIZE(NiColorA, 0x10);