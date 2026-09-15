#pragma once

class TESForm;
class BGSSaveFormBuffer;
class BGSLoadGameBuffer;

class TESPackageData {
public:
	TESPackageData();
	virtual			~TESPackageData();
	virtual void	Copy(TESPackageData* apPackageData);
	virtual bool	Compare(TESPackageData* apOther) const;
	virtual void	Save();
	virtual void	InitItem(TESForm* apOwner);
#ifdef GAME
	virtual void	SaveGame(BGSSaveFormBuffer* apBuffer);
	virtual void	LoadGame(BGSLoadGameBuffer* apBuffer);
	virtual void	InitLoadGame(BGSLoadFormBuffer* apBuffer);
#else
	virtual void	Unk05();
	virtual void	Unk06(HWND);
	virtual void	Unk07();
	virtual void	Unk08();
#endif
};

ASSERT_SIZE(TESPackageData, 0x4);