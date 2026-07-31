#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"

class MediaSet;
class TESFaction;

class MediaLocationController : public TESForm, public TESFullName {
public:
	MediaLocationController();
	~MediaLocationController();

	struct _LoopState {
		enum State {
			LOOP		= 0,
			RANDOM		= 1,
			RETRIGGER	= 2,
			NONE		= 3,
		};
	};
	using LoopState = _LoopState::State;

	struct _DeadRepState {
		enum State {
			CONDITIONAL_NEUTRAL	= 0,
			CONDITIONAL_ENEMY	= 1,
			CONDITIONAL_ALLY	= 2,
			CONDITIONAL_FRIEND	= 3,
			LOCATION			= 4,
			NONE				= 5,
		};
	};
	using DeadRepState = _DeadRepState::State;

	struct ALIGN4 _Flags {
		enum Flags {
			DEAD_REP_MASK		= 0xF,
			LOOP_MASK			= 0x3,

			DEAD_REP_POS		= 0,
			LOOP_POS			= 4,

			DEFAULT_TIME 		= 1u << 6,
#if USE_MODDED_CHANGES
			IGNORE_ACTOR_COUNT	= 1u << 8,
#endif
		};

		uint8_t	eDeadRep			: 4;
		uint8_t	eLoop				: 2;
		bool	bDefaultTime		: 1;
		bool						: 1;
#if USE_MODDED_CHANGES
		bool	bIgnoreActorCount	: 1; // Added by JohnnyGuitar
#endif
	};
	using Flags = _Flags::Flags;

	uint32_t				uiLocationDelay;
	uint32_t				uiLayerTime;
	uint32_t				uiLoopTime;
	uint32_t				uiMediaStartTime;
	bool					bIsActive;
	bool					bInTension;
	bool					bInCombat;
	bool					bIsDay;
	bool					bIsConditional;
	float					fCurrentPlayerRadius;
	uint32_t				uiFoundHostileActors; // Both based on player's compass targets 
	uint32_t				uiFoundFactionActors;
	uint32_t				eCurrentFactionReaction;
	int8_t					cCurrentLayer;
	MediaSet*				pCurrentMediaSet;
	TESFullName				kMediaLocationControllerName;
	TESFaction*				pFaction;
	uint32_t				eFactionConditional;
	TESObjectREFR*			pAudioMarker;
	Bitfield<_Flags>		uiFlags;
	float					fLayerTwoPercent;
	float					fLayerThreePercent;
	float					fRetriggerDelay;
	float					fLocationDelay;
	uint32_t				uiDayStart;
	uint32_t				uiNightStart;
	BSSimpleList<MediaSet*> kConditionalNeutralSets;
	BSSimpleList<MediaSet*> kConditionalAllySets;
	BSSimpleList<MediaSet*> kConditionalFriendSets;
	BSSimpleList<MediaSet*> kConditionalEnemySets;
	BSSimpleList<MediaSet*> kLocationSets;
	BSSimpleList<MediaSet*> kBattleSets;

	TESFORM_TYPE(MediaLocationController);

	DeadRepState GetDeadRep() const;

	LoopState GetLoop() const;

	bool GetDefaultTime() const;

	bool GetDay() const;

	bool GetTension() const;

	bool GetDayNight() const;

	uint32_t GetLocationDelay() const;
	void SetLocationDelay(uint32_t auiDelay);

	MediaSet* GetRandomListItem(BSSimpleList<MediaSet*>* apList) const;
};

ASSERT_SIZE(MediaLocationController, 0xB8);