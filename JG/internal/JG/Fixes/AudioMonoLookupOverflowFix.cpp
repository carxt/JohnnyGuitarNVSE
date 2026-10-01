#include "AudioMonoLookupOverflowFix.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace AudioMonoLookupOverflowFix {

	char* __cdecl strstrHook(char* apBuffer, const char* apSuffix) {
		if (!strstr(apBuffer, apSuffix)) {
			char* pDot = strrchr(apBuffer, '.');
			if (pDot) {
				char cTempBuf[MAX_PATH] = {};
				strcpy_s(cTempBuf, MAX_PATH, pDot + 1);
				*pDot = '\0';
				strcat_s(apBuffer, MAX_PATH, apSuffix);
				strcat_s(apBuffer, MAX_PATH, cTempBuf);
			}
		}
		return apBuffer;
	}

	void Install() {
		HookUtils::WriteRelCall(0x83509D, strstrHook);
	}

}
