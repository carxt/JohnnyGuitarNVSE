#pragma once

class TESFile;

namespace CustomHUDShake {

	void Reset();

	void Update();

	float __fastcall Get(const TESFile* apFile);
	void __fastcall Set(const TESFile* apFile, float afPower);

}