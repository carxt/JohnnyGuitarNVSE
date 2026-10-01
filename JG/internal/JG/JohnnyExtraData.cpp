#include "JohnnyExtraData.hpp"
#ifdef GAME
#include "EditorIDRestoration.hpp"
#endif
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

	_PluginFormExtraData_Get pfGet = nullptr;
	_PluginFormExtraData_Add pfAdd = nullptr;
	_PluginFormExtraData_RemoveByName pfRemoveByName = nullptr;
	_PluginFormExtraData_RemoveByPtr pfRemoveByPtr = nullptr;
}

JohnnyExtraData::JohnnyExtraData() : PluginFormExtraData() {
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

const NiFixedString& JohnnyExtraData::GetName() const {
	return GetDataName();
}

bool JohnnyExtraData::OnRemoval(TESForm* apForm, uint32_t aeRemovalReason) {
	switch (aeRemovalReason) {
		case PluginFormExtraData::RemovalReason::kFormDeletion:
		case PluginFormExtraData::RemovalReason::kTrashedReference:
			DEBUG_MSG("%08X (\"%s\") got deleted!", apForm->GetFormID(), GetEditorID());
			DetachEditorIDs();
			pOwner = nullptr;
			break;
		default:
			break;
	}
	return true;
}

#ifdef GAME
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

		kFormData.kEditorIDs.AddHead(arEDID);
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

TESForm* __fastcall JohnnyExtraData::GetExternalEmittanceSource() const {
	return kScriptData.pExternalEmittanceSource;
}

void __fastcall JohnnyExtraData::SetExternalEmittanceSource(TESForm* apSource) {
	kScriptData.pExternalEmittanceSource = apSource;
}
#else
const char* JohnnyExtraData::GetEditorID() const {
	return pOwner ? pOwner->GetFormEditorID() : nullptr;
}
#endif

const NiFixedString& JohnnyExtraData::GetDataName() {
	assert(JohnnyExtraDataGlobals::strName.m_kHandle);
	return JohnnyExtraDataGlobals::strName;
}

void __fastcall JohnnyExtraData::Initialize(NVSEDataInterface* apNVSEData) {
	if (!apNVSEData)
		return;

	DEBUG_MSG("Initializing JohnnyExtraData");
	using namespace JohnnyExtraDataGlobals;
	pfGet			= static_cast<decltype(pfGet)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataGet));
	pfAdd			= static_cast<decltype(pfAdd)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataAdd));
	pfRemoveByName	= static_cast<decltype(pfRemoveByName)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByName));
	pfRemoveByPtr	= static_cast<decltype(pfRemoveByPtr)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByPtr));
	strName			= "JohnnyExtraData";
}

JohnnyExtraData* __fastcall JohnnyExtraData::Find(const TESForm* apForm) {
	return static_cast<JohnnyExtraData*>(JohnnyExtraDataGlobals::pfGet(apForm, GetDataName()));
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
#ifdef GAME
	if (pOwner && !pOwner->GetTemporary() && !kFormData.kEditorIDs.IsEmpty()) {
		auto pIter = kFormData.kEditorIDs.GetHead();
		SRWUniqueLock kLock(EDIDRestoration::kEDIDMapLock);
		while (pIter) {
			DEBUG_MSG("%08X Removing EDID \"%s\"", pOwner->GetFormID(), pIter->GetItem());
			TESForm::pAllFormsByEditorID->RemoveAt(pIter->GetItem());
			pIter = pIter->GetNext();
		}
	}
#endif
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
