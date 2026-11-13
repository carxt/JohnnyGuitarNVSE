#pragma once

#include "BSMemObject.hpp"
#include "BSSimpleList.hpp"
#include "BSStringT.hpp"
#include "Tile.hpp"
#include "Interface.hpp"

class TileMenu;
class TileExtra;

class Menu {
public:
	virtual						~Menu();
	virtual void				AttachTileByID(uint32_t auiTileID, Tile* apTile);
	virtual void				DoDownClick(uint32_t auiTileID, Tile* apTarget);
	virtual void				DoClick(uint32_t auiTileID, Tile* apTarget);
	virtual void				DoEnter(uint32_t auiTileID, Tile* apTarget);
	virtual void				DoLeave(uint32_t auiTileID, Tile* apTarget);
	virtual void				DoDragEnter(uint32_t auiTileID, Tile* apDragTarget, Tile* apTarget);
	virtual void				DoDragLeave(uint32_t auiTileID, Tile* apDragTarget, Tile* apTarget);
	virtual void				DoStillDown(uint32_t auiTileID, Tile* apTarget);
	virtual void				DoStillDragOver(uint32_t auiTileID, Tile* apTarget);
	virtual void				DoWheelMove(uint32_t auiTileID, Tile* apTarget);
	virtual void				DoIdle();
	virtual bool				DoKey(int32_t aiKey);
	virtual Interface::MenuID	GetMenuID() const;
	virtual bool				DoGamepad(int32_t aiButton, float afKeyState);
	virtual bool				DoGamepadUpEvent(int32_t aiButton, Tile* apTile);
	virtual void				OnXMLDataChange(int32_t aiTrait);
	virtual void				DoControllerSwitch(bool abHasController);

	TileMenu*							pMenu;
	BSSimpleList<Tile::TileTemplate*>	kTemplates;
	Tile*								pLastTile;
	int32_t								iIsModal;
	int32_t								iMenuThickness;
	bool								bRenderedMenu;
	bool								bDeleteTemplates;
	int32_t								iClass;
	Interface::FadeState				eFadeState;

	TileMenu* GetMenuTile() const;
	void SetMenuTile(TileMenu* apMenu, bool abDontAddToStack);

	Tile* RenderTemplate(Tile* apParent, const char* apName, Tile* apLastTile);

	void PrepForVisibility(bool abStayHidden);

	void StartFadeIn();
	void CancelFadeIn();

	void StartFadeOut();
	void CancelFadeOut();

	void InstantFadeOut();

	static bool IsMenuVisible(Interface::MenuID aeMenu);

	static Menu* GetMenuByID(Interface::MenuID aeMenu);
};

ASSERT_SIZE(Menu, 0x28);