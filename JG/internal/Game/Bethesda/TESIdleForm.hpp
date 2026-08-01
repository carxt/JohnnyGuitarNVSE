#pragma once

#include "TESForm.hpp"
#include "TESModelAnim.hpp"
#include "TESCondition.hpp"
#include "NiFormArray.hpp"

struct IdleReplayDelay;

class TESIdleForm : public TESForm, public TESModelAnim {
public:
	TESIdleForm();
	~TESIdleForm();

	struct ALIGN1 _AnimFlags {
		enum Flags : uint8_t {
			GROUP_MASK		= 0x3F,

			LOOSE_IDLE		= 1u << 6,
			ALLOW_NO_FILE	= 1u << 7,
		};

		uint8_t ucGroup			: 6;
		bool	bLooseIdle		: 1;
		bool	bAllowNoFile	: 1;
	};
	using AnimFlags = _AnimFlags::Flags;

	struct ALIGN1 _IdleFlags {
		enum Flags : uint8_t {
			NO_ATTACKING = 1u << 0,
		};

		bool bNoAttacking : 1;
	};
	using IdleFlags = _IdleFlags::Flags;

	struct Data {
		Bitfield<_AnimFlags>	ucAnimFlags;
		uint8_t					ucLoopMin;
		uint8_t					ucLoopMax;
		uint16_t				usReplayDelay;
		Bitfield<_IdleFlags>	ucFlags;
	};

	TESCondition	kConditions;
	Data			kData;
	NiFormArray*	pChildren;
	TESIdleForm*	pParentIdle;
	TESIdleForm*	pPrevIdle;
	BSString		strEditorID;

	TESFORM_TYPE(TESIdleForm);

	TESCondition* GetConditions();
	const TESCondition* GetConditions() const;

	ANIM_GROUP_SECTION GetIdleAnimGroupSection() const;
	void SetIdleAnimGroupSection(ANIM_GROUP_SECTION aeSection);

	bool GetLooseIdle() const;
	void SetLooseIdle(bool abVal);

	bool GetAllowNoFile() const;
	void SetAllowNoFile(bool abVal);

	uint8_t GetLoops() const;

	uint16_t GetReplayDelay() const;

	bool GetNoAttacking() const;
	void SetNoAttacking(bool abVal);

	NiFormArray* GetChildArray();
	const NiFormArray* GetChildArray() const;

	uint32_t GetChildCount() const;

	TESIdleForm* GetChildByIndex(uint32_t auiIndex) const;
	uint32_t GetIndexForChild(TESIdleForm* apChild) const;
	void RemoveChild(TESIdleForm* apChild);
	void RemoveChildAtIndex(uint32_t auiIndex);

	TESIdleForm* GetParentIdle() const;
	void SetParentIdle(TESIdleForm* apIdle);

	TESIdleForm* GetPrevIdle() const;
	void SetPrevIdle(TESIdleForm* apIdle);

	TESIdleForm* GetIdleToPlay(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, BSSimpleList<IdleReplayDelay*>* apReplayDelays) const;

	bool CheckConditions(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, bool abRecurseUp) const;
};

ASSERT_SIZE(TESIdleForm, 0x54);