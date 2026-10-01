#include "nvse/GameUI.h"
#include "Bethesda/BSAudio.hpp"
#include "Bethesda/BSGameSound.hpp"
#include "Bethesda/Conversation.hpp"
#include "Bethesda/PlayerCharacter.hpp"

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
	if (note->GetNoteType() == BGSNote::Type::SOUND)
	{
		BSSoundHandle sound = BSAudio::GetSingleton()->GetSoundHandleByFormID(note->GetNoteSound()->GetFormID(), BSGameSound::TypeFlags::IS_2D | BSGameSound::TypeFlags::ONE_SHOT);

		holotapeDialogues.AddTail(sound);
		isHolotapeVoicePlaying = true;
	}
	else if (note->GetNoteType() == BGSNote::Type::VOICE)
	{
		auto character = BSMemory::create<Character, 0x8D1F40>(false);
		character->SetTemporary();
		ThisCall(0x575690, character, note->GetNoteSpeaker());

		auto pConversation = BSMemory::create<Conversation, 0x83B850>(character, PlayerCharacter::GetSingleton(), note->GetNoteSound());

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
					BSSoundHandle toPlay = BSAudio::GetSingleton()->GetSoundHandleByFilePath(currentResponse->strVoiceFilePath.c_str(), audioFlags, nullptr);
					toPlay.SetVolume(0.9f);
					holotapeDialogues.AddTail(toPlay);

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
			BSSoundHandle sound = BSAudio::GetSingleton()->GetSoundHandleByEditorID("UIPipBoyHolotapeStart", BSGameSound::TypeFlags::IS_2D | BSGameSound::TypeFlags::ONE_SHOT | BSGameSound::TypeFlags::SYSTEM_SOUND);
			sound.SetPosition(PlayerCharacter::GetSingleton()->GetLocationOnReference());
			sound.Play(false);
		}
		else
		{
			bNoHolotapeStopSound = true;
		}
		*(uint8_t*)0x11DCFA4 = true;
		BSAudio::GetSingleton()->EnterDialogue();
	}
}

void MapMenu::StopHolotape()
{

	if (currentHolotapeDialogueSound && currentHolotapeDialogueSound->GetItem().IsPlaying())
	{
		currentHolotapeDialogueSound->GetItem().Stop();
	}
	holotapeDialogues.RemoveAll();
	ThisCall(0x7A1C30, &holotapeSubtitles, 1);
	currentHolotapeDialogueSound = nullptr;
	holotapeTotalTime = 0.0f;
	holotapePlayStartTime = 0;
	isHolotapeVoicePlaying = 0;
	if (!bNoHolotapeStopSound)
	{
		BSSoundHandle handle = BSAudio::GetSingleton()->GetSoundHandleByEditorID("UIPipBoyHolotapeStop", BSGameSound::TypeFlags::IS_2D | BSGameSound::TypeFlags::ONE_SHOT | BSGameSound::TypeFlags::SYSTEM_SOUND);
		handle.SetPosition(PlayerCharacter::GetSingleton()->GetLocationOnReference());
		handle.Play(false);
	}
	bNoHolotapeStopSound = false;
	BSAudio::GetSingleton()->ExitDialogue();
	*(uint8_t*)0x11DCFA4 = false;
	ThisCall(0x775670, HUDMainMenu::GetSingleton()); // ClearSubtitlesString
}