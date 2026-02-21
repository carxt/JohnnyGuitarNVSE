#pragma once

namespace EDIDRestoration {
	extern SRWLOCK kEDIDMapLock;

	void InitHooks();
	void PrintErrors();
}