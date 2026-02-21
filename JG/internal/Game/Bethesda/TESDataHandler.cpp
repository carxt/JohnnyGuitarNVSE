#include "TESDataHandler.hpp"

TESDataHandler* TESDataHandler::GetSingleton() {
#ifdef GAME
    return *reinterpret_cast<TESDataHandler**>(0x11C3F2C);
#else
	return *reinterpret_cast<TESDataHandler**>(0xED3B0C);
#endif
}

// GAME - 0x45DFC0
BSSimpleList<TESFile*>* TESDataHandler::GetFileList() {
	return &kFiles;
}

// GAME - 0x4603B0
// GECK - 0x4DA6C0
bool TESDataHandler::AddFormToDataHandler(TESForm* apForm) {
#ifdef GAME
	return ThisCall<bool>(0x4603B0, this, apForm);
#else
	return ThisCall<bool>(0x4DA6C0, this, apForm);
#endif
}
