#pragma once

#include "NiInterpolator.hpp"
#include "NiInterpController.hpp"
#include "NiTimeController.hpp"
#include "NiFixedString.hpp"
#include "NiTextKeyExtraData.hpp"

class NiControllerManager;
class NiStringPalette;
class NiBlendInterpolator;
class NiInterpController;
class BSAnimNote;

NiSmartPointer(NiControllerSequence);

class NiControllerSequence : public NiObject {
public:
	NiControllerSequence();
	virtual ~NiControllerSequence();
	virtual bool Deactivate(float afEaseOutTime, bool);

	struct _AnimState {
		enum State : uint32_t {
			INACTIVE,
			ANIMATING,
			EASEIN,
			EASEOUT,
			TRANSSOURCE,
			TRANSDEST,
			MORPHSOURCE
		};
	};
	using AnimState = _AnimState::State;

	struct InterpArrayItem {
		NiInterpolatorPtr		m_spInterpolator;
		NiInterpControllerPtr	m_spInterpCtlr;
		NiBlendInterpolator*	m_pkBlendInterp;
		uint8_t					m_ucBlendIdx;
		uint8_t					m_ucPriority;
	};

	class IDTag {
	public:
		IDTag(const NiFixedString& arAVObjectName = nullptr, const NiFixedString& arPropertyType = nullptr,
			const NiFixedString& arCtlrType = nullptr, const NiFixedString& arCtlrID = nullptr, const NiFixedString& arInterpolatorID = nullptr);
		IDTag(const IDTag& arOther);

		NiFixedString m_kAVObjectName;
		NiFixedString m_kPropertyType;
		NiFixedString m_kCtlrType;
		NiFixedString m_kCtlrID;
		NiFixedString m_kInterpolatorID;

		void ClearValues();
	};

	NiFixedString					m_kName;
	uint32_t						m_uiArraySize;
	uint32_t						m_uiArrayGrowBy;
	InterpArrayItem*				m_pkInterpArray;
	IDTag*							m_pkIDTagArray;
	float							m_fSeqWeight;
	NiPointer<NiTextKeyExtraData>	m_spTextKeys;
	NiTimeController::CycleType		m_eCycleType;
	float							m_fFrequency;
	float							m_fBeginKeyTime;
	float							m_fEndKeyTime;
	float							m_fLastTime;
	float							m_fWeightedLastTime;
	float							m_fLastScaledTime;
	NiControllerManager*			m_pkOwner;
	AnimState						m_eState;
	float							m_fOffset;
	float							m_fStartTime;
	float							m_fEndTime;
	float							m_fDestFrame;
	NiControllerSequence*			m_pkPartnerSequence;
	NiFixedString					m_kAccumRootName;
	NiAVObject*						m_pkAccumRoot;
	NiObjectPtr						m_spDeprecatedStringPalette;
	uint16_t						usCurAnimNIdx;
	NiPointer<BSAnimNote>*			spAnimNotes;
	uint16_t						usNumNotes;
	bool							bRemovableObjects;

	CREATE_OBJECT(NiControllerSequence, 0xA326C0);
	NIRTTI_ADDRESS(0x11F36DC);

	static NiControllerSequence* Create(const NiFixedString& arName, uint32_t auiArraySize = 12, uint32_t auiArrayGrowBy = 12);

	bool Activate(char acPriority, bool abStartOver, float afWeight, float afEaseInTime, NiControllerSequence* apTimeSyncSeq, bool asbTransition);

	bool StartMorph(NiControllerSequence* apDestSequence, float afDuration, int32_t aiPriority, float afSourceWeight, float afDestWeight);
	bool StartBlend(NiControllerSequence* apDestSequence, float afDuration, float afDestFrame, int32_t aiPriority, float afSourceWeight, float afDestWeight, NiControllerSequence* apTimeSyncSeq);

	void GetInterpInfoAt(uint32_t auiIndex, const char*& pcAVObjectName, const char*& pcPropertyType, const char*& pcCtlrType, const char*& pcCtlrID, const char*& pcInterpolatorID);

	NiAVObject* GetAccumRoot() const;

	uint32_t AddInterpolator(NiInterpolator* apInterpolator, IDTag& arTag, uint8_t aucPriority);
	NiInterpolator* GetInterpolatorAt(uint32_t auiIndex) const;
	void SetControllerAt(NiInterpController* apInterpCtlr, uint32_t auiIndex);
	void ReplaceInterpolatorAt(NiInterpolator* apInterp, uint32_t auiIndex);
	NiInterpController* GetControllerAt(uint32_t auiIndex) const;

	NiControllerManager* GetOwner() const;
	bool SetOwner(NiControllerManager* pkOwner);

	const NiFixedString& GetName() const;
	void SetName(const NiFixedString& arName);

	void StoreTargets(NiAVObject* apRoot);

	float ComputeScaledTime(float afTime, bool abStoreLastTime);

	AnimState GetState() const;
};

ASSERT_SIZE(NiControllerSequence, 0x74);