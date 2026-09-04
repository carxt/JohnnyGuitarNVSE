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
};

ASSERT_SIZE(ExtraDataList, 0x20);