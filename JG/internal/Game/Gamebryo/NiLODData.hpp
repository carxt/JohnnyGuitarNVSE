#pragma once

#include "NiObject.hpp"

class NiCamera;
class NiLODNode;

NiSmartPointer(NiLODData);

class NiLODData : public NiObject {
public:
	NiLODData();
	virtual ~NiLODData();

	virtual int32_t		GetLODLevel(const NiCamera* apCamera, NiLODNode* apLOD);
	virtual void		UpdateWorldData(NiLODNode* apLOD);
	virtual NiLODData*	Duplicate();
	virtual int32_t		GetLODIndex(int32_t aiLODLevel);

	NIRTTI_ADDRESS(0x11F6050);
};

ASSERT_SIZE(NiLODData, 0x8)