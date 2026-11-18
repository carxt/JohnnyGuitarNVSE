#pragma once

#include "NiMatrix3.hpp"

inline constexpr NiMatrix3::NiMatrix3() noexcept {}

inline constexpr NiMatrix3::NiMatrix3(float af00, float af10, float af20, float af01, float af11, float af21, float af02, float af12, float af22) noexcept {
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

inline constexpr NiMatrix3::NiMatrix3(const NiPoint3& arCol0, const NiPoint3& arCol1, const NiPoint3& arCol2) noexcept {
	SetCol(0, arCol0);
	SetCol(1, arCol1);
	SetCol(2, arCol2);
}

// GAME - 0x476980
inline constexpr NiMatrix3::NiMatrix3(const NiMatrix3& arOther) noexcept {
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


inline constexpr NiMatrix3::operator float*() noexcept {
	return &m_pEntry[0][0];
}

// GAME - 0x4D9AE0
inline constexpr bool NiMatrix3::operator==(const NiMatrix3& arOther) const noexcept {
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
inline constexpr NiMatrix3 NiMatrix3::operator+(const NiMatrix3& arOther) const noexcept {
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
inline constexpr NiMatrix3 NiMatrix3::operator-(const NiMatrix3& arOther) const noexcept {
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
inline constexpr NiMatrix3 NiMatrix3::operator*(const NiMatrix3& arOther) const noexcept {
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
inline constexpr NiMatrix3 NiMatrix3::operator*(float afScalar) const noexcept {
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
inline constexpr NiPoint3 NiMatrix3::operator*(const NiPoint3& arPoint) const noexcept {
	return {
		m_pEntry[0][0] * arPoint.x + m_pEntry[0][1] * arPoint.y + m_pEntry[0][2] * arPoint.z,
		m_pEntry[1][0] * arPoint.x + m_pEntry[1][1] * arPoint.y + m_pEntry[1][2] * arPoint.z,
		m_pEntry[2][0] * arPoint.x + m_pEntry[2][1] * arPoint.y + m_pEntry[2][2] * arPoint.z
	};
}

// GAME - 0x4B3AE0
inline constexpr NiPoint3 operator*(const NiPoint3& arPoint, const NiMatrix3& arOther) noexcept {
	return {
		arPoint.x * arOther.m_pEntry[0][0] + arPoint.y * arOther.m_pEntry[1][0] +
		arPoint.z * arOther.m_pEntry[2][0],
		arPoint.x * arOther.m_pEntry[0][1] + arPoint.y * arOther.m_pEntry[1][1] +
		arPoint.z * arOther.m_pEntry[2][1],
		arPoint.x * arOther.m_pEntry[0][2] + arPoint.y * arOther.m_pEntry[1][2] +
		arPoint.z * arOther.m_pEntry[2][2]
	};
}

inline constexpr NiPoint3 NiMatrix3::GetRow(uint32_t auiRow) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	return {
		m_pEntry[auiRow][0],
		m_pEntry[auiRow][1],
		m_pEntry[auiRow][2]
	};
}

// GAME - 0x476930
inline constexpr void NiMatrix3::GetRow(uint32_t auiRow, NiPoint3& arRow) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	arRow.x = m_pEntry[auiRow][0];
	arRow.y = m_pEntry[auiRow][1];
	arRow.z = m_pEntry[auiRow][2];
}

// GAME - 0x5DF510
inline constexpr void NiMatrix3::SetRow(uint32_t auiRow, const NiPoint3& arRow) noexcept {
	ASSUME_ASSERT(auiRow < 3);
	m_pEntry[auiRow][0] = arRow.x;
	m_pEntry[auiRow][1] = arRow.y;
	m_pEntry[auiRow][2] = arRow.z;
}

// GAME - 0x5DF560
inline constexpr void NiMatrix3::GetRow(uint32_t auiRow, float& arf0, float& arf1, float& arf2) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	arf0 = m_pEntry[auiRow][0];
	arf1 = m_pEntry[auiRow][1];
	arf2 = m_pEntry[auiRow][2];
}

// GAME - 0x7133B0
inline constexpr void NiMatrix3::SetRow(uint32_t auiRow, float af0, float af1, float af2) noexcept {
	ASSUME_ASSERT(auiRow < 3);
	m_pEntry[auiRow][0] = af0;
	m_pEntry[auiRow][1] = af1;
	m_pEntry[auiRow][2] = af2;
}

inline constexpr NiPoint3 NiMatrix3::GetCol(uint32_t auiCol) const noexcept {
	ASSUME_ASSERT(auiCol < 3);
	return {
		m_pEntry[0][auiCol],
		m_pEntry[1][auiCol],
		m_pEntry[2][auiCol]
	};
}

// GAME - 0x439F50
inline constexpr void NiMatrix3::GetCol(uint32_t auiCol, NiPoint3& arCol) const noexcept {
	ASSUME_ASSERT(auiCol < 3);
	arCol.x = m_pEntry[0][auiCol];
	arCol.y = m_pEntry[1][auiCol];
	arCol.z = m_pEntry[2][auiCol];
}

// GAME - 0x4769C0
inline constexpr void NiMatrix3::SetCol(uint32_t auiCol, const NiPoint3& arCol) noexcept {
	ASSUME_ASSERT(auiCol < 3);
	m_pEntry[0][auiCol] = arCol.x;
	m_pEntry[1][auiCol] = arCol.y;
	m_pEntry[2][auiCol] = arCol.z;
}

inline constexpr void NiMatrix3::GetCol(uint32_t auiCol, float& arf0, float& arf1, float& arf2) const noexcept {
	ASSUME_ASSERT(auiCol < 3);
	arf0 = m_pEntry[0][auiCol];
	arf1 = m_pEntry[1][auiCol];
	arf2 = m_pEntry[2][auiCol];
}

// GAME - 0x4B4660
inline constexpr void NiMatrix3::SetCol(uint32_t auiCol, float af0, float af1, float af2) noexcept {
	ASSUME_ASSERT(auiCol < 3);
	m_pEntry[0][auiCol] = af0;
	m_pEntry[1][auiCol] = af1;
	m_pEntry[2][auiCol] = af2;
}

// GAME - 0x4B55C0
inline constexpr float NiMatrix3::GetEntry(uint32_t auiRow, uint32_t auiCol) const noexcept {
	ASSUME_ASSERT(auiRow < 3);
	ASSUME_ASSERT(auiCol < 3);
	return m_pEntry[auiRow][auiCol];
}

// GAME - 0x642660
inline constexpr void NiMatrix3::SetEntry(uint32_t auiRow, uint32_t auiCol, float afEntry) noexcept {
	ASSUME_ASSERT(auiRow < 3);
	ASSUME_ASSERT(auiCol < 3);
	m_pEntry[auiRow][auiCol] = afEntry;
}

// GAME - 0x4B4600
inline constexpr void NiMatrix3::MakeZero() noexcept {
	SetCol(0, 0.f, 0.f, 0.f);
	SetCol(1, 0.f, 0.f, 0.f);
	SetCol(2, 0.f, 0.f, 0.f);
}

// GAME - 0x4DFDD0
inline constexpr void NiMatrix3::MakeIdentity() noexcept {
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