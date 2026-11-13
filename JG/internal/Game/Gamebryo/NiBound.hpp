#pragma once

#include "NiTransform.hpp"
#include "Bethesda/BSMemObject.hpp"

class NiPlane;

class SPEC_EMPTY_BASES NiBound : public BSMemObject {
public:
	NiBound() noexcept;
	NiBound(const NiPoint3& arCenter, float afRadius) noexcept;

	NiPoint3	m_kCenter;
	union {
		int32_t		m_iRadius;
		float		m_fRadius;
	};

	void operator=(const NiBound& arOther) noexcept;
	bool operator==(const NiBound& arOther) const noexcept;

	const NiPoint3& GetCenter() const noexcept;
	void SetCenter(float afX, float afY, float afZ) noexcept;
	void SetCenter(const NiPoint3& arCenter) noexcept;

	float GetRadius() const noexcept;
	void SetRadius(float afRadius) noexcept;
	void SetCenterAndRadius(const NiPoint3& arCenter, float afRadius) noexcept;

	uint32_t WhichSide(const NiPlane& arPlane) const noexcept;

	void Merge(const NiBound* apBound) noexcept;

	void ComputeFromData(uint32_t aiVertexCount, const NiPoint3* apVertexArray) noexcept;

	void Update(const NiTransform& arTransform) noexcept;
	void Update(const NiBound& arBound, const NiTransform& arTransform) noexcept;

	bool IsPointWithin(const NiPoint3& arPoint) const noexcept;
	bool IsBoundWithin(const NiBound& arBound) const noexcept;
};

ASSERT_SIZE(NiBound, 0x10);