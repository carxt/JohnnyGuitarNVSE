#pragma once

#include "NavMeshTriangleEdgePortal.hpp"

class EdgeExtraInfo {
public:
	struct _Type {
		enum Type {
			INVALID					= -1,
			PORTAL					= 0,
			LEDGE_UP				= 1,
			LEDGE_DOWN				= 2,
			ENABLE_DISABLE_PORTAL	= 3,
		};
	};
	using Type = _Type::Type;

	Type						eType	= Type::INVALID;
	NavMeshTriangleEdgePortal	kPortal;
};

ASSERT_SIZE(EdgeExtraInfo, 0xC);