#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleArray.hpp"

class TESIdleForm;
class Actor;
class TESObjectREFR;

class BGSIdleCollection : public BaseFormComponent {
public:
	enum PickType : uint8_t {
		RANDOM		= 0,
		SEQUENCE	= 1,
	};

	struct ALIGN1 _IdleCollectionFlags {
		enum Flags : uint8_t {
			PICK_TYPE	= 1u << 0,
			DO_ONCE		= 1u << 2,
		};

		PickType ePickType	: 1;
		bool				: 1;
		bool bDoOnce		: 1;
	};
	using IdleCollectionFlags = _IdleCollectionFlags::Flags;

	Bitfield<_IdleCollectionFlags>	ucIdleFlags;
	uint8_t							ucIdleCount;
	TESIdleForm**					ppIdles;
	float							fTimerCheckForIdle;

	PickType GetPickType() const;
	void SetPickType(PickType aeType);

	bool GetDoOnce() const;
	void SetDoOnce(bool abVal);

	uint32_t GetIdleCount() const;

	uint32_t GetIdlesForActor(Actor* apActor, TESObjectREFR* apTargetRef, BSSimpleArray<TESIdleForm*>* apOutIdleArray) const;
	
	bool HasIdleForActor(Actor* apActor, TESObjectREFR* apTargetRef) const;
};

ASSERT_SIZE(BGSIdleCollection, 0x10);