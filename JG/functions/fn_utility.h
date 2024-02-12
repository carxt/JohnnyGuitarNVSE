#pragma once
// Utility or miscellaneous functions
#include <iostream>
#include <fstream>
DEFINE_COMMAND_ALT_PLUGIN(GetEditorID, GetEdID, , 0, 1, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetJohnnyPatch, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetTimePlayed, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(AsmBreak, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(RefAddr, , 0, 1, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(EditorIDToFormID, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetDefaultHeapSize, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetLinearVelocity, , 1, 4, kParams_FourStrings);
DEFINE_COMMAND_PLUGIN(IsLevelUpMenuEnabled, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetPipBoyMode, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetFormOverrideIndex, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetSequenceAnimGroup, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(ar_SortEditor, , 0, 2, kParams_OneInt_OneOptionalInt)
DEFINE_COMMAND_PLUGIN(SetUIUpdateSound, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(ar_IsFormInList, , 0, 3, kParams_OneInt_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(IsDLLLoaded, , 0, 2, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(RefreshIdle, , 1, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(ExitGameAlt, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(DumpINI, , 0, 0, NULL);
DEFINE_CMD_NO_ARGS(UpdateCrosshairPrompt);
DEFINE_COMMAND_PLUGIN(SetOptionalBone, , 1, 2, kParams_OneInt_OneString);
DEFINE_COMMAND_PLUGIN(GetOptionalBone, , 1, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(TriggerScreenSplatterEx, , 0, 8, kSplatterParams);
DEFINE_COMMAND_PLUGIN(SetViewmodelClipDistance, , 0, 1, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(GetViewmodelClipDistance, , 0, 0, NULL);
DEFINE_CMD_NO_ARGS(DumpIconMap);
DEFINE_CMD_NO_ARGS(RollCredits);
bool Cmd_RollCredits_Execute(COMMAND_ARGS) {
	*result = 0;
	ThisStdCall<void>(0x75F2A0, nullptr);
	return true;
}

bool Cmd_DumpIconMap_Execute(COMMAND_ARGS) {
	auto it = factionRepIcons.begin();
	for (auto const& it : factionRepIcons) {
		Console_Print("0x%X - %s %s %s %s", it.first, it.second[0], it.second[1], it.second[2], it.second[3]);
	}
	return true;
}

bool Cmd_UpdateCrosshairPrompt_Execute(COMMAND_ARGS) {
	*result = 0;
	ThisStdCall<void>(0x778B10, NULL);
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
bool Cmd_DumpINI_Execute(COMMAND_ARGS) {
	IniSettingCollection* ini = IniSettingCollection::GetIniSettings();
	IniSettingCollection* prefs = IniSettingCollection::GetIniPrefs();
	IniSettingCollection* renderer = *(IniSettingCollection**)0x11F35A4;
	IniSettingCollection* blend = *(IniSettingCollection**)0x11CC694;
	std::ofstream csv;
	csv.open("settings.csv");
	Setting* setting;
	csv << "fallout.ini" << std::endl;
	ListNode<Setting>* istIter = ini->settings.Head();
	do {
		setting = istIter->data;
		if (setting && setting->ValidType()) {
			std::string name = setting->name;
			if (name.find("i") != std::string::npos) {
				std::string sname = name.substr(0, name.find(":"));
				std::string cat = name.substr(name.find(":") + 1);
				switch (setting->GetType()) {
					case kSetting_Bool:
					case kSetting_Integer:
						csv << sname << ";" << cat << ";" << setting->data.i << std::endl;
						break;
					case kSetting_Unsigned:
						csv << sname << ";" << cat << ";" << setting->data.uint << std::endl;
						break;
					case kSetting_String:
						csv << sname << ";" << cat << ";" << setting->data.str << std::endl;
						break;
					case kSetting_Float:
						csv << sname << ";" << cat << ";" << setting->data.f << std::endl;
						break;
				}
			}
		}
	} while (istIter = istIter->next);
	csv << "falloutprefs.ini" << std::endl;
	istIter = prefs->settings.Head();
	do {
		setting = istIter->data;
		if (setting && setting->ValidType()) {
			std::string name = setting->name;
			if (name.find("i") != std::string::npos) {
				std::string sname = name.substr(0, name.find(":"));
				std::string cat = name.substr(name.find(":") + 1);
				switch (setting->GetType()) {
					case kSetting_Bool:
					case kSetting_Integer:
						csv << sname << ";" << cat << ";" << setting->data.i << std::endl;
						break;
					case kSetting_Unsigned:
						csv << sname << ";" << cat << ";" << setting->data.uint << std::endl;
						break;
					case kSetting_String:
						csv << sname << ";" << cat << ";" << setting->data.str << std::endl;
						break;
					case kSetting_Float:
						csv << sname << ";" << cat << ";" << setting->data.f << std::endl;
						break;
				}
			}
		}
	} while (istIter = istIter->next);
	istIter = renderer->settings.Head();
	do {
		setting = istIter->data;
		if (setting && setting->ValidType()) {
			std::string name = setting->name;
			if (name.find("i") != std::string::npos) {
				std::string sname = name.substr(0, name.find(":"));
				std::string cat = name.substr(name.find(":") + 1);
				switch (setting->GetType()) {
					case kSetting_Bool:
					case kSetting_Integer:
						csv << sname << ";" << cat << ";" << setting->data.i << std::endl;
						break;
					case kSetting_Unsigned:
						csv << sname << ";" << cat << ";" << setting->data.uint << std::endl;
						break;
					case kSetting_String:
						csv << sname << ";" << cat << ";" << setting->data.str << std::endl;
						break;
					case kSetting_Float:
						csv << sname << ";" << cat << ";" << setting->data.f << std::endl;
						break;
				}
			}
		}
	} while (istIter = istIter->next);
	istIter = blend->settings.Head();
	do {
		setting = istIter->data;
		if (setting && setting->ValidType()) {
			std::string name = setting->name;
			if (name.find("i") != std::string::npos) {
				std::string sname = name.substr(0, name.find(":"));
				std::string cat = name.substr(name.find(":") + 1);
				switch (setting->GetType()) {
					case kSetting_Bool:
					case kSetting_Integer:
						csv << sname << ";" << cat << ";" << setting->data.i << std::endl;
						break;
					case kSetting_Unsigned:
						csv << sname << ";" << cat << ";" << setting->data.uint << std::endl;
						break;
					case kSetting_String:
						csv << sname << ";" << cat << ";" << setting->data.str << std::endl;
						break;
					case kSetting_Float:
						csv << sname << ";" << cat << ";" << setting->data.f << std::endl;
						break;
				}
			}
		}
	} while (istIter = istIter->next);
	csv.close();
	return true;
}

bool Cmd_RefreshIdle_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 stopAnim = 0;
	Actor* actor = (Actor*)thisObj;
	ExtractArgsEx(EXTRACT_ARGS_EX, &stopAnim);
	if (actor->baseProcess->GetIdleForm350()) {
		actor->baseProcess->ResetQueuedIdleFlags();
		actor->baseProcess->SetIdleForm350(NULL);
		if (stopAnim > 0) ThisStdCall(0x498910, actor->GetAnimData(), 1, 1); // SpecialIdleFree
		*result = 1;
	}
	return true;
}
bool Cmd_IsDLLLoaded_Execute(COMMAND_ARGS) {
	*result = 0;
	int checkOutsideOfGameFolder = 0;
	char dllName[MAX_PATH];
	char dllPath[MAX_PATH];
	char fnvPath[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &dllName, &checkOutsideOfGameFolder)) {
		strncat(dllName, ".dll", 4);
		HMODULE module = GetModuleHandle(dllName);
		if (module) {
			if (!checkOutsideOfGameFolder) {
				GetModuleFileNameA(module, dllPath, MAX_PATH);
				GetModuleFileNameA(NULL, fnvPath, MAX_PATH);
				fnvPath[strlen(fnvPath) - 13] = '\0';
				if (strstr(dllPath, fnvPath) != NULL) *result = 1;
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
	UInt32 arrID, fullMatch;
	BGSListForm* formList;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID, &formList, &fullMatch)) return true;
	NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
	if (!inArr) return true;
	UInt32 size = g_arrInterface->GetArraySize(inArr);
	NVSEArrayElement* elements = new NVSEArrayElement[size];
	g_arrInterface->GetElements(inArr, elements, NULL);
	if (!fullMatch) {
		for (int i = 0; i < size; i++) {
			if (elements[i].Form() == NULL) return true;
			ListNode<TESForm>* listIter = formList->list.Head();
			do {
				if (elements[i].Form() == listIter->data) {
					*result = 1;
					delete[] elements;
					return true;
				}
			} while (listIter = listIter->next);
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			if (elements[i].Form() == NULL) return true;
			int elementFound = 0;
			ListNode<TESForm>* listIter = formList->list.Head();
			do {
				if (elements[i].Form() == listIter->data) {
					elementFound = 1;
					break;
				}
			} while (listIter = listIter->next);
			if (elementFound == 0) {
				delete[] elements;
				return true;
			}
		}
		*result = 1;
	}

	delete[] elements;
	return true;
}
bool Cmd_SetUIUpdateSound_Execute(COMMAND_ARGS) {
	*result = 0;
	TESSound* sound;
	UInt32 type = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sound, &type) && IS_TYPE(sound, TESSound)) {
		*result = 1;
		switch (type) {
			case 1:
				questFailSound = sound;
				break;
			case 2:
				questNewSound = sound;
				break;
			case 3:
				questCompeteSound = sound;
				break;
			case 4:
				locationDiscoverSound = sound;
				break;
			default:
				*result = 0;
				break;
		}
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
	UInt32 arrID;
	UInt32 isReverse = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID, &isReverse)) return true;
	if (!loadEditorIDs) return true;
	NVSEArrayVar* inArr = g_arrInterface->LookupArrayByID(arrID);
	if (!inArr) return true;
	NVSEArrayVar* outArr = g_arrInterface->CreateArray(NULL, 0, scriptObj);
	UInt32 size = g_arrInterface->GetArraySize(inArr);
	NVSEArrayElement* elements = new NVSEArrayElement[size];
	g_arrInterface->GetElements(inArr, elements, NULL);
	std::map<char*, TESForm*, cmp_str> smap(cmp_str(isReverse > 0));
	for (int i = 0; i < size; i++) {
		if (elements[i].Form() == NULL) return true;
		smap.insert(std::pair<char*, TESForm*>(elements[i].Form()->GetName(), elements[i].Form()));
	}
	for (std::map<char*, TESForm*>::iterator it = smap.begin(); it != smap.end(); ++it) {
		g_arrInterface->AppendElement(outArr, NVSEArrayElement(it->second));
	}

	g_arrInterface->AssignCommandResult(outArr, result);
	delete[] elements;
	return true;
}
bool Cmd_GetSequenceAnimGroup_Execute(COMMAND_ARGS) {
	*result = -1;
	UInt32 sequenceID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sequenceID) && sequenceID < 8) {
		if (auto animData = thisObj->GetAnimData()) {
			if (auto sequence = animData->animSequence[sequenceID]) {
				UInt16 groupID = animData->groupIDs[sequenceID] & 0xFF;
				*result = groupID;
			}
		}
	}

	return true;
}
bool Cmd_GetFormOverrideIndex_Execute(COMMAND_ARGS) {
	*result = 0;
	TESForm* form;
	if (scriptObj && ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		UInt8 overriding = form->GetOverridingModIdx();
		*result = ((overriding > scriptObj->modIndex) ? overriding : 0);
		if (IsConsoleMode()) Console_Print("GetFormOverrideIndex >> %.f", *result);
	}
	return true;
}
bool Cmd_GetPipBoyMode_Execute(COMMAND_ARGS) {
	*result = 0;
	if (g_interfaceManager) *result = g_interfaceManager->pipBoyMode;
	if (IsConsoleMode()) Console_Print("GetPipBoyMode >> %.2f", *result);
	return true;
}

bool Cmd_GetLinearVelocity_Execute(COMMAND_ARGS) {
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	char nodeName[MAX_PATH];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName, &X_outS, &Y_outS, &Z_outS)) {
		hkpRigidBody* rigidBody = thisObj->GetRigidBody(nodeName);
		if (rigidBody) {
			NiVector4 linVelocity = rigidBody->motion.linVelocity;
			setVarByName(PASS_VARARGS, X_outS, linVelocity.x);
			setVarByName(PASS_VARARGS, Y_outS, linVelocity.y);
			setVarByName(PASS_VARARGS, Z_outS, linVelocity.z);
		}
	}
	return true;
}

bool Cmd_GetDefaultHeapSize_Execute(COMMAND_ARGS) {
	UInt32 heapSize = *(reinterpret_cast<UInt32*>(0x866E9F + 1));
	*result = heapSize / 1024 / 1024;
	if (IsConsoleMode())
		Console_Print("DefaultHeapInitialAllocMB >> `%f", *result);
	return true;
}

bool Cmd_EditorIDToFormID_Execute(COMMAND_ARGS) {
	char edid[MAX_PATH];
	TESForm* form = NULL;
	*result = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &edid)) {
		form = ((TESForm * (__cdecl*)(char*))(0x483A00))(edid); //LookupEditorID
		if (form) {
			*(UInt32*)result = form->refID;
		}
		if (IsConsoleMode()) {
			Console_Print("EditorIDToFormID >> 0x%X", *result);
		}
	}
	return true;
}

bool Cmd_RefAddr_Execute(COMMAND_ARGS) {
	TESForm* form = NULL;
	if (thisObj) Console_Print("0x%08X", thisObj);
	else if (ExtractArgsEx(EXTRACT_ARGS_EX, &form) && form) Console_Print("0x%08X", form);
	return true;
}
bool Cmd_AsmBreak_Execute(COMMAND_ARGS) {
	__asm int 3
	return true;
}

bool Cmd_GetTimePlayed_Execute(COMMAND_ARGS) {
	int type = 0;
	UInt32 tickCount;
	ExtractArgsEx(EXTRACT_ARGS_EX, &type);
	tickCount = GetTickCount();
	double timePlayed = tickCount - g_initialTickCount;
	switch (type) {
		case 0:
			*result = timePlayed;
			break;
		case 1:
			*result = timePlayed / 1000;
			break;
		case 2:
			*result = timePlayed / 60000;
			break;
	}
	if (IsConsoleMode()) {
		Console_Print("%f", *result);
	}
	return true;
}

bool Cmd_GetJohnnyPatch_Execute(COMMAND_ARGS) {
	int patch = 0;
	bool enabled = false;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &patch)) {
		switch (patch) {
			case 1:
				enabled = loadEditorIDs;
				break;
			case 2:
				enabled = fixHighNoon;
				break;
			case 3:
				enabled = fixFleeing;
				break;
			case 4:
				enabled = fixItemStacks;
				break;
			case 5:
				enabled = fixNPCShootingAngle;
				break;
			case 6:
				enabled = noMuzzleFlashCooldown;
				break;
			case 7:
				enabled = resetVanityCam;
				break;
			default:
				break;
		}
		if (IsConsoleMode())
			Console_Print("GetJohnnyPatch %d >> %d", patch, enabled);
	}
	*result = enabled;
	return true;
}

bool Cmd_GetEditorID_Execute(COMMAND_ARGS) {
	TESForm* form = nullptr;
	const char* edid = "";
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form)) {
		if (!form)
			form = thisObj;
		if (form)
			edid = form->GetName();
		g_strInterface->Assign(PASS_COMMAND_ARGS, edid);
		if (IsConsoleMode())
			Console_Print("GetEditorID >> %s", edid);
	}
	return true;
}
bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS) {
	*result = isShowLevelUp;
	if (IsConsoleMode()) Console_Print("IsLevelUpMenuEnabled >> %.f", *result);
	return true;
}

bool Cmd_ExitGameAlt_Execute(COMMAND_ARGS) {
	ThisStdCall(0x0703DA0, nullptr);
	ThisStdCall(0x07D0A70, nullptr);
	return true;
}

bool Cmd_SetOptionalBone_Execute(COMMAND_ARGS) {
	uintptr_t optIdx = -1;
	*result = 0;
	char boneName[MAX_PATH] = { 0 };
	if (ExtractArgsEx(EXTRACT_ARGS_EX, optIdx, &boneName)) {
		if (optIdx > 4) return true;
		auto doUpdateBone = [optIdx, &boneName, &result](ValidBip01Names* BipedAnim) {
			if (BipedAnim) {
				if (BipedAnim->bip01 && BipedAnim->bip01->GetNiNode()) {
					auto vb = CdeclCall<NiNode*>(0x04AAE30, BipedAnim->bip01, boneName);
					if (vb && vb->GetNiNode()) {
						BipedAnim->bones[optIdx].bone = vb;
						*result = 1;
					}
				}
			}
		};
		if (thisObj && thisObj->IsCharacter()) {
			doUpdateBone(((Character*)thisObj)->validBip01Names);
			if (thisObj == PlayerCharacter::GetSingleton()) {
				doUpdateBone(((PlayerCharacter*)thisObj)->VB01N1stPerson);
			}
		}
	}
	return true;
}

bool Cmd_GetOptionalBone_Execute(COMMAND_ARGS) {
	uintptr_t optIdx = -1;

	if (ExtractArgsEx(EXTRACT_ARGS_EX, &optIdx)) {
		if (thisObj && thisObj->IsCharacter() && optIdx <= 4)
			if (auto BipedAnim = ((Character*)thisObj)->validBip01Names) {
				if (BipedAnim->bones[optIdx].bone && BipedAnim->bones[optIdx].bone->GetNiNode()) {
					g_strInterface->Assign(PASS_COMMAND_ARGS, BipedAnim->bones[optIdx].bone->m_blockName.handle);
					if (IsConsoleMode())
						Console_Print("GetOptionalBone >> %s", BipedAnim->bones[optIdx].bone->m_blockName.handle);
				}
			}
	}
	return true;
}

bool Cmd_TriggerScreenSplatterEx_Execute(COMMAND_ARGS) {
	UInt32 uiCount = 0;
	UInt32 uiNoFade = 0;
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
		* result = 1;
		return true;
	}
	*result = 0;
	return false;
}

bool Cmd_SetViewmodelClipDistance_Execute(COMMAND_ARGS) {
	float fDistance = 0.f;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fDistance)) {
		g_viewmodel_near = max(fDistance, 0.001);
		*result = 1;
	}
	return true;
}

bool Cmd_GetViewmodelClipDistance_Execute(COMMAND_ARGS) {
	*result = g_viewmodel_near;
	if (IsConsoleMode()) Console_Print("GetViewmodelClipDistance >> %.3f", *result);
	return true;
}