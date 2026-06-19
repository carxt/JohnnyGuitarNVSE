#pragma once

#include "GameAPI.h"
#include "Bethesda/SettingT.hpp"
#include "Bethesda/GameSettingCollection.hpp"
#include "Bethesda/INISettingCollection.hpp"
#include "Bethesda/INIPrefSettingCollection.hpp"
#include "Bethesda/RendererSettingCollection.hpp"

class CustomGameSetting {
public:
	union Info {
		const char* str;
		int				i;
		unsigned int	u;
		float			f;
		bool			b;
		char			c;
		char			h;
	};

	CustomGameSetting() : __vftable(nullptr), uValue(0), pKey(nullptr) {};
	~CustomGameSetting() = default;

	void*		__vftable;
	Info		uValue;
	const char* pKey;

	void Initialize(const char* apName, float afValue) {
		ThisCall(0x40E0B0, this, apName, afValue);
	}

	void Initialize(const char* apName, double adValue) {
		ThisCall(0x40E0B0, this, apName, static_cast<float>(adValue));
	}

	void Initialize(const char* apName, int32_t aiValue) {
		ThisCall(0x40C150, this, apName, aiValue);
	}

	void Initialize(const char* apName, const char* apValue) {
		ThisCall(0x40C150, this, apName, apValue);
	}

	void Initialize(const char* apName, char acValue) {
		ThisCall(0x40C150, this, apName, acValue);
	}

	float Float() const {
		return uValue.f;
	}

	int32_t Int() const {
		return uValue.i;
	}

	bool Bool() const {
		return uValue.b;
	}

	const Bitfield32& Bitfield() const {
		return *reinterpret_cast<const Bitfield32*>(&uValue.i);
	}
};