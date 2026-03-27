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
	virtual void	SaveGame(BGSSaveFormBuffer* apBuffer);
	virtual void	LoadGame(BGSLoadGameBuffer* apBuffer);
	virtual void	InitLoadGame(BGSSaveFormBuffer* apBuffer);
};

ASSERT_SIZE(TESPackageData, 0x4);