#pragma once
DEFINE_COMMAND_PLUGIN(GetBookFlags, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetBookFlags, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetBookSkill, , false, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetBookSkill, , false, kParams_OneForm_OneInt);

bool Cmd_GetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* book = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book) && book && IS_TYPE(book, TESObjectBOOK)) {
		*result = book->flags;
		if (IsConsoleMode()) Console_Print("GetBookFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_SetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t flags;
	TESObjectBOOK* book = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book, &flags) && book && IS_TYPE(book, TESObjectBOOK)) {
		book->flags = flags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* book = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book) && book && IS_TYPE(book, TESObjectBOOK)) {
		*result = (book->skillCode == 255 ? -1 : book->skillCode + 32);
		if (IsConsoleMode()) Console_Print("GetBookSkill >> %.f", *result);
	}
	return true;
}

bool Cmd_SetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* book = nullptr;
	uint32_t skill;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &book, &skill) && book && IS_TYPE(book, TESObjectBOOK)) {
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