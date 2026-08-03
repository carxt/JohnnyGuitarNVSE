#include "TESNPC.hpp"

// GAME - 0x502430
TESClass* TESNPC::GetClass() const {
	return pClass;
}

// GAME - 0x601C70
void TESNPC::SetClass(TESNPC* apClass) {
	ThisCall(0x601C70, this, apClass);
}

// GAME - 0x603B50
// GECK - 0x56F440
TESHair* TESNPC::GetHair() const {
#ifdef GAME
	return ThisCall<TESHair*>(0x603B50, this);
#else
	return ThisCall<TESHair*>(0x56F440, this);
#endif
}

// GAME - 0x6031E0
void TESNPC::SetHair(TESHair* apHair) {
	pHair = apHair;
}

// GAME - 0x607950
TESCombatStyle* TESNPC::GetCombatStyle() const {
	return pCombatStyle;
}

// GAME - 0x4AC110
TESRace* TESNPC::GetRace() const {
	return pRace;
}

// GAME - 0x944300
// GECK - 0x56F900
float TESNPC::GetHeight() const {
#ifdef GAME
	return fHeight;
#else
	return ThisCall<float>(0x56F900, this);
#endif
}

// GAME - 0x6041D0
float TESNPC::GetRaceHeight() const {
	return ThisCall<float>(0x6041D0, this);
}

// GAME - 0x604250
// GECK - 0x56F950
float TESNPC::GetWeight() const {
#ifdef GAME
	return ThisCall<float>(0x604250, this);
#else
	return ThisCall<float>(0x56F950, this);
#endif
}

// GAME - 0x603AD0
// GECK - 0x56F390
void TESNPC::GetFaceCoord(FaceGenCoords& arCoords) const {
#ifdef GAME
	ThisCall(0x603AD0, this, &arCoords);
#else
	ThisCall(0x56F390, this, &arCoords);
#endif
}

// GAME - 0x601800
FaceGenCoords* TESNPC::GetOffsetFaceCoord() const {
	return ThisCall<FaceGenCoords*>(0x601800, this);
}
