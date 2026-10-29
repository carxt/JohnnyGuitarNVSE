#pragma once

class NiRefObject;

class NiObjectGarbage {
public:

	static void Add(NiRefObject* apObject);

	static bool IsEmpty();

	static uint32_t GetCount();

	static void ClearAll(bool abTryLock);

};