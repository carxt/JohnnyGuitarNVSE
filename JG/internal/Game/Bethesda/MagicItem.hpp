#pragma once

#include "TESFullName.hpp"
#include "EffectItemList.hpp"

class TESFile;

class MagicItem : public TESFullName, public EffectItemList {
public:
	MagicItem();
	~MagicItem();

	class Data {
	public:
		int32_t		iCostOverride;
		Bitfield32	uiFlags;
	};

	virtual bool					IsAutoCalc() const; // Name overlap with TESObject
	virtual void					SetAutoCalc(bool abVal);
	virtual MagicSystem::SpellType	GetSpellType() const;
	virtual bool					IgnoreResistance() const;
	virtual bool					GetNoAbsorbOrReflect() const;
	virtual uint32_t				GetChunkID() const;
	virtual void*					GetData() const;
	virtual uint32_t				GetDataSize();
	virtual bool					CompareMagicItemData(MagicItem* apItem);
	virtual void					CopyMagicItemData(MagicItem* apItem);
	virtual void					SaveMagicItemComponents();
	virtual void					Endian();
	virtual void					LoadMagicItemChunk(TESFile* apFile, uint32_t aeChunkID);

	uint32_t GetMagicItemFormID() const;
};

ASSERT_SIZE(MagicItem, 0x1C);