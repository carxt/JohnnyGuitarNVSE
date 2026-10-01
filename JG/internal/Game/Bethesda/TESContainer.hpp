#pragma once

#include "BaseFormComponent.hpp"
#include "BSSimpleList.hpp"
#include "ContainerObject.hpp"

class TESObjectREFR;

class TESContainer : public BaseFormComponent {
public:
	TESContainer();
	~TESContainer();

#ifdef EDITOR
	virtual void Func_12(TESContainer*, void*, void*);
#endif

	BSSimpleList<ContainerObject*> kObjects;

	const BSSimpleList<ContainerObject*>* GetObjectList() const;
	BSSimpleList<ContainerObject*>* GetObjectList();

	void AddContainerContents(TESContainer* apSource);

#ifdef GAME
	void AddContainerToReference(TESObjectREFR* apRef, bool abShowMessage);
#endif

	float GetContainerWeight(bool abHardcore) const;

	uint32_t GetObjectCount(const TESBoundObject* apObject) const;

	bool HasObject(const TESBoundObject* apObject) const;

	static bool ContainerCanHoldType(uint8_t aucFormType);

	static bool ContainerCanHoldForm(const TESForm* apForm);
};

ASSERT_SIZE(TESContainer, 0xC);