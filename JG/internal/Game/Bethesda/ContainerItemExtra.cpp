#include "ContainerItemExtra.hpp"

// GAME - 0x40EA20
void ContainerItemExtra::AddToExtraDataList(ExtraDataList* apExtraList, TESHealthForm* apHealth) {
	ThisCall(0x40EA20, this, apExtraList, apHealth);
}