#pragma once
// Utility or miscellaneous functions
DEFINE_COMMAND_PLUGIN(GetEditorID, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetJohnnyPatch, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetTimePlayed, , 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(AsmBreak, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(RefAddr, , 0, 1, kParams_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(EditorIDToFormID, , 0, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetDefaultHeapSize, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetLinearVelocity, , 1, 4, kParamsJohnnyFourStrings);
DEFINE_COMMAND_PLUGIN(IsLevelUpMenuEnabled, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetPipBoyMode, , 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetFormOverrideIndex, , 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetSequenceAnimGroup, , 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(ar_SortEditor, , 0, 2, kParams_OneInt_OneOptionalInt)
DEFINE_COMMAND_PLUGIN(SetUIUpdateSound, , 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(ar_IsFormInList, , 0, 3, kParamsJohnnyOneInt_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(IsDLLLoaded, , 0, 2, kParamsJohnny_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(RefreshIdle, , 1, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(ExitGameAlt, , 0, 0, NULL);

bool Cmd_RefreshIdle_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 stopAnim = 0;
	Actor* actor = (Actor*)thisObj;
	ExtractArgs(EXTRACT_ARGS, &stopAnim);
	if (actor->baseProcess->GetIdleForm350()) {
		actor->baseProcess->ResetQueuedIdleFlags();
		actor->baseProcess->SetIdleForm350(NULL);
		if (stopAnim > 0) ThisStdCall(0x498910, actor->GetAnimData(), 1, 1); // SpecialIdleFree
	}
	return true;
}
bool Cmd_IsDLLLoaded_Execute(COMMAND_ARGS) {
	*result = 0;
	int checkOutsideOfGameFolder = 0;
	char dllName[MAX_PATH];
	char dllPath[MAX_PATH];
	char fnvPath[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &dllName, &checkOutsideOfGameFolder)) {
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
	if (!ExtractArgs(EXTRACT_ARGS, &arrID, &formList, &fullMatch)) return true;
	NVSEArrayVar* inArr = ArrIfc->LookupArrayByID(arrID);
	if (!inArr) return true;
	UInt32 size = ArrIfc->GetArraySize(inArr);
	NVSEArrayElement* elements = new NVSEArrayElement[size];
	ArrIfc->GetElements(inArr, elements, NULL);
	if (!fullMatch) {
		for (int i = 0; i < size; i++) {
			if (elements[i].Form() == NULL) return true;
			ListNode<TESForm>* listIter = formList->list.Head();
			do
			{
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
			do
			{
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
	if (ExtractArgs(EXTRACT_ARGS, &sound, &type) && IS_TYPE(sound, TESSound)) {
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
		}
	}
	return true;
}
struct cmp_str
{
	public:
		cmp_str(bool s_) : s(s_) {};
		bool operator()(char const* a, char const* b) const
		{
			return s ? std::strcmp(a, b) > 0 : std::strcmp(a, b) < 0;
		}
	private:
		bool s;
};
bool Cmd_ar_SortEditor_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	UInt32 isReverse = 0;
	if (!ExtractArgs(EXTRACT_ARGS, &arrID, &isReverse)) return true;
	if (!loadEditorIDs) return true;
	NVSEArrayVar* inArr = ArrIfc->LookupArrayByID(arrID);
	if (!inArr) return true;
	NVSEArrayVar* outArr = ArrIfc->CreateArray(NULL, 0, scriptObj);
	UInt32 size = ArrIfc->GetArraySize(inArr);
	NVSEArrayElement* elements = new NVSEArrayElement[size];
	ArrIfc->GetElements(inArr, elements, NULL);
	std::map<char*, TESForm*, cmp_str> smap(cmp_str(isReverse > 0));
	for (int i = 0; i < size; i++) {
		if (elements[i].Form() == NULL) return true;
		smap.insert(std::pair<char*, TESForm*>(elements[i].Form()->GetName(), elements[i].Form()));
	}
	for (std::map<char*, TESForm*>::iterator it = smap.begin(); it != smap.end(); ++it) {
		ArrIfc->AppendElement(outArr, NVSEArrayElement(it->second));
	}
	
	ArrIfc->AssignCommandResult(outArr, result);
	delete[] elements;
	return true;
}
bool Cmd_GetSequenceAnimGroup_Execute(COMMAND_ARGS)
{
	*result = -1;
	UInt32 sequenceID;
	if (ExtractArgs(EXTRACT_ARGS, &sequenceID) && sequenceID < 8)
	{
		if (auto animData = thisObj->GetAnimData())
		{
			if (auto sequence = animData->animSequence[sequenceID])
			{
				UInt16 groupID = animData->groupIDs[sequenceID] & 0xFF;
				*result = groupID;
			}
		}
	}

	return true;
}
bool Cmd_GetFormOverrideIndex_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm* form;
	if (scriptObj && ExtractArgs(EXTRACT_ARGS, &form))
	{
		UInt8 overriding = form->GetOverridingModIdx();
		*result = ((overriding > scriptObj->modIndex) ? overriding : 0);
		if (IsConsoleMode) Console_Print("GetFormOverrideIndex >> %.f", *result);
	}
	return true;
}
bool Cmd_GetPipBoyMode_Execute(COMMAND_ARGS) {
	*result = 0;
	InterfaceManager* g_interfaceManager = *(InterfaceManager**)0x011D8A80;
	if (g_interfaceManager) *result = g_interfaceManager->pipBoyMode;
	if (IsConsoleMode()) Console_Print("GetPipBoyMode >> %.2f", *result);
	return true;
}

bool Cmd_GetLinearVelocity_Execute(COMMAND_ARGS) {
	char X_outS[VarNameSize], Y_outS[VarNameSize], Z_outS[VarNameSize];
	char nodeName[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &nodeName, &X_outS, &Y_outS, &Z_outS))
	{
		hkpRigidBody* rigidBody = thisObj->GetRigidBody(nodeName);
		if (rigidBody)
		{
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
	if (ExtractArgs(EXTRACT_ARGS, &edid)) {
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
	else if (ExtractArgs(EXTRACT_ARGS, &form) && form) Console_Print("0x%08X", form);
	return true;
}
bool Cmd_AsmBreak_Execute(COMMAND_ARGS) {
	__asm int 3
	return true;
}

bool Cmd_GetTimePlayed_Execute(COMMAND_ARGS) {
	int type = 0;
	UInt32 tickCount;
	ExtractArgs(EXTRACT_ARGS, &type);
	PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton();
	tickCount = ThisStdCall<UInt32>(0x457FE0, NULL);
	double timePlayed = tickCount - g_thePlayer->unk774[6];
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

bool Cmd_GetJohnnyPatch_Execute(COMMAND_ARGS)
{
	int patch = 0;
	bool enabled = false;
	if (ExtractArgs(EXTRACT_ARGS, &patch))
	{
		switch (patch) {
		case 1:
			enabled = loadEditorIDs;
			break;
		case 2:
			enabled = fixHighNoon;
			break;
		}
		if (IsConsoleMode())
			Console_Print("GetJohnnyPatch %d >> %d", patch, enabled);
	}
	*result = enabled;
	return true;
}

bool Cmd_GetEditorID_Execute(COMMAND_ARGS) {
	TESForm* form;
	const char* edid;
	if (ExtractArgs(EXTRACT_ARGS, &form)) {
		edid = form->GetName();
		StrIfc->Assign(PASS_COMMAND_ARGS, edid);
		if (IsConsoleMode())
			Console_Print("GetEditorID >> %s", edid);
	}
	return true;
}
bool Cmd_IsLevelUpMenuEnabled_Execute(COMMAND_ARGS)
{
	*result = isShowLevelUp;
	if (IsConsoleMode()) Console_Print("IsLevelUpMenuEnabled >> %.f", *result);
	return true;
}

bool Cmd_ExitGameAlt_Execute(COMMAND_ARGS)
{
	
	ThisStdCall(0x0703DA0, nullptr);
	ThisStdCall(0x07D0A70, nullptr);
	return true;
}