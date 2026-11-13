#pragma once

#include "NiObject.hpp"
#include "NiFixedString.hpp"
#include "NiCriticalSection.hpp"

class NiTimeController;
class NiExtraData;

class NiObjectNET : public NiObject {
public:
	NiObjectNET();
	virtual ~NiObjectNET();

	struct _CopyType {
		enum Type {
			NONE	= 0,
			EXACT	= 1,
			UNIQUE	= 2,
		};
	};
	using CopyType = _CopyType::Type;

	NiFixedString					m_kName;
	NiPointer<NiTimeController>		m_spControllers;
	NiExtraData**					m_ppkExtra;
	uint16_t						m_usExtraDataSize;
	uint16_t						m_usMaxSize;

	NIRTTI_ADDRESS(0x11F4304);

	const NiFixedString& GetName() const;
	void SetName(const NiFixedString& arString);

	NiTimeController* GetControllers() const;
	NiTimeController* GetController(const NiRTTI* apRTTI) const;
	template <class ControllerType>
	ControllerType* GetController() const {
		return static_cast<ControllerType*>(GetController(&ControllerType::ms_RTTI));
	}

	void PrependController(NiTimeController* apController);
	void RemoveController(NiTimeController* apController);

	bool HasExtraData() const;
	NiExtraData* GetExtraData(const NiFixedString& arKey) const;
	bool AddExtraData(NiExtraData* apExtraData);
	bool AddExtraData(const NiFixedString& arKey, NiExtraData* apExtraData);
	bool RemoveExtraData(const NiFixedString& arKey);
	void DeleteExtraData(uint16_t ausIndex);
	void RemoveAllExtraData();

	static CopyType GetDefaultCopyType();
	static char GetDefaultAppendCharacter();
};

ASSERT_SIZE(NiObjectNET, 0x18);