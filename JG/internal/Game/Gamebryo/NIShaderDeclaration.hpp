#pragma once

#include "NiObject.hpp"

NiSmartPointer(NiShaderDeclaration);

class NiShaderDeclaration : public NiObject {
public:
	NiShaderDeclaration();
	virtual ~NiShaderDeclaration();

	struct _Parameter {
		enum Parameter {
			INVALID			= -1,
			POSITION		= 0,
			BLEND_WEIGHT	= 1,
			BLEND_INDICES	= 2,
			NORMAL			= 3,
			COLOR			= 4,
			TEXCOORD0		= 5,
			TEXCOORD1		= 6,
			TEXCOORD2		= 7,
			TEXCOORD3		= 8,
			TEXCOORD4		= 9,
			TEXCOORD5		= 10,
			TEXCOORD6		= 11,
			TEXCOORD7		= 12,
			TANGENT			= 13,
			BINORMAL		= 14,
			DATA_ZERO		= 15,
			DATA_ONE		= 16,
			SKIP_COUNT_MASK = 0x40000000,
			EXTRA_DATA_MASK = 0x80000000,
		};
	};
	using Parameter = _Parameter::Parameter;

	struct _ParameterType {
		enum Type {
			FLOAT1			= 0,
			FLOAT2			= 1,
			FLOAT3			= 2,
			FLOAT4			= 3,
			UBYTE_COLOR		= 4,
			UBYTE4			= 5,
			SHORT2			= 6,
			SHORT4			= 7,
			NORM_UBYTE4		= 8,
			NORM_SHORT2		= 9,
			NORM_SHORT4		= 10,
			NORM_USHORT2	= 11,
			NORM_USHORT4	= 12,
			UDEC3			= 13,
			NORM_DEC3		= 14,
			FLOAT16_2		= 15,
			FLOAT16_4		= 16,
			NONE			= 17,
			COUNT,
		};
	};
	using ParameterType = _ParameterType::Type;

	struct _ParameterUsage {
		enum Usage {
			POSITION		= 0,
			BLEND_WEIGHT	= 1,
			BLEND_INDICES	= 2,
			NORMAL			= 3,
			PSIZE			= 4,
			TEX_COORD		= 5,
			TANGENT			= 6,
			BINORMAL		= 7,
			TESS_FACTOR		= 8,
			POSITIONT		= 9,
			COLOR			= 10,
			FOG				= 11,
			DEPTH			= 12,
			SAMPLE			= 13,
			COUNTs,
		};
	};
	using ParameterUsage = _ParameterUsage::Usage;

	virtual bool SetEntry(uint32_t auiEntry, uint32_t auiRegister, NiShaderDeclaration::Parameter aeInput, NiShaderDeclaration::ParameterType aeType, uint32_t auiStream);
	virtual bool RemoveEntry(uint32_t auiEntry, uint32_t auiStream = 0);
};

ASSERT_SIZE(NiShaderDeclaration, 0x8)