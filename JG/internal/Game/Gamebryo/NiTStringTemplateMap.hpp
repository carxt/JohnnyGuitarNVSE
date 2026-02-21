#pragma once

#include "NiTMap.hpp"
#include "NiTPointerMap.hpp"

template <class T_Parent, class T_Data>
class NiTStringTemplateMap : public T_Parent {
public:
	NiTStringTemplateMap(uint32_t auiHashSize, bool abCopy);
	virtual ~NiTStringTemplateMap();

	virtual uint32_t	KeyToHashIndex(const char* apKey) const override;
	virtual bool		IsKeysEqual(const char* apKey1, const char* apKey2) const override;
	virtual void		SetValue(NiTMapItem<const char*, T_Data>* apItem, const char* apKey, T_Data val) override;
	virtual void		ClearValue(NiTMapItem<const char*, T_Data>* apItem) override;

	bool m_bCopy;

	void SetAt(const char* apKey, T_Data aData);
};

#include "NiTStringTemplateMap.inl"