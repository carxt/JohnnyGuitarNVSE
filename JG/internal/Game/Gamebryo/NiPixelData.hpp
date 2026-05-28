#pragma once

#include "NiObject.hpp"
#include "NiPalette.hpp"

NiSmartPointer(NiPixelData);

class NiPixelData : public NiObject {
public:
	NiPixelData();
	virtual ~NiPixelData();

	NiPixelFormat	m_kPixelFormat;
	NiPalettePtr	m_spPalette;
	uint8_t*		m_pucPixels;
	uint32_t*		m_puiWidth;
	uint32_t*		m_puiHeight;
	uint32_t*		m_puiOffsetInBytes;
	uint32_t		m_uiMipmapLevels;
	uint32_t		m_uiPixelStride;
	uint32_t		m_uiRevID;
	uint32_t		m_uiFaces;
	bool			bIsInternal;

	CREATE_OBJECT(NiPixelData, 0xA7C3F0);
	NIRTTI_ADDRESS(0x11F4A90);
};

ASSERT_SIZE(NiPixelData, 0x74)