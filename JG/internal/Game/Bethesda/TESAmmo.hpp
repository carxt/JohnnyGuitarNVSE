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

	float GetSpeed() const;
	void SetSpeed(float afSpeed);

	bool GetIsPlayable() const;
	void SetIsPlayable(bool abVal);

	uint8_t GetNumProjectiles() const;
	void SetNumProjectiles(uint8_t aucCount);

	BGSProjectile* GetProjectile() const;
	void SetProjectile(BGSProjectile* apProjectile);

	float GetWeight() const;
	void SetWeight(float afWeight);

	TESForm* GetAmmoConsumedForm() const;
	void SetAmmoConsumedForm(TESForm* apForm);

	float GetAmmoConsumedPercent() const;

	const BSSimpleList<TESAmmoEffect*>* GetAmmoEffectList() const;
	BSSimpleList<TESAmmoEffect*>* GetAmmoEffectList();

	const char* GetShortName() const;
	void SetShortName(const char* apText);

	const char* GetAbbreviation() const;
	void SetAbbreviation(const char* apText);

#ifdef GAME
	void GetEffectNames(char* apBuffer, uint32_t auiBufferSize) const;
#endif
};

#ifdef GAME
ASSERT_SIZE(TESAmmo, 0xDC);
#else
ASSERT_SIZE(TESAmmo, 0x130);
#endif