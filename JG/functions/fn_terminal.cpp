#include "fn_terminal.h"
#include <GameUI.h>

bool Cmd_RefreshTerminalMenu_Execute(COMMAND_ARGS) {
	*result = 0;
	ComputersMenu* g_computersMenu = *(ComputersMenu**)0x11D9334;
	if (g_computersMenu) {
		ThisCall(0x7586E0, g_computersMenu, 0);
		*result = 1;
	}
	return true;
}

bool Cmd_SetTerminalMenuItemFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiMenuEntry = 0;
	uint32_t uiFlags;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiMenuEntry, &uiFlags) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem()) {
			pPos->GetItem()->ucFlags = uiFlags;
			*result = 1;
		}
	}
	return true;
}
bool Cmd_GetTerminalMenuItemFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiMenuEntry = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiMenuEntry) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem()) {
			*result = pPos->GetItem()->ucFlags;
			if (IsConsoleMode())
				Console_Print("GetTerminalMenuItemFlags %d >> %.f", uiMenuEntry, *result);
		}
	}
	return true;
}

bool Cmd_RemoveTerminalMenuItem_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiMenuEntry = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiMenuEntry) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem()) {
			auto pItem = pPos->GetItem();
			pPos->RemoveHead();
			ThisCall(0x5010C0, pItem, 1); // Destructor
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemCount_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		*result = pTerminal->GetMenuItemList()->ItemsInList();
		if (IsConsoleMode()) 
			Console_Print("GetTerminalMenuItemCount >> %.f", *result);
	}
	return true;
}

bool Cmd_GetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiMenuEntry = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiMenuEntry) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem() && pPos->GetItem()->pSubMenu)
			*(FormID*)result = pPos->GetItem()->pSubMenu->GetFormID();
	}
	return true;
}

bool Cmd_SetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	BGSTerminal* pSubMenu = nullptr;
	uint32_t uiMenuEntry = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiMenuEntry, &pSubMenu) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && pSubMenu && IS_TYPE(pSubMenu, BGSTerminal)) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem()) {
			pPos->GetItem()->pSubMenu = pSubMenu;
			*result = 1;
		}
	}
	return true;
}

bool Cmd_SetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	BGSNote* pNote = nullptr;
	uint32_t uiMenuEntry = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiMenuEntry, &pNote) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && pNote && IS_TYPE(pNote, BGSNote)) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem()) {
			pPos->GetItem()->pDisplayNote = pNote;
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiMenuEntry = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiMenuEntry) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem() && pPos->GetItem()->pDisplayNote)
			*(FormID*)result = pPos->GetItem()->pDisplayNote->GetFormID();
	}
	return true;
}

bool Cmd_SetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiTextType = 0, uiMenuEntry = 0;
	char cText[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiTextType, &uiMenuEntry, &cText) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && uiTextType > 0) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem()) {
			if (uiTextType == 1) {
				pPos->GetItem()->strEntryText.Set(cText);
				*result = 1;
			}
			else if (uiTextType == 2) {
				pPos->GetItem()->strResultText.Set(cText);
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiTextType = 0, uiMenuEntry = 0;
	const char* pText = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiTextType, &uiMenuEntry) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && uiTextType > 0) {
		auto pPos = pTerminal->GetMenuItemList()->GetAt(uiMenuEntry);
		if (pPos && pPos->GetItem()) {
			if (uiTextType == 1) {
				pText = pPos->GetItem()->strEntryText.c_str();
			}
			else if (uiTextType == 2) {
				pText = pPos->GetItem()->strResultText.c_str();
			}
		}
		g_strInterface->Assign(PASS_COMMAND_ARGS, pText);
		if (IsConsoleMode()) 
			Console_Print("GetTerminalMenuItemText >> %s", pText);
	}
	return true;
}

bool Cmd_AddTerminalMenuItem_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* pTerminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		TERMINAL_MENU_ITEM* pItem = BSMemory::malloc<TERMINAL_MENU_ITEM>();
		if (pItem) {
			ThisCall(0x500960, pItem); // Constructor
			pTerminal->AddMenuItem(pItem);
			*result = 1;
		}
	}
	return true;
}