#include "fn_book.h"
#include "GameAPI.h"
#include "decoding.h"

bool Cmd_GetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		*result = pBook->kData.ucFlags;
		if (IsConsoleMode()) 
			Console_Print("GetBookFlags >> %.f", *result);
	}
	return true;
}

bool Cmd_SetBookFlags_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t uiFlags;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook, &uiFlags) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		pBook->kData.ucFlags = uiFlags;
		*result = 1;
	}
	return true;
}

bool Cmd_GetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		*result = pBook->GetTeaches();
		if (IsConsoleMode()) 
			Console_Print("GetBookSkill >> %s", ActorValue::GetActorValueName(static_cast<ActorValue::Index>(*result)));
	}
	return true;
}

bool Cmd_SetBookSkill_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectBOOK* pBook = nullptr;
	ActorValue::Index eSkill;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook, &eSkill) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		pBook->SetTeaches(eSkill);
		*result = 1;
	}
	return true;
}