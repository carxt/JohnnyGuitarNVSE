#include "fn_utility.h"
#include "Bethesda/BSUtilities.hpp"
#include <JG/ExtraUISounds.hpp>
#include <JG/ExtraReputationIcons.hpp>
#include <JG/JohnnyPatches.hpp>
#include <shared/BSMemory/BSScrapMemory.hpp>
#include "GameProcess.h"
#include <GameUI.h>
#include <misc/misc.h>
#include <decoding.h>
#include <JG/CameraOverride.hpp>
#include <JG/JohnnyRadios.hpp>
#include <JG/DisabledLevelUp.hpp>
#include <JIP/JIPUtils.hpp>
#include <random>

extern uint32_t g_initialTickCount;

bool Cmd_GameGetSecondsPassed_Eval(COMMAND_ARGS_EVAL) {
	*result = ThisCall<float>(0x07013E0, (void*)0x11F6394);
	return true;
}

bool Cmd_GameGetSecondsPassed_Execute(COMMAND_ARGS) {
	Cmd_GameGetSecondsPassed_Eval(thisObj, 0, 0, result);
	if (IsConsoleMode()) {
		Console_Print("GameGetSecondsPassed >> %0.2f", *result);
	}
	return true;
}

bool Cmd_NullNoArgs_Execute(COMMAND_ARGS) {
	*result = 0;
	return true;
}

bool Cmd_NullArgs_Execute(COMMAND_ARGS) {
	*result = 0;
	return true;
}


bool Cmd_GetAllGameRadios_Execute(COMMAND_ARGS) {
	NVSEArrayVar* radioArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	tList<TESObjectACTI>* g_gameRadios = (tList<TESObjectACTI>*)0x11C8264;
	for (auto radioIter = g_gameRadios->Begin(); !radioIter.End(); radioIter.Next()) {
		if (*radioIter) {
			g_arrInterface->AppendElement(radioArr, NVSEArrayElement(*radioIter));
		}
	}
	g_arrInterface->AssignCommandResult(radioArr, result);
	return true;
}


bool Cmd_GetAvailableRadios_Execute(COMMAND_ARGS) {
	NVSEArrayVar* radioArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	tList<TESObjectACTI> availableRadios = {};
	CdeclCall<void>(0x04FF1A0, thisObj, &availableRadios, nullptr);
	for (auto radioIter = availableRadios.Begin(); !radioIter.End(); radioIter.Next()) {
		if (*radioIter && !CdeclCall<bool>(0x0079BE30, *radioIter) && JohnnyRadios::IsAvailable((*radioIter)->GetFormID())) {
			g_arrInterface->AppendElement(radioArr, NVSEArrayElement(*radioIter));
		}
	}
	g_arrInterface->AssignCommandResult(radioArr, result);
	return true;
}

bool Cmd_RollCredits_Execute(COMMAND_ARGS) {
	*result = 0;
	ThisCall(0x75F2A0, nullptr);
	return true;
}

bool Cmd_DumpIconMap_Execute(COMMAND_ARGS) {
	ExtraReputationIcons::Dump();
	return true;
}

bool Cmd_UpdateCrosshairPrompt_Execute(COMMAND_ARGS) {
	*result = 0;
	ThisCall(0x778B10, nullptr);
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
	*result = 0;
	uint32_t stopAnim = 0;
	Actor* actor = (Actor*)thisObj;
	ExtractArgsEx(EXTRACT_ARGS_EX, &stopAnim);
	if (actor && actor->IsActor() && actor->baseProcess->GetIdleForm350()) {
		actor->baseProcess->ResetQueuedIdleFlags();
		actor->baseProcess->SetIdleForm350(nullptr);
		if (stopAnim > 0) ThisCall(0x498910, actor->GetAnimation(), 1, 1); // SpecialIdleFree
		*result = 1;
	}
	return true;
}

bool Cmd_IsDLLLoaded_Execute(COMMAND_ARGS) {
	*result = 0;
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
				if (strstr(dllPath, fnvPath) != nullptr) *result = 1;
			}
			else {
				*result = 1;
			}
		}
		if (IsConsoleMode()) Console_Print("IsDLLLoaded \"%s\" >> %.f", dllName, *result);
	}
	return true;
}

bool Cmd_ar_IsFormInList_Execute(COMMAND_ARGS) {
	*result = 0;
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
					*result = 1;
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
		*result = 1;
	}

	return true;
}

bool Cmd_SetUIUpdateSound_Execute(COMMAND_ARGS) {
	*result = 0;
	TESSound* sound = nullptr;
	uint32_t type = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sound, &type) && sound && type >= 1 && type <= 4 && IS_TYPE(sound, TESSound)) {
		ExtraUISounds::SetSound(sound, type);
		*result = 1;
		
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
	*result = 0;
	uint32_t arrID;
	uint32_t isReverse = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID, &isReverse)) return true;
	NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
	if (!inArr) return true;
	NVSEArrayVar* outArr = g_arrInterface->CreateArray(nullptr, 0, scriptObj);
	uint32_t size = g_arrInterface->GetArraySize(inArr);
	BSScrapBuffer<NVSEArrayElement> elements(size);
	g_arrInterface->GetElements(inArr, elements.get(), nullptr);
	std::map<const char*, TESForm*, cmp_str> smap(cmp_str(isReverse > 0));
	for (uint32_t i = 0; i < size; i++) {
		if (elements[i].GetTESForm() == nullptr) return true;
		smap.insert(std::pair<const char*, TESForm*>(elements[i].GetTESForm()->GetFormEditorID(), elements[i].GetTESForm()));
	}
	for (std::map<const char*, TESForm*>::iterator it = smap.begin(); it != smap.end(); ++it) {
		g_arrInterface->AppendElement(outArr, NVSEArrayElement(it->second));
	}

	g_arrInterface->AssignCommandResult(outArr, result);
	return true;
}

bool Cmd_GetSequenceAnimGroup_Eval(COMMAND_ARGS_EVAL) {
	*result = -1;
	const uint32_t uiSequence = reinterpret_cast<uint32_t>(arg1);
	if (thisObj && uiSequence < 8) {
		const Animation* pAnim = thisObj->GetAnimation();
		if (pAnim && pAnim->animSequence[uiSequence]) {
			uint16_t usGroupID = pAnim->groupIDs[uiSequence] & 0xFF;
			*result = usGroupID;
		}
	}

	return true;
}

bool Cmd_GetSequenceAnimGroup_Execute(COMMAND_ARGS) {
	*result = -1;
	uint32_t uiSequence;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiSequence))
		Cmd_GetSequenceAnimGroup_Eval(thisObj, reinterpret_cast<void*>(uiSequence), nullptr, result);

	return true;
}

bool Cmd_GetFormOverrideIndex_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form = nullptr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form) && form) {
		TESFile* pFile = form->GetFile(-1);
		if (pFile)
			*result = pFile->ucCompileIndex;
		else
			*result = 0xFF;
		if (IsConsoleMode()) Console_Print("GetFormOverrideIndex >> %.f", *result);
	}
	return true;
}

bool Cmd_GetPipBoyMode_Eval(COMMAND_ARGS_EVAL) {
	*result = 0;
	if (InterfaceManager::GetSingleton())
		*result = InterfaceManager::GetSingleton()->pipBoyMode;
	return true;
}

bool Cmd_GetPipBoyMode_Execute(COMMAND_ARGS) {
	Cmd_GetPipBoyMode_Eval(nullptr, nullptr, nullptr, result);
	if (IsConsoleMode())
		Console_Print("GetPipBoyMode >> %.2f", *result);
	return true;
}

bool Cmd_GetLinearVelocity_Execute(COMMAND_ARGS) {
	char X_outS[VAR_NAME_SIZE] = {}, Y_outS[VAR_NAME_SIZE] = {}, Z_outS[VAR_NAME_SIZE] = {};
	char nodeName[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName, &X_outS, &Y_outS, &Z_outS)) {
		hkpRigidBody* rigidBody = thisObj->GetRigidBody(nodeName);
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
	uint32_t heapSize = *(reinterpret_cast<uint32_t*>(0x866E9F + 1));
	*result = heapSize / 1024 / 1024;
	if (IsConsoleMode())
		Console_Print("DefaultHeapInitialAllocMB >> `%f", *result);
	return true;
}

bool Cmd_EditorIDToFormID_Execute(COMMAND_ARGS) {
	*result = 0;
	char cEDID[MAX_PATH] = {};
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cEDID) && cEDID[0]) {
		const TESForm* pForm = TESForm::GetFormByEditorID(cEDID);
		if (pForm)
			*reinterpret_cast<uint32_t*>(result) = pForm->GetFormID();

		if (IsConsoleMode())
			Console_Print("EditorIDToFormID >> 0x%08X", *result);
	}
	return true;
}

bool Cmd_RefAddr_Execute(COMMAND_ARGS) {
	TESForm* form = nullptr;
	if (thisObj) Console_Print("0x%08X", thisObj);
	else if (ExtractArgsEx(EXTRACT_ARGS_EX, &form) && form) Console_Print("0x%08X", form);
	return true;
}

bool Cmd_RefAddrxData_Execute(COMMAND_ARGS) {
	TESForm* form = nullptr;
	DWORD type;
	if (thisObj && ExtractArgsEx(EXTRACT_ARGS_EX, &type)) {
		if (type < EXTRA_DATA_TYPE::COUNT) {
			void* res = thisObj->extraDataList.GetExtraData(type);
			if (res) {
				Console_Print("0x%08X", res);
				return true;
			}
		}
		Console_Print("Not found");
	}
	return true;
}

bool Cmd_AsmBreak_Execute(COMMAND_ARGS) {
	__asm int 3
	return true;
}

bool Cmd_GetTimePlayed_Eval(COMMAND_ARGS_EVAL) {
	uint32_t uiTtype = reinterpret_cast<uint32_t>(arg1);
	DWORD dwTickCount = GetTickCount();
	double dTimePlayed = dwTickCount - g_initialTickCount;
	switch (uiTtype) {
	case 0:
		*result = dTimePlayed;
		break;
	case 1:
		*result = dTimePlayed / 1000;
		break;
	case 2:
		*result = dTimePlayed / 60000;
		break;
	default:
		*result = 0;
		break;
	}
	return true;
}

bool Cmd_GetTimePlayed_Execute(COMMAND_ARGS) {
	uint32_t uiTtype = 0;
	ExtractArgsEx(EXTRACT_ARGS_EX, &uiTtype);
	Cmd_GetTimePlayed_Eval(nullptr, reinterpret_cast<void*>(uiTtype), nullptr, result);
	if (IsConsoleMode())
		Console_Print("GetTimePlayed >> %f", *result);
	return true;
}


bool Cmd_GetJohnnyPatch_Eval(COMMAND_ARGS_EVAL) {
	using namespace JohnnyPatches;
	uint32_t uiPatch = reinterpret_cast<uint32_t>(arg1);
	bool bEnabled = false;
	switch (uiPatch) {
		case 1:
			bEnabled = true;
			break;
		case 3:
			bEnabled = fixFleeing;
			break;
		case 4:
			bEnabled = fixItemStacks;
			break;
		case 5:
			bEnabled = fixNPCShootingAngle;
			break;
		case 6:
			bEnabled = noMuzzleFlashCooldown;
			break;
		case 7:
			bEnabled = resetVanityCam;
			break;
		case 8:
			bEnabled = bFixJIP && JIPUtils::IsValid();
			break;
		default:
			break;
	}
	*result = bEnabled;
	return true;
}

bool Cmd_GetJohnnyPatch_Execute(COMMAND_ARGS) {
	*result = 0;
	uint32_t uiPatch = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &uiPatch)) {
		Cmd_GetJohnnyPatch_Eval(nullptr, reinterpret_cast<void*>(uiPatch), nullptr, result);
		if (IsConsoleMode())
			Console_Print("GetJohnnyPatch %d >> %d", uiPatch, *result);
	}
	return true;
}

bool Cmd_GetEditorID_Execute(COMMAND_ARGS) {
	TESForm* form = nullptr;
	const char* edid = "";
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		if (!form)
			form = thisObj;
		if (form)
			edid = form->GetFormEditorID();
		g_strInterface->Assign(PASS_COMMAND_ARGS, edid);
		if (IsConsoleMode())
			Console_Print("GetEditorID >> %s", edid);
	}
	return true;
}

bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS) {
	*result = DisabledLevelUp::isShowLevelUp;
	if (IsConsoleMode()) Console_Print("IsLevelUpMenuEnabled >> %.f", *result);
	return true;
}

bool Cmd_ExitGameAlt_Execute(COMMAND_ARGS) {
	ThisCall(0x0703DA0, nullptr);
	ThisCall(0x07D0A70, nullptr);
	return true;
}

bool Cmd_SetOptionalBone_Execute(COMMAND_ARGS) {
	uintptr_t optIdx = -1;
	*result = 0;
	char boneName[MAX_PATH] = { 0 };
	if (ExtractArgsEx(EXTRACT_ARGS_EX, optIdx, &boneName)) {
		if (optIdx > 4) return true;
		auto doUpdateBone = [optIdx, &boneName, &result](BipedAnim* BipedAnim) {
			if (BipedAnim) {
				if (BipedAnim->pRoot && BipedAnim->pRoot->IsNode()) {
					auto vb = CdeclCall<NiNode*>(0x04AAE30, BipedAnim->pRoot, boneName);
					if (vb && vb->IsNode()) {
						BipedAnim->kBones[optIdx].pParent = vb;
						*result = 1;
					}
				}
			}
			};
		if (thisObj && thisObj->IsCharacter()) {
			doUpdateBone(((Character*)thisObj)->pBipedAnim);
			if (thisObj == PlayerCharacter::GetSingleton()) {
				doUpdateBone(((PlayerCharacter*)thisObj)->p1stPersonBipedAnim);
			}
		}
	}
	return true;
}

bool Cmd_GetOptionalBone_Execute(COMMAND_ARGS) {
	uintptr_t optIdx = -1;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &optIdx)) {
		if (thisObj && thisObj->IsCharacter() && optIdx <= 4)
			if (auto BipedAnim = ((Character*)thisObj)->pBipedAnim) {
				if (BipedAnim->kBones[optIdx].pParent && BipedAnim->kBones[optIdx].pParent->IsNode()) {
					g_strInterface->Assign(PASS_COMMAND_ARGS, BipedAnim->kBones[optIdx].pParent->m_kName);
					if (IsConsoleMode())
						Console_Print("GetOptionalBone >> %s", BipedAnim->kBones[optIdx].pParent->m_kName);
				}
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
		*result = 1;
		return true;
	}
	*result = 0;
	return false;
}

bool Cmd_SetViewmodelClipDistance_Execute(COMMAND_ARGS) {
	float fDistance = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fDistance)) {
		JohnnyPatches::g_viewmodel_near = fDistance;
		*result = 1;
	}
	return true;
}

bool Cmd_GetViewmodelClipDistance_Execute(COMMAND_ARGS) {
	*result = JohnnyPatches::g_viewmodel_near;
	if (IsConsoleMode()) Console_Print("GetViewmodelClipDistance >> %.3f", *result);
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
	NVSEArrayVar* outArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	uint32_t arrID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) return true;
	NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
	if (!inArr) return true;
	if (g_arrInterface->GetContainerType(inArr) != NVSEArrayVarInterface::kArrType_Array) return true;
	std::random_device rd;
	std::mt19937 gen(rd());
	auto lAr_Size = g_arrInterface->GetArraySize(inArr);
	if (lAr_Size < 1) return true;
	BSScrapBuffer<NVSEArrayElement> elements(lAr_Size);
	g_arrInterface->GetElements(inArr, elements.get(), NULL);
	for (auto iCounter = (lAr_Size - 1); iCounter >= 1; iCounter--)
	{
		std::uniform_int_distribution<> distrib(1, iCounter);
		auto iPicker = distrib(gen);
		if (iPicker < iCounter)
		{
			NVSEArrayElement bufferElement;
			bufferElement = elements[iPicker];
			elements[iPicker] = elements[iCounter];
			elements[iCounter] = bufferElement;
		}
	}
	for (uint32_t i = 0; i < lAr_Size; i++) {
		g_arrInterface->AppendElement(outArr, NVSEArrayElement(elements[i]));
	}
	g_arrInterface->AssignCommandResult(outArr, result);
	return true;
}

bool Cmd_GetCurrentSkyColor_Execute(COMMAND_ARGS) {
	*result = 0;
	ScriptVar* pRed = nullptr;
	ScriptVar* pGreen = nullptr;
	ScriptVar* pBlue = nullptr;
	uint32_t eColorType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &eColorType, &pRed, &pGreen, &pBlue) && eColorType >= Sky::SC_SKY_UPPER && eColorType < Sky::SC_COUNT) {
		ASSUME_ASSERT(pRed && pGreen && pBlue);
		const Sky* pSky = Sky::GetSingleton();
		const NiColor& rColor = pSky->kColors[eColorType];
		pRed->data = rColor.r;
		pGreen->data = rColor.g;
		pBlue->data = rColor.b;
		if (IsConsoleMode()) 
			Console_Print("GetCurrentSkyColor %d >> %f %f %f", eColorType, rColor.r, rColor.g, rColor.b);
		*result = 1;
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

		if (thisObj == PlayerCharacter::GetSingleton()) {
			PlayerCharacter* pPlayer = static_cast<PlayerCharacter*>(thisObj);
			Animation* pAnimation = pPlayer->GetAnimation(true);
			if (pAnimation) {
				StopAnimLoop(pAnimation, eGroup);
				*result = 1;
			}
			pAnimation = pPlayer->GetAnimation(false);
			if (pAnimation) {
				StopAnimLoop(pAnimation, eGroup);
				*result = 1;
			}
		}
		else {
			Animation* pAnimation = thisObj->GetAnimation();
			if (pAnimation) {
				StopAnimLoop(pAnimation, eGroup);
				*result = 1;
			}
		}

	}
	return true;
}