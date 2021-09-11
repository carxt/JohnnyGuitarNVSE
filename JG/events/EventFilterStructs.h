#pragma once
#include "events/EventFilteringInterface.h"

struct EventFilter_OneForm {
	TESForm* form = nullptr;

	FilterTypeSetArray ToFilter() const
	{
		FormSet formSet{ form };
		return FilterTypeSetArray{ formSet };
	}
};

struct EventFilter_OneForm_OneInt {
	TESForm* form = nullptr;
	int intID = -1;

	FilterTypeSetArray ToFilter() const
	{
		FormSet formSet{ form };
		IntSet idSet{ intID };
		return FilterTypeSetArray{ formSet, idSet };
	}
};