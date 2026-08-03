#include "BSUtilities.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "numbers"

// GAME - 0x4ADE00
// GECK - N/A
NiAVObject* BSUtilities::GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName) {
	return GetObjectByName(apScene, arName, true);
}

// GAME - 0xC4B470
// GECK - 0x9D2160
NiAVObject* BSUtilities::GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName, bool abTestScenegraph) {
#ifdef GAME
	return CdeclCall<NiAVObject*>(0xC4B470, apScene, &arName, abTestScenegraph);
#else
	return CdeclCall<NiAVObject*>(0x9D2160, apScene, &arName, abTestScenegraph);
#endif
}

// GAME - 0x4AAE30
// GECK - 0x51F8A0
NiAVObject* BSUtilities::GetObjectByName(const NiAVObject* apScene, const char* apName) {
#ifdef GAME
	return CdeclCall<NiAVObject*>(0x4AAE30, apScene, apName);
#else
	return CdeclCall<NiAVObject*>(0x51F8A0, apScene, apName);
#endif
}

// GAME - 0xC4B310
// GECK - 0x9D2000
NiAVObject* BSUtilities::GetObjectByName(const NiAVObject* apScene, const char* apName, bool abTestScenegraph) {
#ifdef GAME
	return CdeclCall<NiAVObject*>(0xC4B310, apScene, apName, abTestScenegraph);
#else
	return CdeclCall<NiAVObject*>(0x9D2000, apScene, apName, abTestScenegraph);
#endif
}

// GAME - 0x4B15E0
float BSUtilities::GetAngleDelta(float afStartAngle, float afTargetAngle, float& arfOutDir) noexcept {
	constexpr float fPI = std::numbers::pi_v<float>;
	constexpr float f2PI = 2.f * fPI;

	const float fDelta = afTargetAngle - afStartAngle;

	arfOutDir = 0.f;

	if (fDelta == 0.f)
		return fDelta;

	arfOutDir = 1.f;

	if (fDelta < 0.f) {
		if (fDelta <= -fPI)
			return (fDelta + f2PI);
		else
			arfOutDir = -1.f;
	}
	else if (fDelta > fPI) {
		arfOutDir = -1.f;
		return (f2PI - fDelta);
	}
	return fDelta;
}

float BSUtilities::FLerp(float afNewMin, float afNewMax, float afOldMin, float afOldMax, float afOldValue) noexcept {
	return ((afOldValue - afOldMin) / (afOldMax - afOldMin) * (afNewMax - afNewMin) + afNewMin);
}

// GAME - 0x4E44F0
void BSUtilities::Wrap(float& arfOut, float afMin, float afMax) noexcept {
	if (afMax < afMin)
		return;

	if (afMax < arfOut)
		arfOut = std::fmod(afMax - afMin, arfOut - afMin) + afMin;
	else if (afMin > arfOut)
		arfOut = std::fmod(arfOut - afMin, afMax - afMin) + afMax;
}

// GAME - 0x49E390
bool BSUtilities::CompareFloat(float a, float b, float afMargin) noexcept {
	return afMargin >= std::fabs(a - b);
}

// GAME - 0x49E2F0
// GECK - 0x512130
bool BSUtilities::ComparePoints(const NiPoint3& __restrict a, const NiPoint3& __restrict b, float afMargin) noexcept {
#if USE_DXMATH
	const DirectX::XMVECTOR kAbs = DirectX::XMVectorAbsFast(DirectX::XMVectorSubtract(DirectX::XMLoadNiPoint3(a), DirectX::XMLoadNiPoint3(b)));
	const DirectX::XMVECTOR kMargin = DirectX::XMVectorReplicate(afMargin);
	return DirectX::XMVector3GreaterOrEqual(kMargin, kAbs);
#else
	return CompareFloat(a.x, b.x, afMargin) && CompareFloat(a.y, b.y, afMargin) && CompareFloat(a.z, b.z, afMargin);
#endif
}


// GAME - 0xC4C2D0
// GECK - 0x9D2FC0
void BSUtilities::GetInverseWorldMatrix(const NiTransform& arTransform, const NiSkinInstance* apSkinInstance, D3DXMATRIX& arOut) {
#ifdef GAME
	CdeclCall(0xC4C2D0, &arTransform, apSkinInstance, &arOut);
#else
	CdeclCall(0x9D2FC0, &arTransform, apSkinInstance, &arOut);
#endif
}

// GAME - 0xC4BF40
// GECK - 0x9D2C30
void BSUtilities::ReflectCameraAboutArbitraryPlane(const NiCamera* apWorldCamera, const NiPlane& arPlane, NiCamera* apTargetCamera) {
#ifdef GAME
	CdeclCall(0xC4BF40, apWorldCamera, &arPlane, apTargetCamera);
#else
	CdeclCall(0x9D2C30, apWorldCamera, &arPlane, apTargetCamera);
#endif
}

// GAME - 0xAF4250
// GECK - 0x8A2C30
void BSUtilities::StandardizeModelPath(const char* apSource, char* apTarget, uint32_t auiBufferSize) {
#ifdef GAME
	CdeclCall(0xAF4250, apSource, apTarget, auiBufferSize);
	CdeclCall(0x8A2C30, apSource, apTarget, auiBufferSize);
#endif
}

// GAME - 0x4B5FC0
bool BSUtilities::NodeInFrustum(const NiAVObject* apObject, const NiCamera* apCamera) {
	return CdeclCall<bool>(0x4B5FC0, apObject, apCamera);
}

// GAME - 0x4B61D0
bool BSUtilities::PointInFrustum(NiPoint3 akPoint, const NiCamera* apCamera, float afRadius) {
	return CdeclCall<bool>(0x4B61D0, akPoint, apCamera, afRadius);
}

// GAME - 0x4B5FF0
bool BSUtilities::BoundInFrustum(const NiBound& arBound, const NiCamera* apCamera) {
	return CdeclCall<bool>(0x4B5FF0, &arBound, apCamera);
}
