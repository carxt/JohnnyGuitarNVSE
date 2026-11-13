#pragma once

#include "GameTypes.h"
#include "GameScript.h"
#include <string>

struct ParamInfo;
class TESForm;
class TESObjectREFR;
class BaseExtraList;

const uint32_t kMaxMessageLength = 0x4000;

struct ScriptVar {
	uint32_t		id;
	void* next;
	double		data;
};

// only records individual objects if there's a block that matches it
// ### how can it tell?
class ScriptLocals {
public:
	enum {
		kEvent_OnAdd = 1,
		kEvent_OnEquip = 2,
		kEvent_OnActorEquip = 2,
		kEvent_OnDrop = 4,
		kEvent_OnUnequip = 8,
		kEvent_OnActorUnequip = 8,

		kEvent_OnDeath = 0x10,
		kEvent_OnMurder = 0x20,
		kEvent_OnCombatEnd = 0x40,			// See 0x008A083C
		kEvent_OnHit = 0x80,			// See 0x0089AB12

		kEvent_OnHitWith = 0x100,			// TESObjectWEAP*	0x0089AB2F
		kEvent_OnPackageStart = 0x200,
		kEvent_OnPackageDone = 0x400,
		kEvent_OnPackageChange = 0x800,

		kEvent_OnLoad = 0x1000,
		kEvent_OnMagicEffectHit = 0x2000,			// EffectSetting* 0x0082326F
		kEvent_OnSell = 0x4000,			// 0x0072FE29 and 0x0072FF05, linked to 'Barter Amount Traded' Misc Stat
		kEvent_OnStartCombat = 0x8000,

		kEvent_OnOpen = 0x10000,		// while opening some container, not all
		kEvent_OnClose = 0x20000,
		kEvent_SayToDone = 0x40000,		// in Func0050 0x005791C1 in relation to SayToTopicInfo (OnSayToDone? or OnSayStart/OnSayEnd?)
		kEvent_OnGrab = 0x80000,		// 0x0095FACD and 0x009604B0 (same func which is called from PlayerCharacter_func001B and 0021)

		kEvent_OnRelease = 0x100000,		// 0x0047ACCA in relation to container
		kEvent_OnDestructionStageChange = 0x200000,		// 0x004763E7/0x0047ADEE
		kEvent_OnFire = 0x400000,		// 0x008BAFB9 (references to package use item and use weapon are close)

		kEvent_OnTrigger = 0x10000000,		// 0x005D8D6A	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerEnter = 0x20000000,		// 0x005D8D50	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerLeave = 0x40000000,		// 0x0062C946	OnTriggerLeave ?
		kEvent_OnReset = 0x80000000		// 0x0054E5FB
	};

	struct Event {
		TESForm* object;
		uint32_t		eventMask;
	};

	struct Struct10 {
		bool	effectStart;
		bool	effectFinish;
		uint8_t	unk03[6];
	};

	typedef tList<Event> EventList;
	typedef tList<ScriptVar> VarList;

	Script* m_script;		// 00
	uint32_t			m_unk1;			// 04
	EventList* m_eventList;	// 08
	VarList* m_vars;		// 0C
	Struct10* unk010;		// 10

	ScriptVar* GetVariable(uint32_t id);
};