#pragma once

#include "NiPoint3.hpp"

class SPEC_EMPTY_BASES NiMatrix3 : public BSMemObject {
public:
	constexpr NiMatrix3() noexcept;
	constexpr NiMatrix3(float af00, float af10, float af20, float af01, float af11, float af21, float af02, float af12, float af22) noexcept;
	constexpr NiMatrix3(const NiPoint3& arCol0, const NiPoint3& arCol1, const NiPoint3& arCol2) noexcept;
	constexpr NiMatrix3(const NiMatrix3& arOther) noexcept;

	float		m_pEntry[3][3];

	static const NiMatrix3 IDENTITY;
	static const NiMatrix3 ZERO;

    constexpr explicit operator float*() noexcept;

    constexpr bool operator==(const NiMatrix3& arOther) const noexcept;

    constexpr NiMatrix3 operator+(const NiMatrix3& arOther) const noexcept;
    constexpr NiMatrix3 operator-(const NiMatrix3& arOther) const noexcept;
    constexpr NiMatrix3 operator*(const NiMatrix3& arOther) const noexcept;

    constexpr NiMatrix3 operator*(float afScalar) const noexcept;

    constexpr NiPoint3 operator*(const NiPoint3& arPoint) const noexcept;

    friend constexpr NiPoint3 operator*(const NiPoint3& arPoint, const NiMatrix3& arOther) noexcept;

    constexpr NiPoint3 GetRow(uint32_t auiRow) const noexcept;
    constexpr void GetRow(uint32_t auiRow, NiPoint3& arRow) const noexcept;
    constexpr void SetRow(uint32_t auiRow, const NiPoint3& arRow) noexcept;

    constexpr void GetRow(uint32_t auiRow, float& arf0, float& arf1, float& arf2) const noexcept;
    constexpr void SetRow(uint32_t auiRow, float af0, float af1, float af2) noexcept;

	constexpr NiPoint3 GetCol(uint32_t auiCol) const noexcept;
    constexpr void GetCol(uint32_t auiCol, NiPoint3& arCol) const noexcept;
    constexpr void SetCol(uint32_t auiCol, const NiPoint3& arCol) noexcept;

    constexpr void GetCol(uint32_t auiCol, float& arf0, float& arf1, float& arf2) const noexcept;
    constexpr void SetCol(uint32_t auiCol, float af0, float af1, float af2) noexcept;

    constexpr float GetEntry(uint32_t auiRow, uint32_t auiCol) const noexcept;
    constexpr void SetEntry(uint32_t auiRow, uint32_t auiCol, float afEntry) noexcept;

    constexpr void MakeZero() noexcept;
    constexpr void MakeIdentity() noexcept;

#ifdef D3DMATRIX_DEFINED
    D3DMATRIX ToD3D() const noexcept;
#endif

    void MakeXRotation(float afAngle) noexcept;
    void MakeYRotation(float afAngle) noexcept;
    void MakeZRotation(float afAngle) noexcept;

    void MakeRotation(float afAngle, float afX, float afY, float afZ) noexcept;
    void MakeRotation(float afAngle, const NiPoint3& arAxis) noexcept;

    void FromEulerAnglesXYZ(float afXAngle, float afYAngle, float afZAngle) noexcept;
    bool ToEulerAnglesXYZ(float& arfXAngle, float& arfYAngle, float& arfZAngle) const noexcept;

    void FromEulerAnglesZXY(float afZAngle, float afXAngle, float afYAngle) noexcept;
    bool ToEulerAnglesZXY(float& arfZAngle, float& arfXAngle, float& arfYAngle) const noexcept;

    NiMatrix3 Inverse() const noexcept;
    bool Inverse(NiMatrix3& arOut) const noexcept;

    NiMatrix3 Transpose() const noexcept;
    NiMatrix3 TransposeTimes(const NiMatrix3& arOther) const noexcept;

    static void TransformVertices(const NiMatrix3& arRot, const NiPoint3& arTransform, uint32_t auiVertexCount, const NiPoint3* __restrict apInVertex, NiPoint3* __restrict apOutVertex) noexcept;
};

#include "NiMatrix3.inl"

ASSERT_SIZE(NiMatrix3, 0x24);