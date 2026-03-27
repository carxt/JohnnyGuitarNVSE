#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/TESIcon.hpp"
#include "Bethesda/TESTexture.hpp"

class TESCasino : public TESForm, public TESFullName {
public:
	TESCasino();
	~TESCasino();

	struct ALIGN4 _CasinoFlags {
		enum Flags : uint32_t {
			DEALER_STAYS_ON_17 = 1u << 0,
		};

		bool bDealerStaysOn17 : 1;
	};
	using CasinoFlags = _CasinoFlags::Flags;

	struct Data {
		float					fShufflePercent;
		float					fBlackjackPayout;
		int32_t					iReelStops[7];
		int32_t					iNumDecks;
		int32_t					iMaxWinnings;
		FormID					uiCasinoChipID;
		FormID					uiQuestID;
		Bitfield<_CasinoFlags>	uiFlags;
	};


	union {
		TESModelTextureSwap kModels[10];
		struct {
			TESModelTextureSwap kChip1;
			TESModelTextureSwap kChip5;
			TESModelTextureSwap kChip10;
			TESModelTextureSwap kChip25;
			TESModelTextureSwap kChip100;
			TESModelTextureSwap kChip500;
			TESModelTextureSwap kChipRoulette;
			TESModelTextureSwap kSlotMachine;
			TESModelTextureSwap kBlackjackTable;
			TESModelTextureSwap kRouletteTable;
		};
	};

	TESIcon		kSlotReel[7];
	TESTexture	kBlackjackDeck[4];
	Data		kCasinoData;

	TESFORM_TYPE(TESCasino);
};

ASSERT_SIZE(TESCasino, 0x220);
ASSERT_SIZE(TESCasino::Data, 0x38);