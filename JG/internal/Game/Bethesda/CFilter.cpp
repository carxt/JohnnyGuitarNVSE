#include "CFilter.hpp"

CFilter::CFilter(uint32_t auiFilter) : uiFilter(auiFilter) {}

// GAME - 0x622290
CFilter::CFilter(COL_LAYER aeLayer, uint32_t auiGroup, COL_BIPED_PART aePart) {
	Init(aeLayer, auiGroup, aePart);
}

// GAME - 0x6222C0
void CFilter::Init(COL_LAYER aeLayer, uint32_t auiGroup, COL_BIPED_PART aePart) {
	uiFilter.eLayer		= aeLayer;
	uiFilter.ePart		= aePart;
	uiFilter.usGroup	= auiGroup;
}

// GAME - 0x43B4D0
COL_LAYER CFilter::GetLayer() const {
	return static_cast<COL_LAYER>(uiFilter.eLayer);
}

// GAME - 0x4A39F0
void CFilter::SetLayer(COL_LAYER aeLayer) {
	uiFilter.eLayer = aeLayer;
}

// GAME - 0x4A3A20
uint32_t CFilter::GetGroup() const {
	return uiFilter.usGroup;
}

// GAME - 0x59CE80
void CFilter::SetGroup(uint32_t auiGroup) {
	uiFilter.usGroup = auiGroup;
}

// GAME - 0x4D9DA0
COL_BIPED_PART CFilter::GetPart() const {
	return static_cast<COL_BIPED_PART>(uiFilter.ePart);
}

void CFilter::SetPart(COL_BIPED_PART aePart) {
	uiFilter.ePart = aePart;
}

// GAME - 0x6240B0
uint32_t CFilter::GetBipedPart() const {
	return GetPart();
}

bool CFilter::IsMoppScaled() const {
	return uiFilter.bMoppScaled;
}

void CFilter::SetMopScaled(bool abScaled) {
	uiFilter.bMoppScaled = abScaled;
}

bool CFilter::IsDisabled() const {
	return uiFilter.bDisabled;
}

// GAME - 0x810F90
void CFilter::SetDisabled(bool abDisabled) {
	uiFilter.bDisabled = abDisabled;
}

bool CFilter::IsLinkedGroup() const {
	return uiFilter.bLinkedGroup;
}

void CFilter::SetLinkedGroup(bool abLinked) {
	uiFilter.bLinkedGroup = abLinked;
}

bool CFilter::IsBipLayer() const {
	const COL_LAYER eLayer = GetLayer();
	return eLayer == COL_LAYER::BIPED || eLayer == COL_LAYER::DEAD_BIP;
}

bool CFilter::IsLinked(CFilter aInfo) const {
	return (uiFilter & aInfo.uiFilter) & Flags::LINKED_GROUP;
}

bool CFilter::IsDifferentGroup(CFilter aInfo) const {
	return (uiFilter ^ aInfo.uiFilter) & Flags::GROUP_MASK;
}
