#pragma once

class NiNode;
class NiPoint3;
class BGSSaveFormBuffer;
class BGSLoadGameBuffer;

class SeenData {
public:
	SeenData();
	virtual ~SeenData();
	virtual void		DrawSeenData(NiNode* apDrawNode, const NiPoint3& arSeenStart, int) const;
	virtual uint32_t	GetSaveSize() const;
	virtual void		SaveGameBGS(BGSSaveFormBuffer* apBuffer) const;
	virtual void		SaveGameTES(uint32_t) const;
	virtual void		LoadGameBGS(BGSLoadGameBuffer* apBuffer);
	virtual void		LoadGameTES(uint32_t);

	Bitfield16 usVerticalSeenBits[16];
};

ASSERT_SIZE(SeenData, 0x24);