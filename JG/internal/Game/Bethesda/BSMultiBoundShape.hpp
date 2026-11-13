#pragma once

#include "BSEnums.hpp"
#include "Gamebryo/NiObject.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiColorA.hpp"

class BSMultiBound;
class NiFrustumPlanes;

NiSmartPointer(BSMultiBoundShape);

class BSMultiBoundShape : public NiObject {
public:
	struct _ShapeType {
		enum Type : uint32_t {
			NONE	= 0,
			AABB	= 1,
			OBB		= 2,
			SPHERE	= 3,
			CAPSULE = 4,
		};
	};
	using ShapeType = _ShapeType::Type;

	virtual ShapeType			GetType() const;
	virtual float				GetRadius() const;
	virtual BS_INTERSECT_RESULT	CheckBSBound(const BSMultiBound& arTargetBound) const;
	virtual BS_INTERSECT_RESULT	CheckBound(const NiBound& arTargetBound) const;
	virtual bool				WithinFrustum(const NiFrustumPlanes& arPlanes) const;
	virtual bool				CompletelyWithinFrustum(const NiFrustumPlanes& arPlanes) const;
	virtual void				GetNiBound(NiBound& arBound) const;
	virtual void				CreateDebugGeometry(NiLines* apLines, NiTriShape* apGeometry, NiColorA akColor);
	virtual uint32_t			GetDebugGeomLineSize() const;
	virtual uint32_t			GetDebugGeomShapeSize() const;
	virtual bool				GetPointWithin(const NiPoint3& arPoint) const;
	virtual void				SetCenter(const NiPoint3& arCenter);

	struct BoundVertices {
		NiPoint3 point[8];
	};

	BS_CULL_RESULT eCullResult;

	NIRTTI_ADDRESS(0x12030C0);
};

ASSERT_SIZE(BSMultiBoundShape, 0xC)