#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiShadeProperty);

class NiShadeProperty : public NiProperty {
public:
	NiShadeProperty();
	virtual ~NiShadeProperty();

	struct ALIGN2 _Flags {
		enum Flags : uint16_t {
			// Vanilla Gamebryo. Unused
			SMOOTH_SHADING = 1u << 0,

			// ADDED BY MODS

			IS_PLAYER = 1u << 1,
		};

		bool bSmoothShading : 1;
		bool bIsPlayer		: 1;
	};
	using Flags = _Flags::Flags;

	Bitfield<_Flags>	m_usFlags;
	int32_t				iShaderPropertyType;

	CREATE_OBJECT(NiShadeProperty, 0xA814E0);
	NIRTTI_ADDRESS(0x11F5AE0);

	int32_t GetShaderPropertyType() const;
};

ASSERT_SIZE(NiShadeProperty, 0x20);