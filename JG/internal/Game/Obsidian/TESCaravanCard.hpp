#pragma once

#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/BGSPickupPutdownSounds.hpp"
#include "Bethesda/TESBoundObject.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/TESScriptableForm.hpp"
#include "Bethesda/TESValueForm.hpp"

class TESCaravanCard : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public BGSMessageIcon, public TESValueForm, public TESScriptableForm, public BGSPickupPutdownSounds {
public:
	TESCaravanCard();
	~TESCaravanCard();

	struct _CardSuit {
		enum Suit {
			NONE		= 0,
			HEARTS		= 1,
			SPADES		= 2,
			DIAMONDS	= 3,
			CLUBS		= 4,
			BLANK		= 5,
			COUNT
		};
	};
	using CardSuit = _CardSuit::Suit;

	struct _CardValue {
		enum Value {
			NONE				= 0,
			ACE					= 1,
			TWO					= 2,
			THREE				= 3,
			FOUR				= 4,
			FIVE				= 5,
			SIX					= 6,
			SEVEN				= 7,
			EIGHT				= 8,
			NINE				= 9,
			TEN					= 10,
			VALUE_CARDS_COUNT	= 11,
			JACK				= 12,
			QUEEN				= 13,
			KING				= 14,
			JOKER				= 15,
			COUNT
		};
	};
	using CardValue = _CardValue::Value;

	struct Data {
		CardSuit	eCardSuit;
		CardValue	eFaceValue;
	};

#ifdef GAME
	bool		bIsActive;
#endif
	TESTexture	kFaceTexture;
	TESTexture	kBackTexture;
	Data		kData;

	TESFORM_TYPE(TESCaravanCard);

#ifdef GAME
	bool GetIsActive() const;
	void SetIsActive(bool abVal);
#endif

	TESTexture* GetFaceTexture();
	const TESTexture* GetFaceTexture() const;

	TESTexture* GetBackTexture();
	const TESTexture* GetBackTexture() const;

	CardSuit GetCardSuit() const;

	CardValue GetFaceValue() const;
};

#ifdef GAME
ASSERT_SIZE(TESCaravanCard, 0xBC);
#else
ASSERT_SIZE(TESCaravanCard, 0x12C);
#endif