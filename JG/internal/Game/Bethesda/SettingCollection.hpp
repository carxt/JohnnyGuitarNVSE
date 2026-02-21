#pragma once

#include "Gamebryo/NiTPrimitiveArray.hpp"

template<class T> 
class SettingCollection {
public:
	virtual				~SettingCollection();
	virtual void		Add(T* apSetting);
	virtual void		Remove(T* apSetting);
	virtual uint32_t	GetViewerStrings(NiViewerStringsArray* apStrings);
	virtual bool		WriteSetting(T* apSetting);
	virtual bool		ReadSetting(T* apSetting);
	virtual bool		Open(bool abWrite);
	virtual bool		Close();
	virtual bool		WriteSettings();
	virtual bool		ReadSettings();

	char	cSettingFile[260];
	void*	pHandle;
};

ASSERT_SIZE(SettingCollection<uint32_t>, 0x10C);