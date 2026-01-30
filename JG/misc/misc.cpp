#include "misc.h"
#include <internal\utility.h>
#include <GameAPI.h>

float tan_p(float angle) {
	angle *= kDbl4dPI;
	double ang2 = angle * angle;
	return angle * (211.849369664121 - 12.5288887278448 * ang2) / (269.7350131214121 + ang2 * (ang2 - 71.4145309347748));
}

float dTan(float angle) {
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

float fastDTan(float value) {
	bool sign = (value < 0);
	if (sign) value = -value;
	float tempRes = dTan(value * kDblPId180);
	return (sign ? -tempRes : tempRes);
}

void setVarByName(VARARGS, const char* var_name, float value) {
	ListNode<VariableInfo>* traverse = scriptObj->varList.Head();
	VariableInfo* varInfo;
	do {
		varInfo = traverse->data;
		if (varInfo) {
			if (!strcmp(((char*)varInfo->name.c_str()), var_name)) {
				ScriptVar* scv = eventList->GetVariable(varInfo->idx);
				if (scv) {
					scv->data = value;
					break;
				}
			}
		}
	} while (traverse = traverse->next);
}

//Only ready for a 24-bit BMP, will check for non-24 bit later.
//Also currently doesn't handle negative height/width BMPs, will fix later
bool ReadBMP24(char* filename, unsigned long& R, unsigned long& G, unsigned long& B, unsigned long PixelW, unsigned long PixelH) {

	FILE* f = NULL;
	if (fopen_s(&f, filename, "rb") != 0)
		return false;

	char info[54];
	fread(info, sizeof(char), 54, f);
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];
	if (width < PixelW || height < PixelH) return false;
	int XPadding = (width * 3 + 3) & (~3);
	BYTE* data = new BYTE[XPadding];
	PixelH = height - (PixelH + 1);
	fseek(f, XPadding * PixelH, SEEK_CUR);
	fread(data, sizeof(BYTE), XPadding, f);
	uint32_t PosX = PixelW * 3;
	B = data[PosX];
	G = data[PosX + 1];
	R = data[PosX + 2];
	fclose(f);
	delete data;
	return true;
}