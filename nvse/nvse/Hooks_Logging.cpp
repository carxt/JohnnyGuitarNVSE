#include "Hooks_Logging.h"
#include "SafeWrite.h"
#include <cstdarg>
#include "Utilities.h"

#if RUNTIME

static FILE * s_errorLog = NULL;
static int ErrorLogHook(const char * fmt, const char * fmt_alt, ...)
{
	va_list	args;

	if(0xFFFF < (UInt32)fmt)
	{
		va_start(args, fmt);
		vfprintf(s_errorLog, fmt, args);
	}
	else
	{
		va_start(args, fmt_alt);
		vfprintf(s_errorLog, fmt_alt, args);
	}
	fputc('\n', s_errorLog);

	va_end(args);

	return 0;
}

static FILE * s_havokErrorLog = NULL;
static int HavokErrorLogHook(int severity, const char * fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vfprintf(s_havokErrorLog, fmt, args);
	fputc('\n', s_havokErrorLog);

	va_end(args);

	return 0;
}

void Hook_Logging_Init(void)
{
	UInt32	enableGameErrorLog = 0;

	if(GetNVSEConfigOption_UInt32("Logging", "EnableGameErrorLog", &enableGameErrorLog) && enableGameErrorLog)
	{
		s_errorLog = fopen("falloutnv_error.log", "w");
		s_havokErrorLog = fopen("falloutnv_havok.log", "w");

#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
		WriteRelJump(0x005B5E40, (UInt32)ErrorLogHook);

		WriteRelCall(0x006259D3, (UInt32)HavokErrorLogHook);
		WriteRelCall(0x00625A23, (UInt32)HavokErrorLogHook);
		WriteRelCall(0x00625A63, (UInt32)HavokErrorLogHook);
		WriteRelCall(0x00625A92, (UInt32)HavokErrorLogHook);
#elif RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525ng
		WriteRelJump(0x004F32B0, (UInt32)ErrorLogHook);

		WriteRelCall(0x006259B3, (UInt32)HavokErrorLogHook);
		WriteRelCall(0x00625A03, (UInt32)HavokErrorLogHook);
		WriteRelCall(0x00625A43, (UInt32)HavokErrorLogHook);
		WriteRelCall(0x00625A72, (UInt32)HavokErrorLogHook);
#else
#error
#endif
	}
}

#endif
