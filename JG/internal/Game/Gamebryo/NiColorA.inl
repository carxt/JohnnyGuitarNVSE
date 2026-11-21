#pragma once

#include "NiColorA.hpp"

inline constexpr NiColorA::NiColorA(float afValue) noexcept : r(afValue), g(afValue), b(afValue), a(1.f) {}

inline constexpr NiColorA::NiColorA(float afR, float afG, float afB) noexcept : r(afR), g(afG), b(afB), a(1.f) {}

// GAME - 0x414430
inline constexpr NiColorA::NiColorA(float afR, float afG, float afB, float afA) noexcept : r(afR), g(afG), b(afB), a(afA) {}

inline constexpr NiColorA::NiColorA(const NiColorA& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b), a(arOther.a) {}

inline constexpr float& NiColorA::operator[](uint32_t i) noexcept {
    ASSUME_ASSERT(i < 4);
    if consteval {
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            case 3: return a;
        }
    }
    else {
        return reinterpret_cast<float*>(this)[i];
    }
}

inline constexpr const float& NiColorA::operator[](uint32_t i) const noexcept {
    ASSUME_ASSERT(i < 4);
    if consteval {
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
            case 3: return a;
        }
    }
    else {
        return reinterpret_cast<const float*>(this)[i];
    }
}

inline constexpr NiColorA::operator float* () noexcept {
    return &r;
}

// GAME - 0x4A4CC0
inline constexpr bool NiColorA::operator==(const NiColorA& arOther) const noexcept {
    return r == arOther.r && g == arOther.g && b == arOther.b && a == arOther.a;
}

inline constexpr NiColorA NiColorA::operator-() const noexcept {
    return NiColorA(-r, -g, -b, -a);
}

// GAME - 0x532E40
inline constexpr NiColorA NiColorA::operator+(const NiColorA& arOther) const noexcept {
    return NiColorA(r + arOther.r, g + arOther.g, b + arOther.b, a + arOther.a);
}

// GAME - 0x532EC0
inline constexpr NiColorA NiColorA::operator-(const NiColorA& arOther) const noexcept {
    return NiColorA(r - arOther.r, g - arOther.g, b - arOther.b, a - arOther.a);
}

inline constexpr NiColorA NiColorA::operator*(const NiColorA& arOther) const noexcept {
    return NiColorA(r * arOther.r, g * arOther.g, b * arOther.b, a * arOther.a);
}

inline constexpr NiColorA NiColorA::operator/(const NiColorA& arOther) const noexcept {
    return NiColorA(r / arOther.r, g / arOther.g, b / arOther.b, a / arOther.a);
}

inline constexpr NiColorA NiColorA::operator+(float afVal) const noexcept {
    return NiColorA(r + afVal, g + afVal, b + afVal, a + afVal);
}

inline constexpr NiColorA NiColorA::operator-(float afVal) const noexcept {
    return NiColorA(r - afVal, g - afVal, b - afVal, a - afVal);
}

// GAME - 0x532F60
inline constexpr NiColorA NiColorA::operator*(float afVal) const noexcept {
    return NiColorA(r * afVal, g * afVal, b * afVal, a * afVal);
}

// GAME - 0x5074E0
inline constexpr NiColorA NiColorA::operator/(float afVal) const noexcept {
    return NiColorA(r / afVal, g / afVal, b / afVal, a / afVal);
}

inline constexpr NiColorA& NiColorA::operator+=(const NiColorA& arOther) noexcept {
    r += arOther.r;
    g += arOther.g;
    b += arOther.b;
    a += arOther.a;
    return *this;
}

inline constexpr NiColorA& NiColorA::operator-=(const NiColorA& arOther) noexcept {
    r -= arOther.r;
    g -= arOther.g;
    b -= arOther.b;
    a -= arOther.a;
    return *this;
}

inline constexpr NiColorA& NiColorA::operator*=(const NiColorA& arOther) noexcept {
    r *= arOther.r;
    g *= arOther.g;
    b *= arOther.b;
    a *= arOther.a;
    return *this;
}

inline constexpr NiColorA& NiColorA::operator/=(const NiColorA& arOther) noexcept {
    r /= arOther.r;
    g /= arOther.g;
    b /= arOther.b;
    a /= arOther.a;
    return *this;
}

inline constexpr NiColorA& NiColorA::operator+=(float afVal) noexcept {
    r += afVal;
    g += afVal;
    b += afVal;
    a += afVal;
    return *this;
}

inline constexpr NiColorA& NiColorA::operator-=(float afVal) noexcept {
    r -= afVal;
    g -= afVal;
    b -= afVal;
    a -= afVal;
    return *this;
}

// GAME - 0x5321D0
inline constexpr NiColorA& NiColorA::operator*=(float afVal) noexcept {
    r *= afVal;
    g *= afVal;
    b *= afVal;
    a *= afVal;
    return *this;
}

inline constexpr NiColorA& NiColorA::operator/=(float afVal) noexcept {
    r /= afVal;
    g /= afVal;
    b /= afVal;
    a /= afVal;
    return *this;
}

// GAME - 0x532F40
inline constexpr NiColorA operator*(float afVal, const NiColorA& arOther) noexcept {
    return arOther * afVal;
}

inline constexpr void NiColorA::Scale() noexcept {
    float fMax = r;
    if (g > fMax)
        fMax = g;

    if (b > fMax)
        fMax = b;

    if (fMax > 1.f) {
        float fRecip = 1.f / fMax;
        r *= fRecip;
        g *= fRecip;
        b *= fRecip;
    }

    if (a > 1.f)
        a = 1.f;
}

inline constexpr void NiColorA::Clamp() noexcept {
    if (r > 1.f)
        r = 1.f;

    if (g > 1.f)
        g = 1.f;

    if (b > 1.f)
        b = 1.f;

    if (a > 1.f)
        a = 1.f;
}