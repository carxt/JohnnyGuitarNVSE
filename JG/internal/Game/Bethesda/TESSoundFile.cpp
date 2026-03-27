#include "TESSoundFile.hpp"

// GAME - 0x408DA0
const char* TESSoundFile::GetSoundFile() const {
    return strPath.c_str();
}

// GAME - 0x48CEE0
uint32_t TESSoundFile::GetSoundFileLength() const {
    return strPath.GetLength();
}
