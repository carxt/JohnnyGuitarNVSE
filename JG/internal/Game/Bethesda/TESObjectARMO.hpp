#pragma once

#include "BGSBipedModelList.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSEquipType.hpp"
#include "BGSPickupPutdownSounds.hpp"
#include "BGSRepairItemList.hpp"
#include "TESBipedModelForm.hpp"
#include "TESBoundObject.hpp"
#include "TESEnchantableForm.hpp"
#include "TESFullName.hpp"
#include "TESHealthForm.hpp"
#include "TESScriptableForm.hpp"
#include "TESValueForm.hpp"
#include "TESWeightForm.hpp"

class TESObjectARMO : public TESBoundObject, public TESFullName, public TESScriptableForm, public TESEnchantableForm, 
	public TESValueForm, public TESWeightForm, public TESHealthForm, public TESBipedModelForm, public BGSDestructibleObjectForm, 
		public BGSEquipType, public BGSRepairItemList, public BGSBipedModelList, public BGSPickupPutdownSounds {
public:
	TESObjectARMO();
	~TESObjectARMO();

	struct FoleySound {
		enum Type {
			NORMAL_RUN		= 19,
			NORMAL_SNEAK	= 18,
			NORMAL_WALK		= 17,
			ARMOR_SNEAK		= 20,
			ARMOR_RUN		= 21,
			ARMOR_WALK		= 22,
		};
		
		TESSound*	pSound;
		uint8_t		ucChance;
		Type		eType;
	};

	struct ALIGN1 _ArmorFlags {
		enum Flags : uint8_t {
			MODULATES_VOICE = 1u << 0,
		};

		bool bModulatesVoice : 1;
	};
	using ArmorFlags = _ArmorFlags::Flags;

	struct Data {
		uint16_t				usArmorRating;
		float					fDamageThreshold;
		Bitfield<_ArmorFlags>	ucFlags;
		uint8_t					ucConditionLevel;
	};

	Data			kData;
	Bitfield32		uiFlags;
	union {
		BSSimpleList<FoleySound*>*	__restrict pFoleySounds;
		TESObjectARMO*				__restrict pFoleyTemplate;
	}				pAudioSource;
	bool			bIsFoleyBase;

	TESFORM_TYPE(TESObjectARMO);

	bool GetModulatesVoice() const;

	uint8_t GetArmorWeight() const;

	float GetArmorRating() const;
	float GetCalculatedArmorRating() const;

	float GetDamageThreshold() const;

	TESSound* GetFoleySound(FoleySound::Type aeType) const;
};

ASSERT_SIZE(TESObjectARMO, 0x190);