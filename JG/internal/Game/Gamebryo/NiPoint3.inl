#pragma once

#include "NiPoint3.hpp"

// GAME - 0x6815C0
inline NiPoint3::NiPoint3() noexcept {}

inline NiPoint3::NiPoint3(float afValue) noexcept : x(afValue), y(afValue), z(afValue) {}

// GAME - 0x416870
inline NiPoint3::NiPoint3(float afX, float afY, float afZ) noexcept : x(afX), y(afY), z(afZ) {}

inline NiPoint3::NiPoint3(const NiPoint3& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z) {}

inline float& NiPoint3::operator[](uint32_t i) noexcept {
    ASSUME_ASSERT(i < 3);
    if (std::is_constant_evaluated()) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
    }
    else {
        return reinterpret_cast<float*>(this)[i];
    }
}

inline const float& NiPoint3::operator[](uint32_t i) const noexcept {
    ASSUME_ASSERT(i < 3);
    if (std::is_constant_evaluated()) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
    }
    else {
        return reinterpret_cast<const float*>(this)[i];
    }
}

inline NiPoint3::operator float*() noexcept {
	return &x;
}

inline bool NiPoint3::operator==(const NiPoint3& arOther) const noexcept {
    return x == arOther.x && y == arOther.y && z == arOther.z; 
}

inline NiPoint3 NiPoint3::operator-() const noexcept {
    return NiPoint3(-x, -y, -z); 
}

inline NiPoint3 NiPoint3::operator+(const NiPoint3& arOther) const noexcept {
    return NiPoint3(x + arOther.x, y + arOther.y, z + arOther.z); 
}

inline NiPoint3 NiPoint3::operator-(const NiPoint3& arOther) const noexcept {
    return NiPoint3(x - arOther.x, y - arOther.y, z - arOther.z); 
}

inline float    NiPoint3::operator*(const NiPoint3& arOther) const noexcept {
    return x * arOther.x + y * arOther.y + z * arOther.z; 
}

inline NiPoint3 NiPoint3::operator/(const NiPoint3& arOther) const noexcept {
    return NiPoint3(x / arOther.x, y / arOther.y, z / arOther.z); 
}

inline NiPoint3 NiPoint3::operator+(float afVal) const noexcept {
    return NiPoint3(x + afVal, y + afVal, z + afVal); 
}

inline NiPoint3 NiPoint3::operator-(float afVal) const noexcept {
    return NiPoint3(x - afVal, y - afVal, z - afVal); 
}

inline NiPoint3 NiPoint3::operator*(float afVal) const noexcept {
    return NiPoint3(x * afVal, y * afVal, z * afVal); 
}

inline NiPoint3 NiPoint3::operator/(float afVal) const noexcept {
    return NiPoint3(x / afVal, y / afVal, z / afVal); 
}

inline NiPoint3& NiPoint3::operator+=(const NiPoint3& arOther) noexcept {
    x += arOther.x;
    y += arOther.y;
    z += arOther.z;
    return *this;
}

inline NiPoint3& NiPoint3::operator-=(const NiPoint3& arOther) noexcept {
    x -= arOther.x;
    y -= arOther.y;
    z -= arOther.z;
    return *this;
}

inline NiPoint3& NiPoint3::operator*=(const NiPoint3& arOther) noexcept {
    x *= arOther.x;
    y *= arOther.y;
    z *= arOther.z;
    return *this;
}

inline NiPoint3& NiPoint3::operator/=(const NiPoint3& arOther) noexcept {
    x /= arOther.x;
    y /= arOther.y;
    z /= arOther.z;
    return *this;
}

inline NiPoint3& NiPoint3::operator+=(float afVal) noexcept {
    x += afVal;
    y += afVal;
    z += afVal;
    return *this;
}

inline NiPoint3& NiPoint3::operator-=(float afVal) noexcept {
    x -= afVal;
    y -= afVal;
    z -= afVal;
    return *this;
}

inline NiPoint3& NiPoint3::operator*=(float afVal) noexcept {
    x *= afVal;
    y *= afVal;
    z *= afVal;
    return *this;
}

inline NiPoint3& NiPoint3::operator/=(float afVal) noexcept {
    x /= afVal;
    y /= afVal;
    z /= afVal;
    return *this;
}

inline NiPoint3 operator*(float afVal, const NiPoint3& arVec) noexcept {
    return NiPoint3(arVec.x * afVal, arVec.y * afVal, arVec.z * afVal);
}

// GAME - 0x457990
// GECK - 0x40B3D0
inline float NiPoint3::Length() const noexcept {
    return std::sqrt(x * x + y * y + z * z);
}

// GAME - 0x595C80
inline float NiPoint3::XYLength() const noexcept {
    return std::sqrt(x * x + y * y);
}

// GAME - 0x4A7290
inline float NiPoint3::SqrLength() const noexcept {
    return x * x + y * y + z * z;
}

// GAME - 0x595C80
inline float NiPoint3::SqrXYLength() const noexcept {
    return x * x + y * y;
}

// GAME - 0x4B6190
float NiPoint3::Dot(const NiPoint3& arOther) const noexcept {
    return x * arOther.x + y * arOther.y + z * arOther.z;
}

// GAME - 0x4B3800
// GECK - 0x463390
inline NiPoint3 NiPoint3::Cross(const NiPoint3& arOther) const noexcept {
    return NiPoint3(y * arOther.z - z * arOther.y,
                    z * arOther.x - x * arOther.z,
                    x * arOther.y - y * arOther.x);
}

// GAME - 0x53D1A0
// GECK - 0x41F120
inline NiPoint3 NiPoint3::UnitCross(const NiPoint3& arOther) const noexcept {
    NiPoint3 kCross = Cross(arOther);
    float fLength = kCross.Length();
    if (fLength > 0.000001f)
        return kCross / fLength;
    else
        return NiPoint3::ZERO;
}

// GAME - 0x4A0C10
// GECK - 0x40B400
inline void NiPoint3::Unitize() noexcept {
    const float fLength = Length();
    if (fLength <= 0.000001f) [[unlikely]] {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }
    else [[likely]] {
        const float fRecip = 1.f / fLength;
        x *= fRecip;
        y *= fRecip;
        z *= fRecip;
    }
}

// GAME - 0x457910
inline float NiPoint3::UnitizeGetLength() noexcept {
    float fLength = Length();
    if (fLength <= 0.000001f) [[unlikely]] {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    }
    else [[likely]] {
        float fRecip = 1.f / fLength;
        x *= fRecip;
        y *= fRecip;
        z *= fRecip;
    }
    return fLength;
}

inline float NiPoint3::Distance(const NiPoint3& arOther) const noexcept {
    return (*this - arOther).Length();
}

inline float NiPoint3::SqrDistance(const NiPoint3& arOther) const noexcept {
    return (*this - arOther).SqrLength();
}
