#include "fn_terminal.h"
#ifdef GAME
#include <GameUI.h>

bool Cmd_RefreshTerminalMenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	ComputersMenu* pMenu = *(ComputersMenu**)0x11D9334;
	if (pMenu) {
		ThisCall(0x7586E0, pMenu, false); // ComputersMenu::DisplayTerminal
		arResult = 1;
	}
	return true;
}

bool Cmd_SetTerminalMenuItemFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiIndex = 0;
	uint32_t uiFlags;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiIndex, &uiFlags) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (pEntry) {
			pEntry->entryFlags = uiFlags;
			arResult = 1;
		}
	}
	return true;
}
bool Cmd_GetTerminalMenuItemFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiIndex) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (pEntry) {
			arResult = pEntry->entryFlags;
			if (IsConsoleMode())
				Console_Print("GetTerminalMenuItemFlags %d >> %.f", uiIndex, arResult);
		}
	}
	return true;
}

bool Cmd_RemoveTerminalMenuItem_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiIndex) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (pEntry) {
			pTerminal->menuEntries.RemoveNth(uiIndex);
			ThisCall(0x5010C0, pEntry, 1);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemCount_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		arResult = pTerminal->menuEntries.Count();
		if (IsConsoleMode()) 
			Console_Print("GetTerminalMenuItemCount >> %.f", arResult);
	}
	return true;
}

bool Cmd_GetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiIndex) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (pEntry && pEntry->subMenu)
			ScriptUtils::SetFormIDResult(arResult, pEntry->subMenu->GetFormID());
	}
	return true;
}

bool Cmd_SetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	BGSTerminal* pSubMenu = nullptr;
	uint32_t uiIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiIndex, &pSubMenu) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && pSubMenu && IS_TYPE(pSubMenu, BGSTerminal)) {
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (pEntry) {
			pEntry->subMenu = pSubMenu;
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_SetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	BGSNote* pNote = nullptr;
	uint32_t uiIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiIndex, &pNote) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && pNote && IS_TYPE(pNote, BGSNote)) {
		BGSTerminal::MenuEntry* entry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (entry) {
			entry->displayNote = pNote;
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t uiIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &uiIndex) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (pEntry && pEntry->displayNote) 
			ScriptUtils::SetFormIDResult(arResult, pEntry->displayNote->GetFormID());
	}
	return true;
}

bool Cmd_SetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t eTextType = 0, uiIndex = 0;
	char cText[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &eTextType, &uiIndex, &cText) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && eTextType > 0) {
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (eTextType == 1) {
			pEntry->entryText.Set(cText);
			arResult = 1;
		}
		else if (eTextType == 2) {
			pEntry->resultText.Set(cText);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	uint32_t eTextType = 0, uiIndex = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal, &eTextType, &uiIndex) && pTerminal && IS_TYPE(pTerminal, BGSTerminal) && eTextType > 0) {
		const char* pText = nullptr;
		BGSTerminal::MenuEntry* pEntry = pTerminal->menuEntries.GetNthItem(uiIndex);
		if (eTextType == 1)
			pText = pEntry->entryText.c_str();
		else if (eTextType == 2)
			pText = pEntry->resultText.c_str();

		g_strInterface->Assign(PASS_COMMAND_ARGS, pText);
		if (IsConsoleMode()) 
			Console_Print("GetTerminalMenuItemText >> %s", pText);
	}
	return true;
}

bool Cmd_AddTerminalMenuItem_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* pTerminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pTerminal) && pTerminal && IS_TYPE(pTerminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* pEntry = BSMemory::malloc<BGSTerminal::MenuEntry>();
		if (pEntry) {
			ThisCall(0x500960, pEntry);
			pTerminal->menuEntries.Append(pEntry);
			arResult = 1;
		}
	}
	return true;
}
#endif