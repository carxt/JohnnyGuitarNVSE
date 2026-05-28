#pragma once

#include "NiMemObject.hpp"

class SPEC_EMPTY_BASES NiPixelFormat : public NiMemObject {
public:
	enum Format {
		FORMAT_RGB					= 0,
		FORMAT_RGBA					= 1,
		FORMAT_PAL					= 2,
		FORMAT_PALALPHA				= 3,
		FORMAT_DXT1					= 4,
		FORMAT_DXT3					= 5,
		FORMAT_DXT5					= 6,
		FORMAT_RGB24NONINTERLEAVED	= 7,
		FORMAT_BUMP					= 8,
		FORMAT_BUMPLUMA				= 9,
		FORMAT_RENDERERSPECIFIC		= 10,
		FORMAT_ONE_CHANNEL			= 11,
		FORMAT_TWO_CHANNEL			= 12,
		FORMAT_THREE_CHANNEL		= 13,
		FORMAT_FOUR_CHANNEL			= 14,
		FORMAT_DEPTH_STENCIL		= 15,
		FORMAT_UNKNOWN				= 16,
		FORMAT_MAX					= 17,
	};

	enum Component {
		COMP_RED		= 0,
		COMP_GREEN		= 1,
		COMP_BLUE		= 2,
		COMP_ALPHA		= 3,
		COMP_COMPRESSED = 4,
		COMP_OFFSET_U	= 5,
		COMP_OFFSET_V	= 6,
		COMP_OFFSET_W	= 7,
		COMP_OFFSET_Q	= 8,
		COMP_LUMA		= 9,
		COMP_HEIGHT		= 10,
		COMP_VECTOR_X	= 11,
		COMP_VECTOR_Y	= 12,
		COMP_VECTOR_Z	= 13,
		COMP_PADDING	= 14,
		COMP_INTENSITY	= 15,
		COMP_INDEX		= 16,
		COMP_DEPTH		= 17,
		COMP_STENCIL	= 18,
		COMP_EMPTY		= 19,
		COMP_MAX		= 20,
		NUM_COMPS		= 4,
	};

	enum Tiling {
		TILE_NONE	= 0,
		TILE_XENON	= 1,
		TILE_MAX	= 2,
	};

	enum Representation {
		REP_NORM_INT	= 0,
		REP_HALF		= 1,
		REP_FLOAT		= 2,
		REP_INDEX		= 3,
		REP_COMPRESSED	= 4,
		REP_UNKNOWN		= 5,
		REP_INT			= 6,
		REP_MAX			= 7,
	};

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
	NiComponentSpec		m_akComponents[4];

	bool IsAlpha() const {
		return m_eFormat == FORMAT_DXT3 || m_eFormat == FORMAT_DXT5 || m_eFormat == FORMAT_RGBA;
	}
};

ASSERT_SIZE(NiPixelFormat, 0x044);