#include "BGSSaveLoadManager.hpp"

// GAME - 0x11DE134
BGSSaveLoadManager* BGSSaveLoadManager::GetSingleton() {
	return *reinterpret_cast<BGSSaveLoadManager**>(0x11DE134);
}

// GAME - 0x851110
uint8_t BGSSaveLoadManager::GetMinorVersion() const {
	return ThisCall<uint8_t>(0x851110, this);
}

// GAME - 0x84FEC0
void BGSSaveLoadManager::GetFullFileName(const char* apFilename, char* apFullPath) {
	ThisCall(0x84FEC0, this, apFilename, apFullPath);
}

// GAME - 0x84FF90
void BGSSaveLoadManager::GetFullPath(const char* apFilename, char* apFullPath, bool abTemp) {
	ThisCall(0x84FF90, this, apFilename, apFullPath, abTemp);
}

// GAME - 0x84FF30
void BGSSaveLoadManager::GetSaveDirectoryPath(char* apPath) {
	ThisCall(0x84FF30, this, apPath); 
}