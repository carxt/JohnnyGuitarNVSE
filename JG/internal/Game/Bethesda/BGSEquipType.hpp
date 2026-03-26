#pragma once

#include "BaseFormComponent.hpp"

class TESForm;
class BGSMenuIcon;

class BGSEquipType : public BaseFormComponent {
public:
	BGSEquipType();
	~BGSEquipType();

	uint32_t	eEquipType;

	uint32_t GetEquipType() const;
	void SetEquipType(uint32_t aeEquipType);

	static uint32_t GetEquipType(const TESForm* apForm);
	static BGSMenuIcon* GetEquipTypeIcon(uint32_t aeType);
	static const char* GetEquipTypeIconFilename(uint32_t aeType);
};

ASSERT_SIZE(BGSEquipType, 0x8);