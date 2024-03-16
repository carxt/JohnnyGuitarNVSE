#pragma once
//Mediaset functions
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitNumeric, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitSound, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(GetMediaSetTraitString, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitNumeric, , 0, 3, kParams_OneForm_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitSound, , 0, 3, kParams_OneForm_OneInt_OneForm);
DEFINE_COMMAND_PLUGIN(SetMediaSetTraitString, , 0, 3, kParams_OneForm_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(AudioMarkerSetController, , 1, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(AudioMarkerGetController, , 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(AudioMarkerSetProperty, , 1, 2, kParams_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(AudioMarkerGetProperty, , 1, 1, kParams_OneInt);


bool Cmd_AudioMarkerSetController_Execute(COMMAND_ARGS) {
	MediaLocationController* locationController;
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &locationController) && IS_TYPE(locationController, MediaLocationController)) {
		ExtraAudioMarker* audioMrkr = (ExtraAudioMarker*) thisObj->extraDataList.GetByType(kExtraData_AudioMarker);
		if (audioMrkr && audioMrkr->data) {
			audioMrkr->data->mediaLocCtrlID = locationController->refID;
			Console_Print("AudioMarkerSetController >> 0x%lx, %s", locationController->refID, locationController->GetName());

		}
		else if (IsConsoleMode()) {
			Console_Print("Calling reference is not an AudioMarker");
		}
	}
	return true;
}

bool Cmd_AudioMarkerGetController_Execute(COMMAND_ARGS) {
	MediaLocationController* locationController = NULL;
	*result = 0;
	if (thisObj ) {
		ExtraAudioMarker* audioMrkr = (ExtraAudioMarker*)thisObj->extraDataList.GetByType(kExtraData_AudioMarker);
		if (audioMrkr && audioMrkr->data) {
			uintptr_t locController = audioMrkr->data->mediaLocCtrlID;
			locationController = (MediaLocationController*) LookupFormByID(locController);
			*(DWORD*)result = locationController->refID;
			if (IsConsoleMode()) {
				Console_Print("AudioMarkerGetController >> 0x%lx, %s", locationController->refID, locationController->GetName());

			}
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
				audioMrkr->data->flags = UInt32(newVal);
				break;

			}
			Console_Print("AudioMarkerSetProperty >> %s, %d, %.2f", thisObj->GetName(), type, newVal);
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

			Console_Print("AudioMarkerGetProperty >> %s, %d, %.2f", thisObj->GetName(), type, *result);
		}
		else if (IsConsoleMode()) {
			Console_Print("Calling reference is not an AudioMarker");
		}
	}
	return true;
}
bool Cmd_GetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	int traitID = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID) && IS_TYPE(mediaset, MediaSet)) {
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
	MediaSet* mediaset;
	int traitID = -1;
	float newVal = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID, &newVal) && IS_TYPE(mediaset, MediaSet)) {
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
	MediaSet* mediaset;
	int traitID = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID) && IS_TYPE(mediaset, MediaSet)) {
		switch (traitID) {
			case 0:
				*(UInt32*)result = mediaset->HNAM->refID;
				break;
			case 1:
				*(UInt32*)result = mediaset->INAM->refID;
				break;
		}
	}
	return true;
}
bool Cmd_SetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	TESSound* soundForm;
	int traitID = -1;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID, &soundForm) && IS_TYPE(mediaset, MediaSet) && IS_TYPE(soundForm, TESSound)) {
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
	MediaSet* mediaset;
	int traitID = -1;
	const char* resStr = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID) && IS_TYPE(mediaset, MediaSet)) {
		if (traitID >= 0 && traitID <= 5) {
			resStr = mediaset->data[traitID].filepath.CStr();
			g_strInterface->Assign(PASS_COMMAND_ARGS, resStr);
			if (IsConsoleMode())
				Console_Print("GetMediaSetTraitString %d >> %s", traitID, resStr);
		}
	}
	return true;
}
bool Cmd_SetMediaSetTraitString_Execute(COMMAND_ARGS) {
	MediaSet* mediaset;
	int traitID = -1;
	char newStr[MAX_PATH];
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &mediaset, &traitID, &newStr) && IS_TYPE(mediaset, MediaSet)) {
		if (traitID >= 0 && traitID <= 5) {
			mediaset->data[traitID].filepath.Set(newStr);
			*result = 1;
		}
	}
	return true;
}