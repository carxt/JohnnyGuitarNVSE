#include "JohnnyExtraData.hpp"
#include <atomic>
#include <cassert>

extern NiTMap<const char*, TESForm*>** g_gameFormEditorIDsMap;

#define DEBUG_PRINTS 0

#if DEBUG_PRINTS
#define DEBUG_MSG(...) PrintLog(__VA_ARGS__)
#else
#define DEBUG_MSG(...)
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
	JohnnyExtraDataArray::GetInstance().Add(this);
}

JohnnyExtraData::~JohnnyExtraData() {
	DEBUG_MSG("Deleting JohnnyExtraData for %08X (%s)", pOwner ? pOwner->refID : 0, kFormData.strEditorID.c_str());
	if (pOwner && kFormData.strEditorID) {
		ThisCall(0xE91FD0, *g_gameFormEditorIDsMap, pOwner); // NiTMapBase<DWORD,DWORD>::RemoveAt
	}
	pOwner = nullptr;
	uiFormID = 0xDEADDEAD;
	kFormData.strEditorID = nullptr;
	JohnnyExtraDataArray::GetInstance().Remove(this);
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
}

void JohnnyExtraData::InitName() {
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
			apExtraData->uiFormID = apForm->refID;
		DEBUG_MSG("Adding JohnnyExtraData for %08X (%s)", apForm->refID, apExtraData->kFormData.strEditorID.c_str());
		return true;
	}
	DEBUG_MSG("Failed to add JohnnyExtraData for %08X (%s)", apForm->refID, apExtraData->kFormData.strEditorID.c_str());
	return false;
}

JohnnyExtraData* __fastcall JohnnyExtraData::Add(TESForm* apForm) {
	JohnnyExtraData* pExtraData = new JohnnyExtraData();
	if (Add(apForm, pExtraData))
		return pExtraData;

	delete pExtraData;
	return nullptr;
}

void __fastcall JohnnyExtraDataArray::Add(JohnnyExtraData* apExtraData) {
	if (apExtraData) {
		std::lock_guard<std::mutex> kLock(kMutex);
		kExtraDatas.push_back(apExtraData);
	}
}

void __fastcall JohnnyExtraDataArray::Remove(JohnnyExtraData* apExtraData) {
	if (apExtraData) {
		std::lock_guard<std::mutex> kLock(kMutex);
		std::erase(kExtraDatas, apExtraData);
	}
}

JohnnyExtraDataArray& JohnnyExtraDataArray::GetInstance() {
	static JohnnyExtraDataArray instance;
	return instance;
}

void JohnnyExtraDataArray::ResetScriptData() {
	std::lock_guard<std::mutex> kLock(kMutex);
	for (NiPointer<JohnnyExtraData> spData : kExtraDatas) {
		if (spData) {
			ZeroMemory(&spData->kScriptData, sizeof(spData->kScriptData));
		}
	}
}
