#include "Hooks_Dialog.h"
#include "SafeWrite.h"
#include <cstdarg>
#include "Utilities.h"

#if RUNTIME

#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
#define kHookDialogResponse 0x0104A1B8
#elif RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525ng
#define kHookDialogResponse 0x00000000
#else
#error
#endif

static __declspec(naked) int DialogResponseHook(const char * fmt, ...)
{
	// the problem now is to define the method to specify what data to change in the dialog string.
	//	I can add % specifier, but how to I set the variables ? Or maybe, have the dialog text be a User Defined Script to call then ?
	_asm 
	{
		mov eax, 0
		retn
	}
}

void Hook_Dialog_Init(void)
{
	UInt32	enableDialogHook = 0;

	if(GetNVSEConfigOption_UInt32("Dialog", "EnableDialogHook", &enableDialogHook) && enableDialogHook)
	{
//		WriteRelJump(kHookDialogResponse, (UInt32)DialogResponseHook);
	}
}

#endif
