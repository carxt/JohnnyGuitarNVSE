#pragma once

class NiPoint3;
class NiBound;
class NiTransform;
class NiSkinInstance;
class NiAVObject;
class NiCamera;
class NiPlane;
class NiFixedString;
struct D3DXMATRIX;

class BSUtilities {
public:
    static NiAVObject* GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName);

    static NiAVObject* GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName, bool abTestScenegraph);

    static NiAVObject* GetObjectByName(const NiAVObject* apScene, const char* apName);

    static NiAVObject* GetObjectByName(const NiAVObject* apScene, const char* apName, bool abTestScenegraph);

    static float GetAngleDelta(float afStartAngle, float afTargetAngle, float& arfOutDir) noexcept;

    static float FLerp(float afNewMin, float afNewMax, float afOldMin, float afOldMax, float afOldValue) noexcept;

    static void Wrap(float& arfOut, float afMin, float afMax) noexcept;

    static bool CompareFloat(float a, float b, float afMargin) noexcept;

    static bool ComparePoints(const NiPoint3& __restrict a, const NiPoint3& __restrict b, float afMargin) noexcept;

    static void GetInverseWorldMatrix(const NiTransform& arTransform, const NiSkinInstance* apSkinInstance, D3DXMATRIX& arOut);

    static void ReflectCameraAboutArbitraryPlane(const NiCamera* apWorldCamera, const NiPlane& arPlane, NiCamera* apTargetCamera);

    static void StandardizeModelPath(const char* apSource, char* apTarget, uint32_t auiBufferSize);

    static bool NodeInFrustum(const NiAVObject* apObject, const NiCamera* apCamera);
    static bool PointInFrustum(NiPoint3 akPoint, const NiCamera* apCamera, float afRadius);
    static bool BoundInFrustum(const NiBound& arBound, const NiCamera* apCamera);
};

// GAME - 0x457FE0
static inline DWORD BSGetTickCount() {
    return CdeclCall<DWORD>(0x457FE0);
}

// GAME - 0x43B460
static inline int BSAtomicCompareExchange(int* apAddress, int aiCompare, int aiValue) {
    return InterlockedCompareExchange(reinterpret_cast<LONG*>(apAddress), aiValue, aiCompare);
}

// GAME - 0x4491C0
static inline bool CompareAndSwapEx(int* apDestination, int aiExchange, int aiCompare) {
    return BSAtomicCompareExchange(apDestination, aiCompare, aiExchange) == aiCompare;
}