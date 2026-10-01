#pragma once

#include "BSEnums.hpp"

class BGSChangeFlags {
public:
	struct _ChangeFlags {
		enum Flags {
			FORM_FLAGS						= 0x1,
	
			// TESForm
			BASE_OBJECT_VALUE				= 0x2,
			BASE_OBJECT_FULLNAME			= 0x4,
	
			// BGSEncounterZone
			ENCOUNTER_ZONE_FLAGS			= 0x2,
			ENCOUNTER_ZONE_GAME_DATA		= 0x80000000,
	
			// TESObjectBOOK
			BOOK_TEACHES_SKILL				= 0x20,
	
			// BGSTalkingActivator
			TALKING_ACTIVATOR_SPEAKER		= 0x800000,
	
			// BGSListForm
			FORM_LIST_ADDED_FORM			= 0x80000000,
	
			// TESWaterForm
			WATER_REMAPPED					= 0x80000000,
	
			// TESPackage
			PACKAGE_WAITING					= 0x40000000,
			PACKAGE_NEVER_RUN				= 0x80000000,
	
			// TESQuest
			QUEST_FLAGS						= 0x2,
			QUEST_SCRIPT_DELAY				= 0x4,
			QUEST_OBJECTIVES				= 0x20000000,
			QUEST_SCRIPT					= 0x40000000,
			QUEST_STAGES					= 0x80000000,
	
			// TESTopicInfo
			TOPIC_SAIDONCE					= 0x80000000,
	
			// TESClass
			CLASS_TAG_SKILLS				= 0x2,
	
			// TESFaction
			FACTION_FLAGS					= 0x2,
			FACTION_REACTIONS				= 0x4,
			FACTION_CRIME_COUNTS			= 0x80000000,
	
			// TESActorBase
			ACTOR_BASE_DATA					= 0x2,
			ACTOR_BASE_ATTRIBUTES			= 0x4,
			ACTOR_BASE_AIDATA				= 0x8,
			ACTOR_BASE_SPELLLIST			= 0x10,
			ACTOR_BASE_FULLNAME				= 0x20,
	
			// TESNPC
			NPC_SKILLS						= 0x200,
			NPC_CLASS						= 0x400,
			NPC_FACE						= 0x800,
			NPC_GENDER						= 0x1000000,
			NPC_RACE						= 0x2000000,
	
			// TESCreature
			CREATURE_SKILLS					= 0x200,
	
			// TESLeveledList
			LEVELED_LIST_ADDED_OBJECT		= 0x80000000,
	
			// BGSNote
			NOTE_READ						= 0x80000000,
	
			// TESObjectCELL
			CELL_FLAGS						= 0x2,
			CELL_FULLNAME					= 0x4,
			CELL_OWNERSHIP					= 0x8,
			CELL_EXTERIOR_SHORT				= 0x10000000,
			CELL_EXTERIOR_CHAR				= 0x20000000,
			CELL_DETACHTIME					= 0x40000000,
			CELL_SEENDATA					= 0x80000000,
	
			// TESObjectREFR
			REFR_MOVE						= 0x2,
			REFR_HAVOK_MOVE					= 0x4,
			REFR_CELL_CHANGED				= 0x8,
			REFR_SCALE						= 0x10,
			REFR_INVENTORY					= 0x20,
			REFR_EXTRA_OWNERSHIP			= 0x40,
			REFR_EXTRA_ACTIVATING_CHILDREN	= 0x4000000,
			REFR_LEVELED_INVENTORY			= 0x8000000,
			REFR_ANIMATION					= 0x10000000,
			REFR_EXTRA_ENCOUNTER_ZONE		= 0x20000000,
			REFR_EXTRA_CREATED_ONLY			= 0x40000000,
			REFR_EXTRA_GAME_ONLY			= 0x80000000,
	
			OBJECT_EXTRA_ITEM_DATA			= 0x400,
			OBJECT_EXTRA_AMMO				= 0x800,
			OBJECT_EXTRA_LOCK				= 0x1000,
			OBJECT_OPEN_DEFAULT_STATE		= 0x400000,
			OBJECT_OPEN_STATE				= 0x800000,
	
			// Actor
			ACTOR_LIFESTATE					= 0x400,
			ACTOR_EXTRA_PACKAGE_DATA		= 0x800,
			ACTOR_EXTRA_MERCHANT_CONTAINER	= 0x1000,
			ACTOR_EXTRA_DISMEMBERED_LIMBS	= 0x20000,
			ACTOR_LEVELED_ACTOR				= 0x40000,
			ACTOR_DISPOSITION_MODIFIERS		= 0x80000,
			ACTOR_DAMAGE_MODIFIERS			= 0x200000,
			ACTOR_OVERRIDE_MODIFIERS		= 0x400000,
			ACTOR_PERMANENT_MODIFIERS		= 0x800000,
	
			// TESObjectDOOR
			DOOR_EXTRA_TELEPORT				= 0x20000,
		};
	};
	using ChangeFlags = _ChangeFlags::Flags;

	Bitfield32 uiFlags;

	operator uint32_t() const {
		return uiFlags;
	}

	bool CheckFlags(uint32_t auiFlag) const;

	bool CheckBit(uint32_t auiBit) const;

	static const char* GetFlagName(uint32_t auiFlag, FORM_TYPE aeFormType, bool abShortName);
};
using BGSChangeFlag = BGSChangeFlags::ChangeFlags;
using FormChangeFlag = BGSChangeFlags::ChangeFlags;

ASSERT_SIZE(BGSChangeFlags, 0x4);