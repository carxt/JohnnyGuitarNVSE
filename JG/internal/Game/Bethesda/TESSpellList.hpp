#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"

class SpellItem;
class TESLevSpell;

class TESSpellList : public BaseFormComponent {
public:
	TESSpellList();
	~TESSpellList();
#ifdef GAME
	virtual uint32_t	GetSaveSizeTES(uint32_t auiChangeFlags);
	virtual void		SaveGameTES(uint32_t auiChangeFlags);
	virtual void		LoadGameTES(uint32_t auiChangeFlags);
#endif

	BSSimpleList<SpellItem*>	kSpells;
	BSSimpleList<TESLevSpell*>	kLeveledSpells;

	uint32_t	GetSpellCount() const;
};

ASSERT_SIZE(TESSpellList, 0x14);