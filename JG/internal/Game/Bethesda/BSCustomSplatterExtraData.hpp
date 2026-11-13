#pragma once

#include "Gamebryo/NiExtraData.hpp"
#include "BSSplatterData.hpp"

class BSCustomSplatterExtraData : public NiExtraData {
public:
	BSCustomSplatterExtraData();
	virtual ~BSCustomSplatterExtraData();


	BSSplatterData kData;

	NIRTTI_ADDRESS(0x11C7820);

	static BSCustomSplatterExtraData* Create(BSSplatterData& arData);

	static const NiFixedString& GetTag();

private:
	static constexpr AddressPtr<NiFixedString*, 0x11C77E4> pTag;
};

ASSERT_SIZE(BSCustomSplatterExtraData, 0x1C);