#include "GameScript.h"

/***********************************
 ScriptLineBuffer
***********************************/

bool ScriptLineBuffer::Write(const void* buf, uint32_t bufsize) {
	if ((dataOffset + bufsize) >= kBufferSize) return false;
	memcpy(dataBuf + dataOffset, buf, bufsize);
	dataOffset += bufsize;
	return true;
}

bool ScriptLineBuffer::Write32(uint32_t buf) {
	if ((dataOffset + 4) >= kBufferSize) return false;
	*(uint32_t*)(dataBuf + dataOffset) = buf;
	dataOffset += 4;
	return true;
}

bool ScriptLineBuffer::WriteString(const char* buf) {
	uint32_t len = StrLen(buf);
	if ((dataOffset + 2 + len) >= kBufferSize) return false;
	uint8_t* dataPtr = dataBuf + dataOffset;
	*(uint16_t*)dataPtr = len;
	memcpy(dataPtr + 2, buf, len);
	dataOffset += 2 + len;
	return true;
}

bool ScriptLineBuffer::Write16(uint16_t buf) {
	if ((dataOffset + 2) >= kBufferSize) return false;
	*(uint16_t*)(dataBuf + dataOffset) = buf;
	dataOffset += 2;
	return true;
}

bool ScriptLineBuffer::WriteByte(uint8_t buf) {
	if ((dataOffset + 1) >= kBufferSize) return false;
	*(dataBuf + dataOffset) = buf;
	dataOffset++;
	return true;
}

bool ScriptLineBuffer::WriteFloat(double buf) {
	if ((dataOffset + 8) >= kBufferSize) return false;
	memcpy(dataBuf + dataOffset, &buf, 8);
	dataOffset += 8;
	return true;
}