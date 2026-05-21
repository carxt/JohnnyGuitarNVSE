#include "RadioSkipOGGWAVPatch.hpp"
#include "GameForms.h"
#include <GameObjects.h>
#include <decoding.h>


namespace RadioSkipOGGWAVPatch {
	ULONGLONG uiLastPipRadioUpdate;
	void* hk_QueueRadioSkipUpdate()
	{
		auto* pEbp = GetParentBasePtr(_AddressOfReturnAddress(), false);
		RadioEntry* pRadio = *((decltype(&pRadio))(pEbp + 0x8));
		RadioEntry* pGlobalRadio = *((decltype(&pGlobalRadio))(0x11DD42C));
		if (pRadio == pGlobalRadio)
		{
			uiLastPipRadioUpdate = GetTickCount64() + 200; //you'd have to be running at 5 fps for this to be an issue
		}
		return CdeclCall<void*>(0x453A70);

	}

	void* __fastcall hk_QueryRadioSkipUpdatePipboy(void* sound, void* edx, int offset)
	{
		if (uiLastPipRadioUpdate > GetTickCount64())
		{
			return NULL;
		}
		return  ThisCall<void*>(0xAD8FD0, sound, offset);
	}



	void Install() {

		WriteRelCall(0x834749, (uint32_t)hk_QueueRadioSkipUpdate);
		WriteRelCall(0x8337F7, (uint32_t)hk_QueryRadioSkipUpdatePipboy);

	}

}