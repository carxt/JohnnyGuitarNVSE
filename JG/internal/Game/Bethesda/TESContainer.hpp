#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"
#include "ContainerObject.hpp"

class TESObjectREFR;

class TESContainer : public BaseFormComponent {
public:
	TESContainer();
	~TESContainer();

	BSSimpleList<ContainerObject*> kObjects;

	static TESContainer* Create(TESContainer* apThis);
	void Destroy();

	const BSSimpleList<ContainerObject*>* GetObjectList() const;
	BSSimpleList<ContainerObject*>* GetObjectList();

	void AddContainerContents(TESContainer* apSource);

	void AddContainerToReference(TESObjectREFR* apRef, bool abShowMessage);

	float GetContainerWeight(bool abHardcore) const;

	uint32_t GetObjectCount(TESBoundObject* apObject);

	bool HasObject(TESBoundObject* apObject) const;

	static bool ContainerCanHoldType(uint32_t auiFormType);
};

ASSERT_SIZE(TESContainer, 0xC);