#include "BSDirectoryEntry.hpp"

// GAME - 0xAFDBC0
// GECK - 0x8ACB70
bool BSDirectoryEntry::IsFileEntryInDirectory(BSFileEntry* apFileEntry) const {
	return apFileEntry >= pFiles && apFileEntry < &pFiles[uiFiles];
}
