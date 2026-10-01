#include "fn_mediaset.h"
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/ExtraRadius.hpp"
#include "Bethesda/Interface.hpp"
#include "Obsidian/AudioMarkerInfo.hpp"
#include "Obsidian/ExtraAudioMarker.hpp"

bool Cmd_GetAcousticSpace_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		BGSAcousticSpace* pAcousticSpace = pCell->GetAcousticSpace();
		if (pAcousticSpace)
			*reinterpret_cast<FormID*>(result) = pAcousticSpace->GetFormID();

		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetAcousticSpace  >> 0x%lx", *reinterpret_cast<FormID*>(result));
	}
	return true;
}

bool Cmd_SetAcousticSpace_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	BGSAcousticSpace* pAcousticSpace = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, pAcousticSpace) && pCell)
	{
		if (!IS_TYPE(pCell, TESObjectCELL)) [[unlikely]] {
			if (Script::GetConsoleOuput())
				Interface::PrintLine("SetAcousticSpace >> Passed an invalid cell");
			return true;
		}

		if (pAcousticSpace && !IS_TYPE(pAcousticSpace, BGSAcousticSpace)) [[unlikely]] {
			if (Script::GetConsoleOuput())
				Interface::PrintLine("SetAcousticSpace >> Passed an invalid acoustic space");
			return true;
		}
		pCell->SetAcousticSpace(pAcousticSpace);
	}
	return true;
}


SPEC_NOINLINE bool Cmd_AudioMarkerGetCurrent_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (PlayerCharacter::GetSingleton() && PlayerCharacter::GetSingleton()->pCurrMusicMarker) {
		if (TESObjectREFR* pMarkerRef = PlayerCharacter::GetSingleton()->pCurrMusicMarker->pReference)
			*reinterpret_cast<FormID*>(result) = pMarkerRef->GetFormID();
	}
	return true;
}


bool Cmd_AudioMarkerGetCurrent_Execute(COMMAND_ARGS) {
	return Cmd_AudioMarkerGetCurrent_Eval(thisObj, nullptr, nullptr, result);
}


SPEC_NOINLINE bool Cmd_AudioMarkerGetController_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj) {
		ExtraAudioMarker* pExtraMarker = thisObj->GetExtra()->GetExtraData<ExtraAudioMarker>();
		if (pExtraMarker && pExtraMarker->pData) {
			uintptr_t uiCtrlFormID = pExtraMarker->pData->uiMediaLocationController;
			TESForm* pFoundForm = TESForm::GetFormByNumericID(uiCtrlFormID);
			if (pFoundForm->GetFormType() == FORM_TYPE::MediaLocationController)
				*reinterpret_cast<FormID*>(result) = pFoundForm->GetFormID();
		}
	}
	return true;
}

bool Cmd_AudioMarkerGetController_Execute(COMMAND_ARGS) {
	Cmd_AudioMarkerGetController_Eval(thisObj, nullptr, nullptr, result);
	if (thisObj && Script::GetConsoleOuput()) {
		if (*result)
			Interface::PrintLine("AudioMarkerGetController >> 0x%lx", *reinterpret_cast<FormID*>(result));
		else
			Interface::PrintLine("Calling reference is not an AudioMarker");
	}
	return true;
}


bool Cmd_AudioMarkerSetController_Execute(COMMAND_ARGS) {
	MediaLocationController* locationController;
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &locationController) && locationController && IS_TYPE(locationController, MediaLocationController)) {
		ExtraAudioMarker* audioMrkr = thisObj->GetExtra()->GetExtraData<ExtraAudioMarker>();
		if (audioMrkr && audioMrkr->pData) {
			audioMrkr->pData->uiMediaLocationController = locationController->GetFormID();
			Interface::PrintLine("AudioMarkerSetController >> 0x%lx, %s", locationController->GetFormID(), locationController->GetFormEditorID());

		}
		else if (Script::GetConsoleOuput()) {
			Interface::PrintLine("Calling reference is not an AudioMarker");
		}
	}
	return true;
}


bool Cmd_AudioMarkerSetProperty_Execute(COMMAND_ARGS) {
	DWORD type;
	float newVal;
	enum kAMType {
		kRadius,
		kLayer2,
		kLayer3,
		kFlags
	};
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &type, &newVal)) {
		ExtraAudioMarker* audioMrkr = thisObj->GetExtra()->GetExtraData<ExtraAudioMarker>();
		ExtraRadius* rad = thisObj->GetExtra()->GetExtraData<ExtraRadius>();
		if (audioMrkr && audioMrkr->pData) {
			switch (type) {
			case kRadius:
				if (rad) {
					rad->fRadius = newVal;
				}
				break;
			case kLayer2:
				audioMrkr->pData->fSecondLayerPercent = newVal;
				break;
			case kLayer3:
				audioMrkr->pData->fThirdLayerPercent = newVal;
				break;
			case kFlags:
				audioMrkr->pData->bUseController = bool(newVal);
				break;

			}
			Interface::PrintLine("AudioMarkerSetProperty >> %s, %d, %.2f", thisObj->GetFormEditorID(), type, newVal);
		}
		else if (Script::GetConsoleOuput()) {
			Interface::PrintLine("Calling reference is not an AudioMarker");
		}
	}
	return true;
}

bool Cmd_AudioMarkerGetProperty_Execute(COMMAND_ARGS) {
	DWORD type;
	enum kAMType {
		kRadius,
		kLayer2,
		kLayer3,
		kFlags
	};
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &type)) {
		ExtraAudioMarker* audioMrkr = thisObj->GetExtra()->GetExtraData<ExtraAudioMarker>();
		ExtraRadius* rad = thisObj->GetExtra()->GetExtraData<ExtraRadius>();
		if (audioMrkr && audioMrkr->pData) {
			switch (type) {
			case kRadius:
				if (rad) {
					*result = rad->fRadius;
				}
				break;
			case kLayer2:
				*result = audioMrkr->pData->fSecondLayerPercent;
				break;
			case kLayer3:
				*result = audioMrkr->pData->fThirdLayerPercent;
				break;
			case kFlags:
				*result = audioMrkr->pData->bUseController;
				break;

			}

			Interface::PrintLine("AudioMarkerGetProperty >> %s, %d, %.2f", thisObj->GetFormEditorID(), type, *result);
		}
		else if (Script::GetConsoleOuput()) {
			Interface::PrintLine("Calling reference is not an AudioMarker");
		}
	}
	return true;
}

bool Cmd_GetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaSet* pMediaSet = nullptr;
	int32_t iTrait = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iTrait) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		switch (iTrait) {
		case 0:
			*result = pMediaSet->GetType();
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			*result = pMediaSet->kLayers[iTrait - 1].fAttenuation;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			*result = pMediaSet->kLayers[iTrait - 7].fPercent;
			break;
		case 13:
			*result = pMediaSet->ucEnableFlags;
			break;
		case 14:
			*result = pMediaSet->fWaitTime;
			break;
		case 15:
			*result = pMediaSet->fLoopFadeOut;
			break;
		case 16:
			*result = pMediaSet->fRecoveryTime;
			break;
		case 17:
			*result = pMediaSet->fNightTimeMax;
			break;
		}

		if (Script::GetConsoleOuput())
			Interface::PrintLine("GetMediaSetTraitNumeric %d >> %.2f", iTrait, *result);
	}
	return true;
}

bool Cmd_SetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaSet* pMediaSet = nullptr;
	int32_t iTrait = -1;
	float fValue = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iTrait, &fValue) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		*result = 1;
		switch (iTrait) {
		case 0:
			pMediaSet->SetType(MediaSet::Type(fValue));
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			pMediaSet->kLayers[iTrait - 1].fAttenuation = fValue;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			pMediaSet->kLayers[iTrait - 7].fPercent = fValue;
			break;
		case 13:
			pMediaSet->ucEnableFlags = fValue;
			break;
		case 14:
			pMediaSet->fWaitTime = fValue;
			break;
		case 15:
			pMediaSet->fLoopFadeOut = fValue;
			break;
		case 16:
			pMediaSet->fRecoveryTime = fValue;
			break;
		case 17:
			pMediaSet->fNightTimeMax = fValue;
			break;
		default:
			*result = 0;
			break;
		}
	}
	return true;
}

bool Cmd_GetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaSet* pMediaSet = nullptr;
	int32_t iSoundType = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iSoundType) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		TESSound* pSound = nullptr;
		switch (iSoundType) {
		case 0:
			pSound = pMediaSet->GetSoundA();
			break;
		case 1:
			pSound = pMediaSet->GetSoundB();
			break;
		}

		if (pSound)
			*reinterpret_cast<FormID*>(result) = pSound->GetFormID();
	}
	return true;
}

bool Cmd_SetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaSet* pMediaSet = nullptr;
	TESSound* pSound = nullptr;
	int32_t iSoundType = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iSoundType, &pSound) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (pSound && !IS_TYPE(pSound, TESSound))
			return true;

		switch (iSoundType) {
		case 0:
			pMediaSet->SetSoundA(pSound);
			*result = 1;
			break;
		case 1:
			pMediaSet->SetSoundB(pSound);
			*result = 1;
			break;
		}
	}
	return true;
}

bool Cmd_GetMediaSetTraitString_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaSet* pMediaSet = nullptr;
	int32_t iLayer = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iLayer) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (iLayer >= 0 && iLayer <= 5) {
			const char* pName = pMediaSet->kLayers[iLayer].strName.c_str();
			g_strInterface->Assign(PASS_COMMAND_ARGS, pName);
			if (Script::GetConsoleOuput())
				Interface::PrintLine("GetMediaSetTraitString %d >> %s", iLayer, pName);
		}
	}
	return true;
}

bool Cmd_SetMediaSetTraitString_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaSet* pMediaSet = nullptr;
	int32_t iLayer = -1;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iLayer, &cName) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (iLayer >= 0 && iLayer <= 5) {
			pMediaSet->kLayers[iLayer].strName.Set(cName);
			*result = 1;
		}
	}
	return true;
}