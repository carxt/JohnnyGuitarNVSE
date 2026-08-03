#pragma once

#include "NiAVObject.hpp"

NiSmartPointer(NiAVObjectPalette);

class NiAVObjectPalette : public NiObject {
public:
	NiAVObjectPalette();
	virtual ~NiAVObjectPalette();

	virtual NiAVObject*		GetAVObject(const NiFixedString& arName);
	virtual void			SetAVObject(const NiFixedString& arName, NiAVObject* apObject);

	NIRTTI_ADDRESS(0x11F5B58);
};

ASSERT_SIZE(NiAVObjectPalette, 0x8)