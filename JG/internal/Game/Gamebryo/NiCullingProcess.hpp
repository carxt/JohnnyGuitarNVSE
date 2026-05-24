#pragma once

#include "NiRTTI.hpp"
#include "NiObject.hpp"
#include "NiFrustumPlanes.hpp"

class NiVisibleArray;
class NiAVObject;

class SPEC_EMPTY_BASES NiCullingProcess : public NiMemObject {
public:
	NiCullingProcess();

	virtual const NiRTTI*				GetRTTI() const;
	virtual NiNode*						IsNode() const;
	virtual BSFadeNode*					IsFadeNode() const;
	virtual BSMultiBoundNode*			IsMultiBoundNode() const;
	virtual NiGeometry*					IsGeometry() const;
	virtual NiTriBasedGeom*				IsTriBasedGeometry() const;
	virtual NiTriStrips*				IsTriStrips() const;
	virtual NiTriShape*					IsTriShape() const;
	virtual BSSegmentedTriShape*		IsSegmentedTriShape() const;
	virtual BSResizableTriShape*		IsResizableTriShape() const;
	virtual NiParticles*				IsParticlesGeom() const;
	virtual NiLines*					IsLinesGeom() const;
	virtual bhkNiCollisionObject*		IsBhkNiCollisionObject() const;
	virtual bhkBlendCollisionObject*	IsBhkBlendCollisionObject() const;
	virtual bhkRigidBody*				IsBhkRigidBody() const;
	virtual bhkLimitedHingeConstraint*	IsBhkLimitedHingeConstraint() const;
	virtual								~NiCullingProcess();
	virtual void						Process(NiAVObject* apObject);
	virtual void						ProcessAlt(const NiCamera* apCamera, NiAVObject* apScene, NiVisibleArray* apVisibleSet);
	virtual void						Append(NiGeometry* apGeom);

	bool				m_bUseVirtualAppend;
	NiVisibleArray*		m_pkVisibleSet;
	NiCamera*			m_pkCamera;
	NiFrustum			m_kFrustum;
	NiFrustumPlanes		m_kPlanes;

	NIRTTI_ADDRESS(0x11F4990);

	void SetCamera(const NiCamera* apCamera);
	NiCamera* GetCamera() const;

	void SetFrustum(const NiFrustum& arFrustum);
};

ASSERT_SIZE(NiCullingProcess, 0x90);