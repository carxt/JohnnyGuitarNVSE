#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "BGSOpenCloseForm.hpp"
#include "TESBoundAnimObject.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"

class TESSound;
class Actor;
class DoorLock;

class TESObjectDOOR : public TESBoundAnimObject, public TESFullName, public TESModelTextureSwap, public TESScriptableForm,
						public BGSDestructibleObjectForm, public BGSOpenCloseForm {
public:
	TESObjectDOOR();
	~TESObjectDOOR();

	struct ALIGN1 _DoorFlags {
		enum Flags : uint8_t {
			OBLIVION_GATE	= 1u << 0,
			AUTOMATIC		= 1u << 1,
			HIDDEN			= 1u << 2,
			MINIMAL_USE		= 1u << 3,
			SLIDING_DOOR	= 1u << 4,
		};

		bool bOblivionGate	: 1;
		bool bAutomatic		: 1;
		bool bHidden		: 1;
		bool bMinimalUse	: 1;
		bool bSlidingDoor	: 1;
	};
	using DoorFlags = _DoorFlags::Flags;

	uint32_t				_pad74;
	TESSound*				pOpenSound;
	TESSound*				pCloseSound;
	TESSound*				pLoopSound;
	Bitfield<_DoorFlags>	ucFlags;
	BSSimpleList<TESForm*>	kRandomTeleports;

	TESFORM_TYPE(TESObjectDOOR);

	TESSound* GetOpenSound() const;
	void SetOpenSound(TESSound* apSound);

	TESSound* GetCloseSound() const;
	void SetCloseSound(TESSound* apSound);

	TESSound* GetLoopSound() const;
	void SetLoopSound(TESSound* apSound);

	bool IsOblivionGate() const;
	void SetOblivionGate(bool abVal);

	bool IsAutomaticDoor() const;
	void SetAutomaticDoor(bool abVal);

	bool IsHidden() const;
	void SetHidden(bool abVal);

	bool IsMinimalUse() const;
	void SetMinimalUse(bool abVal);

	bool IsSlidingDoor() const;
	void SetSlidingDoor(bool abVal);

	bool IsRandomDoor() const;

	bool RandomlyTeleportsTo(const TESForm* apSpace) const;

	TESObjectREFR* FindRandomTeleportTarget(TESObjectREFR* apStartDoor, TESObjectREFR* apActionRef) const;
	
	const BSSimpleList<TESForm*>* GetRandomTeleportList() const;
	BSSimpleList<TESForm*>* GetRandomTeleportList();
	void ClearRandomTeleportList();

	static bool CanBeRandomTeleport(const TESForm* apSpace);

	static bool CanActorIgnoreLock(TESObjectREFR* apDoor, Actor* apActor, bool abActivate, bool abMovement);
	static bool CanActorIgnoreLock(const DoorLock* apLock, Actor* apActor, TESObjectREFR* apDoor, bool abActivate, bool abMovement);
};

ASSERT_SIZE(TESObjectDOOR, 0x90)