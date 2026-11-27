#include "FormExtraData.hpp"

#include <forward_list>

static std::forward_list<std::pair<NiFixedString&, const char*>> kRegistrationQueue;

SPEC_NOINLINE bool __fastcall NVSE::FormExtraData::RegisterExtraData(NiFixedString& arName, const char* apName) {
	kRegistrationQueue.push_front({ arName, apName });
	return true;
}

void __fastcall NVSE::FormExtraData::Init(NVSEDataInterface* apNVSEData) {
    pfGet			= static_cast<decltype(pfGet)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataGet));
	pfAdd			= static_cast<decltype(pfAdd)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataAdd));
	pfRemoveByName	= static_cast<decltype(pfRemoveByName)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByName));
	pfRemoveByPtr	= static_cast<decltype(pfRemoveByPtr)>(apNVSEData->GetFunc(NVSEDataInterface::kNVSEData_PluginFormExtraDataRemoveByPtr));

	for (auto& rItem : kRegistrationQueue) {
		rItem.first = rItem.second;
	}
	kRegistrationQueue.clear();
}
