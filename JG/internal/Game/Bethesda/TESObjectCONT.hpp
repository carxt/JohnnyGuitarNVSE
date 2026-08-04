#pragma once

#include "TESBoundAnimObject.hpp"
#include "TESContainer.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"
#include "TESWeightForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSOpenCloseForm.hpp"

class TESSound;

class TESObjectCONT : public TESBoundAnimObject, public TESContainer, public TESFullName, public TESModelTextureSwap,
						public TESScriptableForm, public TESWeightForm, public BGSDestructibleObjectForm, public BGSOpenCloseForm {
public:
	TESObjectCONT();
	~TESObjectCONT();

	struct ALIGN1 _ContainerFlags {
		enum Flags : uint8_t {
			RESPAWNS = 1u << 1,
		};

		bool bRespawns : 1;
	};
	using ContainerFlags = _ContainerFlags::Flags;

	struct Data {
		Bitfield<_ContainerFlags>	ucFlags;
	};

	uint32_t	_pad88;
	TESSound*	pOpenSound;
	TESSound*	pCloseSound;
	TESSound*	pLoopSound;
	Data		kData;

	TESFORM_TYPE(TESObjectCONT);

	TESSound* GetOpenSound() const;
	void SetOpenSound(TESSound* apSound);

	TESSound* GetCloseSound() const;
	void SetCloseSound(TESSound* apSound);

	TESSound* GetLoopSound() const;
	void SetLoopSound(TESSound* apSound);

	bool GetRespawn() const;

	bool CanActivate(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef, bool abAllowLockpicing) const;
};

ASSERT_SIZE(TESObjectCONT, 0x9C);