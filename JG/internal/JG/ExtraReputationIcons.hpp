#pragma once

class TESReputation;

namespace ExtraReputationIcons {

	struct _Tier {
		enum Tier {
			NONE		= -1,
			IN_PAIN		= 0,
			SAD			= 1,
			NEUTRAL		= 2,
			VERY_HAPPY	= 3,
			COUNT,
		};
	};
	using Tier = _Tier::Tier;

	void Install();

	const char* __fastcall Get(const TESReputation* apReputation, Tier aeTier);
	const char* __fastcall Get(const TESReputation* apReputation);
	void __fastcall Set(TESReputation* apReputation, Tier aeTier, const char* apPath);

	void Dump();

}