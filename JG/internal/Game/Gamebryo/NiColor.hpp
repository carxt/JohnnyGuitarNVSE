#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint3;
class NiColorA;

class SPEC_EMPTY_BASES NiColor : public BSMemObject {
public:
	NiColor() noexcept;
	explicit NiColor(float afValue) noexcept;
	NiColor(float afR, float afG, float afB) noexcept;
	NiColor(const NiColor& arOther) noexcept;
	explicit NiColor(const NiPoint3& arOther) noexcept;
	explicit NiColor(const NiColorA& arOther) noexcept;

	float r;
	float g;
	float b;

	static const NiColor BLACK;
	static const NiColor WHITE;
	static const NiColor RED;
	static const NiColor GREEN;
	static const NiColor BLUE;
	static const NiColor YELLOW;
	static const NiColor MAGENTA;
	static const NiColor CYAN;

	float& operator[](uint32_t i) noexcept;
	const float& operator[](uint32_t i) const noexcept;

	explicit operator float* () noexcept;

	bool operator==(const NiColor& arOther) const noexcept;

	NiColor operator-() const noexcept;

	NiColor operator+(const NiColor& arOther) const noexcept;
	NiColor operator-(const NiColor& arOther) const noexcept;
	float	operator*(const NiColor& arOther) const noexcept;
	NiColor operator/(const NiColor& arOther) const noexcept;

	NiColor operator+(float afVal) const noexcept;
	NiColor operator-(float afVal) const noexcept;
	NiColor operator*(float afVal) const noexcept;
	NiColor operator/(float afVal) const noexcept;

	NiColor& operator+=(const NiColor& arOther) noexcept;
	NiColor& operator-=(const NiColor& arOther) noexcept;
	NiColor& operator*=(const NiColor& arOther) noexcept;
	NiColor& operator/=(const NiColor& arOther) noexcept;

	NiColor& operator+=(float afVal) noexcept;
	NiColor& operator-=(float afVal) noexcept;
	NiColor& operator*=(float afVal) noexcept;
	NiColor& operator/=(float afVal) noexcept;

	friend NiColor operator*(float afVal, const NiColor& arOther) noexcept;

	void Scale() noexcept;

	void Clamp() noexcept;

	float Luminance() const noexcept;
};

ASSERT_SIZE(NiColor, 0xC);