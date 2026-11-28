#include "FormExtraData.hpp"

#include <forward_list>
#include <shared/Utils/DebugLog.hpp>

static std::forward_list<std::pair<NiFixedString&, const char*>>* pRegistrationQueue = nullptr;

SPEC_NOINLINE bool __fastcall NVSE::FormExtraData::RegisterExtraData(NiFixedString& arName, const char* apName) {
	if (!pRegistrationQueue)
		pRegistrationQueue = new std::forward_list<std::pair<NiFixedString&, const char*>>();
	pRegistrationQueue->push_front({ arName, apName });
	return true;
}

void __fastcall NVSE::FormExtraData::Init(NVSEDataInterface* apNVSEData) {
    pfGet			= static_cast<decltype(pfGet)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataGet));
	pfAdd			= static_cast<decltype(pfAdd)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataAdd));
	pfRemoveByName	= static_cast<decltype(pfRemoveByName)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByName));
	pfRemoveByPtr	= static_cast<decltype(pfRemoveByPtr)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByPtr));

	if (pRegistrationQueue) {
		for (auto& rItem : *pRegistrationQueue) {
			rItem.first = rItem.second;
			_MESSAGE("Registering Form ExtraData \"%s\"", rItem.second);
		}
		delete pRegistrationQueue;
		pRegistrationQueue = nullptr;
	}
}
