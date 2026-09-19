#include "GameObjects.h"
#include "CommandTable.h"

#ifdef GAME
extern bool (*Cmd_Update3D)(COMMAND_ARGS);
void __fastcall UpdateReference3D(TESObjectREFR* apReference) {
	double dResult;
	uint32_t uiOffset = 0;
	Cmd_Update3D(nullptr, nullptr, apReference, nullptr, nullptr, nullptr, &dResult, &uiOffset);
}
#endif