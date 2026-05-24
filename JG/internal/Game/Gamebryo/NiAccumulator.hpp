#pragma once

#include "NiObject.hpp"

class NiGeometry;
class NiCamera;
class NiAVObject;
class NiVisibleArray;

NiSmartPointer(NiAccumulator);

class NiAccumulator : public NiObject {
public:
	NiAccumulator();
	virtual ~NiAccumulator();

	virtual void StartAccumulating(const NiCamera* pkCamera);
	virtual void FinishAccumulating();
	virtual void RegisterObjectArray(NiVisibleArray& arArray);
	virtual bool RegisterObject(NiGeometry* apGeometry);
	virtual bool AddShared(NiAVObject* apObject);
	virtual void ClearSharedMap();

	NiCamera* m_pkCamera;

	NIRTTI_ADDRESS(0x11F6060);
};

ASSERT_SIZE(NiAccumulator, 0xC);