#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESFile;
class TESForm;

class TESFullName : public BaseFormComponent {
public:
	TESFullName();
	~TESFullName();

	BSString	strFullName;

	const char* c_str() const;

	const char* GetFullName() const;
	static const char* GetFullName(const TESForm* apForm);

	uint32_t GetFullNameLength() const;
	static uint32_t GetFullNameLength(const TESForm* apForm);
};

ASSERT_SIZE(TESFullName, 0xC);