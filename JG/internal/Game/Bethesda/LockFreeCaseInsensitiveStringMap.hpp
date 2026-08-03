#pragma once

#include "LockFreeStringMap.hpp"

template<class T>
class LockFreeCaseInsensitiveStringMap : public LockFreeStringMap<T> {
public:
	LockFreeCaseInsensitiveStringMap(uint32_t auiMaxThreads, uint32_t auiBucketCount, uint32_t auiDeleteBatchSize);
	~LockFreeCaseInsensitiveStringMap() override;
	bool		GetAt(const char* apKey, T& arData) override;
	bool		SetAtAlt(const char* apKey, const T& arData, bool abReplaceExisting) override;
	bool		RemoveAt(const char* apKey) override;
	uint32_t	GetBucketForKey(const char* apKey) override;
	const char* CopyKey(const char* apKey) override;
};

ASSERT_SIZE(LockFreeCaseInsensitiveStringMap<char>, 0x40);
ASSERT_SIZE(LockFreeCaseInsensitiveStringMap<char>::LockFreeMapInterface, 0x24);