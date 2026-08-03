#include "fn_utility.h"
#ifdef GAME
#include "Bethesda/BSUtilities.hpp"
#include "Bethesda/TimeGlobal.hpp"
#include "decoding.h"
#include "GameProcess.h"
#include "GameUI.h"
#include "JG/CameraOverride.hpp"
#include "JG/DisabledLevelUp.hpp"
#include "JG/ExtraReputationIcons.hpp"
#include "JG/ExtraUISounds.hpp"
#include "JG/JohnnyPatches.hpp"
#include "JG/JohnnyRadios.hpp"
#include "JIP/JIPUtils.hpp"
#include "misc/misc.h"
#include "random"
#include "shared/BSMemory/BSScrapMemory.hpp"

extern DWORD dwGameStartTimestamp;

SPEC_INLINE bool Cmd_GameGetSecondsPassed_Eval(COMMAND_ARGS_EVAL) {
	arResult = TimeGlobal::GetSingleton()->GetRealTimeSeconds();
	return true;
}

bool Cmd_GameGetSecondsPassed_Execute(COMMAND_ARGS) {
	Cmd_GameGetSecondsPassed_Eval(nullptr, nullptr, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("GameGetSecondsPassed >> %0.2f", arResult);
	return true;
}

bool Cmd_NullNoArgs_Execute(COMMAND_ARGS) {
	arResult = 0;
	return true;
}

bool Cmd_NullArgs_Execute(COMMAND_ARGS) {
	arResult = 0;
	return true;
}

bool Cmd_GetAllGameRadios_Execute(COMMAND_ARGS) {
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);
	BSSimpleList<TESObjectACTI*>* pRadioStations = reinterpret_cast<BSSimpleList<TESObjectACTI*>*>(0x11C8264);
	while (pRadioStations && !pRadioStations->IsEmpty()) {
		TESObjectACTI* pRadio = pRadioStations->GetItem();
		if (pRadio)
			g_arrInterface->AppendElement(pArray, NVSEArrayElement(pRadio));
		pRadioStations = pRadioStations->GetNext();
	}
	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;
}

bool Cmd_GetAvailableRadios_Execute(COMMAND_ARGS) {
	NVSEArrayVar* pArray = g_arrInterface->CreateArray(nullptr, 0, apScript);

	BSSimpleList<TESObjectACTI*> kRadios;
	CdeclCall(0x04FF1A0, apRef, &kRadios, nullptr);

	auto pIter = kRadios.GetHead();
	while (pIter && !pIter->IsEmpty()) {
		TESObjectACTI* pRadio = pIter->GetItem();
		if (pRadio && !CdeclCall<bool>(0x0079BE30, pRadio) && JohnnyRadios::IsAvailable(pRadio->GetFormID()))
			g_arrInterface->AppendElement(pArray, NVSEArrayElement(pRadio));
		pIter = pIter->GetNext();
	}

	g_arrInterface->AssignCommandResult(pArray, &arResult);
	return true;
}

bool Cmd_RollCredits_Execute(COMMAND_ARGS) {
	arResult = 0;
	CdeclCall(0x75F2A0);
	return true;
}

bool Cmd_DumpIconMap_Execute(COMMAND_ARGS) {
	ExtraReputationIcons::Dump();
	return true;
}

bool Cmd_UpdateCrosshairPrompt_Execute(COMMAND_ARGS) {
	arResult = 0;
	CdeclCall(0x778B10);
	return true;
}

enum EType {
	kSetting_Bool = 0,
	kSetting_c,
	kSetting_h,
	kSetting_Integer,
	kSetting_Unsigned,
	kSetting_Float,
	kSetting_String,
	kSetting_r,
	kSetting_a,
	kSetting_Other
};

bool Cmd_RefreshIdle_Execute(COMMAND_ARGS) {
	arResult = 0;
	BOOL bStopAnim = FALSE;
	Actor* pActor = static_cast<Actor*>(apRef);
	ExtractArgsEx(EXTRACT_ARGS_EX, &bStopAnim);
	if (pActor && pActor->IsActor() && pActor->GetCurrentAIProcess() && pActor->GetCurrentAIProcess()->GetCurrentProcessIdle()) {
		pActor->GetCurrentAIProcess()->ClearPostAnimationActions();
		pActor->GetCurrentAIProcess()->SetCurrentProcessIdle(nullptr);
		if (bStopAnim > 0)
			ThisCall(0x498910, pActor->GetAnimation(), 1, 1); // SpecialIdleFree
		arResult = 1;
	}
	return true;
}

bool Cmd_IsDLLLoaded_Execute(COMMAND_ARGS) {
	arResult = 0;
	int checkOutsideOfGameFolder = 0;
	char dllName[MAX_PATH] = {};
	char dllPath[MAX_PATH] = {};
	char fnvPath[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dllName, &checkOutsideOfGameFolder)) {
		strncat_s(dllName, ".dll", 4);
		HMODULE module = GetModuleHandle(dllName);
		if (module) {
			if (!checkOutsideOfGameFolder) {
				GetModuleFileNameA(module, dllPath, MAX_PATH);
				GetModuleFileNameA(nullptr, fnvPath, MAX_PATH);
				fnvPath[strlen(fnvPath) - 13] = '\0';
				if (strstr(dllPath, fnvPath) != nullptr) 
					arResult = 1;
			}
			else {
				arResult = 1;
			}
		}
		if (IsConsoleMode()) Console_Print("IsDLLLoaded \"%s\" >> %.f", dllName, arResult);
	}
	return true;
}

bool Cmd_ar_IsFormInList_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t arrID, fullMatch;
	BGSListForm* formList = nullptr;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID, &formList, &fullMatch)) return true;

	if (!formList || !IS_TYPE(formList, BGSListForm)) return true;

	NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
	if (!inArr) return true;
	uint32_t size = g_arrInterface->GetArraySize(inArr);
	BSScrapBuffer<NVSEArrayElement> elements(size);
	g_arrInterface->GetElements(inArr, elements.get(), nullptr);
	if (!fullMatch) {
		for (uint32_t i = 0; i < size; i++) {
			if (elements[i].GetTESForm() == nullptr) return true;
			BSSimpleList<TESForm*>* pIter= formList->GetFormList();
			while(pIter && !pIter->IsEmpty()) {
				if (elements[i].GetTESForm() == pIter->GetItem()) {
					arResult = 1;
					return true;
				}
				pIter = pIter->GetNext();
			};
		}
	}
	else {
		for (uint32_t i = 0; i < size; i++) {
			if (elements[i].GetTESForm() == nullptr) return true;
			int elementFound = 0;
			BSSimpleList<TESForm*>* pIter = formList->GetFormList();
			while (pIter && !pIter->IsEmpty()) {
				if (elements[i].GetTESForm() == pIter->GetItem()) {
					elementFound = 1;
					break;
				}
				pIter = pIter->GetNext();
			};
			if (elementFound == 0) {
				return true;
			}
		}
		arResult = 1;
	}

	return true;
}

bool Cmd_SetUIUpdateSound_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESSound* pSound = nullptr;
	uint32_t uiType = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pSound, &uiType) && pSound && IS_TYPE(pSound, TESSound) && uiType >= 1 && uiType <= 4) {
		ExtraUISounds::SetQuestSound(pSound, QuestUpdateManager::UpdateType(uiType - 1));
		arResult = 1;
	}
	return true;
}

struct cmp_str {
public:
	cmp_str(bool s_) : s(s_) {};
	bool operator()(char const* a, char const* b) const {
		return s ? std::strcmp(a, b) > 0 : std::strcmp(a, b) < 0;
	}
private:
	bool s;
};

bool Cmd_ar_SortEditor_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t arrID;
	uint32_t isReverse = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID, &isReverse))
		return true;

	NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
	if (!inArr)
		return true;

	const uint32_t size = g_arrInterface->GetArraySize(inArr);
	BSScrapBuffer<NVSEArrayElement> elements(size);
	g_arrInterface->GetElements(inArr, elements.get(), nullptr);

	std::map<const char*, TESForm*, cmp_str> smap(cmp_str(isReverse > 0));
	for (uint32_t i = 0; i < size; i++) {
		if (elements[i].GetTESForm() == nullptr) 
			return true;

		smap.insert(std::pair<const char*, TESForm*>(elements[i].GetTESForm()->GetFormEditorID(), elements[i].GetTESForm()));
	}

	NVSEArrayVar* outArr = g_arrInterface->CreateArray(nullptr, 0, apScript);

	for (std::map<const char*, TESForm*>::iterator it = smap.begin(); it != smap.end(); ++it) {
		g_arrInterface->AppendElement(outArr, NVSEArrayElement(it->second));
	}

	g_arrInterface->AssignCommandResult(outArr, &arResult);
	return true;
}

SPEC_NOINLINE bool Cmd_GetSequenceAnimGroup_Eval(COMMAND_ARGS_EVAL) {
	arResult = -1;
	const uint32_t uiSequence = reinterpret_cast<uint32_t>(apParam1);
	if (apRef && uiSequence < 8) {
		const Animation* pAnim = apRef->GetAnimation();
		if (pAnim && pAnim->animSequence[uiSequence]) {
			const uint16_t usGroupID = pAnim->groupIDs[uiSequence] & 0xFF;
			arResult = usGroupID;
		}
	}
	return true;
}

bool Cmd_GetSequenceAnimGroup_Execute(COMMAND_ARGS) {
	uint32_t uiSequence = UINT32_MAX;
	ExtractArgsEx(EXTRACT_ARGS_EX, &uiSequence);
	return Cmd_GetSequenceAnimGroup_Eval(apRef, reinterpret_cast<void*>(uiSequence), nullptr, arResult);
}

bool Cmd_GetFormOverrideIndex_Execute(COMMAND_ARGS) {
	arResult = 0;
	TESForm* pForm = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm) && pForm) {
		TESFile* pFile = pForm->GetFile(-1);
		if (pFile)
			arResult = pFile->ucCompileIndex;
		else
			arResult = 0xFF;

		if (IsConsoleMode()) 
			Console_Print("GetFormOverrideIndex >> %.f", arResult);
	}
	return true;
}

SPEC_NOINLINE bool Cmd_GetPipBoyMode_Eval(COMMAND_ARGS_EVAL) {
	arResult = 0;
	if (InterfaceManager::GetSingleton())
		arResult = InterfaceManager::GetSingleton()->pipBoyMode;
	return true;
}

bool Cmd_GetPipBoyMode_Execute(COMMAND_ARGS) {
	Cmd_GetPipBoyMode_Eval(nullptr, nullptr, nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("GetPipBoyMode >> %.2f", arResult);
	return true;
}

bool Cmd_GetLinearVelocity_Execute(COMMAND_ARGS) {
	char X_outS[VAR_NAME_SIZE] = {}, Y_outS[VAR_NAME_SIZE] = {}, Z_outS[VAR_NAME_SIZE] = {};
	char nodeName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName, &X_outS, &Y_outS, &Z_outS)) {
		NiAVObject* pObject = BSUtilities::GetObjectByName(apRef->Get3D(), nodeName);
		if (!pObject)
			return true;

		if (!pObject->m_spCollisionObject || !pObject->m_spCollisionObject->IsBhkNiCollisionObject())
			return true;

		bhkNiCollisionObject* pColObj = static_cast<bhkNiCollisionObject*>(pObject->m_spCollisionObject.m_pObject);
		if (!pColObj->worldObj || !pColObj->worldObj->refObject)
			return true;

		uint32_t eMotionType = static_cast<bhkRigidBody*>(pColObj->worldObj)->GetMotionType();
		if (!bhkRigidBody::IsMotionTypeDynamic(eMotionType))
			return true;

		hkpRigidBody* rigidBody = static_cast<hkpRigidBody*>(pColObj->worldObj->refObject);
		if (rigidBody) {
			NiPoint4 linVelocity = rigidBody->motion.linVelocity;
			setVarByName(PASS_VARARGS, X_outS, linVelocity.x);
			setVarByName(PASS_VARARGS, Y_outS, linVelocity.y);
			setVarByName(PASS_VARARGS, Z_outS, linVelocity.z);
		}
	}
	return true;
}

bool Cmd_GetDefaultHeapSize_Execute(COMMAND_ARGS) {
	uint32_t uiHeapSize = *reinterpret_cast<uint32_t*>(0x866E9F + 1);
	arResult = uiHeapSize / 1024.f / 1024.f;
	if (IsConsoleMode())
		Console_Print("DefaultHeapInitialAllocMB >> `%f", arResult);
	return true;
}

bool Cmd_EditorIDToFormID_Execute(COMMAND_ARGS) {
	arResult = 0;
	char cEDID[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cEDID) && cEDID[0]) {
		const TESForm* pForm = TESForm::GetFormByEditorID(cEDID);
		if (pForm)
			ScriptUtils::SetFormIDResult(arResult, pForm->GetFormID());

		if (IsConsoleMode())
			Console_Print("EditorIDToFormID >> 0x%08X", arResult);
	}
	return true;
}

bool Cmd_RefAddr_Execute(COMMAND_ARGS) {
	TESForm* pForm = nullptr;
	if (apRef) 
		Console_Print("0x%08X", apRef);
	else if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm) && pForm)
		Console_Print("0x%08X", pForm);
	return true;
}

bool Cmd_RefAddrxData_Execute(COMMAND_ARGS) {
	uint32_t uiType;
	if (apRef && ExtractArgsEx(EXTRACT_ARGS_EX, &uiType)) {
		if (uiType < EXTRA_DATA_TYPE::COUNT) {
			BSExtraData* pData = apRef->GetExtraData(uiType);
			if (pData)
				Console_Print("0x%08X", pData);
			else
				Console_Print("Not found");
		}
	}
	return true;
}

bool Cmd_AsmBreak_Execute(COMMAND_ARGS) {
	__asm int 3
	return true;
}

SPEC_NOINLINE bool Cmd_GetTimePlayed_Eval(COMMAND_ARGS_EVAL) {
	const uint32_t uiType = reinterpret_cast<uint32_t>(apParam1);
	const DWORD dwTickCount = GetTickCount();
	const double dTimePlayed = dwTickCount - dwGameStartTimestamp;
	switch (uiType) {
	case 0:
		arResult = dTimePlayed;
		break;
	case 1:
		arResult = dTimePlayed / 1000;
		break;
	case 2:
		arResult = dTimePlayed / 60000;
		break;
	default:
		arResult = 0;
		break;
	}
	return true;
}

bool Cmd_GetTimePlayed_Execute(COMMAND_ARGS) {
	uint32_t uiType = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &uiType);
	Cmd_GetTimePlayed_Eval(nullptr, reinterpret_cast<void*>(uiType), nullptr, arResult);
	if (IsConsoleMode())
		Console_Print("GetTimePlayed >> %f", arResult);
	return true;
}


SPEC_NOINLINE bool Cmd_GetJohnnyPatch_Eval(COMMAND_ARGS_EVAL) {
	const uint32_t uiPatch = reinterpret_cast<uint32_t>(apParam1);
	bool bEnabled = false;
	switch (uiPatch) {
		case 1:
			bEnabled = true; // EditorIDs
			break;
		case 3:
			bEnabled = JohnnyPatches::bFixFleeing;
			break;
		case 4:
			bEnabled = JohnnyPatches::bFixItemStacks;
			break;
		case 5:
			bEnabled = JohnnyPatches::bFixNPCShootingAngle;
			break;
		case 6:
			bEnabled = JohnnyPatches::bNoMuzzleFlashCooldown;
			break;
		case 7:
			bEnabled = JohnnyPatches::bResetVanityCam;
			break;
		case 8:
			bEnabled = JohnnyPatches::bFixJIP && JIPUtils::IsValid();
			break;
		default:
			break;
	}
	arResult = bEnabled;
	return true;
}

bool Cmd_GetJohnnyPatch_Execute(COMMAND_ARGS) {
	arResult = 0;
	uint32_t uiPatch = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiPatch)) {
		Cmd_GetJohnnyPatch_Eval(nullptr, reinterpret_cast<void*>(uiPatch), nullptr, arResult);
		if (IsConsoleMode())
			Console_Print("GetJohnnyPatch %d >> %d", uiPatch, arResult);
	}
	return true;
}

bool Cmd_GetEditorID_Execute(COMMAND_ARGS) {
	TESForm* pForm = nullptr;
	const char* pEDID = "";
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &pForm)) {
		if (!pForm)
			pForm = apRef;

		if (pForm)
			pEDID = pForm->GetFormEditorID();

		g_strInterface->Assign(PASS_COMMAND_ARGS, pEDID);

		if (IsConsoleMode())
			Console_Print("GetEditorID >> %s", pEDID);
	}
	return true;
}

bool Cmd_ExitGameAlt_Execute(COMMAND_ARGS) {
	CdeclCall(0x0703DA0); // Interface::CloseConsole
	CdeclCall(0x07D0A70); // StartMenu::ChooseMainMenu
	return true;
}

bool Cmd_SetOptionalBone_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (!apRef || !apRef->IsCharacter())
		return true;

	BIPED_BONE eIndex = BIPED_BONE::NONE;
	char cBoneName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eIndex, &cBoneName) && ScriptUtils::InRange(eIndex)) {
		const NiFixedString strBoneName = cBoneName;

		auto doUpdateBone = [eIndex, &strBoneName, &arResult](BipedAnim* apBiped) {
			if (apBiped && apBiped->pRoot && apBiped->pRoot->IsNode()) {
				NiAVObject* pObject = BSUtilities::GetObjectByName(apBiped->pRoot, strBoneName);
				if (pObject && pObject->IsNode()) {
					apBiped->kBones[eIndex].pParent = static_cast<NiNode*>(pObject);
					arResult = 1;
				}
			}
		};

		doUpdateBone(static_cast<Character*>(apRef)->pBipedAnim);
		if (apRef == PlayerCharacter::GetSingleton())
			doUpdateBone(static_cast<PlayerCharacter*>(apRef)->p1stPersonBipedAnim);
	}
	return true;
}

bool Cmd_GetOptionalBone_Execute(COMMAND_ARGS) {
	arResult = 0;
	if (!apRef || !apRef->IsCharacter())
		return true;

	BIPED_BONE eIndex = BIPED_BONE::NONE;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eIndex) && ScriptUtils::InRange(eIndex)) {
		BipedAnim* pBiped = static_cast<Character*>(apRef)->pBipedAnim;
		if (pBiped && pBiped->kBones[eIndex].pParent && pBiped->kBones[eIndex].pParent->IsNode()) {
			g_strInterface->Assign(PASS_COMMAND_ARGS, pBiped->kBones[eIndex].pParent->GetName());
			if (IsConsoleMode())
				Console_Print("GetOptionalBone >> %s", pBiped->kBones[eIndex].pParent->GetName().c_str());
		}
	}
	return true;
}

bool Cmd_TriggerScreenSplatterEx_Execute(COMMAND_ARGS) {
	uint32_t uiCount = 0;
	uint32_t uiNoFade = 0;
	float fDuration = 0.f;
	float fSizeMult = 0.f;
	float fOpacityMult = 0.f;


	char cTexturePath0[MAX_PATH] = {};
	char cTexturePath1[MAX_PATH] = {};
	char cTexturePath2[MAX_PATH] = {};

	NiSourceTexture* pAlphaTex = nullptr;
	NiSourceTexture* pColorTex = nullptr;
	NiSourceTexture* pFlareTex = nullptr;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiCount, &fDuration, &fSizeMult, &fOpacityMult, &cTexturePath0, &cTexturePath1, &cTexturePath2, &uiNoFade)) {
		TES* pTES = TES::GetSingleton();
		pTES->CreateTextureImage(cTexturePath0, pAlphaTex, false, false);
		pTES->CreateTextureImage(cTexturePath1, pColorTex, false, false);
		pTES->CreateTextureImage(cTexturePath2, pFlareTex, false, false);
		*(bool*)0x11C77E9 = uiNoFade;

		ScreenCustomSplatter::ActivateAlt(uiCount, fDuration, fSizeMult, fOpacityMult, pAlphaTex, pColorTex, pFlareTex);
		arResult = 1;
		return true;
	}
	arResult = 0;
	return false;
}

bool Cmd_SetViewmodelClipDistance_Execute(COMMAND_ARGS) {
	float fDistance = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fDistance)) {
		JohnnyPatches::fViewmodelNearDistance = fDistance;
		arResult = 1;
	}
	return true;
}

bool Cmd_GetViewmodelClipDistance_Execute(COMMAND_ARGS) {
	arResult = JohnnyPatches::fViewmodelNearDistance;
	if (IsConsoleMode()) 
		Console_Print("GetViewmodelClipDistance >> %.3f", arResult);
	return true;
}

bool Cmd_SetCameraTranslate_Execute(COMMAND_ARGS) {
	BOOL bOverride = FALSE;
	NiPoint3 kNewPos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bOverride, &kNewPos.x, &kNewPos.y, &kNewPos.z))
		CameraOverride::OverridePos(bOverride > 0, kNewPos);
	return true;
}

bool Cmd_SetCameraRotate_Execute(COMMAND_ARGS) {
	CameraOverride::CameraRotationType eRotType = CameraOverride::CameraRotationType::ROTATE_NONE;
	BOOL bOverride = FALSE;
	float fAngle = 0.f;
	const TESObjectREFR* pRef = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &bOverride, &eRotType, &fAngle, &pRef))
		CameraOverride::OverrideRot(bOverride > 0, eRotType, fAngle, pRef);
	return true;
}

bool Cmd_ar_Shuffle_Execute(COMMAND_ARGS) {
	NVSEArrayVar* outArr = g_arrInterface->CreateArray(NULL, 0, apScript);
	uint32_t arrID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID))
		return true;

	NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
	if (!inArr) 
		return true;

	if (g_arrInterface->GetContainerType(inArr) != NVSEArrayVarInterface::kArrType_Array) 
		return true;

	std::random_device rd;
	std::mt19937 gen(rd());
	auto lAr_Size = g_arrInterface->GetArraySize(inArr);
	if (lAr_Size < 1) 
		return true;

	BSScrapBuffer<NVSEArrayElement> kElements(lAr_Size);
	g_arrInterface->GetElements(inArr, kElements.get(), NULL);
	for (auto iCounter = (lAr_Size - 1); iCounter >= 1; iCounter--) {
		std::uniform_int_distribution<> distrib(1, iCounter);
		int32_t iPicker = distrib(gen);
		if (iPicker < iCounter) {
			NVSEArrayElement bufferElement = kElements[iPicker];
			kElements[iPicker] = kElements[iCounter];
			kElements[iCounter] = bufferElement;
		}
	}

	for (uint32_t i = 0; i < lAr_Size; i++) {
		g_arrInterface->AppendElement(outArr, NVSEArrayElement(kElements[i]));
	}
	
	g_arrInterface->AssignCommandResult(outArr, &arResult);
	return true;
}

bool Cmd_GetCurrentSkyColor_Execute(COMMAND_ARGS) {
	arResult = 0;
	ScriptVar* pRed = nullptr;
	ScriptVar* pGreen = nullptr;
	ScriptVar* pBlue = nullptr;
	uint32_t eColorType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eColorType, &pRed, &pGreen, &pBlue) && eColorType >= Sky::SkyColor::SKY_UPPER && eColorType < Sky::SkyColor::COUNT) {
		ASSUME_ASSERT(pRed && pGreen && pBlue);
		const Sky* pSky = Sky::GetSingleton();
		const NiColor& rColor = pSky->kColors[eColorType];
		pRed->data = rColor.r;
		pGreen->data = rColor.g;
		pBlue->data = rColor.b;
		if (IsConsoleMode()) 
			Console_Print("GetCurrentSkyColor %d >> %f %f %f", eColorType, rColor.r, rColor.g, rColor.b);
		arResult = 1;
	}
	return true;
}

void __fastcall StopAnimLoop(Animation* apAnimation, uint32_t aiGroup) {
	if (aiGroup == -1) {
		for (uint32_t i = 0; i < 8; ++i) {
			apAnimation->uiLoopCounts[i] = 0;
		}
	}
	else {
		apAnimation->uiLoopCounts[aiGroup] = 0;
	}
}

bool Cmd_StopIdleLoop_Execute(COMMAND_ARGS) {
	int32_t eGroup = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eGroup)) {
		if (eGroup != -1 && (eGroup < 0 || eGroup > 7))
			return true;

		if (apRef == PlayerCharacter::GetSingleton()) {
			PlayerCharacter* pPlayer = static_cast<PlayerCharacter*>(apRef);
			Animation* pAnimation = pPlayer->GetAnimation(true);
			if (pAnimation) {
				StopAnimLoop(pAnimation, eGroup);
				arResult = 1;
			}
			pAnimation = pPlayer->GetAnimation(false);
			if (pAnimation) {
				StopAnimLoop(pAnimation, eGroup);
				arResult = 1;
			}
		}
		else {
			Animation* pAnimation = apRef->GetAnimation();
			if (pAnimation) {
				StopAnimLoop(pAnimation, eGroup);
				arResult = 1;
			}
		}
	}
	return true;
}
#endif