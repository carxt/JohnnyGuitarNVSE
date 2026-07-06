#pragma once

#include "BaseFormComponent.hpp"
#include "BSStringT.hpp"

class TESSoundFile : public BaseFormComponent {
public:
	TESSoundFile();

	virtual void	SetSoundFile(const char* apPath);

	BSString	strPath;

	const char* GetSoundFile() const;
	uint32_t GetSoundFileLength() const;
};

ASSERT_SIZE(TESSoundFile, 0xC);