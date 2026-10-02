#pragma once

#include "BSTextureSet.hpp"
#include "BSStringT.hpp"

NiSmartPointer(BSShaderTextureSet);

class BSShaderTextureSet : public BSTextureSet {
public:
	BSShaderTextureSet();
	~BSShaderTextureSet();

	BSString strTextures[BSShaderProperty::TextureType::COUNT];

	CREATE_OBJECT(BSShaderTextureSet, 0xBA8A00);
	NIRTTI_ADDRESS(0x120044C);
};

ASSERT_SIZE(BSShaderTextureSet, 0x38);