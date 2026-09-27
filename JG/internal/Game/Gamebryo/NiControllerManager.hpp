#pragma once

#include "NiTimeController.hpp"
#include "NiTObjectArray.hpp"
#include "NiTStringMap.hpp"
#include "NiControllerSequence.hpp"
#include "NiDefaultAVObjectPalette.hpp"
#include "NiTPrimitiveSet.hpp"
#include "NiTObjectSet.hpp"
#include "NiTStringPointerMap.hpp"

class BSAnimNoteListener;

class NiControllerManager : public NiTimeController {
public:
	NiTObjectArray<NiPointer<NiControllerSequence>>		m_kSequenceArray;
	NiTPrimitiveSet<NiControllerSequence*>				m_kActiveSequences;
	NiTStringPointerMap<NiControllerSequence*>			m_kIndexMap;
	BSAnimNoteListener*									pListener;
	bool												m_bCumulative;
	NiTObjectSet<NiPointer<NiControllerSequence> >		m_kTempBlendSeqs;
	NiDefaultAVObjectPalettePtr							m_spObjectPalette;

	CREATE_OBJECT(NiControllerManager, 0xA2F6C0);
	NIRTTI_ADDRESS(0x11F36AC);

	static NiControllerManager* Create(NiAVObject* apTarget, bool abCumulativeAnimations = false);

	NiAVObject* GetAccumRoot() const;
	NiControllerSequence* GetSequenceByName(const NiFixedString& arName) const;
	NiControllerSequence* GetSequenceAt(uint32_t auiIndex) const;

	uint32_t GetSequenceCount() const;

	bool Morph(NiControllerSequence* apSourceSequence, NiControllerSequence* apDestSequence, float afDuration, int32_t aiPriority = 0, float afSourceWeight = 1.f, float afDestWeight = 1.f);
	bool CrossFade(NiControllerSequence* apSourceSequence, NiControllerSequence* apDestSequence, float afDuration, int32_t aiPriority = 0, bool abStartOver = false, float afWeight = 1.f, NiControllerSequence* apTimeSyncSeq = nullptr);
	
	NiControllerSequence* CreateTempBlendSequence(NiControllerSequence* apSequence, NiControllerSequence* apSequenceToSynchronize);
	bool BlendFromPose(NiControllerSequence* apSequence, float afDestFrame, float afDuration, int32_t aiPriority = 0, NiControllerSequence* apSequenceToSynchronize = nullptr);

	bool AddSequence(NiControllerSequence* apSequence, const NiFixedString& arName, bool abStoreTargets = true);
	void RemoveSequence(NiControllerSequence* apSequence);
	void RemoveSequence(NiControllerSequence* apSequence, NiControllerSequencePtr& arOut);

	bool ActivateSequence(NiControllerSequence* apSequence, int32_t aiPriority, bool abStartOver, float afWeight, float afEaseInTime, NiControllerSequence* apTimeSyncSeq);
	bool DeactivateSequence(NiControllerSequence* apSequence, float afEaseOutTime);
	bool DeactivateTransSourceSequence(float afEaseOutTime);
	void DeactivateAll(float afEaseOutTime);
};

ASSERT_SIZE(NiControllerManager, 0x7C);