#include "ExtraUISounds.hpp"
#include <decoding.h>
namespace ExtraUISounds {
	TESSound* questFailSound = 0;
	TESSound* questNewSound = 0;
	TESSound* questCompeteSound = 0;
	TESSound* locationDiscoverSound = 0;

	void __fastcall UIUpdateSoundHook(BSSoundHandle* sound, int dummy) {
		tList<QuestUpdateManager>* g_questUpdateManager = (tList <QuestUpdateManager>*)0x11D970C;
		if (g_questUpdateManager) {
			ListNode<QuestUpdateManager>* iter = g_questUpdateManager->Head();
			do {
				switch (iter->data->updateType) {
				case QuestAdded:
					if (questNewSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(questNewSound->GetFormID(), 0x121);
					break;
				case QuestCompleted:
					if (questCompeteSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(questCompeteSound->GetFormID(), 0x121);
					break;
				case QuestFailed:
					if (questFailSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(questFailSound->GetFormID(), 0x121);
					break;
				case LocationDiscovered:
					if (locationDiscoverSound != nullptr)
						*sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(locationDiscoverSound->GetFormID(), 0x121);
					break;
				}
				sound->Play(false);
			} while (iter = iter->next);
		}
	}

	void Install() {
		WriteRelCall(0x77A8E9, (uint32_t)UIUpdateSoundHook);
	}
}