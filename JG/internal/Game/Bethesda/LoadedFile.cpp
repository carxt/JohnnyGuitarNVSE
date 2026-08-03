#include "LoadedFile.hpp"
#include "ModelLoader.hpp"

// GAME - 0x43BAF0
LoadedFile::LoadedFile(const char* apFileName, BSFile* apFile) {
#ifdef GAME
    ThisCall(0x43BAF0, this, apFileName, apFile);
#else
    ThisCall(0x4BC350, this, apFileName, apFile);
#endif
}

// GAME - 0x43BB80
LoadedFile::~LoadedFile() {
#ifdef GAME
    ThisCall(0x43BB80, this);
#else
    ThisCall(0x4BC3C0, this);
#endif
}

// GAME - 0x44B0F0
// GECK - 0x4BB290
void LoadedFile::IncRefCount() {
#ifdef GAME
    ThisCall(0x44B0F0, this);
#else
    ThisCall(0x4BB290, this);
#endif
}

// GAME - 0x44B180
// GECK - 0x4C1740
void LoadedFile::DecRefCount() {
#ifdef GAME
    ThisCall(0x44B180, this);
#else
    ThisCall(0x4C1740, this);
#endif
}

// GAME - Inlined at 0xAC5613
BSFile* LoadedFile::GetFile() {
    bUsed = true;
    return pFile;
}
