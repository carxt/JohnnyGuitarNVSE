#include "Utilities.h"
#include "internal/utility.h"
#include "shared/BSMemory/BSMemory.hpp"

#if RUNTIME

char* CopyCString(const char* src) {
	uint32_t length = StrLen(src);
	if (!length) return NULL;
	char* result = BSMemory::malloc<char>(length + 1);
	StrCopy(result, src);
	return result;
}

#endif