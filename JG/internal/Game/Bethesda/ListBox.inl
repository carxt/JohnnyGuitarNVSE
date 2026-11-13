#pragma once

#include "ListBox.hpp"

// GAME - 0x825C00
template<BSC::LBItem T>
inline Tile* ListBox<T>::GetScrollBar() const {
	return pScrollBar;
}

// GAME - 0x75A0D0
template<BSC::LBItem T>
inline void ListBox<T>::Initialize(Tile* apContainerRect, const char* apTemplateName) {
	ThisCall(0x75A0D0, this, apContainerRect, apTemplateName);
}

template<BSC::LBItem T>
inline const ListBoxItemList<T>* ListBox<T>::GetHead() const {
	return ListBoxItemList<T>::GetHead();
}

template<BSC::LBItem T>
inline ListBoxItemList<T>* ListBox<T>::GetHead() {
	return ListBoxItemList<T>::GetHead();
}

template<BSC::LBItem T>
inline bool ListBox<T>::IsEmpty() const {
	return ListBoxItemList<T>::IsEmpty();
}

// GAME - 0x7D6E90
template<BSC::LBItem T>
inline Tile* ListBox<T>::GetFirstItem() const {
	return ThisCall<Tile*>(0x7D6E90, this);
}

// GAME - 0x7F6FB0
template<BSC::LBItem T>
inline Tile* ListBox<T>::GetLastItem() const {
	return ThisCall<Tile*>(0x7F6FB0, this);
}

// GAME - 0x7A22D0
template<BSC::LBItem T>
inline Tile* ListBox<T>::GetTileFor(const T& arData) const {
	return ThisCall<Tile*>(0x7A22D0, this, &arData);
}

// GAME - 0x7E1110
template<BSC::LBItem T>
inline T ListBox<T>::GetDataFor(const Tile* apTile) const {
	return ThisCall<T>(0x7E1110, this, apTile);
}

// GAME - 0x726C40
template<BSC::LBItem T>
inline uint32_t ListBox<T>::CountItems() const {
	return ThisCall<uint32_t>(0x726C40, this);
}

// GAME - 0x726660
template<BSC::LBItem T>
inline uint32_t ListBox<T>::CountUnfiltered() const {
	return ThisCall<uint32_t>(0x726660, this);
}

// GAME - 0x7D87B0
template<BSC::LBItem T>
inline uint32_t ListBox<T>::CountVisible() const {
	return ThisCall<uint32_t>(0x7D87B0, this);
}

// GAME - 0x7878D0
template<BSC::LBItem T>
inline uint32_t ListBox<T>::CountSelected() const {
	return ThisCall<uint32_t>(0x7878D0, this);
}

// GAME - 0x764430
template<BSC::LBItem T>
inline Tile* ListBox<T>::AddItem(T aData, const char* apItemString, pfnCompareFunc_t apComparFunc, const char* apTemplateName) {
	return ThisCall<Tile*>(0x764430, this, aData, apItemString, apComparFunc, apTemplateName);
}

// GAME - 0x7D8040
template<BSC::LBItem T>
inline bool ListBox<T>::RemoveItem(Tile* apTile) {
	return ThisCall<bool>(0x7D8040, this, apTile);
}

// GAME - 0x7F7280
template<BSC::LBItem T>
inline bool ListBox<T>::RemoveAt(uint32_t auiIndex, bool abLiteral) {
	return ThisCall<bool>(0x7F7280, this, auiIndex, abLiteral);
}

// GAME - 0x7877A0
template<BSC::LBItem T>
inline bool ListBox<T>::IsSelected(const Tile* apTile) const {
	return ThisCall<bool>(0x7877A0, this, apTile);
}

// GAME - 0x754930
template<BSC::LBItem T>
inline void ListBox<T>::ToggleSelection(Tile* apTile) {
	ThisCall(0x754930, this, apTile);
}

// GAME - 0x787760
template<BSC::LBItem T>
inline bool ListBox<T>::Select(Tile* apTile) {
	return ThisCall<bool>(0x787760, this, apTile);
}

// GAME - 0x787C20
template<BSC::LBItem T>
inline bool ListBox<T>::Deselect(Tile* apTile) {
	return ThisCall<bool>(0x787C20, this, apTile);
}

// GAME - 0x787850
template<BSC::LBItem T>
inline void ListBox<T>::DeselectAll(bool abUnfilteredOnly) {
	ThisCall(0x787850, this, abUnfilteredOnly);
}

// GAME - 0x7242F0
template<BSC::LBItem T>
inline bool ListBox<T>::IsListItem(const Tile* apTile) const {
	return ThisCall<bool>(0x7242F0, this, apTile);
}

// GAME - 0x7D88A0
template<BSC::LBItem T>
inline bool ListBox<T>::IsEnabled() const {
	return ThisCall<bool>(0x7D88A0, this);
}

// GAME - 0x7A2350
template<BSC::LBItem T>
inline void ListBox<T>::SetEnabled(bool abVal) {
	ThisCall(0x7A2350, this, abVal);
}

// GAME - 0x7A1930
template<BSC::LBItem T>
inline void ListBox<T>::SetAutoUpdate(bool abVal) {
	ThisCall(0x7A1930, this, abVal);
}

// GAME - 0x7D7630
template<BSC::LBItem T>
inline bool ListBox<T>::IsVisible() const {
	return ThisCall<bool>(0x7D7630, this);
}

// GAME - 0x7A5A30
template<BSC::LBItem T>
inline void ListBox<T>::SetVisible(bool abVal) {
	ThisCall(0x7A5A30, this, abVal);
}

// GAME - 0x7312E0
template<BSC::LBItem T>
inline void ListBox<T>::SaveListState() {
	ThisCall(0x7312E0, this);
}

// GAME - 0x7832E0
template<BSC::LBItem T>
inline void ListBox<T>::SetListState(float afNewHighlightIndex, float afNewScrollbarValue) {
	ThisCall(0x7832E0, this, afNewHighlightIndex, afNewScrollbarValue);
}

// GAME - 0x72A660
template<BSC::LBItem T>
inline void ListBox<T>::RestoreListState(bool abPlayFocusSound) {
	ThisCall(0x72A660, this, abPlayFocusSound);
}

// GAME - 0x71A670
template<BSC::LBItem T>
inline void ListBox<T>::Synchronize() {
	ThisCall(0x71A670, this);
}

// GAME - 0x729FE0
template<BSC::LBItem T>
inline void ListBox<T>::Filter(pfnFilterFunc_t apFilterFunc) {
	ThisCall(0x729FE0, this, apFilterFunc);
}

// GAME - 0x7314C0
template<BSC::LBItem T>
inline void ListBox<T>::Traverse(pfnTraverseFunc_t apTraverseFunc, int32_t aiStart, int32_t aiEnd) {
	ThisCall(0x7314C0, this, apTraverseFunc, aiStart, aiEnd);
}
