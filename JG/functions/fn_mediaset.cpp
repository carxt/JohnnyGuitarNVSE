#include "fn_mediaset.h"
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/ExtraRadius.hpp"
#include "Bethesda/Interface.hpp"
#include "Obsidian/AudioMarkerInfo.hpp"

bool Cmd_GetAcousticSpace_Execute(COMMAND_ARGS) {
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

bool Cmd_SetAcousticSpace_Execute(COMMAND_ARGS) {
	*result = 0;
	TESObjectCELL* pCell = nullptr;
	BGSAcousticSpace* pAcousticSpace = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, pAcousticSpace) && pCell) {
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
		AudioMarkerData* pMarkerData = thisObj->GetAudioMarkerData();
		if (pMarkerData) {
			FormID uiCtrlFormID = pMarkerData->uiMediaLocationController;
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
			Interface::PrintLine("AudioMarkerGetController >> 0x%08X", *reinterpret_cast<FormID*>(result));
		else
			Interface::PrintLine("Calling reference is not an AudioMarker");
	}
	return true;
}


bool Cmd_AudioMarkerSetController_Execute(COMMAND_ARGS) {
	MediaLocationController* pController;
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &pController) && pController && IS_TYPE(pController, MediaLocationController)) {
		AudioMarkerData* pMarkerData = thisObj->GetAudioMarkerData();
		if (pMarkerData) {
			pMarkerData->uiMediaLocationController = pController->GetFormID();
			if (Script::GetConsoleOuput())
				Interface::PrintLine("AudioMarkerSetController >> 0x%08X, %s", pController->GetFormID(), pController->GetFormEditorID());

		}
		else if (Script::GetConsoleOuput()) {
			Interface::PrintLine("Calling reference is not an AudioMarker");
		}
	}
	return true;
}


bool Cmd_AudioMarkerSetProperty_Execute(COMMAND_ARGS) {
	DWORD uiTrait;
	float fValue;
	enum kAMType {
		kRadius,
		kLayer2,
		kLayer3,
		kFlags
	};
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &uiTrait, &fValue)) {
		AudioMarkerData* pMarkerData = thisObj->GetAudioMarkerData();
		if (pMarkerData) {
			switch (uiTrait) {
				case kRadius:
					thisObj->GetExtra()->SetRadius(fValue);
					break;
				case kLayer2:
					pMarkerData->fSecondLayerPercent = fValue;
					break;
				case kLayer3:
					pMarkerData->fThirdLayerPercent = fValue;
					break;
				case kFlags:
					pMarkerData->bUseController = bool(fValue);
					break;
			}
			if (Script::GetConsoleOuput())
				Interface::PrintLine("AudioMarkerSetProperty >> %s, %d, %.2f", thisObj->GetFormEditorID(), uiTrait, fValue);
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
		AudioMarkerData* pMarkerData = thisObj->GetAudioMarkerData();
		if (pMarkerData) {
			switch (type) {
				case kRadius:
					*result = thisObj->GetExtra()->GetRadius();
					break;
				case kLayer2:
					*result = pMarkerData->fSecondLayerPercent;
					break;
				case kLayer3:
					*result = pMarkerData->fThirdLayerPercent;
					break;
				case kFlags:
					*result = pMarkerData->bUseController;
					break;
	
			}
			if (Script::GetConsoleOuput())
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
	uint32_t uiLayer = UINT_MAX;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &uiLayer) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (uiLayer < 6) {
			const char* pName = pMediaSet->kLayers[uiLayer].strName.c_str();
			g_strInterface->Assign(PASS_COMMAND_ARGS, pName);
			if (Script::GetConsoleOuput())
				Interface::PrintLine("GetMediaSetTraitString %d >> %s", uiLayer, pName);
		}
	}
	return true;
}

bool Cmd_SetMediaSetTraitString_Execute(COMMAND_ARGS) {
	*result = 0;
	MediaSet* pMediaSet = nullptr;
	uint32_t uiLayer = UINT_MAX;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &uiLayer, &cName) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (uiLayer < 6) {
			pMediaSet->kLayers[uiLayer].strName.Set(cName);
			*result = 1;
		}
	}
	return true;
}