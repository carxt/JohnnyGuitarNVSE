#include "Setting.hpp"

const Setting::Value& Setting::GetValue() const {
	return uValue;
}

Setting::Value& Setting::GetValue() {
	return uValue;
}

const char* Setting::Key() const {
	return pKey;
}

// GAME - 0x4F8940
Setting::Type Setting::DataType() const {
	return DataType(pKey);
}

// GAME - 0xC33090
// GECK - 0x9D19D0
Setting::Type Setting::DataType(const char* apKey) {
#ifdef GAME
	return CdeclCall<Type>(0xC33090, apKey);
#else
	return CdeclCall<Type>(0x9D19D0, apKey);
#endif
}

// GAME - 0xC32FB0
uint32_t Setting::DataSize() const {
#ifdef GAME
	return ThisCall<uint32_t>(0xC32FB0, this);
#else
	if (pKey) {
		switch (*pKey) {
			case 'S':
			case 's':
				if (uValue.s)
					return strlen(uValue.s) + 1;
				return 0;
			case 'a':
			case 'f':
			case 'i':
			case 'r':
			case 'u':
				return 4;
			case 'b':
			case 'c':
			case 'h':
				return 1;
			default:
				return 0;
		}
	}
	return 0;
#endif
}

bool Setting::Bool() const {
	return uValue.b;
}

Setting::operator bool() const {
	return Bool();
}

// GAME - 0x4DE2B0
Setting& Setting::operator=(bool abValue) {
	if (this)
		this->uValue.b = abValue;
	return *this;
}

char Setting::Char() const {
	return uValue.c;
}

Setting::operator char() const {
	return Char();
}

// GAME - 0x4DE2B0
Setting& Setting::operator=(char acValue) {
	if (this)
		this->uValue.c = acValue;
	return *this;
}

unsigned char Setting::UChar() const {
	return uValue.h;
}

Setting::operator unsigned char() const {
	return UChar();
}

// GAME - 0x4DE2B0
Setting& Setting::operator=(unsigned char aucValue) {
	if (this)
		this->uValue.h = aucValue;
	return *this;
}

int32_t Setting::Int() const {
	return uValue.i;
}

Setting::operator int32_t() const {
	return Int();
}

// GAME - 0x45CEA0
Setting& Setting::operator=(int32_t aiValue) {
	if (this)
		this->uValue.i = aiValue;
	return *this;
}

uint32_t Setting::UInt() const {
	return uValue.u;
}

Setting::operator uint32_t() const {
	return UInt();
}

// GAME - 0x45CEA0
Setting& Setting::operator=(uint32_t auiValue) {
	if (this)
		this->uValue.u = auiValue;
	return *this;
}

float Setting::Float() const {
	return uValue.f;
}

Setting::operator float() const {
	return Float();
}

// GAME - 0x4DE290
Setting& Setting::operator=(float afValue) {
	if (this)
		this->uValue.f = afValue;
	return *this;
}

const char* Setting::String() const {
	return uValue.s;
}

Setting::operator const char*() const {
	return String();
}

// GAME - 0xC33170
// GECK - 0x9D1AB0
Setting& Setting::operator=(const char* apValue) {
#ifdef GAME
	return ThisCall<Setting&>(0xC33170, this, apValue);
#else
	return ThisCall<Setting&>(0x9D1AB0, this, apValue);
#endif
}

// GAME - 0x50E640
bool Setting::operator==(bool abVal) const {
	return this && uValue.b == abVal;
}

// GAME - 0x6834A0
bool Setting::operator==(int32_t aiVal) const {
	return this && uValue.i == aiVal;
}