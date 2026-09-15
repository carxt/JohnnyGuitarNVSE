#include "fn_book.h"
#include "Bethesda/TESObjectBOOK.hpp"
#include "JG/ScriptUtils.hpp"

bool Cmd_GetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook) && pBook && IS_ID(pBook, TESObjectBOOK)) {
		*result = pBook->kData.ucFlags;
		if (IsConsoleMode()) 
			Console_Print("GetBookFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_SetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t uiFlags = 0;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook, &uiFlags) && pBook && IS_ID(pBook, TESObjectBOOK)) {
		pBook->kData.ucFlags = uiFlags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook) && pBook && IS_ID(pBook, TESObjectBOOK)) {
		*result = pBook->GetTeaches();
		if (IsConsoleMode()) 
			Console_Print("GetBookSkill >> %.f", *result);
	}
	return true;
}

bool Cmd_SetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* pBook = nullptr;
	ActorValue::Index eActorValue = ActorValue::Index::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook, &eActorValue) && pBook && IS_ID(pBook, TESObjectBOOK) && ScriptUtils::InRange(eActorValue)) {
		pBook->SetTeaches(eActorValue);
		*result = 1;
	}
	return true;
}