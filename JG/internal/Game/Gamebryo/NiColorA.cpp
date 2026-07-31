#include "NiColorA.hpp"
#include "NiColor.hpp"
#include "NiPoint3.hpp"
#include "NiPoint4.hpp"

// GAME - 0x11A9BD0
const NiColorA NiColorA::BLACK	    = { 0.f, 0.f, 0.f, 1.f };

// GAME - 0x11A9BE0
const NiColorA NiColorA::WHITE	    = { 1.f, 1.f, 1.f, 1.f };

// GAME - 0x11A9BF0
const NiColorA NiColorA::RED	    = { 1.f, 0.f, 0.f, 1.f };

// GAME - 0x11A9C00
const NiColorA NiColorA::GREEN	    = { 0.f, 1.f, 0.f, 1.f };

// GAME - 0x11A9C10
const NiColorA NiColorA::BLUE	    = { 0.f, 0.f, 1.f, 1.f };

// GAME - 0x11A9C20
const NiColorA NiColorA::YELLOW	    = { 1.f, 1.f, 0.f, 1.f };

// GAME - 0x11A9C30
const NiColorA NiColorA::MAGENTA    = { 1.f, 0.f, 1.f, 1.f };

// GAME - 0x11A9C40
const NiColorA NiColorA::CYAN		= { 0.f, 1.f, 1.f, 1.f };

// GAME - 0x6815C0
NiColorA::NiColorA() noexcept {}

NiColorA::NiColorA(float afValue) noexcept : r(afValue), g(afValue), b(afValue), a(1.f) {}

NiColorA::NiColorA(float afR, float afG, float afB) noexcept : r(afR), g(afG), b(afB), a(1.f) {}

// GAME - 0x414430
NiColorA::NiColorA(float afR, float afG, float afB, float afA) noexcept : r(afR), g(afG), b(afB), a(afA) {}

NiColorA::NiColorA(const NiColorA& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b), a(arOther.a) {}

NiColorA::NiColorA(const NiPoint3& arOther) noexcept : r(arOther.x), g(arOther.y), b(arOther.z), a(1.f) {}

NiColorA::NiColorA(const NiPoint4& arOther) noexcept : r(arOther.x), g(arOther.y), b(arOther.z), a(arOther.w) {}

NiColorA::NiColorA(const NiColor& arOther) noexcept : r(arOther.r), g(arOther.g), b(arOther.b), a(1.f) {}

float& NiColorA::operator[](uint32_t i) noexcept {
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

const float& NiColorA::operator[](uint32_t i) const noexcept {
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

NiColorA::operator float* () noexcept {
    return &r;
}

// GAME - 0x4A4CC0
bool NiColorA::operator==(const NiColorA& arOther) const noexcept {
    return r == arOther.r && g == arOther.g && b == arOther.b && a == arOther.a;
}

NiColorA NiColorA::operator-() const noexcept {
    return NiColorA(-r, -g, -b, -a);
}

// GAME - 0x532E40
NiColorA NiColorA::operator+(const NiColorA& arOther) const noexcept {
    return NiColorA(r + arOther.r, g + arOther.g, b + arOther.b, a + arOther.a);
}

// GAME - 0x532EC0
NiColorA NiColorA::operator-(const NiColorA& arOther) const noexcept {
    return NiColorA(r - arOther.r, g - arOther.g, b - arOther.b, a - arOther.a);
}

NiColorA NiColorA::operator*(const NiColorA& arOther) const noexcept {
    return NiColorA(r * arOther.r, g * arOther.g, b * arOther.b, a * arOther.a);
}

NiColorA NiColorA::operator/(const NiColorA& arOther) const noexcept {
    return NiColorA(r / arOther.r, g / arOther.g, b / arOther.b, a / arOther.a);
}

NiColorA NiColorA::operator+(float afVal) const noexcept {
    return NiColorA(r + afVal, g + afVal, b + afVal, a + afVal);
}

NiColorA NiColorA::operator-(float afVal) const noexcept {
    return NiColorA(r - afVal, g - afVal, b - afVal, a - afVal);
}

// GAME - 0x532F60
NiColorA NiColorA::operator*(float afVal) const noexcept {
    return NiColorA(r * afVal, g * afVal, b * afVal, a * afVal);
}

// GAME - 0x5074E0
NiColorA NiColorA::operator/(float afVal) const noexcept {
    return NiColorA(r / afVal, g / afVal, b / afVal, a / afVal);
}

NiColorA& NiColorA::operator+=(const NiColorA& arOther) noexcept {
    r += arOther.r;
    g += arOther.g;
    b += arOther.b;
    a += arOther.a;
    return *this;
}

NiColorA& NiColorA::operator-=(const NiColorA& arOther) noexcept {
    r -= arOther.r;
    g -= arOther.g;
    b -= arOther.b;
    a -= arOther.a;
    return *this;
}

NiColorA& NiColorA::operator*=(const NiColorA& arOther) noexcept {
    r *= arOther.r;
    g *= arOther.g;
    b *= arOther.b;
    a *= arOther.a;
    return *this;
}

NiColorA& NiColorA::operator/=(const NiColorA& arOther) noexcept {
    r /= arOther.r;
    g /= arOther.g;
    b /= arOther.b;
    a /= arOther.a;
    return *this;
}

NiColorA& NiColorA::operator+=(float afVal) noexcept {
    r += afVal;
    g += afVal;
    b += afVal;
    a += afVal;
    return *this;
}

NiColorA& NiColorA::operator-=(float afVal) noexcept {
    r -= afVal;
    g -= afVal;
    b -= afVal;
    a -= afVal;
    return *this;
}

// GAME - 0x5321D0
NiColorA& NiColorA::operator*=(float afVal) noexcept {
    r *= afVal;
    g *= afVal;
    b *= afVal;
    a *= afVal;
    return *this;
}

NiColorA& NiColorA::operator/=(float afVal) noexcept {
    r /= afVal;
    g /= afVal;
    b /= afVal;
    a /= afVal;
    return *this;
}

// GAME - 0x532F40
NiColorA operator*(float afVal, const NiColorA& arOther) noexcept {
    return arOther * afVal;
}

void NiColorA::Scale() noexcept {
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

void NiColorA::Clamp() noexcept {
    if (r > 1.f)
        r = 1.f;

    if (g > 1.f)
        g = 1.f;

    if (b > 1.f)
        b = 1.f;

    if (a > 1.f)
        a = 1.f;
}