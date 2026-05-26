#pragma once

class BSFile;

class BGSSaveLoadFile {
public:
	char		cFileName[260];
	BSFile*		pFile;
	uint32_t	uiSimulatedFileSize;
	uint32_t	uiSimulatedFilePosition;
};

ASSERT_SIZE(BGSSaveLoadFile, 0x110);