#pragma once

#include "bhkTTNode.hpp"

// GAME - 0x620720
template<typename T>
inline bhkTTNode<T>::bhkTTNode(T* apReference, hkpCollidable* apCollidable) {
	pReference	= apReference;
	pCollidable = apCollidable;
	uiFlags		= 0;
	pNext		= nullptr;
}

template<typename T>
inline uint32_t bhkTTNode<T>::GetFlags(uint32_t auiFlags) const {
	return uiFlags.Get(auiFlags);
}

// GAME - 0x620760
template<typename T>
inline void bhkTTNode<T>::SetFlags(uint32_t auiFlags, bool abSet) {
	uiFlags.Set(auiFlags, abSet);
}

// GAME - 0x6ECD40
template<typename T>
inline void bhkTTNode<T>::SetNext(bhkTTNode* apNext) {
	pNext = apNext;
}

// GAME - 0x726070
template<typename T>
inline bhkTTNode<T>* bhkTTNode<T>::GetNext() const {
	return pNext;
}

// GAME - 0x44DDC0
template<typename T>
inline hkpCollidable* bhkTTNode<T>::GetCollidable() const {
	return pCollidable;
}

// GAME - 0x84E3A0
template<typename T>
inline T* bhkTTNode<T>::GetReference() const {
	return pReference;
}

// GAME - 0x620810
template<typename T>
inline bhkTTNode<T>* bhkTTNode<T>::GetEntry(const hkpCollidable* apCollidable) {
	bhkTTNode* pIter = this;
	while (pIter && pIter->GetCollidable() != apCollidable)
		pIter = pIter->GetNext();
	return pIter;
}

// GAME - 0x57C400
template<typename T>
inline bhkTTNode<T>* bhkTTNode<T>::GetEntry(const T* apReference) {
	bhkTTNode* pIter = this;
	while (pIter && pIter->GetReference() != apReference)
		pIter = pIter->GetNext();
	return pIter;
}
