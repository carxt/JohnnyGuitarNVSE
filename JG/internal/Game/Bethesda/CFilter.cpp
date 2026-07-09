#include "CFilter.hpp"

CFilter::CFilter(uint32_t auiFilter) : uiFilter(auiFilter) {}

// GAME - 0x622290
CFilter::CFilter(COL_LAYER aeLayer, uint32_t auiGroup, BIPED_PART aePart) {
	Init(aeLayer, auiGroup, aePart);
}

// GAME - 0x6222C0
void CFilter::Init(COL_LAYER aeLayer, uint32_t auiGroup, BIPED_PART aePart) {
	uiFilter = aeLayer | (auiGroup << 16) | (aePart << 8);
}

// GAME - 0x43B4D0
COL_LAYER CFilter::GetLayer() const {
	return static_cast<COL_LAYER>(uiFilter & LAYER_MASK);
}

// GAME - 0x4A39F0
void CFilter::SetLayer(COL_LAYER auiLayer) {
	uiFilter &= ~LAYER_MASK;
	uiFilter |= auiLayer & LAYER_MASK;
}

// GAME - 0x4A3A20
uint32_t CFilter::GetGroup() const {
	return uiFilter & GROUP_MASK;
}

// GAME - 0x59CE80
void CFilter::SetGroup(uint32_t auiGroup) {
	uiFilter &= ~GROUP_MASK;
	uiFilter |= auiGroup << 16;
}

// GAME - 0x4D9DA0
BIPED_PART CFilter::GetPart() const {
	return static_cast<BIPED_PART>((uiFilter >> 8) & 0x1F);
}

void CFilter::SetPart(BIPED_PART aePart) {
	uiFilter &= ~PART_MASK;
	uiFilter |= (aePart << 8) & PART_MASK;
}

// GAME - 0x6240B0
uint32_t CFilter::GetBipedPart() const {
	return GetPart();
}

bool CFilter::IsMoppScaled() const {
	return (uiFilter & MOPP_SCALED) != 0;
}

void CFilter::SetMopScaled(bool abScaled) {
	if (abScaled)
		uiFilter |= MOPP_SCALED;
	else
		uiFilter &= ~MOPP_SCALED;
}

bool CFilter::IsDisabled() const {
	return (uiFilter & DISABLED) != 0;
}

// GAME - 0x810F90
void CFilter::SetDisabled(bool abDisabled) {
	if (abDisabled)
		uiFilter |= DISABLED;
	else
		uiFilter &= ~DISABLED;
}

bool CFilter::IsLinkedGroup() const {
	return (uiFilter & LINKED_GROUP) != 0;
}

void CFilter::SetLinkedGroup(bool abLinked) {
	if (abLinked)
		uiFilter |= LINKED_GROUP;
	else
		uiFilter &= ~LINKED_GROUP;
}

bool CFilter::IsBipLayer() const {
	const COL_LAYER eLayer = GetLayer();
	return eLayer == COL_LAYER::BIPED || eLayer == COL_LAYER::DEAD_BIP;
}

bool CFilter::IsLinked(CFilter aInfo) const {
	return (uiFilter & aInfo.uiFilter) & LINKED_GROUP;
}

bool CFilter::IsDifferentGroup(CFilter aInfo) const {
	return (uiFilter ^ aInfo.uiFilter) & GROUP_MASK;
}
