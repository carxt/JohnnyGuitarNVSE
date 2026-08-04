#pragma once

#include "NiSwitchNode.hpp"
#include "NiLODData.hpp"

NiSmartPointer(NiLODNode);

class NiLODNode : public NiSwitchNode {
public:
	NiLODNode();
	virtual ~NiLODNode();

	NiLODDataPtr	m_spLODData;
	bool			m_bLODActive;

	CREATE_OBJECT(NiLODNode, 0xA99710);
	NIRTTI_ADDRESS(0x11F5F1C);

#ifdef GAME
	static constexpr AddressPtr<int32_t, 0x11ABDF4> ms_iGlobalLOD;
#else
	static constexpr AddressPtr<int32_t, 0xEB6E44> ms_iGlobalLOD;
#endif
};

ASSERT_SIZE(NiLODNode, 0xD4)