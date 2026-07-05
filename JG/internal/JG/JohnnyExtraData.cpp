#include "JohnnyExtraData.hpp"
#include "EditorIDRestoration.hpp"
#include <atomic>
#include <cassert>

#define DEBUG_PRINTS 0

#if DEBUG_PRINTS
#define DEBUG_MSG(...) _MESSAGE(__VA_ARGS__)
#else
#define DEBUG_MSG(...) __noop(__VA_ARGS__)
#endif

namespace JohnnyExtraDataGlobals {
	NiFixedString strName;

	PluginFormExtraData* (*pfGet)(const TESForm*, const char*) = nullptr;
	bool (*pfAdd)(TESForm*, PluginFormExtraData*) = nullptr;
	void (*pfRemoveByName)(TESForm*, const char*) = nullptr;
	void (*pfRemoveByPtr)(TESForm*, PluginFormExtraData*) = nullptr;
}

JohnnyExtraData::JohnnyExtraData() : PluginFormExtraData(GetName()) {
	pOwner		= nullptr;
	uiFormID	= 0;
	ZeroMemory(&kFormData, sizeof(kFormData));
	ZeroMemory(&kScriptData, sizeof(kScriptData));
	// Commented out because we don't actually need it yet, so it's just wasting memory
	//JohnnyExtraDataArray::GetInstance().Add(this);
}

JohnnyExtraData::~JohnnyExtraData() {
	DEBUG_MSG("Deleting JohnnyExtraData for %08X (\"%s\")", pOwner ? pOwner->GetFormID() : 0, GetEditorID());
	DetachEditorIDs();
	pOwner = nullptr;
	uiFormID = 0xDEADDEAD;
	//JohnnyExtraDataArray::GetInstance().Remove(this);
}

const NiFixedString& JohnnyExtraData::GetEditorID() const {
	return kFormData.kEditorIDs.GetItem();
}

JohnnyExtraData::EDIDResult __fastcall JohnnyExtraData::SetEditorID(const NiFixedString& arEDID) {
	if (!arEDID.GetLength()) {
		DEBUG_MSG("%08X Tried to set an empty EDID", pOwner->GetFormID());
		return EDIDResult::FAILURE;
	}

	if (!GetEditorID()) {
		DEBUG_MSG("%08X Adding EDID \"%s\"", pOwner->GetFormID(), arEDID);
		kFormData.kEditorIDs.SetItem(arEDID);
		return EDIDResult::SUCCESS;
	}
	else if (GetEditorID() != arEDID) {
		if (kFormData.kEditorIDs.IsInList(arEDID)) {
			DEBUG_MSG("%08X EDID alias \"%s\" already exists", pOwner->GetFormID(), arEDID);
			return EDIDResult::ALREADY_EXISTS;
		}

		kFormData.kEditorIDs.AddTail(arEDID);
		DEBUG_MSG("%08X Adding EDID alias \"%s\"", pOwner->GetFormID(), arEDID);
		return EDIDResult::SUCCESS;
	}
	else {
		DEBUG_MSG("%08X EDID \"%s\" is already set", pOwner->GetFormID(), arEDID);
		return EDIDResult::ALREADY_EXISTS;
	}
}

JohnnyExtraData::EDIDResult __fastcall JohnnyExtraData::RemoveEditorID(const NiFixedString& arEDID) {
	kFormData.kEditorIDs.Remove(arEDID);
	return EDIDResult::SUCCESS;
}

const NiFixedString& JohnnyExtraData::GetName() {
	assert(JohnnyExtraDataGlobals::strName.m_kHandle);
	return JohnnyExtraDataGlobals::strName;
}

void __fastcall JohnnyExtraData::Initialize(NVSEDataInterface* apNVSEData) {
	DEBUG_MSG("Initializing JohnnyExtraData");
	JohnnyExtraDataGlobals::pfGet			= static_cast<PluginFormExtraData * (*)(const TESForm*, const char*)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_FormExtraDataGet));
	JohnnyExtraDataGlobals::pfAdd			= static_cast<bool(*)(TESForm*, PluginFormExtraData*)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_FormExtraDataAdd));
	JohnnyExtraDataGlobals::pfRemoveByName	= static_cast<void (*)(TESForm*, const char*)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_FormExtraDataRemoveByName));
	JohnnyExtraDataGlobals::pfRemoveByPtr	= static_cast<void (*)(TESForm*, PluginFormExtraData*)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_FormExtraDataRemoveByPtr));
	JohnnyExtraDataGlobals::strName = "JohnnyExtraData";
}

JohnnyExtraData* __fastcall JohnnyExtraData::Find(const TESForm* apForm) {
	return static_cast<JohnnyExtraData*>(JohnnyExtraDataGlobals::pfGet(apForm, GetName()));
}

JohnnyExtraData* __fastcall JohnnyExtraData::GetOrCreate(TESForm* apForm) {
	JohnnyExtraData* pExtraData = Find(apForm);
	if (pExtraData)
		return pExtraData;

	return Add(apForm);
}

bool __fastcall JohnnyExtraData::Add(TESForm* apForm, JohnnyExtraData* apExtraData) {
	if (JohnnyExtraDataGlobals::pfAdd(apForm, apExtraData)) {
		apExtraData->pOwner = apForm;
		if (!apForm->GetTemporary())
			apExtraData->uiFormID = apForm->GetFormID();

		DEBUG_MSG("Adding JohnnyExtraData for %08X (\"%s\")", apForm->GetFormID(), apExtraData->GetEditorID());
		return true;
	}
	DEBUG_MSG("Failed to add JohnnyExtraData for %08X (\"%s\")", apForm->GetFormID(), apExtraData->GetEditorID());
	return false;
}

JohnnyExtraData* __fastcall JohnnyExtraData::Add(TESForm* apForm) {
	JohnnyExtraData* pExtraData = new JohnnyExtraData();
	if (!pExtraData) {
		DEBUG_MSG("Failed to allocate JohnnyExtraData for %08X", apForm->GetFormID());
		return nullptr;
	}

	if (Add(apForm, pExtraData))
		return pExtraData;

	delete pExtraData;
	return nullptr;
}

void JohnnyExtraData::DetachEditorIDs() {
	if (pOwner && !pOwner->GetTemporary() && !kFormData.kEditorIDs.IsEmpty()) {
		auto pIter = kFormData.kEditorIDs.GetHead();
		SRWUniqueLock kLock(EDIDRestoration::kEDIDMapLock);
		while (pIter) {
			DEBUG_MSG("%08X Removing EDID \"%s\"", pOwner->GetFormID(), pIter->GetItem());
			TESForm::pAllFormsByEditorID->RemoveAt(pIter->GetItem());
			pIter = pIter->GetNext();
		}
	}
}

void __fastcall JohnnyExtraDataArray::Add(JohnnyExtraData* apExtraData) {
	if (apExtraData) {
		SRWUniqueLock kLock(kDataLock);
		kExtraDatas.push_back(apExtraData);
		bChanged = true;
	}
}

void __fastcall JohnnyExtraDataArray::Remove(JohnnyExtraData* apExtraData) {
	if (apExtraData) {
		SRWUniqueLock kLock(kDataLock);
		if (std::erase(kExtraDatas, apExtraData))
			bChanged = true;
	}
}

JohnnyExtraDataArray& JohnnyExtraDataArray::GetInstance() {
	static JohnnyExtraDataArray instance;
	return instance;
}

void JohnnyExtraDataArray::ResetScriptData() {
	SRWSharedLock kLock(kDataLock);
	for (NiPointer<JohnnyExtraData> spData : kExtraDatas) {
		if (spData) {
			ZeroMemory(&spData->kScriptData, sizeof(spData->kScriptData));
		}
	}
}
