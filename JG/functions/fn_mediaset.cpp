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
		ExtraAudioMarker* pExtraMarker = thisObj->extraDataList.GetExtraData<ExtraAudioMarker>();
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
		ExtraAudioMarker* audioMrkr = thisObj->extraDataList.GetExtraData<ExtraAudioMarker>();
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
	float newVal;
	enum kAMType {
		kRadius,
		kLayer2,
		kLayer3,
		kFlags
	};
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &type, &newVal)) {
		ExtraAudioMarker* audioMrkr = thisObj->extraDataList.GetExtraData<ExtraAudioMarker>();
		ExtraRadius* rad = thisObj->extraDataList.GetExtraData<ExtraRadius>();
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
			Console_Print("AudioMarkerSetProperty >> %s, %d, %.2f", thisObj->GetFormEditorID(), type, newVal);
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
		ExtraAudioMarker* audioMrkr = thisObj->extraDataList.GetExtraData<ExtraAudioMarker>();
		ExtraRadius* rad = thisObj->extraDataList.GetExtraData<ExtraRadius>();
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
	MediaSet* mediaset = nullptr;
	int traitID = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID) && mediaset && IS_TYPE(mediaset, MediaSet)) {
		switch (traitID) {
		case 0:
			*result = mediaset->uiType;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			*result = mediaset->data[traitID - 1].dB;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			*result = mediaset->data[traitID - 7].boundary;
			break;
		case 13:
			*result = mediaset->flags;
			break;
		case 14:
			*result = mediaset->DNAM;
			break;
		case 15:
			*result = mediaset->ENAM;
			break;
		case 16:
			*result = mediaset->FNAM;
			break;
		case 17:
			*result = mediaset->GNAM;
			break;
		}
		if (IsConsoleMode())
			Console_Print("GetMediaSetTraitNumeric %d >> %.2f", traitID, *result);
	}
	return true;
}
bool Cmd_SetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	MediaSet* mediaset = nullptr;
	int traitID = -1;
	float newVal = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID, &newVal) && mediaset && IS_TYPE(mediaset, MediaSet)) {
		*result = 1;
		switch (traitID) {
		case 0:
			mediaset->uiType = newVal;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			mediaset->data[traitID - 1].dB = newVal;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			mediaset->data[traitID - 7].boundary = newVal;
			break;
		case 13:
			mediaset->flags = newVal;
			break;
		case 14:
			mediaset->DNAM = newVal;
			break;
		case 15:
			mediaset->ENAM = newVal;
			break;
		case 16:
			mediaset->FNAM = newVal;
			break;
		case 17:
			mediaset->GNAM = newVal;
			break;
		default:
			*result = 0;
			break;
		}
	}
	return true;
}
bool Cmd_GetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	MediaSet* mediaset = nullptr;
	int traitID = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID) && mediaset && IS_TYPE(mediaset, MediaSet)) {
		switch (traitID) {
		case 0:
			*(uint32_t*)result = mediaset->HNAM->GetFormID();
			break;
		case 1:
			*(uint32_t*)result = mediaset->INAM->GetFormID();
			break;
		}
	}
	return true;
}

bool Cmd_SetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	MediaSet* mediaset = nullptr;
	TESSound* soundForm = nullptr;
	int traitID = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID, &soundForm) && mediaset && IS_TYPE(mediaset, MediaSet)) {
		if (soundForm && !IS_TYPE(soundForm, TESSound))
			return true;

		switch (traitID) {
		case 0:
			mediaset->HNAM = soundForm;
			*result = 1;
			break;
		case 1:
			mediaset->INAM = soundForm;
			*result = 1;
			break;
		}
	}
	return true;
}

bool Cmd_GetMediaSetTraitString_Execute(COMMAND_ARGS) {
	MediaSet* mediaset = nullptr;
	int traitID = -1;
	const char* resStr = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID) && mediaset && IS_TYPE(mediaset, MediaSet)) {
		if (traitID >= 0 && traitID <= 5) {
			resStr = mediaset->data[traitID].filepath.c_str();
			g_strInterface->Assign(PASS_COMMAND_ARGS, resStr);
			if (IsConsoleMode())
				Console_Print("GetMediaSetTraitString %d >> %s", traitID, resStr);
		}
	}
	return true;
}

bool Cmd_SetMediaSetTraitString_Execute(COMMAND_ARGS) {
	MediaSet* mediaset = nullptr;
	int traitID = -1;
	char newStr[MAX_PATH] = {};
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID, &newStr) && mediaset && IS_TYPE(mediaset, MediaSet)) {
		if (traitID >= 0 && traitID <= 5) {
			mediaset->data[traitID].filepath.Set(newStr);
			*result = 1;
		}
	}
	return true;
}