#pragma once

#include "BSSimpleList.hpp"
#include "ListBoxBase.hpp"
#include "BSConcepts.hpp"

template<BSC::LBItem T>
struct ListBoxItem {
	ListBoxItem(Tile* apTile, const T& aData) : pTile(apTile), tData(aData) {}

	Tile*	pTile;
	T		tData;
	bool	bFiltered;
};

ASSERT_SIZE(ListBoxItem<void*>, 0xC);

template<BSC::LBItem T>
using ListBoxItemList = BSSimpleList<ListBoxItem<T>*>;

template <BSC::LBItem T>
class ListBox : public ListBoxBase, protected ListBoxItemList<T> {
public:
	using pfnCompareFunc_t	= int32_t(__cdecl*)(ListBoxItem<T>* apA, ListBoxItem<T>* apB);
	using pfnFilterFunc_t	= bool(__cdecl*)(T aData);
	using pfnTraverseFunc_t = void(__cdecl*)(Tile* apTile, T aData);

	ListBox();
	virtual	~ListBox();
	virtual void	RemoveAll();
	virtual void	Sort(pfnCompareFunc_t apSortFunc);

	struct ALIGN2 _Flags {
		enum Flags {
			AUTO_UPDATE		= 1u << 0,
			FROM_CONTAINER	= 1u << 1, // Assumes T is ItemChange*, and fully owned by the ListBox
		};

		bool bAutoUpdate	: 1;
		bool bFromContainer : 1;
	};
	using Flags = _Flags::Flags;

	Tile*				pContainerRect;
	Tile*				pHighlightedItem;
	Tile*				pScrollBar;
	const char*			pTemplateName;
	uint16_t			usNextIndex;
	float				fTotalListHeight;
	float				fSavedHighlightIndex;
	float				fSavedScrollbarValue;
	Bitfield<_Flags>	usFlags;

	Tile* GetScrollBar() const;

	void Initialize(Tile* apContainerRect, const char* apTemplateName);

	const ListBoxItemList<T>* GetHead() const;
	ListBoxItemList<T>* GetHead();

	bool IsEmpty() const;

	Tile* GetFirstItem() const;
	Tile* GetLastItem() const;

	Tile* GetTileFor(const T& arData) const;

	T GetDataFor(const Tile* apTile) const;

	uint32_t CountItems() const;

	uint32_t CountUnfiltered() const;

	uint32_t CountVisible() const;

	uint32_t CountSelected() const;

	Tile* AddItem(T aData, const char* apItemString, pfnCompareFunc_t apComparFunc, const char* apTemplateName);
	bool RemoveItem(Tile* apTile);

	bool RemoveAt(uint32_t auiIndex, bool abLiteral);

	bool IsSelected(const Tile* apTile) const;

	void ToggleSelection(Tile* apTile);

	bool Select(Tile* apTile);
	bool Deselect(Tile* apTile);
	void DeselectAll(bool abUnfilteredOnly);

	bool IsListItem(const Tile* apTile) const;

	bool IsEnabled() const;
	void SetEnabled(bool abVal);

	void SetAutoUpdate(bool abVal);

	bool IsVisible() const;
	void SetVisible(bool abVal);

	void SaveListState();

	void SetListState(float afNewHighlightIndex, float afNewScrollbarValue);

	void RestoreListState(bool abPlayFocusSound);

	void Synchronize();

	void Filter(pfnFilterFunc_t apFilterFunc);

	void Traverse(pfnTraverseFunc_t apTraverseFunc, int32_t aiStart = 0, int32_t aiEnd = INT32_MAX);
};

#include "ListBox.inl"

ASSERT_SIZE(ListBox<void*>, 0x30);