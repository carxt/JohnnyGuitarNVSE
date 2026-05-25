#pragma once

#include "NiPoint3.hpp"

class NiPlane {
public:
	NiPlane();
	NiPlane(const NiPoint3& arNormal, float afConstant);
	NiPlane(const NiPoint3& arNormal, const NiPoint3& arPoint);
	NiPlane(const NiPoint3& arPoint0, const NiPoint3& arPoint1, const NiPoint3& arPoint2);

	enum Sides {
		NO_SIDE			= 0,
		POSITIVE_SIDE	= 1,
		NEGATIVE_SIDE	= 2,
	};

	NiPoint3	m_kNormal;
	float		m_fConstant;

	float Distance(const NiPoint3& arPoint) const;
	Sides WhichSide(const NiPoint3& arPoint) const;
};

ASSERT_SIZE(NiPlane, 0x10);