#pragma once

#include "Bethesda/BSMemObject.hpp"

class NiPoint3;
class NiPoint4;
class NiColor;

class SPEC_EMPTY_BASES NiColorA : public BSMemObject {
public:
	constexpr explicit NiColorA(float afValue) noexcept;
	constexpr explicit NiColorA(float afR, float afG, float afB) noexcept;
	constexpr NiColorA(float afR = 0.f, float afG = 0.f, float afB = 0.f, float afA = 0.f) noexcept;
	constexpr NiColorA(const NiColorA& arOther) noexcept;
	explicit NiColorA(const NiPoint3& arOther) noexcept;
	explicit NiColorA(const NiPoint4& arOther) noexcept;
	explicit NiColorA(const NiColor& arOther) noexcept;
	explicit NiColorA(const NiColor& arOther, float afA) noexcept;

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

	constexpr float& operator[](uint32_t i) noexcept;
	constexpr const float& operator[](uint32_t i) const noexcept;

	constexpr explicit operator float* () noexcept;

	constexpr bool operator==(const NiColorA& arOther) const noexcept;

	constexpr NiColorA operator-() const noexcept;

	constexpr NiColorA operator+(const NiColorA& arOther) const noexcept;
	constexpr NiColorA operator-(const NiColorA& arOther) const noexcept;
	constexpr NiColorA operator*(const NiColorA& arOther) const noexcept;
	constexpr NiColorA operator/(const NiColorA& arOther) const noexcept;

	constexpr NiColorA operator+(float afVal) const noexcept;
	constexpr NiColorA operator-(float afVal) const noexcept;
	constexpr NiColorA operator*(float afVal) const noexcept;
	constexpr NiColorA operator/(float afVal) const noexcept;

	constexpr NiColorA& operator+=(const NiColorA& arOther) noexcept;
	constexpr NiColorA& operator-=(const NiColorA& arOther) noexcept;
	constexpr NiColorA& operator*=(const NiColorA& arOther) noexcept;
	constexpr NiColorA& operator/=(const NiColorA& arOther) noexcept;

	constexpr NiColorA& operator+=(float afVal) noexcept;
	constexpr NiColorA& operator-=(float afVal) noexcept;
	constexpr NiColorA& operator*=(float afVal) noexcept;
	constexpr NiColorA& operator/=(float afVal) noexcept;

	friend constexpr NiColorA operator*(float afVal, const NiColorA& arOther) noexcept;

	constexpr void Scale() noexcept;

	constexpr void Clamp() noexcept;
};

#include "NiColorA.inl"

ASSERT_SIZE(NiColorA, 0x10);