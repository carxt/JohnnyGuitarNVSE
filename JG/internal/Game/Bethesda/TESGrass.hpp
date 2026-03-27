#pragma once

#include "TESBoundObject.hpp"
#include "TESModel.hpp"

class TESGrass : public TESBoundObject, public TESModel {
public:
	TESGrass();
	~TESGrass();

	struct _WaterState {
		enum State : uint32_t {
			ABOVE_ONLY_ATLEAST	= 0,
			ABOVE_ONLY_ATMOST	= 1,
			BELOW_ONLY_ATLEAST	= 2,
			BELOW_ONLY_ATMOST	= 3,
			BOTH_ATLEAST		= 4,
			BOTH_ATMOST			= 5,
			BOTH_ATMOST_ABOVE	= 6,
			BOTH_ATMOST_BELOW	= 7,
		};
	};
	using WaterState = _WaterState::State;

	virtual int8_t				GetDensity() const;
	virtual void				SetDensity(int8_t acDensity);
	virtual int8_t				GetMinSlopeDegrees() const;
	virtual void				SetMinSlopeDegrees(int8_t acMinSlopeDegrees);
	virtual int8_t				GetMaxSlopeDegrees() const;
	virtual void				SetMaxSlopeDegrees(int8_t acMaxSlopeDegrees);
	virtual int8_t				GetMinSlope() const;
	virtual int8_t				GetMaxSlope() const;
	virtual int16_t				GetDistanceFromWater() const;
	virtual void				SetDistanceFromWater(int16_t asDistanceFromWater);
	virtual WaterState			GetUnderwaterState() const;
	virtual void				SetUnderwaterState(WaterState aeUnderwaterState);
	virtual float				GetPositionRange() const;
	virtual void				SetPositionRange(float afPositionRange);
	virtual float				GetHeightRange() const;
	virtual void				SetHeightRange(float afHeightRange);
	virtual float				GetColorRange() const;
	virtual void				SetColorRange(float afColorRange);
	virtual float				GetWavePeriod() const;
	virtual void				SetWavePeriod(float afWavePeriod);
	virtual bool				GetVertexLighting() const;
	virtual void				SetVertexLighting(bool abVertexLighting);
	virtual bool				GetUniformScaling() const;
	virtual void				SetUniformScaling(bool abUniformScaling);
	virtual bool				GetFitToSlope() const;
	virtual void				SetFitToSlope(bool abFitToSlope);
	
	struct ALIGN1 _GrassFlags {
		enum Flags : uint8_t{
			VERTEX_LIGHTING	= 1u << 0,
			UNIFORM_SCALING	= 1u << 1,
			FIT_TO_SLOPE	= 1u << 2,
		};
		bool bVertexLighting	: 1;
		bool bUniformScaling	: 1;
		bool bFitToSlope		: 1;
	};
	using GrassFlags = _GrassFlags::Flags;

	struct Data {
		int8_t					cDensity;
		int8_t					cMinSlopeDegrees;
		int8_t					cMaxSlopeDegrees;
		int16_t					sDistanceFromWaterLevel;
		WaterState				eUnderwaterState;
		float					fPositionRange;
		float					fHeightRange;
		float					fColorRange;
		float					fWavePeriod;
		Bitfield<_GrassFlags>	ucFlags;
	};

	Data kData;

	TESFORM_TYPE(TESGrass);
};

ASSERT_SIZE(TESGrass, 0x68);