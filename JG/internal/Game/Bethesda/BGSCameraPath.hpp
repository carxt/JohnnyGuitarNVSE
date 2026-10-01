#pragma once

#include "TESForm.hpp"
#include "NiFormArray.hpp"
#include "TESCondition.hpp"

class BGSCameraShot;

class BGSCameraPath : public TESForm {
public:
	BGSCameraPath();
	~BGSCameraPath();

	struct ALIGN1 _CameraPathFlags {
		enum Flags : uint8_t {
			ZOOM_DISABLE	= 1u << 0,
			ZOOM_SHOT_LIST	= 1u << 1,
			ALLOW_NO_SHOTS	= 1u << 7,
		};

		bool bZoomDisable  : 1;
		bool bZoomShotList : 1;
		bool			   : 5;
		bool bAllowNoShots : 1;
	};
	using CameraPathFlags = _CameraPathFlags::Flags;

	struct Data {
		Bitfield<_CameraPathFlags> ucFlags;
	};

	TESCondition						kConditions;
	BSSimpleList<BGSCameraShot*>		kShots;
	Data								kData;
	NiFormArray*						pChildPaths;
	BGSCameraPath*						pParentPath;
	BGSCameraPath*						pPrevPath;

	TESFORM_TYPE(BGSCameraPath);

	const TESCondition* GetConditions() const;
	TESCondition* GetConditions();

	const BSSimpleList<BGSCameraShot*>* GetShotList() const;
	BSSimpleList<BGSCameraShot*>* GetShotList();

	bool GetZoomDisable() const;
	void SetZoomDisable();

	bool GetZoomShotList() const;
	void SetZoomShotList();

	bool GetZoomDefault() const;
	void SetZoomDefault();

	bool GetAllowNoShots() const;
	void SetAllowNoShots(bool abVal);

	NiFormArray* GetChildArray() const;
	uint32_t GetChildCount() const;

	BGSCameraPath* GetChildByIndex(uint32_t auiIndex) const;
	uint32_t GetIndexForChild(BGSCameraPath* apChild) const;
	void RemoveChild(BGSCameraPath* apPath);
	void RemoveChildAtIndex(uint32_t auiIndex);

	BGSCameraPath* GetParentPath() const;
	BGSCameraPath* GetPrevPath() const;

#ifdef GAME
	BGSCameraPath* GetCameraPathToPlay(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const;
#endif
};

#ifdef GAME
ASSERT_SIZE(BGSCameraPath, 0x38);
#else
ASSERT_SIZE(BGSCameraPath, 0x50);
#endif