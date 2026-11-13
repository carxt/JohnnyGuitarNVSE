#pragma once

#include "Gamebryo/NiNode.hpp"

class BSCullingProcess;
class NiCamera;
class NiVisibleArray;

NiSmartPointer(BSSceneGraph);

class BSSceneGraph : public NiNode {
public:
	virtual float	GetFarDistance();
	virtual void	SetViewDistanceBasedOnFrameRate(float afTime);

	NiPointer<NiCamera> spCamera;
	NiVisibleArray*		pVisArray;
	BSCullingProcess*	pCuller;
	bool				bMenuSceneGraph;
	float				fCurrentFOV;

	NIRTTI_ADDRESS(0x1203180);

	NiCamera* GetCamera() const;

	BSCullingProcess* GetCullingProcess() const;

	float GetCameraFOV() const;
	void SetCameraFOV(float afFOV, bool abForce, NiCamera* apCamera, bool abSetLODMult);

	NiNode* GetCameraRoot() const;
};

ASSERT_SIZE(BSSceneGraph, 0xC0);