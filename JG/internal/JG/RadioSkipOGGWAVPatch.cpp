#include "RadioSkipOGGWAVPatch.hpp"
#include "GameForms.h"
#include "GameSound.h"

namespace RadioSkipOGGWAVPatch {
	//Fix playback
	unsigned int BSWin32Audio_GetTimePassed()
	{
		auto pBSWin32Audio = BSWin32Audio::GetSingleton();
		return ThisCall<unsigned int>(0x63D040, pBSWin32Audio);

	}
	void* hk_QueryRadioSkipUpdate(BSSoundHandle* pSound, unsigned int iOffset, bool bDoRewind)
	{
		unsigned int lMsToRewind = 50; //the default value added by the game to skip
		unsigned int lRewindedOffset = iOffset - lMsToRewind;
		if (bDoRewind && ((BSWin32Audio_GetTimePassed()) <= iOffset))
		{
			return NULL;
		}
		return  ThisCall<void*>(0xAD8FD0, pSound, iOffset);
	}
	void* __fastcall hk_QueryRadioSkipUpdatePipboy(BSSoundHandle* pSound, void* _EDX, unsigned int iOffset)
	{

		return  hk_QueryRadioSkipUpdate(pSound, iOffset, true);
	}
	void* __fastcall hk_QueryRadioSkipUpdatePlaced(BSSoundHandle* pSound, void* _EDX, unsigned int iOffset)
	{
		auto* _ebp = GetParentBasePtr(_AddressOfReturnAddress(), false);
		char* lSoundPath = reinterpret_cast<char*>(_ebp - 0x17C);
		//undo seek for ogg/wav
		bool doRewind = (strstr(lSoundPath, ".ogg") != NULL) || (strstr(lSoundPath, ".wav") != NULL);
		return hk_QueryRadioSkipUpdate(pSound, iOffset, doRewind);
	}

	void* __cdecl hk_AllowOGGPlayBackFilepath(char* pPath, const char* pConstantWAV)
	{
		//Radios can actually play OGG directly... but the code only checks for WAV, although later it checks and if it doesn't find a wav, it falls back to an OGG.
		//This leads to the hacky workaround where you must specify the file path as .wav even though it's an OGG.
		auto retVal = strstr(pPath, pConstantWAV);
		if (!retVal) { retVal = strstr(pPath, ".ogg"); }
		return retVal;
	}

	void Install() 
	{

		HookUtils::WriteRelCall(0x8337F7, (uintptr_t)hk_QueryRadioSkipUpdatePipboy);
		HookUtils::WriteRelCall(0x8354CC, (uintptr_t)hk_QueryRadioSkipUpdatePlaced);
		HookUtils::WriteRelCall(0x833680, (uintptr_t)hk_AllowOGGPlayBackFilepath);

	}

}