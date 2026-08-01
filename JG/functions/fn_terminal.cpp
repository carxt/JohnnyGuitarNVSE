#include "fn_terminal.h"
#include <GameUI.h>

bool Cmd_RefreshTerminalMenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	ComputersMenu* g_computersMenu = *(ComputersMenu**)0x11D9334;
	if (g_computersMenu) {
		ThisCall(0x7586E0, g_computersMenu, 0);
		arResult = 1;
	}
	return true;
}

bool Cmd_SetTerminalMenuItemFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	uint32_t flags;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID, &flags) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			entry->entryFlags = flags;
			arResult = 1;
		}
	}
	return true;
}
bool Cmd_GetTerminalMenuItemFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			arResult = entry->entryFlags;
			if (IsConsoleMode()) Console_Print("GetTerminalMenuItemFlags %d >> %.f", menuEntryID, arResult);
		}
	}
	return true;
}

bool Cmd_RemoveTerminalMenuItem_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			ThisCall(0x5010F0, entry);
			terminal->menuEntries.RemoveNth(menuEntryID);
			BSMemory::free(entry);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemCount_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		arResult = terminal->menuEntries.Count();
		if (IsConsoleMode()) Console_Print("GetTerminalMenuItemCount >> %.f", arResult);
	}
	return true;
}

bool Cmd_GetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry && entry->subMenu) reinterpret_cast<uint32_t&>(arResult) = entry->subMenu->GetFormID();
	}
	return true;
}

bool Cmd_SetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	BGSTerminal* submenu = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID, &submenu) && terminal && IS_TYPE(terminal, BGSTerminal) && submenu && IS_TYPE(submenu, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			entry->subMenu = submenu;
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_SetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	BGSNote* note = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID, &note) && terminal && IS_TYPE(terminal, BGSTerminal) && note && IS_TYPE(note, BGSNote)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			entry->displayNote = note;
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry && entry->displayNote) reinterpret_cast<uint32_t&>(arResult) = entry->displayNote->GetFormID();
	}
	return true;
}

bool Cmd_SetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	int textID = 0, menuEntryID = 0;
	char text[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &textID, &menuEntryID, &text) && terminal && IS_TYPE(terminal, BGSTerminal) && textID > 0) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (textID == 1) {
			entry->entryText.Set(text);
			arResult = 1;
		}
		else if (textID == 2) {
			entry->resultText.Set(text);
			arResult = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	int textID = 0, menuEntryID = 0;
	const char* text = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &textID, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal) && textID > 0) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (textID == 1) {
			text = entry->entryText.c_str();
		}
		else if (textID == 2) {
			text = entry->resultText.c_str();
		}
		g_strInterface->Assign(PASS_COMMAND_ARGS, text);
		if (IsConsoleMode()) Console_Print("GetTerminalMenuItemText >> %s", text);
	}
	return true;
}

bool Cmd_AddTerminalMenuItem_Execute(COMMAND_ARGS) {
	arResult = 0;
	BGSTerminal* terminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = BSMemory::malloc<BGSTerminal::MenuEntry>();
		if (entry) {
			ThisCall(0x500960, entry);
			terminal->menuEntries.Append(entry);
			arResult = 1;
		}
	}
	return true;
}