#pragma once

#include "NiPoint2.hpp"

// GAME - 0x6815C0
inline constexpr NiPoint2::NiPoint2() noexcept {}

inline constexpr NiPoint2::NiPoint2(float afVal) noexcept : x(afVal), y(afVal) {}

// GAME - 0x452DC0
inline constexpr NiPoint2::NiPoint2(float afX, float afY) noexcept : x(afX), y(afY) {}

inline constexpr NiPoint2::NiPoint2(const NiPoint2& arOther) noexcept : x(arOther.x), y(arOther.y) {}

inline constexpr float& NiPoint2::operator[](uint32_t i) noexcept {
    ASSUME_ASSERT(i < 2);
    if consteval {
        switch (i) {
            case 0: return x;
            case 1: return y;
        }
    }
    else {
        return reinterpret_cast<float*>(this)[i];
    }
}

inline constexpr const float& NiPoint2::operator[](uint32_t i) const noexcept {
    ASSUME_ASSERT(i < 2);
    if consteval {
        switch (i) {
            case 0: return x;
            case 1: return y;
        }
    }
    else {
        return reinterpret_cast<const float*>(this)[i];
    }
}

inline constexpr NiPoint2::operator float*() noexcept {
	return &x;
}

// GAME - 0x452DF0
inline constexpr bool NiPoint2::operator==(const NiPoint2& arOther) const noexcept {
    return x == arOther.x && y == arOther.y;
}

inline constexpr NiPoint2 NiPoint2::operator-() const noexcept {
    return NiPoint2(-x, -y);
}

// GAME - 0x4DFE30
// GECK - 0x60B880
inline constexpr NiPoint2 NiPoint2::operator+(const NiPoint2& arOther) const noexcept { 
    return NiPoint2(x + arOther.x, y + arOther.y); 
}

// GAME - 0x4E8880
inline constexpr NiPoint2 NiPoint2::operator-(const NiPoint2& arOther) const noexcept { 
    return NiPoint2(x - arOther.x, y - arOther.y);
}

// GAME - 0x6B99E0
inline constexpr float    NiPoint2::operator*(const NiPoint2& arOther) const noexcept { 
    return x * arOther.x + y * arOther.y; 
}

inline constexpr NiPoint2 NiPoint2::operator/(const NiPoint2& arOther) const noexcept { 
    return NiPoint2(x / arOther.x, y / arOther.y); 
}

inline constexpr NiPoint2 NiPoint2::operator+(float afVal) const noexcept { 
    return NiPoint2(x + afVal, y + afVal); 
}

inline constexpr NiPoint2 NiPoint2::operator-(float afVal) const noexcept { 
    return NiPoint2(x - afVal, y - afVal); 
}

// GAME - 0x4A4F40
inline constexpr NiPoint2 NiPoint2::operator*(float afVal) const noexcept { 
    return NiPoint2(x * afVal, y * afVal); 
}

// GAME - 0x7F2890
inline constexpr NiPoint2 NiPoint2::operator/(float afVal) const noexcept { 
    return NiPoint2(x / afVal, y / afVal); 
}

// GAME - 0x4E88D0
inline constexpr NiPoint2& NiPoint2::operator+=(const NiPoint2& arOther) noexcept { 
    x += arOther.x; 
    y += arOther.y; 
    return *this; 
}

// GAME - 0x4E8910
inline constexpr NiPoint2& NiPoint2::operator-=(const NiPoint2& arOther) noexcept { 
    x -= arOther.x; 
    y -= arOther.y; 
    return *this; 
}

inline constexpr NiPoint2& NiPoint2::operator*=(const NiPoint2& arOther) noexcept { 
    x *= arOther.x; 
    y *= arOther.y; 
    return *this; 
}

inline constexpr NiPoint2& NiPoint2::operator/=(const NiPoint2& arOther) noexcept { 
    x /= arOther.x; 
    y /= arOther.y; 
    return *this; 
}

// GAME - 0x4E88D0
inline constexpr NiPoint2& NiPoint2::operator+=(float afVal) noexcept {
    x += afVal;
    y += afVal;
    return *this; 
}

inline constexpr NiPoint2& NiPoint2::operator-=(float afVal) noexcept {
    x -= afVal;
    y -= afVal;
    return *this; 
}

// GAME - 0x6AD180
inline constexpr NiPoint2& NiPoint2::operator*=(float afVal) noexcept {
    x *= afVal;
    y *= afVal;
    return *this; 
}

// GAME - 0x4E7530
inline constexpr NiPoint2& NiPoint2::operator/=(float afVal) noexcept {
    x /= afVal;
    y /= afVal;
    return *this; 
}

// GAME - 0x532FD0
inline constexpr NiPoint2 operator*(float afVal, const NiPoint2& arVec) noexcept {
    return arVec * afVal;
}

// GAME - 0x589850
inline constexpr float NiPoint2::Length() const noexcept {
    return std::sqrt(x * x + y * y);
}

// GAME - 0x595C80
inline constexpr float NiPoint2::SqrLength() const noexcept {
    return x * x + y * y;
}

// GAME - 0x6B99E0
inline constexpr float NiPoint2::Dot(const NiPoint2& arOther) const noexcept {
    return x * arOther.x + y * arOther.y;
}

// GAME - 0x4E7560
inline constexpr float NiPoint2::Unitize() noexcept {
    float fLength = Length();
    if (fLength <= 0.000001f) [[unlikely]] {
        x = 0.f;
        y = 0.f;
        return 0.f;
    }
    else [[likely]] {
        float fRecip = 1.f / fLength;
        x *= fRecip;
        y *= fRecip;
    }
    return fLength;
}