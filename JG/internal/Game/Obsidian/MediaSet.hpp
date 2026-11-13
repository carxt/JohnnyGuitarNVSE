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

	struct _Type {
		enum Type {
			BATTLE		= 0,
			LOCATION	= 1,
			DUNGEON		= 2,
			INCIDENTAL	= 3,
			NONE		= 4,
		};
	};
	using Type = _Type::Type;

#ifdef GAME
	uint32_t	uiMinLayerUpdate;
	uint32_t	uiSeekTime;
	uint32_t	uiLoopUpdate;
	bool		bStarted;
	bool		bInCombat;
	bool		bInTension;
	bool		bIsDay;
#endif
	int8_t		cCurrentLayer;
	TESFullName	kMediaSetName;
	Type		eType;
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
	TESSound*	pSoundA;
	TESSound*	pSoundB;

	TESFORM_TYPE(MediaSet);

	Type GetType() const;
	void SetType(Type aeType);

	TESSound* GetSoundA() const;
	void SetSoundA(TESSound* apSound);

	TESSound* GetSoundB() const;
	void SetSoundB(TESSound* apSound);
};

#ifdef GAME
ASSERT_SIZE(MediaSet, 0xC4);
#else
ASSERT_SIZE(MediaSet, 0xC8);
#endif