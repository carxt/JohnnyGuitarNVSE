#pragma once

#include "netimmerse.h"
#include "NiPSysEmitter.hpp"

NiSmartPointer(NiPSysVolumeEmitter);

class NiPSysVolumeEmitter : public NiPSysEmitter {
public:
	NiPSysVolumeEmitter();
	virtual ~NiPSysVolumeEmitter();

	virtual void SetEmitterObj(NiAVObject* apEmitterObj);
	virtual void ComputeVolumeInitialPositionAndVelocity(NiTransform& arEmitterToPSys, NiPoint3& arPosition, NiPoint3& arVelocity);

	NiAVObject* m_pkEmitterObj;

	NIRTTI_ADDRESS(0x12027D8);
};

ASSERT_SIZE(NiPSysVolumeEmitter, 0x58)