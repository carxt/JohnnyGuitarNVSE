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
	void* hk_QueryRadioSkipUpdate(BSSoundHandle* pSound, unsigned int offset, bool bDoRewind)
	{
		unsigned int msToRewind = 50; //the default value added by the game to skip
		unsigned int setOffset = offset - msToRewind;
		if (bDoRewind && ((BSWin32Audio_GetTimePassed()) <= setOffset))
		{
			return NULL;
		}
		return  ThisCall<void*>(0xAD8FD0, pSound, bDoRewind ? setOffset : offset);
	}
	void* __fastcall hk_QueryRadioSkipUpdatePipboy(BSSoundHandle* pSound, void* edx, unsigned int offset)
	{

		return  hk_QueryRadioSkipUpdate(pSound, offset, true);
	}
	void* __fastcall hk_QueryRadioSkipUpdatePlaced(BSSoundHandle* pSound, void* edx, unsigned int offset)
	{
		auto* _ebp = GetParentBasePtr(_AddressOfReturnAddress(), false);
		char* path = reinterpret_cast<char*>(_ebp - 0x17C);
		bool doRewind = strstr(path, ".mp3") == NULL; //the entire issue is the seek code assumes mp3
		auto toRet = hk_QueryRadioSkipUpdate(pSound, offset, doRewind);
		return toRet;
	}

	void* __cdecl hk_AllowOGGPlayBackFilepath(char* pPath, const char* pConstantWAV)
	{
		//Radios can actually play OGG directly... but the code only checks for WAV, although later it checks and if it doesn't find a wav, it falls back to an OGG.
		//This leads to the hacky workaround where you must specify the file path as .wav even though it's an OGG.
		auto toRet = strstr(pPath, pConstantWAV);
		if (!toRet) { toRet = strstr(pPath, ".ogg"); }
		return toRet;
	}

	void Install() 
	{

		WriteRelCall(0x8337F7, (uintptr_t)hk_QueryRadioSkipUpdatePipboy);
		WriteRelCall(0x8354CC, (uintptr_t)hk_QueryRadioSkipUpdatePlaced);
		WriteRelCall(0x833680, (uintptr_t)hk_AllowOGGPlayBackFilepath);

	}

}