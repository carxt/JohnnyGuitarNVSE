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

_PluginFormExtraData_Get			FormExtraData::pfGet = nullptr;
_PluginFormExtraData_Add			FormExtraData::pfAdd = nullptr;
_PluginFormExtraData_RemoveByName	FormExtraData::pfRemoveByName = nullptr;
_PluginFormExtraData_RemoveByPtr	FormExtraData::pfRemoveByPtr = nullptr;

bool __fastcall FormExtraData::RegisterExtraData(NiFixedString& arName, const char* apName) {
	kRegistrationQueue.push_front({ arName, apName });
	return true;
}

void __fastcall FormExtraData::Initialize(NVSEDataInterface* apNVSEData) {
	if (!apNVSEData)
		return;

	DEBUG_MSG("Initializing JohnnyExtraData");
	pfGet = static_cast<decltype(pfGet)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataGet));
	pfAdd = static_cast<decltype(pfAdd)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataAdd));
	pfRemoveByName = static_cast<decltype(pfRemoveByName)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByName));
	pfRemoveByPtr = static_cast<decltype(pfRemoveByPtr)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByPtr));

	for (auto& rItem : kRegistrationQueue) {
		rItem.first = rItem.second;
	}
	kRegistrationQueue.clear();
}

FormExtraData::FormExtraData() {
	++uiCurrentDataCount;
}

FormExtraData::~FormExtraData() {
	--uiCurrentDataCount;
}

uint32_t FormExtraData::GetDataCount() {
	return uiCurrentDataCount;
}

JohnnyExtraData::JohnnyExtraData() : pOwner(nullptr) {
}

JohnnyExtraData::~JohnnyExtraData() {
	DEBUG_MSG("Deleting JohnnyExtraData for %08X (\"%s\")", pOwner ? pOwner->GetFormID() : 0, GetOwnerEDID());
	Reset();
}

void JohnnyExtraData::Reset() {
#ifdef GAME
	DetachEditorIDs();
#endif
	pOwner = nullptr;
}

bool JohnnyExtraData::OnRemoval(TESForm* apForm, uint32_t aeRemovalReason) {
	switch (aeRemovalReason) {
		case PluginFormExtraData::RemovalReason::kFormDeletion:
		case PluginFormExtraData::RemovalReason::kTrashedReference:
			DEBUG_MSG("%08X (\"%s\") got deleted!", apForm->GetFormID(), GetOwnerEDID());
			Reset();
			break;
		default:
			break;
	}
	return true;
}

bool JohnnyExtraData::OnAdd(TESForm* apForm) {
	pOwner = apForm;
	return true;
}

const char* JohnnyExtraData::GetOwnerEDID() const {
#ifdef GAME
	return kEditorIDs.GetItem();
#else
	return pOwner ? pOwner->GetFormEditorID() : nullptr;
#endif
}

#ifdef GAME
const NiFixedString& JohnnyExtraData::GetEditorID() const {
	return kEditorIDs.GetItem();
}

JohnnyExtraData::EDIDResult __fastcall JohnnyExtraData::SetEditorID(const NiFixedString& arEDID) {
	if (!arEDID.GetLength()) {
		DEBUG_MSG("%08X Tried to set an empty EDID", pOwner->GetFormID());
		return EDIDResult::FAILURE;
	}

	if (!GetEditorID()) {
		DEBUG_MSG("%08X Adding EDID \"%s\"", pOwner->GetFormID(), arEDID);
		kEditorIDs.SetItem(arEDID);
		return EDIDResult::SUCCESS;
	}
	else if (GetEditorID() != arEDID) {
		if (kEditorIDs.IsInList(arEDID)) {
			DEBUG_MSG("%08X EDID alias \"%s\" already exists", pOwner->GetFormID(), arEDID);
			return EDIDResult::ALREADY_EXISTS;
		}

		kEditorIDs.AddHead(arEDID);
		DEBUG_MSG("%08X Adding EDID alias \"%s\"", pOwner->GetFormID(), arEDID);
		return EDIDResult::SUCCESS;
	}
	else {
		DEBUG_MSG("%08X EDID \"%s\" is already set", pOwner->GetFormID(), arEDID);
		return EDIDResult::ALREADY_EXISTS;
	}
}

JohnnyExtraData::EDIDResult __fastcall JohnnyExtraData::RemoveEditorID(const NiFixedString& arEDID) {
	kEditorIDs.Remove(arEDID);
	return EDIDResult::SUCCESS;
}

JohnnyExtraData::EDIDList* JohnnyExtraData::GetEditorIDHead() {
	return &kEditorIDs;
}

void JohnnyExtraData::DetachEditorIDs() {
	if (pOwner && !pOwner->GetTemporary() && !kEditorIDs.IsEmpty()) {
		auto pIter = kEditorIDs.GetHead();
		SRWUniqueLock kLock(EDIDRestoration::kEDIDMapLock);
		while (pIter) {
			DEBUG_MSG("%08X Removing EDID \"%s\"", pOwner->GetFormID(), pIter->GetItem());
			TESForm::pAllFormsByEditorID->RemoveAt(pIter->GetItem());
			pIter = pIter->GetNext();
		}
	}
}
#endif

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
	SRWUniqueLock kLock(kDataLock);
	for (NiPointer<JohnnyExtraData> spData : kExtraDatas) {
	}
}
