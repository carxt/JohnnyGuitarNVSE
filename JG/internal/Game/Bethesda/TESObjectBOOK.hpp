#pragma once

#include "TESBoundObject.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESIcon.hpp"
#include "TESScriptableForm.hpp"
#include "TESEnchantableForm.hpp"
#include "TESValueForm.hpp"
#include "TESWeightForm.hpp"
#include "TESDescription.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSMessageIcon.hpp"
#include "BGSPickupPutdownSounds.hpp"
#include "ActorValue.hpp"

class TESObjectBOOK : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public TESScriptableForm, 
	public TESEnchantableForm, public TESValueForm, public TESWeightForm, public TESDescription, public BGSDestructibleObjectForm, 
		public BGSMessageIcon, public BGSPickupPutdownSounds 
{
public:
	TESObjectBOOK();
	~TESObjectBOOK();

	struct ALIGN1 _BookFlags {
		enum Flags : uint8_t {
			SCROLL		= 1u << 0,
			CANT_TAKE	= 1u << 1,
		};
		bool bScroll	: 1;
		bool bCantTake	: 1;
	};
	using BookFlags = _BookFlags::Flags;

	struct Data {
		Bitfield<_BookFlags>	ucFlags;
		uint8_t					eTeaches;
	};

	Data kData;

	TESFORM_TYPE(TESObjectBOOK);

	bool GetScroll() const;
	void SetScroll(bool abVal);

	bool GetCantTake() const;
	void SetCantTake(bool abVal);

	ActorValue::Index GetTeaches() const;
	void SetTeaches(ActorValue::Index aeIndex);

	const char* GetText() const;

#ifdef GAME
	bool Read(TESObjectREFR* apReader);
#endif
};

#ifdef GAME
ASSERT_SIZE(TESObjectBOOK, 0xC4)
#else
ASSERT_SIZE(TESObjectBOOK, 0x120)
#endif