#pragma once
DEFINE_COMMAND_PLUGIN(AddTerminalMenuItem, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemText, , false, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemText, , false, kParams_OneForm_TwoInts_OneString);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemNote, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemNote, , false, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemSubmenu, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemSubmenu, , false, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemCount, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(RemoveTerminalMenuItem, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemFlags, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemFlags, , false, kParams_OneForm_TwoInts);
DEFINE_COMMAND_ALT_PLUGIN(RefreshTerminalMenu, rtm, , false, nullptr);

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
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	uint32_t flags;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID, &flags) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			entry->entryFlags = flags;
			*result = 1;
		}
	}
	return true;
}
bool Cmd_GetTerminalMenuItemFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			*result = entry->entryFlags;
			if (IsConsoleMode()) Console_Print("GetTerminalMenuItemFlags %d >> %.f", menuEntryID, *result);
		}
	}
	return true;
}

bool Cmd_RemoveTerminalMenuItem_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			ThisCall(0x5010F0, entry);
			terminal->menuEntries.RemoveNth(menuEntryID);
			GameHeapFree(entry);
			*result = 1;
		}
	}
	return true;
}
bool Cmd_GetTerminalMenuItemCount_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		*result = terminal->menuEntries.Count();
		if (IsConsoleMode()) Console_Print("GetTerminalMenuItemCount >> %.f", *result);
	}
	return true;
}
bool Cmd_GetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry && entry->subMenu) *(uint32_t*)result = entry->subMenu->refID;
	}
	return true;
}
bool Cmd_SetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	BGSTerminal* submenu = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID, &submenu) && terminal && IS_TYPE(terminal, BGSTerminal) && submenu && IS_TYPE(submenu, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			entry->subMenu = submenu;
			*result = 1;
		}
	}
	return true;
}
bool Cmd_SetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	BGSNote* note = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID, &note) && terminal && IS_TYPE(terminal, BGSTerminal) && note && IS_TYPE(note, BGSNote)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) {
			entry->displayNote = note;
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	int menuEntryID = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &menuEntryID) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry && entry->displayNote) *(uint32_t*)result = entry->displayNote->refID;
	}
	return true;
}
bool Cmd_SetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal = nullptr;
	int textID = 0, menuEntryID = 0;
	char text[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal, &textID, &menuEntryID, &text) && terminal && IS_TYPE(terminal, BGSTerminal) && textID > 0) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (textID == 1) {
			entry->entryText.Set(text);
			*result = 1;
		}
		else if (textID == 2) {
			entry->resultText.Set(text);
			*result = 1;
		}
	}
	return true;
}
bool Cmd_GetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	*result = 0;
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
	*result = 0;
	BGSTerminal* terminal = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &terminal) && terminal && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = (BGSTerminal::MenuEntry*)GameHeapAlloc(sizeof(BGSTerminal::MenuEntry));
		if (entry) {
			ThisCall(0x500960, entry);
			terminal->menuEntries.Append(entry);
			*result = 1;
		}
	}
	return true;
}