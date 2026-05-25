#pragma once

#include "BaseFormComponent.hpp"
#include "BSExtraData.hpp"
#include "BSSimpleList.hpp"

class TESObjectREFR;
class ContainerItemExtra;
class TESContainer;
class TESGlobal;
class TESForm;

struct LeveledObject {
	LeveledObject();
	~LeveledObject();

	TESForm*			pForm;
	uint16_t			usCount;
	uint16_t			usLevel;
	ContainerItemExtra* pItemExtra;
};

class TESLeveledList : public BaseFormComponent {
public:
	TESLeveledList();
	~TESLeveledList();

	virtual uint8_t		GetChanceNone() const;
	virtual bool		GetMultCalc() const;
	virtual uint32_t	GetMaxLevelDifference() const;

	struct ALIGN1 _LeveledListFlags {
		enum Flags : uint8_t {
			CALC_ALL_BELOW	= 1u << 0,
			MULT_CALC		= 1u << 1,
			USE_ALL			= 1u << 2,
		};

		bool bCalcAllBelow	: 1;
		bool bMultCalc		: 1;
		bool bUseAll		: 1;
	};
	using LeveledListFlags = _LeveledListFlags::Flags;

	BSSimpleList<LeveledObject*>	kLeveledObjects;
	uint8_t							ucChanceNone;
	Bitfield<_LeveledListFlags>		ucFlags;
	TESGlobal*						pChanceGlobal;
	BSSimpleList<LeveledObject*>	kScriptAddedObjects;

	const BSSimpleList<LeveledObject*>* GetLeveledList() const;
	BSSimpleList<LeveledObject*>* GetLeveledList();

	LeveledObject* AddLeveledObject(uint16_t ausLevel, uint16_t ausCount, TESForm* apForm, ContainerItemExtra* apExtra);

	bool GetCalcAllBelow() const;
	bool GetUseAll() const;

	void CalculateCurrentFormList(uint16_t ausLevel, uint16_t ausCount, TESContainer* apOut, uint32_t aeAllBelowForce);
	void CalculateCurrentForm(uint16_t ausLevel, TESForm*& apOutForm, uint16_t& asOutCount, ContainerItemExtra*& apOutExtra, bool abRecurse, uint32_t aeAllBelowForce);

	static TESLeveledList* GetFormAsLeveledList(const TESForm* apForm);
};

ASSERT_SIZE(TESLeveledList, 0x1C);