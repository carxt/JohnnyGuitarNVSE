#pragma once
//Mediaset functions
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitNumeric, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitSound, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitString, , false, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitNumeric, , false, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitSound, , false, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitString, , false, kParams_OneForm_OneInt_OneString);
DEFINE_CMD_ALT_COND_PLUGIN(AudioMarkerGetController, AMKGetCtrl, , true, nullptr);
DEFINE_CMD_ALT_COND_PLUGIN(AudioMarkerGetCurrent, AMKGetCur, , false, nullptr);
DEFINE_COMMAND_ALT_PLUGIN(AudioMarkerGetProperty, AMKGetProp, , true, kParams_OneInt);
DEFINE_COMMAND_ALT_PLUGIN(AudioMarkerSetProperty, AMKSetProp, , true, kParams_OneInt_OneFloat);
DEFINE_COMMAND_ALT_PLUGIN(AudioMarkerSetController, AMKSetCtrl, , true, kParams_OneForm);

DEFINE_COMMAND_PLUGIN(GetAcousticSpace, , true, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetAcousticSpace, , true, kParams_OneForm_OneOptionalForm);




bool Cmd_GetAcousticSpace_Execute(COMMAND_ARGS) 
{
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL))
	{
		ExtraCellAcousticSpace* pXAcousticSpace = (ExtraCellAcousticSpace*)pCell->extraDataList.GetByType(kExtraData_CellAcousticSpace);
		if (pXAcousticSpace && pXAcousticSpace->acousticSpace)
		{
			*(DWORD*) result = pXAcousticSpace->acousticSpace->refID;
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

		if (pAcousticSpace && !IS_TYPE(pAcousticSpace, BGSAcousticSpace) ) [[unlikely]]
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






bool Cmd_AudioMarkerGetCurrent_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (PlayerCharacter::GetSingleton() && PlayerCharacter::GetSingleton()->currMusicMarker) {
		if (auto mMarker = PlayerCharacter::GetSingleton()->currMusicMarker->markerRef) {
			*(DWORD*)result = mMarker->refID;
		}
	}
	return true;
}




bool Cmd_AudioMarkerGetCurrent_Execute(COMMAND_ARGS){
	Cmd_AudioMarkerGetCurrent_Eval(thisObj, nullptr, nullptr, result);
	return true;
}


bool Cmd_AudioMarkerGetController_Eval(COMMAND_ARGS_EVAL) {
	MediaLocationController* locationController = nullptr;
	*result = 0;
	if (thisObj) {
		ExtraAudioMarker* audioMrkr = (ExtraAudioMarker*)thisObj->extraDataList.GetByType(kExtraData_AudioMarker);
		if (audioMrkr && audioMrkr->data) {
			uintptr_t locController = audioMrkr->data->mediaLocCtrlID;
			locationController = (MediaLocationController*)LookupFormByID(locController);
			*(DWORD*)result = locationController->refID;
			if (IsConsoleMode()) {

			}
		}
		else if (IsConsoleMode()) {
		}
	}
	return true;
}

bool Cmd_AudioMarkerGetController_Execute(COMMAND_ARGS) {
	Cmd_AudioMarkerGetController_Eval(thisObj, nullptr, nullptr, result);
	if (IsConsoleMode()) {
		if (thisObj) {
			if (*result) {
				Console_Print("AudioMarkerGetController >> 0x%lx", *(DWORD*) result );
			}
			else {
				Console_Print("Calling reference is not an AudioMarker");
			}
		}
	}
	return true;
}



bool Cmd_AudioMarkerSetController_Execute(COMMAND_ARGS) {
	MediaLocationController* locationController;
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &locationController) && locationController && IS_TYPE(locationController, MediaLocationController)) {
		ExtraAudioMarker* audioMrkr = (ExtraAudioMarker*) thisObj->extraDataList.GetByType(kExtraData_AudioMarker);
		if (audioMrkr && audioMrkr->data) {
			audioMrkr->data->mediaLocCtrlID = locationController->refID;
			Console_Print("AudioMarkerSetController >> 0x%lx, %s", locationController->refID, locationController->GetFormEditorID());

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
		ExtraAudioMarker* audioMrkr = (ExtraAudioMarker*)thisObj->extraDataList.GetByType(kExtraData_AudioMarker);
		ExtraRadius* rad = (ExtraRadius*)thisObj->extraDataList.GetByType(kExtraData_Radius);
		if (audioMrkr && audioMrkr->data) {
			switch (type) {
			case kRadius:
				if (rad) {
					rad->radius = newVal;
				}
				break;
			case kLayer2:
				audioMrkr->data->layer2TriggerPerc = newVal;
				break;
			case kLayer3:
				audioMrkr->data->layer3TriggerPerc = newVal;
				break;
			case kFlags:
				audioMrkr->data->flags = uint32_t(newVal);
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
		ExtraAudioMarker* audioMrkr = (ExtraAudioMarker*)thisObj->extraDataList.GetByType(kExtraData_AudioMarker);
		ExtraRadius* rad = (ExtraRadius*)thisObj->extraDataList.GetByType(kExtraData_Radius);
		if (audioMrkr && audioMrkr->data) {
			switch (type) {
			case kRadius:
				if (rad) {
					*result = rad->radius;
				}
				break;
			case kLayer2:
				*result = audioMrkr->data->layer2TriggerPerc;
				break;
			case kLayer3:
				*result = audioMrkr->data->layer3TriggerPerc;
				break;
			case kFlags:
				*result =  audioMrkr->data->flags;
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
				*result = mediaset->type;
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
				mediaset->type = newVal;
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
				*(uint32_t*)result = mediaset->HNAM->refID;
				break;
			case 1:
				*(uint32_t*)result = mediaset->INAM->refID;
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
	MediaSet* mediaset = nullptr ;
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