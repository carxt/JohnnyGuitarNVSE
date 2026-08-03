#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "BGSEquipType.hpp"
#include "BGSMessageIcon.hpp"
#include "BGSPickupPutdownSounds.hpp"
#include "EffectItem.hpp"
#include "TESBoundObject.hpp"
#include "TESWeightForm.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"
#include "MagicItem.hpp"

class SpellItem;

class AlchemyItem : public TESBoundObject, public MagicItem, public TESModelTextureSwap, public TESIcon,
	public BGSMessageIcon, public TESScriptableForm, public TESWeightForm, public BGSEquipType, public BGSDestructibleObjectForm, public BGSPickupPutdownSounds {
public:
	AlchemyItem();
	~AlchemyItem();

	struct _Flags {
		enum Flags {
			MEDICINE = 0x4,
		};
	};
	using Flags = _Flags::Flags;

	class Data {
	public:
		int32_t		iCostOverride;
		Bitfield8	ucFlags;
		SpellItem*	pAddictionItem;
		float		fAddictionChance;
		TESSound*	pConsumeSound;
	};

	Data	kData;
	TESIcon	kMessageIcon;

	TESFORM_TYPE(AlchemyItem);

	bool GetFlag(Flags aeFlag) const;
	void SetFlag(Flags aeFlag, bool abVal);

	SpellItem* GetAddictionItem() const;
	void SetAddictionItem(SpellItem* apItem);

	float GetAddictionChance() const;
	void SetAddictionChance(float afChance);

	TESSound* GetConsumptionSound() const;
	void SetConsumptionSound(TESSound* apSound);

	bool IsWater() const;
};

ASSERT_SIZE(AlchemyItem, 0xD8);