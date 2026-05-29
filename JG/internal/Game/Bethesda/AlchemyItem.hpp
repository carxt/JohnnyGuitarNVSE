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

	class Data : public MagicItem::Data {
	public:
		SpellItem*	pAddictionItem;
		float		fAddictionChance;
		TESSound*	pConsumeSound;
	};

	Data	kData;
	TESIcon	kMessageIcon;

	TESFORM_TYPE(AlchemyItem);
};

ASSERT_SIZE(AlchemyItem, 0xD8);