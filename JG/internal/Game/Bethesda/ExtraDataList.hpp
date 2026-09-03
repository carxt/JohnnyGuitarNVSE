#pragma once

#include "BaseExtraList.hpp"
#include "BSSimpleList.hpp"
#include "BSStringT.hpp"

class AlchemyItem;
class TESForm;

class ExtraDataList : public BaseExtraList {
public:
	static ExtraDataList* Create();

	void CopyList(ExtraDataList* apCopy);

#ifdef GAME
	void CopyListForContainer(ExtraDataList* apCopy, bool abDontRemove);
#endif

	void CopyListForReference(ExtraDataList* apCopy, bool abRemove);

	void SetPoison(AlchemyItem* apPoison);
	void RemovePoison();

	TESForm* GetEmittanceSource() const;
	void SetEmittanceSource(TESForm* apSource);

	bool GetWeaponModSlotActive(uint8_t aucSlot) const;
	void SetWeaponModSlot(uint8_t aucSlot);

	uint8_t GetWeaponModFlags() const;
	void SetWeaponModFlags(uint8_t aucFlags);
};

ASSERT_SIZE(ExtraDataList, 0x20);