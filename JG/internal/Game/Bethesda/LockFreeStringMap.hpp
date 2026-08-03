#pragma once

#include "LockFreeMap.hpp"

template<class T>
class LockFreeStringMap : public LockFreeMap<const char*, T> {
public:
	LockFreeStringMap(uint32_t auiMaxThreads, uint32_t auiBucketCount, uint32_t auiDeleteBatchSize);
	~LockFreeStringMap() override;
	uint32_t	GetBucketForKey(const char* apKey) override;
	void		DeleteKey(const char* apKey) override;
	const char*	CopyKey(const char* apKey) override;
	void		CopyKeyDirect(const char* apKey, const char*& arCopiedKey) override;
	bool		IsKeyGreaterOrEqual(const char* apKey1, const char* apKey2) const override;
	bool		IsKeyEqual(const char* apKey1, const char* apKey2) const override;

	class LockFreeStringMapIterator : public LockFreeMap<const char*, T>::LockFreeMapIterator {
	public:
		LockFreeStringMapIterator();
		virtual ~LockFreeStringMapIterator();
		virtual void ClearKey() override;

		char cBuffer[256];
	};
};

#include "LockFreeStringMap.inl"