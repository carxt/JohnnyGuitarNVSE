#pragma once

// Added to remove a cyclic dependency between GameForms.h and GameExtraData.h

class TESForm;
class TESFaction;

// C+?
class BSExtraData {
public:
	BSExtraData();
	virtual ~BSExtraData();

	virtual void	Fn_01(void);

	static BSExtraData* Create(uint8_t xType, uint32_t size, uint32_t vtbl);

	//	void		** _vtbl;	// 000
	uint8_t		type;		// 004
	uint8_t		pad[3];		// 005
	BSExtraData* next;		// 008
};

// 020
struct BaseExtraList {
	virtual void	Unk_00(void);

	BSExtraData* m_data;					// 004
	uint8_t			m_presenceBitfield[0x15];	// 008 - if a bit is set, then the extralist should contain that extradata
	uint8_t			pad1D[3];					// 01D

	bool HasType(uint32_t type) const;
	BSExtraData* GetByType(uint32_t type) const;
	void MarkType(uint32_t type, bool bCleared);
	void Remove(BSExtraData* toRemove, bool doFree = false);
	void RemoveByType(uint32_t type);
	BSExtraData* Add(BSExtraData* xData);
	void RemoveAll(bool doFree = true);
	bool MarkScriptEvent(uint32_t eventMask, TESForm* eventTarget);
	void Copy(BaseExtraList* sourceList);
	bool IsWorn();
	char GetExtraFactionRank(TESFaction* faction);
};

struct ExtraDataList : public BaseExtraList {
	ExtraDataList* CreateCopy();
	static ExtraDataList* __stdcall Create(BSExtraData* xBSData = NULL);
};

static_assert(sizeof(ExtraDataList) == 0x020);
