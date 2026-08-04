#pragma once

class NiSearchPath {
public:
	uint32_t	m_uiNextPath;
	char		m_acFilePath[260];
	char		m_acReferencePath[260];
};

ASSERT_SIZE(NiSearchPath, 0x20C);