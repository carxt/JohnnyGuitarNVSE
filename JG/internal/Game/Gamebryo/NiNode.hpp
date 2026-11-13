#pragma once

#include "NiAVObject.hpp"
#include "NiTObjectArray.hpp"

NiSmartPointer(NiNode);

class NiFixedString;

class NiNode : public NiAVObject {
public:
	NiNode();
	virtual ~NiNode();

	virtual void	AttachChild(NiAVObject* apChild, bool abFirstAvail);
	virtual void	InsertChildAt(uint32_t i, NiAVObject* apChild);
	virtual void	DetachChildAlt(NiAVObject* apChild, NiAVObjectPtr& arRemovedChild);
	virtual void	DetachChild(NiAVObject* apChild);
	virtual void	DetachChildAtAlt(uint32_t i, NiAVObjectPtr& arRemovedChild);
	virtual void	DetachChildAt(uint32_t i);
	virtual void	SetAtAlt(uint32_t i, NiAVObject* apChild, NiAVObjectPtr& arRemovedChild);
	virtual void	SetAt(uint32_t i, NiAVObject* apChild);
	virtual void	UpdateUpwardPass();

	NiTObjectArray<NiAVObjectPtr> m_kChildren;

	CREATE_OBJECT(NiNode, 0xA5F030);
	NIRTTI_ADDRESS(0x11F4428);

	static NiNode* Create(uint16_t ausChildCount = 0);

	uint32_t GetArrayCount() const;
	uint32_t GetChildCount() const;
	NiAVObject* GetAt(uint32_t i) const;
	NiAVObject* GetAtChecked(uint32_t i) const;
	NiAVObject* GetLastChild() const;
	void CompactChildArray();
	void SetChildArraySize(uint32_t auiSize);

	void DetachAllChildren();

	void UpdatePropertiesUpward(NiPropertyState*& apParentState);

	template <typename FUNC>
	void ForEachChild(FUNC&& arFunction) const {
		for (uint32_t i = 0; i < GetArrayCount(); i++) {
			NiAVObject* pChild = GetAt(i);
			if (pChild)
				arFunction(pChild);
		}
	}

	template <typename FUNC>
	void ForEachChildRecurse(FUNC&& arFunction) const {
		for (uint32_t i = 0; i < GetArrayCount(); i++) {
			NiAVObject* pChild = GetAt(i);
			if (!pChild)
				continue;

			if (arFunction(pChild) && pChild->IsNode())
				static_cast<NiNode*>(pChild)->ForEachChildRecurse(arFunction);
		}
	}
};

ASSERT_SIZE(NiNode, 0xAC);