#include "BSArchive.hpp"

// GAME - 0xAFDC00
// GECK - 0x8ACBB0
bool BSArchive::IsFileEntryInArchive(BSFileEntry* apFileEntry) const {
#ifdef GAME
	return ThisCall<bool>(0xAFDC00, this, apFileEntry);
#else
	return ThisCall<bool>(0x8ACBB0, this, apFileEntry);
#endif
}
