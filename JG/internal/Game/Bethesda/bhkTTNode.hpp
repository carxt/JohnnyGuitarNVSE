#pragma once

class hkpCollidable;

template <typename T>
struct bhkTTNode {
	bhkTTNode(T* apReference, hkpCollidable* apCollidable);

	Bitfield32		uiFlags;
	bhkTTNode*		pNext;
	hkpCollidable*	pCollidable;
	T*				pReference;

	uint32_t GetFlags(uint32_t auiFlags) const;
	void SetFlags(uint32_t auiFlags, bool abSet);

	void SetNext(bhkTTNode* apNext);
	bhkTTNode<T>* GetNext() const;

	hkpCollidable* GetCollidable() const;

	T* GetReference() const;

	bhkTTNode<T>* GetEntry(const hkpCollidable* apCollidable);
	bhkTTNode<T>* GetEntry(const T* apReference);
};

#include "bhkTTNode.inl"

ASSERT_SIZE(bhkTTNode<void>, 0x10);