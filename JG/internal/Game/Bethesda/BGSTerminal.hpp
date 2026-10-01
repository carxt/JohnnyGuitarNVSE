#pragma once

#include "TESObjectACTI.hpp"
#include "TESCondition.hpp"
#include "TESDescription.hpp"
#include "Script.hpp"

class BGSNote;
class ScriptLocals;
class BGSTerminal;
class TERMINAL_MENU_ITEM;

class BGSTerminal : public TESObjectACTI, public TESDescription {
public:
	BGSTerminal();
	~BGSTerminal();

	struct ALIGN1 _TerminalFlags {
		enum Flags : uint8_t {
			LEVELED			= 1u << 0,
			UNLOCKED		= 1u << 1,
			ALT_COLORS		= 1u << 2,
			HIDE_WELCOME	= 1u << 3,
		};

		bool bLeveled		: 1;
		bool bUnlocked		: 1;
		bool bAltColors		: 1;
		bool bHideWelcome	: 1;
	};
	using TerminalFlags = _TerminalFlags::Flags;

	struct Data {
		uint8_t						eDifficulty;
		Bitfield<_TerminalFlags>	ucFlags;
		uint8_t						eType;
	};

	BSSimpleList<TERMINAL_MENU_ITEM*>	kMenuItems;
	BGSNote*							pPassword;
	Data								kData;

	BSSimpleList<TERMINAL_MENU_ITEM*>* GetMenuItemList();
	const BSSimpleList<TERMINAL_MENU_ITEM*>* GetMenuItemList() const;
	void AddMenuItem(TERMINAL_MENU_ITEM* apItem);
	void RemoveMenuItem(TERMINAL_MENU_ITEM* apItem);
	void ClearMenuItemList();

	BGSNote* GetPassword() const;
	void SetPassword(BGSNote* apPassword);

#ifdef GAME
	LOCK_LEVEL GetRawDifficulty(const TESObjectREFR* apRef) const;
	void SetRawDifficulty(TESObjectREFR* apRef, LOCK_LEVEL aeLevel);
#endif

	bool IsLeveled() const;
	void SetLeveled(bool abVal);

	bool IsUnlocked() const;
#ifdef GAME
	bool IsUnlocked(const TESObjectREFR* apRef) const;
	void SetUnlocked(TESObjectREFR* apRef);
#endif

	bool UsesAltColor() const;
	void SetUsesAltColor(bool abVal);

	bool HidesWelcomeTextWhenDisplayingImage() const;
	void SetHidesWelcomeTextWhenDisplayingImage(bool abVal);

#ifdef GAME
	const char* GetServerText() const;

	LOCK_LEVEL GetHackDifficultyLockLevel(const TESObjectREFR* apRef) const;

	uint32_t GetHackMiniGameValue(const TESObjectREFR* apRef) const;

	float GetMinSkillRequiredToHack(const TESObjectREFR* apRef) const;

	bool IsHackEligible(const TESObjectREFR* apRef, float afSkill) const;

	static bool IsHacked(const TESObjectREFR* apRef);
	static void SetHacked(TESObjectREFR* apRef, bool abVal);

	static bool IsLockedOut(const TESObjectREFR* apRef);
	static void LockOut(TESObjectREFR* apRef, bool abVal);

	static bool IsTerminalRefInUse(const TESObjectREFR* apRef);

	static void ResetState(TESObjectREFR* apRef);
#endif
};

#ifdef GAME
ASSERT_SIZE(BGSTerminal, 0xA8);
#else
ASSERT_SIZE(BGSTerminal, 0xE4);
#endif

class TERMINAL_MENU_ITEM {
public:
	struct ALIGN1 _Flags {
		enum Flags : uint8_t {
			ADD_NOTE		= 1u << 0,
			FORCE_REDRAW	= 1u << 1,
			SELECTED		= 1u << 2,
		};

		bool bAddNote		: 1;
		bool bForceRedraw	: 1;
		bool bSelected		: 1;
	};
	using Flags = _Flags::Flags;

	BSString			strEntryText;
	BSString			strResultText;
	Script				kResultScript;
	TESCondition		kConditions;
	BGSNote*			pDisplayNote;
	BGSTerminal*		pSubMenu;
	Bitfield<_Flags>	ucFlags;

	bool IsAutoAdd() const;
	void SetAutoAdd(bool abVal);

	bool ForcesRedraw() const;
	void SetForcesRedraw(bool abVal);

	bool IsSelected() const;
	void SetSelected(bool abVal);

#ifdef GAME
	bool RunResultScript(TESObjectREFR* apActivator);
#endif
};

#ifdef GAME
ASSERT_SIZE(TERMINAL_MENU_ITEM, 0x78);
#else
ASSERT_SIZE(TERMINAL_MENU_ITEM, 0x80);
#endif