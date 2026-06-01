#pragma once

#include "NiMatrix3.hpp"
#include "NiPoint3.hpp"

class NiTransform {
public:
	BS_ALLOCATORS

	NiTransform();

	NiMatrix3	m_kRotate;
	NiPoint3	m_kTranslate;
	float		m_fScale;

	NiTransform operator*(const NiTransform& arOther) const noexcept;

	// 0x524C40
	inline NiPoint3 operator*(const NiPoint3& arPoint) const noexcept {
		return(((m_kRotate * arPoint) * m_fScale) + m_kTranslate);
	};

	inline bool operator==(const NiTransform& arTransform) const noexcept {
		return m_kRotate == arTransform.m_kRotate && m_kTranslate == arTransform.m_kTranslate && m_fScale == arTransform.m_fScale;
	}

	void MakeIdentity() noexcept;
	void Invert(NiTransform& arDest) const noexcept;
};

ASSERT_SIZE(NiTransform, 0x34);