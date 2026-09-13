#pragma once

#include "NiMemObject.hpp"

class SPEC_EMPTY_BASES NiPixelFormat : public NiMemObject {
public:
	struct _Format {
		enum Format {
			RGB					 = 0,
			RGBA				 = 1,
			PAL					 = 2,
			PALALPHA			 = 3,
			DXT1				 = 4,
			DXT3				 = 5,
			DXT5				 = 6,
			RGB24_NONINTERLEAVED = 7,
			BUMP				 = 8,
			BUMPLUMA			 = 9,
			RENDERER_SPECIFIC	 = 10,
			ONE_CHANNEL			 = 11,
			TWO_CHANNEL			 = 12,
			THREE_CHANNEL		 = 13,
			FOUR_CHANNEL		 = 14,
			DEPTH_STENCIL		 = 15,
			UNKNOWN				 = 16,
			COUNT,
		};
	};
	using Format = _Format::Format;

	struct _Component {
		enum Component {
			RED				= 0,
			GREEN			= 1,
			BLUE			= 2,
			ALPHA			= 3,
			COMPRESSED		= 4,
			OFFSET_U		= 5,
			OFFSET_V		= 6,
			OFFSET_W		= 7,
			OFFSET_Q		= 8,
			LUMA			= 9,
			HEIGHT			= 10,
			VECTOR_X		= 11,
			VECTOR_Y		= 12,
			VECTOR_Z		= 13,
			PADDING			= 14,
			INTENSITY		= 15,
			INDEX			= 16,
			DEPTH			= 17,
			STENCIL			= 18,
			EMPTY			= 19,
			COUNT,
			COMP_COUNT		= 4,
		};
	};
	using Component = _Component::Component;

	struct _Tiling {
		enum Tiling {
			NONE  = 0,
			XENON = 1,
			COUNT,
		};
	};
	using Tiling = _Tiling::Tiling;

	struct _Representation {
		enum Representation {
			NORM_INT	= 0,
			HALF		= 1,
			FLOAT		= 2,
			INDEX		= 3,
			COMPRESSED	= 4,
			UNKNOWN		= 5,
			INT			= 6,
			COUNT,
		};
	};
	using Representation = _Representation::Representation;

	class NiComponentSpec {
	public:
		Component		m_eComponent;
		Representation	m_eRepresentation;
		uint8_t			m_ucBitsPerComponent;
		bool			m_bSigned;
	};

	Bitfield8			m_ucFlags;
	uint8_t				m_ucBitsPerPixel;
	Format				m_eFormat;
	Tiling				m_eTiling;
	D3DFORMAT			m_uiRendererHint;
	uint32_t			m_uiExtraData;
	NiComponentSpec		m_akComponents[Component::COMP_COUNT];

	bool IsAlpha() const {
		return m_eFormat == Format::DXT3 || m_eFormat == Format::DXT5 || m_eFormat == Format::RGBA;
	}
};

ASSERT_SIZE(NiPixelFormat, 0x44);