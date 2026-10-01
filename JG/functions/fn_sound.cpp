#include "fn_sound.h"

#include "Bethesda/BGSAddonNodeSoundHandleExtra.hpp"
#include "Bethesda/BSAudio.hpp"
#include "Bethesda/BSAudioManager.hpp"
#include "Bethesda/BSGameSound.hpp"
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/TESSound.hpp"
#include "Obsidian/FalloutAudioMedia.hpp"

#include <mutex>

SPEC_NOINLINE void __fastcall RemoveSoundExtra(NiAVObject* apObject, uint32_t auiSoundID) {
	if (!apObject->HasExtraData())
		return;

	BGSAddonNodeSoundHandleExtra* pExtra = static_cast<BGSAddonNodeSoundHandleExtra*>(apObject->GetExtraData(BGSAddonNodeSoundHandleExtra::GetTag()));
	if (pExtra && pExtra->IsExactKindOf<BGSAddonNodeSoundHandleExtra>() && pExtra->hSound == auiSoundID)
		apObject->RemoveExtraData(BGSAddonNodeSoundHandleExtra::GetTag());
}

bool Cmd_StopSoundAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	TESSound* pSoundForm = nullptr;
	TESObjectREFR* pSourceRef = nullptr;
	float fFadeOutTime = -1.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSoundForm, &pSourceRef, &fFadeOutTime) && pSoundForm && IS_TYPE(pSoundForm, TESSound) && pSourceRef) {
		BSAudioManager* pMgr = BSAudioManager::GetSingleton();

		std::scoped_lock kLock(pMgr->kProcessingCritSection);

		uint32_t uiKey;
		auto kObjIter = pMgr->kMovingObjects.GetFirstPos();
		while (kObjIter) {
			NiPointer<NiAVObject> spObject;
			pMgr->kMovingObjects.GetNext(kObjIter, uiKey, spObject);
			if (TESObjectREFR::FindReferenceFor3D(spObject) != pSourceRef)
				continue;

			BSGameSound* pSound = nullptr;
			if (!pMgr->kPlayingSounds.GetAt(uiKey, pSound))
				continue;

			if (pSound && pSound->pSourceSound == pSoundForm) {
				BSSoundHandle hSound(pSound->GetID());
				if (fFadeOutTime < 0.f)
					hSound.Stop();
				else
					hSound.FadeOutAndRelease(fFadeOutTime * 1000.0);

				RemoveSoundExtra(spObject, pSound->GetID());

				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_StopSoundLooping_Execute(COMMAND_ARGS) {
	*result = 0;
	TESSound* pSoundForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSoundForm) && pSoundForm && IS_TYPE(pSoundForm, TESSound)) {
		BSAudioManager* pMgr = BSAudioManager::GetSingleton();

		std::scoped_lock lock(pMgr->kProcessingCritSection);

		BSGameSound* pSound;
		uint32_t uiKey;
		auto kIter = pMgr->kPlayingSounds.GetFirstPos();
		while (kIter) {
			pMgr->kPlayingSounds.GetNext(kIter, uiKey, pSound);
			if (!pSound || pSound->pSourceSound != pSoundForm)
				continue;

			BSSoundHandle hSound(pSound->GetID());
			hSound.Stop();
			*result = 1;
		}
	}

	return true;
}

bool Cmd_PlaySoundFade_Execute(COMMAND_ARGS) {
	*result = 0;
	float fTime = 0;
	TESSound* apSound;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &apSound, &fTime) && apSound && IS_TYPE(apSound, TESSound)) {
		TESObjectREFR* pRef = thisObj;
		if (!pRef)
			pRef = PlayerCharacter::GetSingleton();

		NiAVObject* pRef3D = pRef->Get3DVerySimple();
		if (pRef3D) {
			constexpr uint32_t uiFlags = BSGameSound::TypeFlags::IS_3D | BSGameSound::TypeFlags::ONE_SHOT;
			BSSoundHandle hSound = BSAudio::GetSingleton()->GetSoundHandleByFormID(apSound->GetFormID(), uiFlags);
			hSound.SetPosition(pRef->GetLocationOnReference());
			hSound.SetObjectToFollow(pRef3D);
			hSound.FadeInPlay(fTime * 1000);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_PlaySoundFile_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	BOOL bForce = FALSE;
	BOOL bLoop = FALSE;
	BOOL bPlayInMainMenu = FALSE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &bForce, &bLoop, &bPlayInMainMenu) && cPath[0]) {
		const FalloutAudioMedia::Type eType = bPlayInMainMenu > 0 ? FalloutAudioMedia::Type::MAIN_MENU : FalloutAudioMedia::Type::SPECIAL;
		FalloutAudioMedia::MediaOpen(eType, cPath, 1000, bLoop, bForce, 0.f, 0);
		*result = 1;
	}
	return true;
}

bool Cmd_StopSoundFile_Execute(COMMAND_ARGS) {
	FalloutAudioMedia::MediaClose();
	*result = 1;
	return true;
}

bool Cmd_PlaySoundFromPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	BOOL bVoice = FALSE;
	BOOL bSystemSound = FALSE;
	BOOL bLoop = FALSE;
	BOOL bDontCache = FALSE;
	float fFadeInTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeInTime, &bVoice, &bSystemSound, &bLoop, &bDontCache) && cPath[0]) {
		Bitfield32 uiAudioFlags = BSGameSound::TypeFlags::IS_2D | BSGameSound::TypeFlags::ONE_SHOT;
		uiAudioFlags.Set<BSGameSound::TypeFlags::VOICE>(bVoice > 0);
		uiAudioFlags.Set<BSGameSound::TypeFlags::SYSTEM_SOUND>(bSystemSound > 0);
		uiAudioFlags.Set<BSGameSound::TypeFlags::LOOP>(bLoop > 0);
		uiAudioFlags.Set<BSGameSound::TypeFlags::DONT_CACHE>(bDontCache > 0);

		BSSoundHandle hSound = BSAudio::GetSingleton()->GetSoundHandleByFilePath(cPath, uiAudioFlags, nullptr);
		if (fFadeInTime <= 0)
			hSound.Play(false);
		else
			hSound.FadeInPlay(fFadeInTime * 1000);
		*result = 1;
	}
	return true;
}

bool Cmd_PlaySound3DFromPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	BOOL bVoice = FALSE;
	BOOL bLoop = FALSE;
	BOOL bDontCache = FALSE;
	float fFadeInTime = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeInTime, &bVoice, &bLoop, &bDontCache) && cPath[0]) {
		const TESObjectREFR* pRef = thisObj ? thisObj : PlayerCharacter::GetSingleton();

		NiAVObject* pRef3D = pRef->Get3DVerySimple();
		if (pRef3D) {
			Bitfield32 uiAudioFlags = BSGameSound::TypeFlags::IS_3D | BSGameSound::TypeFlags::ONE_SHOT;
			uiAudioFlags.Set<BSGameSound::TypeFlags::VOICE>(bVoice > 0);
			uiAudioFlags.Set<BSGameSound::TypeFlags::LOOP>(bLoop > 0);
			uiAudioFlags.Set<BSGameSound::TypeFlags::DONT_CACHE>(bDontCache > 0);

			BSSoundHandle hSound = BSAudio::GetSingleton()->GetSoundHandleByFilePath(cPath, uiAudioFlags, nullptr);
			hSound.SetPosition(pRef->GetLocationOnReference());
			hSound.SetObjectToFollow(pRef3D);
			if (fFadeInTime <= 0)
				hSound.Play(false);
			else
				hSound.FadeInPlay(fFadeInTime * 1000);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_StopSoundFromPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	float fFadeOutTime = -1.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeOutTime) && cPath[0]) {
		BSAudioManager* pMgr = BSAudioManager::GetSingleton();

		std::scoped_lock kLock(pMgr->kProcessingCritSection);

		BSGameSound* pSound = nullptr;
		uint32_t uiKey;
		auto kIter = pMgr->kPlayingSounds.GetFirstPos();
		while (kIter) {
			pMgr->kPlayingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
				BSSoundHandle hSound(pSound->GetID());
				if (fFadeOutTime <= 0)
					hSound.Stop();
				else
					hSound.FadeOutAndRelease(fFadeOutTime * 1000);
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_StopSound3DFromPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	float fFadeOutTime = -1.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &fFadeOutTime) && cPath[0]) {
		const TESObjectREFR* pRef = thisObj ? thisObj : PlayerCharacter::GetSingleton();

		BSAudioManager* pMgr = BSAudioManager::GetSingleton();

		std::scoped_lock kLock(pMgr->kProcessingCritSection);

		BSGameSound* pSound = nullptr;
		uint32_t uiKey;
		auto kIter = pMgr->kPlayingSounds.GetFirstPos();
		while (kIter) {
			pMgr->kPlayingSounds.GetNext(kIter, uiKey, pSound);
			if (pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
				NiPointer<NiAVObject> spObject;
				if (!pMgr->kMovingObjects.GetAt(pSound->GetID(), spObject))
					continue;

				if (TESObjectREFR::FindReferenceFor3D(spObject) != pRef)
					continue;

				BSSoundHandle hSound(pSound->GetID());
				if (fFadeOutTime <= 0) {
					hSound.Stop();
				}
				else {
					uint32_t uiTime = fFadeOutTime * 1000.0;
					hSound.FadeOutAndRelease(uiTime);
				}

				RemoveSoundExtra(spObject, pSound->GetID());

				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_IsSoundPlayingFromPath_Execute(COMMAND_ARGS) {
	*result = 0;
	char cPath[MAX_PATH] = {};
	TESObjectREFR* pRef = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cPath, &pRef) && cPath[0]) {
		BSAudioManager* pMgr = BSAudioManager::GetSingleton();

		std::scoped_lock kLock(pMgr->kProcessingCritSection);

		BSGameSound* pSound = nullptr;
		uint32_t uiKey;
		if (!pRef) {
			auto kIter = pMgr->kPlayingSounds.GetFirstPos();
			while (kIter) {
				pMgr->kPlayingSounds.GetNext(kIter, uiKey, pSound);
				if (pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
					*result = 1;
					return true;
				}
			}
		}
		else {
			auto kIter = pMgr->kMovingObjects.GetFirstPos();
			while (kIter) {
				NiPointer<NiAVObject> spObject;
				pMgr->kMovingObjects.GetNext(kIter, uiKey, spObject);
				if (!spObject)
					continue;

				if (TESObjectREFR::FindReferenceFor3D(spObject) != pRef)
					continue;

				if (pMgr->kPlayingSounds.GetAt(uiKey, pSound) && pSound && _stricmp(pSound->GetFileName(), cPath) == 0) {
					*result = 1;
					return true;
				}
			}
		}
	}
	return true;
}