#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESTexture : public BaseFormComponent {
public:
	TESTexture();
	virtual ~TESTexture();

	virtual uint32_t	GetMaxAllowedSize() const;
	virtual const char* GetAsNormalFile(BSString& arStr) const;
	virtual const char* GetDefaultPath() const;

	BSString strTextureName;

	const char* GetTextureName() const;
	void SetTextureName(const char* apName);

	uint32_t GetTextureNameLength() const;
};

ASSERT_SIZE(TESTexture, 0xC);