#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESForm;

class TESDescription : public BaseFormComponent {
public:
	TESDescription();
	~TESDescription();

	virtual const char* GetDescription(TESForm* apForm, uint32_t auiChunkID) const;

#ifdef GAME
	uint32_t	uiFileOffset;
#else
	BSString	strText;
	uint32_t	uiDlgItem;
#endif
};

#ifdef GAME
ASSERT_SIZE(TESDescription, 0x8);
#else
ASSERT_SIZE(TESDescription, 0x10);
#endif