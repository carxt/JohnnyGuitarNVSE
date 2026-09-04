#include "nvse/GameUI.h"
#include "GameObjects.h"
#ifdef GAME
#include <internal/Game/Bethesda/Conversation.hpp>

uint8_t* g_MenuVisibilityArray = (uint8_t*)0x011F308F;
NiTPrimitiveArray<Tile*>* g_TileMenuArray = (NiTPrimitiveArray<Tile*> *)0x011F3508;

InterfaceManager* InterfaceManager::GetSingleton(void) {
	return *(InterfaceManager**)0x011D8A80;
}

Menu* InterfaceManager::GetMenuByType(uint32_t menuType) {
	return CdeclCall<Menu*>(0xA09030, menuType);
}

void RaceSexMenu::UpdatePlayerHead(void) {
	ThisCall(0x7B25A0, this);
}
// reimplementation by lStewieAl
bool bNoHolotapeStopSound = false;
void MapMenu::PlayHolotape(BGSNote* note, bool playStartStopSound)
{
	if (isHolotapeVoicePlaying)
	{
		StopHolotape();
	}
	if (note->type == BGSNote::kSound)
	{
		BSSoundHandle sound = BSWin32Audio::GetSingleton()->GetSoundHandleByFormID(note->voice->GetFormID(), BSAudioManager::kAudioFlags_2D | BSAudioManager::kAudioFlags_100);

		holotapeDialogues.Append(&sound);
		isHolotapeVoicePlaying = true;
	}
	else if (note->type == BGSNote::kVoice)
	{
		auto character = BSMemory::create<Character, 0x8D1F40>(false);
		character->SetTemporary();
		ThisCall(0x575690, character, note->speaker);

		auto pConversation = BSMemory::create<Conversation, 0x83B850>(character, PlayerCharacter::GetSingleton(), note->voice);

		// use the audio flags from the original function to be compatible with JIP's VoiceModulation hook
		uint32_t audioFlags = *(uint32_t*)0x7974CA;

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
		delete character;
	}

	if (isHolotapeVoicePlaying)
	{
		if (playStartStopSound)
		{
			BSSoundHandle sound = BSWin32Audio::GetSingleton()->GetSoundHandleByEditorName("UIPipBoyHolotapeStart", BSAudioManager::kAudioFlags_100 | BSAudioManager::kAudioFlags_SystemSound | BSAudioManager::kAudioFlags_2D);
			sound.SetPosition(PlayerCharacter::GetSingleton()->GetLocationOnReference());
			sound.Play(false);
		}
		else
		{
			bNoHolotapeStopSound = true;
		}
		*(uint8_t*)0x11DCFA4 = true;
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
	if (!bNoHolotapeStopSound)
	{
		BSSoundHandle handle = BSWin32Audio::GetSingleton()->GetSoundHandleByEditorName("UIPipBoyHolotapeStop", BSAudioManager::kAudioFlags_100 | BSAudioManager::kAudioFlags_SystemSound | BSAudioManager::kAudioFlags_2D);
		handle.SetPosition(PlayerCharacter::GetSingleton()->GetLocationOnReference());
		handle.Play(false);
	}
	bNoHolotapeStopSound = false;
	ThisCall(0xAD8650, BSWin32Audio::GetSingleton()); // FadeOutDialogueSound
	*(uint8_t*)0x11DCFA4 = false;
	ThisCall(0x775670, HUDMainMenu::GetSingleton()); // ClearSubtitlesString
}
#endif