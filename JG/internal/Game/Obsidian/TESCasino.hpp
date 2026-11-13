#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/TESIcon.hpp"
#include "Bethesda/TESTexture.hpp"

class TESQuest;
class TESCasinoChips;

class TESCasino : public TESForm, public TESFullName {
public:
	TESCasino();
	~TESCasino();

	struct _ModelType {
		enum Type {
			CHIP_1			= 0,
			CHIP_5			= 1,
			CHIP_10			= 2,
			CHIP_25			= 3,
			CHIP_100		= 4,
			CHIP_500		= 5,
			CHIP_ROULETTE	= 6,
			SLOT_MACHINE	= 7,
			BLACKJACK_TABLE	= 8,
			ROULETTE_TABLE	= 9,
			COUNT,
		};
	};
	using ModelType = _ModelType::Type;

	struct _TextureType {
		enum Type {
			REEL_A = 0,
			REEL_B = 1,
			REEL_C = 2,
			REEL_D = 3,
			REEL_E = 4,
			REEL_F = 5,
			REEL_W = 6,
			DECK_1 = 7,
			DECK_2 = 8,
			DECK_3 = 9,
			DECK_4 = 10,
			COUNT,
		};
	};
	using TextureType = _TextureType::Type;

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
		TESModelTextureSwap kModels[ModelType::COUNT];
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
	union {
		TESTexture kTextures[TextureType::COUNT];
		struct {
			TESTexture kReelA;
			TESTexture kReelB;
			TESTexture kReelC;
			TESTexture kReelD;
			TESTexture kReelE;
			TESTexture kReelF;
			TESTexture kReelW;
			TESTexture kDeck1;
			TESTexture kDeck2;
			TESTexture kDeck3;
			TESTexture kDeck4;
		};
	};
	Data		kData;

	TESFORM_TYPE(TESCasino);

	const TESModelTextureSwap* GetModel(ModelType aeType) const;
	TESModelTextureSwap* GetModel(ModelType aeType);

	const TESTexture* GetTexture(TextureType aeType) const;
	TESTexture* GetTexture(TextureType aeType);

	int32_t GetMaxTotalWinnings() const;

	TESCasinoChips* GetChipType() const;

	TESQuest* GetQuest() const;
};

#ifdef GAME
ASSERT_SIZE(TESCasino, 0x220);
#else
ASSERT_SIZE(TESCasino, 0x384);
#endif