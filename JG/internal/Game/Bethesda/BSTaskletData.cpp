#include "BSTaskletData.hpp"

// GAME - 0x6C78D0
BSTaskletData::BSTaskletData() {
	bYielding = false;
}

// GAME - 0x6C78F0
BSTaskletData::~BSTaskletData() {
}

bool BSTaskletData::OnStartup() {
	return true;
}

void BSTaskletData::Process() {
}

void BSTaskletData::OnComplete() {
}

// GAME - 0x6EA330
void BSTaskletData::TaskYield() {
	bYielding = true;
}
