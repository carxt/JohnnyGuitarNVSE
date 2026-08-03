#include "GameAPI.h"
#include "Bethesda/MenuConsole.hpp"
#include "Bethesda/TLSData.hpp"

static NVSEStringVarInterface* s_StringVarInterface = NULL;

bool IsConsoleMode() {
	return TLSData::Get()->bConsoleOutput;
}

void Console_Print(const char* fmt, ...) {
	MenuConsole* pConsole = MenuConsole::GetSingleton();
	if (pConsole) {
		va_list	args;

		va_start(args, fmt);

		pConsole->PrintLine(fmt, args);

		va_end(args);
	}
}