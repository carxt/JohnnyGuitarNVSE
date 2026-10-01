#pragma once

#include "BSEnums.hpp"

class Actor;
class BGSSaveGameBuffer;
class BGSLoadGameBuffer;

class ActorPackageData {
public:
	ActorPackageData();
	virtual					~ActorPackageData();
	virtual void			HandleDeletedReference(Actor* apActor);
	virtual PACKAGE_TYPE	GetPackageType() const;
	virtual void			SaveGame(BGSSaveGameBuffer* apBuffer);
	virtual void			LoadGame(BGSLoadGameBuffer* apBuffer);
	virtual void			InitLoadGame(BGSLoadGameBuffer* apBuffer);
};

ASSERT_SIZE(ActorPackageData, 0x4);