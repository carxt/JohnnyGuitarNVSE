#include "NiPoint3.hpp"
#include "NiPoint2.hpp"
#include "NiPoint4.hpp"

#if USE_DXMATH
#include <DirectXMath.h>
#endif

// GAME - 0x11A946C
const NiPoint3 NiPoint3::UNIT_X		= { 1.f, 0.f, 0.f };

// GAME - 0x11A9478
const NiPoint3 NiPoint3::UNIT_Y		= { 0.f, 1.f, 0.f };

// GAME - 0x11A9484
const NiPoint3 NiPoint3::UNIT_Z		= { 0.f, 0.f, 1.f };

// GAME - 0x11A9490
const NiPoint3 NiPoint3::UNIT_ALL	= { 1.f, 1.f, 1.f };

// GAME - 0x11F426C
const NiPoint3 NiPoint3::ZERO		= { 0.f, 0.f, 0.f };

// GAME - 0x6815C0
NiPoint3::NiPoint3() noexcept {}

NiPoint3::NiPoint3(float afValue) noexcept : x(afValue), y(afValue), z(afValue) {}

// GAME - 0x416870
NiPoint3::NiPoint3(float afX, float afY, float afZ) noexcept : x(afX), y(afY), z(afZ) {}

NiPoint3::NiPoint3(const NiPoint3& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z) {}

NiPoint3::NiPoint3(const NiPoint2& arOther) noexcept : x(arOther.x), y(arOther.y), z(0.f) {}

NiPoint3::NiPoint3(const NiPoint4& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z) {}

float& NiPoint3::operator[](uint32_t i) noexcept {
    ASSUME_ASSERT(i < 3);
    if consteval {
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

const float& NiPoint3::operator[](uint32_t i) const noexcept {
    ASSUME_ASSERT(i < 3);
    if consteval {
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

NiPoint3::operator float* () noexcept {
    return &x;
}

bool NiPoint3::operator==(const NiPoint3& arOther) const noexcept {
    return x == arOther.x && y == arOther.y && z == arOther.z;
}

NiPoint3 NiPoint3::operator-() const noexcept {
    return NiPoint3(-x, -y, -z);
}

NiPoint3 NiPoint3::operator+(const NiPoint3& arOther) const noexcept {
    return NiPoint3(x + arOther.x, y + arOther.y, z + arOther.z);
}

NiPoint3 NiPoint3::operator-(const NiPoint3& arOther) const noexcept {
    return NiPoint3(x - arOther.x, y - arOther.y, z - arOther.z);
}

float    NiPoint3::operator*(const NiPoint3& arOther) const noexcept {
    return x * arOther.x + y * arOther.y + z * arOther.z;
}

NiPoint3 NiPoint3::operator/(const NiPoint3& arOther) const noexcept {
    return NiPoint3(x / arOther.x, y / arOther.y, z / arOther.z);
}

NiPoint3 NiPoint3::operator+(float afVal) const noexcept {
    return NiPoint3(x + afVal, y + afVal, z + afVal);
}

NiPoint3 NiPoint3::operator-(float afVal) const noexcept {
    return NiPoint3(x - afVal, y - afVal, z - afVal);
}

NiPoint3 NiPoint3::operator*(float afVal) const noexcept {
    return NiPoint3(x * afVal, y * afVal, z * afVal);
}

NiPoint3 NiPoint3::operator/(float afVal) const noexcept {
    return NiPoint3(x / afVal, y / afVal, z / afVal);
}

NiPoint3& NiPoint3::operator+=(const NiPoint3& arOther) noexcept {
    x += arOther.x;
    y += arOther.y;
    z += arOther.z;
    return *this;
}

NiPoint3& NiPoint3::operator-=(const NiPoint3& arOther) noexcept {
    x -= arOther.x;
    y -= arOther.y;
    z -= arOther.z;
    return *this;
}

NiPoint3& NiPoint3::operator*=(const NiPoint3& arOther) noexcept {
    x *= arOther.x;
    y *= arOther.y;
    z *= arOther.z;
    return *this;
}

NiPoint3& NiPoint3::operator/=(const NiPoint3& arOther) noexcept {
    x /= arOther.x;
    y /= arOther.y;
    z /= arOther.z;
    return *this;
}

NiPoint3& NiPoint3::operator+=(float afVal) noexcept {
    x += afVal;
    y += afVal;
    z += afVal;
    return *this;
}

NiPoint3& NiPoint3::operator-=(float afVal) noexcept {
    x -= afVal;
    y -= afVal;
    z -= afVal;
    return *this;
}

NiPoint3& NiPoint3::operator*=(float afVal) noexcept {
    x *= afVal;
    y *= afVal;
    z *= afVal;
    return *this;
}

NiPoint3& NiPoint3::operator/=(float afVal) noexcept {
    x /= afVal;
    y /= afVal;
    z /= afVal;
    return *this;
}

NiPoint3 operator*(float afVal, const NiPoint3& arVec) noexcept {
    return NiPoint3(arVec.x * afVal, arVec.y * afVal, arVec.z * afVal);
}

void NiPoint3::operator=(const NiPoint2& arOther) noexcept {
    x = arOther.x;
    y = arOther.y;
}

bool NiPoint3::IsOk() const noexcept {
    return x != FLT_MAX && _isnan(x) == 0 && _finite(x) != 0
        && y != FLT_MAX && _isnan(y) == 0 && _finite(y) != 0
        && z != FLT_MAX && _isnan(z) == 0 && _finite(z) != 0;
}

// GAME - 0x457990
// GECK - 0x40B3D0
float NiPoint3::Length() const noexcept {
    return std::sqrt(x * x + y * y + z * z);
}

// GAME - 0x595C80
float NiPoint3::XYLength() const noexcept {
    return std::sqrt(x * x + y * y);
}

// GAME - 0x4A7290
float NiPoint3::SqrLength() const noexcept {
    return x * x + y * y + z * z;
}

// GAME - 0x595C80
float NiPoint3::SqrXYLength() const noexcept {
    return x * x + y * y;
}

int32_t NiPoint3::LengthCheck(float afLength) const noexcept {
    const float fOurSqrLength = SqrLength();
    const float fSqrLength = afLength * afLength;
    if (fSqrLength <= fOurSqrLength)
        return fSqrLength < fOurSqrLength;
    else
        return -1;
}

int32_t NiPoint3::LengthCheck(const NiPoint3& arOther, float afLength) const noexcept {
    return (*this - arOther).LengthCheck(afLength);
}

// GAME - 0x4B6190
float NiPoint3::Dot(const NiPoint3& arOther) const noexcept {
    return x * arOther.x + y * arOther.y + z * arOther.z;
}

float NiPoint3::DotXY(const NiPoint3& arOther) const noexcept {
    return x * arOther.x + y * arOther.y;
}

// GAME - 0x4B3800
// GECK - 0x463390
NiPoint3 NiPoint3::Cross(const NiPoint3& arOther) const noexcept {
    return NiPoint3(y * arOther.z - z * arOther.y,
        z * arOther.x - x * arOther.z,
        x * arOther.y - y * arOther.x);
}

// GAME - 0x53D1A0
// GECK - 0x41F120
NiPoint3 NiPoint3::UnitCross(const NiPoint3& arOther) const noexcept {
    NiPoint3 kCross = Cross(arOther);
    float fLength = kCross.Length();
    if (fLength > 0.000001f)
        return kCross / fLength;
    else
        return NiPoint3::ZERO;
}

// GAME - 0x4A0C10
// GECK - 0x40B400
void NiPoint3::Unitize() noexcept {
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
float NiPoint3::UnitizeGetLength() noexcept {
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
    return fLength;
}

// GAME - 0x525340
void NiPoint3::UnitizeVector(NiPoint3& arVector) noexcept {
#if USE_DXMATH
    DirectX::XMVECTOR kV = DirectX::XMLoadNiPoint3(arVector);
    kV = DirectX::XMVector3Normalize(kV);
    DirectX::XMStoreNiPoint3(arVector, kV);
#else
    CdeclCall(0x525340, &arVector);
#endif
}

// GAME - 0xA7E960
void NiPoint3::UnitizeVectors(NiPoint3* apVectors, uint32_t auiCount, uint32_t auiStride) noexcept {
#if USE_DXMATH
    for (uint32_t i = 0; i < auiCount; ++i) {
        DirectX::XMFLOAT3& rVector = *reinterpret_cast<DirectX::XMFLOAT3*>(reinterpret_cast<uintptr_t>(apVectors) + i * auiStride);
        DirectX::XMVECTOR kV = DirectX::XMLoadFloat3(&rVector);
        kV = DirectX::XMVector3Normalize(kV);
        DirectX::XMStoreFloat3(&rVector, kV);
    }
#else
    CdeclCall(0xA7E960, apVectors, auiCount, auiStride);
#endif
}

float NiPoint3::Distance(const NiPoint3& arOther) const noexcept {
    return (*this - arOther).Length();
}

float NiPoint3::SqrDistance(const NiPoint3& arOther) const noexcept {
    return (*this - arOther).SqrLength();
}

bool NiPoint3::CloseEnough(const NiPoint3& arOther, float afDelta) const noexcept {
    return std::fabs(x - arOther.x) < afDelta
        && std::fabs(y - arOther.y) < afDelta
        && std::fabs(z - arOther.z) < afDelta;
}

bool NiPoint3::CloseEnoughXY(const NiPoint3& arOther, float afDelta) const noexcept {
    return std::fabs(x - arOther.x) < afDelta
        && std::fabs(y - arOther.y) < afDelta;
}