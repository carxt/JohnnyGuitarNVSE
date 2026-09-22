#include "TESNPC.hpp"
#ifdef EDITOR
#include "TESRace.hpp"
#endif

// GAME - 0x502430
TESClass* TESNPC::GetClass() const {
	return pClass;
}

// GAME - 0x601C70
// GECK - 0x56F380
void TESNPC::SetClass(TESClass* apClass) {
#ifdef GAME
	ThisCall(0x601C70, this, apClass);
#else
	ThisCall(0x56F380, this, apClass);
#endif
}

// GAME - 0x5D9F70
FaceGenCoords* TESNPC::GetAlternateOffsetFaceCoord() const {
	return pAlternateFaceOffsetCoord;
}

// GAME - 0x5D9F70
void TESNPC::SetAlternateOffsetFaceCoord(FaceGenCoords* apCoords) {
	pAlternateFaceOffsetCoord = apCoords;
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

// GAME - 0x602130
float TESNPC::GetHairLength() const {
	return fHairLength;
}

// GAME - 0x602150
TESEyes* TESNPC::GetEyeColor() const {
	return pEyeColor;
}

void TESNPC::SetEyeColor(TESEyes* apEyes) {
	pEyeColor = apEyes;
}

// GAME - 0x607950
TESCombatStyle* TESNPC::GetCombatStyle() const {
	return pCombatStyle;
}

// GAME - 0x4AC110
TESRace* TESNPC::GetRace() const {
	return pRace;
}

// GAME - 0x4169D0
uint32_t TESNPC::GetHairColor() const {
	return uiHairColor;
}

// GAME - 0x7B3720
void TESNPC::SetHairColor(uint32_t auiColor) {
	uiHairColor = auiColor;
}

// GAME - 0x602170
const BSSimpleList<BGSHeadPart*>* TESNPC::GetHeadPartList() const {
	return &kHeadParts;
}

// GAME - 0x602170
BSSimpleList<BGSHeadPart*>* TESNPC::GetHeadPartList() {
	return &kHeadParts;
}

// GAME - 0x944300
// GECK - 0x56F900
float TESNPC::GetHeight() const {
	return fHeight;
}

// GAME - 0x6041D0
// GECK - 0x56F900
float TESNPC::GetRaceHeight() const {
#ifdef GAME
	return ThisCall<float>(0x6041D0, this);
#else
	return ThisCall<float>(0x56F900, this);
#endif
}

// GAME - 0x9442E0
void TESNPC::SetHeight(float afHeight) {
	fHeight = afHeight;
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

// GAME - 0x6053F0
void TESNPC::SetWeight(float afWeight) {
	fWeight = afWeight;
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
// GECK - 0x56F2E0
FaceGenCoords* TESNPC::GetOffsetFaceCoord() {
#ifdef GAME
	return ThisCall<FaceGenCoords*>(0x601800, this);
#else
	return ThisCall<FaceGenCoords*>(0x56F2E0, this);
#endif
}

// GAME - 0x603790
// GECK - 0x571CC0
void TESNPC::CopyHeadData(TESNPC* apSource) {
#ifdef GAME
	ThisCall(0x603790, this, apSource);
#else
	ThisCall(0x571CC0, this, apSource);
#endif
}

#ifdef GAME
// GAME - 0x60B240
void TESNPC::SwitchRace(TESRace* apRace, Actor* apActor) {
	ThisCall(0x60B240, this, apRace, apActor);
}
#endif

// GAME - 0x605D70
// GECK - 0x573390
void TESNPC::ReplaceRefModel(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x605D70, this, apRef);
#else
	ThisCall(0x573390, this, apRef);
#endif
}

// GAME - 0x603FC0
// GECK - 0x56F780
uint32_t TESNPC::GetFormHealthLeveled(bool abAddBase) {
#ifdef GAME
	return ThisCall<uint32_t>(0x603FC0, this, abAddBase);
#else
	return ThisCall<uint32_t>(0x56F780, this, abAddBase);
#endif
}
