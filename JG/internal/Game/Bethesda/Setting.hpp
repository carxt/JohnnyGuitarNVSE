#pragma once

class Setting {
public:
	Setting();
	virtual ~Setting();
	virtual bool IsPrefSetting() const;

	struct _Type {
		enum Type {
			BOOL = 0,
			CHAR,
			UCHAR,
			INT,
			UINT,
			FLOAT,
			STRING,
			RGB,
			RGBA,
			OTHER
		};
	};
	using Type = _Type::Type;

	union Value {
		bool			b;
		int8_t			c;
		uint8_t			h;
		int32_t			i;
		uint32_t		u;
		float			f;
		const char*		s;
		uint8_t			r[3];
		uint8_t			a[4];
	};

	Value		uValue;
	const char* pKey;

	const Value& GetValue() const;
	Value& GetValue();

	const char* Key() const;

	Type DataType() const;
	static Type DataType(const char* apKey);

	uint32_t DataSize() const;

	bool Bool() const;
	operator bool() const;
	Setting& operator=(bool abValue);

	char Char() const;
	operator char() const;
	Setting& operator=(char acValue);

	unsigned char UChar() const;
	operator unsigned char() const;
	Setting& operator=(unsigned char aucValue);

	int32_t Int() const;
	operator int32_t() const;
	Setting& operator=(int32_t aiValue);

	uint32_t UInt() const;
	operator uint32_t() const;
	Setting& operator=(uint32_t auiValue);

	float Float() const;
	operator float() const;
	Setting& operator=(float afValue);

	const char* String() const;
	operator const char*() const;
	Setting& operator=(const char* apValue);

	bool operator==(bool abVal) const;
	bool operator==(int32_t aiVal) const;
};

ASSERT_SIZE(Setting, 0xC);