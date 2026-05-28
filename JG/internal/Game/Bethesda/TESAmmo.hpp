#pragma once

#include "TESBoundObject.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESIcon.hpp"
#include "BGSMessageIcon.hpp"
#include "TESValueForm.hpp"
#include "BGSClipRoundsForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSPickupPutdownSounds.hpp"
#include "TESScriptableForm.hpp"

class BGSProjectile;
class TESAmmoEffect;

class TESAmmo : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public BGSMessageIcon, public TESValueForm, public BGSClipRoundsForm,
					public BGSDestructibleObjectForm, public BGSPickupPutdownSounds, public TESScriptableForm {
public:
	TESAmmo();
	~TESAmmo();

	struct ALIGN4 _AmmoFlags {
		enum Flags : uint32_t {
			IGNORE_WEAP_RESISTANCE	= 1u << 0,
			NON_PLAYABLE			= 1u << 1,
		};

		bool bIgnoreWeaponResistance	: 1;
		bool bNonPlayable				: 1;
	};
	using AmmoFlags = _AmmoFlags::Flags;

	struct Data {
		float					fSpeed;
		Bitfield<_AmmoFlags>	uiFlags;
	};

	struct NVData {
		uint8_t			ucProjectilePerAmmo;
		BGSProjectile*	pProjectile;
		float			fWeight;
		TESForm*		pAmmoConsumedObject;
		float			fAmmoConsumedPercent;
	};

	Data							kData;
	NVData 							kNVData;
	BSString						strShortName;
	BSString						strAbbreviation;
	BSSimpleList<TESAmmoEffect*>	kAmmoEffects;

	TESFORM_TYPE(TESAmmo);

	bool GetIsPlayable() const;

	BGSProjectile* GetProjectile() const;
	uint8_t GetNumProjectiles() const;

	TESForm* GetAmmoConsumedForm() const;
	float GetAmmoConsumedPercent() const;

	const BSSimpleList<TESAmmoEffect*>* GetAmmoEffectList() const;
	BSSimpleList<TESAmmoEffect*>* GetAmmoEffectList();

	const char* GetShortName() const;
	const char* GetAbbreviation() const;

	void GetEffectNames(char* apBuffer, uint32_t auiBufferSize) const;
};

ASSERT_SIZE(TESAmmo, 0xDC);