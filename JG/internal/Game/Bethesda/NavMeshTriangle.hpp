#pragma once

class NavMeshTriangle {
public:
	struct ALIGN4 _CoverFlags {
		enum Flags {
			DATA_MASK	= 0xF,
			SIDE_LEFT	= 1u << 4,
			SIDE_RIGHT	= 1u << 5,
		};

		uint8_t ucData		: 4;
		uint8_t	bSideLeft	: 1;
		uint8_t	bSideRight	: 1;
	};
	using CoverFlags = _CoverFlags::Flags;

	struct ALIGN4 _TriangleFlags {
		enum Flags {
			EDGE_INFO_MASK		= 7,
			OBJECT_COUNT_MASK	= 0xE000,
			OBJECT_COUNT_POS	= 13,
			LARGE_ACTOR			= 0x10,
			DISABLED			= 0x20,
			PREFERRED			= 0x40,
			WATER				= 0x200,
			DOOR				= 0x400,
			CLOSED_DOOR			= 0x1000,
			COVER_OFFSET		= 0x10,
			COVER_MASK			= 0xFBE0000,
			COVER_WALL_MASK		= 0xFFF0000,
			AVOID_NODE			= 0x80000000,
		};

		uint32_t uiEdgeInfo		: 3;
		uint32_t				: 1;
		uint32_t bLargeActor	: 1;
		uint32_t bDisabled		: 1;
		uint32_t bPreferred		: 1;
		uint32_t				: 2;
		uint32_t bWater			: 1;
		uint32_t bDoor			: 1;
		uint32_t				: 1;
		uint32_t bClosedDoor	: 1;
		uint32_t uiObjectCount  : 3;

		uint32_t uiCover0_Value	: 4;
		uint32_t bCover0_Left	: 1;
		uint32_t bCover0_Right	: 1;

		uint32_t uiCover1_Value	: 4;
		uint32_t bCover1_Left	: 1;
		uint32_t bCover1_Right	: 1;

		uint32_t				: 3;

		uint32_t bAvoidNode		: 1;

		uint32_t GetEdgeCover(uint16_t ausEdge) const {
			return *reinterpret_cast<const uint32_t*>(this) >> (6 * ausEdge + COVER_OFFSET);
		}
	};
	using Flags = _TriangleFlags::Flags;

	uint16_t					usVertices[3];
	uint16_t					usTriangles[3]; // Neighbor triangles
	Bitfield<_TriangleFlags>	uiFlags;

	uint16_t GetVertex(uint16_t ausVertex) const;
	uint16_t GetTriOrExtraInfo(uint16_t ausTriangle) const;
	uint16_t GetTriangle(uint16_t ausTriangle) const;

	void GetVerts(uint16_t& ausVertex0, uint16_t& ausVertex1, uint16_t& ausVertex2) const;
	void GetSides(uint16_t& ausTriangle0, uint16_t& ausTriangle1, uint16_t& ausTriangle2) const;

	void InvalidateVertex(uint16_t ausVertex);
	void InvalidateTriangle(uint16_t ausTriangle);

	bool IsVertexValid(uint16_t ausVertex) const;
	bool IsEdgeConnected(uint16_t ausEdge) const;
	bool IsEdgeOpen(uint16_t ausEdge) const;

	bool HasEdgeExtraInfo() const;

	bool EdgeHasExtraInfo(uint8_t aucTriangle) const;

	uint16_t GetEdgeExtraInfo(uint16_t ausTriangle) const;

	uint32_t GetObjectCount() const;

	bool GetFlag(uint32_t auiFlag) const;
	void SetFlag(uint32_t auiFlag);

	bool IsLargeActor() const;
	bool IsDisabled() const;
	bool IsPreferred() const;
	bool IsWater() const;
	bool IsDoor() const;

	bool HasCoverOrWallFlags() const;

	void GetEdgeCoverData(uint16_t ausEdge, uint16_t& ausCoverValue, bool& abLeft, bool& abRight) const;
	bool GetEdgeSides(uint16_t ausEdge, bool& abLeft, bool& abRight) const;
	uint32_t GetEdgeCover(uint16_t ausEdge) const;
	void SetEdgeCover(uint16_t ausEdge, uint16_t ausCoverValue, bool abLeft, bool abRight);

	static float GetCoverHeight(uint32_t auiVal);
};

ASSERT_SIZE(NavMeshTriangle, 0x10);