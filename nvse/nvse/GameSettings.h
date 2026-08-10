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

	CustomGameSetting() = default;
	~CustomGameSetting() = default;

	void*		__vftable		= nullptr;
	Info		uValue			= { .i = 0 };
	const char* pKey			= nullptr;
#ifdef EDITOR
	uint32_t	formData[11]	= {};
#endif

	template<typename T>
		requires (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, const char*>)
	void Initialize(const char* apName, const T value) {
#ifdef GAME
		if constexpr (std::is_floating_point_v<T>)
			ThisCall(0x40E0B0, this, apName, static_cast<float>(value));
		else
			ThisCall(0x40C150, this, apName, value);
#else
		if constexpr (std::is_floating_point_v<T>)
			ThisCall(0x491120, this, apName, static_cast<float>(value));
		else
			ThisCall(0x491070, this, apName, value);
#endif
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

	const char* String() const {
		return uValue.str;
	}

	const Bitfield32& Bitfield() const {
		return *reinterpret_cast<const Bitfield32*>(&uValue.i);
	}
};

#ifdef GAME
ASSERT_SIZE(CustomGameSetting, 0xC);
#else
ASSERT_SIZE(CustomGameSetting, 0x38);
#endif