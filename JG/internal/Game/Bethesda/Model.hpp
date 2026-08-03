#pragma once

#include "Gamebryo/NiNode.hpp"

class BSStream;

NiSmartPointer(Model);

class Model {
public:
	Model(const char* apFileName, BSStream* apStream, bool abAssignShaders, bool abKeepUV);
	Model(const char* apFileName, NiNode* apNode);
	~Model();

	const char* pFileName;
	int32_t		iRefCount;
	int32_t		iManualRefCount;
	NiNodePtr	spModel;

	const char* GetFileName() const;

	void IncRefCount();
	void DecRefCount();

	void IncManualRefCount();
	void DecManualRefCount();
	void ModManualRefCount(int32_t aiVal);

	int32_t GetRefCount() const;
	int32_t GetActualRefCount() const;
	int32_t GetManualRefCount() const;

	NiNode* GetModel() const;
};

ASSERT_SIZE(Model, 0x10)