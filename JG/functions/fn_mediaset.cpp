#include "fn_mediaset.h"
#include "GameObjects.h"
#include "decoding.h"

#include "Bethesda/ExtraCellAcousticSpace.hpp"
#include "Bethesda/ExtraRadius.hpp"
#include "Obsidian/ExtraAudioMarker.hpp"

bool Cmd_GetAcousticSpace_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* pCell = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell) && pCell && IS_TYPE(pCell, TESObjectCELL)) {
		ExtraCellAcousticSpace* pXAcousticSpace = pCell->extraDataList.GetExtraData<ExtraCellAcousticSpace>();
		if (pXAcousticSpace && pXAcousticSpace->pSpace) 
			reinterpret_cast<uint32_t&>(arResult) = pXAcousticSpace->pSpace->GetFormID();

		if (IsConsoleMode())
			Console_Print("GetAcousticSpace  >> 0x%08X", reinterpret_cast<uint32_t&>(arResult));
	}
	return true;
}

bool Cmd_SetAcousticSpace_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESObjectCELL* pCell = nullptr;
	BGSAcousticSpace* pAcousticSpace = nullptr;
	uintptr_t ExtraCellAcousticSpace_Update = 0x041C090;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pCell, pAcousticSpace) && pCell) {
		if (!IS_TYPE(pCell, TESObjectCELL)) [[unlikely]] {
			if (IsConsoleMode())
				Console_Print("SetAcousticSpace >> Passed an invalid cell");
			return true;
		}

		if (pAcousticSpace && !IS_TYPE(pAcousticSpace, BGSAcousticSpace)) [[unlikely]] {
			if (IsConsoleMode())
				Console_Print("SetAcousticSpace >> Passed an invalid acoustic space");
			return true;
		}
		ThisCall(ExtraCellAcousticSpace_Update, &pCell->extraDataList, pAcousticSpace);
	}
	return true;
}

SPEC_NOINLINE bool Cmd_AudioMarkerGetCurrent_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	if (PlayerCharacter::GetSingleton() && PlayerCharacter::GetSingleton()->currMusicMarker) {
		if (TESObjectREFR* pMarkerRef = PlayerCharacter::GetSingleton()->currMusicMarker->pReference)
			reinterpret_cast<uint32_t&>(arResult) = pMarkerRef->GetFormID();
	}
	return true;
}

bool Cmd_AudioMarkerGetCurrent_Execute(COMMAND_ARGS) {
	return Cmd_AudioMarkerGetCurrent_Eval(apRef, nullptr, nullptr, arResult);
}

SPEC_NOINLINE bool Cmd_AudioMarkerGetController_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	if (apRef) {
		ExtraAudioMarker* pExtraMarker = apRef->GetExtraData<ExtraAudioMarker>();
		if (pExtraMarker && pExtraMarker->pData) {
			uintptr_t uiCtrlFormID = pExtraMarker->pData->uiMediaLocationController;
			TESForm* pFoundForm = TESForm::GetFormByNumericID(uiCtrlFormID);
			if (pFoundForm->GetFormType() == FORM_TYPE::MediaLocationController)
				reinterpret_cast<uint32_t&>(arResult) = pFoundForm->GetFormID();
		}
	}
	return true;
}

bool Cmd_AudioMarkerGetController_Execute(COMMAND_ARGS) {
	Cmd_AudioMarkerGetController_Eval(apRef, nullptr, nullptr, arResult);
	if (apRef && IsConsoleMode()) {
		if (arResult)
			Console_Print("AudioMarkerGetController >> 0x%lx", reinterpret_cast<uint32_t&>(arResult));
		else
			Console_Print("Calling reference is not an AudioMarker");
	}
	return true;
}

bool Cmd_AudioMarkerSetController_Execute(COMMAND_ARGS) {
	MediaLocationController* locationController;
	if (apRef && ExtractArgsEx(EXTRACT_ARGS_EX, &locationController) && locationController && IS_TYPE(locationController, MediaLocationController)) {
		ExtraAudioMarker* pAudioMarker = apRef->GetExtraData<ExtraAudioMarker>();
		if (pAudioMarker && pAudioMarker->pData) {
			pAudioMarker->pData->uiMediaLocationController = locationController->GetFormID();

			if (IsConsoleMode())
				Console_Print("AudioMarkerSetController >> 0x%08X, %s", locationController->GetFormID(), locationController->GetFormEditorID());

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
	if (apRef && ExtractArgsEx(EXTRACT_ARGS_EX, &type, &fValue)) {
		ExtraAudioMarker* pAudioMarker = apRef->GetExtraData<ExtraAudioMarker>();
		if (pAudioMarker && pAudioMarker->pData) {
			switch (type) {
			case kRadius:
				apRef->GetExtra()->SetRadius(fValue);
				break;
			case kLayer2:
				pAudioMarker->pData->fSecondLayerPercent = fValue;
				break;
			case kLayer3:
				pAudioMarker->pData->fThirdLayerPercent = fValue;
				break;
			case kFlags:
				pAudioMarker->pData->bUseController = bool(fValue);
				break;

			}

			if (IsConsoleMode())
				Console_Print("AudioMarkerSetProperty >> %s, %d, %.2f", apRef->GetFormEditorID(), type, fValue);
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
	if (apRef && ExtractArgsEx(EXTRACT_ARGS_EX, &type)) {
		const ExtraAudioMarker* pAudioMarker = apRef->GetExtraData<ExtraAudioMarker>();
		if (pAudioMarker && pAudioMarker->pData) {
			switch (type) {
			case kRadius:
				{
					ExtraRadius* pRadius = apRef->GetExtraData<ExtraRadius>();
					if (pRadius)
						arResult = pRadius->fRadius;
				}
				break;
			case kLayer2:
				arResult = pAudioMarker->pData->fSecondLayerPercent;
				break;
			case kLayer3:
				arResult = pAudioMarker->pData->fThirdLayerPercent;
				break;
			case kFlags:
				arResult = pAudioMarker->pData->bUseController;
				break;

			}

			if (IsConsoleMode())
				Console_Print("AudioMarkerGetProperty >> %s, %d, %.2f", apRef->GetFormEditorID(), type, arResult);
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
			arResult = pMediaSet->GetType();
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			arResult = pMediaSet->kLayers[iTrait - 1].fAttenuation;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			arResult = pMediaSet->kLayers[iTrait - 7].fPercent;
			break;
		case 13:
			arResult = pMediaSet->ucEnableFlags;
			break;
		case 14:
			arResult = pMediaSet->fWaitTime;
			break;
		case 15:
			arResult = pMediaSet->fLoopFadeOut;
			break;
		case 16:
			arResult = pMediaSet->fRecoveryTime;
			break;
		case 17:
			arResult = pMediaSet->fNightTimeMax;
			break;
		}

		if (IsConsoleMode())
			Console_Print("GetMediaSetTraitNumeric %d >> %.2f", iTrait, arResult);
	}
	return true;
}
bool Cmd_SetMediaSetTraitNumeric_Execute(COMMAND_ARGS) {
	MediaSet* pMediaSet = nullptr;
	int32_t iTrait = -1;
	float fValue = -1;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iTrait, &fValue) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		arResult = 1;
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
			arResult = 0;
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
			{
				TESSound* pSound = pMediaSet->GetSound1();
				if (pSound)
					reinterpret_cast<uint32_t&>(arResult) = pSound->GetFormID();
			}
			break;
		case 1:
			{
				TESSound* pSound = pMediaSet->GetSound2();
				if (pSound)
					reinterpret_cast<uint32_t&>(arResult) = pSound->GetFormID();
			}
			break;
		}
	}
	return true;
}

bool Cmd_SetMediaSetTraitSound_Execute(COMMAND_ARGS) {
	MediaSet* pMediaSet = nullptr;
	TESSound* pSound = nullptr;
	int iSoundType = -1;
	arResult = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iSoundType, &pSound) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (pSound && !IS_TYPE(pSound, TESSound))
			return true;

		switch (iSoundType) {
		case 0:
			pMediaSet->SetSound1(pSound);
			arResult = 1;
			break;
		case 1:
			pMediaSet->SetSound2(pSound);
			arResult = 1;
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
	arResult = 0;
	MediaSet* pMediaSet = nullptr;
	int32_t iLayer = -1;
	char cName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pMediaSet, &iLayer, &cName) && pMediaSet && IS_TYPE(pMediaSet, MediaSet)) {
		if (iLayer >= 0 && iLayer <= 5) {
			pMediaSet->kLayers[iLayer].strName.Set(cName);
			arResult = 1;
		}
	}
	return true;
}