#include "NiColor.hpp"
#include "NiPoint3.hpp"
#include "NiColorA.hpp"

// GAME - 0x11F4998
const NiColor NiColor::BLACK	= { 0.f, 0.f, 0.f };

// GAME - 0x11A9B7C
const NiColor NiColor::WHITE	= { 1.f, 1.f, 1.f };

// GAME - 0x11A9B88
const NiColor NiColor::RED		= { 1.f, 0.f, 0.f };

// GAME - 0x11A9B94
const NiColor NiColor::GREEN	= { 0.f, 1.f, 0.f };

// GAME - 0x11A9BA0
const NiColor NiColor::BLUE		= { 0.f, 0.f, 1.f };

// GAME - 0x11A9BAC
const NiColor NiColor::YELLOW	= { 1.f, 1.f, 0.f };

// GAME - 0x11A9BB8
const NiColor NiColor::MAGENTA  = { 1.f, 0.f, 1.f };

// GAME - 0x11A9BC4
const NiColor NiColor::CYAN		= { 0.f, 1.f, 1.f };

// GAME - 0x6815C0
NiColor::NiColor() noexcept {}

NiColor::NiColor(float afValue) noexcept : r(afValue), g(afValue), b(afValue) {}

// GAME - 0x416870
NiColor::NiColor(float afR, float afG, float afB) noexcept : r(afR), g(afG), b(afB) {}

NiColor::NiColor(const NiColor& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b) {}

NiColor::NiColor(const NiPoint3& arOther) noexcept : r(arOther.x), g(arOther.y), b(arOther.z) {}

NiColor::NiColor(const NiColorA& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b) {}

float& NiColor::operator[](uint32_t i) noexcept {
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

const float& NiColor::operator[](uint32_t i) const noexcept {
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

NiColor::operator float* () noexcept {
    return &r;
}

bool NiColor::operator==(const NiColor& arOther) const noexcept {
    return r == arOther.r && g == arOther.g && b == arOther.b;
}

// GAME - 0x4A0BD0
NiColor NiColor::operator-() const noexcept {
    return NiColor(-r, -g, -b);
}

// GAME - 0x7FB730
NiColor NiColor::operator+(const NiColor& arOther) const noexcept {
    return NiColor(r + arOther.r, g + arOther.g, b + arOther.b);
}

NiColor NiColor::operator-(const NiColor& arOther) const noexcept {
    return NiColor(r - arOther.r, g - arOther.g, b - arOther.b);
}

float    NiColor::operator*(const NiColor& arOther) const noexcept {
    return r * arOther.r + g * arOther.g + b * arOther.b;
}

NiColor NiColor::operator/(const NiColor& arOther) const noexcept {
    return NiColor(r / arOther.r, g / arOther.g, b / arOther.b);
}

NiColor NiColor::operator+(float afVal) const noexcept {
    return NiColor(r + afVal, g + afVal, b + afVal);
}

NiColor NiColor::operator-(float afVal) const noexcept {
    return NiColor(r - afVal, g - afVal, b - afVal);
}

// GAME - 0x633B40
NiColor NiColor::operator*(float afVal) const noexcept {
    return NiColor(r * afVal, g * afVal, b * afVal);
}

NiColor NiColor::operator/(float afVal) const noexcept {
    return NiColor(r / afVal, g / afVal, b / afVal);
}

// GAME - 0x63C8A0
NiColor& NiColor::operator+=(const NiColor& arOther) noexcept {
    r += arOther.r;
    g += arOther.g;
    b += arOther.b;
    return *this;
}

NiColor& NiColor::operator-=(const NiColor& arOther) noexcept {
    r -= arOther.r;
    g -= arOther.g;
    b -= arOther.b;
    return *this;
}

NiColor& NiColor::operator*=(const NiColor& arOther) noexcept {
    r *= arOther.r;
    g *= arOther.g;
    b *= arOther.b;
    return *this;
}

// GAME - 0x80ED20
NiColor& NiColor::operator/=(const NiColor& arOther) noexcept {
    r /= arOther.r;
    g /= arOther.g;
    b /= arOther.b;
    return *this;
}

NiColor& NiColor::operator+=(float afVal) noexcept {
    r += afVal;
    g += afVal;
    b += afVal;
    return *this;
}

NiColor& NiColor::operator-=(float afVal) noexcept {
    r -= afVal;
    g -= afVal;
    b -= afVal;
    return *this;
}

// GAME - 0x439180
NiColor& NiColor::operator*=(float afVal) noexcept {
    r *= afVal;
    g *= afVal;
    b *= afVal;
    return *this;
}

NiColor& NiColor::operator/=(float afVal) noexcept {
    r /= afVal;
    g /= afVal;
    b /= afVal;
    return *this;
}

NiColor operator*(float afVal, const NiColor& arOther) noexcept {
    return NiColor(arOther.r * afVal, arOther.g * afVal, arOther.b * afVal);
}

void NiColor::Scale() noexcept {
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
void NiColor::Clamp() noexcept {
    if (r > 1.f)
        r = 1.f;

    if (g > 1.f)
        g = 1.f;

    if (b > 1.f)
        b = 1.f;
}

// GAME - 0xB719E0
float NiColor::Luminance() const noexcept {
    return g * 0.36f + r * 0.31f + b * 0.32f;
}