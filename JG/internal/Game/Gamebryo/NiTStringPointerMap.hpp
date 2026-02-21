#pragma once

#include "NiTStringTemplateMap.hpp"

template <class T_Data>
class NiTStringPointerMap : public NiTStringTemplateMap<NiTPointerMap<const char*, T_Data>, T_Data> {
public:
	NiTStringPointerMap(uint32_t auiHashSize = 37, bool abCopy = true) : NiTStringTemplateMap<NiTPointerMap<const char*, T_Data>, T_Data>(auiHashSize, abCopy) {};
};
static_assert(sizeof(NiTStringPointerMap<uint32_t>) == 0x14);