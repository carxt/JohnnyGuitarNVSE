// all credits to JazzisParis
#include "internal/utility.h"
#include "nvse/GameAPI.h"
#include "internal/md5/md5.h"
#include "internal/sha1/sha1.h"
#include <time.h>
void LightCS::Enter() {
	UInt32 threadID = GetCurrentThreadId();
	if (owningThread == threadID) {
		enterCount++;
		return;
	}
	while (InterlockedCompareExchange(&owningThread, threadID, 0));
	enterCount = 1;
}

#define FAST_SLEEP_COUNT 10000UL

void LightCS::EnterSleep() {
	UInt32 threadID = GetCurrentThreadId();
	if (owningThread == threadID) {
		enterCount++;
		return;
	}
	UInt32 fastIdx = FAST_SLEEP_COUNT;
	while (InterlockedCompareExchange(&owningThread, threadID, 0)) {
		if (fastIdx) {
			fastIdx--;
			Sleep(0);
		}
		else Sleep(1);
	}
	enterCount = 1;
}

void LightCS::Leave() {
	if (!--enterCount)
		owningThread = 0;
}
bool fCompare(float lval, float rval) {
	return fabs(lval - rval) < FLT_EPSILON;
}

__declspec(naked) int __stdcall lfloor(float value) {
	__asm
	{
		fld		dword ptr[esp + 4]
		fstcw[esp + 4]
		mov		dx, [esp + 4]
		or word ptr[esp + 4], 0x400
		fldcw[esp + 4]
		fistp	dword ptr[esp + 4]
		mov		eax, [esp + 4]
		mov[esp + 4], dx
		fldcw[esp + 4]
		retn	4
	}
}

__declspec(naked) int __stdcall lceil(float value) {
	__asm
	{
		fld		dword ptr[esp + 4]
		fstcw[esp + 4]
		mov		dx, [esp + 4]
		or word ptr[esp + 4], 0x800
		fldcw[esp + 4]
		fistp	dword ptr[esp + 4]
		mov		eax, [esp + 4]
		mov[esp + 4], dx
		fldcw[esp + 4]
		retn	4
	}
}

__declspec(naked) float __stdcall fSqrt(float value) {
	__asm
	{
		fld		dword ptr[esp + 4]
		fsqrt
		retn	4
	}
}

__declspec(naked) double __stdcall dSqrt(double value) {
	__asm
	{
		fld		qword ptr[esp + 4]
		fsqrt
		retn	8
	}
}

double cos_p(double angle) {
	angle *= angle;
	return 0.999999953464 + angle * (angle * (0.0416635846769 + angle * (0.00002315393167 * angle - 0.0013853704264)) - 0.499999053455);
}

double dCos(double angle) {
	if (angle < 0) angle = -angle;
	while (angle > kDblPIx2)
		angle -= kDblPIx2;

	int quad = int(angle * kDbl2dPI);
	switch (quad) {
		case 0:
			return cos_p(angle);
		case 1:
			return -cos_p(kDblPI - angle);
		case 2:
			return -cos_p(angle - kDblPI);
		default:
			return cos_p(kDblPIx2 - angle);
	}
}

double dSin(double angle) {
	return dCos(kDblPId2 - angle);
}

double tan_p(double angle) {
	angle *= kDbl4dPI;
	double ang2 = angle * angle;
	return angle * (211.849369664121 - 12.5288887278448 * ang2) / (269.7350131214121 + ang2 * (ang2 - 71.4145309347748));
}

double dTan(double angle) {
	while (angle > kDblPIx2)
		angle -= kDblPIx2;

	int octant = int(angle * kDbl4dPI);
	switch (octant) {
		case 0:
			return tan_p(angle);
		case 1:
			return 1.0 / tan_p(kDblPId2 - angle);
		case 2:
			return -1.0 / tan_p(angle - kDblPId2);
		case 3:
			return -tan_p(kDblPI - angle);
		case 4:
			return tan_p(angle - kDblPI);
		case 5:
			return 1.0 / tan_p(kDblPIx3d2 - angle);
		case 6:
			return -1.0 / tan_p(angle - kDblPIx3d2);
		default:
			return -tan_p(kDblPIx2 - angle);
	}
}

double dAtan(double value) {
	bool sign = (value < 0);
	if (sign) value = -value;

	bool complement = (value > 1.0);
	if (complement) value = 1.0 / value;

	bool region = (value > kDblTanPId12);
	if (region)
		value = (value - kDblTanPId6) / (1.0 + kDblTanPId6 * value);

	double res = value;
	value *= value;
	res *= (1.6867629106 + value * 0.4378497304) / (1.6867633134 + value);

	if (region) res += kDblPId6;
	if (complement) res = kDblPId2 - res;

	return sign ? -res : res;
}

double dAsin(double value) {
	__asm
	{
		fld		value
		fld		st
		fmul	st, st
		fld1
		fsubrp	st(1), st
		fsqrt
		fdivp	st(1), st
		fstp	value
	}
	return dAtan(value);
}

double dAcos(double value) {
	return kDblPId2 - dAsin(value);
}

double dAtan2(double y, double x) {
	if (x != 0) {
		double z = y / x;
		if (x > 0)
			return dAtan(z);
		else if (y < 0)
			return dAtan(z) - kDblPI;
		else
			return dAtan(z) + kDblPI;
	}
	else if (y > 0)
		return kDblPId2;
	else if (y < 0)
		return -kDblPId2;
	return 0;
}

UInt32 __fastcall GetNextPrime(UInt32 num) {
	if (num <= 2) return 2;
	else if (num == 3) return 3;
	UInt32 a = num / 6, b = num - (6 * a), c = (b < 2) ? 1 : 5, d;
	num = (6 * a) + c;
	a = (3 + c) / 2;
	do {
		b = 4;
		c = 5;
		do {
			d = num / c;
			if (c > d) return num;
			if (num == (c * d)) break;
			c += b ^= 6;
		} while (true);
		num += a ^= 6;
	} while (true);
	return num;
}

__declspec(naked) UInt32 __fastcall RGBHexToDec(UInt32 rgb) {
	__asm
	{
		movzx	eax, cl
		imul	eax, 0xF4240
		movzx	edx, ch
		imul	edx, 0x3E8
		add		eax, edx
		shr		ecx, 0x10
		add		eax, ecx
		retn
	}
}

__declspec(naked) UInt32 __fastcall RGBDecToHex(UInt32 rgb) {
	__asm
	{
		push	ebx
		mov		eax, ecx
		mov		ecx, 0xF4240
		cdq
		idiv	ecx
		mov		ebx, eax
		mov		eax, edx
		mov		ecx, 0x3E8
		cdq
		idiv	ecx
		shl		eax, 8
		add		eax, ebx
		shl		edx, 0x10
		add		eax, edx
		pop		ebx
		retn
	}
}

__declspec(naked) UInt32 __fastcall StrLen(const char* str) {
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		iterHead :
		cmp[eax], 0
			jz		done
			inc		eax
			jmp		iterHead
			done :
		sub		eax, ecx
			retn
	}
}

__declspec(naked) char* __fastcall StrEnd(const char* str) {
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		iterHead :
		cmp[eax], 0
			jz		done
			inc		eax
			jmp		iterHead
			done :
		retn
	}
}

__declspec(naked) bool __fastcall MemCmp(const void* ptr1, const void* ptr2, UInt32 bsize) {
	__asm
	{
		push	ebx
		mov		ebx, [esp + 8]
		iterHead:
		mov		eax, [ecx]
			cmp[edx], eax
			jnz		retnFalse
			add		ecx, 4
			add		edx, 4
			sub		ebx, 4
			jnz		iterHead
			mov		al, 1
			jmp		done
			retnFalse :
		xor al, al
			done :
		pop		ebx
			retn	4
	}
}

__declspec(naked) void __fastcall MemZero(void* dest, UInt32 bsize) {
	__asm
	{
		test	ecx, ecx
		jz		done
		pxor	xmm0, xmm0
		copy16 :
		cmp		edx, 0x10
			jb		copy8
			movdqu	xmmword ptr[ecx], xmm0
			add		ecx, 0x10
			sub		edx, 0x10
			jnz		copy16
			jmp		done
			copy8 :
		test	dl, dl
			jz		done
			cmp		dl, 8
			jb		copy4
			movq	qword ptr[ecx], xmm0
			add		ecx, 8
			sub		dl, 8
			jz		done
			copy4 :
		mov		dword ptr[ecx], 0
			done :
			retn
	}
}

void* (__cdecl* _memcpy)(void* destination, const void* source, size_t num) = memcpy;

__declspec(naked) char* __fastcall StrCopy(char* dest, const char* src) {
	__asm
	{
		push	ebx
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		test	edx, edx
		jz		nullTerm
		xor ebx, ebx
		getSize :
		cmp[edx + ebx], 0
			jz		doCopy
			inc		ebx
			jmp		getSize
			doCopy :
		push	ebx
			push	edx
			push	eax
			call	_memcpy
			add		esp, 0xC
			add		eax, ebx
			nullTerm :
		mov[eax], 0
			done :
			pop		ebx
			retn
	}
}

__declspec(naked) char* __fastcall StrNCopy(char* dest, const char* src, UInt32 length) {
	__asm
	{
		push	ebx
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		test	edx, edx
		jz		nullTerm
		mov		ecx, [esp + 8]
		xor ebx, ebx
		getSize :
		cmp[edx + ebx], 0
			jz		doCopy
			inc		ebx
			cmp		ebx, ecx
			jb		getSize
			doCopy :
		push	ebx
			push	edx
			push	eax
			call	_memcpy
			add		esp, 0xC
			add		eax, ebx
			nullTerm :
		mov[eax], 0
			done :
			pop		ebx
			retn	4
	}
}

__declspec(naked) char* __fastcall StrCat(char* dest, const char* src) {
	__asm
	{
		call	StrEnd
		mov		ecx, eax
		call	StrCopy
		retn
	}
}

__declspec(naked) UInt32 __fastcall StrHash(const char* inKey) {
	__asm
	{
		xor eax, eax
		test	ecx, ecx
		jz		done
		xor edx, edx
		iterHead :
		mov		dl, [ecx]
			cmp		dl, 'Z'
			jg		notCap
			test	dl, dl
			jz		done
			cmp		dl, 'A'
			jl		notCap
			or dl, 0x20
			notCap:
		imul	eax, 0x65
			add		eax, edx
			inc		ecx
			jmp		iterHead
			done :
		retn
	}
}

__declspec(naked) bool __fastcall CmprLetters(const char* lstr, const char* rstr) {
	__asm
	{
		mov		al, [ecx]
		cmp[edx], al
		jz		retnTrue
		cmp		al, 'A'
		jl		retnFalse
		cmp		al, 'z'
		jg		retnFalse
		cmp		al, 'Z'
		jle		isCap
		cmp		al, 'a'
		jl		retnFalse
		isCap :
		xor al, 0x20
			cmp[edx], al
			jz		retnTrue
			retnFalse :
		xor al, al
			retn
			retnTrue :
		mov		al, 1
			retn
	}
}

__declspec(naked) bool __fastcall StrEqualCS(const char* lstr, const char* rstr) {
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retnFalse
		test	edx, edx
		jz		retnFalse
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jnz		retnFalse
		mov		edx, esi
		iterHead :
		mov		al, [ecx]
			test	al, al
			jz		retnTrue
			cmp[edx], al
			jnz		retnFalse
			inc		ecx
			inc		edx
			jmp		iterHead
			retnTrue :
		mov		al, 1
			pop		edi
			pop		esi
			retn
			retnFalse :
		xor al, al
			pop		edi
			pop		esi
			retn
	}
}

__declspec(naked) bool __fastcall StrEqualCI(const char* lstr, const char* rstr) {
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retnFalse
		test	edx, edx
		jz		retnFalse
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jnz		retnFalse
		mov		edx, esi
		iterHead :
		cmp[ecx], 0
			jz		retnTrue
			call	CmprLetters
			test	al, al
			jz		retnFalse
			inc		ecx
			inc		edx
			jmp		iterHead
			retnTrue :
		mov		al, 1
			pop		edi
			pop		esi
			retn
			retnFalse :
		xor al, al
			pop		edi
			pop		esi
			retn
	}
}

__declspec(naked) char __fastcall StrCompare(const char* lstr, const char* rstr) {
	__asm
	{
		push	ebx
		test	ecx, ecx
		jnz		proceed
		test	edx, edx
		jz		retnEQ
		jmp		retnLT
		proceed :
		test	edx, edx
			jz		retnGT
			iterHead :
		mov		al, [ecx]
			mov		bl, [edx]
			test	al, al
			jz		iterEnd
			cmp		al, bl
			jz		iterNext
			cmp		al, 'Z'
			jg		lNotCap
			cmp		al, 'A'
			jl		lNotCap
			or al, 0x20
			lNotCap:
		cmp		bl, 'Z'
			jg		rNotCap
			cmp		bl, 'A'
			jl		rNotCap
			or bl, 0x20
			rNotCap :
			cmp		al, bl
			jl		retnLT
			jg		retnGT
			iterNext :
		inc		ecx
			inc		edx
			jmp		iterHead
			iterEnd :
		test	bl, bl
			jz		retnEQ
			retnLT :
		mov		al, -1
			pop		ebx
			retn
			retnGT :
		mov		al, 1
			pop		ebx
			retn
			retnEQ :
		xor al, al
			pop		ebx
			retn
	}
}

__declspec(naked) char __fastcall StrBeginsCS(const char* lstr, const char* rstr) {
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retn0
		test	edx, edx
		jz		retn0
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jg		retn0
		mov		edx, esi
		iterHead :
		mov		al, [ecx]
			test	al, al
			jz		iterEnd
			cmp[edx], al
			jnz		retn0
			inc		ecx
			inc		edx
			jmp		iterHead
			iterEnd :
		cmp[edx], 0
			setz	al
			inc		al
			pop		edi
			pop		esi
			retn
			retn0 :
		xor al, al
			pop		edi
			pop		esi
			retn
	}
}

__declspec(naked) char __fastcall StrBeginsCI(const char* lstr, const char* rstr) {
	__asm
	{
		push	esi
		push	edi
		test	ecx, ecx
		jz		retn0
		test	edx, edx
		jz		retn0
		mov		esi, ecx
		call	StrLen
		mov		edi, eax
		mov		ecx, edx
		call	StrLen
		cmp		eax, edi
		jg		retn0
		mov		edx, esi
		iterHead :
		cmp[ecx], 0
			jz		iterEnd
			call	CmprLetters
			test	al, al
			jz		retn0
			inc		ecx
			inc		edx
			jmp		iterHead
			iterEnd :
		cmp[edx], 0
			setz	al
			inc		al
			pop		edi
			pop		esi
			retn
			retn0 :
		xor al, al
			pop		edi
			pop		esi
			retn
	}
}

__declspec(naked) void __fastcall FixPath(char* str) {
	__asm
	{
		test	ecx, ecx
		jz		done
		iterHead :
		mov		al, [ecx]
			test	al, al
			jz		done
			cmp		al, 'Z'
			jg		checkSlash
			cmp		al, 'A'
			jl		iterNext
			or byte ptr[ecx], 0x20
			jmp		iterNext
			checkSlash :
		cmp		al, '\\'
			jnz		iterNext
			mov		byte ptr[ecx], '/'
			iterNext :
			inc		ecx
			jmp		iterHead
			done :
		retn
	}
}

__declspec(naked) void __fastcall StrToLower(char* str) {
	__asm
	{
		test	ecx, ecx
		jz		done
		iterHead :
		mov		al, [ecx]
			cmp		al, 'Z'
			jg		iterNext
			test	al, al
			jz		done
			cmp		al, 'A'
			jl		iterNext
			or byte ptr[ecx], 0x20
			iterNext:
		inc		ecx
			jmp		iterHead
			done :
		retn
	}
}

__declspec(naked) void __fastcall ReplaceChr(char* str, char from, char to) {
	__asm
	{
		test	ecx, ecx
		jz		done
		mov		al, [esp + 4]
		iterHead:
		cmp[ecx], 0
			jz		done
			cmp[ecx], dl
			jnz		iterNext
			mov[ecx], al
			iterNext :
		inc		ecx
			jmp		iterHead
			done :
		retn	4
	}
}

__declspec(naked) char* __fastcall FindChr(const char* str, char chr) {
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		iterHead :
		cmp[eax], 0
			jz		retnNULL
			cmp[eax], dl
			jz		done
			inc		eax
			jmp		iterHead
			retnNULL :
		xor eax, eax
			done :
		retn
	}
}

__declspec(naked) char* __fastcall FindChrR(const char* str, UInt32 length, char chr) {
	__asm
	{
		test	ecx, ecx
		jz		retnNULL
		lea		eax, [ecx + edx]
		mov		dl, [esp + 4]
		iterHead:
		cmp		eax, ecx
			jz		retnNULL
			dec		eax
			cmp[eax], dl
			jz		done
			jmp		iterHead
			retnNULL :
		xor eax, eax
			done :
		retn	4
	}
}

__declspec(naked) char* __fastcall SubStr(const char* srcStr, const char* subStr) {
	__asm
	{
		push	ebx
		push	esi
		push	edi
		mov		esi, ecx
		mov		ecx, edx
		call	StrLen
		test	eax, eax
		jz		retnNULL
		mov		edi, edx
		mov		ebx, eax
		mov		ecx, esi
		call	StrLen
		sub		eax, ebx
		mov		ebx, eax
		mainHead :
		cmp		ebx, 0
			jl		retnNULL
			subHead :
		cmp[edx], 0
			jnz		proceed
			mov		eax, esi
			jmp		done
			proceed :
		call	CmprLetters
			test	al, al
			jz		mainNext
			inc		ecx
			inc		edx
			jmp		subHead
			mainNext :
		dec		ebx
			inc		esi
			mov		ecx, esi
			mov		edx, edi
			jmp		mainHead
			retnNULL :
		xor eax, eax
			done :
		pop		edi
			pop		esi
			pop		ebx
			retn
	}
}

__declspec(naked) char* __fastcall SlashPos(const char* str) {
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		iterHead :
		mov		cl, [eax]
			test	cl, cl
			jz		retnNULL
			cmp		cl, '/'
			jz		done
			cmp		cl, '\\'
			jz		done
			inc		eax
			jmp		iterHead
			retnNULL :
		xor eax, eax
			done :
		retn
	}
}

__declspec(naked) char* __fastcall SlashPosR(const char* str) {
	__asm
	{
		call	StrEnd
		test	eax, eax
		jz		done
		iterHead :
		cmp		eax, ecx
			jz		retnNULL
			dec		eax
			mov		dl, [eax]
			cmp		dl, '/'
			jz		done
			cmp		dl, '\\'
			jz		done
			jmp		iterHead
			retnNULL :
		xor eax, eax
			done :
		retn
	}
}

__declspec(naked) char* __fastcall GetNextToken(char* str, char delim) {
	__asm
	{
		push	ebx
		mov		eax, ecx
		xor bl, bl
		iterHead :
		mov		cl, [eax]
			test	cl, cl
			jz		done
			cmp		cl, dl
			jz		chrEQ
			test	bl, bl
			jnz		done
			jmp		iterNext
			chrEQ :
		test	bl, bl
			jnz		iterNext
			mov		bl, 1
			mov[eax], 0
			iterNext :
			inc		eax
			jmp		iterHead
			done :
		pop		ebx
			retn
	}
}

__declspec(naked) char* __fastcall GetNextToken(char* str, const char* delims) {
	__asm
	{
		push	ebx
		push	esi
		mov		eax, ecx
		mov		esi, edx
		xor bl, bl
		mainHead :
		mov		cl, [eax]
			test	cl, cl
			jz		done
			subHead :
		cmp[edx], 0
			jz		wasFound
			cmp		cl, [edx]
			jz		chrEQ
			inc		edx
			jmp		subHead
			chrEQ :
		test	bl, bl
			jnz		mainNext
			mov		bl, 1
			mov[eax], 0
			mainNext :
			inc		eax
			mov		edx, esi
			jmp		mainHead
			wasFound :
		test	bl, bl
			jz		mainNext
			done :
		pop		esi
			pop		ebx
			retn
	}
}

char* __fastcall CopyString(const char* key) {
	char* newKey = (char*)malloc(StrLen(key) + 1);
	StrCopy(newKey, key);
	return newKey;
}

char* __fastcall IntToStr(int num, char* str) {
	if (num < 0) {
		num = -num;
		*str++ = '-';
	}
	int temp = num, digits = 1;
	while (temp /= 10) digits++;
	temp = digits;
	str += digits;
	*str = 0;
	do {
		*--str = '0' + (num % 10);
		num /= 10;
	} while (--digits);
	return str + temp;
}

char* __fastcall FltToStr(float num, char* str) {
	if (num != 0) {
		if (num < 0) {
			*str++ = '-';
			num = -num;
		}
		int intNum = (int)num;
		if (intNum) {
			str = IntToStr(intNum, str);
			if (intNum == num)
				return str;
		}
		else *str++ = '0';
		*str++ = '.';
		intNum = (int)((num - intNum) * 100000);
		int divis = intNum % 10;
		if (divis == 9) intNum++;
		else if (divis == 1) intNum--;
		divis = 10000;
		do {
			*str++ = '0' + (intNum / divis);
			intNum %= divis;
			divis /= 10;
		} while (intNum);
	}
	else *str++ = '0';
	*str = 0;
	return str;
}

int __fastcall StrToInt(const char* str) {
	if (!str) return 0;
	int result = 0;
	bool neg = *str == '-';
	if (neg) str++;
	char chr;
	while (chr = *str++) {
		if ((chr < '0') || (chr > '9')) break;
		result *= 10;
		result += chr - '0';
	}
	return neg ? -result : result;
}

double __fastcall StrToDbl(const char* str) {
	if (!str) return 0;
	double result = 0;
	UInt32 intPart = 0, divisor = 1;
	bool neg = *str == '-', point = false;
	if (neg) str++;
	char chr;
	while (chr = *str++) {
		if ((chr >= '0') && (chr <= '9')) {
			if (point) divisor *= 10;
			intPart *= 10;
			intPart += chr - '0';
		}
		else if (chr == '.') {
			if (point) break;
			point = true;
			result = intPart;
			intPart = 0;
		}
		else break;
	}
	result += ((double)intPart / divisor);
	return neg ? -result : result;
}

char* __fastcall UIntToHex(UInt32 num, char* str) {
	char res[8];
	UInt8 size = 0, temp;
	do {
		temp = num % 0x10;
		res[size++] = temp + ((temp < 10) ? '0' : '7');
	} while (num >>= 4);
	do {
		*str++ = res[--size];
	} while (size);
	*str = 0;
	return str;
}

UInt32 __fastcall HexToUInt(const char* str) {
	if (!str || !*str) return 0;
	char size = 0, chr;
	UInt32 result = 0, mult = 1;
	do {
		str++;
		size++;
	} while (*str && (size < 8));
	do {
		chr = 0x20 | *--str;
		if (chr < '0') break;
		else if (chr <= '9') chr -= '0';
		else if (chr < 'a') break;
		else if (chr <= 'f') chr -= 'W';
		else break;
		result += chr * mult;
		mult <<= 4;
	} while (--size);
	return result;
}

bool __fastcall FileExists(const char* path) {
	DWORD attr = GetFileAttributes(path);
	return (attr != INVALID_FILE_ATTRIBUTES) && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

bool FileStream::Open(const char* filePath) {
	theFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (theFile == INVALID_HANDLE_VALUE)
		return false;
	streamLength = GetFileSize(theFile, NULL);
	return true;
}

bool FileStream::OpenAt(const char* filePath, UInt32 inOffset) {
	theFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (theFile == INVALID_HANDLE_VALUE)
		return false;
	streamLength = GetFileSize(theFile, NULL);
	streamOffset = inOffset;
	if (streamOffset >= streamLength) {
		Close();
		return false;
	}
	if (streamOffset)
		SetFilePointer(theFile, streamOffset, NULL, FILE_BEGIN);
	return true;
}

bool FileStream::OpenWrite(const char* filePath) {
	theFile = CreateFile(filePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (theFile == INVALID_HANDLE_VALUE)
		return false;
	streamOffset = streamLength = GetFileSize(theFile, NULL);
	SetFilePointer(theFile, streamLength, NULL, FILE_BEGIN);
	return true;
}

bool FileStream::Create(const char* filePath) {
	theFile = CreateFile(filePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	return theFile != INVALID_HANDLE_VALUE;
}

bool FileStream::OpenWriteEx(char* filePath, bool append) {
	MakeAllDirs(filePath);
	if (append) {
		if (!OpenWrite(filePath))
			return false;
		if (streamLength) {
			char newLn = '\n';
			WriteBuf(&newLn, 1);
		}
	}
	else if (!Create(filePath))
		return false;
	return true;
}

void FileStream::SetOffset(UInt32 inOffset) {
	if (inOffset > streamLength)
		streamOffset = streamLength;
	else streamOffset = inOffset;
	SetFilePointer(theFile, streamOffset, NULL, FILE_BEGIN);
}

void FileStream::ReadBuf(void* outData, UInt32 inLength) {
	UInt32 bytesRead;
	ReadFile(theFile, outData, inLength, &bytesRead, NULL);
	streamOffset += bytesRead;
}

void FileStream::WriteBuf(const void* inData, UInt32 inLength) {
	if (streamOffset > streamLength)
		SetEndOfFile(theFile);
	UInt32 bytesWritten;
	WriteFile(theFile, inData, inLength, &bytesWritten, NULL);
	streamOffset += bytesWritten;
	if (streamLength < streamOffset)
		streamLength = streamOffset;
}

void FileStream::MakeAllDirs(char* fullPath) {
	char* traverse = fullPath, curr;
	while (curr = *traverse) {
		if ((curr == '\\') || (curr == '/')) {
			*traverse = 0;
			CreateDirectory(fullPath, NULL);
			*traverse = '\\';
		}
		traverse++;
	}
}
bool DebugLog::Create(const char* filePath) {
	theFile = _fsopen(filePath, "wb", 0x20);
	return theFile != NULL;
}

const char kIndentLevelStr[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

void DebugLog::Message(const char* msgStr) {
	if (!theFile) return;
	if (indent < 40)
		fputs(kIndentLevelStr + indent, theFile);
	fputs(msgStr, theFile);
	fputc('\n', theFile);
	fflush(theFile);
}

void DebugLog::FmtMessage(const char* fmt, va_list args) {
	if (!theFile) return;
	if (indent < 40)
		fputs(kIndentLevelStr + indent, theFile);
	vfprintf(theFile, fmt, args);
	fputc('\n', theFile);
	fflush(theFile);
}

DebugLog gLog, s_debug;

void PrintLog(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	gLog.FmtMessage(fmt, args);
	va_end(args);
}

void PrintDebug(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	s_debug.FmtMessage(fmt, args);
	va_end(args);
}
LineIterator::LineIterator(const char* filePath, char* buffer) {
	dataPtr = buffer;
	FileStream sourceFile;
	if (!sourceFile.Open(filePath)) {
		*dataPtr = 3;
		return;
	}
	UInt32 length = sourceFile.GetLength();
	sourceFile.ReadBuf(dataPtr, length);
	*(UInt16*)(dataPtr + length) = 0x300;
	UInt8 data;
	while (data = *buffer) {
		if ((data == '\n') || (data == '\r'))
			*buffer = 0;
		buffer++;
	}
	while (!*dataPtr)
		dataPtr++;
}

void LineIterator::Next() {
	while (*dataPtr)
		dataPtr++;
	while (!*dataPtr)
		dataPtr++;
}

bool FileToBuffer(const char* filePath, char* buffer) {
	FileStream srcFile;
	if (!srcFile.Open(filePath)) return false;
	UInt32 length = srcFile.GetLength();
	if (!length) return false;
	if (length > kMaxMessageLength)
		length = kMaxMessageLength;
	srcFile.ReadBuf(buffer, length);
	buffer[length] = 0;
	return true;
}

void __fastcall GetTimeStamp(char* buffer) {
	time_t rawTime = time(NULL);
	tm timeInfo;
	localtime_s(&timeInfo, &rawTime);
	sprintf_s(buffer, 0x10, "%02d:%02d:%02d", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
}

__declspec(naked) UInt32 __fastcall ByteSwap(UInt32 dword) {
	__asm
	{
		mov		eax, ecx
		bswap	eax
		retn
	}
}

void GetMD5File(const char* filePath, char* outHash) {
	FileStream sourceFile;
	if (!sourceFile.Open(filePath)) return;

	MD5 md5;

	HANDLE handle = sourceFile.GetHandle();

	UInt8 buffer[0x400], digest[0x10];
	UInt32 offset = 0, length;

	while (!sourceFile.HitEOF()) {
		ReadFile(handle, buffer, 0x400, &length, NULL);
		offset += length;
		sourceFile.SetOffset(offset);
		md5.MD5Update(buffer, length);
	}
	md5.MD5Final(digest);

	for (UInt8 idx = 0; idx < 0x10; idx++, outHash += 2)
		sprintf_s(outHash, 3, "%02X", digest[idx]);
}

void GetSHA1File(const char* filePath, char* outHash) {
	FileStream sourceFile;
	if (!sourceFile.Open(filePath)) return;

	SHA1 sha;

	HANDLE handle = sourceFile.GetHandle();

	char buffer[0x400];
	UInt32 offset = 0, length;

	while (!sourceFile.HitEOF()) {
		ReadFile(handle, buffer, 0x400, &length, NULL);
		offset += length;
		sourceFile.SetOffset(offset);
		sha.addBytes(buffer, length);
	}
	unsigned char* digest = sha.getDigest();

	for (UInt8 idx = 0; idx < 0x14; idx++, outHash += 2)
		sprintf_s(outHash, 3, "%02X", digest[idx]);
}

// Taken from xNVSE
UInt8* GetParentBasePtr(void* addressOfReturnAddress, bool lambda) {
	auto* basePtr = static_cast<UInt8*>(addressOfReturnAddress) - 4;
#if _DEBUG
	if (lambda) // in debug mode, lambdas are wrapped inside a closure wrapper function, so one more step needed
		basePtr = *reinterpret_cast<UInt8**>(basePtr);
#endif
	return *reinterpret_cast<UInt8**>(basePtr);
}