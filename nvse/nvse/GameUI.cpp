#include "nvse/GameUI.h"
#include "GameObjects.h"
#include <internal/Game/Bethesda/Conversation.hpp>

uint8_t* g_MenuVisibilityArray = (uint8_t*)0x011F308F;
NiTPrimitiveArray<Tile*>* g_TileMenuArray = (NiTPrimitiveArray<Tile*> *)0x011F3508;

#if 1
static const uint32_t s_RaceSexMenu__UpdatePlayerHead = 0x007B25A0;	// End of RaceSexMenu::Func003.case0, call containing QueuedHead::Init (3rd before jmp)
static uint8_t* g_bUpdatePlayerModel = (uint8_t*)0x011C5CB4;	// this is set to true when player confirms change of race in RaceSexMenu -
																	// IF requires change of skeleton - and back to false when model updated
const _TempMenuByType TempMenuByType = (_TempMenuByType)0x00707990;	// Called from called from call RaceSexMenu::Init
#elif EDITOR
#else
#error
#endif

InterfaceManager* InterfaceManager::GetSingleton(void) {
	return *(InterfaceManager**)0x011D8A80;
}

bool InterfaceManager::IsMenuVisible(uint32_t menuType) {
	if ((menuType >= kMenuType_Min) && (menuType <= kMenuType_Max))
		return g_MenuVisibilityArray[menuType] != 0;

	return false;
}

Menu* InterfaceManager::GetMenuByType(uint32_t menuType) {
	return CdeclCall<Menu*>(0xA09030, menuType);
}

Menu* InterfaceManager::TempMenuByType(uint32_t menuType) {
	if ((menuType >= kMenuType_Min) && (menuType <= kMenuType_Max)) {
		return ::TempMenuByType(menuType);
	}
	return NULL;
}

// From JIP
__declspec(naked) uint32_t InterfaceManager::GetTopVisibleMenuID()
{
	__asm
	{
		cmp		byte ptr [ecx+0xC], 2
		jb		retn0
		mov		eax, [ecx+0xD0]
		add		ecx, 0x114
		test	eax, eax
		jz		stackIter
		mov		eax, [eax+0x20]
		retn
		ALIGN 16
	stackIter:
		add		ecx, 4
		cmp		[ecx], 0
		jnz		stackIter
		mov		eax, [ecx-4]
		cmp		eax, 1
		jnz		done
		mov		ecx, 0x11F3479
		mov		eax, 0x3EA
		cmp		[ecx], 0
		jnz		done
		mov		al, 0xFF
		cmp		[ecx+0x15], 0
		jnz		done
		mov		al, 0xEB
		cmp		[ecx+1], 0
		jnz		done
		mov		eax, 0x40B
		cmp		[ecx+0x21], 0
		jnz		done
		mov		al, 0x25
		cmp		[ecx+0x3B], 0
		jnz		done
	retn0:
		xor		eax, eax
	done:
		retn
	}
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
			sound.SetPosition(PlayerCharacter::GetSingleton()->GetPos());
			sound.Play(false);
		}
		else
		{
			noHolotapeStopSound = true;
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
	if (!noHolotapeStopSound)
	{
		BSSoundHandle handle = BSWin32Audio::GetSingleton()->GetSoundHandleByEditorName("UIPipBoyHolotapeStop", BSAudioManager::kAudioFlags_100 | BSAudioManager::kAudioFlags_SystemSound | BSAudioManager::kAudioFlags_2D);
		handle.SetPosition(PlayerCharacter::GetSingleton()->GetPos());
		handle.Play(false);
	}
	noHolotapeStopSound = false;
	ThisCall(0xAD8650, BSWin32Audio::GetSingleton()); // FadeOutDialogueSound
	*(uint8_t*)0x11DCFA4 = false;
	ThisCall(0x775670, HUDMainMenu::GetSingleton()); // ClearSubtitlesString
}
