#pragma once
DEFINE_COMMAND_PLUGIN(AddTerminalMenuItem, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemText, , 0, 3, kParamsJohnny_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemText, , 0, 4, kParamsJohnny_OneForm_TwoInts_OneString);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemNote, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemNote, , 0, 3, kParamsJohnnyOneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(GetTerminalMenuItemSubmenu, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetTerminalMenuItemSubmenu, , 0, 3, kParamsJohnnyOneForm_OneInt_OneForm);

bool Cmd_GetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal;
	int menuEntryID = 0;
	if (ExtractArgs(EXTRACT_ARGS, &terminal, &menuEntryID) && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry && entry->subMenu) *(UInt32*)result = entry->subMenu->refID;
	}
	return true;
}
bool Cmd_SetTerminalMenuItemSubmenu_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal;
	BGSTerminal* submenu;
	int menuEntryID = 0;
	if (ExtractArgs(EXTRACT_ARGS, &terminal, &menuEntryID, &submenu) && IS_TYPE(terminal, BGSTerminal) && IS_TYPE(submenu, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) entry->subMenu = submenu;
	}
	return true;
}
bool Cmd_SetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal;
	BGSNote* note;
	int menuEntryID = 0;
	if (ExtractArgs(EXTRACT_ARGS, &terminal, &menuEntryID, &note) && IS_TYPE(terminal, BGSTerminal) && IS_TYPE(note, BGSNote)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry) entry->displayNote = note;
	}
	return true;
}

bool Cmd_GetTerminalMenuItemNote_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal;
	int menuEntryID = 0;
	if (ExtractArgs(EXTRACT_ARGS, &terminal, &menuEntryID) && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (entry && entry->displayNote) *(UInt32*)result = entry->displayNote->refID;
	}
	return true;
}
bool Cmd_SetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal;
	int textID = 0, menuEntryID = 0;
	char text[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &terminal, &textID, &menuEntryID, &text) && IS_TYPE(terminal, BGSTerminal) && textID > 0) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (textID == 1) {
			entry->entryText.Set(text);
		}
		else if (textID == 2) {
			entry->resultText.Set(text);
		}
	}
	return true;
}
bool Cmd_GetTerminalMenuItemText_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal;
	int textID = 0, menuEntryID = 0;
	const char* text = NULL;
	if (ExtractArgs(EXTRACT_ARGS, &terminal, &textID, &menuEntryID) && IS_TYPE(terminal, BGSTerminal) && textID > 0) {
		BGSTerminal::MenuEntry* entry = terminal->menuEntries.GetNthItem(menuEntryID);
		if (textID == 1) {
			text = entry->entryText.CStr();
		}
		else if (textID == 2) {
			text = entry->resultText.CStr();
		}
		StrIfc->Assign(PASS_COMMAND_ARGS, text);
		if (IsConsoleMode()) Console_Print("GetTerminalMenuItemText >> %s", text);
	}
	return true;
}
bool Cmd_AddTerminalMenuItem_Execute(COMMAND_ARGS) {
	*result = 0;
	BGSTerminal* terminal;
	if (ExtractArgs(EXTRACT_ARGS, &terminal) && IS_TYPE(terminal, BGSTerminal)) {
		BGSTerminal::MenuEntry* entry = (BGSTerminal::MenuEntry*)GameHeapAlloc(sizeof(BGSTerminal::MenuEntry));
		if (entry) {
			ThisStdCall(0x500960, entry);
			terminal->menuEntries.Append(entry);
			*result = 1;
		}
	}
	return true;
}