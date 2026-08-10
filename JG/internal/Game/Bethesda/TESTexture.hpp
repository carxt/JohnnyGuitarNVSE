#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESForm;
class TESObjectREFR;

class TESTexture : public BaseFormComponent {
public:
	TESTexture();
	virtual ~TESTexture();

	virtual uint32_t	GetMaxAllowedSize() const;
	virtual const char* GetAsNormalFile(BSString& arStr) const;
	virtual const char* GetDefaultPath() const;

	BSString strTextureName;
#ifdef EDITOR
	void*	 pImage;
	uint32_t uiTextFieldControlId;
	uint32_t uiEditButtonControlId;
	uint32_t uiIconControlId;
#endif

	const char* GetTextureName() const;
	static const char* GetTextureName(const TESForm* apForm, const TESObjectREFR* apRef);
	void SetTextureName(const char* apName);

	uint32_t GetTextureNameLength() const;
};

#ifdef GAME
ASSERT_SIZE(TESTexture, 0xC);
#else
ASSERT_SIZE(TESTexture, 0x1C);
#endif