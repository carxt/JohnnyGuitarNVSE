#pragma once

#include "TESIcon.hpp"

class BGSMessageIcon : public BaseFormComponent {
public:
	BGSMessageIcon();
	~BGSMessageIcon();

	TESIcon	kIcon;

	const TESIcon* GetIcon() const;
	TESIcon* GetIcon();

	const char* GetMessageIconTextureName() const;
	void SetMessageIconTextureName(const char* apName);

	uint32_t GetMessageIconTextureNameLength() const;
};

#ifdef GAME
ASSERT_SIZE(BGSMessageIcon, 0x10);
#else
ASSERT_SIZE(BGSMessageIcon, 0x20);
#endif