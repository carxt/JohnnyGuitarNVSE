#pragma once

#include "BaseFormComponent.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESModelRDT.hpp"
#include "BGSMessageIcon.hpp"

class BGSBipedModelList;

class TESBipedModelForm : public BaseFormComponent {
public:
	TESBipedModelForm();
	~TESBipedModelForm();

	struct ALIGN1 _BipedFlags {
		enum Flags : uint8_t {
			HAS_BACKPACK	= 1u << 2,
			MEDIUM_ARMOR	= 1u << 3,
			ADDON_MODEL		= 1u << 4,
			POWER_ARMOR		= 1u << 5,
			NON_PLAYABLE	= 1u << 6,
			HEAVY_ARMOR		= 1u << 7,
		};

		bool 				: 1;
		bool 				: 1;
		bool bHasBackpack	: 1;
		bool bMediumArmor	: 1;
		bool bAddonModel	: 1;
		bool bPowerArmor	: 1;
		bool bNonPlayable	: 1;
		bool bHeavyArmor	: 1;
	};
	using BipedFlags = _BipedFlags::Flags;

	struct Data {
		Bitfield32				uiObjectSlots;
		Bitfield<_BipedFlags>	ucFlags;
	};

	Data 				kData;
	TESModelTextureSwap kBipedModels[SEX::COUNT];
	TESModelTextureSwap kWorldModels[SEX::COUNT];
	TESIcon				kIcons[SEX::COUNT];
	BGSMessageIcon		kMessageIcons[SEX::COUNT];
	TESModelRDT			kConstraintTemplate;

	bool GetHasBackpack() const;
	void SetHasBackpack(bool abVal);

	bool GetIsMediumArmor() const;
	void SetIsMediumArmor(bool abVal);

	bool GetIsAddonModel() const;
	void SetIsAddonModel(bool abVal);

	bool GetIsPowerArmor() const;
	void SetIsPowerArmor(bool abVal);

	bool GetPlayable() const;
	void SetPlayable(bool abVal);

	bool GetIsHeavyArmor() const;
	void SetIsHeavyArmor(bool abVal);

	bool FillsBipedSlot(BIPED_OBJECT aeSlot, bool abHair, BGSBipedModelList* apModelList) const;
	void SetFillsBipedSlot(BIPED_OBJECT aeSlot, bool abVal);

	bool FillsMatchingBipedSlots(const TESBipedModelForm* apOther) const;

	const char* GetBipedConstraint() const;

	const char* GetBipedModel(SEX aeSex) const;
	void SetBipedModel(SEX aeSex, const char* apPath);

	TESModelTextureSwap* GetBipedTESModel(SEX aeSex) const;
	static TESModelTextureSwap* GetBipedTESModel(const TESForm* apForm, const TESObjectREFR* apRef);

	const char* GetWorldModel(SEX aeSex) const;
	static const char* GetWorldModel(const TESForm* apForm, const TESObjectREFR* apRef);
	void SetWorldModel(SEX aeSex, const char* apPath);

	TESModelTextureSwap* GetWorldTESModel(SEX aeSex) const;
	static TESModelTextureSwap* GetWorldTESModel(const TESForm* apForm, const TESObjectREFR* apRef);

	const char* GetIcon(SEX aeSex) const;
	static const char* GetIcon(const TESForm* apForm, const TESObjectREFR* apRef);
	void SetIcon(SEX aeSex, const char* apPath);

	const char* GetMessageIcon(SEX aeSex) const;
	static const char* GetMessageIcon(const TESForm* apForm, const TESObjectREFR* apRef);
	void SetMessageIcon(SEX aeSex, const char* apPath);

	static TESBipedModelForm* GetFormAsBipedModel(const TESForm* apForm);
};

#ifdef GAME
ASSERT_SIZE(TESBipedModelForm, 0xDC);
#else
ASSERT_SIZE(TESBipedModelForm, 0x168);
#endif