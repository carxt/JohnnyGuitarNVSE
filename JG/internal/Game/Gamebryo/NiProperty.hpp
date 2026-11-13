#pragma once

#include "NiObjectNET.hpp"

class NiUpdateData;

NiSmartPointer(NiProperty);

class NiProperty : public NiObjectNET {
public:
	NiProperty();
	virtual ~NiProperty();

	struct _Type {
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
	using Type = _Type::Type;

	virtual Type	GetType() const;
	virtual void	Update(NiUpdateData& arData);

	NIRTTI_ADDRESS(0x11F4420);
};

ASSERT_SIZE(NiProperty, 0x18);