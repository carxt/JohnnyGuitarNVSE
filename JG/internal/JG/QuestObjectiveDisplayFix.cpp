#include "QuestObjectiveDisplayFix.hpp"
namespace QuestObjectiveDisplayFix {
	void Install()
	{
		QuestObjectiveDisplayHook<0x05A5E70>();
	}
}