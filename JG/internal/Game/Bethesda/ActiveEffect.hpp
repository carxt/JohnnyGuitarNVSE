#pragma once

#include "BSSoundHandle.hpp"
#include "BSSimpleList.hpp"
#include "MagicSystem.hpp"

class MagicItem;
class EffectItem;
class MagicTarget;
class MagicCaster;
class BGSSaveGameBuffer;
class BGSLoadGameBuffer;
class BGSLoadFormBuffer;
class Actor;
class TESForm;
class TESBoundObject;
class MagicHitEffect;
class EffectSetting;

class ActiveEffect {
public:
	ActiveEffect();
	virtual					~ActiveEffect();
	virtual ActiveEffect*	Copy();
	virtual void			Finalize();
	virtual void			Update(float afDelta);
	virtual uint16_t		GetSaveSizeTES(Actor* apActor);
	virtual void			SaveGameBGS(BGSSaveGameBuffer* apBuffer);
	virtual void			SaveGameTES(Actor* apActor);
	virtual void			LoadGameBGS(BGSLoadGameBuffer* apBuffer);
	virtual void			LoadGameTES(Actor* apActor);
	virtual bool			InitLoadGameBGS();
	virtual bool			InitLoadGameTES(Actor* apActor);
	virtual void			FinishInitLoadGame(Actor* apActor);
	virtual bool			RevertBGS(BGSLoadFormBuffer* apBuffer);
	virtual bool			RevertTES(Actor* apActor);
	virtual void			CheckDeletedCaster(MagicCaster* apCaster);
	virtual bool			IsCausingDamage();
	virtual void			FinishLoadGame(BGSLoadFormBuffer* apBuffer);
	virtual void			CopyData(ActiveEffect* apTarget);
	virtual bool			CheckCast(MagicCaster* apCaster);
	virtual bool			CheckTarget(MagicTarget* apTarget);
	virtual void			Start();
	virtual void			Continue();
	virtual void			Finish();

	struct ALIGN4 _EffectFlags {
		enum Flags : uint32_t {
			NO_HITEFFECT_FORCED		= 1u << 0,
			NO_HITEFFECT_SHADER		= 1u << 1,
			NO_HITEFFECT_NIF		= 1u << 2,
			NO_SOUND				= 1u << 3,
			NO_INTIAL_FLARE			= 1u << 4,
			DEFERRED_SOUND			= 1u << 5,
			DEFERRED_HITEFFECT		= 1u << 6,
			HAS_CONDITIONS			= 1u << 7,
			FROM_WORN_ENCHANTMENT	= 1u << 8,
			WAS_DISPELED			= 1u << 9,
			QUEUED_FOR_REMOVAL		= 1u << 31,
		};

		bool bNoHitEffectForced		: 1;
		bool bNoHitEffectShader		: 1;
		bool bNoHitEffectNIF		: 1;
		bool bNoSound				: 1;
		bool bNoInitialFlare		: 1;
		bool bDeferredSound			: 1;
		bool bDeferredHitEffect		: 1;
		bool bHasConditions			: 1;
		bool bFromWornEnchantment	: 1;
		bool bWasDispeled			: 1;
		bool						: 6;
		bool						: 8;
		bool						: 7;
		bool bQueuedForRemoval		: 1;
	};
	using EffectFlags = _EffectFlags::Flags;

	float							fElapsedTime;
	MagicItem*						pSpell;
	EffectItem*						pEffect;
	bool							bActive;
	bool							bStarted;
	bool							bFinished;
	bool							bDone;
	bool							bWornEnchantment;
	Bitfield<_EffectFlags>			uiFlags;
	float							fMagnitude;
	float							fDuration;
	MagicTarget*					pTarget;
	MagicCaster*					pCaster;
	MagicSystem::SpellType			eSpellType;
	BSSoundHandle					hSound;
	TESBoundObject*					pSource;
	BSSimpleList<MagicHitEffect*>*	pHitEffects;
	MagicItem*						pDisplacementSpell;

	float GetElapsedTime() const;
	void SetElapsedTime(float afTime);

	MagicItem* GetSpell() const;

	EffectItem* GetEffectItem() const;

	bool IsActive() const;

	bool IsStarted() const;

	bool IsDone() const;

	float GetMagnitude() const;
	void SetMagnitude(float afMagnitude);

	float GetDuration() const;
	void SetDuration(float afDuration);

	MagicTarget* GetTarget() const;
	
	MagicCaster* GetCaster() const;

	MagicSystem::SpellType GetSpellType() const;

	TESBoundObject* GetEnchantmentSource() const;

	MagicItem* GetDisplacementSpell() const;

	EffectSetting* GetEffectSetting() const;

	void Dispel(bool abImmediate);
};

ASSERT_SIZE(ActiveEffect, 0x48);