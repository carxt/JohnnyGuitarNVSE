#pragma once

#include "BSShaderProperty.hpp"

class NiTexture;

class BSTextureSet : public NiObject {
public:
	BSTextureSet();
	virtual ~BSTextureSet();

	virtual const char*	GetTexturePath(BSShaderProperty::TextureType aeTextureIndex) const;
	virtual void		GetTexture(BSShaderProperty::TextureType aeTextureIndex, NiPointer<NiTexture>& arTexture) const;
	virtual bool		SetTexturePath(BSShaderProperty::TextureType aeTextureIndex, const char* apPath);

	NIRTTI_ADDRESS(0x1200444);
};

ASSERT_SIZE(BSTextureSet, 0x8);