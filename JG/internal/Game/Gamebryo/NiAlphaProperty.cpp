#include "NiAlphaProperty.hpp"

static constexpr NiAlphaProperty::AlphaFunc D3DBlendToNiBlend[12] = {
	NiAlphaProperty::AlphaFunc::ZERO,			// 0  D3DBLEND_ZERO 
	NiAlphaProperty::AlphaFunc::ZERO,			// 1  D3DBLEND_ZERO
	NiAlphaProperty::AlphaFunc::ONE,			// 2  D3DBLEND_ONE
	NiAlphaProperty::AlphaFunc::SRC_COLOR,		// 3  D3DBLEND_SRCCOLOR
	NiAlphaProperty::AlphaFunc::INV_SRC_COLOR,	// 4  D3DBLEND_INVSRCCOLOR
	NiAlphaProperty::AlphaFunc::SRC_ALPHA,		// 5  D3DBLEND_SRCALPHA
	NiAlphaProperty::AlphaFunc::INV_SRC_ALPHA,	// 6  D3DBLEND_INVSRCALPHA
	NiAlphaProperty::AlphaFunc::DEST_ALPHA,		// 7  D3DBLEND_DESTALPHA
	NiAlphaProperty::AlphaFunc::INV_DEST_ALPHA,	// 8  D3DBLEND_INVDESTALPHA
	NiAlphaProperty::AlphaFunc::DEST_COLOR,		// 9  D3DBLEND_DESTCOLOR
	NiAlphaProperty::AlphaFunc::INV_DEST_COLOR,	// 10 D3DBLEND_INVDESTCOLOR
	NiAlphaProperty::AlphaFunc::SRC_ALPHA_SAT,	// 11 D3DBLEND_SRCALPHASAT
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

NiAlphaProperty::AlphaFunc NiAlphaProperty::GetSrcBlendMode() const {
	return static_cast<AlphaFunc>(m_usFlags.ucSrcBlend);
}

// GAME - 0x439340
void NiAlphaProperty::SetSrcBlendMode(AlphaFunc aeSrcBlend) {
	m_usFlags.ucSrcBlend = aeSrcBlend;
}

NiAlphaProperty::AlphaFunc NiAlphaProperty::GetDestBlendMode() const {
	return static_cast<AlphaFunc>(m_usFlags.Get(Flags::DEST_BLEND, Flags::DEST_BLEND_POS));
}

// GAME - 0x439390
void NiAlphaProperty::SetDestBlendMode(AlphaFunc aeDestBlend) {
	m_usFlags.Set(aeDestBlend, Flags::DEST_BLEND, Flags::DEST_BLEND_POS);
}

NiAlphaProperty::TestFunc NiAlphaProperty::GetTestMode() const {
	return static_cast<TestFunc>(m_usFlags.ucTestFunc);
}

// GAME - 0x4393E0
void NiAlphaProperty::SetTestMode(TestFunc aeTestFunc) {
	m_usFlags.ucTestFunc = aeTestFunc;
}

// GAME - 0xBA5060
NiAlphaProperty::AlphaFunc NiAlphaProperty::GetNiAlphaFunctionFromD3D(D3DBLEND aeBlend) {
	return D3DBlendToNiBlend[aeBlend];
}
