#include "nvse/GameUI.h"
#include "GameObjects.h"
#include <internal/Game/Bethesda/Conversation.hpp>

UInt8* g_MenuVisibilityArray = (UInt8*)0x011F308F;
NiTArray <TileMenu*>* g_TileMenuArray = (NiTArray <TileMenu*> *)0x011F3508;

#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
static const UInt32 s_RaceSexMenu__UpdatePlayerHead = 0x007B25A0;	// End of RaceSexMenu::Func003.case0, call containing QueuedHead::Init (3rd before jmp)
static UInt8* g_bUpdatePlayerModel = (UInt8*)0x011C5CB4;	// this is set to true when player confirms change of race in RaceSexMenu -
																	// IF requires change of skeleton - and back to false when model updated
const _TempMenuByType TempMenuByType = (_TempMenuByType)0x00707990;	// Called from called from call RaceSexMenu::Init
#elif EDITOR
#else
#error
#endif

InterfaceManager* InterfaceManager::GetSingleton(void) {
	return *(InterfaceManager**)0x011D8A80;
}

bool InterfaceManager::IsMenuVisible(UInt32 menuType) {
	if ((menuType >= kMenuType_Min) && (menuType <= kMenuType_Max))
		return g_MenuVisibilityArray[menuType] != 0;

	return false;
}

Menu* InterfaceManager::GetMenuByType(UInt32 menuType) {
	if ((menuType >= kMenuType_Min) && (menuType <= kMenuType_Max)) {
		TileMenu* tileMenu = g_TileMenuArray->Get(menuType - kMenuType_Min);
		if (tileMenu)
			return tileMenu->menu;
	}

	return NULL;
}

Menu* InterfaceManager::TempMenuByType(UInt32 menuType) {
	if ((menuType >= kMenuType_Min) && (menuType <= kMenuType_Max)) {
		return ::TempMenuByType(menuType);
	}
	return NULL;
}


void RaceSexMenu::UpdatePlayerHead(void) {
	ThisCall(s_RaceSexMenu__UpdatePlayerHead, this);
}
// reimplementation by lStewieAl
bool noHolotapeStopSound = false;
void MapMenu::PlayHolotape(BGSNote* note, bool playStartStopSound)
{
	if (isHolotapeVoicePlaying)
	{
		StopHolotape();
	}
	if (note->type == BGSNote::kSound)
	{
		BSSoundHandle sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(note->voice->refID, BSAudioManager::kAudioFlags_2D | BSAudioManager::kAudioFlags_100);

		holotapeDialogues.Append(&sound);
		isHolotapeVoicePlaying = true;
	}
	else if (note->type == BGSNote::kVoice)
	{
		auto character = BSNew<Character>();
		ThisCall(0x8D1F40, character, false);
		character->flags |= TESForm::kFormFlags_DontSaveForm;
		ThisCall(0x575690, character, note->speaker);

		auto pConversation = BSNew<Conversation>();
		ThisCall(0x83B850, pConversation, character, PlayerCharacter::GetSingleton(), note->voice);

		// use the audio flags from the original function to be compatible with JIP's VoiceModulation hook
		UInt32 audioFlags = *(UInt32*)0x7974CA;

		pConversation->FirstItem();
		if (auto currentItem = pConversation->GetCurrentItem())
		{
			if (currentItem->FirstResponse())
			{
				isHolotapeVoicePlaying = true;
				do
				{
					// append subtitle
					currentItem = pConversation->GetCurrentItem();
					auto currentResponse = currentItem->GetCurrentItem();
					if (!currentResponse) break;

					auto voiceLineStr = &currentResponse->strResponseText;
					ThisCall(0x7A1AC0, &holotapeSubtitles, voiceLineStr);

					auto topicInfo = currentItem->pTopicInfo;
					ThisCall(0x61F170, topicInfo, 0, character);

					// append sound
					BSSoundHandle toPlay = BSWin32Audio::GetSingleton()->GetSoundHandleByFilePath(currentResponse->strVoiceFilePath.c_str(), audioFlags, nullptr);
					toPlay.SetVolume(0.9f);
					holotapeDialogues.Append(&toPlay);

					ThisCall(0x61F170, topicInfo, 1, character);
				} while (currentItem->NextResponse());
			}
		}

		delete pConversation;
		character->Destroy(true);
	}

	if (isHolotapeVoicePlaying)
	{
		if (playStartStopSound)
		{
			BSSoundHandle sound = BSWin32Audio::GetSingleton()->GetSoundHandleByEditorName("UIPipBoyHolotapeStart", BSAudioManager::kAudioFlags_100 | BSAudioManager::kAudioFlags_SystemSound | BSAudioManager::kAudioFlags_2D);
			sound.SetPosition(*PlayerCharacter::GetSingleton()->GetPos());
			sound.Play(false);
		}
		else
		{
			noHolotapeStopSound = true;
		}
		*(UInt8*)0x11DCFA4 = true;
		ThisCall(0xAD85A0, BSWin32Audio::GetSingleton()); // FadeInDialogueSound
	}
}

void MapMenu::StopHolotape()
{

	if (currentHolotapeDialogueSound && currentHolotapeDialogueSound->data.IsPlaying())
	{
		currentHolotapeDialogueSound->data.Stop();
	}
	holotapeDialogues.FreeAll();
	ThisCall(0x7A1C30, &holotapeSubtitles, 1);
	currentHolotapeDialogueSound = nullptr;
	holotapeTotalTime = 0.0f;
	holotapePlayStartTime = 0;
	isHolotapeVoicePlaying = 0;
	if (!noHolotapeStopSound)
	{
		BSSoundHandle handle = BSWin32Audio::GetSingleton()->GetSoundHandleByEditorName("UIPipBoyHolotapeStop", BSAudioManager::kAudioFlags_100 | BSAudioManager::kAudioFlags_SystemSound | BSAudioManager::kAudioFlags_2D);
		handle.SetPosition(*PlayerCharacter::GetSingleton()->GetPos());
		handle.Play(false);
	}
	noHolotapeStopSound = false;
	ThisCall(0xAD8650, BSWin32Audio::GetSingleton()); // FadeOutDialogueSound
	*(UInt8*)0x11DCFA4 = false;
	ThisCall(0x775670, HUDMainMenu::GetSingleton()); // ClearSubtitlesString
}
