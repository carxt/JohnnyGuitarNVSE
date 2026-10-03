#include "HitData.hpp"

// GAME - 0x9B4D90
HitData::HitData() {
	ThisCall(0x9B4D90, this);
}

HitData::HitData(const HitData& arOther) {
	uiRefCount = 0;
	Copy(arOther);
}

HitData::~HitData() {
}

// GAME - 0x9B4DC0
void HitData::ClearData() {
	ThisCall(0x9B4DC0, this);
}

// GAME - 0x9B4EC0
void HitData::Copy(const HitData& arOther) {
	ThisCall(0x9B4EC0, this, &arOther);
}

HitData& HitData::operator=(const HitData& arOther) {
	Copy(arOther);
	return *this;
}

// GAME - 0x87ADF0
void HitData::IncRefCount() {
	ThisCall(0x87ADF0, this);
}

// GAME - 0x87CEA0
void HitData::DecRefCount() {
	ThisCall(0x87CEA0, this);
}
