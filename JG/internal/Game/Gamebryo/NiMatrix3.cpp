#include "NiMatrix3.hpp"
#include <numbers>

// GAME - 0x11A9448
// GECK - 0xEB44CC
const NiMatrix3 NiMatrix3::IDENTITY = NiMatrix3(1.f, 0.f, 0.f,
												0.f, 1.f, 0.f,
												0.f, 0.f, 1.f);

// GAME - 0x11F4248
const NiMatrix3 NiMatrix3::ZERO		= NiMatrix3(0.f, 0.f, 0.f,
												0.f, 0.f, 0.f,
												0.f, 0.f, 0.f);

NiMatrix3::NiMatrix3() noexcept {}

NiMatrix3::NiMatrix3(float af00, float af10, float af20, float af01, float af11, float af21, float af02, float af12, float af22) noexcept {
	m_pEntry[0][0] = af00;
	m_pEntry[0][1] = af10;
	m_pEntry[0][2] = af20;

	m_pEntry[1][0] = af01;
	m_pEntry[1][1] = af11;
	m_pEntry[1][2] = af21;

	m_pEntry[2][0] = af02;
	m_pEntry[2][1] = af12;
	m_pEntry[2][2] = af22;
}

NiMatrix3::NiMatrix3(const NiPoint3& arCol0, const NiPoint3& arCol1, const NiPoint3& arCol2) noexcept {
	SetCol(0, arCol0);
	SetCol(1, arCol1);
	SetCol(2, arCol2);
}

// GAME - 0x476980
NiMatrix3::NiMatrix3(const NiMatrix3& arOther) noexcept {
	m_pEntry[0][0] = arOther.m_pEntry[0][0];
	m_pEntry[0][1] = arOther.m_pEntry[0][1];
	m_pEntry[0][2] = arOther.m_pEntry[0][2];

	m_pEntry[1][0] = arOther.m_pEntry[1][0];
	m_pEntry[1][1] = arOther.m_pEntry[1][1];
	m_pEntry[1][2] = arOther.m_pEntry[1][2];

	m_pEntry[2][0] = arOther.m_pEntry[2][0];
	m_pEntry[2][1] = arOther.m_pEntry[2][1];
	m_pEntry[2][2] = arOther.m_pEntry[2][2];
}

NiMatrix3::operator float*() noexcept {
	return &m_pEntry[0][0];
}

// GAME - 0x4D9AE0
bool NiMatrix3::operator==(const NiMatrix3& arOther) const noexcept {
	return m_pEntry[0][0] == arOther.m_pEntry[0][0]
		&& m_pEntry[0][1] == arOther.m_pEntry[0][1]
		&& m_pEntry[0][2] == arOther.m_pEntry[0][2]

		&& m_pEntry[1][0] == arOther.m_pEntry[1][0]
		&& m_pEntry[1][1] == arOther.m_pEntry[1][1]
		&& m_pEntry[1][2] == arOther.m_pEntry[1][2]

		&& m_pEntry[2][0] == arOther.m_pEntry[2][0]
		&& m_pEntry[2][1] == arOther.m_pEntry[2][1]
		&& m_pEntry[2][2] == arOther.m_pEntry[2][2];
}

// GAME - 0xC23C00
NiMatrix3 NiMatrix3::operator+(const NiMatrix3& arOther) const noexcept {
	NiMatrix3 kResult;
	kResult.m_pEntry[0][0] = m_pEntry[0][0] + arOther.m_pEntry[0][0];
	kResult.m_pEntry[0][1] = m_pEntry[0][1] + arOther.m_pEntry[0][1];
	kResult.m_pEntry[0][2] = m_pEntry[0][2] + arOther.m_pEntry[0][2];

	kResult.m_pEntry[1][0] = m_pEntry[1][0] + arOther.m_pEntry[1][0];
	kResult.m_pEntry[1][1] = m_pEntry[1][1] + arOther.m_pEntry[1][1];
	kResult.m_pEntry[1][2] = m_pEntry[1][2] + arOther.m_pEntry[1][2];

	kResult.m_pEntry[2][0] = m_pEntry[2][0] + arOther.m_pEntry[2][0];
	kResult.m_pEntry[2][1] = m_pEntry[2][1] + arOther.m_pEntry[2][1];
	kResult.m_pEntry[2][2] = m_pEntry[2][2] + arOther.m_pEntry[2][2];
	return kResult;
}

// GAME - 0xC23C70
NiMatrix3 NiMatrix3::operator-(const NiMatrix3& arOther) const noexcept {
	NiMatrix3 kResult;
	kResult.m_pEntry[0][0] = m_pEntry[0][0] - arOther.m_pEntry[0][0];
	kResult.m_pEntry[0][1] = m_pEntry[0][1] - arOther.m_pEntry[0][1];
	kResult.m_pEntry[0][2] = m_pEntry[0][2] - arOther.m_pEntry[0][2];

	kResult.m_pEntry[1][0] = m_pEntry[1][0] - arOther.m_pEntry[1][0];
	kResult.m_pEntry[1][1] = m_pEntry[1][1] - arOther.m_pEntry[1][1];
	kResult.m_pEntry[1][2] = m_pEntry[1][2] - arOther.m_pEntry[1][2];

	kResult.m_pEntry[2][0] = m_pEntry[2][0] - arOther.m_pEntry[2][0];
	kResult.m_pEntry[2][1] = m_pEntry[2][1] - arOther.m_pEntry[2][1];
	kResult.m_pEntry[2][2] = m_pEntry[2][2] - arOther.m_pEntry[2][2];
	return kResult;
}

// GAME - 0x43F8D0
NiMatrix3 NiMatrix3::operator*(const NiMatrix3& arOther) const noexcept {
	NiMatrix3 kResult;
	kResult.m_pEntry[0][0] =
			m_pEntry[0][0] * arOther.m_pEntry[0][0] +
			m_pEntry[0][1] * arOther.m_pEntry[1][0] +
			m_pEntry[0][2] * arOther.m_pEntry[2][0];

	kResult.m_pEntry[1][0] =
			m_pEntry[1][0] * arOther.m_pEntry[0][0] +
			m_pEntry[1][1] * arOther.m_pEntry[1][0] +
			m_pEntry[1][2] * arOther.m_pEntry[2][0];

	kResult.m_pEntry[2][0] =
			m_pEntry[2][0] * arOther.m_pEntry[0][0] +
			m_pEntry[2][1] * arOther.m_pEntry[1][0] +
			m_pEntry[2][2] * arOther.m_pEntry[2][0];

	kResult.m_pEntry[0][1] =
			m_pEntry[0][0] * arOther.m_pEntry[0][1] +
			m_pEntry[0][1] * arOther.m_pEntry[1][1] +
			m_pEntry[0][2] * arOther.m_pEntry[2][1];

	kResult.m_pEntry[1][1] =
			m_pEntry[1][0] * arOther.m_pEntry[0][1] +
			m_pEntry[1][1] * arOther.m_pEntry[1][1] +
			m_pEntry[1][2] * arOther.m_pEntry[2][1];

	kResult.m_pEntry[2][1] =
			m_pEntry[2][0] * arOther.m_pEntry[0][1] +
			m_pEntry[2][1] * arOther.m_pEntry[1][1] +
			m_pEntry[2][2] * arOther.m_pEntry[2][1];

	kResult.m_pEntry[0][2] =
			m_pEntry[0][0] * arOther.m_pEntry[0][2] +
			m_pEntry[0][1] * arOther.m_pEntry[1][2] +
			m_pEntry[0][2] * arOther.m_pEntry[2][2];

	kResult.m_pEntry[1][2] =
			m_pEntry[1][0] * arOther.m_pEntry[0][2] +
			m_pEntry[1][1] * arOther.m_pEntry[1][2] +
			m_pEntry[1][2] * arOther.m_pEntry[2][2];

	kResult.m_pEntry[2][2] =
			m_pEntry[2][0] * arOther.m_pEntry[0][2] +
			m_pEntry[2][1] * arOther.m_pEntry[1][2] +
			m_pEntry[2][2] * arOther.m_pEntry[2][2];

	return kResult;
}

// GAME - 0xA85520
NiMatrix3 NiMatrix3::operator*(float afScalar) const noexcept {
	NiMatrix3 kResult;
	kResult.m_pEntry[0][0] = m_pEntry[0][0] * afScalar;
	kResult.m_pEntry[0][1] = m_pEntry[0][1] * afScalar;
	kResult.m_pEntry[0][2] = m_pEntry[0][2] * afScalar;

	kResult.m_pEntry[1][0] = m_pEntry[1][0] * afScalar;
	kResult.m_pEntry[1][1] = m_pEntry[1][1] * afScalar;
	kResult.m_pEntry[1][2] = m_pEntry[1][2] * afScalar;

	kResult.m_pEntry[2][0] = m_pEntry[2][0] * afScalar;
	kResult.m_pEntry[2][1] = m_pEntry[2][1] * afScalar;
	kResult.m_pEntry[2][2] = m_pEntry[2][2] * afScalar;
	return kResult;
}

// GAME - 0x4B4500
NiPoint3 NiMatrix3::operator*(const NiPoint3& arPoint) const noexcept {
	return {
		m_pEntry[0][0] * arPoint.x + m_pEntry[0][1] * arPoint.y + m_pEntry[0][2] * arPoint.z,
		m_pEntry[1][0] * arPoint.x + m_pEntry[1][1] * arPoint.y + m_pEntry[1][2] * arPoint.z,
		m_pEntry[2][0] * arPoint.x + m_pEntry[2][1] * arPoint.y + m_pEntry[2][2] * arPoint.z
	};
}

// GAME - 0x4B3AE0
NiPoint3 operator*(const NiPoint3& arPoint, const NiMatrix3& arOther) noexcept {
	return {
		arPoint.x * arOther.m_pEntry[0][0] + arPoint.y * arOther.m_pEntry[1][0] +
		arPoint.z * arOther.m_pEntry[2][0],
		arPoint.x * arOther.m_pEntry[0][1] + arPoint.y * arOther.m_pEntry[1][1] +
		arPoint.z * arOther.m_pEntry[2][1],
		arPoint.x * arOther.m_pEntry[0][2] + arPoint.y * arOther.m_pEntry[1][2] +
		arPoint.z * arOther.m_pEntry[2][2]
	};
}

NiPoint3 NiMatrix3::GetRow(uint32_t auiRow) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	return {
		m_pEntry[auiRow][0],
		m_pEntry[auiRow][1],
		m_pEntry[auiRow][2]
	};
}

// GAME - 0x476930
void NiMatrix3::GetRow(uint32_t auiRow, NiPoint3& arRow) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	arRow.x = m_pEntry[auiRow][0];
	arRow.y = m_pEntry[auiRow][1];
	arRow.z = m_pEntry[auiRow][2];
}

// GAME - 0x5DF510
void NiMatrix3::SetRow(uint32_t auiRow, const NiPoint3& arRow) noexcept {
	ASSUME_ASSERT(auiRow < 3);
	m_pEntry[auiRow][0] = arRow.x;
	m_pEntry[auiRow][1] = arRow.y;
	m_pEntry[auiRow][2] = arRow.z;
}

// GAME - 0x5DF560
void NiMatrix3::GetRow(uint32_t auiRow, float& arf0, float& arf1, float& arf2) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	arf0 = m_pEntry[auiRow][0];
	arf1 = m_pEntry[auiRow][1];
	arf2 = m_pEntry[auiRow][2];
}

// GAME - 0x7133B0
void NiMatrix3::SetRow(uint32_t auiRow, float af0, float af1, float af2) noexcept {
	ASSUME_ASSERT(auiRow < 3);
	m_pEntry[auiRow][0] = af0;
	m_pEntry[auiRow][1] = af1;
	m_pEntry[auiRow][2] = af2;
}

NiPoint3 NiMatrix3::GetCol(uint32_t auiCol) const noexcept {
	ASSUME_ASSERT(auiCol < 3);
	return {
		m_pEntry[0][auiCol],
		m_pEntry[1][auiCol],
		m_pEntry[2][auiCol]
	};
}

// GAME - 0x439F50
void NiMatrix3::GetCol(uint32_t auiCol, NiPoint3& arCol) const noexcept {
	ASSUME_ASSERT(auiCol < 3);
	arCol.x = m_pEntry[0][auiCol];
	arCol.y = m_pEntry[1][auiCol];
	arCol.z = m_pEntry[2][auiCol];
}

// GAME - 0x4769C0
void NiMatrix3::SetCol(uint32_t auiCol, const NiPoint3& arCol) noexcept {
	ASSUME_ASSERT(auiCol < 3);
	m_pEntry[0][auiCol] = arCol.x;
	m_pEntry[1][auiCol] = arCol.y;
	m_pEntry[2][auiCol] = arCol.z;
}

void NiMatrix3::GetCol(uint32_t auiCol, float& arf0, float& arf1, float& arf2) const noexcept {
	ASSUME_ASSERT(auiCol < 3);
	arf0 = m_pEntry[0][auiCol];
	arf1 = m_pEntry[1][auiCol];
	arf2 = m_pEntry[2][auiCol];
}

// GAME - 0x4B4660
void NiMatrix3::SetCol(uint32_t auiCol, float af0, float af1, float af2) noexcept {
	ASSUME_ASSERT(auiCol < 3);
	m_pEntry[0][auiCol] = af0;
	m_pEntry[1][auiCol] = af1;
	m_pEntry[2][auiCol] = af2;
}

// GAME - 0x4B55C0
float NiMatrix3::GetEntry(uint32_t auiRow, uint32_t auiCol) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	ASSUME_ASSERT(auiCol < 3);
	return m_pEntry[auiRow][auiCol];
}

// GAME - 0x642660
void NiMatrix3::SetEntry(uint32_t auiRow, uint32_t auiCol, float afEntry) noexcept {
	ASSUME_ASSERT(auiRow < 3);
	ASSUME_ASSERT(auiCol < 3);
	m_pEntry[auiRow][auiCol] = afEntry;
}

// GAME - 0x4B4600
void NiMatrix3::MakeZero() noexcept {
	SetCol(0, 0.f, 0.f, 0.f);
	SetCol(1, 0.f, 0.f, 0.f);
	SetCol(2, 0.f, 0.f, 0.f);
}

// GAME - 0x4DFDD0
void NiMatrix3::MakeIdentity() noexcept {
	m_pEntry[0][0] = 1.f;
	m_pEntry[0][1] = 0.f;
	m_pEntry[0][2] = 0.f;

	m_pEntry[1][0] = 0.f;
	m_pEntry[1][1] = 1.f;
	m_pEntry[1][2] = 0.f;

	m_pEntry[2][0] = 0.f;
	m_pEntry[2][1] = 0.f;
	m_pEntry[2][2] = 1.f;
}

#ifdef D3DMATRIX_DEFINED
D3DMATRIX NiMatrix3::ToD3D() const noexcept {
	D3DMATRIX kResult;
	kResult._11 = GetEntry(0, 0);
	kResult._12 = GetEntry(1, 0);
	kResult._13 = GetEntry(2, 0);
	kResult._14 = 0.0f;

	kResult._21 = GetEntry(0, 1);
	kResult._22 = GetEntry(1, 1);
	kResult._23 = GetEntry(2, 1);
	kResult._24 = 0.0f;

	kResult._31 = GetEntry(0, 2);
	kResult._32 = GetEntry(1, 2);
	kResult._33 = GetEntry(2, 2);
	kResult._34 = 0.0f;

	kResult._41 = 0.0f;
	kResult._42 = 0.0f;
	kResult._43 = 0.0f;
	kResult._44 = 1.0f;
	return kResult;
}
#endif

// GAME - 0x524AC0
// GECK - 0x40B480
void NiMatrix3::MakeXRotation(float afAngle) noexcept {
#if USE_DXMATH
	DirectX::XMStoreNiMatrix3(*this, DirectX::XMMatrixRotationX(afAngle));
#else
	const float fSin = std::sin(afAngle);
	const float fCos = std::cos(afAngle);

	m_pEntry[0][0] = 1.f;
	m_pEntry[0][1] = 0.f;
	m_pEntry[0][2] = 0.f;

	m_pEntry[1][0] = 0.f;
	m_pEntry[1][1] = fCos;
	m_pEntry[1][2] = fSin;

	m_pEntry[2][0] = 0.f;
	m_pEntry[2][1] = -fSin;
	m_pEntry[2][2] = fCos;
#endif
}

// GAME - 0x43F850
// GECK - 0x40B4D0
void NiMatrix3::MakeYRotation(float afAngle) noexcept {
#if USE_DXMATH
	DirectX::XMStoreNiMatrix3(*this, DirectX::XMMatrixRotationY(afAngle));
#else
	const float fSin = std::sin(afAngle);
	const float fCos = std::cos(afAngle);

	m_pEntry[0][0] = fCos;
	m_pEntry[0][1] = 0.f;
	m_pEntry[0][2] = -fSin;

	m_pEntry[1][0] = 0.f;
	m_pEntry[1][1] = 1.f;
	m_pEntry[1][2] = 0.f;

	m_pEntry[2][0] = fSin;
	m_pEntry[2][1] = 0.f;
	m_pEntry[2][2] = fCos;
#endif
}

// GAME - 0x4A0C90
// GECK - 0x40B520
void NiMatrix3::MakeZRotation(float afAngle) noexcept {
#if USE_DXMATH
	DirectX::XMStoreNiMatrix3(*this, DirectX::XMMatrixRotationZ(afAngle));
#else
	const float fSin = std::sin(afAngle);
	const float fCos = std::cos(afAngle);

	m_pEntry[0][0] = fCos;
	m_pEntry[0][1] = fSin;
	m_pEntry[0][2] = 0.f;

	m_pEntry[1][0] = -fSin;
	m_pEntry[1][1] = fCos;
	m_pEntry[1][2] = 0.f;

	m_pEntry[2][0] = 0.f;
	m_pEntry[2][1] = 0.f;
	m_pEntry[2][2] = 1.f;
#endif
}

// GAME - 0x4168A0
void NiMatrix3::MakeRotation(float afAngle, float afX, float afY, float afZ) noexcept {
#if USE_DXMATH
	DirectX::XMStoreNiMatrix3(*this, DirectX::XMMatrixRotationNormal(DirectX::XMVectorSet(afX, afY, afZ, 0.f), afAngle));
#else
	const float fSin = std::sin(afAngle);
	const float fCos = std::cos(afAngle);

	const float fOmCos = 1.f - fCos;

	const float fX2 = afX * afX;
	const float fY2 = afY * afY;
	const float fZ2 = afZ * afZ;

	const float fXYm = afX * afY * fOmCos;
	const float fXZm = afX * afZ * fOmCos;
	const float fYZm = afY * afZ * fOmCos;

	const float fXSin = afX * fSin;
	const float fYSin = afY * fSin;
	const float fZSin = afZ * fSin;

	m_pEntry[0][0] = fX2  * fOmCos + fCos;
	m_pEntry[0][1] = fXYm + fZSin;
	m_pEntry[0][2] = fXZm - fYSin;

	m_pEntry[1][0] = fXYm - fZSin;
	m_pEntry[1][1] = fY2  * fOmCos + fCos;
	m_pEntry[1][2] = fYZm + fXSin;

	m_pEntry[2][0] = fXZm + fYSin;
	m_pEntry[2][1] = fYZm - fXSin;
	m_pEntry[2][2] = fZ2  * fOmCos + fCos;
#endif
}

void NiMatrix3::MakeRotation(float afAngle, const NiPoint3& arAxis) noexcept {
	MakeRotation(afAngle, arAxis.x, arAxis.y, arAxis.z);
}

// GAME - 0xA59540
// GECK - 0x80A7D0
void NiMatrix3::FromEulerAnglesXYZ(float afXAngle, float afYAngle, float afZAngle) noexcept {
#if USE_DXMATH
	DirectX::XMMATRIX kXRot = DirectX::XMMatrixRotationX(afXAngle);
	DirectX::XMMATRIX kYRot = DirectX::XMMatrixRotationY(afYAngle);
	DirectX::XMMATRIX kZRot = DirectX::XMMatrixRotationZ(afZAngle);
	DirectX::XMMATRIX kRot  = kXRot * (kYRot * kZRot);
	DirectX::XMStoreNiMatrix3(*this, kRot);
#else
	NiMatrix3 kXRot, kYRot, kZRot;
	kXRot.MakeXRotation(afXAngle);
	kYRot.MakeYRotation(afYAngle);
	kZRot.MakeZRotation(afZAngle);
	*this = kXRot * (kYRot * kZRot);
#endif
}

// GAME - 0xA592C0
bool NiMatrix3::ToEulerAnglesXYZ(float& arfXAngle, float& arfYAngle, float& arfZAngle) const noexcept {
	return ThisCall<bool>(0xA592C0, this, &arfXAngle, &arfYAngle, &arfZAngle);
}

// GAME - 0xA59660
void NiMatrix3::FromEulerAnglesZXY(float afZAngle, float afXAngle, float afYAngle) noexcept {
#if USE_DXMATH
	DirectX::XMMATRIX kXRot = DirectX::XMMatrixRotationX(afXAngle);
	DirectX::XMMATRIX kYRot = DirectX::XMMatrixRotationY(afYAngle);
	DirectX::XMMATRIX kZRot = DirectX::XMMatrixRotationZ(afZAngle);
	DirectX::XMMATRIX kRot = kZRot * (kXRot * kYRot);
	DirectX::XMStoreNiMatrix3(*this, kRot);
#else
	NiMatrix3 kXRot, kYRot, kZRot;
	kXRot.MakeXRotation(afXAngle);
	kYRot.MakeYRotation(afYAngle);
	kZRot.MakeZRotation(afZAngle);
	*this = kZRot * (kXRot * kYRot);
#endif
}

// GAME - 0xA59400
bool NiMatrix3::ToEulerAnglesZXY(float& arfZAngle, float& arfXAngle, float& arfYAngle) const noexcept {
	return ThisCall<bool>(0xA59400, this, &arfZAngle, &arfXAngle, &arfYAngle);
}

// GAME - 0x4B45B0
NiMatrix3 NiMatrix3::Inverse() const noexcept {
	NiMatrix3 kResult;

	if (!Inverse(kResult))
		kResult.MakeZero();

	return kResult;
}

// GAME - 0x4B46A0
// GECK - 0x44ED10
bool NiMatrix3::Inverse(NiMatrix3& arOut) const noexcept {
	arOut.m_pEntry[0][0] = m_pEntry[1][1] * m_pEntry[2][2] -
						   m_pEntry[1][2] * m_pEntry[2][1];
	arOut.m_pEntry[0][1] = m_pEntry[0][2] * m_pEntry[2][1] -
						   m_pEntry[0][1] * m_pEntry[2][2];
	arOut.m_pEntry[0][2] = m_pEntry[0][1] * m_pEntry[1][2] -
						   m_pEntry[0][2] * m_pEntry[1][1];

	arOut.m_pEntry[1][0] = m_pEntry[1][2] * m_pEntry[2][0] -
						   m_pEntry[1][0] * m_pEntry[2][2];
	arOut.m_pEntry[1][1] = m_pEntry[0][0] * m_pEntry[2][2] -
						   m_pEntry[0][2] * m_pEntry[2][0];
	arOut.m_pEntry[1][2] = m_pEntry[0][2] * m_pEntry[1][0] -
						   m_pEntry[0][0] * m_pEntry[1][2];

	arOut.m_pEntry[2][0] = m_pEntry[1][0] * m_pEntry[2][1] -
						   m_pEntry[1][1] * m_pEntry[2][0];
	arOut.m_pEntry[2][1] = m_pEntry[0][1] * m_pEntry[2][0] -
						   m_pEntry[0][0] * m_pEntry[2][1];
	arOut.m_pEntry[2][2] = m_pEntry[0][0] * m_pEntry[1][1] -
						   m_pEntry[0][1] * m_pEntry[1][0];

	const float fDet = m_pEntry[0][0] * arOut.m_pEntry[0][0] +
					   m_pEntry[0][1] * arOut.m_pEntry[1][0] +
					   m_pEntry[0][2] * arOut.m_pEntry[2][0];

	if (std::abs(fDet) <= 0.000001f)
		return false;

	const float fInvDet = 1.0f / fDet;
	for (uint32_t uiRow = 0; uiRow < 3; uiRow++) {
		for (uint32_t uiCol = 0; uiCol < 3; uiCol++) {
			arOut.m_pEntry[uiRow][uiCol] *= fInvDet;
		}
	}

	return true;
}

// GAME - 0x4768C0
NiMatrix3 NiMatrix3::Transpose() const noexcept {
#if USE_DXMATH
	NiMatrix3 kResult;
	DirectX::XMStoreNiMatrix3(kResult, DirectX::XMMatrixTranspose(DirectX::XMLoadNiMatrix3(*this)));
	return kResult;
#else
	NiPoint3 kRows[3];

	GetRow(0, kRows[0]);
	GetRow(1, kRows[1]);
	GetRow(2, kRows[2]);

	return NiMatrix3(kRows[0], kRows[1], kRows[2]);
#endif
}

// GAME - 0xA588A0
NiMatrix3 NiMatrix3::TransposeTimes(const NiMatrix3& arOther) const noexcept {
	NiMatrix3 kResult;
	kResult.m_pEntry[0][0] =
			m_pEntry[0][0] * arOther.m_pEntry[0][0] +
			m_pEntry[1][0] * arOther.m_pEntry[1][0] +
			m_pEntry[2][0] * arOther.m_pEntry[2][0];
	kResult.m_pEntry[1][0] =
			m_pEntry[0][1] * arOther.m_pEntry[0][0] +
			m_pEntry[1][1] * arOther.m_pEntry[1][0] +
			m_pEntry[2][1] * arOther.m_pEntry[2][0];
	kResult.m_pEntry[2][0] =
			m_pEntry[0][2] * arOther.m_pEntry[0][0] +
			m_pEntry[1][2] * arOther.m_pEntry[1][0] +
			m_pEntry[2][2] * arOther.m_pEntry[2][0];

	kResult.m_pEntry[0][1] =
			m_pEntry[0][0] * arOther.m_pEntry[0][1] +
			m_pEntry[1][0] * arOther.m_pEntry[1][1] +
			m_pEntry[2][0] * arOther.m_pEntry[2][1];
	kResult.m_pEntry[1][1] =
			m_pEntry[0][1] * arOther.m_pEntry[0][1] +
			m_pEntry[1][1] * arOther.m_pEntry[1][1] +
			m_pEntry[2][1] * arOther.m_pEntry[2][1];
	kResult.m_pEntry[2][1] =
			m_pEntry[0][2] * arOther.m_pEntry[0][1] +
			m_pEntry[1][2] * arOther.m_pEntry[1][1] +
			m_pEntry[2][2] * arOther.m_pEntry[2][1];

	kResult.m_pEntry[0][2] =
			m_pEntry[0][0] * arOther.m_pEntry[0][2] +
			m_pEntry[1][0] * arOther.m_pEntry[1][2] +
			m_pEntry[2][0] * arOther.m_pEntry[2][2];
	kResult.m_pEntry[1][2] =
			m_pEntry[0][1] * arOther.m_pEntry[0][2] +
			m_pEntry[1][1] * arOther.m_pEntry[1][2] +
			m_pEntry[2][1] * arOther.m_pEntry[2][2];
	kResult.m_pEntry[2][2] =
			m_pEntry[0][2] * arOther.m_pEntry[0][2] +
			m_pEntry[1][2] * arOther.m_pEntry[1][2] +
			m_pEntry[2][2] * arOther.m_pEntry[2][2];
	return kResult;
}

// GAME - 0xA582F0
// GECK - 0x809540
void NiMatrix3::TransformVertices(const NiMatrix3& arRot, const NiPoint3& arTransform, uint32_t auiVertexCount, const NiPoint3* __restrict apInVertex, NiPoint3* __restrict apOutVertex) noexcept {
#if USE_DXMATH
	const DirectX::XMMATRIX kRot = DirectX::XMLoadNiMatrix3(arRot);
	const DirectX::XMVECTOR kTrans = DirectX::XMLoadNiPoint3(arTransform);
	for (uint32_t i = 0; i < auiVertexCount; i++) {
		DirectX::XMVECTOR kInVertex = DirectX::XMLoadNiPoint3(apInVertex[i]);
		kInVertex = DirectX::XMVectorAdd(DirectX::XMVector3Transform(kInVertex, kRot), kTrans);
		DirectX::XMStoreNiPoint3(apOutVertex[i], kInVertex);
	}
#else
	for (uint32_t i = 0; i < auiVertexCount; i++) {
		apOutVertex[i].x = arTransform.x +
			arRot.m_pEntry[0][0] * apInVertex[i].x +
			arRot.m_pEntry[0][1] * apInVertex[i].y +
			arRot.m_pEntry[0][2] * apInVertex[i].z;
		apOutVertex[i].y = arTransform.y +
			arRot.m_pEntry[1][0] * apInVertex[i].x +
			arRot.m_pEntry[1][1] * apInVertex[i].y +
			arRot.m_pEntry[1][2] * apInVertex[i].z;
		apOutVertex[i].z = arTransform.z +
			arRot.m_pEntry[2][0] * apInVertex[i].x +
			arRot.m_pEntry[2][1] * apInVertex[i].y +
			arRot.m_pEntry[2][2] * apInVertex[i].z;
	}
#endif
}
