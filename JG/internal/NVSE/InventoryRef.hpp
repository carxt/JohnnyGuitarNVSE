#pragma once

class TESBoundObject;
class TESObjectREFR;
class ItemChange;
class ExtraDataList;
class BSExtraData;

struct ItemEntryData {
	ItemEntryData(TESBoundObject* apForm, ItemChange* apItemChange, ExtraDataList* apExtraDataList) :
		pForm(apForm), pItemChange(apItemChange), pExtraDataList(apExtraDataList) {}

	TESBoundObject*	pForm			= nullptr;
	ItemChange*		pItemChange		= nullptr;
	ExtraDataList*	pExtraDataList	= nullptr;
};

class InventoryRef : public ItemEntryData {
public:
	class DeferredAction {
	public:
		enum Type {
			EQUIP,
			REMOVE,
		};

		Type			eType;
		ItemEntryData	pItemData;
		TESObjectREFR*	pTarget;
	};

	class ActionStack {
	public:
		struct Node {
			Node*			pNext;
			DeferredAction	kAction;
		};

		Node* pHead;
	};

	TESObjectREFR*	pContainerRef;
	TESObjectREFR*	pTempRef;
	ActionStack		kDeferredActions;
	ItemChange*		pTempItemChange;
	uint8_t			padding[0x10];
	bool			bDoValidation;
	bool			bRemoved;

	bool __fastcall CreateExtraData(BSExtraData* apExtraData);
};

ASSERT_SIZE(InventoryRef, 0x30);