#include "fn_mediaset.h"
#include <GameExtraData.h>
#include <GameObjects.h>
#include "decoding.h"

bool Cmd_GetAcousticSpace_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL))
	{
		ExtraCellAcousticSpace* pXAcousticSpace = pCell->extraDataList.GetExtraData<ExtraCellAcousticSpace>();
		if (pXAcousticSpace && pXAcousticSpace->pSpace)
		{
			*(DWORD*)result = pXAcousticSpace->pSpace->GetFormID();
		}
		if (IsConsoleMode())
		{
			Console_Print("GetAcousticSpace  >> 0x%lx", *(DWORD*)result);
		}
	}
	return true;
}

bool Cmd_SetAcousticSpace_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	BGSAcousticSpace* pAcousticSpace = nullptr;
	uintptr_t ExtraCellAcousticSpace_Update = 0x041C090;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, pAcousticSpace) && pCell)
	{
		if (!IS_TYPE(pCell, TESObjectCELL)) [[unlikely]]
		{
			if (IsConsoleMode())
			{
				Console_Print("SetAcousticSpace >> Passed an invalid cell");
			}
			return true;
		}

		if (pAcousticSpace && !IS_TYPE(pAcousticSpace, BGSAcousticSpace)) [[unlikely]]
		{
			if (IsConsoleMode())
			{
				Console_Print("SetAcousticSpace >> Passed an invalid acoustic space");
			}
			return true;
		}
		ThisCall(ExtraCellAcousticSpace_Update, &pCell->extraDataList, pAcousticSpace);
	}
	return true;
}


SPEC_NOINLINE bool Cmd_AudioMarkerGetCurrent_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (PlayerCharacter::GetSingleton() && PlayerCharacter::GetSingleton()->currMusicMarker) {
		if (TESObjectREFR* pMarkerRef = PlayerCharacter::GetSingleton()->currMusicMarker->pReference)
			*reinterpret_cast<uint32_t*>(result) = pMarkerRef->GetFormID();
	}
	return true;
}


bool Cmd_AudioMarkerGetCurrent_Execute(COMMAND_ARGS) {
	return Cmd_AudioMarkerGetCurrent_Eval(thisObj, nullptr, nullptr, result);
}


SPEC_NOINLINE bool Cmd_AudioMarkerGetController_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (thisObj) {
		ExtraAudioMarker* pExtraMarker = thisObj->GetExtraData<ExtraAudioMarker>();
		if (pExtraMarker && pExtraMarker->pData) {
			uintptr_t uiCtrlFormID = pExtraMarker->pData->uiMediaLocationController;
			TESForm* pFoundForm = TESForm::GetFormByNumericID(uiCtrlFormID);
			if (pFoundForm->GetFormType() == FORM_TYPE::MediaLocationController)
				*reinterpret_cast<uint32_t*>(result) = pFoundForm->GetFormID();
		}
	}
	return true;
}

bool Cmd_AudioMarkerGetController_Execute(COMMAND_ARGS) {
	Cmd_AudioMarkerGetController_Eval(thisObj, nullptr, nullptr, result);
	if (thisObj && IsConsoleMode()) {
		if (*result)
			Console_Print("AudioMarkerGetController >> 0x%lx", *reinterpret_cast<uint32_t*>(result));
		else
			Console_Print("Calling reference is not an AudioMarker");
	}
	return true;
}


bool Cmd_AudioMarkerSetController_Execute(COMMAND_ARGS) {
	MediaLocationController* locationController;
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &locationController) && locationController && IS_TYPE(locationController, MediaLocationController)) {
		ExtraAudioMarker* audioMrkr = thisObj->GetExtraData<ExtraAudioMarker>();
		if (audioMrkr && audioMrkr->pData) {
			audioMrkr->pData->uiMediaLocationController = locationController->GetFormID();
			Console_Print("AudioMarkerSetController >> 0x%lx, %s", locationController->GetFormID(), locationController->GetFormEditorID());

		}
		else if (IsConsoleMode()) {
			Console_Print("Calling reference is not an AudioMarker");
		}
	}
	return true;
}


bool Cmd_AudioMarkerSetProperty_Execute(COMMAND_ARGS) {
	DWORD type;
	float fValue;
	enum kAMType {
		kRadius,
		kLayer2,
		kLayer3,
		kFlags
	};
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &type, &fValue)) {
		ExtraAudioMarker* audioMrkr = thisObj->GetExtraData<ExtraAudioMarker>();
		ExtraRadius* rad = thisObj->GetExtraData<ExtraRadius>();
		if (audioMrkr && audioMrkr->pData) {
			switch (type) {
			case kRadius:
				if (rad) {
					rad->fRadius = fValue;
				}
				break;
			case kLayer2:
				audioMrkr->pData->fSecondLayerPercent = fValue;
				break;
			case kLayer3:
				audioMrkr->pData->fThirdLayerPercent = fValue;
				break;
			case kFlags:
				audioMrkr->pData->bUseController = bool(fValue);
				break;

			}
			Console_Print("AudioMarkerSetProperty >> %s, %d, %.2f", thisObj->GetFormEditorID(), type, fValue);
		}
		else if (IsConsoleMode()) {
			Console_Print("Calling reference is not an AudioMarker");
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
		ExtraAudioMarker* audioMrkr = thisObj->GetExtraData<ExtraAudioMarker>();
		ExtraRadius* rad = thisObj->GetExtraData<ExtraRadius>();
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

			Console_Print("AudioMarkerGetProperty >> %s, %d, %.2f", thisObj->GetFormEditorID(), type, *result);
		}
		else if (IsConsoleMode()) {
			Console_Print("Calling reference is not an AudioMarker");
		}
	}
	return true;
}
bool Cmd_GetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
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
		if (IsConsoleMode())
			Console_Print("GetMediaSetTraitNumeric %d >> %.2f", iTrait, *result);
	}
	return true;
}
bool Cmd_SetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	MediaSet* pMediaSet = nullptr;
	int32_t iTrait = -1;
	float fValue = -1;
	*result = 0;
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
	MediaSet* pMediaSet = nullptr;
	int iSoundType = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iSoundType) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		switch (iSoundType) {
		case 0:
			*(uint32_t*)result = pMediaSet->GetSound1()->GetFormID();
			break;
		case 1:
			*(uint32_t*)result = pMediaSet->GetSound2()->GetFormID();
			break;
		}
	}
	return true;
}

bool Cmd_SetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	MediaSet* pMediaSet = nullptr;
	TESSound* pSound = nullptr;
	int iSoundType = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iSoundType, &pSound) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (pSound && !IS_TYPE(pSound, TESSound))
			return true;

		switch (iSoundType) {
		case 0:
			pMediaSet->SetSound1(pSound);
			*result = 1;
			break;
		case 1:
			pMediaSet->SetSound2(pSound);
			*result = 1;
			break;
		}
	}
	return true;
}

bool Cmd_GetMediaSetTraitString_Execute(COMMAND_ARGS) {
	MediaSet* pMediaSet = nullptr;
	int32_t iLayer = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iLayer) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (iLayer >= 0 && iLayer <= 5) {
			const char* pName = pMediaSet->kLayers[iLayer].strName.c_str();
			g_strInterface->Assign(PASS_COMMAND_ARGS, pName);
			if (IsConsoleMode())
				Console_Print("GetMediaSetTraitString %d >> %s", iLayer, pName);
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