#pragma once
#include "events/EventFilteringInterface.h"

struct EventFilter_Null : EventFilter_Base
{
	[[nodiscard]] FilterTypeSetArray ToFilter() const override
	{
		return FilterTypeSetArray{};
	}
};

struct EventFilter_OneForm : EventFilter_Base
{
	TESForm* form = nullptr;

	[[nodiscard]] FilterTypeSetArray ToFilter() const override
	{
		RefID refID = kIgnFilter_RefID;
		if (form) refID = form->refID;
		RefIDSet formSet{ refID };
		return FilterTypeSetArray{ formSet };
	}
};

struct EventFilter_OneForm_OneInt : EventFilter_Base
{
	TESForm* form = nullptr;
	int intID = kIgnFilter_Int;

	[[nodiscard]] FilterTypeSetArray ToFilter() const override
	{
		RefID refID = kIgnFilter_RefID;
		if (form) refID = form->refID;
		RefIDSet formSet{ refID };
		IntSet idSet{ intID };
		return FilterTypeSetArray{ formSet, idSet };
	}
};