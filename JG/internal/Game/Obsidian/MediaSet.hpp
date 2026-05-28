#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"

class TESSound;

class MediaSet : public TESForm, public TESFullName {
public:
	MediaSet();
	~MediaSet();

	struct MediaLayer {
		BSString	strName;
		float		fAttenuation;
		float		fPercent;
	};

	enum Type {
		BATTLE		= 0,
		LOCATION	= 1,
		DUNGEON		= 2,
		INCIDENTAL	= 3,
		NONE		= 4,
	};

	uint32_t	uiMinLayerUpdate;
	uint32_t	uiSeekTime;
	uint32_t	uiLoopUpdate;
	bool		bStarted;
	bool		bInCombat;
	bool		bInTension;
	bool		bIsDay;
	int8_t		cCurrentLayer;
	TESFullName	kMediaSetName;
	uint32_t	eType;
	union {
		struct {
			MediaLayer	kLoopBattleDayOuter;
			MediaLayer	kExploreDayMiddle;
			MediaLayer	kSuspenseDayInner;
			MediaLayer	kNightOuter;
			MediaLayer	kNightMiddle;
			MediaLayer	kNightInner;
		};
		MediaLayer kLayers[6];
	};
	Bitfield8	ucEnableFlags;
	float		fWaitTime;
	float		fLoopFadeOut;
	float		fRecoveryTime;
	float		fNightTimeMax;
	TESSound*	pSound1;
	TESSound*	pSound2;

	TESFORM_TYPE(MediaSet);

	Type GetType() const;
	void SetType(Type aeType);

	TESSound* GetSound1() const;
	void SetSound1(TESSound* apSound);

	TESSound* GetSound2() const;
	void SetSound2(TESSound* apSound);
};

ASSERT_SIZE(MediaSet, 0xC4);