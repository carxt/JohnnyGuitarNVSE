#include "NiPoint2.hpp"
#include "NiPoint3.hpp"
#include "NiPoint4.hpp"

// GAME - 0x11F4980
const NiPoint2 NiPoint2::ZERO	= { 0.f, 0.f };

// GAME - 0x11A9B48
const NiPoint2 NiPoint2::UNIT_X	= { 1.f, 0.f };

// GAME - 0x11A9B50
const NiPoint2 NiPoint2::UNIT_Y	= { 0.f, 1.f };

// GAME - 0x6815C0
NiPoint2::NiPoint2() noexcept {}

NiPoint2::NiPoint2(float afVal) noexcept : x(afVal), y(afVal) {}

// GAME - 0x452DC0
NiPoint2::NiPoint2(float afX, float afY) noexcept : x(afX), y(afY) {}

NiPoint2::NiPoint2(const NiPoint2& arOther) noexcept : x(arOther.x), y(arOther.y) {}

NiPoint2::NiPoint2(const NiPoint3& arOther) noexcept : x(arOther.x), y(arOther.y) {}

NiPoint2::NiPoint2(const NiPoint4& arOther) noexcept : x(arOther.x), y(arOther.y) {}

float& NiPoint2::operator[](uint32_t i) noexcept {
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

const float& NiPoint2::operator[](uint32_t i) const noexcept {
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

NiPoint2::operator float*() noexcept {
	return &x;
}

// GAME - 0x452DF0
bool NiPoint2::operator==(const NiPoint2& arOther) const noexcept {
    return x == arOther.x && y == arOther.y;
}

NiPoint2 NiPoint2::operator-() const noexcept {
    return NiPoint2(-x, -y);
}

// GAME - 0x4DFE30
// GECK - 0x60B880
NiPoint2 NiPoint2::operator+(const NiPoint2& arOther) const noexcept { 
    return NiPoint2(x + arOther.x, y + arOther.y); 
}

// GAME - 0x4E8880
NiPoint2 NiPoint2::operator-(const NiPoint2& arOther) const noexcept { 
    return NiPoint2(x - arOther.x, y - arOther.y);
}

// GAME - 0x6B99E0
float    NiPoint2::operator*(const NiPoint2& arOther) const noexcept { 
    return x * arOther.x + y * arOther.y; 
}

NiPoint2 NiPoint2::operator/(const NiPoint2& arOther) const noexcept { 
    return NiPoint2(x / arOther.x, y / arOther.y); 
}

NiPoint2 NiPoint2::operator+(float afVal) const noexcept { 
    return NiPoint2(x + afVal, y + afVal); 
}

NiPoint2 NiPoint2::operator-(float afVal) const noexcept { 
    return NiPoint2(x - afVal, y - afVal); 
}

// GAME - 0x4A4F40
NiPoint2 NiPoint2::operator*(float afVal) const noexcept { 
    return NiPoint2(x * afVal, y * afVal); 
}

// GAME - 0x7F2890
NiPoint2 NiPoint2::operator/(float afVal) const noexcept { 
    return NiPoint2(x / afVal, y / afVal); 
}

// GAME - 0x4E88D0
NiPoint2& NiPoint2::operator+=(const NiPoint2& arOther) noexcept { 
    x += arOther.x; 
    y += arOther.y; 
    return *this; 
}

// GAME - 0x4E8910
NiPoint2& NiPoint2::operator-=(const NiPoint2& arOther) noexcept { 
    x -= arOther.x; 
    y -= arOther.y; 
    return *this; 
}

NiPoint2& NiPoint2::operator*=(const NiPoint2& arOther) noexcept { 
    x *= arOther.x; 
    y *= arOther.y; 
    return *this; 
}

NiPoint2& NiPoint2::operator/=(const NiPoint2& arOther) noexcept { 
    x /= arOther.x; 
    y /= arOther.y; 
    return *this; 
}

// GAME - 0x4E88D0
NiPoint2& NiPoint2::operator+=(float afVal) noexcept {
    x += afVal;
    y += afVal;
    return *this; 
}

NiPoint2& NiPoint2::operator-=(float afVal) noexcept {
    x -= afVal;
    y -= afVal;
    return *this; 
}

// GAME - 0x6AD180
NiPoint2& NiPoint2::operator*=(float afVal) noexcept {
    x *= afVal;
    y *= afVal;
    return *this; 
}

// GAME - 0x4E7530
NiPoint2& NiPoint2::operator/=(float afVal) noexcept {
    x /= afVal;
    y /= afVal;
    return *this; 
}

// GAME - 0x532FD0
NiPoint2 operator*(float afVal, const NiPoint2& arVec) noexcept {
    return arVec * afVal;
}

bool NiPoint2::IsOk() const noexcept {
    return x != FLT_MAX && _isnan(x) == 0 && _finite(x) != 0
        && y != FLT_MAX && _isnan(y) == 0 && _finite(y) != 0;
}

// GAME - 0x589850
float NiPoint2::Length() const noexcept {
    return std::sqrt(x * x + y * y);
}

// GAME - 0x595C80
float NiPoint2::SqrLength() const noexcept {
    return x * x + y * y;
}

// GAME - 0x6B99E0
float NiPoint2::Dot(const NiPoint2& arOther) const noexcept {
    return x * arOther.x + y * arOther.y;
}

// GAME - 0x4E7560
float NiPoint2::Unitize() noexcept {
    const float fLength = Length();
    if (fLength <= 0.000001f) [[unlikely]] {
        x = 0.f;
        y = 0.f;
        return 0.f;
    }
    else [[likely]] {
        const float fRecip = 1.f / fLength;
        x *= fRecip;
        y *= fRecip;
    }
    return fLength;
}