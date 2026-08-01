#pragma once

class Script;
class ScriptLocals;
#define PASS_VARARGS  apScript, apScriptLocals
#define VARARGS Script *apScript, ScriptLocals *apScriptLocals
#define VAR_NAME_SIZE 64

//All thanks to jazzisparis for the code, since it's way faster than tanf.

extern float __fastcall tan_p(float angle);

extern float __fastcall dTan(float angle);

extern float __fastcall fastDTan(float value);

extern void __fastcall setVarByName(VARARGS, const char* var_name, float value);

//Only ready for a 24-bit BMP, will check for non-24 bit later.
//Also currently doesn't handle negative height/width BMPs, will fix later
extern bool __fastcall ReadBMP24(char* filename, unsigned long& R, unsigned long& G, unsigned long& B, unsigned long PixelW, unsigned long PixelH);