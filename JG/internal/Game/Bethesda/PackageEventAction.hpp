#pragma once

class TESIdleForm;
class Script;
class TESTopic;

class PackageEventAction {
public:
	PackageEventAction();
	~PackageEventAction();

	TESIdleForm*	pIdle;
	Script*			pScript;
	TESTopic*		pTopic;
	uint32_t		eType;
};

ASSERT_SIZE(PackageEventAction, 0x10);