#pragma once

#include "BSStringT.hpp"
#include "Gamebryo/NiTList.hpp"

class ScriptCompiler;

class MenuConsole {
public:
	MenuConsole();
	~MenuConsole();

	ScriptCompiler*		pCompiler;
	NiTList<BSString>	kStrings;
	NiTList<BSString>	kInputs;
	int32_t				iInputsPos;
	int32_t				iNumStrings;
	int32_t				iLastString;
	bool				bLastMenuMode;
	int32_t				iConsoleLineSpacing;
	int32_t				iConsoleXPos;
	int32_t				iConsoleYPos;
	char				cVisible;
	bool				bIsActive;
	bool				bRecordingBatch;
	int32_t				iRecordingLineCount;
	char				cRecordedCommands[20][100];
	char				cOutputFileName[260];

	static MenuConsole* GetSingleton(bool abCreate = true);

	void Print(const char* apFormat, va_list args);
	void Print(const char* apFormat, ...);

	bool IsConsoleVisible() const;
	bool ToggleVisible();
};

ASSERT_SIZE(MenuConsole, 0x914);