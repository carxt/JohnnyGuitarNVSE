#pragma once

class Script;
struct ScriptEventList;
#define PASS_VARARGS  scriptObj, eventList
#define VARARGS Script *scriptObj, ScriptEventList *eventList

//All thanks to jazzisparis for the code, since it's way faster than tanf.

extern float tan_p(float angle);

extern float dTan(float angle);

extern float fastDTan(float value);

extern void setVarByName(VARARGS, const char* var_name, float value);

//Only ready for a 24-bit BMP, will check for non-24 bit later.
//Also currently doesn't handle negative height/width BMPs, will fix later
extern bool ReadBMP24(char* filename, unsigned long& R, unsigned long& G, unsigned long& B, unsigned long PixelW, unsigned long PixelH);