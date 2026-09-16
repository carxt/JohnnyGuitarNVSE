#pragma once

#include "BSShaderProperty.hpp"
#include "Gamebryo/NiTexturingProperty.hpp"

class NiAVObject;

class BSShaderBloodSplatterProperty : public BSShaderProperty {
public:
	virtual D3DTEXTUREADDRESS				GetClampD3D() const;
	virtual void							SetClampD3D(D3DTEXTUREADDRESS aeClampMode);
	virtual NiTexturingProperty::ClampMode	GetClampNi() const;
	virtual void							SetClampNi(NiTexturingProperty::ClampMode aeClampMode);

	NiPointer<NiTexture>			spTexture[2];
	NiTexturingProperty::ClampMode	eClampMode;
	float*							pfFadeAlpha;

	NIRTTI_ADDRESS(0x11FF0F4);

	struct SplatterGeometry {
		NiGeometry*	pGeometry;
		RenderPass*	pPass;
	};

	void SetTexture(uint32_t auiIndex, NiTexture* apTexture);

	static void SetFadeSourceRecurse(NiAVObject* apObject, float* apfFadeAlpha);
};

ASSERT_SIZE(BSShaderBloodSplatterProperty, 0x70)