#pragma once

#include "Setting.hpp"

template <typename COLLECTION>
class SettingT : public Setting {
public:
	SettingT();
	virtual ~SettingT();

	static COLLECTION* GetCollection();

private:
	static COLLECTION* pCollection;

	static void InitCollection();
};

#include "SettingT.inl"