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

#ifdef GAME
	static constexpr AddressPtr<NiCriticalSection, 0x11F4380> kExtraDataLock;
#else
	static constexpr AddressPtr<NiCriticalSection, 0xF1FE80> kExtraDataLock;
#endif

	const NiFixedString& GetName() const;
	void SetName(const NiFixedString& arName);

	NiTimeController* GetControllers() const;
	void SetControllers(NiTimeController* apController);

	NiTimeController* GetController(const NiRTTI* apRTTI) const;
	template <class ControllerType>
	ControllerType* GetController() const {
		return static_cast<ControllerType*>(GetController(&ControllerType::ms_RTTI));
	}

	void PrependController(NiTimeController* apController);
	void RemoveController(NiTimeController* apController);
	void RemoveAllControllers();

	uint16_t GetExtraDataSize() const;
	bool SetExtraDataSize(uint16_t ausSize);

	NiExtraData* GetExtraData(const NiFixedString& arKey) const;
	bool AddExtraData(NiExtraData* apExtraData);
	bool AddExtraData(const NiFixedString& arKey, NiExtraData* apExtraData);
	bool InsertExtraData(NiExtraData* apExtraData);
	void DeleteExtraData(uint16_t ausIndex);
	bool RemoveExtraData(const NiFixedString& arKey);
	void RemoveAllExtraData();

	static CopyType GetDefaultCopyType();
	static char GetDefaultAppendCharacter();
};

ASSERT_SIZE(NiObjectNET, 0x18);