#pragma once

#include "BSSimpleList.hpp"

class Script;
struct ACTION_OBJECT;
struct SCRIPT_LOCAL;
struct SCRIPT_EFFECT_DATA;

class ScriptLocals {
public:
	enum
	{
		kEvent_OnAdd = 0x00000001,
		kEvent_OnEquip = 0x00000002,		  // Called on Item and on Refr
		kEvent_OnActorEquip = kEvent_OnEquip, // presumably the game checks the type of the object
		kEvent_OnDrop = 0x00000004,
		kEvent_OnUnequip = 0x00000008,
		kEvent_OnActorUnequip = kEvent_OnUnequip,
		kEvent_OnDeath = 0x00000010,
		kEvent_OnMurder = 0x00000020,
		kEvent_OnCombatEnd = 0x00000040, // See 0x008A083C
		kEvent_OnHit = 0x00000080,		 // See 0x0089AB12
		kEvent_OnHitWith = 0x00000100,	 // TESObjectWEAP*	0x0089AB2F
		kEvent_OnPackageStart = 0x00000200,
		kEvent_OnPackageDone = 0x00000400,
		kEvent_OnPackageChange = 0x00000800,
		kEvent_OnLoad = 0x00001000,
		kEvent_OnMagicEffectHit = 0x00002000, // EffectSetting* 0x0082326F
		kEvent_OnSell = 0x00004000,			  // 0x0072FE29 and 0x0072FF05, linked to 'Barter Amount Traded' Misc Stat
		kEvent_OnStartCombat = 0x00008000,

		kEvent_OnOpen = 0x00010000,					  // while opening some container, not all
		kEvent_OnClose = 0x00020000,				  // idem
		kEvent_SayToDone = 0x00040000,				  // in Func0050 0x005791C1 in relation to SayToTopicInfo (OnSayToDone? or OnSayStart/OnSayEnd?)
		kEvent_OnGrab = 0x00080000,					  // 0x0095FACD and 0x009604B0 (same func which is called from PlayerCharacter_func001B and 0021)
		kEvent_OnRelease = 0x00100000,				  // 0x0047ACCA in relation to container
		kEvent_OnDestructionStageChange = 0x00200000, // 0x004763E7/0x0047ADEE
		kEvent_OnFire = 0x00400000,					  // 0x008BAFB9 (references to package use item and use weapon are close)

		kEvent_OnTrigger = 0x10000000,		// 0x005D8D6A	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerEnter = 0x20000000, // 0x005D8D50	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerLeave = 0x40000000, // 0x0062C946	OnTriggerLeave ?
		kEvent_OnReset = 0x80000000			// 0x0054E5FB
	};


	Script*							pScript;
	Bitfield32						uiFlags;
	BSSimpleList<ACTION_OBJECT*>*	pActions;
	BSSimpleList<SCRIPT_LOCAL*>*	pVariables;
	SCRIPT_EFFECT_DATA*				pScriptEffectData;

	SCRIPT_LOCAL* GetVariable(uint32_t auiIndex) const;
};

ASSERT_SIZE(ScriptLocals, 0x14);