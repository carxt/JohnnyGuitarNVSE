#pragma once

#include "NiObjectNET.hpp"

class NiUpdateData;

NiSmartPointer(NiProperty);

class NiProperty : public NiObjectNET {
public:
	NiProperty();
	virtual ~NiProperty();

	enum PropertyType : uint32_t {
		ALPHA,
		CULLING,
		MATERIAL,
		SHADE,
		STENCIL,
		TEXTURING,
		WIREFRAME,
		MAX_TYPES
	};

	virtual PropertyType	Type() const;
	virtual void			Update(NiUpdateData& arUpdateData);

	NIRTTI_ADDRESS(0x11F4420);
};

ASSERT_SIZE(NiProperty, 0x18);