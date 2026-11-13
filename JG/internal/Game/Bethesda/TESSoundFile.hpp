#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESSoundFile : public BaseFormComponent {
public:
	TESSoundFile();

#ifdef EDITOR
	virtual void	Func_12(HWND, int32_t);
#endif
	virtual void	SetSoundFile(const char* apPath);

	BSString	strPath;

	const char* GetSoundFile() const;
	uint32_t GetSoundFileLength() const;
};

ASSERT_SIZE(TESSoundFile, 0xC);