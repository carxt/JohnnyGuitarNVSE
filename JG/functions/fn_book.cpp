#include "fn_book.h"
#ifdef GAME
#include "GameAPI.h"
#include "decoding.h"

bool Cmd_GetBookFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		arResult = pBook->kData.ucFlags;
		if (IsConsoleMode()) 
			Console_Print("GetBookFlags >> %.f", arResult);
	}
	return true;
}

bool Cmd_SetBookFlags_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t uiFlags;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook, &uiFlags) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		pBook->kData.ucFlags = uiFlags;
		arResult = 1;
	}
	return true;
}

bool Cmd_GetBookSkill_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectBOOK* pBook = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		arResult = pBook->GetTeaches();
		if (IsConsoleMode()) 
			Console_Print("GetBookSkill >> %s", ActorValue::GetActorValueName(static_cast<ActorValue::Index>(arResult)));
	}
	return true;
}

bool Cmd_SetBookSkill_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectBOOK* pBook = nullptr;
	ActorValue::Index eSkill;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pBook, &eSkill) && pBook && IS_TYPE(pBook, TESObjectBOOK)) {
		pBook->SetTeaches(eSkill);
		arResult = 1;
	}
	return true;
}
#endif