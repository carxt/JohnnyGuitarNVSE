#pragma once

#include "Gamebryo/NiIntegerExtraData.hpp"

class NiObjectNET;

NiSmartPointer(BSXFlags);

class BSXFlags : public NiIntegerExtraData {
public:
	BSXFlags();
	virtual ~BSXFlags();

	enum Flags : uint32_t {
		ANIMATED				= 1u << 0,
		HAVOK					= 1u << 1,
		RAGDOLL					= 1u << 2,
		COMPLEX					= 1u << 3,
		ADDON					= 1u << 4,
		EDITOR_MARKER			= 1u << 5,
		DYNAMIC					= 1u << 6,
		ARTICULATED				= 1u << 7,
		IK_TARGET				= 1u << 8,
		EXTERNAL_EMITTANCE		= 1u << 9, // Unused
		SKINNED_WEAPON			= 1u << 10, // Added by JohnnyGuitar
	};

	CREATE_OBJECT(BSXFlags, 0xC43190);
	NIRTTI_ADDRESS(0x1202DE0);

	uint32_t GetFlags(uint32_t auiFlags) const;
	void SetFlags(uint32_t auiFlags, bool abVal);
	void ClearFlags(uint32_t auiFlags);

	bool GetAnimated() const;

	bool GetHavok() const;

	bool GetRagdoll() const;

	bool GetComplex() const;

	bool GetAddon() const;

	bool GetEditorMarker() const;

	bool GetDynamic() const;

	bool GetArticulated() const;

	bool GetIKTarget() const;

	static const NiFixedString& GetTag();

	static BSXFlags* Find(const NiObjectNET* apObject);

	static uint32_t GetFlags(const NiObjectNET* apObject, uint32_t auiFlags);

private:
#ifdef GAME
	static constexpr AddressPtr<NiFixedString*, 0x1202DDC> pTag;
#else
	static constexpr AddressPtr<NiFixedString*, 0xF2CE60> pTag;
#endif
};

ASSERT_SIZE(BSXFlags, 0x10)