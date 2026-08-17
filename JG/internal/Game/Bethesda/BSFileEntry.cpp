#include "BSFileEntry.hpp"

#define FULL_OFFSET 1

uint32_t BSFileEntry::GetFileSize() const {
	return uiSize.uiSize;
}

uint32_t BSFileEntry::GetFileOffset() const {
#if FULL_OFFSET
	return uint32_t(uiOffset);
#else
	return uiOffset.uiOffset;
#endif
}

void BSFileEntry::SetOffset(uint32_t auiOffset) {
#if FULL_OFFSET
	uiOffset = auiOffset;
#else
	uiOffset.uiOffset = auiOffset;
#endif
}

bool BSFileEntry::IsSecondaryArchive() const {
#if FULL_OFFSET
	return false;
#else
	return uiOffset.bSecondaryArchive;
#endif
}

bool BSFileEntry::GetCompressionFlag() const {
	return uiSize.bCompression;
}

bool BSFileEntry::IsChecked() const {
	return uiSize.bChecked;
}

void BSFileEntry::SetChecked(bool abChecked) {
	uiSize.bChecked = abChecked;
}

bool BSFileEntry::IsInvalidated() const {
	return GetFileOffset() == 0;
}