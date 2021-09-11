#pragma once
#include "events/EventFilteringInterface.h"

// In order to enforce having the ToFilter() method.
struct EventFilter_BaseStruct
{
	virtual ~EventFilter_BaseStruct() = default;
	[[nodiscard]] virtual FilterTypeSetArray ToFilter() const = 0;
};

struct EventFilter_OneForm : EventFilter_BaseStruct
{
	TESForm* form = nullptr;

	[[nodiscard]] FilterTypeSetArray ToFilter() const override
	{
		RefID refID = g_xMarkerID;
		if (form) refID = form->refID;
		RefIDSet formSet{ refID };
		return FilterTypeSetArray{ formSet };
	}
};

struct EventFilter_OneForm_OneInt : EventFilter_BaseStruct
{
	TESForm* form = nullptr;
	int intID = g_IgnoreIntFilter;

	[[nodiscard]] FilterTypeSetArray ToFilter() const override
	{
		RefID refID = g_xMarkerID;
		if (form) refID = form->refID;
		RefIDSet formSet{ refID };
		IntSet idSet{ intID };
		return FilterTypeSetArray{ formSet, idSet };
	}
};