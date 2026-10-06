#pragma once

#include "BSSoundMessage.hpp"

class TESSound;

class BSGameSound {
public:
	BSGameSound();
	virtual				~BSGameSound();
	virtual bool		IsPlaying() const;
	virtual bool		IsInDecay() const;
	virtual bool		IsPaused() const;
	virtual float		GetVolume() const;
	virtual void		SetInaudible(bool abSet);
	virtual void		SetEnvironmentType(uint32_t aeEnvironmentType);
	virtual bool		ComparePriority(uint32_t auiOtherPriority);
	virtual bool		PriorityTest(BSGameSound* apOtherSound);
	virtual bool		Open();
	virtual bool		Prepare();
	virtual void		Copy(BSGameSound* apSource, bool abPrepare);
	virtual bool		Play(bool abLoop);
	virtual bool		Pause();
	virtual bool		Stop();
	virtual bool		SetVolume(float afVolume);
	virtual void		UpdateEmitterPosition();
	virtual bool		Update(DWORD adwTimeDelta);
	virtual bool		ProcessDataRequest(int); // Stub
	virtual bool		SetEmitterPosition(NiPoint3 akPos);
	virtual bool		SetEmitterPositionF(float afPosX, float afPosY, float afPosZ);
	virtual void		GetEmitterPosition(NiPoint3& arPos) const;
	virtual void		SetEmitterOrientation(float, float, float); // Stub
	virtual void		SetMinMax(float afMin, float afMax);
	virtual void		SetAttenuationCurve(uint16_t ausVal0, uint16_t ausVal1, uint16_t ausVal2, uint16_t ausVal3, uint16_t ausVal4);
	virtual bool		SetFrequency(float afFrequency);
	virtual float		GetFrequency() const;
	virtual void		Seek(uint32_t auiMilliseconds);

	struct ALIGN4 _TypeFlags {
		enum Flags : uint32_t {
			IS_2D							= 1u << 0,
			IS_3D							= 1u << 1,
			VOICE							= 1u << 2,
			FOOTSTEPS						= 1u << 3,
			LOOP							= 1u << 4,
			SYSTEM_SOUND					= 1u << 5,
			VARIABLE_FREQUENCY				= 1u << 6,
			BATTLE_SOUND					= 1u << 7, // Casing, explosion, gunfire, block
			ONE_SHOT						= 1u << 8,
			UNKBIT9							= 1u << 9,
			UNKBIT10						= 1u << 10,
			MUSIC							= 1u << 11,
			REGION							= 1u << 12,
			MAYBE_UNDERWATER				= 1u << 13,
			IMPACT							= 1u << 14, // Projectile impacts, disable, explosion impacts, collision sounds
			CACHED							= 1u << 15,
			DONT_CACHE						= 1u << 16,
			IS_2D_GUNFIRE					= 1u << 17,
			FIRST_PERSON					= 1u << 18,
			MODULATED						= 1u << 19,
			RADIO							= 1u << 20,
			IGNORE_TIMESCALE				= 1u << 21,
			UNKBIT22						= 1u << 22, // Prevents being stopped? Is muted instead. Used by radio
			MUSIC_B23						= 1u << 23,
			EXTERNAL_SYNC					= 1u << 24, // Used by radios to skip to current time
			ENVELOPE_FAST					= 1u << 25,
			ENVELOPE_SLOW					= 1u << 26,
			IS_2D_RADIUS					= 1u << 27,
			BEAM_EMITTER					= 1u << 28,
			UNKBIT29						= 1u << 29,
			ANIMATION_DRIVEN				= 1u << 30,
			UNKBIT31						= 1u << 31, // Player's equip sound
		};

		bool b2D						: 1;
		bool b3D						: 1;
		bool bVoice						: 1;
		bool bFootsteps					: 1;
		bool bLoop						: 1;
		bool bSystemSound				: 1;
		bool bVariableFrequency			: 1;
		bool bBattleSound				: 1;
		bool bOneShot					: 1;
		bool bUnkBit9					: 1;
		bool bUnkBit10					: 1;
		bool bMusic						: 1;
		bool bRegion					: 1;
		bool bMaybeUnderwater			: 1;
		bool bImpact					: 1;
		bool bIsCached					: 1;
		bool bDontCache					: 1;
		bool b2DGunfire					: 1;
		bool bFirstPerson				: 1;
		bool bModulated					: 1;
		bool bRadio						: 1;
		bool bIgnoreTimescale			: 1;
		bool bUnkBit22					: 1;
		bool bMusicB23					: 1;
		bool bExternalSync				: 1;
		bool bEnvelopeFast				: 1;
		bool bEnvelopeSlow				: 1;
		bool b2DRadius					: 1;
		bool bBeamEmitter				: 1;
		bool bUnkBit29					: 1;
		bool bAnimationDriven			: 1;
		bool bUnkBit31					: 1;
	};
	using TypeFlags = _TypeFlags::Flags;

	struct ALIGN4 _StateFlags {
		enum StateFlags : uint32_t {
			OPENED			= 1u << 0,
			UNK_1			= 1u << 1,
			UNK_2			= 1u << 2,
			UNK_3			= 1u << 3,
			FINISHED		= 1u << 4,
			PLAYING			= 1u << 5,
			PAUSED			= 1u << 6,
			UNK_7			= 1u << 7,
			VALID			= 1u << 8,
			FADING			= 1u << 9,
			SILENT			= 1u << 10,
			READY			= 1u << 11,
			OPENING			= 1u << 12,
			PLAYED			= 1u << 13,
			UNK_14			= 1u << 14,
			IS_VALID_BEAM	= 1u << 15,
			TIME_RESTRICTED	= 1u << 16,
			INAUDIBLE		= 1u << 17,
			UNK_18			= 1u << 18,
			DECAY			= 1u << 19,
			SYNC_PAUSED		= 1u << 20,
		};

		bool bOpened		: 1;
		bool bUnk1			: 1;
		bool bUnk2			: 1;
		bool bUnk3			: 1;
		bool bFinished		: 1;
		bool bPlaying		: 1;
		bool bPaused		: 1;
		bool bUnk7			: 1;
		bool bValid			: 1;
		bool bFading		: 1;
		bool bSilent		: 1;
		bool bReady			: 1;
		bool bOpening		: 1;
		bool bPlayed		: 1;
		bool bUnk14			: 1;
		bool bIsValidBeam	: 1;
		bool bTimeRestricted: 1;
		bool bInaudible		: 1;
		bool bUnk18			: 1;
		bool bInDecay		: 1;
		bool bSyncPaused	: 1;
	};
	using StateFlags = _StateFlags::StateFlags;

	struct ALIGN4 _ModifierFlags {
		enum Flags {
			MUTE_WHEN_SUBMERGED = 1u << 0,
			START_AT_RANDOM_POS = 1u << 1,
		};

		bool bMuteWhenSubmerged : 1;
		bool bStartAtRandomPos	: 1;
	};
	using ModifierFlags = _ModifierFlags::Flags;

	using pfnPlayCallback_t = void(__cdecl*)(void* apContext, int32_t aiDuration);
	using pfnCompletionCallback_t = void(__cdecl*)(void* apContext, bool abSucceeded);

	uint32_t					uiSoundID;
	Bitfield<_TypeFlags>		uiTypeFlags;
	Bitfield<_ModifierFlags>	uiModifierFlags;
	Bitfield<_StateFlags>		uiStateFlags;
	int32_t						iDuration; // In milliseconds
	uint16_t					usStaticAttenuation;
	uint16_t					usReverbAttenuation;
	uint16_t					usSystemAttenuation;
	uint16_t					usDistanceAttenuation;
	uint16_t					usFaderAttenuation;
	float						fCurrentVolume;
	float						fBeginTime;
	float						fEndTime;
	Bitfield32					uiWeatherFlags;
	uint16_t					usSamplesPerSecond;
#if USE_JIP_CHANGES // JIP
	char						cFileName[254];
	TESSound*					pSourceSound;
#else
	char						cFileName[MAX_PATH];
#endif
	float						fFrequencyMod;
	float						fMaxDist;
	float						fMinDist;
	uint32_t					uiSoundHash;
	uint32_t					uiDirectoryHash;
	uint32_t					uiSoundSize;
	float						fDistanceToListener;
	uint32_t					eEnvironmentType;
	uint8_t						ucFreqVariance;
	uint16_t					usModSamplesPerSecond;
	uint32_t					uiSynchStartTime;
	uint32_t					uiCleanupDelayInMS;
	pfnCompletionCallback_t		pfnCompletionCallback;
	pfnPlayCallback_t			pfnPlayedCallback;
	void*						pSoundCompletionContext;
	void*						pSoundPlayContext;
	uint32_t					uiLoopStart;
	uint32_t					uiLoopEnd;
	NiPoint3					kBeamEndPos;
	uint32_t					uiPriority;
	SoundMessageList			kQueuedMessags;

	uint32_t GetID() const;

	bool Is2DRadiusSound() const;
	bool Is3DSound() const;

	bool IsPlayable() const;
	bool IsOneShot() const;
	bool IsSimpleLoop() const;
	bool IsEnvelopeLoop() const;
	bool IsEnvelopeLoopFast() const;
	bool IsEnvelopeLoopSlow() const;
	bool IsLoopingSound() const;

	bool IsInaudible() const;

	const char* GetFileName() const;
};

ASSERT_SIZE(BSGameSound, 0x198);