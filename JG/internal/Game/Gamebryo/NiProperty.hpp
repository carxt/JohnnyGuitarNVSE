#pragma once

#include "NiObjectNET.hpp"

class NiUpdateData;

NiSmartPointer(NiProperty);

class NiProperty : public NiObjectNET {
public:
	NiProperty();
	virtual ~NiProperty();

	struct _PropertyType {
		enum Type : uint32_t {
			ALPHA,
			CULLING,
			MATERIAL,
			SHADE,
			STENCIL,
			TEXTURING,
			WIREFRAME,
			COUNT
		};
	};
	using PropertyType = _PropertyType::Type;

	virtual PropertyType	Type() const;
	virtual void			Update(NiUpdateData& arData);

	NIRTTI_ADDRESS(0x11F4420);
};

ASSERT_SIZE(NiProperty, 0x18);