#include "TESSoundFile.hpp"

// GAME - 0x408DA0
const char* TESSoundFile::GetSoundFile() const {
#ifdef GAME
    return ThisCall<const char*>(0x408DA0, this);
#else
    return strPath.c_str();
#endif
}

// GAME - 0x48CEE0
uint32_t TESSoundFile::GetSoundFileLength() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x48CEE0, this);
#else
    return strPath.GetLength();
#endif
}
