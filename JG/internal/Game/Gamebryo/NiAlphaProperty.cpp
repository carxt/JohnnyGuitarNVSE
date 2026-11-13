#include "NiAlphaProperty.hpp"

static constexpr NiAlphaProperty::AlphaFunction D3DBlendToNiBlend[12] = {
	NiAlphaProperty::AlphaFunction::ZERO,			// 0  D3DBLEND_ZERO 
	NiAlphaProperty::AlphaFunction::ZERO,			// 1  D3DBLEND_ZERO
	NiAlphaProperty::AlphaFunction::ONE,			// 2  D3DBLEND_ONE
	NiAlphaProperty::AlphaFunction::SRC_COLOR,		// 3  D3DBLEND_SRCCOLOR
	NiAlphaProperty::AlphaFunction::INV_SRC_COLOR,	// 4  D3DBLEND_INVSRCCOLOR
	NiAlphaProperty::AlphaFunction::SRC_ALPHA,		// 5  D3DBLEND_SRCALPHA
	NiAlphaProperty::AlphaFunction::INV_SRC_ALPHA,	// 6  D3DBLEND_INVSRCALPHA
	NiAlphaProperty::AlphaFunction::DEST_ALPHA,		// 7  D3DBLEND_DESTALPHA
	NiAlphaProperty::AlphaFunction::INV_DEST_ALPHA,	// 8  D3DBLEND_INVDESTALPHA
	NiAlphaProperty::AlphaFunction::DEST_COLOR,		// 9  D3DBLEND_DESTCOLOR
	NiAlphaProperty::AlphaFunction::INV_DEST_COLOR,	// 10 D3DBLEND_INVDESTCOLOR
	NiAlphaProperty::AlphaFunction::SRC_ALPHA_SAT,	// 11 D3DBLEND_SRCALPHASAT
};

bool NiAlphaProperty::GetAlphaBlending() const {
	return m_usFlags.bAlphaBlending;
}

// GAME - 0x49ED90
void NiAlphaProperty::SetAlphaBlending(bool abBlend) {
	m_usFlags.bAlphaBlending = abBlend;
}

bool NiAlphaProperty::GetAlphaTesting() const {
	return m_usFlags.bAlphaTesting;
}

// GAME - 0x4393C0
void NiAlphaProperty::SetAlphaTesting(bool abTest) {
	m_usFlags.bAlphaTesting = abTest;
}

uint8_t NiAlphaProperty::GetTestRef() const {
	return m_ucAlphaTestRef;
}

// GAME - 0x94DB80
void NiAlphaProperty::SetTestRef(uint8_t aucRef) {
	m_ucAlphaTestRef = aucRef;
}

NiAlphaProperty::AlphaFunction NiAlphaProperty::GetSrcBlendMode() const {
	return static_cast<AlphaFunction>(m_usFlags.ucSrcBlend);
}

// GAME - 0x439340
void NiAlphaProperty::SetSrcBlendMode(AlphaFunction aeSrcBlend) {
	m_usFlags.ucSrcBlend = aeSrcBlend;
}

NiAlphaProperty::AlphaFunction NiAlphaProperty::GetDestBlendMode() const {
	return static_cast<AlphaFunction>(m_usFlags.Get(Flags::DEST_BLEND, Flags::DEST_BLEND_POS));
}

// GAME - 0x439390
void NiAlphaProperty::SetDestBlendMode(AlphaFunction aeDestBlend) {
	m_usFlags.Set(aeDestBlend, Flags::DEST_BLEND, Flags::DEST_BLEND_POS);
}

NiAlphaProperty::TestFunction NiAlphaProperty::GetTestMode() const {
	return static_cast<TestFunction>(m_usFlags.ucTestFunc);
}

// GAME - 0x4393E0
void NiAlphaProperty::SetTestMode(TestFunction aeTestFunc) {
	m_usFlags.ucTestFunc = aeTestFunc;
}

// GAME - 0xBA5060
NiAlphaProperty::AlphaFunction NiAlphaProperty::GetNiAlphaFunctionFromD3D(D3DBLEND aeBlend) {
	return D3DBlendToNiBlend[aeBlend];
}
