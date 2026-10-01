#pragma once

class NiFixedString;

namespace FixedStrings {

#define REGISTER_STRING(name) \
	inline const NiFixedString& Get##name() { return *(pStrings[StringName::##name]); }; \

	struct _StringName {
		enum Name {
			Bip01 = 0,
			Bip,
			Bip01Head,
			Bip01Neck,
			Bip01Spine,
			Bip01Spine1,
			MagicNode,
			SpecialIdle_Cast,
			SpecialIdle_AreaEffect,
			AttachSound,
			SoundMarker,
			SkinnedDecalNode,
			DecalNode,
			ModelSwapNode,
			Open,
			Close,
			DVPG,
			Parent,
			Weapon,
			EditorMarker,
			EditorMarker0,
			EditorMarker1,
			EditorMarker2,
			ArrowQuiver,
			MarkerSource,
			MarkerTarget,
			AttachLight,
			Skin,
			FaceGenEars,
			Unequip,
			LaserSight,
			AimSight,
			Grass,
			Decal,
			PermanentDecal,
			GrabLeft,
			GrabRight,
			Arrow0,
			ArrowBone,
			RaceHeadBiped,
			RaceHeadSkinned,
			HeadAnims,
			EntryPoint,
			Bip01LUpperArm,
			Bip01LForearm,
			Bip01RUpperArm,
			Bip01Yaw,
			Bip01Pitch,
			Bip01Looking,
			Talking,
			Camera1st,
			Camera3rd,
			HeadMeshExport,
			PinnedLimb,
			COUNT,
		};
	};
	using StringName = _StringName::Name;

#ifdef GAME
	constexpr inline AddressPtr<NiFixedString*, 0x11C61A4, StringName::COUNT> pStrings;
#else
	constexpr inline AddressPtr<NiFixedString*, 0xED6384,  StringName::COUNT> pStrings;
#endif

	REGISTER_STRING(Bip01)
	REGISTER_STRING(Bip)
	REGISTER_STRING(Bip01Head)
	REGISTER_STRING(Bip01Neck)
	REGISTER_STRING(Bip01Spine)
	REGISTER_STRING(Bip01Spine1)
	REGISTER_STRING(MagicNode)
	REGISTER_STRING(SpecialIdle_Cast)
	REGISTER_STRING(SpecialIdle_AreaEffect)
	REGISTER_STRING(AttachSound)
	REGISTER_STRING(SoundMarker)
	REGISTER_STRING(SkinnedDecalNode)
	REGISTER_STRING(DecalNode)
	REGISTER_STRING(ModelSwapNode)
	REGISTER_STRING(Open)
	REGISTER_STRING(Close)
	REGISTER_STRING(DVPG)
	REGISTER_STRING(Parent)
	REGISTER_STRING(Weapon)
	REGISTER_STRING(EditorMarker)
	REGISTER_STRING(EditorMarker0)
	REGISTER_STRING(EditorMarker1)
	REGISTER_STRING(EditorMarker2)
	REGISTER_STRING(ArrowQuiver)
	REGISTER_STRING(MarkerSource)
	REGISTER_STRING(MarkerTarget)
	REGISTER_STRING(AttachLight)
	REGISTER_STRING(Skin)
	REGISTER_STRING(FaceGenEars)
	REGISTER_STRING(Unequip)
	REGISTER_STRING(LaserSight)
	REGISTER_STRING(AimSight)
	REGISTER_STRING(Grass)
	REGISTER_STRING(Decal)
	REGISTER_STRING(PermanentDecal)
	REGISTER_STRING(GrabLeft)
	REGISTER_STRING(GrabRight)
	REGISTER_STRING(Arrow0)
	REGISTER_STRING(ArrowBone)
	REGISTER_STRING(RaceHeadBiped)
	REGISTER_STRING(RaceHeadSkinned)
	REGISTER_STRING(HeadAnims)
	REGISTER_STRING(EntryPoint)
	REGISTER_STRING(Bip01LUpperArm)
	REGISTER_STRING(Bip01LForearm)
	REGISTER_STRING(Bip01RUpperArm)
	REGISTER_STRING(Bip01Yaw)
	REGISTER_STRING(Bip01Pitch)
	REGISTER_STRING(Bip01Looking)
	REGISTER_STRING(Talking)
	REGISTER_STRING(Camera1st)
	REGISTER_STRING(Camera3rd)
	REGISTER_STRING(HeadMeshExport)
	REGISTER_STRING(PinnedLimb)

#undef REGISTER_STRING
}