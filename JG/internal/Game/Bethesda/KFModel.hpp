#pragma once

#include "Gamebryo/NiSmartPointer.hpp"

class BSStream;
class BSAnimGroupSequence;
class TESAnimGroup;

NiSmartPointer(KFModel);

class KFModel {
public:
	KFModel(const char* apFileName, BSStream* apStream);
	~KFModel();

	const char*						pFileName;
	NiPointer<BSAnimGroupSequence>	spControllerSequence;
	NiPointer<TESAnimGroup>			spAnimGroup;
	int32_t							iRefCount;
	int32_t							iManualRefCount;

	const char* GetFileName() const;

	BSAnimGroupSequence* GetSequence() const;

	TESAnimGroup* GetAnimGroup() const;

	void IncRefCount();
	void DecRefCount();

	void IncManualRefCount();
	void DecManualRefCount();

	int32_t GetRefCount() const;
	int32_t GetActualRefCount() const;
	int32_t GetManualRefCount() const;
};

ASSERT_SIZE(KFModel, 0x14)