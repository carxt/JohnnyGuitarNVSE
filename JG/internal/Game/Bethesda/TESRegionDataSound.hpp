#pragma once

#include "TESRegionData.hpp"
#include "BSSimpleList.hpp"
#include "TESRegionSound.hpp"

class TESSound;
class TESFile;
class BGSMusicType;
class MediaSet;

class TESRegionDataSound : public TESRegionData {
public:
	TESRegionDataSound();
	virtual ~TESRegionDataSound();

	virtual bool			LoadRegionDataSound(TESFile* apFile);
	virtual BGSMusicType*	GetMusicType() const;
	virtual bool			SetMusicType(BGSMusicType* apMusicType);
	virtual MediaSet*		GetIncidentalMediaSet() const;
	virtual MediaSet*		GetRandomBattleMediaSet() const;
	virtual void			SetIncidentalMediaSet(MediaSet* apMediaSet);

	BGSMusicType*						pMusicType;
	BSSimpleList<TESRegionSound*>		kSoundTypes;
	uint32_t							uiIncidentalMediaSet;
	BSSimpleList<MediaSet*>				kBattleMediaSets;
};

ASSERT_SIZE(TESRegionDataSound, 0x20)