#include "BSTasklet.hpp"

// GAME - 0x6C5E40
BSTasklet::BSTasklet() : pData(nullptr) {
}

BSTasklet::BSTasklet(BSTaskletData* apData) : pData(apData) {
}

// GAME - 0x6C5E70
BSTasklet::~BSTasklet() {
}

BSTaskletData* BSTasklet::GetTaskData() const {
	return pData;
}

// GAME - 0x6ECD40
void BSTasklet::SetTaskData(BSTaskletData* apData) {
	pData = apData;
}
