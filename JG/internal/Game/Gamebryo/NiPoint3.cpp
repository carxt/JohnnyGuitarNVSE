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

NiPoint3::NiPoint3(const NiPoint2& arOther) noexcept : x(arOther.x), y(arOther.y), z(0.f) {}

NiPoint3::NiPoint3(const NiPoint4& arOther) noexcept : x(arOther.x), y(arOther.y), z(arOther.z) {}

void NiPoint3::operator=(const NiPoint2& arOther) noexcept {
	x = arOther.x;
	y = arOther.y;
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