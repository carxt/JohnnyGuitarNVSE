#pragma once

#include "NiObject.hpp"
#include "Bethesda/NiUpdateData.hpp"

class NiObjectNET;
class NiAVObject;

class NiTimeController : public NiObject {
public:
	NiTimeController();
	virtual ~NiTimeController();

	virtual void	Start(float afTime = -FLT_MAX);			// 35
	virtual void	Stop();									// 36
	virtual void	Update(NiUpdateData& arUpdateData);		// 37
	virtual void	SetTarget(NiObjectNET* apTarget);		// 38
	virtual bool	IsTransformController() const;			// 39
	virtual bool	IsVertexController() const;				// 40
	virtual float	ComputeScaledTime(float fTime);			// 41
	virtual void	OnPreDisplay() const;					// 42
	virtual bool	IsStreamable() const;					// 43
	virtual bool	TargetIsRequiredType() const;			// 44

	struct _AnimType {
		enum Type {
			APP_TIME,
			APP_INIT
		};
	};
	using AnimType = _AnimType::Type;

	struct _CycleType {
		enum Type {
			LOOP,
			REVERSE,
			CLAMP,
			MAX_CYCLE_TYPES
		};
	};
	using CycleType = _CycleType::Type;

	struct ALIGN2 _Flags {
		enum Flags : uint16_t {
			ANIM_TYPE			= 0x1,
			ANIM_TYPE_POS		= 0,

			CYCLE_TYPE			= 0x6,
			CYCLE_TYPE_POS		= 1,

			ACTIVE				= 1u << 3,
			DIRECTION			= 1u << 4,
			MANAGER_CONTROLLED	= 1u << 5,
			COMPUTE_SCALED_TIME	= 1u << 6,
			FORCE_UPDATE		= 1u << 7,
		};

		uint8_t	eAnimType			: 1;
		uint8_t eCycleType			: 2;
		bool	bActive				: 1;
		bool	bDirection			: 1;
		bool	bManagerControlled	: 1;
		bool	bComputeScaledTime	: 1;
		bool	bForceUpdate		: 1;
	};
	using Flags = _Flags::Flags;

	Bitfield<_Flags>				m_usFlags;
	float							m_fFrequency;
	float							m_fPhase;
	float							m_fLoKeyTime;
	float							m_fHiKeyTime;
	float							m_fStartTime;
	float							m_fLastTime;
	float							m_fWeightedLastTime;
	float							m_fScaledTime;
	NiObjectNET*					m_pkTarget;
	NiPointer<NiTimeController>		m_spNext;

	NIRTTI_ADDRESS(0x11F49E4);

	void SetAnimType(AnimType aeType);
	AnimType GetAnimType() const;

	void SetCycleType(CycleType aeType);
	CycleType GetCycleType() const;

	void SetActive(bool abActive);
	bool GetActive() const;

	void SetComputeScaledTime(bool abComputeScaledTime);
	bool GetComputeScaledTime() const;

	bool DontDoUpdate(float afTime);

	NiTimeController* GetNext() const;
	void SetNext(NiTimeController* apNext);

	static void StartAnimations(NiAVObject* apObject);
	static void StartAnimations(NiAVObject* apObject, float afTime);

protected:
	void SetManagerControlledBit(bool abManagerControlled);
	bool GetManagerControlledBit() const;
};

ASSERT_SIZE(NiTimeController, 0x34);