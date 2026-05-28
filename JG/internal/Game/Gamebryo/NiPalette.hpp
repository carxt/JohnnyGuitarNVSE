#pragma once

#include "NiObject.hpp"

NiSmartPointer(NiPalette);

class NiPalette : public NiObject {
public:
	NiPalette();
	virtual ~NiPalette();

	struct PaletteEntry {
		uint8_t m_ucRed;
		uint8_t m_ucGreen;
		uint8_t m_ucBlue;
		uint8_t m_ucAlpha;
	};

	struct RendererData {
		NiPalette* m_pkPalette;
	};

	bool			m_bAlpha;
	uint32_t		m_uiEntries;
	uint32_t		m_uiRevID;
	PaletteEntry*	m_pkPalette;
	RendererData*	m_pkRendererData;
	NiPalette*		m_pkPrev;
	NiPalette*		m_pkNext;

	CREATE_OBJECT(NiPalette, 0xA8B220);
	NIRTTI_ADDRESS(0x11F5C08);
};

ASSERT_SIZE(NiPalette, 0x24)