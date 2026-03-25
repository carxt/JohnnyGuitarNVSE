#pragma once

class TESFaction;

class FactionRank {
public:
	TESFaction* pFaction;
	int8_t		cRank;
};

ASSERT_SIZE(FactionRank, 0x8);