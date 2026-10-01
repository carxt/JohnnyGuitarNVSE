#pragma once

#include "NiProperty.hpp"
#include "NiTPrimitiveArray.hpp"

class NiTexture;
class NiTextureTransform;

NiSmartPointer(NiTexturingProperty);

class NiTexturingProperty : public NiProperty {
public:
	NiTexturingProperty();
	virtual ~NiTexturingProperty();

	struct _ApplyMode {	
		enum Mode {
			REPLACE		= 0,
			DECAL		= 1,
			MODULATE	= 2,
			DEPRECATED	= 3,
			DEPRECATED2	= 4,
			COUNT,
		};
	};
	using ApplyMode = _ApplyMode::Mode;

	struct _FilterMode {
		enum Mode {
			NEAREST				= 0,
			BILERP				= 1,
			TRILERP				= 2,
			NEAREST_MIPNEAREST	= 3,
			NEAREST_MIPLERP		= 4,
			BILERP_MIPNEAREST	= 5,
			ANISOTROPY			= 6,
			MAGLERP_MINANISO	= 7,
			COUNT,
		};
	};
	using FilterMode = _FilterMode::Mode;

	struct _ClampMode {
		enum Mode {
			CLAMP_S_CLAMP_T = 0,
			CLAMP_S_WRAP_T	= 1,
			WRAP_S_CLAMP_T	= 2,
			WRAP_S_WRAP_T	= 3,
			COUNT
		};
	};
	using ClampMode = _ClampMode::Mode;

	class SPEC_EMPTY_BASES Map : public NiMemObject {
	public:
		Map();
		virtual				~Map();
		virtual void		LoadBinary(NiStream& arStream);
		virtual void		SaveBinary(NiStream& arStream);
		virtual uint32_t	GetClassID() const;

		Bitfield16				m_usFlags;
		NiPointer<NiTexture>	m_spTexture;
		NiTextureTransform*		m_pkTextureTransform;
	};

	class ShaderMap : public Map {
	public:
		uint32_t m_uiID;
	};

	struct ALIGN2 _Flags {
		enum Flags : uint16_t {
			MULTI_TEXTURE_MASK	= 0x1,
			APPLY_MODE_MASK		= 0xE,
			APPLY_MODE_POS		= 0x1,
			DECAL_COUNT_MASK	= 0xFF0,
			DECAL_COUNT_POS		= 0x4,
		};

		bool	bMultiTexture	: 1;
		uint8_t bApplyMode		: 3;
	};

	Bitfield<_Flags>				m_usFlags;
	NiTPrimitiveArray<Map*>			m_kMaps;
	NiTPrimitiveArray<ShaderMap*>*	m_pkShaderMaps;

	CREATE_OBJECT(NiTexturingProperty, 0xA6AD40);
	NIRTTI_ADDRESS(0x11F49A4);
};

ASSERT_SIZE(NiTexturingProperty, 0x30)