#pragma once

#include "NiTStringTemplateMap.hpp"

template <class T_Data>
class NiTStringMap : public NiTStringTemplateMap<NiTMap<const char*, T_Data>, T_Data> {
public:
	NiTStringMap(uint32_t auiHashSize = 37, bool abCopy = true) : NiTStringTemplateMap<NiTMap<const char*, T_Data>, T_Data>(auiHashSize, abCopy) {};
};
static_assert(sizeof(NiTStringMap<uint32_t>) == 0x14);