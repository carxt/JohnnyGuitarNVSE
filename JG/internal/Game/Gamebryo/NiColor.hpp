#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint3;
class NiColorA;

class SPEC_EMPTY_BASES NiColor : public BSMemObject {
public:
	constexpr explicit NiColor(float afValue) noexcept;
	constexpr NiColor(float afR = 0.f, float afG = 0.f, float afB = 0.f) noexcept;
	constexpr NiColor(const NiColor& arOther) noexcept;
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

	constexpr float& operator[](uint32_t i) noexcept;
	constexpr const float& operator[](uint32_t i) const noexcept;

	constexpr explicit operator float* () noexcept;

	constexpr bool operator==(const NiColor& arOther) const noexcept;

	constexpr NiColor operator-() const noexcept;

	constexpr NiColor operator+(const NiColor& arOther) const noexcept;
	constexpr NiColor operator-(const NiColor& arOther) const noexcept;
	constexpr float	  operator*(const NiColor& arOther) const noexcept;
	constexpr NiColor operator/(const NiColor& arOther) const noexcept;

	constexpr NiColor operator+(float afVal) const noexcept;
	constexpr NiColor operator-(float afVal) const noexcept;
	constexpr NiColor operator*(float afVal) const noexcept;
	constexpr NiColor operator/(float afVal) const noexcept;

	constexpr NiColor& operator+=(const NiColor& arOther) noexcept;
	constexpr NiColor& operator-=(const NiColor& arOther) noexcept;
	constexpr NiColor& operator*=(const NiColor& arOther) noexcept;
	constexpr NiColor& operator/=(const NiColor& arOther) noexcept;

	constexpr NiColor& operator+=(float afVal) noexcept;
	constexpr NiColor& operator-=(float afVal) noexcept;
	constexpr NiColor& operator*=(float afVal) noexcept;
	constexpr NiColor& operator/=(float afVal) noexcept;

	friend constexpr NiColor operator*(float afVal, const NiColor& arOther) noexcept;

	constexpr void Scale() noexcept;

	constexpr void Clamp() noexcept;

	constexpr float Luminance() const noexcept;
};

#include "NiColor.inl"

ASSERT_SIZE(NiColor, 0xC);