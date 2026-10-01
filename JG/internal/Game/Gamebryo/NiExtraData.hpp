#pragma once

#include "NiObject.hpp"
#include "NiFixedString.hpp"

NiSmartPointer(NiExtraData);

class NiExtraData : public NiObject {
public:
	NiExtraData();
	virtual			~NiExtraData();

	virtual bool	IsStreamable() const; // 35
	virtual bool	IsCloneable() const;  // 36

	NiFixedString m_kName;

	CREATE_OBJECT(NiExtraData, 0xA7B380);
	NIRTTI_ADDRESS(0x11F4A80);

	const NiFixedString& GetName() const;
	void SetName(const NiFixedString& arName);
};

ASSERT_SIZE(NiExtraData, 0xC);