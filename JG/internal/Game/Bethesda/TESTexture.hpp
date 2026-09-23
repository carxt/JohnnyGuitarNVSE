#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESForm;
class TESObjectREFR;
class TESBitmap;

class TESTexture : public BaseFormComponent {
public:
	TESTexture();
	~TESTexture();

#ifdef EDITOR
	virtual void		Func_12(HWND, int32_t);
#endif
	virtual uint32_t	GetMaxAllowedSize() const;
	virtual const char* GetAsNormalFile(BSString& arStr) const;
	virtual const char* GetDefaultPath() const;
#ifdef EDITOR
	virtual const char* Func_16() const;
	virtual void		Func_17(const char* apFileName);
#endif

	BSString	strTextureName;
#ifdef EDITOR
	TESBitmap*	pImage;
	uint32_t	uiTextFieldControlId;
	uint32_t	uiEditButtonControlId;
	uint32_t	uiIconControlId;
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