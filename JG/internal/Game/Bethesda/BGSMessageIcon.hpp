#pragma once

#include "TESIcon.hpp"

class BGSMessageIcon : public BaseFormComponent {
public:
	BGSMessageIcon();
	~BGSMessageIcon();

	TESIcon	kIcon;

	const char* GetMessageIconTextureName() const;
	void SetMessageIconTextureName(const char* apName);

	uint32_t GetMessageIconTextureNameLength() const;
};

ASSERT_SIZE(BGSMessageIcon, 0x10);