#pragma once

class Setting {
public:
	Setting();
	virtual ~Setting();
	virtual bool IsPrefSetting() const;

	enum Type {
		kSetting_Bool = 0,
		kSetting_c,
		kSetting_h,
		kSetting_Integer,
		kSetting_Unsigned,
		kSetting_Float,
		kSetting_String,
		kSetting_r,
		kSetting_a,
		kSetting_Other
	};

	union Info {
		const char*		str;
		int32_t			i;
		uint32_t		u;
		float			f;
		bool			b;
		int8_t			c;
		uint8_t			h;
		DWORD			r;
		uint8_t			rgb[4];
	};

	Info		uValue;
	const char* pKey;

	static Type DataType(const char* apKey);

	Type GetType() const {
		return DataType(pKey);
	}

	Info& GetValue() {
		return uValue;
	}

	const char* String() const {
		return uValue.str;
	}

	int32_t Int() const {
		return uValue.i;
	}

	uint32_t UInt() const {
		return uValue.u;
	}

	float Float() const {
		return uValue.f;
	}

	bool Bool() const {
		return uValue.b;
	}

	char Char() const {
		return uValue.c;
	}

	operator bool() const {
		return Bool();
	}

	operator int() const {
		return Int();
	}

	operator unsigned int() const {
		return UInt();
	}

	operator float() const {
		return Float();
	}

	operator const char* () const {
		return String();
	}

	operator char() const {
		return Char();
	}
};

ASSERT_SIZE(Setting, 0xC);