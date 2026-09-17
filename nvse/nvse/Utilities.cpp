#include "Utilities.h"
#include <shared/BSMemory/BSMemory.hpp>

#if RUNTIME

char* CopyCString(const char* src) {
	uint32_t length = strlen(src);
	if (!length) return NULL;
	char* result = BSMemory::malloc<char>(length + 1);
	strcpy_s(result, length + 1, src);
	return result;
}

#endif