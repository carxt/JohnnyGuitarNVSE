#pragma once

#include "Gamebryo/NiTList.hpp"
#include "BSStringT.hpp"

class ScriptCompiler;

class MenuConsole {
public:
	MenuConsole();
	~MenuConsole();

	struct RecordedCommand {
		char cBuf[100];
	};

	ScriptCompiler*		pConsoleCompiler;
	NiTList<BSString>	kPrintedLines;
	NiTList<BSString>	kInputHistory;
	int32_t				iInputsPos;
	int32_t				iNumStrings;
	int32_t				iLastString;
	bool				bLastMenuMode;
	int32_t				iConsoleLineSpacing;
	int32_t				iConsoleXPos;
	int32_t				iConsoleYPos;
	int8_t				cVisible;
	bool				bIsActive;
	bool				bIsBatchRecording;
	bool				bUnk3B;
	int32_t				iRecordingLineCount;
	RecordedCommand		kRecordedCommands[20];
	char				cOutputFileName[MAX_PATH];

	static MenuConsole* GetSingleton(bool abCreate = true);

	void PrintLine(const char* apFormat, va_list args);
	void PrintLine(const char* apFormat, ...);

	bool IsConsoleVisible() const;
	void SetVisible(int8_t acState);

	bool ToggleVisible();
};

ASSERT_SIZE(MenuConsole, 0x914);