#pragma once

#include "ActorPackageData.hpp"

class TESPackage;
class TESObjectREFR;

class ActorPackage {
public:
	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			SAVE_LOAD_SHARE_PACAKGE = 1u << 0,
		};

		bool bSaveLoadSharePackage : 1;
	};
	using Flags = _Flags::Flags;

	TESPackage*			pPackage;
	ActorPackageData*	pData;
	TESObjectREFR*		pTarget;
	int32_t				iCurrentProcedureIndex;
	float				fPackageStartTime;
	Bitfield<_Flags>	uiFlags;

	void InitFromPackage(TESPackage* apPackage, TESObjectREFR* apTarget);

	TESPackage* GetTESPackage() const;

	ActorPackageData* GetInstanceData() const;
	void SetInstanceData(ActorPackageData* apData);

	TESObjectREFR* GetTarget() const;
	void SetTarget(TESObjectREFR* apTarget);

	int32_t GetCurrentProcedureIndex() const;
	void SetCurrentProcedureIndex(int32_t aiIndex);

	float GetPackageStartTime() const;
};

ASSERT_SIZE(ActorPackage, 0x18);