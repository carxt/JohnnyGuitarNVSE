#pragma once

class Tile;
class Menu;

class ListBoxBase {
public:
	virtual bool	Highlight(Tile* apTile);
	virtual Tile*	GetHighlightedItem() const;
	virtual Tile*	GetHighlightTarget(uint32_t aeCode) const;
	virtual bool	BelongsTo(const Menu* apMenu) const;
	virtual void	ScrollToHighlight();
	virtual Tile*	GetTileAt(uint32_t auiIndex, bool abLiteral) const;
};

ASSERT_SIZE(ListBoxBase, 0x4);