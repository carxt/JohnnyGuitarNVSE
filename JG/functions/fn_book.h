#pragma once
DEFINE_COMMAND_PLUGIN(GetBookFlags, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetBookFlags, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetBookSkill, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetBookSkill, , 0, 2, kParams_OneForm_OneInt);

bool Cmd_GetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* book;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book) && IS_TYPE(book, TESObjectBOOK)) {
		*result = book->flags;
		if (IsConsoleMode()) Console_Print("GetBookFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_SetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 flags;
	TESObjectBOOK* book;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book, &flags) && IS_TYPE(book, TESObjectBOOK)) {
		book->flags = flags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* book;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book) && IS_TYPE(book, TESObjectBOOK)) {
		*result = (book->skillCode == 255 ? -1 : book->skillCode + 32);
		if (IsConsoleMode()) Console_Print("GetBookSkill >> %.f", *result);
	}
	return true;
}

bool Cmd_SetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* book;
	UInt32 skill;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book, &skill) && IS_TYPE(book, TESObjectBOOK)) {
		if (skill == -1) {
			book->skillCode = -1;
		}
		else if (skill < kAVCode_Barter || skill >= kAVCode_InventoryWeight) {
			return true;
		}
		else {
			book->skillCode = skill - 32;
		}
		*result = 1;
	}
	return true;
}