#pragma once

#include "NiNode.hpp"

NiSmartPointer(NiSwitchNode);

class NiSwitchNode : public NiNode {
public:
	NiSwitchNode();
	~NiSwitchNode();

	struct ALIGN2 _SwitchFlags {
		enum Flags : uint16_t {
			UPDATE_ONLY_ACTIVE_CHILD	= 1u << 0,
			UPDATE_CONTROLLERS			= 1u << 1,
		};

		bool bUpdateOnlyActiveChild : 1;
		bool bUpdateControllers		: 1;
	};
	using SwitchFlags = _SwitchFlags::Flags;

	Bitfield<_SwitchFlags>		m_usFlags;
	int32_t						m_iIndex;
	float						m_fSavedTime;
	uint32_t					m_uiRevID;
	NiTPrimitiveArray<uint32_t>	m_kChildRevID;

	CREATE_OBJECT(NiSwitchNode, 0xA94550);
	NIRTTI_ADDRESS(0x11F5EB4);

	NiAVObject* GetActiveChild();

	bool GetUpdateOnlyActiveChild() const;
	void SetUpdateOnlyActiveChild(bool abEnable);
	
	bool GetUpdateControllers() const;
	void SetUpdateControllers(bool abEnable);

	int32_t GetIndex() const;
	void SetIndex(int32_t aiIndex);

	float GetSavedTime() const;
};

ASSERT_SIZE(NiSwitchNode, 0xCC)