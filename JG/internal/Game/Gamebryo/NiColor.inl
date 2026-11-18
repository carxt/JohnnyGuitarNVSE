#pragma once

#include "NiColor.hpp"

inline constexpr NiColor::NiColor(float afValue) noexcept : r(afValue), g(afValue), b(afValue) {}

// GAME - 0x416870
inline constexpr NiColor::NiColor(float afR, float afG, float afB) noexcept : r(afR), g(afG), b(afB) {}

inline constexpr NiColor::NiColor(const NiColor& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b) {}

inline constexpr float& NiColor::operator[](uint32_t i) noexcept {
    ASSUME_ASSERT(i < 3);
    if consteval {
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
        }
    }
    else {
        return reinterpret_cast<float*>(this)[i];
    }
}

inline constexpr const float& NiColor::operator[](uint32_t i) const noexcept {
    ASSUME_ASSERT(i < 3);
    if consteval {
        switch (i) {
            case 0: return r;
            case 1: return g;
            case 2: return b;
        }
    }
    else {
        return reinterpret_cast<const float*>(this)[i];
    }
}

inline constexpr NiColor::operator float* () noexcept {
    return &r;
}

inline constexpr bool NiColor::operator==(const NiColor& arOther) const noexcept {
    return r == arOther.r && g == arOther.g && b == arOther.b;
}

// GAME - 0x4A0BD0
inline constexpr NiColor NiColor::operator-() const noexcept {
    return NiColor(-r, -g, -b);
}

// GAME - 0x7FB730
inline constexpr NiColor NiColor::operator+(const NiColor& arOther) const noexcept {
    return NiColor(r + arOther.r, g + arOther.g, b + arOther.b);
}

inline constexpr NiColor NiColor::operator-(const NiColor& arOther) const noexcept {
    return NiColor(r - arOther.r, g - arOther.g, b - arOther.b);
}

inline constexpr float   NiColor::operator*(const NiColor& arOther) const noexcept {
    return r * arOther.r + g * arOther.g + b * arOther.b;
}

inline constexpr NiColor NiColor::operator/(const NiColor& arOther) const noexcept {
    return NiColor(r / arOther.r, g / arOther.g, b / arOther.b);
}

inline constexpr NiColor NiColor::operator+(float afVal) const noexcept {
    return NiColor(r + afVal, g + afVal, b + afVal);
}

inline constexpr NiColor NiColor::operator-(float afVal) const noexcept {
    return NiColor(r - afVal, g - afVal, b - afVal);
}

// GAME - 0x633B40
inline constexpr NiColor NiColor::operator*(float afVal) const noexcept {
    return NiColor(r * afVal, g * afVal, b * afVal);
}

inline constexpr NiColor NiColor::operator/(float afVal) const noexcept {
    return NiColor(r / afVal, g / afVal, b / afVal);
}

// GAME - 0x63C8A0
inline constexpr NiColor& NiColor::operator+=(const NiColor& arOther) noexcept {
    r += arOther.r;
    g += arOther.g;
    b += arOther.b;
    return *this;
}

inline constexpr NiColor& NiColor::operator-=(const NiColor& arOther) noexcept {
    r -= arOther.r;
    g -= arOther.g;
    b -= arOther.b;
    return *this;
}

inline constexpr NiColor& NiColor::operator*=(const NiColor& arOther) noexcept {
    r *= arOther.r;
    g *= arOther.g;
    b *= arOther.b;
    return *this;
}

// GAME - 0x80ED20
inline constexpr NiColor& NiColor::operator/=(const NiColor& arOther) noexcept {
    r /= arOther.r;
    g /= arOther.g;
    b /= arOther.b;
    return *this;
}

inline constexpr NiColor& NiColor::operator+=(float afVal) noexcept {
    r += afVal;
    g += afVal;
    b += afVal;
    return *this;
}

inline constexpr NiColor& NiColor::operator-=(float afVal) noexcept {
    r -= afVal;
    g -= afVal;
    b -= afVal;
    return *this;
}

// GAME - 0x439180
inline constexpr NiColor& NiColor::operator*=(float afVal) noexcept {
    r *= afVal;
    g *= afVal;
    b *= afVal;
    return *this;
}

inline constexpr NiColor& NiColor::operator/=(float afVal) noexcept {
    r /= afVal;
    g /= afVal;
    b /= afVal;
    return *this;
}

inline constexpr NiColor operator*(float afVal, const NiColor& arOther) noexcept {
    return NiColor(arOther.r * afVal, arOther.g * afVal, arOther.b * afVal);
}

inline constexpr void NiColor::Scale() noexcept {
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
}

// GAME - 0xA69690
inline constexpr void NiColor::Clamp() noexcept {
    if (r > 1.f)
        r = 1.f;

    if (g > 1.f)
        g = 1.f;

    if (b > 1.f)
        b = 1.f;
}

// GAME - 0xB719E0
inline constexpr float NiColor::Luminance() const noexcept {
    return g * 0.36f + r * 0.31f + b * 0.32f;
}